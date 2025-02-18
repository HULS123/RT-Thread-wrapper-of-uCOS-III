/*
 * Copyright (c) 2021, Meco Jianting Man <jiantingman@foxmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-25     Meco Man     the first verion
 */
/*
*********************************************************************************************************
*                                              uC/OS-III
*                                        The Real-Time Kernel
*
*                    Copyright 2009-2020 Silicon Laboratories Inc. www.silabs.com
*
*                                 SPDX-License-Identifier: APACHE-2.0
*
*               This software is subject to an open source license and is distributed by
*                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
*                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
*
*********************************************************************************************************
*/
/*
************************************************************************************************************************
*                                                      uC/OS-III
*                                                 The Real-Time Kernel
*
*                                  (c) Copyright 2009-2012; Micrium, Inc.; Weston, FL
*                           All rights reserved.  Protected by international copyright laws.
*
*                                                  DEBUGGER CONSTANTS
*
* File    : OS_DBG.C
* By      : JJL
* Version : V3.03.00
*
* LICENSING TERMS:
* ---------------
*           uC/OS-III is provided in source form for FREE short-term evaluation, for educational use or
*           for peaceful research.  If you plan or intend to use uC/OS-III in a commercial application/
*           product then, you need to contact Micrium to properly license uC/OS-III for its use in your
*           application/product.   We provide ALL the source code for your convenience and to help you
*           experience uC/OS-III.  The fact that the source is provided does NOT mean that you can use
*           it commercially without paying a licensing fee.
*
*           Knowledge of the source code may NOT be used to develop a similar product.
*
*           Please help us continue to provide the embedded community with the finest software available.
*           Your honesty is greatly appreciated.
*
*           You can contact us at www.micrium.com, or by phone at +1 (954) 217-2036.
************************************************************************************************************************
*/

#include "os.h"

#ifndef PKG_USING_UCOSIII_WRAPPER_TINY

CPU_INT16U  const  OSDbg_DbgEn                 = OS_CFG_DBG_EN;                /* Debug constants are defined below   */

#if OS_CFG_DBG_EN > 0u

/*
************************************************************************************************************************
*                                                      DEBUG DATA
************************************************************************************************************************
*/

CPU_INT08U  const  OSDbg_ArgChkEn              = OS_CFG_ARG_CHK_EN;
CPU_INT08U  const  OSDbg_AppHooksEn            = OS_CFG_APP_HOOKS_EN;

CPU_INT32U  const  OSDbg_EndiannessTest        = 0x12345678LU;                 /* Variable to test CPU endianness     */

CPU_INT08U  const  OSDbg_CalledFromISRChkEn    = OS_CFG_CALLED_FROM_ISR_CHK_EN;

CPU_INT08U  const  OSDbg_FlagEn                = OS_CFG_FLAG_EN;
OS_FLAG_GRP const  OSDbg_FlagGrp               = { 0u };
#if OS_CFG_FLAG_EN > 0u
CPU_INT08U  const  OSDbg_FlagDelEn             = OS_CFG_FLAG_DEL_EN;
CPU_INT08U  const  OSDbg_FlagModeClrEn         = OS_CFG_FLAG_MODE_CLR_EN;
CPU_INT08U  const  OSDbg_FlagPendAbortEn       = OS_CFG_FLAG_PEND_ABORT_EN;
CPU_INT16U  const  OSDbg_FlagGrpSize           = sizeof(OS_FLAG_GRP);          /* Size in Bytes of OS_FLAG_GRP        */
CPU_INT16U  const  OSDbg_FlagWidth             = sizeof(OS_FLAGS);             /* Width (in bytes) of OS_FLAGS        */
#else
CPU_INT08U  const  OSDbg_FlagDelEn             = 0u;
CPU_INT08U  const  OSDbg_FlagModeClrEn         = 0u;
CPU_INT08U  const  OSDbg_FlagPendAbortEn       = 0u;
CPU_INT16U  const  OSDbg_FlagGrpSize           = 0u;
CPU_INT16U  const  OSDbg_FlagWidth             = 0u;
#endif

#if OS_CFG_ISR_POST_DEFERRED_EN > 0u
CPU_INT16U  const  OSDbg_IntQ                  = sizeof(OS_INT_Q);
#else
CPU_INT16U  const  OSDbg_IntQ                  = 0u;
#endif

OS_MEM      const  OSDbg_Mem                   = { 0u };
CPU_INT08U  const  OSDbg_MemEn                 = OS_CFG_MEM_EN;
#if OS_CFG_MEM_EN > 0u
CPU_INT16U  const  OSDbg_MemSize               = sizeof(OS_MEM);               /* Mem. Partition header size (bytes)  */
#else
CPU_INT16U  const  OSDbg_MemSize               = 0u;
#endif


CPU_INT08U  const  OSDbg_MsgEn                 = OS_MSG_EN;
#if (OS_MSG_EN) > 0u
CPU_INT16U  const  OSDbg_MsgSize               = 0u;
CPU_INT16U  const  OSDbg_MsgPoolSize           = 0u;
CPU_INT16U  const  OSDbg_MsgQSize              = 0u;
#endif


OS_MUTEX    const  OSDbg_Mutex                 = { 0u };
CPU_INT08U  const  OSDbg_MutexEn               = OS_CFG_MUTEX_EN;
#if OS_CFG_MUTEX_EN > 0u
CPU_INT08U  const  OSDbg_MutexDelEn            = OS_CFG_MUTEX_DEL_EN;
CPU_INT08U  const  OSDbg_MutexPendAbortEn      = OS_CFG_MUTEX_PEND_ABORT_EN;
CPU_INT16U  const  OSDbg_MutexSize             = sizeof(OS_MUTEX);             /* Size in bytes of OS_MUTEX           */
#else
CPU_INT08U  const  OSDbg_MutexDelEn            = 0u;
CPU_INT08U  const  OSDbg_MutexPendAbortEn      = 0u;
CPU_INT16U  const  OSDbg_MutexSize             = 0u;
#endif

CPU_INT08U  const  OSDbg_ObjTypeChkEn          = OS_CFG_OBJ_TYPE_CHK_EN;

CPU_INT16U  const  OSDbg_PrioMax               = OS_CFG_PRIO_MAX;              /* Maximum number of priorities        */
CPU_INT16U  const  OSDbg_PrioTblSize           = sizeof(OSPrioTbl);

CPU_INT16U  const  OSDbg_PtrSize               = sizeof(void *);               /* Size in Bytes of a pointer          */


CPU_INT08U  const  OSDbg_QEn                   = OS_CFG_Q_EN;
#if OS_CFG_Q_EN > 0u
OS_Q        const  OSDbg_Q                     = { 0u };
CPU_INT08U  const  OSDbg_QDelEn                = OS_CFG_Q_DEL_EN;
CPU_INT08U  const  OSDbg_QFlushEn              = OS_CFG_Q_FLUSH_EN;
CPU_INT08U  const  OSDbg_QPendAbortEn          = OS_CFG_Q_PEND_ABORT_EN;
CPU_INT16U  const  OSDbg_QSize                 = sizeof(OS_Q);                 /* Size in bytes of OS_Q structure     */
#else
CPU_INT08U  const  OSDbg_QDelEn                = 0u;
CPU_INT08U  const  OSDbg_QFlushEn              = 0u;
CPU_INT08U  const  OSDbg_QPendAbortEn          = 0u;
CPU_INT16U  const  OSDbg_QSize                 = 0u;
#endif


CPU_INT08U  const  OSDbg_SchedRoundRobinEn     = OS_CFG_SCHED_ROUND_ROBIN_EN;


OS_SEM      const  OSDbg_Sem                   = { 0u };
CPU_INT08U  const  OSDbg_SemEn                 = OS_CFG_SEM_EN;
#if OS_CFG_SEM_EN > 0u
CPU_INT08U  const  OSDbg_SemDelEn              = OS_CFG_SEM_DEL_EN;
CPU_INT08U  const  OSDbg_SemPendAbortEn        = OS_CFG_SEM_PEND_ABORT_EN;
CPU_INT08U  const  OSDbg_SemSetEn              = OS_CFG_SEM_SET_EN;
CPU_INT16U  const  OSDbg_SemSize               = sizeof(OS_SEM);               /* Size in bytes of OS_SEM             */
#else
CPU_INT08U  const  OSDbg_SemDelEn              = 0u;
CPU_INT08U  const  OSDbg_SemPendAbortEn        = 0u;
CPU_INT08U  const  OSDbg_SemSetEn              = 0u;
CPU_INT16U  const  OSDbg_SemSize               = 0u;
#endif

CPU_INT08U  const  OSDbg_StkWidth              = sizeof(CPU_STK);

CPU_INT08U  const  OSDbg_StatTaskEn            = OS_CFG_STAT_TASK_EN;
CPU_INT08U  const  OSDbg_StatTaskStkChkEn      = OS_CFG_STAT_TASK_STK_CHK_EN;

CPU_INT08U  const  OSDbg_TaskChangePrioEn      = OS_CFG_TASK_CHANGE_PRIO_EN;
CPU_INT08U  const  OSDbg_TaskDelEn             = OS_CFG_TASK_DEL_EN;
CPU_INT08U  const  OSDbg_TaskQEn               = OS_CFG_TASK_Q_EN;
CPU_INT08U  const  OSDbg_TaskQPendAbortEn      = OS_CFG_TASK_Q_PEND_ABORT_EN;
CPU_INT08U  const  OSDbg_TaskProfileEn         = OS_CFG_TASK_PROFILE_EN;
CPU_INT16U  const  OSDbg_TaskRegTblSize        = OS_CFG_TASK_REG_TBL_SIZE;
CPU_INT08U  const  OSDbg_TaskSemPendAbortEn    = OS_CFG_TASK_SEM_PEND_ABORT_EN;
CPU_INT08U  const  OSDbg_TaskSuspendEn         = OS_CFG_TASK_SUSPEND_EN;


CPU_INT16U  const  OSDbg_TCBSize               = sizeof(OS_TCB);               /* Size in Bytes of OS_TCB             */

CPU_INT08U  const  OSDbg_TimeDlyHMSMEn         = OS_CFG_TIME_DLY_HMSM_EN;
CPU_INT08U  const  OSDbg_TimeDlyResumeEn       = OS_CFG_TIME_DLY_RESUME_EN;

#if defined(OS_CFG_TLS_TBL_SIZE) && (OS_CFG_TLS_TBL_SIZE > 0u)
CPU_INT16U  const  OSDbg_TLS_TblSize           = OS_CFG_TLS_TBL_SIZE * sizeof(OS_TLS);
#else
CPU_INT16U  const  OSDbg_TLS_TblSize           = 0u;
#endif


OS_TMR      const  OSDbg_Tmr                   = { 0u };
CPU_INT08U  const  OSDbg_TmrEn                 = OS_CFG_TMR_EN;
#if OS_CFG_TMR_EN > 0u
CPU_INT08U  const  OSDbg_TmrDelEn              = OS_CFG_TMR_DEL_EN;
CPU_INT16U  const  OSDbg_TmrSize               = sizeof(OS_TMR);
#else
CPU_INT08U  const  OSDbg_TmrDelEn              = 0u;
CPU_INT16U  const  OSDbg_TmrSize               = 0u;
CPU_INT16U  const  OSDbg_TmrSpokeSize          = 0u;
#endif

CPU_INT16U  const  OSDbg_VersionNbr            = OS_VERSION;

/*$PAGE*/
/*
************************************************************************************************************************
*                                                      DEBUG DATA
*                                     TOTAL DATA SPACE (i.e. RAM) USED BY uC/OS-III
************************************************************************************************************************
*/

CPU_INT32U  const  OSDbg_DataSize = sizeof(OSIntNestingCtr)

#if OS_CFG_APP_HOOKS_EN > 0u
                                  + sizeof(OS_AppTaskCreateHookPtr)
                                  + sizeof(OS_AppTaskDelHookPtr)
                                  + sizeof(OS_AppIdleTaskHookPtr)
                                  + sizeof(OS_AppStatTaskHookPtr)
#endif

#if OS_CFG_STAT_TASK_EN > 0u
                                  + sizeof(OSIdleTaskCtr)
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
                                  + sizeof(OSIntDisTimeMax)
#endif

#if OS_CFG_ISR_POST_DEFERRED_EN > 0u
                                  + sizeof(OSIntQInPtr)
                                  + sizeof(OSIntQOutPtr)
                                  + sizeof(OSIntQNbrEntries)
                                  + sizeof(OSIntQNbrEntriesMax)
                                  + sizeof(OSIntQOvfCtr)
                                  + sizeof(OSIntQTaskTCB)
                                  + sizeof(OSIntQTaskTimeMax)
#endif

                                  + sizeof(OSRunning)
                                  + sizeof(OSInitialized)

#ifdef OS_SAFETY_CRITICAL_IEC61508
                                  + sizeof(OSSafetyCriticalStartFlag)
#endif

#if OS_CFG_FLAG_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSFlagDbgListPtr)
#endif
                                  + sizeof(OSFlagQty)
#endif

#if OS_CFG_MEM_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSMemDbgListPtr)
#endif
                                  + sizeof(OSMemQty)
#endif

#if OS_CFG_MUTEX_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSMutexDbgListPtr)
#endif
                                  + sizeof(OSMutexQty)
#endif

                                  + sizeof(OSPrioCur)
                                  + sizeof(OSPrioTbl)

#if OS_CFG_Q_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSQDbgListPtr)
#endif
                                  + sizeof(OSQQty)
#endif

                                  + sizeof(OSSchedLockNestingCtr)

#if OS_CFG_SCHED_LOCK_TIME_MEAS_EN > 0u
                                  + sizeof(OSSchedLockTimeBegin)
                                  + sizeof(OSSchedLockTimeMax)
                                  + sizeof(OSSchedLockTimeMaxCur)
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN
                                  + sizeof(OSSchedRoundRobinDfltTimeQuanta)
                                  + sizeof(OSSchedRoundRobinEn)
#endif

#if OS_CFG_SEM_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSSemDbgListPtr)
#endif
                                  + sizeof(OSSemQty)
#endif

#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSTaskDbgListPtr)
#endif
                                  + sizeof(OSTaskQty)

#if OS_CFG_STAT_TASK_EN > 0u
                                  + sizeof(OSStatResetFlag)
                                  + sizeof(OSStatTaskCPUUsage)
                                  + sizeof(OSStatTaskCPUUsageMax)
                                  + sizeof(OSStatTaskCtr)
                                  + sizeof(OSStatTaskCtrMax)
                                  + sizeof(OSStatTaskCtrRun)
                                  + sizeof(OSStatTaskRdy)
                                  + sizeof(OSStatTaskTCB)
#endif

#if OS_CFG_TMR_EN > 0u
#if OS_CFG_DBG_EN > 0u
                                  + sizeof(OSTmrDbgListPtr)
#endif
                                  + sizeof(OSTmrQty)
#endif

#if OS_CFG_TASK_REG_TBL_SIZE > 0u
                                  + sizeof(OSTaskRegNextAvailID)
#endif

                                  + sizeof(OSTCBCurPtr)
                                  ;


/*
************************************************************************************************************************
*                                               OS DEBUG INITIALIZATION
*
* Description: This function is used to make sure that debug variables that are unused in the application are not
*              optimized away.  This function might not be necessary for all compilers.  In this case, you should simply
*              DELETE the code in this function while still leaving the declaration of the function itself.
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : (1) This code doesn't do anything, it simply prevents the compiler from optimizing out the 'const'
*                  variables which are declared in this file.
*              (2) You may decide to 'compile out' the code (by using #if 0/#endif) INSIDE the function if your compiler
*                  DOES NOT optimize out the 'const' variables above.
************************************************************************************************************************
*/

void  OS_Dbg_Init (void)
{
    void  const  *p_temp;


    p_temp = (void const *)&OSDbg_DbgEn;

    p_temp = (void const *)&OSDbg_DataSize;

    p_temp = (void const *)&OSDbg_ArgChkEn;
    p_temp = (void const *)&OSDbg_AppHooksEn;

    p_temp = (void const *)&OSDbg_EndiannessTest;

    p_temp = (void const *)&OSDbg_CalledFromISRChkEn;

    p_temp = (void const *)&OSDbg_FlagGrp;
    p_temp = (void const *)&OSDbg_FlagEn;
#if OS_CFG_FLAG_EN > 0u
    p_temp = (void const *)&OSDbg_FlagDelEn;
    p_temp = (void const *)&OSDbg_FlagModeClrEn;
    p_temp = (void const *)&OSDbg_FlagPendAbortEn;
    p_temp = (void const *)&OSDbg_FlagGrpSize;
    p_temp = (void const *)&OSDbg_FlagWidth;
#endif

#if OS_CFG_ISR_POST_DEFERRED_EN > 0u
    p_temp = (void const *)&OSDbg_IntQ;
#endif

    p_temp = (void const *)&OSDbg_Mem;
    p_temp = (void const *)&OSDbg_MemEn;
#if OS_CFG_MEM_EN > 0u
    p_temp = (void const *)&OSDbg_MemSize;
#endif

    p_temp = (void const *)&OSDbg_MsgEn;
    p_temp = (void const *)&OSDbg_Mutex;
    p_temp = (void const *)&OSDbg_MutexEn;
#if (OS_CFG_MUTEX_EN) > 0u
    p_temp = (void const *)&OSDbg_MutexDelEn;
    p_temp = (void const *)&OSDbg_MutexPendAbortEn;
    p_temp = (void const *)&OSDbg_MutexSize;
#endif

    p_temp = (void const *)&OSDbg_ObjTypeChkEn;

    p_temp = (void const *)&OSDbg_PrioMax;
    p_temp = (void const *)&OSDbg_PrioTblSize;

    p_temp = (void const *)&OSDbg_PtrSize;
#if OS_CFG_Q_EN > 0u
    p_temp = (void const *)&OSDbg_Q;
#endif
    p_temp = (void const *)&OSDbg_QEn;
#if (OS_CFG_Q_EN) > 0u
    p_temp = (void const *)&OSDbg_QDelEn;
    p_temp = (void const *)&OSDbg_QFlushEn;
    p_temp = (void const *)&OSDbg_QPendAbortEn;
    p_temp = (void const *)&OSDbg_QSize;
#endif

    p_temp = (void const *)&OSDbg_SchedRoundRobinEn;

    p_temp = (void const *)&OSDbg_Sem;
    p_temp = (void const *)&OSDbg_SemEn;
#if (OS_CFG_SEM_EN) > 0u
    p_temp = (void const *)&OSDbg_SemDelEn;
    p_temp = (void const *)&OSDbg_SemPendAbortEn;
    p_temp = (void const *)&OSDbg_SemSetEn;
    p_temp = (void const *)&OSDbg_SemSize;
#endif

    p_temp = (void const *)&OSDbg_StkWidth;

    p_temp = (void const *)&OSDbg_StatTaskEn;
    p_temp = (void const *)&OSDbg_StatTaskStkChkEn;

    p_temp = (void const *)&OSDbg_TaskChangePrioEn;
    p_temp = (void const *)&OSDbg_TaskDelEn;
    p_temp = (void const *)&OSDbg_TaskQEn;
    p_temp = (void const *)&OSDbg_TaskQPendAbortEn;
    p_temp = (void const *)&OSDbg_TaskProfileEn;
    p_temp = (void const *)&OSDbg_TaskRegTblSize;
    p_temp = (void const *)&OSDbg_TaskSemPendAbortEn;
    p_temp = (void const *)&OSDbg_TaskSuspendEn;

    p_temp = (void const *)&OSDbg_TCBSize;

    p_temp = (void const *)&OSDbg_TimeDlyHMSMEn;
    p_temp = (void const *)&OSDbg_TimeDlyResumeEn;


    p_temp = (void const *)&OSDbg_Tmr;
    p_temp = (void const *)&OSDbg_TmrEn;
#if (OS_CFG_TMR_EN) > 0u
    p_temp = (void const *)&OSDbg_TmrDelEn;
    p_temp = (void const *)&OSDbg_TmrSize;
#endif

    p_temp = (void const *)&OSDbg_VersionNbr;

    p_temp = p_temp;                                        /* Prevent compiler warning for not using 'p_temp'        */
}
#endif

#endif /*PKG_USING_UCOSIII_WRAPPER_TINY*/
