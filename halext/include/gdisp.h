/*
    ChibiOS/RT - Copyright (C) 2012
                 Joel Bodenmann aka Tectu <joel@unormal.org>

    This file is part of ChibiOS-LCD-Driver.

    ChibiOS-LCD-Driver is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS-LCD-Driver is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file    gdisp.h
 * @brief   GDISP Graphic Driver subsystem header file.
 *
 * @addtogroup GDISP
 * @{
 */
#ifndef _GDISP_H
#define _GDISP_H

#if HAL_USE_GDISP || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.														 */
/*===========================================================================*/

/**
 * @brief   Some basic colors
 */
#define White			HTML2COLOR(0xFFFFFF)
#define Black			HTML2COLOR(0x000000)
#define Gray			HTML2COLOR(0x808080)
#define Grey			Gray
#define Blue			HTML2COLOR(0x0000FF)
#define Red				HTML2COLOR(0xFF0000)
#define Fuchsia			HTML2COLOR(0xFF00FF)
#define Magenta			Fuchsia
#define Green			HTML2COLOR(0x008000)
#define Yellow			HTML2COLOR(0xFFFF00)
#define Aqua			HTML2COLOR(0x00FFFF)
#define Cyan			Aqua
#define Lime			HTML2COLOR(0x00FF00)
#define Maroon			HTML2COLOR(0x800000)
#define Navy			HTML2COLOR(0x000080)
#define Olive			HTML2COLOR(0x808000)
#define Purple			HTML2COLOR(0x800080)
#define Silver			HTML2COLOR(0xC0C0C0)
#define Teal			HTML2COLOR(0x008080)
#define Orange			HTML2COLOR(0xFFA500)
#define Pink			HTML2COLOR(0xFFC0CB)
#define SkyBlue			HTML2COLOR(0x87CEEB)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    GDISP more complex functionality to be compiled
 * @{
 */
	/**
	 * @brief   Should all operations be clipped to the screen and colors validated.
	 * @details	Defaults to TRUE.
	 * @note    If this is FALSE, any operations that extend beyond the
	 *          edge of the screen will have undefined results. Any
	 *			out-of-range colors will produce undefined results.
	 * @note	If defined then all low level and high level driver routines
	 *			must check the validity of inputs and do something sensible
	 *			if they are out of range. It doesn't have to be efficient,
	 *			just valid.
	 */
	#ifndef GDISP_NEED_VALIDATION
		#define GDISP_NEED_VALIDATION	TRUE
	#endif

	/**
	 * @brief   Are circle functions needed.
	 * @details	Defaults to TRUE
	 */
	#ifndef GDISP_NEED_CIRCLE
		#define GDISP_NEED_CIRCLE		TRUE
	#endif

	/**
	 * @brief   Are ellipse functions needed.
	 * @details	Defaults to TRUE
	 */
	#ifndef GDISP_NEED_ELLIPSE
		#define GDISP_NEED_ELLIPSE		TRUE
	#endif

	/**
	 * @brief   Are text functions needed.
	 * @details	Defaults to TRUE
	 */
	#ifndef GDISP_NEED_TEXT
		#define GDISP_NEED_TEXT			TRUE
	#endif

	/**
	 * @brief   Is scrolling needed.
	 * @details	Defaults to FALSE
	 */
	#ifndef GDISP_NEED_SCROLL
		#define GDISP_NEED_SCROLL		FALSE
	#endif

	/**
	 * @brief   Is the capability to read pixels back needed.
	 * @details	Defaults to FALSE
	 */
	#ifndef GDISP_NEED_PIXELREAD
		#define GDISP_NEED_PIXELREAD	FALSE
	#endif

	/**
	 * @brief   Control some aspect of the drivers operation.
	 * @details	Defaults to FALSE
	 */
	#ifndef GDISP_NEED_CONTROL
		#define GDISP_NEED_CONTROL		FALSE
	#endif

	/**
	 * @brief   Do the drawing functions need to be thread-safe.
	 * @details	Defaults to FALSE
	 * @note	Turning this on adds two context switches per transaction
	 *			so it can significantly slow graphics drawing.
	 */
	#ifndef GDISP_NEED_MULTITHREAD
		#define GDISP_NEED_MULTITHREAD	FALSE
	#endif
/** @} */

/*===========================================================================*/
/* Low Level Driver details and error checks.                                */
/*===========================================================================*/

/* Include the low level driver information */
#include "gdisp_lld.h"

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

/**
 * @brief   Type for the text justification.
 */
typedef enum justify {justifyLeft, justifyCenter, justifyRight} justify_t;
/**
 * @brief   Type for the font metric.
 */
typedef enum fontmetric {fontHeight, fontDescendersHeight, fontLineSpacing, fontCharPadding, fontMinWidth, fontMaxWidth} fontmetric_t;

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if GDISP_NEED_TEXT || defined(__DOXYGEN__)
/**
 * @brief   Predefined fonts.
 */
extern const struct font fontSmall;
extern const struct font fontSmallDouble;
extern const struct font fontSmallNarrow;
extern const struct font fontLarger;
extern const struct font fontLargerDouble;
extern const struct font fontLargerNarrow;
extern const struct font fontUI1;
extern const struct font fontUI1Double;
extern const struct font fontUI1Narrow;
extern const struct font fontUI2;
extern const struct font fontUI2Double;
extern const struct font fontUI2Narrow;
extern const struct font fontLargeNumbers;
extern const struct font fontLargeNumbersDouble;
extern const struct font fontLargeNumbersNarrow;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if GDISP_NEED_MULTITHREAD

	/* Base Functions */
	void gdispInit(GDISPDriver *gdisp);

	/* Drawing Functions */
	void gdispClear(color_t color);
	void gdispDrawPixel(coord_t x, coord_t y, color_t color);
	void gdispDrawLine(coord_t x0, coord_t y0, coord_t x1, coord_t y1, color_t color);
	void gdispFillArea(coord_t x, coord_t y, coord_t cx, coord_t cy, color_t color);
	void gdispBlitArea(coord_t x, coord_t y, coord_t cx, coord_t cy, pixel_t *buffer);

	/* Circle Functions */
	#if GDISP_NEED_CIRCLE
	void gdispDrawCircle(coord_t x, coord_t y, coord_t radius, color_t color);
	void gdispFillCircle(coord_t x, coord_t y, coord_t radius, color_t color);
	#endif
	
	/* Ellipse Functions */
	#if GDISP_NEED_ELLIPSE
	void gdispDrawEllipse(coord_t x, coord_t y, coord_t a, coord_t b, color_t color);
	void gdispFillEllipse(coord_t x, coord_t y, coord_t a, coord_t b, color_t color);
	#endif

	/* Basic Text Rendering Functions */
	#if GDISP_NEED_TEXT
	void gdispDrawChar(coord_t x, coord_t y, char c, font_t font, color_t color);
	void gdispFillChar(coord_t x, coord_t y, char c, font_t font, color_t color, color_t bgcolor);
	void gdispDrawString(coord_t x, coord_t y, const char *str, font_t font, color_t color);
	#endif
	
	/* Read a pixel Function */
	#if GDISP_NEED_PIXELREAD
	color_t gdispGetPixelColor(coord_t x, coord_t y);
	#endif

	/* Scrolling Function - clears the area scrolled out */
	#if GDISP_NEED_SCROLL
	void gdispVerticalScroll(coord_t x, coord_t y, coord_t cx, coord_t cy, int lines, color_t bgcolor);
	#endif

	/* Set driver specific control */
	#if GDISP_NEED_CONTROL
	void gdispControl(int what, void *value);
	#endif

#else

	/* The same as above but use the low level driver directly if no multi-thread support is needed */
	#define gdispInit(gdisp)									gdisp_lld_init()
	#define gdispClear(color)									gdisp_lld_clear(color)
	#define gdispDrawPixel(x, y, color)							gdisp_lld_drawpixel(x, y, color)
	#define gdispDrawLine(x0, y0, x1, y1, color)				gdisp_lld_drawline(x0, y0, x1, y1, color)
	#define gdispFillArea(x, y, cx, cy, color)					gdisp_lld_fillarea(x, y, cx, cy, color)
	#define gdispBlitArea(x, y, cx, cy, buffer)					gdisp_lld_blitarea(x, y, cx, cy, buffer)
	#define gdispDrawCircle(x, y, radius, color)				gdisp_lld_drawcircle(x, y, radius, color)
	#define gdispFillCircle(x, y, radius, color)				gdisp_lld_fillcircle(x, y, radius, color)
	#define gdispDrawEllipse(x, y, a, b, color)					gdisp_lld_drawellipse(x, y, a, b, color)
	#define gdispFillEllipse(x, y, a, b, color)					gdisp_lld_fillellipse(x, y, a, b, color)
	#define gdispDrawChar(x, y, c, font, color)					gdisp_lld_drawchar(x, y, c, font, color)
	#define gdispFillChar(x, y, c, font, color, bgcolor)		gdisp_lld_fillchar(x, y, c, font, color, bgcolor)
	#define gdispGetPixelColor(x, y)							gdisp_lld_getpixelcolor(x, y)
	#define gdispVerticalScroll(x, y, cx, cy, lines, bgcolor)	gdisp_lld_verticalscroll(x, y, cx, cy, lines, bgcolor)
	#define gdispControl(what, value)							gdisp_lld_control(what, value)

#endif

void gdispDrawBox(coord_t x, coord_t y, coord_t cx, coord_t cy, color_t color);

/* Extra Text Functions */
#if GDISP_NEED_TEXT
	void gdispDrawString(coord_t x, coord_t y, const char *str, font_t font, color_t color);
	void gdispFillString(coord_t x, coord_t y, const char *str, font_t font, color_t color, color_t bgcolor);
	void gdispFillStringBox(coord_t x, coord_t y, coord_t cx, coord_t cy, const char* str, font_t font, color_t color, color_t bgColor, justify_t justify);
	coord_t gdispGetFontMetric(font_t font, fontmetric_t metric);
	coord_t gdispGetCharWidth(char c, font_t font);
	coord_t gdispGetStringWidth(const char* str, font_t font);
#endif

/* Support routine for packed pixel formats */
#ifndef gdispPackPixels
	void gdispPackPixels(const pixel_t *buf, coord_t cx, coord_t x, coord_t y, color_t color);
#endif

/* Deprecated Routines (already!) */
#define gdispSetPowerMode(powerMode)			gdispControl(GDISP_CONTROL_POWER, (void *)(powerMode))
#define gdispSetOrientation(newOrientation)		gdispControl(GDISP_CONTROL_ORITENTATION, (void *)(newOrientation))

#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_GDISP */

#endif /* _GDISP_H */
/** @} */
