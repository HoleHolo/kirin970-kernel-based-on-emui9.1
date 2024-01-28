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


#include "ppp_public.h"
#include "TTFUtil.h"



/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767  �����־�ļ���ID���� */
#define    THIS_FILE_ID                 PS_FILE_ID_PPP_PUBLIC_C
/*lint +e767   */

PPP_DATA_Q_STAT_ST *g_dataStat = VOS_NULL_PTR;


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/



/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

/******************************************************************************
   5 ����ʵ��
******************************************************************************/

PPP_ZC_STRU * PPP_MemAlloc(VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    /* �ýӿ���������ʱ��Ҫ����MACͷ���ȣ�
      ������ADS�շ���ΪIP����Ϊ��NDIS��E5�������ݽṹͳһ����Ҫ����MACͷ��
      �㿽��ָ���C�˷��ص�ʱ��ͳһƫ�ƹ̶��ֽڣ��ҵ��㿽��ͷ����
    */
    /*
       ��������ʱ����������0��������USB�շ�����Ϊ�ֽ�����ʽ��PPP֡����MACͷ
    */
    PPP_ZC_STRU *pstMem = PPP_ZC_MEM_ALLOC(usLen + usReserveLen);


    if (VOS_NULL_PTR != pstMem)
    {
        if ( usReserveLen > 0)
        {
            /* �ճ��������ȣ���PPPģ��������ݳ�����usLen���������������δ��ֵǰ���� */
            PPP_ZC_RESERVE(pstMem, usReserveLen);

            /* �������������ܴ��� */
            g_dataStat->ulMemAllocUplinkCnt++;
        }
        else
        {
            /* �������������ܴ��� */
            g_dataStat->ulMemAllocDownlinkCnt++;

        }
    }
    else
    {
        if ( usReserveLen > 0)
        {
            /* ������������ʧ�ܴ��� */
            g_dataStat->ulMemAllocUplinkFailCnt++;
        }
        else
        {
            /* ������������ʧ�ܴ��� */
            g_dataStat->ulMemAllocDownlinkFailCnt++;
        }
    }

    return pstMem;
}


VOS_VOID PPP_MemWriteData(PPP_ZC_STRU *pstMem, VOS_UINT16 usDstLen, VOS_UINT8 *pucSrc, VOS_UINT16 usLen)
{
    /* ���úý�Ҫд���㿽���ڴ��������ݳ��� */
    PPP_ZC_SET_DATA_LEN(pstMem, usLen);

    /* �������ڴ����ݲ��� */
    PSACORE_MEM_CPY(PPP_ZC_GET_DATA_PTR(pstMem), usDstLen, pucSrc, usLen);

    return;
}


PPP_ZC_STRU * PPP_MemCopyAlloc(VOS_UINT8 *pSrc, VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    PPP_ZC_STRU                        *pstMem = VOS_NULL_PTR;


    pstMem = PPP_MemAlloc(usLen, usReserveLen);

    if ( VOS_NULL_PTR != pstMem )
    {
        /* �������ڴ����ݲ��� */
        PPP_MemWriteData(pstMem, usLen, pSrc, usLen);
    }

    return pstMem;
}


VOS_UINT32 PPP_MemGet(PPP_ZC_STRU *pMemSrc, VOS_UINT16 usOffset, VOS_UINT8 *pDest, VOS_UINT16 usLen)
{
    VOS_UINT16                          usMemSrcLen;


    /* ������� */
    if ( (VOS_NULL_PTR == pMemSrc)||(VOS_NULL_PTR == pDest) )
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par pMemSrc Or pDest is Null!\r\n");

        return PS_FAIL;
    }

    if ( 0 == usLen )
    {
        PPP_MNTN_LOG(PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par usLen is 0!\r\n");

        return PS_FAIL;
    }

    /* �ж�TTF�ڴ��ĳ����Ƿ����Ҫ�� */
    usMemSrcLen = PPP_ZC_GET_DATA_LEN(pMemSrc);

    if ( usMemSrcLen < (usOffset + usLen) )
    {
        PPP_MNTN_LOG2(PS_PRINT_WARNING,
                      "PPP_MemGet, Warning, MemSrcLen %d Less Than (Offset + Len) %d!\r\n",
                      usMemSrcLen, (usOffset + usLen));

        return PS_FAIL;
    }

    PSACORE_MEM_CPY(pDest, usLen, PPP_ZC_GET_DATA_PTR(pMemSrc) + usOffset, usLen);

    return PS_SUCC;
}


VOS_VOID PPP_MemFree(PPP_ZC_STRU *pstMem)
{
    /* �ͷ��㿽���ڴ� */
    PPP_ZC_MEM_FREE(pstMem);

    g_dataStat->ulMemFreeCnt++;

    return;
}

VOS_VOID PPPA_SetDataStatAddr(PPP_DATA_Q_STAT_ST *dataStat)
{
    g_dataStat = dataStat;
}

VOS_VOID PPPA_SendPppsCommMsg(PPPS_PPPA_MsgTypeUint16 msgId)
{
    PPPS_PPPA_CommMsg           *commMsg = VOS_NULL_PTR;

    commMsg = (PPPS_PPPA_CommMsg*)PS_ALLOC_MSG_WITH_HEADER_LEN(PS_PID_APP_PPP, sizeof(PPPS_PPPA_CommMsg));
    if (commMsg == VOS_NULL_PTR) {
        PPP_MNTN_LOG(PS_PRINT_WARNING, "alloc Msg Fail");
        return;
    }
    
    commMsg->ulReceiverPid    = MSPS_PID_PPPS;
    commMsg->msgId            = msgId;

    (VOS_VOID)PS_SEND_MSG(PS_PID_APP_PPP, commMsg);
}


VOS_VOID PppaSfChk(VOS_BOOL result, VOS_UINT32 ulFileNo, VOS_UINT32 ulLineNo)
{    
    if (result) {
        PPP_MNTN_LOG2(PS_PRINT_WARNING, "PppaSfChk Fail", ulFileNo,ulLineNo);
    }
}



