/*
    ChibiOS/GFX - Copyright (C) 2012, 2013
                 Joel Bodenmann aka Tectu <joel@unormal.org>

    This file is part of ChibiOS/GFX.

    ChibiOS/GFX is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/GFX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file    include/gos/win32.h
 * @brief   GOS - Operating System Support header file for WIN32.
 */

#ifndef _GOS_WIN32_H
#define _GOS_WIN32_H

#if GFX_USE_OS_WIN32

//#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/* Stop cygwin from defining these types */
#define __int8_t_defined

/**
 * size_t
 * TRUE, FALSE
 * are already defined by Win32
 */
typedef __int8				bool_t;
typedef __int8				int8_t;
typedef unsigned __int8		uint8_t;
typedef __int16				int16_t;
typedef unsigned __int16	uint16_t;
typedef __int32				int32_t;
typedef unsigned __int32	uint32_t;
typedef DWORD				delaytime_t;
typedef DWORD				systemticks_t;
typedef LONG				semcount_t;
typedef DWORD				threadreturn_t;
typedef int					threadpriority_t;

#define DECLARE_THREAD_FUNCTION(fnName, param)	threadreturn_t WINAPI fnName(void *param)
#define DECLARE_THREAD_STACK(name, sz)			uint8_t name[0];

#define TIME_IMMEDIATE				0
#define TIME_INFINITE				INFINITE
#define MAX_SEMAPHORE_COUNT			((semcount_t)(((unsigned long)((semcount_t)(-1))) >> 1))
#define LOW_PRIORITY				THREAD_PRIORITY_BELOW_NORMAL
#define NORMAL_PRIORITY				THREAD_PRIORITY_NORMAL
#define HIGH_PRIORITY				THREAD_PRIORITY_ABOVE_NORMAL

typedef HANDLE gfxSem;
typedef HANDLE gfxMutex;
typedef HANDLE gfxThreadHandle;

#define gfxExit()						ExitProcess(0)
#define gfxAlloc(sz)					malloc(sz)
#define gfxFree(ptr)					free(ptr)
#define gfxSleepMilliseconds(ms)		Sleep(ms)
#define gfxYield()						Sleep(0)
#define gfxSystemTicks()				GetTickCount()
#define gfxMillisecondsToTicks(ms)		(ms)
#define gfxMutexInit(pmutex)			*(pmutex) = CreateMutex(NULL, FALSE, NULL)
#define gfxMutexDestory(pmutex)			CloseHandle(*(pmutex))
#define gfxMutexEnter(pmutex) 			WaitForSingleObject(*(pmutex), INFINITE)
#define gfxMutexExit(pmutex)			ReleaseMutex(*(pmutex))
#define gfxSemInit(psem, val, limit)	*(psem) = CreateSemaphore(NULL, val, limit, NULL)
#define gfxSemDestory(psem)				CloseHandle(*(psem))
#define gfxSemSignal(psem)				ReleaseSemaphore(*(psem), 1, NULL)
#define gfxSemSignalI(psem)				ReleaseSemaphore(*(psem), 1, NULL)
#define gfxSemCounterI(psem)			gfxSemCounter(psem)
#define gfxThreadMe()					GetCurrentThread()
#define gfxThreadClose(thread)			CloseHandle(thread)

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void gfxHalt(const char *msg);
void gfxSleepMicroseconds(delaytime_t ms);
bool_t gfxSemWait(gfxSem *psem, delaytime_t ms);
semcount_t gfxSemCounter(gfxSem *pSem);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
gfxThreadHandle gfxThreadCreate(void *stackarea, size_t stacksz, threadpriority_t prio, DECLARE_THREAD_FUNCTION((*fn),p), void *param);
threadreturn_t gfxThreadWait(gfxThreadHandle thread);

#ifdef __cplusplus
}
#endif



#endif /* GFX_USE_OS_WIN32 */

#endif /* _GOS_WIN32_H */
