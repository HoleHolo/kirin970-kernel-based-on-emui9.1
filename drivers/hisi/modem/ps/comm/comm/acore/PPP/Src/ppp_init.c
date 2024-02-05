  /*
   * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
   * foss@huawei.com
   *
   * If distributed as part of the Linux kernel, the following license terms
   * apply:
   *
   * * This program is free software; you can redistribute it and/or modify
   * * it under the terms of the GNU General Public License version 2 and
   * * only version 2 as published by the Free Software Foundation.
   * *
   * * This program is distributed in the hope that it will be useful,
   * * but WITHOUT ANY WARRANTY; without even the implied warranty of
   * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   * * GNU General Public License for more details.
   * *
   * * You should have received a copy of the GNU General Public License
   * * along with this program; if not, write to the Free Software
   * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
   *
   * Otherwise, the following license terms apply:
   *
   * * Redistribution and use in source and binary forms, with or without
   * * modification, are permitted provided that the following conditions
   * * are met:
   * * 1) Redistributions of source code must retain the above copyright
   * *    notice, this list of conditions and the following disclaimer.
   * * 2) Redistributions in binary form must reproduce the above copyright
   * *    notice, this list of conditions and the following disclaimer in the
   * *    documentation and/or other materials provided with the distribution.
   * * 3) Neither the name of Huawei nor the names of its contributors may
   * *    be used to endorse or promote products derived from this software
   * *    without specific prior written permission.
   *
   * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   * POSSIBILITY OF SUCH DAMAGE.
   *
   */

 
#include "ppp_init.h"
#include "ppps_pppa_interface.h"
#include "product_config.h"
#include "ppp_public.h"

#include "ppp_input.h"
#include "NVIM_Interface.h"
#include "hdlc_software.h"
#include "acore_nv_id_gucttf.h"
#include "acore_nv_stru_gucttf.h"
#include "nv_stru_gucnas.h"
#include "acore_nv_stru_gucnas.h"

#include "TTFComm.h"
#include "PsLogFilterInterface.h"
#include "LinuxInterface.h"
#include "ppp_atcmd.h"
#include "TTFUtil.h"


#define    THIS_FILE_ID        PS_FILE_ID_PPP_INIT_C

/******************************************************************************
   PPP�������ȼ�����modem_send�ߣ���modem_recv�����
******************************************************************************/
#define PPP_TASK_PRI                                  143

#define PPPA_OFFSETOF(s, m)      /*lint -e(545)*/TTF_OFFSET_OF(s, m)

#define PPPA_ARRAY_SIZE(x)                       (sizeof(x) / sizeof(x[0]))

typedef struct {
    VOS_UINT16                          msgId;
    VOS_UINT16                          traceLen;
}PPPA_MSG_TRACE_LEN_TABLE_STRU;

VOS_UINT8   g_logFilterCfg = VOS_TRUE;

VOS_VOID PPP_BindToCpu(VOS_VOID)
{
    struct cpumask          mask;

    /* ��ȡ��ǰ�̵߳�affinity */
    if (sched_getaffinity(current->pid, &mask) < 0) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "warning: unable to get cpu affinity\n");
        return;
    }

    /* ���CPU��������1��ȥ�󶨺�0 */
    if (cpumask_weight(&mask) > 1) {
        cpumask_clear_cpu(0, &mask);
        if (sched_setaffinity(current->pid, &mask) < 0) {
            PPP_MNTN_LOG(PS_PRINT_WARNING, "warning: unable to set cpu affinity\n");
        }
    }
}

VOS_VOID PPPA_ReadNv(VOS_VOID)
{
    VOS_UINT32                         ret;
    NAS_NV_PRIVACY_FILTER_CFG_STRU     privacyFilterCfg = {0};

    /* ��ȡ��������NV */
    ret = GUCTTF_NV_Read(MODEM_ID_0,
                               en_NV_Item_Privacy_Log_Filter_Cfg,
                               &privacyFilterCfg,
                               sizeof(NAS_NV_PRIVACY_FILTER_CFG_STRU));
    if (ret != NV_OK)
    {
        TTF_LOG( PS_PID_APP_PPP, DIAG_MODE_COMM, PS_PRINT_ERROR, "read log filter nv fail" );
        g_logFilterCfg = VOS_TRUE;
        return;
    }

    g_logFilterCfg  = privacyFilterCfg.ucFilterEnableFlg;
}


VOS_UINT8 PPPA_GetPrivacyFilterCfg(VOS_VOID)
{
    return VOS_TRUE;
}

VOS_VOID* PPPA_FilterPppcPppaMsg(MsgBlock *msg)
{
    VOS_UINT32                          loop;
    PPPS_PPPA_CommMsg                  *commMsg = (PPPS_PPPA_CommMsg*)msg;
    MsgBlock                           *traceMsg = VOS_NULL_PTR;
    PPPA_MSG_TRACE_LEN_TABLE_STRU       traceTable[] = {
        {ID_PPPS_PPPA_NEGO_DATA_IND, PPPA_OFFSETOF(PPPS_PPPA_NegoData, data)},
        {ID_PPPS_PPPA_PDP_ACTIVE_REQ, PPPA_OFFSETOF(PPPS_PPPA_PdpActiveReq, config)}
    };
        
    if (PPPA_GetPrivacyFilterCfg() != VOS_TRUE) {
        return msg;
    }

    if (msg->ulReceiverPid != PS_PID_APP_PPP) {
        return msg;
    }

    for (loop = 0; loop < PPPA_ARRAY_SIZE(traceTable); loop++) {
        if (commMsg->msgId == traceTable[loop].msgId) {
            traceMsg = (MsgBlock*)PS_MEM_ALLOC(PS_PID_APP_PPP, traceTable[loop].traceLen);
            if (traceMsg == VOS_NULL_PTR) {
                return VOS_NULL_PTR;
            }
            PSACORE_MEM_CPY(traceMsg, traceTable[loop].traceLen, msg, traceTable[loop].traceLen);
            traceMsg->ulLength = traceTable[loop].traceLen - VOS_MSG_HEAD_LENGTH;
            return traceMsg;
        }
    }
    return msg;
}

VOS_VOID* PPPA_FilterPppaPppcMsg(MsgBlock *msg)
{
    VOS_UINT32                          loop;
    PPPS_PPPA_CommMsg                  *commMsg = (PPPS_PPPA_CommMsg*)msg;
    MsgBlock                           *traceMsg = VOS_NULL_PTR;
    PPPA_MSG_TRACE_LEN_TABLE_STRU       traceTable[] = {
        {ID_PPPA_PPPS_NEGO_DATA_IND, PPPA_OFFSETOF(PPPS_PPPA_NegoData, data)},
        {ID_PPPA_PPPS_PDP_ACTIVE_RSP, PPPA_OFFSETOF(PPPA_PPPS_PdpActiveRsp, result)}
    };
        
    if (PPPA_GetPrivacyFilterCfg() != VOS_TRUE) {
        return msg;
    }

    if (msg->ulReceiverPid != MSPS_PID_PPPS) {
        return msg;
    }

    for (loop = 0; loop < PPPA_ARRAY_SIZE(traceTable); loop++) {
        if (commMsg->msgId == traceTable[loop].msgId) {
            traceMsg = (MsgBlock*)PS_MEM_ALLOC(PS_PID_APP_PPP, traceTable[loop].traceLen);
            if (traceMsg == VOS_NULL_PTR) {
                return VOS_NULL_PTR;
            }
            PSACORE_MEM_CPY(traceMsg, traceTable[loop].traceLen, msg, traceTable[loop].traceLen);
            traceMsg->ulLength = traceTable[loop].traceLen - VOS_MSG_HEAD_LENGTH;
            return traceMsg;
        }
    }
    return msg;
}

VOS_VOID PPPA_PppcLogFilterInit(VOS_VOID)
{
    PS_OM_LayerMsgReplaceCBReg(PS_PID_APP_PPP, PPPA_FilterPppaPppcMsg);

    PS_OM_LayerMsgReplaceCBReg(MSPS_PID_PPPS, PPPA_FilterPppcPppaMsg);
}

VOS_UINT32    APP_PPP_PidInit(enum VOS_INIT_PHASE_DEFINE InitPhase )
{
    switch( InitPhase ) {
        case   VOS_IP_LOAD_CONFIG:
            PPPA_InitCfgInfo();

            PPPA_ReadNv();

            PPPA_PppcLogFilterInit();
    
            /*��ʼ��PPP�����ݶ���*/
            if (PPP_DataQInit() != VOS_OK) {
                return VOS_ERR;
            }
            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
           break;
    }

    return VOS_OK;
}

VOS_VOID PppMsgTimerProc( struct MsgCB * pMsg )
{
    REL_TIMER_MSG  *pPsMsg  = (REL_TIMER_MSG *)pMsg;

    if (pPsMsg->ulName == PPPA_DATA_DELAY_PROC_TIMER) {
        PPPA_DataEventProc();
    } else {
        PPP_MNTN_LOG1(PS_PRINT_WARNING,"Unknow Timer!\n", pPsMsg->ulName);
    }
}

VOS_VOID PPPA_RcvPppsNegoData(PPPS_PPPA_NegoData *negoData)
{   
    PPP_ZC_STRU *mem = VOS_NULL_PTR;
    if (negoData->dataLen != negoData->ulLength - (sizeof(PPPS_PPPA_NegoData)- VOS_MSG_HEAD_LENGTH)) {
        PPP_MNTN_LOG2(PS_PRINT_WARNING,"wrong ulLength!\n", negoData->dataLen, negoData->ulLength);
        return;
    } 
    
    mem = PPP_MemCopyAlloc(negoData->data, negoData->dataLen, 0);
    PPPA_SendDlDataToAT(PPPA_PPP_ID, mem);
    if (negoData->pktType == PPP_ECHO_REQ) {
        PPPA_INPUT_ProcEchoReq();
    }
/*lint -e429*/
}
/*lint +e429*/

VOS_VOID PPPA_RcvPppsPdpActReq(PPPS_PPPA_PdpActiveReq *pMsg)
{
    if (pMsg->ulLength != sizeof(PPPS_PPPA_PdpActiveReq)- VOS_MSG_HEAD_LENGTH) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING,"wrong ulLength!\n", pMsg->ulLength);
        return;
    } 
    
    At_RcvTeConfigInfoReq(PPPA_PPP_ID, &((pMsg)->config));
}

VOS_VOID PPPA_RcvPppsPppRelInd(PPPS_PPPA_CommMsg *pMsg)
{
    if (pMsg->ulLength != sizeof(PPPS_PPPA_CommMsg)- VOS_MSG_HEAD_LENGTH) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING,"wrong ulLength!\n", pMsg->ulLength);
        return;
    } 
    
    At_RcvPppReleaseInd(PPPA_PPP_ID);
    
    PPP_ReleaseHdlc(PPPA_PPP_ID);
}

VOS_VOID PPPA_RcvHdlcCfgInfo(PPPS_PPPA_HdlcCfg *hdlcCfg)
{

    if (hdlcCfg->ulLength != sizeof(PPPS_PPPA_HdlcCfg)- VOS_MSG_HEAD_LENGTH) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING,"wrong ulLength!\n", hdlcCfg->ulLength);
        return;
    } 
    
    PPP_HDLC_UpdateCfg(PPPA_PPP_ID, hdlcCfg->hisAcf, hdlcCfg->hisPcf, hdlcCfg->hisAccm);
}


VOS_VOID PPPA_PppsMsgProc(struct MsgCB * pMsg)
{
    PPPS_PPPA_CommMsg            *commMsg = (PPPS_PPPA_CommMsg*)pMsg;

    switch (commMsg->msgId) {
        case ID_PPPS_PPPA_NEGO_DATA_IND:
            PPPA_RcvPppsNegoData((PPPS_PPPA_NegoData*)pMsg);
            break;
        case ID_PPPS_PPPA_PDP_ACTIVE_REQ:
            PPPA_RcvPppsPdpActReq((PPPS_PPPA_PdpActiveReq*)pMsg);
            break;
        case ID_PPPS_PPPA_PPP_RELEASE_IND:
            PPPA_RcvPppsPppRelInd(commMsg);
            break;
        case ID_PPPS_PPPA_HDLC_CFG_IND:
            PPPA_RcvHdlcCfgInfo((PPPS_PPPA_HdlcCfg*)pMsg);
            break;
        default:
            PPP_MNTN_LOG1(PS_PRINT_ERROR,"err msg", commMsg->msgId);
    }
}

VOS_VOID PPPA_PppaMsgProc(struct MsgCB* msg)
{
    PPP_InternalMsgHeader *ctrlOper = (PPP_InternalMsgHeader *)msg;

    switch (ctrlOper->msgId) {
        case ID_PPPA_AT_CTRL_OPERATION_MSG:
            PPPA_AtCtrlOperMsgProc(ctrlOper);
            break;
        default:
            PPP_MNTN_LOG1(PS_PRINT_ERROR, "err msg", ctrlOper->msgId);
    }
}

VOS_VOID APP_PPP_MsgProc( struct MsgCB * pMsg )
{
    if(pMsg == VOS_NULL_PTR) {
        return;
    }

    switch (pMsg->ulSenderPid) {
        case VOS_PID_TIMER:
            PppMsgTimerProc(pMsg);
            break;
        case MSPS_PID_PPPS:
            PPPA_PppsMsgProc(pMsg);
            break;
        case PS_PID_APP_PPP:
            PPPA_PppaMsgProc(pMsg);
            break;
        default:
            PPP_MNTN_LOG1(PS_PRINT_ERROR, "err msg", pMsg->ulSenderPid);
    }
}

VOS_VOID APP_PPP_FidTask(VOS_UINT32 para1, VOS_UINT32 para2, VOS_UINT32 para3, VOS_UINT32 para4)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = VOS_ERR;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        PPP_MNTN_LOG(PS_PRINT_ERROR, "APP_PPP_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        PPP_MNTN_LOG(PS_PRINT_ERROR, "APP_PPP_FidTask: ERROR, create event fail.");
        return;
    }

    PPP_BindToCpu();

    ulExpectEvent = PPP_RCV_DATA_EVENT | VOS_MSG_SYNC_EVENT;
    ulEventMask   = VOS_EVENT_ANY | VOS_EVENT_WAIT;

    PPPA_SaveTaskId(ulTaskID);

    for(;;)
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);
        if (VOS_OK != ulRtn)
        {
            PPP_MNTN_LOG(PS_PRINT_ERROR, "APP_PPP_FidTask: ERROR, read event error.");
            continue;
        }

        /* �¼����� */
        if ((ulEvent & PPP_RCV_DATA_EVENT) == PPP_RCV_DATA_EVENT) {
            PPPA_DataEventProc();
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (pMsg != VOS_NULL_PTR) {
            if (pMsg->ulReceiverPid == PS_PID_APP_PPP) {
                APP_PPP_MsgProc(pMsg);
            }

            (VOS_VOID)VOS_FreeMsg(PS_PID_APP_PPP, pMsg);
        }
    }
}

VOS_UINT32 APP_PPP_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;


    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ����PID��ʼ�� */
            ulRslt = VOS_RegisterPIDInfo(PS_PID_APP_PPP,
                                (Init_Fun_Type)APP_PPP_PidInit,
                                (Msg_Fun_Type)APP_PPP_MsgProc);
            if (VOS_OK != ulRslt)
            {
                PS_PRINTF("[pppa]:<APP_PPP_FidInit>, register PPP PID fail!\n");
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_PPP, (VOS_VOIDFUNCPTR)APP_PPP_FidTask);
            if (VOS_OK != ulRslt)
            {
                PS_PRINTF("[pppa]:<APP_PPP_FidInit>, VOS_RegisterMsgTaskEntry fail!\n");
                return VOS_ERR;
            }

            /* �������ȼ� */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_PPP, VOS_PRIORITY_P4);
            if( VOS_OK != ulRslt )
            {
                PS_PRINTF("[pppa]:<APP_PPP_FidInit>, register priority fail!\n");
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


