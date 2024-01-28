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


#ifndef __APPNASCOMM_H__
#define __APPNASCOMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "LPSCommon.h"
#include  "AppRrcInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/
/*公共错误码*/
#define APP_ERR_COMMON_SECTION_BEGIN                        (0)
#define APP_ERR_SM_SECTION_BEGIN                            (200)
#define APP_ERR_SM_NW_SECTION_BEGIN                         (400)
#define APP_ERR_MM_SECTION_BEGIN                            (600)
#define APP_ERR_MM_NW_SECTION_BEGIN							(800)

/*公共错误码*/
#define APP_SUCCESS                                         (APP_ERR_COMMON_SECTION_BEGIN + 0)
#define APP_FAILURE                                         (APP_ERR_COMMON_SECTION_BEGIN + 1)
#define APP_ERR_NULL_PTR                                    (APP_ERR_COMMON_SECTION_BEGIN + 2)
#define APP_ERR_PARA_ERROR                                  (APP_ERR_COMMON_SECTION_BEGIN + 3)
#define APP_ERR_TIME_OUT                                    (APP_ERR_COMMON_SECTION_BEGIN + 4)
#define APP_ERR_ID_INVALID                                  (APP_ERR_COMMON_SECTION_BEGIN + 5)
#define APP_ERR_NUM_VALUE_INVALID                           (APP_ERR_COMMON_SECTION_BEGIN + 6)
#define APP_ERR_NUM_LEN_INVALID                             (APP_ERR_COMMON_SECTION_BEGIN + 7)
#define APP_ERR_CAPABILITY_ERROR                            (APP_ERR_COMMON_SECTION_BEGIN + 8)
#define APP_ERR_CLIENTID_NO_FREE                            (APP_ERR_COMMON_SECTION_BEGIN + 9)
#define APP_ERR_CALLBACK_FUNC_ERROR                         (APP_ERR_COMMON_SECTION_BEGIN + 10)
#define APP_ERR_MSG_DECODING_FAIL                           (APP_ERR_COMMON_SECTION_BEGIN + 11)
#define APP_ERR_TI_ALLOC_FAIL                               (APP_ERR_COMMON_SECTION_BEGIN + 12)
#define APP_ERR_TI_GET_FAIL                                 (APP_ERR_COMMON_SECTION_BEGIN + 13)
#define APP_ERR_CMD_TYPE_ERROR                              (APP_ERR_COMMON_SECTION_BEGIN + 14)
#define APP_ERR_MUX_LINK_EST_FAIL                           (APP_ERR_COMMON_SECTION_BEGIN + 15)
#define APP_ERR_USIM_SIM_CARD_NOTEXIST                      (APP_ERR_COMMON_SECTION_BEGIN + 16)
#define APP_ERR_CLIENTID_NOT_EXIST                          (APP_ERR_COMMON_SECTION_BEGIN + 17)
#define APP_ERR_NEED_PIN1                                   (APP_ERR_COMMON_SECTION_BEGIN + 18)
#define APP_ERR_NEED_PUK1                                   (APP_ERR_COMMON_SECTION_BEGIN + 19)
#define APP_ERR_USIM_SIM_INVALIDATION                       (APP_ERR_COMMON_SECTION_BEGIN + 20)
#define APP_ERR_UNSPECIFIED_ERROR                           (APP_ERR_COMMON_SECTION_BEGIN + 21)
#define APP_ERR_INSUFFICIENT_RESOURCES                      (APP_ERR_COMMON_SECTION_BEGIN + 22)

#define APP_ERR_CONN_OR_NO_IMSI                             (APP_ERR_COMMON_SECTION_BEGIN + 23)
#define APP_ERR_NOT_SUPPORT_NOW                             (APP_ERR_COMMON_SECTION_BEGIN + 24)
#define APP_ERR_NOT_STARTED_YET                             (APP_ERR_COMMON_SECTION_BEGIN + 25)

/* MM与APP错误码*/
#define APP_ERR_MM_NW_BEAR_NOT_SYNC                         (APP_ERR_MM_SECTION_BEGIN + 0)
#define APP_ERR_MM_REL_IND                                  (APP_ERR_MM_SECTION_BEGIN + 1)
#define APP_ERR_MM_AUTH_TIME_OUT                            (APP_ERR_MM_SECTION_BEGIN + 2)
#define APP_ERR_MM_T3410_TIME_OUT                           (APP_ERR_MM_SECTION_BEGIN + 3)
#define APP_ERR_MM_LINK_ERR                                 (APP_ERR_MM_SECTION_BEGIN + 4)
#define APP_ERR_MM_AUTH_FAIL                                (APP_ERR_MM_SECTION_BEGIN + 5)
#define APP_ERR_MM_THROT                                    (APP_ERR_MM_SECTION_BEGIN + 6)
#define APP_ERR_MM_PLMN_SRCH_INTERRUPT                      (APP_ERR_MM_SECTION_BEGIN + 7)
#define APP_ERR_MM_SYS_INFO_INTERRUPT                       (APP_ERR_MM_SECTION_BEGIN + 8)
#define APP_ERR_MM_SUSPEND_INTERRUPT                        (APP_ERR_MM_SECTION_BEGIN + 9)
#define APP_ERR_MM_DETACH                                   (APP_ERR_MM_SECTION_BEGIN + 10)
#define APP_ERR_MM_LRRC_ERR_IND                             (APP_ERR_MM_SECTION_BEGIN + 11)
#define APP_ERR_MM_IMSI_PAGING_DETACH                       (APP_ERR_MM_SECTION_BEGIN + 12)
#define APP_ERR_MM_ATTACH_EST_FAIL                          (APP_ERR_MM_SECTION_BEGIN + 13)
#define APP_ERR_MM_STATUS_CANT_TRIGGER                      (APP_ERR_MM_SECTION_BEGIN + 14)
#define APP_ERR_MM_POWER_OFF                                (APP_ERR_MM_SECTION_BEGIN + 15)
#define APP_ERR_MM_AREA_LOST                                (APP_ERR_MM_SECTION_BEGIN + 16)
#define APP_ERR_MM_SYS_CFG_OR_UE_CAP_CHG                    (APP_ERR_MM_SECTION_BEGIN + 17)
#define APP_ERR_MM_GU_ATTACH_FAIL                           (APP_ERR_MM_SECTION_BEGIN + 18)
#define APP_ERR_MM_GU_DETACH                                (APP_ERR_MM_SECTION_BEGIN + 19)
#define APP_ERR_MM_ATTACH_MMC_REL                           (APP_ERR_MM_SECTION_BEGIN + 20)
#define APP_ERR_MM_ATTACH_CS_CALL_INTERRUPT                 (APP_ERR_MM_SECTION_BEGIN + 21)
#define APP_ERR_MM_USIM_PULL_OUT                            (APP_ERR_MM_SECTION_BEGIN + 22)

#define APP_ERR_MM_UNKNOWN                                  (APP_ERR_MM_SECTION_BEGIN + 199)

/* MM与网侧错误码*/
/*协议定义的网络拒绝原因值*/

#define APP_ERR_MM_NW_REJ_NULL                              (APP_ERR_MM_NW_SECTION_BEGIN + 0)
#define APP_ERR_MM_NW_REJ_IMSI_UNKNOWN_IN_HSS               (APP_ERR_MM_NW_SECTION_BEGIN + 2)
#define APP_ERR_MM_NW_REJ_ILLEGAL_UE                        (APP_ERR_MM_NW_SECTION_BEGIN + 3)
#define APP_ERR_MM_NW_REJ_IMEI_NOT_ACCEPTED                 (APP_ERR_MM_NW_SECTION_BEGIN + 5)
#define APP_ERR_MM_NW_REJ_ILLEGAL_ME                        (APP_ERR_MM_NW_SECTION_BEGIN + 6)
#define APP_ERR_MM_NW_REJ_EPS_SERV_NOT_ALLOW                (APP_ERR_MM_NW_SECTION_BEGIN + 7)
#define APP_ERR_MM_NW_REJ_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW  (APP_ERR_MM_NW_SECTION_BEGIN + 8)
#define APP_ERR_MM_NW_REJ_UE_ID_NOT_DERIVED                 (APP_ERR_MM_NW_SECTION_BEGIN + 9)
#define APP_ERR_MM_NW_REJ_IMPLICIT_DETACHED                 (APP_ERR_MM_NW_SECTION_BEGIN + 10)
#define APP_ERR_MM_NW_REJ_PLMN_NOT_ALLOW                    (APP_ERR_MM_NW_SECTION_BEGIN + 11)
#define APP_ERR_MM_NW_REJ_TA_NOT_ALLOW                      (APP_ERR_MM_NW_SECTION_BEGIN + 12)
#define APP_ERR_MM_NW_REJ_ROAM_NOT_ALLOW                    (APP_ERR_MM_NW_SECTION_BEGIN + 13)
#define APP_ERR_MM_NW_REJ_EPS_SERV_NOT_ALLOW_IN_PLMN        (APP_ERR_MM_NW_SECTION_BEGIN + 14)
#define APP_ERR_MM_NW_REJ_NO_SUITABL_CELL                   (APP_ERR_MM_NW_SECTION_BEGIN + 15)
#define APP_ERR_MM_NW_REJ_MSC_UNREACHABLE                   (APP_ERR_MM_NW_SECTION_BEGIN + 16)
#define APP_ERR_MM_NW_REJ_NETWORK_FAILURE                   (APP_ERR_MM_NW_SECTION_BEGIN + 17)
#define APP_ERR_MM_NW_REJ_CS_NOT_AVAIL                      (APP_ERR_MM_NW_SECTION_BEGIN + 18)
#define APP_ERR_MM_NW_REJ_ESM_FAILURE                       (APP_ERR_MM_NW_SECTION_BEGIN + 19)
#define APP_ERR_MM_NW_REJ_MAC_FAILURE                       (APP_ERR_MM_NW_SECTION_BEGIN + 20)
#define APP_ERR_MM_NW_REJ_SYNCH_FAILURE                     (APP_ERR_MM_NW_SECTION_BEGIN + 21)
#define APP_ERR_MM_NW_REJ_PROCEDURE_CONGESTION              (APP_ERR_MM_NW_SECTION_BEGIN + 22)
#define APP_ERR_MM_NW_REJ_UE_SECU_CAP_MISMATCH              (APP_ERR_MM_NW_SECTION_BEGIN + 23)
#define APP_ERR_MM_NW_REJ_SECU_MODE_REJECTED_UNSPECIFIED    (APP_ERR_MM_NW_SECTION_BEGIN + 24)
#define APP_ERR_MM_NW_REJ_NOT_AUTHORIZED_FOR_THIS_CSG       (APP_ERR_MM_NW_SECTION_BEGIN + 25)
#define APP_ERR_MM_NW_REJ_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN   (APP_ERR_MM_NW_SECTION_BEGIN + 35)
#define APP_ERR_MM_NW_REJ_CS_FALLBACK_CALL_EST_NOT_ALLOWED  (APP_ERR_MM_NW_SECTION_BEGIN + 38)
#define APP_ERR_MM_NW_REJ_CS_DOMAIN_TMP_NOT_ALLOWED         (APP_ERR_MM_NW_SECTION_BEGIN + 39)
#define APP_ERR_MM_NW_REJ_NO_EPS_BEARER_CONTEXT_ACTIVATED   (APP_ERR_MM_NW_SECTION_BEGIN + 40)
#define APP_ERR_MM_NW_REJ_SERVER_NETWORK_FAILURE            (APP_ERR_MM_NW_SECTION_BEGIN + 42)
#define APP_ERR_MM_NW_REJ_SEMANTICALLY_INCORRECT_MSG        (APP_ERR_MM_NW_SECTION_BEGIN + 95)
#define APP_ERR_MM_NW_REJ_INVALID_MANDATORY_INF             (APP_ERR_MM_NW_SECTION_BEGIN + 96)
#define APP_ERR_MM_NW_REJ_MSG_NONEXIST_NOTIMPLEMENTE        (APP_ERR_MM_NW_SECTION_BEGIN + 97)
#define APP_ERR_MM_NW_REJ_MSG_TYPE_NOT_COMPATIBLE           (APP_ERR_MM_NW_SECTION_BEGIN + 98)
#define APP_ERR_MM_NW_REJ_IE_NONEXIST_NOTIMPLEMENTED        (APP_ERR_MM_NW_SECTION_BEGIN + 99)
#define APP_ERR_MM_NW_REJ_CONDITIONAL_IE_ERROR              (APP_ERR_MM_NW_SECTION_BEGIN + 100)
#define APP_ERR_MM_NW_REJ_MSG_NOT_COMPATIBLE                (APP_ERR_MM_NW_SECTION_BEGIN + 101)
#define APP_ERR_MM_NW_REJ_PROTOCOL_ERROR                    (APP_ERR_MM_NW_SECTION_BEGIN + 111)
#define APP_ERR_MM_NW_REJ_OTHERS                            (APP_ERR_MM_NW_SECTION_BEGIN + 255)


/* SM与APP错误码 */
#define APP_ERR_SM_CALL_CID_INVALID                         (APP_ERR_SM_SECTION_BEGIN + 0)
#define APP_ERR_SM_CALL_CID_ACTIVE                          (APP_ERR_SM_SECTION_BEGIN + 1)
#define APP_ERR_SM_CALL_MOD_CID_NOT_MATCH                   (APP_ERR_SM_SECTION_BEGIN + 2)
#define APP_ERR_SM_CALL_CID_NOT_MATCH_BEARER                (APP_ERR_SM_SECTION_BEGIN + 3)
#define APP_ERR_SM_BEARER_TYPE_NOT_DEDICATED                (APP_ERR_SM_SECTION_BEGIN + 4)
#define APP_ERR_SM_NO_INCOMING_CALL                         (APP_ERR_SM_SECTION_BEGIN + 5)
#define APP_ERR_SM_LLC_OR_SNDCP_FAIL                        (APP_ERR_SM_SECTION_BEGIN + 6)
#define APP_ERR_SM_REACTIV_REQ                              (APP_ERR_SM_SECTION_BEGIN + 7)
#define APP_ERR_SM_FEATURE_NOT_SUPPORT                      (APP_ERR_SM_SECTION_BEGIN + 8)
#define APP_ERR_SM_GPRS_ATTACH_FAIL                         (APP_ERR_SM_SECTION_BEGIN + 9)
#define APP_ERR_SM_OTHER_BEARER_CONT_EXIST                  (APP_ERR_SM_SECTION_BEGIN + 10)
#define APP_ERR_SM_NSAPI_IN_USE                             (APP_ERR_SM_SECTION_BEGIN + 11)
#define APP_ERR_SM_COLLISION_WITH_NW                        (APP_ERR_SM_SECTION_BEGIN + 12)
#define APP_ERR_SM_BEARER_INACTIVE                          (APP_ERR_SM_SECTION_BEGIN + 13)
#define APP_ERR_SM_DETACHED                                 (APP_ERR_SM_SECTION_BEGIN + 14)
#define APP_ERR_SM_LINK_CID_INVALID                         (APP_ERR_SM_SECTION_BEGIN + 15)
#define APP_ERR_SM_LINK_BEARER_INACTIVE                     (APP_ERR_SM_SECTION_BEGIN + 16)
#define APP_ERR_SM_APN_LEN_ILLEGAL                          (APP_ERR_SM_SECTION_BEGIN + 17)
#define APP_ERR_SM_APN_SYNTACTICAL_ERROR                    (APP_ERR_SM_SECTION_BEGIN + 18)
#define APP_ERR_SM_SET_APN_BEFORE_SET_AUTH                  (APP_ERR_SM_SECTION_BEGIN + 19)
#define APP_ERR_SM_AUTH_TYPE_ILLEGAL                        (APP_ERR_SM_SECTION_BEGIN + 20)
#define APP_ERR_SM_USER_NAME_TOO_LONG                       (APP_ERR_SM_SECTION_BEGIN + 21)
#define APP_ERR_SM_USER_PASSWORD_TOO_LONG                   (APP_ERR_SM_SECTION_BEGIN + 22)
#define APP_ERR_SM_ACCESS_NUM_TOO_LONG                      (APP_ERR_SM_SECTION_BEGIN + 23)
#define APP_ERR_SM_CALL_CID_IN_OPERATION                    (APP_ERR_SM_SECTION_BEGIN + 24)
#define APP_ERR_SM_BEARER_TYPE_NOT_DEFAULT                  (APP_ERR_SM_SECTION_BEGIN + 25)
#define APP_ERR_SM_BEARER_TYPE_ILLEGAL                      (APP_ERR_SM_SECTION_BEGIN + 26)
#define APP_ERR_SM_MUST_EXIST_DEFAULT_TYPE_CID              (APP_ERR_SM_SECTION_BEGIN + 27)
#define APP_ERR_SM_PDN_TYPE_ILLEGAL                         (APP_ERR_SM_SECTION_BEGIN + 28)
#define APP_ERR_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL             (APP_ERR_SM_SECTION_BEGIN + 29)
#define APP_ERR_SM_SUSPENDED                                (APP_ERR_SM_SECTION_BEGIN + 30)
#define APP_ERR_SM_MULTI_EMERGENCY_NOT_ALLOWED              (APP_ERR_SM_SECTION_BEGIN + 31)
#define APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED                (APP_ERR_SM_SECTION_BEGIN + 32)
#define APP_ERR_SM_MODIFY_EMERGENCY_NOT_ALLOWED             (APP_ERR_SM_SECTION_BEGIN + 33)
#define APP_ERR_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED      (APP_ERR_SM_SECTION_BEGIN + 34)
#define APP_ERR_SM_ONLY_EMERGENCY_ALLOWED                   (APP_ERR_SM_SECTION_BEGIN + 35)

#define APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED                  (APP_ERR_SM_SECTION_BEGIN + 36)

#define APP_ERR_SM_THROT_ALG_NOT_ALLOWED                    (APP_ERR_SM_SECTION_BEGIN + 37)

#define APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED_IGNORE           (APP_ERR_SM_SECTION_BEGIN + 38)
#define APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED_PERM             (APP_ERR_SM_SECTION_BEGIN + 39)
#define APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED_TEMP             (APP_ERR_SM_SECTION_BEGIN + 40)
#define APP_ERR_SM_BACKOFF_ALG_NOT_ALLOWED_RSV              (APP_ERR_SM_SECTION_BEGIN + 41)
#define APP_ERR_SM_THROT_T3396_IS_RUNNING                   (APP_ERR_SM_SECTION_BEGIN + 42)
#define APP_ERR_SM_NAS_SIG_LOW_PRIORITY_NOT_SUPPROT         (APP_ERR_SM_SECTION_BEGIN + 43)

#define APP_ERR_SM_NAS_MO_SIG_ACCESS_BAR                    (APP_ERR_SM_SECTION_BEGIN + 44)
#define APP_ERR_SM_MAX_EPS_NUM_REACHED                      (APP_ERR_SM_SECTION_BEGIN + 45)
#define APP_ERR_SM_THROT_BACKOFF_IS_RUNNING                 (APP_ERR_SM_SECTION_BEGIN + 46)
#define APP_ERR_SM_MM_NOT_SYNC                              (APP_ERR_SM_SECTION_BEGIN + 47)
#define APP_ERR_SM_NW_RECONFIGURE                           (APP_ERR_SM_SECTION_BEGIN + 48)
#define APP_ERR_SM_DELETE_SDF                               (APP_ERR_SM_SECTION_BEGIN + 49)
#define APP_ERR_SM_NOT_IN_ACL_LIST                          (APP_ERR_SM_SECTION_BEGIN + 50)
#define APP_ERR_SM_APN_DISABLE                              (APP_ERR_SM_SECTION_BEGIN + 51)
#define APP_ERR_SM_IMS_DEREG_NOT_ATTACH                     (APP_ERR_SM_SECTION_BEGIN + 52)
#define APP_ERR_SM_BEARER_ALLOC_NOT_ALLOWED     (APP_ERR_SM_SECTION_BEGIN + 53)
#define APP_ERR_SM_BEARER_MOD_NOT_ALLOWED     (APP_ERR_SM_SECTION_BEGIN + 54)

/* SM与网侧错误码 */
#define APP_ERR_SM_NW_OPERATOR_DETERMINED_BARRING           (APP_ERR_SM_NW_SECTION_BEGIN + 0)
#define APP_ERR_SM_NW_INSUFFICIENT_RESOURCES                (APP_ERR_SM_NW_SECTION_BEGIN + 1)
#define APP_ERR_SM_NW_MISSING_OR_UKNOWN_APN                 (APP_ERR_SM_NW_SECTION_BEGIN + 2)
#define APP_ERR_SM_NW_UNKNOWN_PDN_TYPE                      (APP_ERR_SM_NW_SECTION_BEGIN + 3)
#define APP_ERR_SM_NW_USER_AUTH_FAIL                        (APP_ERR_SM_NW_SECTION_BEGIN + 4)
#define APP_ERR_SM_NW_REQ_REJ_BY_SGW_OR_PGW                 (APP_ERR_SM_NW_SECTION_BEGIN + 5)
#define APP_ERR_SM_NW_REQ_REJ_UNSPECITY                     (APP_ERR_SM_NW_SECTION_BEGIN + 6)
#define APP_ERR_SM_NW_SERVICE_OPTION_NOT_SUPPORT            (APP_ERR_SM_NW_SECTION_BEGIN + 7)
#define APP_ERR_SM_NW_REQ_SERVICE_NOT_SUBSCRIBE             (APP_ERR_SM_NW_SECTION_BEGIN + 8)
#define APP_ERR_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER         (APP_ERR_SM_NW_SECTION_BEGIN + 9)
#define APP_ERR_SM_NW_PTI_ALREADY_IN_USE                    (APP_ERR_SM_NW_SECTION_BEGIN + 10)
#define APP_ERR_SM_NW_REGULAR_DEACT                         (APP_ERR_SM_NW_SECTION_BEGIN + 11)
#define APP_ERR_SM_NW_EPS_QOS_NOT_ACCEPT                    (APP_ERR_SM_NW_SECTION_BEGIN + 12)
#define APP_ERR_SM_NW_NET_FAIL                              (APP_ERR_SM_NW_SECTION_BEGIN + 13)
#define APP_ERR_SM_NW_SEMANTIC_ERR_IN_TFT                   (APP_ERR_SM_NW_SECTION_BEGIN + 14)
#define APP_ERR_SM_NW_SYNTACTIC_ERR_IN_TFT                  (APP_ERR_SM_NW_SECTION_BEGIN + 15)
#define APP_ERR_SM_NW_INVALID_EPS_BERER_IDENTITY            (APP_ERR_SM_NW_SECTION_BEGIN + 16)
#define APP_ERR_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER         (APP_ERR_SM_NW_SECTION_BEGIN + 17)
#define APP_ERR_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER       (APP_ERR_SM_NW_SECTION_BEGIN + 18)
#define APP_ERR_SM_NW_BEARER_WITHOUT_TFT_ACT                (APP_ERR_SM_NW_SECTION_BEGIN + 19)
#define APP_ERR_SM_NW_PTI_MISMATICH                         (APP_ERR_SM_NW_SECTION_BEGIN + 20)
#define APP_ERR_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED          (APP_ERR_SM_NW_SECTION_BEGIN + 21)
#define APP_ERR_SM_NW_PDN_TPYE_IPV4_ONLY_ALLOWED            (APP_ERR_SM_NW_SECTION_BEGIN + 22)
#define APP_ERR_SM_NW_PDN_TPYE_IPV6_ONLY_ALLOWED            (APP_ERR_SM_NW_SECTION_BEGIN + 23)
#define APP_ERR_SM_NW_SINGLE_ADDR_BERERS_ONLY_ALLOWED       (APP_ERR_SM_NW_SECTION_BEGIN + 24)
#define APP_ERR_SM_NW_ESM_INFO_NOT_RECEIVED                 (APP_ERR_SM_NW_SECTION_BEGIN + 25)
#define APP_ERR_SM_NW_PDN_CONN_NOT_EXIST                    (APP_ERR_SM_NW_SECTION_BEGIN + 26)
#define APP_ERR_SM_NW_MULTI_PDN_CONN_FOR_ONE_APN_NOT_ALLOWED    (APP_ERR_SM_NW_SECTION_BEGIN + 27)
#define APP_ERR_SM_NW_COLLISION_WITH_NW_INTIAL_REQEST       (APP_ERR_SM_NW_SECTION_BEGIN + 28)
#define APP_ERR_SM_NW_INVALID_PTI_VALUE                     (APP_ERR_SM_NW_SECTION_BEGIN + 29)
#define APP_ERR_SM_NW_SYNCTACTIC_INCORRECT_MSG              (APP_ERR_SM_NW_SECTION_BEGIN + 30)
#define APP_ERR_SM_NW_INVALID_MANDATORY_INFOR               (APP_ERR_SM_NW_SECTION_BEGIN + 31)
#define APP_ERR_SM_NW_MSG_TYPE_NON_EXIST                    (APP_ERR_SM_NW_SECTION_BEGIN + 32)
#define APP_ERR_SM_NW_MSG_TYPE_NOT_COMPATIBLE_WITH_PROT     (APP_ERR_SM_NW_SECTION_BEGIN + 33)
#define APP_ERR_SM_NW_INFOR_ELEM_NON_EXIST                  (APP_ERR_SM_NW_SECTION_BEGIN + 34)
#define APP_ERR_SM_NW_CONDITIONAL_IE_ERROR                  (APP_ERR_SM_NW_SECTION_BEGIN + 35)
#define APP_ERR_SM_NW_MSG_NOT_COMPATIBLE_WITH_PROT          (APP_ERR_SM_NW_SECTION_BEGIN + 36)
#define APP_ERR_SM_NW_PROT_ERR_UNSPECIFIED                  (APP_ERR_SM_NW_SECTION_BEGIN + 37)
#define APP_ERR_SM_NW_APN_RESTRICTION_INCOMPATIBLE_WITH_ACT_EPS_BEARER  (APP_ERR_SM_NW_SECTION_BEGIN + 38)
#define APP_ERR_SM_NW_UNSUPPORTED_QCI_VALUE                 (APP_ERR_SM_NW_SECTION_BEGIN + 39)
#define APP_ERR_SM_NW_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN     (APP_ERR_SM_NW_SECTION_BEGIN + 40)
#define APP_ERR_SM_NW_REACTIVATION_REQUESTED                      (APP_ERR_SM_NW_SECTION_BEGIN + 41)
#define APP_ERR_SM_NW_BEARER_HANDLING_NOT_SUPPORTED               (APP_ERR_SM_NW_SECTION_BEGIN + 42)
#define APP_ERR_SM_NW_MAXIMUM_NUMBER_OF_EPS_BEARERS_REACHED       (APP_ERR_SM_NW_SECTION_BEGIN + 43)

#define NAS_MM_MAX_TA_NUM               64                  /* TA 列表最大个数 */
#define NAS_MM_MAX_LA_NUM               64                  /* LA 列表最大个数 */

#define NAS_MM_MAX_PLMN_NUM             64
#define NAS_MM_MAX_UEID_BUF_SIZE        10                  /* UNIT: BYTE  */
#define NAS_MM_MAX_MSID_SIZE            10

#define NAS_MM_PLMN_AND_ACT_LEN         5

#define NAS_MM_SERVICE_TABLE_LEN        12

#define NAS_MM_MAX_PLMN_AND_ACT_LEN     (NAS_MM_PLMN_AND_ACT_LEN * NAS_MM_MAX_PLMN_NUM)
#define NAS_MM_LRPLMNSI_LEN             1

#define NAS_MM_AUTH_KEY_ASME_LEN        32
#define NAS_MM_AUTH_CKEY_LEN            16
#define NAS_MM_AUTH_IKEY_LEN            16
#define NAS_MM_AUTH_KEY_NAS_ENC_LEN     16
#define NAS_MM_AUTH_KEY_NAS_INT_LEN     16

#define NAS_MM_MIN_UE_NET_CAP_LEN       2
#define NAS_MM_MAX_UE_NET_CAP_LEN       13                  /* UE网络能力最大长度为13BYTE */
#define NAS_MM_MAX_MS_NET_CAP_LEN       8                   /* UNIT: BYTE  */

#define NAS_MMC_MAX_UPLMN_NUM           NAS_MM_MAX_PLMN_NUM   /* USIM卡中UPLMN最大个数 */
#define NAS_MMC_MAX_OPLMN_NUM           NAS_MM_MAX_PLMN_NUM   /* USIM卡中OPLMN最大个数 */

#define NAS_EMM_USIM_SEQ_UINT32_LEN  2

/* SQN verify */
#define NAS_EMM_USIM_SEQ_ARRAY_LEN   32
#define NAS_EMM_USIM_SQN_LEN         6

#define NAS_EMM_SOFT_USIM_KEY_LEN       16
#define NAS_EMM_SOFT_USIM_OP_LEN        16

#define MAX_SUPPORTED_CODEC_NUM         10

#define NAS_LMM_MAX_CAUSE_NUM           20

#define NAS_MM_MAX_PDP_REJ_CAUSE_NUM         16
#define NAS_MM_DAM_MAX_PLMN_NUM              16

#define NAS_LMM_DAM_NV_CSERVICE_MAX_VALUE     60
#define NAS_LMM_DAM_NV_CSERVICE_MIN_VALUE     1
#define NAS_LMM_DAM_CSERVICE_DEFAULT_VALUE    5
#define NAS_TMO_IMSI_HPLMN_MAX_NUM       8
#define NAS_MM_MAX_HOME_NODEB_NAME_LEN  (48)

#define NAS_MM_MAX_T3402_PLMN_NUM       (16)

#define NAS_MT_DETACH_TAU_PLMN_MAX_NUM  (6)

#define NAS_MM_MAX_T3396_PLMN_NUM       (7)
#define NAS_LMM_BAND_MAX_LENTH          (8)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
**************************************************************************/


/*****************************************************************************
 枚举名    : NAS_MM_RAT_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 接入技术的取值
*****************************************************************************/
enum NAS_MM_RAT_TYPE_ENUM
{
    NAS_MM_RAT_WCDMA                    = 0,
    NAS_MM_RAT_GSM_GPRS                 = 1,
    NAS_MM_RAT_LTE_FDD                  = 2,
    NAS_MM_RAT_LTE_TDD                  = 3,
    NAS_MM_RAT_TYPE_BUTT
};
typedef VOS_UINT32  NAS_MM_RAT_TYPE_ENUM_UINT32;
typedef NAS_MM_RAT_TYPE_ENUM_UINT32  NAS_EMM_RAT_TYPE_ENUM_UINT32;
typedef NAS_MM_RAT_TYPE_ENUM_UINT32  NAS_MMC_RAT_TYPE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MM_SEL_MODE_ENUM
 枚举说明  : 选网模式
*****************************************************************************/
enum    NAS_MM_SEL_MODE_ENUM
{
    NAS_MM_PLMN_SEL_AUTO                = 0x00,    /* 自动网络选择模式 */
    NAS_MM_PLMN_SEL_MANUAL              = 0x01,    /* 手动网络选择模式 */
    /*NAS_MM_PLMN_SEL_NO_IMSI             = 0x02, */   /* 卡无效模式 */
    NAS_MM_PLMN_SEL_BUTT
};
typedef VOS_UINT32 NAS_MM_SEL_MODE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_MM_UPDATE_STAT_ENUM
 枚举说明  : EMM UPDATE状态
*****************************************************************************/
enum    NAS_MM_UPDATE_STATE_ENUM
{
    NAS_MM_US_EU1_UPDATED               = 0x00,   /* 更新状态       */
    NAS_MM_US_EU2_NOT_UPDATED           = 0x01,   /* 未更新状态     */
    NAS_MM_US_EU3_ROAMING_NOT_ALLOWED   = 0x02,   /* 漫游不允许状态 */

    NAS_MM_US_BUTT
};
typedef VOS_UINT32  NAS_MM_UPDATE_STATE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_EMM_SOFT_USIM_AUTH_ALG_ENUM
 结构说明  : 软USIM完成AUTH使用的算法
*****************************************************************************/
enum NAS_EMM_SOFT_USIM_AUTH_ALG_ENUM
{
   NAS_EMM_SOFT_USIM_ALG_MILLENGE       = 0,    /* Millenge算法 */
   NAS_EMM_SOFT_USIM_ALG_TEST           = 1,    /* Test算法 */

   NAS_EMM_SOFT_USIM_ALG_BUTT
};
typedef VOS_UINT32   NAS_EMM_SOFT_USIM_AUTH_ALG_ENUM_UINT32;
/*=======================LAST RPLMN SELECTION INDICATION============================*/
enum NAS_MM_LRPLMNSI_ENUM
{
    NAS_MM_LRPLMNSI_RPLMN               = 0x00,
    NAS_MM_LRPLMNSI_HPLMN,
    NAS_MM_LRPLMNSI_BUTT
};
typedef VOS_UINT8 NAS_MM_LRPLMNSI_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_LMM_UE_OPERATION_MODE_ENUM
 结构说明  : UE的操作模式
*****************************************************************************/
enum NAS_LMM_UE_OPERATION_MODE_ENUM
{
   NAS_LMM_UE_PS_MODE_1                 = 1,    /* PS MODE 1 */
   NAS_LMM_UE_PS_MODE_2                 = 2,    /* PS MODE 2 */
   NAS_LMM_UE_CS_PS_MODE_1              = 3,    /* CS/PS MODE 1 */
   NAS_LMM_UE_CS_PS_MODE_2              = 4,    /* CS/PS MODE 2 */

   NAS_LMM_UE_MODE_BUTT
};
typedef VOS_UINT32   NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_CS_SERVICE_ENUM
 结构说明  : UE附着的CS业务类型
*****************************************************************************/
enum NAS_LMM_CS_SERVICE_ENUM
{
   NAS_LMM_CS_SERVICE_CSFB_SMS         = 1,    /* CSFB AND SMS */
   NAS_LMM_CS_SERVICE_SMS_ONLY         = 2,    /* SMS ONLY*/
   NAS_LMM_CS_SERVICE_1xCSFB           = 3,    /* 1xCSFB */

   NAS_LMM_CS_SERVICE_BUTT
};
typedef VOS_UINT32   NAS_LMM_CS_SERVICE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_LMM_GU_UE_MODE_ENUM
 结构说明  : GU的UE操作模式
*****************************************************************************/
enum NAS_LMM_GU_UE_MODE_ENUM
{
   NAS_LMM_GU_UE_MODE_PS                 = 1,
   NAS_LMM_GU_UE_MODE_CS                 = 2,
   NAS_LMM_GU_UE_MODE_CS_PS              = 3,

   NAS_LMM_GU_UE_MODE_BUTT
};
typedef VOS_UINT32   NAS_LMM_GU_UE_MODE_ENUM_UINT32;




/*****************************************************************************
 枚举名    : NAS_LMM_DISABLE_LTE_CAUSE_ENUM
 结构说明  : DISABLE LTE的原因
*****************************************************************************/
enum NAS_LMM_DISABLE_LTE_CAUSE_ENUM
{
   NAS_LMM_DISABLE_LTE_CAUSE_NULL                 = 1,

   NAS_LMM_DISABLE_LTE_CAUSE_BUTT
};
typedef VOS_UINT32   NAS_LMM_DISABLE_LTE_CAUSE_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_LMM_SUP_ENUM
 结构说明  : 是否支持某功能
*****************************************************************************/
enum NAS_LMM_SUP_ENUM
{
   NAS_LMM_NOT_SUP                      = 0,    /* 即 NOT AVAILABLE */
   NAS_LMM_SUP                          = 1,    /* 即 AVAILABLE */

   NAS_LMM_SUP_BUTT
};
typedef VOS_UINT32   NAS_LMM_SUP_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_LMM_SUP_VOICE_DOMAIN_ENUM
 结构说明  : UE支持的Voice Domain类型
*****************************************************************************/
enum NAS_LMM_SUP_VOICE_DOMAIN_ENUM
{
   NAS_LMM_SUP_VOICE_DOMAIN_CS              = 0,
   NAS_LMM_SUP_VOICE_DOMAIN_IMS             = 1,

   NAS_LMM_SUP_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32   NAS_LMM_SUP_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_LMM_SUP_SMS_DOMAIN_ENUM
 结构说明  : UE支持的SMS Domain类型
*****************************************************************************/
enum NAS_LMM_SUP_SMS_DOMAIN_ENUM
{
   NAS_LMM_SUP_SMS_DOMAIN_SGS             = 0,
   NAS_LMM_SUP_SMS_DOMAIN_IP              = 1,

   NAS_LMM_SUP_SMS_DOMAIN_BUTT
};
typedef VOS_UINT32   NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32;



/*****************************************************************************
 枚举名    : NAS_EMM_USAGE_SETTING_ENUM
 结构说明  :
*****************************************************************************/
enum    NAS_EMM_USAGE_SETTING_ENUM
{
    EMM_SETTING_VOICE_CENTRIC                = 0x00, /*语音中心 */
    EMM_SETTING_DATA_CENTRIC                ,

    EMM_USAGE_SETTING_BUTT
};
/*typedef VOS_UINT8   NAS_EMM_USAGE_SETTING_UINT8;*/
typedef VOS_UINT32  NAS_EMM_USAGE_SETTING_UINT32;

typedef NAS_EMM_USAGE_SETTING_UINT32    LNAS_LMM_UE_CENTER_ENUM_UINT32;


/*****************************************************************************
 枚举名    : NAS_LMM_VOICE_DOMAIN_ENUM
 结构说明  : UE的Voice Domain类型
*****************************************************************************/
enum NAS_LMM_VOICE_DOMAIN_ENUM
{
   NAS_LMM_VOICE_DOMAIN_CS_ONLY         = 0,    /* CS voice only */
   NAS_LMM_VOICE_DOMAIN_IMS_PS_ONLY     = 1,    /* IMS PS voice only */
   NAS_LMM_VOICE_DOMAIN_CS_PREFERRED    = 2,    /* CS voice preferred, IMS PS Voice as secondary */
   NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED= 3,    /* IMS PS voice preferred, CS Voice as secondary */

   NAS_LMM_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32   NAS_LMM_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_ESM_BEARER_PRIO_ENUM_UINT32
 结构说明  :
*****************************************************************************/
enum NAS_ESM_BEARER_PRIO_ENUM
{
   NAS_ESM_BEARER_PRIO_NORMAL         = 0,    /* CS voice only */
   NAS_ESM_BEARER_PRIO_LOW            = 1,    /* IMS PS voice only */

   NAS_ESM_BEARER_PRIO_BUTT
};
typedef VOS_UINT32   NAS_ESM_BEARER_PRIO_ENUM_UINT32;


/*****************************************************************************
 结构名称: LRRC_LNAS_CELL_TYPE_ENUM_UINT8
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum NAS_MM_CELL_TYPE_ENUM
{
    NAS_MM_CELL_TYPE_MACRO      = 0,          /* 小区类型是宏小区 */
    NAS_MM_CELL_TYPE_HYBRID     = 1,          /* 小区类型为混合小区 */
    NAS_MM_CELL_TYPE_CSG        = 2,          /* 小区类型为CSG小区 */
    NAS_MM_CELL_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MM_CELL_TYPE_ENUM_UINT8;
/*****************************************************************************
 结构名称: NAS_BACKOFF_RAT_SUPPORT_ENUM_UINT32
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
enum NAS_BACKOFF_RAT_SUPPORT_ENUM
{
    NAS_BACKOFF_RAT_SUPPORT_ALL    = 0,          /* 支持GUL */
    NAS_BACKOFF_RAT_SUPPORT_LTE    = 1,          /* 支持LTE */
    NAS_BACKOFF_RAT_SUPPORT_GU     = 2,          /* 支持GU */
    NAS_BACKOFF_RAT_SUPPORT_NONE   = 3,          /* GUL都不支持 */
    NAS_BACKOFF_RAT_SUPPORT_BUTT
};
typedef VOS_UINT32 NAS_BACKOFF_RAT_SUPPORT_ENUM_UINT32;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
结构名称    :NAS_MM_PLMN_ID_STRU中
使用说明    :
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------

    AT命令：
    at+cops=1,2,"mcc digit 1, mcc digit 2, mcc digit 3, mnc digit 1, mnc digit 2, mnc

digit 3",2 :

    e.g.
    at+cops=1,2,"789456",2 :
    --------------------------------------------------------------------------------
    (mcc digit 1)|(mcc digit 2)|(mcc digit 3)|(mnc digit 1)|(mnc digit 2)|(mnc digit 3)
    --------------------------------------------------------------------------------
       7         |     8       |      9      |     4       |      5      |     6
    --------------------------------------------------------------------------------

    在aucPlmnId[3]中的存放格式:
    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2 = 8        |           MCC digit 1 = 7
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3 = 6        |           MCC digit 3 = 9
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2 = 5        |           MNC digit 1 = 4
    ---------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
}NAS_MM_PLMN_ID_STRU;
typedef NAS_MM_PLMN_ID_STRU             NAS_EMM_PLMN_ID_STRU;
typedef NAS_MM_PLMN_ID_STRU             NAS_MMC_PLMN_ID_STRU;



/*****************************************************************************
 结构名    : NAS_MMC_OPRT_CTRL_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Operator Controlled PLMN数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;        /* PLMN ID个数   */
    NAS_MM_PLMN_ID_STRU                 astPlmnId[NAS_MMC_MAX_OPLMN_NUM];
} NAS_MMC_OPRT_CTRL_STRU;



/*****************************************************************************
结构名称    :NAS_MM_LAC_STRU
使用说明    :LAC信息 可参考24.008 10.5.1.3
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLac;
    VOS_UINT8                           ucLacCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_LAC_STRU;
typedef NAS_MM_LAC_STRU                 NAS_EMM_LAC_STRU;
typedef NAS_MM_LAC_STRU                 NAS_MMC_LAC_STRU;



/*****************************************************************************
结构名称    :NAS_MM_RAC_STRU
使用说明    :RAC信息 可参考24.008 10.5.5.15
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRac;
    VOS_UINT8                           aucRsv[3];
}NAS_MM_RAC_STRU;
typedef NAS_MM_RAC_STRU                 NAS_EMM_RAC_STRU;
typedef NAS_MM_RAC_STRU                 NAS_MMC_RAC_STRU;



/*****************************************************************************
结构名称    :NAS_MM_TAC_STRU
使用说明    :TAC信息  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_TAC_STRU;
typedef NAS_MM_TAC_STRU                 NAS_EMM_TAC_STRU;
typedef NAS_MM_TAC_STRU                 NAS_MMC_TAC_STRU;



/*****************************************************************************
 结构名    : NAS_MM_LA_STRU
 结构说明  : LA信息数据结构
*****************************************************************************/
typedef struct
{
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    NAS_MM_LAC_STRU                     stLac;
}NAS_MM_LA_STRU;
typedef NAS_MM_LA_STRU                  NAS_EMM_LA_STRU;
typedef NAS_MM_LA_STRU                  NAS_MMC_LA_STRU;


/*****************************************************************************
 结构名    : NAS_MM_RA_STRU
 结构说明  : RA信息数据结构
*****************************************************************************/
typedef struct
{
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    NAS_MM_LAC_STRU                     stLac;
    NAS_MM_RAC_STRU                     stRac;
}NAS_MM_RA_STRU;
typedef NAS_MM_RA_STRU                  NAS_EMM_RA_STRU;
typedef NAS_MM_RA_STRU                  NAS_MMC_RA_STRU;

/*****************************************************************************
 结构名    : NAS_MM_TA_STRU
 结构说明  : TA信息数据结构
*****************************************************************************/
typedef struct
{
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    NAS_MM_TAC_STRU                     stTac;
}NAS_MM_TA_STRU;
typedef NAS_MM_TA_STRU                  NAS_EMM_TA_STRU;
typedef NAS_MM_TA_STRU                  NAS_MMC_TA_STRU;

/*****************************************************************************
 结构名    : NAS_MM_TA_LIST_STRU
 结构说明  : TA信息数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTaNum;            /* TA的个数    */
    NAS_MM_TA_STRU                      astTa[NAS_MM_MAX_TA_NUM];
}NAS_MM_TA_LIST_STRU;

typedef NAS_MM_TA_LIST_STRU             NAS_EMM_TA_LIST_STRU;
typedef NAS_MM_TA_LIST_STRU             NAS_MMC_TA_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MM_FORB_TA_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FORB TA list数据结构
*****************************************************************************/
typedef NAS_MM_TA_LIST_STRU             NAS_MM_FORB_TA_LIST_STRU;
typedef NAS_MM_FORB_TA_LIST_STRU        NAS_EMM_FORB_TA_LIST_STRU;
typedef NAS_MM_FORB_TA_LIST_STRU        NAS_MMC_FORB_TA_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_LA_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LA list数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLaNum;
    NAS_MM_LA_STRU                      astLa[NAS_MM_MAX_LA_NUM];
}NAS_MM_LA_LIST_STRU;
typedef NAS_MM_LA_LIST_STRU             NAS_EMM_LA_LIST_STRU;
typedef NAS_MM_LA_LIST_STRU             NAS_MMC_LA_LIST_STRU;

/*****************************************************************************
 结构名    : NAS_MM_FORB_LA_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FORB LA list数据结构
*****************************************************************************/
typedef NAS_MM_LA_LIST_STRU             NAS_MM_FORB_LA_LIST_STRU;
typedef NAS_MM_FORB_LA_LIST_STRU        NAS_EMM_FORB_LA_LIST_STRU;
typedef NAS_MM_FORB_LA_LIST_STRU        NAS_MMC_FORB_LA_LIST_STRU;

/*****************************************************************************
结构名称    :NAS_MM_PLMN_LIST_STRU
使用说明    :10.5.13/3GPP TS 24.008 PLMN List information element
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MM_PLMN_ID_STRU                 astPlmnId[NAS_MM_MAX_PLMN_NUM];
}NAS_MM_PLMN_LIST_STRU;
typedef NAS_MM_PLMN_LIST_STRU           NAS_EMM_PLMN_LIST_STRU;
typedef NAS_MM_PLMN_LIST_STRU           NAS_MMC_PLMN_LIST_STRU;
typedef NAS_MM_PLMN_LIST_STRU           NAS_ESM_PLMN_LIST_STRU;
/*****************************************************************************
 结构名    : NAS_MM_PLMN_ACT_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 带有接入技术的PLMN
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    VOS_UINT8                           aucPlmnId[NAS_MM_MAX_PLMN_AND_ACT_LEN];
}NAS_MM_PLMN_ACT_LIST_STRU;

/*==============================================================================
结构名称    : NAS_MM_GUTI_HEAD_STRU
结构说明    : 24.301 9.9.3.10  EPS mobile identity
              两个成员的结构如下:
              ----------------------------------------------------------
              (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
              ----------------------------------------------------------
                  Length of EPS mobile identity contents, UNIT is byte
              ----------------------------------------------------------
                  1     1      1      1  | OorE |  Type of identity
              ----------------------------------------------------------
==============================================================================*/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_GUTI_HEAD_STRU;
typedef NAS_MM_GUTI_HEAD_STRU           NAS_EMM_GUTI_HEAD_STRU;
typedef NAS_MM_GUTI_HEAD_STRU           NAS_MMC_GUTI_HEAD_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MME_GROUPID_STRU
使用说明    :NAS_MM_MME_GROUPID_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
                               GroupId
    ----------------------------------------------------------------------------------
                              GroupIdCnt
    ----------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_MME_GROUPID_STRU;
typedef NAS_MM_MME_GROUPID_STRU         NAS_EMM_MME_GROUPID_STRU;
typedef NAS_MM_MME_GROUPID_STRU         NAS_MMC_MME_GROUPID_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MME_CODE_STRU
使用说明    :NAS_MM_MME_CODE_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}NAS_MM_MME_CODE_STRU;
typedef NAS_MM_MME_CODE_STRU            NAS_EMM_MME_CODE_STRU;
typedef NAS_MM_MME_CODE_STRU            NAS_MMC_MME_CODE_STRU;


/*****************************************************************************
结构名称    :NAS_MM_MTMSI_STRU
使用说明    :NAS_MM_MTMSI_STRU的相关参数
协议描述的 各DIGIT与字节/位的关系如下:
    ----------------------------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ----------------------------------------------------------------------------------
                               MTmsi
    ----------------------------------------------------------------------------------
    ......
    ----------------------------------------------------------------------------------
                             MTmsiCnt3
    ----------------------------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}NAS_MM_MTMSI_STRU;
typedef NAS_MM_MTMSI_STRU               NAS_EMM_MTMSI_STRU;
typedef NAS_MM_MTMSI_STRU               NAS_MMC_MTMSI_STRU;

/*****************************************************************************
结构名称    :NAS_MM_GUTI_STRU
使用说明    :NAS_MM_GUTI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    NAS_MM_GUTI_HEAD_STRU               stGutiHead;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    NAS_MM_MME_GROUPID_STRU             stMmeGroupId;
    NAS_MM_MME_CODE_STRU                stMmeCode;
    NAS_MM_MTMSI_STRU                   stMTmsi;
}NAS_MM_GUTI_STRU;
typedef NAS_MM_GUTI_STRU                NAS_EMM_GUTI_STRU;
typedef NAS_MM_GUTI_STRU                NAS_MMC_GUTI_STRU;

/*****************************************************************************
结构名称    : NAS_MM_MBMSSER_ID_STRU
使用说明    : 24.008 10.5.6.13
              MBMS Service ID (octet 3, 4 and 5)
              In the MBMS Service ID field bit 8 of octet 3 is the most
              significant bit and bit 1 of octet 5 the least significant bit.
              The coding of the MBMS Service ID is the responsibility of each
              administration. Coding using full hexadecimal representation may
              be used. The MBMS Service ID consists of 3 octets.
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMbmsSerId;
}NAS_MM_MBMSSER_ID_STRU;
typedef NAS_MM_MBMSSER_ID_STRU          NAS_EMM_MBMSSER_ID_STRU;
typedef NAS_MM_MBMSSER_ID_STRU          NAS_MMC_MBMSSER_ID_STRU;

/*****************************************************************************
结构名称    :NAS_MM_TMGI_STRU
使用说明    :NAS_MM_TMGI_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmn         :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitSpare          :31;

    NAS_MM_MBMSSER_ID_STRU              stMbmsSer;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
}NAS_MM_TMGI_STRU;
typedef NAS_MM_TMGI_STRU                NAS_EMM_TMGI_STRU;
typedef NAS_MM_TMGI_STRU                NAS_MMC_TMGI_STRU;

/*****************************************************************************
结构名称    :NAS_MM_TMGI_MBMS_HEAD_STRU
使用说明    :NAS_MM_TMGI_MBMS_HEAD_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeTi;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_TMGI_MBMS_HEAD_STRU;
typedef NAS_MM_TMGI_MBMS_HEAD_STRU      NAS_EMM_TMGI_MBMS_HEAD_STRU;
typedef NAS_MM_TMGI_MBMS_HEAD_STRU      NAS_MMC_TMGI_MBMS_HEAD_STRU;

/*****************************************************************************
结构名称    :NAS_MM_TMGI_MBMS_STRU
使用说明    :NAS_MM_TMGI_MBMS_STRU的相关参数
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpMbmsSesId  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitSpare          :31;

    NAS_MM_TMGI_MBMS_HEAD_STRU          stMsidHead;
    NAS_MM_TMGI_STRU                    stTmgi;
    VOS_UINT8                           ucMbmsSesId;
    VOS_UINT8                           aucRsv[3];
}NAS_MM_TMGI_MBMS_STRU;
typedef NAS_MM_TMGI_MBMS_STRU           NAS_EMM_TMGI_MBMS_STRU;
typedef NAS_MM_TMGI_MBMS_STRU           NAS_MMC_TMGI_MBMS_STRU;


/*****************************************************************************
结构名称    :NAS_MM_DRX_STRU
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSplitPgCode;      /* SPLIT PG CYCLE CODE*/
    VOS_UINT8                           ucPsDrxLen;         /* DRX length         */
    VOS_UINT8                           ucSplitOnCcch;      /* SPLIT on CCCH      */
    VOS_UINT8                           ucNonDrxTimer;      /* non-DRX timer      */
}NAS_MM_DRX_STRU;
typedef NAS_MM_DRX_STRU                 NAS_EMM_DRX_STRU;
typedef NAS_MM_DRX_STRU                 NAS_MMC_DRX_STRU;
/*****************************************************************************
结构名称    :NAS_MM_CSG_ID_HOME_NODEB_NAME_STRU
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHomeNodeBNameLen;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT8                           aucHomeNodeBName[NAS_MM_MAX_HOME_NODEB_NAME_LEN];
}NAS_MM_CSG_ID_HOME_NODEB_NAME_STRU;

/*****************************************************************************
结构名称    :NAS_MM_CSG_INFO_STRU
使用说明    :
*****************************************************************************/
typedef struct
{
    NAS_MM_CELL_TYPE_ENUM_UINT8         ucCellType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulCsgId;
}NAS_MM_CSG_INFO_STRU;


/*****************************************************************************
结构名称    :NAS_MM_NETWORK_ID_STRU
使用说明    :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPlmnId   :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpLac      :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRac      :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpTac      :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpCellId   :1;
    VOS_UINT32                          bitOpLteBand  :1;
    VOS_UINT32                          bitOpRsv      :26;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    NAS_MM_LAC_STRU                     stLac;
    NAS_MM_RAC_STRU                     stRac;
    NAS_MM_TAC_STRU                     stTac;
    VOS_UINT32                          ulCellId;        /* Cell Identity */
    VOS_UINT32                          ulForbiddenInfo;
    VOS_UINT32                          ulCellStatus;
    VOS_UINT32                          aulLteBand[NAS_LMM_BAND_MAX_LENTH];
    VOS_UINT32                          ulArfcn;                                /* 驻留频点信息 */
    NAS_MM_CELL_TYPE_ENUM_UINT8         ucCellType;
    VOS_UINT8                           ucAccessType;     /* 接入类型:TDD/FDD */
    VOS_UINT8                           ucBandWidth;
    VOS_UINT8                           ucSupportImsEmcFlag;
    VOS_UINT32                          ulCsgId;
}NAS_MM_NETWORK_ID_STRU;
typedef NAS_MM_NETWORK_ID_STRU          NAS_EMM_NETWORK_ID_STRU;
typedef NAS_MM_NETWORK_ID_STRU          NAS_MMC_NETWORK_ID_STRU;


/*****************************************************************************
结构名称    :NAS_MM_KSI_SN_STRU
使用说明    :KSI and sequence number, 24.301 9.9.3.17
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKsiSn;
    VOS_UINT8                           aucRsv[3];
}NAS_MM_KSI_SN_STRU;
typedef NAS_MM_KSI_SN_STRU              NAS_EMM_KSI_SN_STRU;
typedef NAS_MM_KSI_SN_STRU              NAS_MCM_KSI_SN_STRU;

/*****************************************************************************
结构名称    :NAS_MM_NKSI_STRU
使用说明    :NAS key set identifier, 24.301 9.9.3.19
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNksi;
    VOS_UINT8                           aucRsv[3];
}NAS_MM_NKSI_STRU;
typedef NAS_MM_NKSI_STRU                NAS_EMM_NKSI_STRU;
typedef NAS_MM_NKSI_STRU                NAS_MMC_NKSI_STRU;

/*****************************************************************************
结构名称    :NAS_MM_UE_NET_CAP_STRU
使用说明    :24.301-950 9.9.3.34
    --------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    --------------------------------------------------------------
        Length of UE network capability contents, UNIT is byte      octet 0
    --------------------------------------------------------------
        EEA0 |EEA 1|EEA2 |EEA3 |EEA4 |EEA5 |EEA6 |EEA7              octet 1
    --------------------------------------------------------------
        EIA0 |EIA1 |EIA2 |EIA3 |EIA4 |EIA5 |EIA6 |EIA7              octet 2
    --------------------------------------------------------------
        UEA0 |UEA1 |UEA2 |UEA3 |UEA4 |UEA5 |UEA6 |UEA7              octet 3
    --------------------------------------------------------------
        UCS2 |UIA1 |UIA2 |UIA3 |UIA4 |UIA5 |UIA6 |UIA7              octet 4
    --------------------------------------------------------------
        0    |0    |0    |0    |LPP  |LCS  |1xSR |NF                octet 5
        spare|spare|spare|spar |     |     |VCC  |
    --------------------------------------------------------------
         spare                                                      octet6-13
    --------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucUeNetCapLen;
    VOS_UINT8                           aucUeNetCap[NAS_MM_MAX_UE_NET_CAP_LEN];
    VOS_UINT8                           aucRsv[2];
}NAS_MM_UE_NET_CAP_STRU;
typedef NAS_MM_UE_NET_CAP_STRU          NAS_EMM_UE_NET_CAP_STRU;
typedef NAS_MM_UE_NET_CAP_STRU          NAS_MMC_UE_NET_CAP_STRU;


/*****************************************************************************
结构名称    :NAS_MM_MS_NET_CAP_STRU
使用说明    :24.008 10.5.5.12

    aucMsNetCap数组中与协议描述的字节/位的关系如下:
    --------------------------------------------------------------
    (BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    --------------------------------------------------------------
        Length of MS network capability contents, UNIT is byte      octet 0
    --------------------------------------------------------------
        MS network capability value                                 octet 1-8
    --------------------------------------------------------------
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMsNetCapLen;
    VOS_UINT8                           aucMsNetCap[NAS_MM_MAX_MS_NET_CAP_LEN];
    VOS_UINT8                           aucRsv[3];
}NAS_MM_MS_NET_CAP_STRU;
typedef NAS_MM_MS_NET_CAP_STRU          NAS_EMM_MS_NET_CAP_STRU;
typedef NAS_MM_MS_NET_CAP_STRU          NAS_MMC_MS_NET_CAP_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MS_CLASSMARK_1_STRU
使用说明    :24.008 840 10.5.1.5
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucValue;
    VOS_UINT8                           aucRsv[3];

}NAS_MM_MS_CLASSMARK_1_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MS_CLASSMARK_2_STRU
使用说明    :24.008 840 10.5.1.6
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenLvLen;

    VOS_UINT8                           bitRfPowerCap   : 3;
    VOS_UINT8                           bitA5_1         : 1;
    VOS_UINT8                           bitEsind        : 1;
    VOS_UINT8                           bitRevisionLev  : 2;
    VOS_UINT8                           bitSpare1       : 1;


    VOS_UINT8                           bitFc           : 1;
    VOS_UINT8                           bitVgcs         : 1;
    VOS_UINT8                           bitVbs          : 1;
    VOS_UINT8                           bitSmCap        : 1;
    VOS_UINT8                           bitSsScreenInd  : 2;
    VOS_UINT8                           bitPsCap        : 1;
    VOS_UINT8                           bitSpare2       : 1;

    VOS_UINT8                           bitA5_2         : 1;
    VOS_UINT8                           bitA5_3         : 1;
    VOS_UINT8                           bitCMSP         : 1;
    VOS_UINT8                           bitSolsa        : 1;
    VOS_UINT8                           bitUcs2         : 1;
    VOS_UINT8                           bitLcsvaCap     : 1;
    VOS_UINT8                           bitSpare3       : 1;
    VOS_UINT8                           bitCm3          : 1;

}NAS_MM_MS_CLASSMARK_2_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MS_CLASSMARK_3_STRU
使用说明    :24.008 840 10.5.1.7
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenLvLen;
    VOS_UINT8                           aucValue[32];
    VOS_UINT8                           aucRsv[3];

}NAS_MM_MS_CLASSMARK_3_STRU;

/*****************************************************************************
结构名称    :NAS_MM_MS_CLASSMARK_STRU
使用说明    :24.008 840 10.5.1.6
            0   EPS encryption algorithm *** not supported
            1   EPS encryption algorithm *** supported

            #define NAS_MM_ALGORITHM_NOT_SUPPORT    0
            #define NAS_MM_ALGORITHM_SUPPORT        1
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpClassMark1     :1;
    VOS_UINT32                          bitOpClassMark2     :1;
    VOS_UINT32                          bitOpClassMark3     :1;

    VOS_UINT32                          bitOpRsv            :29;

    NAS_MM_MS_CLASSMARK_1_STRU          stClassMark1;
    NAS_MM_MS_CLASSMARK_2_STRU          stClassMark2;
    NAS_MM_MS_CLASSMARK_3_STRU          stClassMark3;

}NAS_MM_MS_CLASSMARK_STRU;
typedef NAS_MM_MS_CLASSMARK_STRU        NAS_EMM_MS_CLASSMARK_STRU;
typedef NAS_MM_MS_CLASSMARK_STRU        NAS_MMC_MS_CLASSMARK_STRU;



/*****************************************************************************
结构名称    :NAS_EMM_SRV_INFO_STRU
使用说明    :MM的公用信息

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEmmSrvInfoLen;
    VOS_UINT8                           aucEmmSrvInfo[NAS_MM_SERVICE_TABLE_LEN];
    VOS_UINT8                           aucRsv[2];
}NAS_EMM_SRV_INFO_STRU;


typedef struct
{
    VOS_UINT32                      aulSEQ[NAS_EMM_USIM_SEQ_UINT32_LEN];
}NAS_EMM_USIM_SEQ_STRU;

/*****************************************************************************
结构名称    :NAS_EMM_USIM_CONTROL_STRU
使用说明    :鉴权过程中RES的数据结构
*****************************************************************************/
typedef struct
{

    NAS_EMM_USIM_SEQ_STRU            astSEQ[NAS_EMM_USIM_SEQ_ARRAY_LEN];
    NAS_EMM_USIM_SEQ_STRU            stMaxSEQ;
    VOS_UINT8                        ucMaxInd;
    VOS_UINT8                        aucMaxSqn[NAS_EMM_USIM_SQN_LEN];
    VOS_UINT8                        aucRsv[1];
}NAS_EMM_USIM_CONTROL_STRU;

/*****************************************************************************
结构名称    :NAS_EMM_SOFT_USIM_AUTH_PARAM_STRU
使用说明    :软USIM模拟完成鉴权流程需要的参数,支持TEST和Millenge两种算法
*****************************************************************************/
typedef struct
{
    NAS_EMM_SOFT_USIM_AUTH_ALG_ENUM_UINT32 enSoftUsimAlg;
    VOS_UINT8                           aucKey[NAS_EMM_SOFT_USIM_KEY_LEN];
    VOS_UINT8                           aucOp[NAS_EMM_SOFT_USIM_OP_LEN];
}NAS_EMM_SOFT_USIM_AUTH_PARAM_STRU;


/*****************************************************************************
结构名称    :NAS_LMM_ADAPTION_CAUSE_STRU
使用说明    :用户配置网侧原因的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucCnCause;          /*网侧原因值*/
    VOS_UINT8                       ucHplmnCause;       /*用户配置匹配HPLMN的原因值*/
    VOS_UINT8                       ucNotHplmnCause;    /*用户配置不匹配HPLMN的原因值*/
    VOS_UINT8                       ucRsv;
}NAS_LMM_ADAPTION_CAUSE_STRU;

/*****************************************************************************
结构名称    :NAS_LMM_CONFIG_CAUSE_STRU
使用说明    :用户配置网侧原因的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCauseNum;     /*用户配置的原因值数*/
    VOS_UINT8                           aucRsv[3];
    NAS_LMM_ADAPTION_CAUSE_STRU         astAdaptCause[NAS_LMM_MAX_CAUSE_NUM];
}LNAS_LMM_CONFIG_NWCAUSE_STRU;


/*****************************************************************************
结构名称    :NAS_MM_DAM_PLMN_LIST_STRU
使用说明    :美国需求DAM生效的PLMN列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MM_PLMN_ID_STRU                 astPlmnId[NAS_MM_DAM_MAX_PLMN_NUM];
} NAS_MM_DAM_PLMN_LIST_STRU;

/*****************************************************************************
结构名称    :NAS_CONFIG_PDP_REJ_CAUSE_STRU
使用说明    :NV配置的PDP激活被拒原因值列表
*****************************************************************************/
typedef struct
{
    VOS_UINT8                ucCauseNum;     /*用户配置的原因值数*/
    VOS_UINT8                aucRsv[3];
    VOS_UINT8                aucCause[NAS_MM_MAX_PDP_REJ_CAUSE_NUM];
} NAS_CONFIG_PDP_REJ_CAUSE_STRU;

typedef NAS_CONFIG_PDP_REJ_CAUSE_STRU  NAS_CONFIG_PDP_PERM_CAUSE_STRU;
typedef NAS_CONFIG_PDP_REJ_CAUSE_STRU  NAS_CONFIG_PDP_TEMP_CAUSE_STRU;
typedef NAS_MM_DAM_PLMN_LIST_STRU      NAS_DAM_IMSI_PLMN_LIST;

/*****************************************************************************
结构名称    :NAS_DAM_CONFIG_PLMN_PARA
使用说明    :DAM需求配置的某运营商的MCC-MNC段和DAM生效的PLMN列表
*****************************************************************************/
typedef struct
{
    NAS_DAM_IMSI_PLMN_LIST               stImsiPlmnList;  /* IMSI的MCC-MNC段列表  */
    NAS_MM_DAM_PLMN_LIST_STRU            stDamPlmnList;   /* DAM特性生效的PLMN列表 */
} NAS_DAM_CONFIG_PLMN_PARA;
/*****************************************************************************
结构名称    :NAS_CONFIG_BACKOFF_FX_PARA_STRU
使用说明    :NV配置的Back-off算法参数Fx
*****************************************************************************/
typedef struct
{
    VOS_UINT8              ucFxIgnore;   /* 1小时内超时限定次数     */
    VOS_UINT8              ucFxPerm;     /* 1小时内永久拒绝限定次数 */
    VOS_UINT8              ucFxTemp;     /* 1小时内临时拒绝限定次数 */
    VOS_UINT8              ucRsv;
} NAS_CONFIG_BACKOFF_FX_PARA_STRU;

/*****************************************************************************
结构名称    :NAS_DAM_CONFIG_PLMN_PARA
使用说明    :TMO定制需求生效的IMSI PLMN列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulPlmnNum;
    NAS_MM_PLMN_ID_STRU        astPlmnId[NAS_TMO_IMSI_HPLMN_MAX_NUM];
} NAS_TMO_IMSI_HPLMN_LIST;
typedef NAS_TMO_IMSI_HPLMN_LIST LNAS_LMM_NV_TMO_IMSI_HPLMN_LIST_CONFIG_STRU;

/*****************************************************************************
结构名称    :NAS_PLMN_T3402_STRU
使用说明    :LNAS关于DATA RETRY特性T3402定时器针对PLMN列表维护的数据结构
*****************************************************************************/
typedef struct
{
    NAS_MM_PLMN_ID_STRU                 stPlmnId;                               /* 受控制的PLMN ID */
    VOS_UINT32                          ulTimerLen;                             /* 网侧分配的T3402定时器时长(UNIT: 秒) */
    VOS_UINT32                          ulTimerRemainLen;                       /* 关机时Timer暂停状态下的剩余时长(UNIT: ms)*/
}NAS_PLMN_T3402_STRU;
/*****************************************************************************
结构名称    :NAS_MM_MT_DETACH_TAU_PLMN_LIST_STRU
使用说明    :TAU优化网络周期DETACH生效的PLMN列表
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    NAS_MM_PLMN_ID_STRU                 astPlmnId[NAS_MT_DETACH_TAU_PLMN_MAX_NUM];
} NAS_MM_MT_DETACH_TAU_PLMN_LIST_STRU;
/*****************************************************************************
结构名称    :NAS_PLMN_T3396_STRU
使用说明    :LNAS关于DATA RETRY特性T3396定时器针对PLMN列表维护的数据结构
*****************************************************************************/
typedef struct
{
    NAS_MM_PLMN_ID_STRU                 stPlmnId;                               /* 受控制的PLMN ID */
    VOS_UINT32                          ulT3396RemainLenForCustom;              /* 关机时Timer暂停状态下的剩余时长(UNIT: ms)*/
}NAS_PLMN_T3396_STRU;
/*****************************************************************************
 结构名    : ESM_APP_ERR_CODE_MAP_STRU
 结构说明  : ESM和APS间原因值转换
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enEsmCuase;
    VOS_UINT32                          ulAppCause;
} ESM_APP_ERR_CODE_MAP_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppNasComm.h */
