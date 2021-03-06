/*
 * This file is subject to the terms of the GFX License, v1.0. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://chibios-gfx.com/license.html
 */

/**
 * @file    drivers/gdisp/Nokia6610GE12/gdisp_lld_config.h
 * @brief   GDISP Graphic Driver subsystem low level driver header for the Nokia6610 GE12 display.
 *
 * @addtogroup GDISP
 * @{
 */

#ifndef _GDISP_LLD_CONFIG_H
#define _GDISP_LLD_CONFIG_H

#if GFX_USE_GDISP 

/*===========================================================================*/
/* Driver hardware support.                                                  */
/*===========================================================================*/

#define GDISP_DRIVER_NAME				"Nokia6610GE12"

#define GDISP_HARDWARE_FILLS			TRUE
#define GDISP_HARDWARE_BITFILLS			TRUE
#define GDISP_HARDWARE_CONTROL			TRUE

#define GDISP_SOFTWARE_TEXTFILLDRAW		FALSE
#define GDISP_SOFTWARE_TEXTBLITCOLUMN	FALSE

#define GDISP_PIXELFORMAT				GDISP_PIXELFORMAT_RGB444
/* This driver supports both packed and unpacked pixel formats and line formats.
 * 	By default we leave these as FALSE.
 */
#define GDISP_PACKED_PIXELS				FALSE
#define GDISP_PACKED_LINES				FALSE

#endif	/* GFX_USE_GDISP */

#endif	/* _GDISP_LLD_CONFIG_H */
/** @} */
