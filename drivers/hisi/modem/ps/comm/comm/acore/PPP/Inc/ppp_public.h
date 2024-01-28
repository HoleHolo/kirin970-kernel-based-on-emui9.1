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


#ifndef __PPP_PUBLIC_H__
#define __PPP_PUBLIC_H__

#include "vos.h"
#include "AtPppInterface.h"
#include "product_config.h"
#include "TTFUtil.h"
#include "v_IO.h"
#include "TTFComm.h"
#include "ImmInterface.h"
#include "acore_nv_id_gucttf.h"
#include "acore_nv_stru_gucttf.h"
#include "NVIM_Interface.h"
#include "ppps_pppa_interface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#ifndef __STATIC_
#if defined(DMT) || defined(__UT_CENTER__)
#define __STATIC_
#else
#define __STATIC_ static
#endif
#endif

#define PPPA_PPP_ID             1

#define PPPA_IP                 0x0021
/* ��̫��IPV4Э������Ϊ0x0800, ������Ϊ0x0008 */
#define PPPA_ETH_IPV4_PROTO     0x0008

#ifndef VOS_NTOHL
#if    VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define    VOS_NTOHL(x)    (x)
#define    VOS_HTONL(x)    (x)
#define    VOS_NTOHS(x)    (x)
#define    VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ff) << 24) | \
             (((x) & 0x0000ff00) <<  8) | \
             (((x) & 0x00ff0000) >>  8) | \
             (((x) & 0xff000000) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#endif    /* _BYTE_ORDER==_LITTLE_ENDIAN */

#endif

#ifndef INADDR_ANY
#define    INADDR_ANY            (VOS_UINT32)0x00000000L
#endif

#ifndef INADDR_BROADCAST
#define    INADDR_BROADCAST    (VOS_UINT32)0xffffffffL    /* must be masked */
#endif

#ifndef INADDR_NONE
#define    INADDR_NONE            0xffffffffUL        /* -1 return */
#endif


#define NEG_ACCEPTED        (1)
#define NEG_ENABLED         (2)
#define IsAccepted(x)       ((x) & NEG_ACCEPTED)
#define IsEnabled(x)        ((x) & NEG_ENABLED)

#define SCRIPT_LEN          (512)        /* Size of login/dial/hangup scripts */

#if    VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define ua_htonl(src, tgt) PSACORE_MEM_CPY(tgt,sizeof(VOS_UINT32),src,sizeof(VOS_UINT32))
#define ua_ntohl(src, tgt) PSACORE_MEM_CPY(tgt,sizeof(VOS_UINT32),src,sizeof(VOS_UINT32))
#define ua_htons(src, tgt) PSACORE_MEM_CPY(tgt,sizeof(VOS_UINT16),src,sizeof(VOS_UINT16))
#define ua_ntohs(src, tgt) PSACORE_MEM_CPY(tgt,sizeof(VOS_UINT16),src,sizeof(VOS_UINT16))
#else
#define ua_htonl(src, tgt) \
        *((VOS_CHAR*)(tgt)) = *(((VOS_CHAR*)(src))+3); \
        *(((VOS_CHAR*)(tgt))+1) = *(((VOS_CHAR*)(src))+2); \
        *(((VOS_CHAR*)(tgt))+2) = *(((VOS_CHAR*)(src))+1); \
        *(((VOS_CHAR*)(tgt))+3) = *((VOS_CHAR*)(src));

#define ua_ntohl(src, tgt) \
        *((VOS_CHAR*)tgt) = *(((VOS_CHAR*)src)+3); \
        *(((VOS_CHAR*)tgt)+1) = *(((VOS_CHAR*)src)+2); \
        *(((VOS_CHAR*)tgt)+2) = *(((VOS_CHAR*)src)+1); \
        *(((VOS_CHAR*)tgt)+3) = *((VOS_CHAR*)src);

#define ua_htons(src, tgt) \
        *((VOS_CHAR*)tgt) = *(((VOS_CHAR*)src)+1); \
        *(((VOS_CHAR*)tgt)+1) = *((VOS_CHAR*)src);

#define ua_ntohs(src, tgt) \
        *((VOS_CHAR*)tgt) = *(((VOS_CHAR*)src)+1); \
        *(((VOS_CHAR*)tgt)+1) = *((VOS_CHAR*)src);

#endif
/*ϵͳ�����Ҫ��PPP ID����Ŀ��ʵ����Ҫ�Ŀռ���
��ֵ��һ����Ϊͷ�ǲ��������*/
/*#define PPP_MAX_ID_NUM 1*/
#define PPP_MAX_ID_NUM_ALLOC (PPP_MAX_ID_NUM+1)

/*���յ��ı�����ϵͳ����ռ䣬��ҪԤ�������ͷ����*/
#define PPP_RECIEVE_RESERVE_FOR_HEAD 4

/*���յ��ı�����ϵͳ����ռ䣬��ҪԤ�������β����*/
#define PPP_RECIEVE_RESERVE_FOR_TAIL 2

#define PPPoE_RESERVE_HEADER_LEN    20     /*Ԥ�����ֽ�������PPPoE��д��̫֡ͷ����PPPoEͷ��*/

#define PPP_FEATURE_PPP         0          /*ʹ��PPP*/

#define PPP_FEATURE             PPP_FEATURE_PPP   /*��ǰѡ��PPP*/

#define PPP_MAX_DATA_CNT_IN_QUEUE (2000)

#define PPP_RAB_TO_PPPID(pusPppId, ucRabId) \
    ( TAF_SUCCESS == At_PsRab2PppId((ucRabId), pusPppId) )

#define PPP_PPPID_TO_RAB(usPppId, pucRabId) \
    ( TAF_SUCCESS == At_PppId2PsRab((usPppId), pucRabId) )

#define PPP_MNTN_LOG(Level, String) \
            ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, Level), (PS_PID_APP_PPP), __FILE__, __LINE__, "\r\n"))
#define PPP_MNTN_LOG1(Level, String, Para1) \
            ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, Level), (PS_PID_APP_PPP), __FILE__, __LINE__, "%d \r\n", Para1))
#define PPP_MNTN_LOG2(Level, String, Para1, Para2) \
            ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, Level), (PS_PID_APP_PPP), __FILE__, __LINE__, "%d, %d \r\n", Para1, Para2))
#define PPP_MNTN_LOG3(Level, String, Para1, Para2, Para3) \
            ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, Level), (PS_PID_APP_PPP), __FILE__, __LINE__, "%d, %d, %d \r\n", Para1, Para2, Para3))
#define PPP_MNTN_LOG4(Level, String, Para1, Para2, Para3, Para4) \
            ((VOS_VOID)DIAG_LogReport(DIAG_GEN_LOG_MODULE(MODEM_ID_0, DIAG_MODE_COMM, Level), (PS_PID_APP_PPP), __FILE__, __LINE__, "%d, %d, %d, %d \r\n", Para1, Para2, Para3, Para4))

/* --------------�㿽��������غ�-------------- */
typedef IMM_ZC_STRU      PPP_ZC_STRU;
typedef IMM_ZC_HEAD_STRU PPP_ZC_QUEUE_STRU;

#define PPP_ZC_MAX_DATA_LEN                  (IMM_MAX_ETH_FRAME_LEN)            /* A���ڿ������ڴ����󳤶� */
#define PPP_ZC_UL_RESERVE_LEN                (IMM_MAC_HEADER_RES_LEN)           /* MACͷ���ȣ����з�����Ҫ���� */
#define PPP_ZC_DL_RESERVE_LEN                (0)                                /* ���з�����Ҫ���� */

#define PPP_ZC_MEM_ALLOC(ulLen)              (IMM_ZcStaticAlloc(ulLen))
#define PPP_ZC_MEM_FREE(pstMem)              (IMM_ZcFreeAny(pstMem))
#define PPP_ZC_GET_DATA_PTR(pstImmZc)        ((VOS_UINT8 *)IMM_ZcGetDataPtr(pstImmZc))
#define PPP_ZC_GET_DATA_LEN(pstImmZc)        ((VOS_UINT16)IMM_ZcGetUsedLen(pstImmZc))
#define PPP_ZC_GET_DATA_APP(pstImmZc)        ((VOS_UINT16)IMM_ZcGetUserApp(pstImmZc))
#define PPP_ZC_SET_DATA_APP(pstImmZc, ucApp) (IMM_ZcSetUserApp(pstImmZc, ucApp))
#define PPP_ZC_SET_DATA_LEN(pstImmZc, ulLen) (IMM_ZcPut(pstImmZc, ulLen))
#define PPP_ZC_REMOVE_HDR(pstImmZc, ulLen)   (IMM_ZcPull(pstImmZc, ulLen))
#define PPP_ZC_RESERVE(pstMem, usReserveLen) (IMM_ZcReserve(pstMem, usReserveLen))
#define PPP_ZC_GET_RESERVE_ROOM(pstMem)      (pstMem->end - pstMem->tail)

#define PPP_ZC_QUEUE_INIT(pstZcQueue)           (IMM_ZcQueueHeadInit(pstZcQueue))
#define PPP_ZC_ENQUEUE_HEAD(pstZcQueue, pstMem) (IMM_ZcQueueHead(pstZcQueue, pstMem))
#define PPP_ZC_ENQUEUE_TAIL(pstZcQueue, pstMem) (IMM_ZcQueueTail(pstZcQueue, pstMem))
#define PPP_ZC_DEQUEUE_HEAD(pstZcQueue)         (IMM_ZcDequeueHead(pstZcQueue))
#define PPP_ZC_DEQUEUE_TAIL(pstZcQueue)         (IMM_ZcDequeueTail(pstZcQueue))
#define PPP_ZC_PEEK_QUEUE_HEAD(pstZcQueue)      (IMM_ZcQueuePeek(pstZcQueue))
#define PPP_ZC_PEEK_QUEUE_TAIL(pstZcQueue)      (IMM_ZcQueuePeekTail(pstZcQueue))
#define PPP_ZC_GET_QUEUE_LEN(pstZcQueue)        (IMM_ZcQueueLen(pstZcQueue))

/* A�˿�ά�ɲ�ӿ� */
#define PPP_MNTN_TRACE_MSG(pMsg)                DIAG_TraceReport(pMsg)

VOS_VOID PppaSfChk(VOS_BOOL result, VOS_UINT32 ulFileNo, VOS_UINT32 ulLineNo);
#define PPPA_SF_CHK(result)  PppaSfChk(((result) != EOK) ? VOS_TRUE : VOS_FALSE, (THIS_FILE_ID), (__LINE__))
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

/*IP��ַ*/
struct ppp_in_addr
{
    VOS_UINT32 s_addr;
};

typedef struct
{
    VOS_UINT32                  ulUplinkCnt;                /* �������ݰ��ܸ��� */
    VOS_UINT32                  ulUplinkDropCnt;            /* ���ж����� */
    VOS_UINT32                  ulUplinkSndDataCnt;         /* ���з����� */

    VOS_UINT32                  ulDownlinkCnt;              /* �������ݰ��ܸ��� */
    VOS_UINT32                  ulDownlinkDropCnt;          /* ���ж����� */
    VOS_UINT32                  ulDownlinkSndDataCnt;       /* ���з����� */

    VOS_UINT32                  ulMemAllocDownlinkCnt;      /* �����ڴ�������� */
    VOS_UINT32                  ulMemAllocDownlinkFailCnt;  /* �����ڴ�����ʧ�ܴ��� */
    VOS_UINT32                  ulMemAllocUplinkCnt;        /* �����ڴ�������� */
    VOS_UINT32                  ulMemAllocUplinkFailCnt;    /* �����ڴ�����ʧ�ܴ��� */
    VOS_UINT32                  ulMemFreeCnt;               /* �����ڴ��ͷŴ��� */

    VOS_UINT32                  ulDropCnt;                  /* ������������ */

    VOS_UINT32                  ulQMaxCnt;                  /* �����г��ֹ����������� */
    VOS_UINT32                  ulSndMsgCnt;                /* DataNotify��Ϣ������ */
    VOS_UINT32                  ulProcMsgCnt;               /* DataNotify��Ϣ������ */
} PPP_DATA_Q_STAT_ST;


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/
/* ��ʱ����Ϣ */
#define PPPA_DATA_DELAY_PROC_TIMER               0x0001


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/* �������·������о���任������������С�
         C0  C1  C2  C3              C0  C1  C2  C3
    R0 | 0 | 1 | 2 | 3 |        R0 | 3 | 6 | 9 | C |
       -----------------           -----------------
    R1 | 4 | 5 | 6 | 7 |        R1 | 7 | A | D | 0 |
       -----------------   ==>     -----------------
    R2 | 8 | 9 | A | B |        R2 | B | E | 1 | 4 |
       -----------------           -----------------
    R3 | C | D | E | F |        R3 | F | 2 | 5 | 8 |
*/
#define PPP_MATRIX_TRANSFORM(aucDst, aucSrc) \
{                               \
    aucDst[0] = aucSrc[0][3];   \
    aucDst[1] = aucSrc[1][2];   \
    aucDst[2] = aucSrc[2][1];   \
    aucDst[3] = aucSrc[3][0];   \
    aucDst[4] = aucSrc[1][3];   \
    aucDst[5] = aucSrc[2][2];   \
    aucDst[6] = aucSrc[3][1];   \
    aucDst[7] = aucSrc[0][0];   \
    aucDst[8] = aucSrc[2][3];   \
    aucDst[9] = aucSrc[3][2];   \
    aucDst[10] = aucSrc[0][1];  \
    aucDst[11] = aucSrc[1][0];  \
    aucDst[12] = aucSrc[3][3];  \
    aucDst[13] = aucSrc[0][2];  \
    aucDst[14] = aucSrc[1][1];  \
    aucDst[15] = aucSrc[2][0];  \
}

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern PPP_ZC_STRU *PPP_MemAlloc(VOS_UINT16 usLen, VOS_UINT16 usReserveLen);
extern PPP_ZC_STRU *PPP_MemCopyAlloc(VOS_UINT8 *pSrc, VOS_UINT16 usLen, VOS_UINT16 usReserveLen);
extern VOS_VOID     PPP_MemFree(PPP_ZC_STRU *pstData);
extern VOS_UINT32   PPP_MemGet(PPP_ZC_STRU *pMemSrc, VOS_UINT16 usOffset, VOS_UINT8 *pDest, VOS_UINT16 usLen);
VOS_VOID PPP_MemWriteData(PPP_ZC_STRU *pstMem, VOS_UINT16 usDstLen, VOS_UINT8 *pucSrc, VOS_UINT16 usLen);
extern VOS_VOID PPPA_SetDataStatAddr(PPP_DATA_Q_STAT_ST *dataStat);
extern VOS_VOID PPPA_SendPppsCommMsg(PPPS_PPPA_MsgTypeUint16 msgId);



#pragma pack()

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif  /*end of __PPP_PUBLIC_H__*/
