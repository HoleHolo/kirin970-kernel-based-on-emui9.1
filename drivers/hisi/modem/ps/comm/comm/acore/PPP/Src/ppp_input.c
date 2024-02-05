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


#include "ppp_input.h"
#include "ppp_public.h"
#include "hdlc_interface.h"
#include "product_config.h"
#include "TTFComm.h"
#include "TTFUtil.h"
#include "ppps_pppa_interface.h"

#include "hdlc_software.h"
#include "ppp_convert.h"

#include "AdsDeviceInterface.h"



/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_PPP_INPUT_C

#define PPPA_DATA_QUEUE_MAX_CNT     1500

typedef struct
{
    PPP_ZC_QUEUE_STRU           stDataQ;                    /* PPP���ݶ��У����������ݶ������� */
    VOS_UINT32                  dataQMaxCnt;                /* PPP���ݶ��������� */
    PPP_DATA_Q_STAT_ST          stStat;                     /* PPP���ݶ��е�ͳ����Ϣ */
    HTIMER                      delayProtTimer;             /* ��ʱ����ʱ��ȥ */
    volatile VOS_UINT32         ulNotifyMsg;                /* ֪ͨPPP�������� */
    VOS_SPINLOCK                spinLock;                   /* ulNotifyMsg�ڶ�������лᱻ�޸ģ������Ҫʹ�������� */
    VOS_UINT32                  pppTaskId;                  /* PPP����ID��֪ͨPPP������������ʱʹ�� */
    VOS_UINT32                  rawDataByPass;              /* RAWDATA����ʱ�����Ƿ���͸��ģʽ */
}PPP_DATA_Q_CTRL_ST;


/*PPP�����ݶ��нṹ��,���������ݶ���ͬһ��������*/
PPP_DATA_Q_CTRL_ST     g_PppDataQCtrl;

#define PPPA_GET_DATAQ_CTRL()   &g_PppDataQCtrl
#define PPPA_GET_STAT_ADDR()    &(g_PppDataQCtrl.stStat)
#define PPPA_DATA_DELAY_PROC_TIMER_LEN  10

VOS_BOOL    g_pppUsed           = VOS_FALSE;
VOS_UINT32  g_pppDelayTimerLen  = PPPA_DATA_DELAY_PROC_TIMER_LEN;

VOS_VOID PPP_ClearDataQ(VOS_VOID)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();
    PPP_ZC_STRU        *pstMem = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(&(dataQCtrl->stDataQ));

    while (pstMem != VOS_NULL_PTR) {
        PPP_MemFree(pstMem);
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(&(dataQCtrl->stDataQ));
    }
}

VOS_UINT32 PPP_DataQInit(VOS_VOID)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();
    VOS_UINT32          rslt = VOS_OK;

    PSACORE_MEM_SET(dataQCtrl, sizeof(PPP_DATA_Q_CTRL_ST), 0, sizeof(PPP_DATA_Q_CTRL_ST));

    PPP_ZC_QUEUE_INIT(&(dataQCtrl->stDataQ));
    dataQCtrl->rawDataByPass = VOS_FALSE;
    dataQCtrl->ulNotifyMsg = VOS_TRUE;
    dataQCtrl->dataQMaxCnt = PPPA_DATA_QUEUE_MAX_CNT;

    PPPA_SetDataStatAddr(&(dataQCtrl->stStat));
    
    VOS_SpinLockInit(&(dataQCtrl->spinLock));

    return rslt;
}

VOS_VOID PPPA_SaveTaskId(VOS_UINT32 taskId)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();

    dataQCtrl->pppTaskId = taskId;
}


VOS_UINT32 PPP_GetRawDataByPassMode(VOS_VOID)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();
    
    return dataQCtrl->rawDataByPass;
}

VOS_VOID PPP_SetRawDataByPassMode(VOS_UINT32 ulRawDataByPassMode)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();
    
    dataQCtrl->rawDataByPass = ulRawDataByPassMode;
}

VOS_UINT32 PPP_INPUT_GetDataCnt(VOS_VOID)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl = PPPA_GET_DATAQ_CTRL();

    return PPP_ZC_GET_QUEUE_LEN(&(dataQCtrl->stDataQ));
}


VOS_VOID PPP_NotiFyProcData(PPP_DATA_Q_CTRL_ST *dataQCtrl)
{
    VOS_ULONG           ulFlags     = 0UL;
    
    VOS_SpinLockIntLock(&(dataQCtrl->spinLock), ulFlags);

    if (dataQCtrl->ulNotifyMsg != VOS_TRUE) {
        VOS_SpinUnlockIntUnlock(&(dataQCtrl->spinLock) , ulFlags);
        return;
    }
    dataQCtrl->ulNotifyMsg = VOS_FALSE;
    VOS_SpinUnlockIntUnlock(&(dataQCtrl->spinLock) , ulFlags);
    dataQCtrl->stStat.ulSndMsgCnt++;
    (VOS_VOID)VOS_EventWrite(dataQCtrl->pppTaskId, PPP_RCV_DATA_EVENT);
}


VOS_UINT32 PPP_EnqueueData(PPP_ZC_STRU *pstImmZc, PPP_DataTypeUint8 enDataType, PPP_ID usPppId)
{
    PPP_DATA_Q_CTRL_ST *dataQCtrl   = PPPA_GET_DATAQ_CTRL();
    PPP_ZC_QUEUE_STRU  *pstDataQ    = &(dataQCtrl->stDataQ);

    if (PPP_ZC_GET_QUEUE_LEN(pstDataQ) > dataQCtrl->dataQMaxCnt)
    {
        PPP_MemFree(pstImmZc);
        dataQCtrl->stStat.ulDropCnt++;
        PPP_NotiFyProcData(dataQCtrl);
        return PS_FAIL;
    }

    /*�����ݽ��������β��*/
    PPP_ZC_ENQUEUE_TAIL(pstDataQ, pstImmZc);

    if (PPP_ZC_GET_QUEUE_LEN(pstDataQ) > dataQCtrl->stStat.ulQMaxCnt)
    {
        dataQCtrl->stStat.ulQMaxCnt = PPP_ZC_GET_QUEUE_LEN(pstDataQ);
    }

    PPP_NotiFyProcData(dataQCtrl);

    return PS_SUCC;
} /* PPP_EnqueueData */

VOS_UINT32 PPP_PullPacketEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc)
{
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();
    if (pstImmZc == VOS_NULL_PTR)
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                      "PPP_PullPacketEvent, WARNING, pstImmZc is NULL!\r\n" );

        return PS_FAIL;
    }

    dataStat->ulUplinkCnt++;

    /*���pstData��usApp�ֶ�:��8λ��usPppId,��8λ��PPP��������*/
    PPP_ZC_SET_DATA_APP(pstImmZc, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PULL_PACKET_TYPE);

    if ( PS_SUCC != PPP_EnqueueData(pstImmZc, PPP_PULL_PACKET_TYPE, (PPP_ID)usPppId)) {
        dataStat->ulUplinkDropCnt++;
    }

    return PS_SUCC;
} /* PPP_PullPacketEvent */

VOS_UINT32 PPP_PullRawDataEvent(VOS_UINT16 usPppId, IMM_ZC_STRU *pstImmZc)
{
    PPP_ZC_STRU        *pstMem = VOS_NULL_PTR;
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    dataStat->ulUplinkCnt++;

    if(VOS_NULL_PTR == pstImmZc)
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                      "PPP_PullRawDataEvent, WARNING, Alloc TTF mem fail!\r\n" );

        return PS_FAIL;
    }
    
    if (PPP_GetRawDataByPassMode() == VOS_TRUE){

        pstMem = pstImmZc;
        /* PPPģʽ͸��ģʽ�µݽ���ADS����PPP���ģ����Э��������0 */
        if (PS_SUCC != PPP_SendUlDataToAds(usPppId, pstMem))
        {
            return PS_FAIL;
        }
    } else {
        /*���pstData��usApp�ֶ�:��8λ��usPppId,��8λ��PPP��������*/
        PPP_ZC_SET_DATA_APP(pstImmZc, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PULL_RAW_DATA_TYPE);

        if ( PS_SUCC != PPP_EnqueueData(pstImmZc, PPP_PULL_RAW_DATA_TYPE, (PPP_ID)usPppId) ) {
            dataStat->ulUplinkDropCnt++;
        }
    }

    return PS_SUCC;
} /* PPP_PullRawEvent */

VOS_BOOL PPPA_GetUsedFalg(VOS_VOID)
{
    return g_pppUsed;
}
VOS_INT PPP_DlPacketProc(PPP_ID usPppId, IMM_ZC_STRU *pstImmZc)
{
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    if(pstImmZc == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "PPP_PushPacketEvent, WARNING, pstImmZc is NULL!\r\n" );
        return PS_FAIL;
    }

    /*��������ӻ�û��������*/
    if (PPPA_GetUsedFalg() != VOS_TRUE) {
        /*�ñ�����Ҫ����ʼ��Ϊ0*/
        dataStat->ulDownlinkDropCnt++;
        PPP_MNTN_LOG1(PS_PRINT_NORMAL, "ppp id err", dataStat->ulDownlinkDropCnt);
        PPP_MemFree(pstImmZc);
        return PS_FAIL;
    }

    /*���pstData��usApp�ֶ�:��8λ��usPppId,��8λ��PPP��������*/
    PPP_ZC_SET_DATA_APP(pstImmZc, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);

    if ( PS_SUCC != PPP_EnqueueData(pstImmZc, PPP_PUSH_PACKET_TYPE, usPppId) ) {
        dataStat->ulDownlinkDropCnt++;
    }

    return PS_SUCC;
}

VOS_VOID PPPA_SendDlDataToAT(PPP_ID pppId, IMM_ZC_STRU *data)
{
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    AT_SendZcDataToModem(pppId, data);
    dataStat->ulDownlinkSndDataCnt++;
}

VOS_INT PPP_DlRawDataProc(PPP_ID usPppId, IMM_ZC_STRU *pstImmZc)
{
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();
    
    if(pstImmZc == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                      "PPP_PushRawDataEvent, WARNING, pstImmZc is NULL!\r\n" );

        return PS_FAIL;
    }

    if(PPPA_GetUsedFalg() != VOS_TRUE) {
        dataStat->ulDownlinkDropCnt++;
        PPP_MemFree(pstImmZc);
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                     "PPP_PushRawData, WARNING, Invalid PPP id, packet from GGSN droped\r\n");

        return PS_FAIL;
    }

    if (PPP_GetRawDataByPassMode() == VOS_TRUE) {
        PPPA_SendDlDataToAT(usPppId, pstImmZc);
    } else {
        /*���pstData��usApp�ֶ�:��8λ��usPppId,��8λ��PPP��������*/
        PPP_ZC_SET_DATA_APP(pstImmZc, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PUSH_RAW_DATA_TYPE);

        if (PS_SUCC != PPP_EnqueueData(pstImmZc, PPP_PUSH_RAW_DATA_TYPE, usPppId)) {
            dataStat->ulDownlinkDropCnt++;
            return PS_FAIL;
        }
    }

    return PS_SUCC;
}


VOS_UINT32 PPP_PushPacketEvent(VOS_UINT8 ucRabId, PPP_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam)
{
    PPP_ID              usPppId;
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    dataStat->ulDownlinkCnt++;

    if ( !PPP_RAB_TO_PPPID(&usPppId, ucRabId) )
    {
        dataStat->ulDownlinkDropCnt++;
        PPP_MemFree(pstImmZc);
        PPP_MNTN_LOG1(PS_PRINT_NORMAL,
                      "PPP, PPP_PushPacketEvent, NORMAL, Can not get PPP Id, RabId <1>", ucRabId);

        return PS_FAIL;
    }

    return PPP_DlPacketProc(usPppId, pstImmZc);
}


VOS_UINT32 PPP_PushRawDataEvent(VOS_UINT8 ucRabId, PPP_ZC_STRU *pstImmZc, ADS_PKT_TYPE_ENUM_UINT8 enPktType, VOS_UINT32 ulExParam)
{
    PPP_ID              usPppId;
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    dataStat->ulDownlinkCnt++;

    /* ͨ��RabId��Ѱ�ҵ�PPP ID����Ӧ��ʵ�� */
    if ( !PPP_RAB_TO_PPPID(&usPppId, ucRabId) )
    {
        PPP_MemFree(pstImmZc);
        PPP_MNTN_LOG1(PS_PRINT_WARNING,
                      "PPP, PPP_PushRawDataEvent, WARNING, Can not get PPP Id, RabId <1>", ucRabId);

        return PS_FAIL;
    }

    return PPP_DlRawDataProc(usPppId, pstImmZc);
}
VOS_UINT32 PPP_SendUlDataToAds(VOS_UINT16 usPppId,  PPP_ZC_STRU *pstImmZc)
{
    VOS_UINT8               ucRabId  = 0;
    PPP_DATA_Q_STAT_ST     *dataStat = PPPA_GET_STAT_ADDR();

    /* ͨ��usPppId��Ѱ�ҵ�usRabId */
    if ( !PPP_PPPID_TO_RAB(usPppId, &ucRabId) )
    {
        dataStat->ulUplinkDropCnt++;
        PPP_MemFree(pstImmZc);
        PPP_MNTN_LOG2(PS_PRINT_NORMAL,
                    "PPP, PPP_PushPacketEvent, WARNING, Can not get PPP Id %d, RabId %d",
                    usPppId, ucRabId);

        return PS_FAIL;
    }

    /* ���ݷ��͸�ADS�����ʧ����Ҫ�ͷ��ڴ� */
    if ( VOS_OK != ADS_UL_SendPacket(pstImmZc, ucRabId) )
    {
        dataStat->ulUplinkDropCnt++;
        PPP_MemFree(pstImmZc);
        return PS_FAIL;
    }

    dataStat->ulUplinkSndDataCnt++;

    return PS_SUCC;
}

VOS_VOID PPPA_SetNotifyFlag(VOS_UINT32 notifyFlag)
{
    VOS_ULONG           ulFlags     = 0UL;
    PPP_DATA_Q_CTRL_ST *dataQCtrl   = PPPA_GET_DATAQ_CTRL();
    
    VOS_SpinLockIntLock(&(dataQCtrl->spinLock), ulFlags);    /*lint !e571*/
    dataQCtrl->ulNotifyMsg = notifyFlag;
    VOS_SpinUnlockIntUnlock(&(dataQCtrl->spinLock), ulFlags);
}

VOS_VOID PPP_ProcDataNotify(VOS_VOID)
{
    PPP_ID                  usPppId;
    VOS_BOOL                delayProc = VOS_FALSE;
    PPP_DATA_Q_STAT_ST     *dataStat    = PPPA_GET_STAT_ADDR();
    PPP_DATA_Q_CTRL_ST     *dataQCtrl   = PPPA_GET_DATAQ_CTRL();
    
    PPP_ZC_STRU *pstMem = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(&dataQCtrl->stDataQ);

    dataStat->ulProcMsgCnt++;

    /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstMem )
    {
        PPP_MNTN_LOG2(LOG_LEVEL_WARNING,
                      "PPP_ProcDataNotify, WARNING, queue is null!",
                      dataQCtrl->ulNotifyMsg, PPP_ZC_GET_QUEUE_LEN(&(dataQCtrl->stDataQ)));
        PPPA_SetNotifyFlag(VOS_TRUE);
        return;
    }

    /* ����ý��(�����ͷŶ����Ѿ��ڸ��������ڲ���ɣ��������ͷŽ��) */
    usPppId         = (PPP_ZC_GET_DATA_APP(pstMem) & 0xFF00) >> 8;

    delayProc = PPP_HDLC_SOFT_ProcData(usPppId, &g_PppDataQCtrl.stDataQ);

    /* �����Ҫ��ʱ������������ʱ������ʱ��������֪ͨ��� */
    if (delayProc == VOS_TRUE) {
        VOS_StartRelTimer(&(dataQCtrl->delayProtTimer), PS_PID_APP_PPP, g_pppDelayTimerLen,
                     PPPA_DATA_DELAY_PROC_TIMER, (VOS_UINT32)usPppId, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0);
        return;
    }
    
    PPPA_SetNotifyFlag(VOS_TRUE);
    if (PPP_ZC_GET_QUEUE_LEN(&(dataQCtrl->stDataQ)) > 0) {
        PPP_NotiFyProcData(dataQCtrl);
    }
}
/* ĿǰЭ�̱�����ͨ��VOS��Ϣ���ͣ�ÿ����෢��100��Э�̱��� */
#define PPPA_MAX_NEGO_PKT_CNT_PER_SEC   100

/* ĿǰΪ32Kʱ�ӣ�1sΪ32768��slice */
#define PPPA_SLICE_CNT_OF_ONE_SEC       32768

VOS_VOID PPPA_SendPppsNegoData(PPP_ZC_STRU *negoData, VOS_UINT16 proto)
{
    PPPS_PPPA_NegoData *negoMsg = VOS_NULL_PTR;
    VOS_UINT16 msgLen = sizeof(PPPS_PPPA_NegoData) + PPP_ZC_GET_DATA_LEN(negoData);
    static VOS_UINT16 msgSendCnt = 0;
    static VOS_UINT32 beginTime = 0;
    VOS_UINT32 currTime;

    if (msgSendCnt == 0) {
        /* ���͵�һ������ʱ��¼��ʼʱ�� */
        beginTime = mdrv_timer_get_normal_timestamp();
    } else {
        currTime = mdrv_timer_get_normal_timestamp();
        if (currTime - beginTime > PPPA_SLICE_CNT_OF_ONE_SEC) {
            /* ��ǰʱ�����ʼʱ��������1s�����¿�ʼ���� */
            msgSendCnt = 0;
            beginTime = currTime;
        } else {
            /* 1s�ڷ��͵�Э�̱�����������100�����ܼ�������Э�̱��� */
            if (msgSendCnt > PPPA_MAX_NEGO_PKT_CNT_PER_SEC) {
                PPP_MNTN_LOG(PS_PRINT_WARNING, "too many nego pkt");
                return;
            }
        }
    }
    msgSendCnt++;
    negoMsg = (PPPS_PPPA_NegoData*)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_APP_PPP, msgLen);
    if (negoMsg == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "alloc Msg Fail");
        return;
    }

    negoMsg->ulReceiverPid  = MSPS_PID_PPPS;
    negoMsg->msgId          = ID_PPPA_PPPS_NEGO_DATA_IND;
    negoMsg->proto          = proto;
    negoMsg->dataLen        = PPP_ZC_GET_DATA_LEN(negoData);
    negoMsg->pktType        = PPPS_PPPA_PKT_TYPE_BUTT;

    if (negoMsg->dataLen > 0) {
        PSACORE_MEM_CPY(negoMsg->data, negoMsg->dataLen, PPP_ZC_GET_DATA_PTR(negoData), negoMsg->dataLen);
    }

    (VOS_VOID)PS_SEND_MSG(PS_PID_APP_PPP, negoMsg);
}


VOS_VOID PPP_FrameMntnInfo
(
    PPP_FrameMntn            *ptrPppMntnSt,
    VOS_UINT16                usDataLen
)
{
    ptrPppMntnSt->ulReceiverPid   = MSPS_PID_PPPS;
    ptrPppMntnSt->ulSenderPid     = PS_PID_APP_PPP;
    ptrPppMntnSt->ulLength        = (usDataLen + sizeof(PPP_FrameMntn))- VOS_MSG_HEAD_LENGTH;
    ptrPppMntnSt->msgName       = PPP_RECV_PROTO_PACKET_TYPE;
    ptrPppMntnSt->pppPhase      = 0;
    ptrPppMntnSt->ipcpState     = 0;
    ptrPppMntnSt->lcpState      = 0;
    ptrPppMntnSt->pppId         = PPPA_PPP_ID;
    ptrPppMntnSt->dataLen       = usDataLen;

    PPP_MNTN_TRACE_MSG(ptrPppMntnSt);
}

VOS_VOID PPP_TtfMemFrameMntnInfo
(
    PPP_ZC_STRU *pstMem,
    VOS_UINT16   usProto
)
{
    VOS_UINT16                usFrameLen        = 0;
    PPP_FrameMntn            *ptrPppFrameMntnSt = VOS_NULL_PTR;
    VOS_UINT8                *pucBuff           = VOS_NULL_PTR;
    VOS_UINT32                ulRet             = PS_FAIL;

    /* PPP ֡����*/
    usFrameLen = (VOS_UINT16)PPP_ZC_GET_DATA_LEN(pstMem);

    /*lint -e516 -esym(516,*)*/
    ptrPppFrameMntnSt = (PPP_FrameMntn *)PS_MEM_ALLOC(PS_PID_APP_PPP,
                        usFrameLen + sizeof(PPP_FrameMntn) + sizeof(usProto));    
    if (VOS_NULL_PTR == ptrPppFrameMntnSt)
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,"PPP, PPP_TtfMemFrameMntnInfo, ERROR, Call VOS_MemAlloc fail!\n");
        return;
    }

    /* ����PPP֡Э������,�����ֽ���*/
    pucBuff = (VOS_UINT8 *)(ptrPppFrameMntnSt + 1);
    *((VOS_UINT16 *)(pucBuff)) = (VOS_HTONS(usProto)); 
    (pucBuff) += sizeof(VOS_UINT16);         

    /* ����֡����,ԭʼ���Ƽ���*/
    ulRet = PPP_MemGet(pstMem, 0, pucBuff, usFrameLen);
    if (PS_SUCC != ulRet)
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,"PPP, Ppp_frame_MntnInfo, ERROR, TTF_MemGet Fail!\n");
        PS_MEM_FREE(PS_PID_APP_PPP, ptrPppFrameMntnSt);
        return ;
    }

    /****************************************************************
       ���Ϳ�ά�ɲ���Ϣ
       ����: ����ά�ɲ���Ϣͷ�������ݲ����غ�
             ����֡�� + 2byte protocol�ֶ�
    *****************************************************************/
    PPP_FrameMntnInfo(ptrPppFrameMntnSt, usFrameLen + sizeof(usProto));

    /* �ͷ��ڴ�*/
    PS_MEM_FREE(PS_PID_APP_PPP, ptrPppFrameMntnSt);    
    /*lint -e516 +esym(516,*)*/
}

VOS_VOID PPP_HDLC_ProcIpModeUlData(VOS_UINT16  pppId, PPP_ZC_STRU *pstMem, VOS_UINT16  usProto)
{
    if (usProto != PPPA_IP)
    {
        /* ��PPPЭ�̰���Ϊ��ά�ɲ���Ϣ,IP��������ά�ɲ�ά��*/
        PPP_TtfMemFrameMntnInfo(pstMem, usProto);
        PPPA_SendPppsNegoData(pstMem, usProto); 
        PPP_MemFree(pstMem);
    } else {
        PPP_SendUlDataToAds(pppId, pstMem);
    } 
}

VOS_VOID PPP_SetupHdlc(VOS_UINT16 pppId, VOS_BOOL ipMode)
{
    PPP_HDLC_SetUp(pppId, ipMode);
}

VOS_VOID PPP_ReleaseHdlc(VOS_UINT16 pppId)
{
    PPP_HDLC_Release(pppId);

}

VOS_VOID PPPA_SetUsedFlag(VOS_BOOL isUsed)
{
    g_pppUsed = isUsed;
}

VOS_VOID PPPA_DataEventProc(VOS_VOID)
{

    PPP_ProcDataNotify();

}

VOS_VOID PPPA_INPUT_ProcEchoReq(VOS_VOID)
{
    static VOS_UINT32   preDropCnt = 0;
    PPP_DATA_Q_STAT_ST *dataStat = PPPA_GET_STAT_ADDR();

    if (dataStat->ulDropCnt == preDropCnt) {
        return;
    }
    preDropCnt = dataStat->ulDropCnt;
    PPPA_SendPppsCommMsg(ID_PPPA_PPPS_IGNORE_ECHO);
}




