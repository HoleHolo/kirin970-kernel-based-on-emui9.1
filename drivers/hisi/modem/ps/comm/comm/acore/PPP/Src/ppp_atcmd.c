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


#include "ppp_atcmd.h"
#include "ppps_pppa_interface.h"
#include "ppp_input.h"
#include "product_config.h"
#include "ppp_public.h"
#include "NVIM_Interface.h"
#include "acore_nv_stru_gucnas.h"
#include "nv_stru_gucnas.h"
#include "AdsDeviceInterface.h"



#define THIS_FILE_ID            PS_FILE_ID_PPP_ATCMD_C

#define PPPA_DEF_MRU            1500
#define PPPA_MIN_MRU            296
#define PPPA_DEF_ECHO_LOST_CNT  0xFFFF

typedef struct {
    VOS_UINT16          mru;
    VOS_UINT16          echoMaxLostCnt;
    VOS_UINT32          winsEnable:1;
    VOS_UINT32          chapEnable:1;
    VOS_UINT32          papEnable:1;
    VOS_UINT32          resv:29;
}PPPA_CONFIG_INFO_STRU;

enum PPP_MSG_TYPE_ENUM
{
    AT_PPP_CREATE_RAW_PPP_REQ  = 0x01,      /*PPPģ���յ�AT��CREATE RAW PPPָʾ*/
    AT_PPP_RELEASE_RAW_PPP_REQ     /*PPPģ���յ�AT��RELEASE RAW PPPָʾ*/
};
typedef VOS_UINT32  PPP_MSG_TYPE_ENUM_UINT32;

__STATIC_ PPPA_CONFIG_INFO_STRU   g_pppaCfg = {0};

VOS_VOID PPP_UpdateWinsConfig(VOS_UINT8 ucWins)
{
    g_pppaCfg.winsEnable = (ucWins == WINS_CONFIG_DISABLE) ? VOS_FALSE : VOS_TRUE;
}


__STATIC_ VOS_VOID PPPA_SendPppsCreateInd(VOS_VOID)
{
    PPPA_PPPS_CreatePpp           *createPppInd = VOS_NULL_PTR;

    createPppInd = (PPPA_PPPS_CreatePpp*)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_APP_PPP, sizeof(PPPA_PPPS_CreatePpp));
    if (createPppInd == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "alloc Msg Fail");
        return;
    }
    
    createPppInd->ulReceiverPid             = MSPS_PID_PPPS;
    createPppInd->msgId                     = ID_PPPA_PPPS_CREATE_PPP_IND;
    createPppInd->config.mru                = g_pppaCfg.mru;
    createPppInd->config.chapEnable         = g_pppaCfg.chapEnable;
    createPppInd->config.papEnable          = g_pppaCfg.papEnable;
    createPppInd->config.winsEnable         = g_pppaCfg.winsEnable;
    createPppInd->config.echoMaxLostCnt     = g_pppaCfg.echoMaxLostCnt;

    (VOS_VOID)PS_SEND_MSG(PS_PID_APP_PPP, createPppInd);
}

VOS_VOID PPPA_InitCfgInfo(VOS_VOID) 
{
    PPP_CONFIG_MRU_TYPE_NV_STRU     mruNv  = {0};
    WINS_CONFIG_STRU                winsNv = {0};
    NV_TTF_PPP_CONFIG_STRU          cfgNv  = {0};
    
    g_pppaCfg.mru                  = PPPA_DEF_MRU;
    if ((GUCTTF_NV_Read(MODEM_ID_0, en_NV_Item_PPP_CONFIG_MRU_Type, &mruNv, sizeof(mruNv)) == NV_OK) && 
        (mruNv.usPppConfigType >= PPPA_MIN_MRU) && (mruNv.usPppConfigType <= PPPA_DEF_MRU)) {
        g_pppaCfg.mru              = mruNv.usPppConfigType;
    }

    g_pppaCfg.winsEnable            = VOS_TRUE;
    if ((GUCTTF_NV_Read(MODEM_ID_0, en_NV_Item_WINS_Config, &winsNv, sizeof(winsNv)) == NV_OK) && 
        (winsNv.ucStatus != 0) && (winsNv.ucWins == WINS_CONFIG_DISABLE)) {
        g_pppaCfg.winsEnable        = VOS_FALSE;
    }

    g_pppaCfg.echoMaxLostCnt = PPPA_DEF_ECHO_LOST_CNT;
    g_pppaCfg.papEnable      = VOS_TRUE;
    if (GUCTTF_NV_Read(MODEM_ID_0, en_NV_Item_PPP_CONFIG, &cfgNv, sizeof(cfgNv)) == NV_OK) {
        g_pppaCfg.chapEnable        = cfgNv.enChapEnable;
        g_pppaCfg.papEnable         = cfgNv.enPapEnable;
        g_pppaCfg.echoMaxLostCnt    = cfgNv.usLcpEchoMaxLostCnt;
    }
}

VOS_UINT32 Ppp_CreatePppReq(PPP_ID *pusPppId)
{
    if (PPPA_GetUsedFalg() == VOS_TRUE) {
        return VOS_ERR;
    }

    PPPA_SetUsedFlag(VOS_TRUE);
    *pusPppId = PPPA_PPP_ID;
    PPPA_SendPppsCreateInd();

    PPP_SetupHdlc(PPPA_PPP_ID, VOS_TRUE);
    
    return VOS_OK;
}

__STATIC_ VOS_VOID Ppp_EventMntnInfo(VOS_UINT16       usPppID, VOS_UINT32 ulEvent)
{
    PPP_EVENT_MNTN_INFO_STRU    event = {0};

    event.ulReceiverCpuId = VOS_LOCAL_CPUID;
    event.ulReceiverPid   = PS_PID_APP_PPP;
    event.ulSenderCpuId   = VOS_LOCAL_CPUID;
    event.ulSenderPid     = PS_PID_APP_PPP;
    event.ulLength        = sizeof(event) - VOS_MSG_HEAD_LENGTH;

    event.ulMsgname      = ulEvent;
    event.usPppId        = usPppID;

    PPP_MNTN_TRACE_MSG(&event);
}

VOS_UINT32 Ppp_CreateRawDataPppReq ( PPP_ID *pusPppId)
{
    if (PPPA_GetUsedFalg() == VOS_TRUE) {
        return VOS_ERR;
    }

    PPPA_SetUsedFlag(VOS_TRUE);
    *pusPppId = PPPA_PPP_ID;
    PPP_SetupHdlc(PPPA_PPP_ID, VOS_FALSE);
    Ppp_EventMntnInfo(PPPA_PPP_ID, AT_PPP_CREATE_RAW_PPP_REQ);

    return VOS_OK;
}

VOS_UINT32 Ppp_ReleasePppReq ( PPP_ID usPppId)
{
    if (PPPA_GetUsedFalg() != VOS_TRUE) {
        return VOS_ERR;
    }
    
    PPPA_SetUsedFlag(VOS_FALSE);
    PPP_ClearDataQ();
    PPPA_SendPppsCommMsg(ID_PPPA_PPPS_RELEASE_PPP_IND);

    return VOS_OK;
}

VOS_UINT32 Ppp_ReleaseRawDataPppReq ( PPP_ID usPppId)
{
    if (PPPA_GetUsedFalg() != VOS_TRUE) {
        return VOS_ERR;
    }

    PPPA_SetUsedFlag(VOS_FALSE);
    PPP_ReleaseHdlc(PPPA_PPP_ID);
    Ppp_EventMntnInfo(usPppId, AT_PPP_RELEASE_RAW_PPP_REQ);

    return VOS_OK;
}

__STATIC_ VOS_VOID PPPA_SendPppsPdpActRsp(PPPA_PDP_ACTIVE_RESULT_STRU *pdpActRslt)
{
    PPPA_PPPS_PdpActiveRsp           *pdpActRsp = VOS_NULL_PTR;

    pdpActRsp = (PPPA_PPPS_PdpActiveRsp*)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_APP_PPP, sizeof(PPPA_PPPS_PdpActiveRsp));
    if (pdpActRsp == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "alloc Msg Fail");
        return;
    }
    
    pdpActRsp->ulReceiverPid    = MSPS_PID_PPPS;
    pdpActRsp->msgId            = ID_PPPA_PPPS_PDP_ACTIVE_RSP;
    pdpActRsp->result           = *pdpActRslt;

    (VOS_VOID)PS_SEND_MSG(PS_PID_APP_PPP, pdpActRsp);
}

VOS_UINT32 Ppp_RcvConfigInfoInd(PPP_ID usPppId, PPPA_PDP_ACTIVE_RESULT_STRU *pstAtPppIndConfigInfo)
{
    VOS_UINT8                               ucRabId = 0;
    VOS_UINT32                              ulResult;

    if (PPPA_GetUsedFalg() != VOS_TRUE) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING, "PPP not ues", usPppId);
        return VOS_ERR;
    }

    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if ( !PPP_PPPID_TO_RAB(usPppId, &ucRabId) ) {
        PPP_MNTN_LOG2(PS_PRINT_NORMAL, "Can not get PPP Id", usPppId, ucRabId);
        return VOS_ERR;
    }

    /* ���ʱ��PDP�Ѿ����ע���������ݽ��սӿڡ����⵱ǰ��֧��PPP���Ͳ��š� */
    ulResult= ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)PPP_PushPacketEvent, 0);
    if ( VOS_OK != ulResult )
    {
        PPP_MNTN_LOG1(PS_PRINT_NORMAL, "Register DL CB failed", ucRabId);

        return VOS_ERR;
    }

    PPPA_SendPppsPdpActRsp(pstAtPppIndConfigInfo);

    return VOS_OK;
}

VOS_UINT32 Ppp_RegDlDataCallback(PPP_ID usPppId)
{
    VOS_UINT8                               ucRabId = 0;
    VOS_UINT32                              ulResult;


    if (PPPA_GetUsedFalg() != VOS_TRUE) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING, "PPP not ues", usPppId);
        return VOS_ERR;
    }

    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if (!PPP_PPPID_TO_RAB(usPppId, &ucRabId)){
        PPP_MNTN_LOG2(PS_PRINT_NORMAL, "Can not get PPP Id", usPppId, ucRabId);

        return VOS_ERR;
    }

    /* ���ʱ��PDP�Ѿ����ע���������ݽ��սӿ� */
    ulResult= ADS_DL_RegDlDataCallback(ucRabId, (RCV_DL_DATA_FUNC)PPP_PushRawDataEvent, 0);
    if ( VOS_OK != ulResult ) {
        PPP_MNTN_LOG1(PS_PRINT_WARNING, "Register DL CB failed", ucRabId);
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 PPP_RcvAtCtrlOperEvent(VOS_UINT16 pppId, PPP_AtCtrlOperTypeUint32 operType)
{
    PPP_AT_CtrlOperCmd  *ctrlOper = VOS_NULL_PTR;

    if (operType >= PPP_AT_CTRL_BUTT) {
        PPP_MNTN_LOG2(LOG_LEVEL_WARNING, "invalid para!", pppId, operType);
        return VOS_ERR;
    }

    ctrlOper = (PPP_AT_CtrlOperCmd *)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_APP_PPP, sizeof(PPP_AT_CtrlOperCmd));
    if (ctrlOper == VOS_NULL_PTR) {
        PPP_MNTN_LOG2(LOG_LEVEL_WARNING, "alloc msg fail!", pppId, operType);
        return VOS_ERR;
    }

    ctrlOper->msgHdr.ulReceiverPid = PS_PID_APP_PPP;
    ctrlOper->msgHdr.msgId = ID_PPPA_AT_CTRL_OPERATION_MSG;
    ctrlOper->msgHdr.pppId = pppId;
    ctrlOper->operType = operType;

    return PS_SEND_MSG(PS_PID_APP_PPP, ctrlOper);

}

VOS_VOID PPPA_AtCtrlOperMsgProc(PPP_InternalMsgHeader *msg)
{
    const PPP_AT_CtrlOperCmd *ctrlOper = (const PPP_AT_CtrlOperCmd *)msg;
    PPP_AtCtrlOperTypeUint32 operType = ctrlOper->operType;
    PPP_ID pppId = ctrlOper->msgHdr.pppId;

    switch (operType) {
        case PPP_AT_CTRL_REL_PPP_REQ:
            Ppp_ReleasePppReq(pppId);
            break;
        case PPP_AT_CTRL_REL_PPP_RAW_REQ:
            Ppp_ReleaseRawDataPppReq(pppId);
            break;
        case PPP_AT_CTRL_HDLC_DISABLE:
            PPP_MNTN_LOG(LOG_LEVEL_WARNING, "Disable Hdlc");
            break;
        default:
            PPP_MNTN_LOG1(LOG_LEVEL_WARNING, "operType is ERROR!", operType);
            break;
    }
}


