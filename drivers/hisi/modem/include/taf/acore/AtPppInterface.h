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

#ifndef __ATPPPINTERFACE_H__
#define __ATPPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PppInterface.h"
#include "TafTypeDef.h"
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "ImmInterface.h"
#endif

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/
/* ��ΪAPS���棬����ģʽ�£�APS��֪ͨPPP������Э�̣��м�ģʽ�²�֪ͨPPPC */



/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef PPPA_AUTH_PAP_CONTENT_STRU AT_PPP_AUTH_PAP_CONTENT_STRU;

typedef PPPA_AUTH_CHAP_CONTENT_STRU AT_PPP_AUTH_CHAP_CONTENT_STRU;

typedef PPPA_REQ_AUTH_CONFIG_INFO_STRU AT_PPP_REQ_AUTH_CONFIG_INFO_STRU;

typedef PPPA_REQ_IPCP_CONFIG_INFO_STRU AT_PPP_REQ_IPCP_CONFIG_INFO_STRU;

typedef PPPA_PDP_ACTIVE_CONFIG_STRU AT_PPP_REQ_CONFIG_INFO_STRU;

/*PCO��Я����IPCP��Ϣ*/
typedef PPPA_PCO_IPV4_ITEM_STRU AT_PPP_PCO_IPV4_ITEM_STRU;

typedef PPPA_PDP_ACTIVE_RESULT_STRU AT_PPP_IND_CONFIG_INFO_STRU;

/* ��ΪAPS���棬����ģʽ�£�APS��֪ͨPPP������Э�̣��м�ģʽ�²�֪ͨPPPC */

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* �������ӿ�ʹ�õ��µĽṹ�壬��˲�����PppInterface.h */
extern VOS_UINT32 At_RcvTeConfigInfoReq (VOS_UINT16 usPppId,AT_PPP_REQ_CONFIG_INFO_STRU *pstPppReqConfigInfo);
extern TAF_UINT32 At_RcvPppReleaseInd ( TAF_UINT16 usPppId);
extern TAF_UINT32 At_PsRab2PppId (TAF_UINT8 ucExRabId, TAF_UINT16 *pusPppId);
extern TAF_UINT32 At_PppId2PsRab (TAF_UINT16 usPppId, TAF_UINT8 *pucExRabId);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 AT_SendZcDataToModem(
    VOS_UINT16                          usPppId,
    IMM_ZC_STRU                        *pstDataBuf
);
#endif

extern VOS_UINT32 Ppp_RegDlDataCallback(PPP_ID usPppId);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


