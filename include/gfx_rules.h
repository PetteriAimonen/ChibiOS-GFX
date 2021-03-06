/*
 * This file is subject to the terms of the GFX License, v1.0. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://chibios-gfx.com/license.html
 */

/**
 * @file    include/gfx_rules.h
 * @brief   GFX system safety rules header file.
 *
 * @addtogroup GFX
 * @{
 */

#ifndef _GFX_RULES_H
#define _GFX_RULES_H

/**
 * Safety checks on all the defines.
 *
 * These are defined in the order of their inter-dependancies.
 */

#ifndef GFX_DISPLAY_RULE_WARNINGS
	#define GFX_DISPLAY_RULE_WARNINGS	FALSE
#endif

#if !GFX_USE_OS_CHIBIOS && !GFX_USE_OS_WIN32 && !GFX_USE_OS_POSIX
	#if GFX_DISPLAY_RULE_WARNINGS
		#warning "GOS: No Operating System has been defined. ChibiOS (GFX_USE_OS_CHIBIOS) has been turned on for you."
	#endif
	#undef GFX_USE_OS_CHIBIOS
	#define GFX_USE_OS_CHIBIOS	TRUE
#endif
#if GFX_USE_OS_CHIBIOS + GFX_USE_OS_WIN32 + GFX_USE_OS_POSIX != 1 * TRUE
	#error "GOS: More than one operation system has been defined as TRUE."
#endif

#if GFX_USE_GWIN
	#if !GFX_USE_GDISP
		#error "GWIN: GFX_USE_GDISP must be TRUE when using GWIN"
	#endif
	#if !GDISP_NEED_CLIP
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GWIN: Drawing can occur outside the defined windows as GDISP_NEED_CLIP is FALSE"
		#endif
	#endif
	#if GWIN_NEED_BUTTON
		#if !GDISP_NEED_TEXT
			#error "GWIN: GDISP_NEED_TEXT is required if GWIN_NEED_BUTTON is TRUE."
		#endif
		#if !GFX_USE_GEVENT
			#if GFX_DISPLAY_RULE_WARNINGS
				#warning "GWIN: GFX_USE_GEVENT is required if GWIN_NEED_BUTTON is TRUE. It has been turned on for you."
			#endif
			#undef GFX_USE_GEVENT
			#define GFX_USE_GEVENT	TRUE
		#endif
		#if !GFX_USE_GINPUT || !(GINPUT_NEED_MOUSE || GINPUT_NEED_TOGGLE)
			#if GFX_DISPLAY_RULE_WARNINGS
				#warning "GWIN: You have set GWIN_NEED_BUTTON to TRUE but no supported GINPUT (mouse/toggle) devices have been included"
			#endif
		#endif
		#if !GDISP_NEED_MULTITHREAD && !GDISP_NEED_ASYNC
			#if GFX_DISPLAY_RULE_WARNINGS
				#warning "GWIN: Either GDISP_NEED_MULTITHREAD or GDISP_NEED_ASYNC is required if GWIN_NEED_BUTTON is TRUE."
				#warning "GWIN: GDISP_NEED_MULTITHREAD has been turned on for you."
			#endif
			#undef GDISP_NEED_MULTITHREAD
			#define GDISP_NEED_MULTITHREAD	TRUE
		#endif
	#endif
	#if GWIN_NEED_CONSOLE
		#if !GDISP_NEED_TEXT
			#error "GWIN: GDISP_NEED_TEXT is required if GWIN_NEED_CONSOLE is TRUE."
		#endif
	#endif
	#if GWIN_NEED_GRAPH
	#endif
#endif

#if GFX_USE_GINPUT
	#if !GFX_USE_GEVENT
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GINPUT: GFX_USE_GEVENT is required if GFX_USE_GINPUT is TRUE. It has been turned on for you."
		#endif
		#undef GFX_USE_GEVENT
		#define	GFX_USE_GEVENT		TRUE
	#endif
	#if !GFX_USE_GTIMER
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GINPUT: GFX_USE_GTIMER is required if GFX_USE_GINPUT is TRUE. It has been turned on for you."
		#endif
		#undef GFX_USE_GTIMER
		#define	GFX_USE_GTIMER		TRUE
	#endif
#endif

#if GFX_USE_GDISP
	#if GDISP_NEED_MULTITHREAD && GDISP_NEED_ASYNC
		#error "GDISP: Only one of GDISP_NEED_MULTITHREAD and GDISP_NEED_ASYNC should be defined."
	#endif
	#if GDISP_NEED_ASYNC && !(GFX_USE_GQUEUE && GQUEUE_NEED_GSYNC)
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GDISP: GFX_USE_GQUEUE or GQUEUE_NEED_GSYNC is not TRUE. It has been turned on for you."
		#endif
		#undef GFX_USE_GQUEUE
		#define	GFX_USE_GQUEUE		TRUE
		#undef GQUEUE_NEED_GSYNC
		#define	GQUEUE_NEED_GSYNC	TRUE
	#endif
#endif

#if GFX_USE_TDISP
#endif

#if GFX_USE_GAUDIN
	#if GFX_USE_GEVENT && !GFX_USE_GTIMER
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GAUDIN: GFX_USE_GTIMER is required if GFX_USE_GAUDIN and GFX_USE_GEVENT are TRUE. It has been turned on for you."
		#endif
		#undef GFX_USE_GTIMER
		#define	GFX_USE_GTIMER		TRUE
	#endif
#endif

#if GFX_USE_GADC
	#if !GFX_USE_GTIMER
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GADC: GFX_USE_GTIMER is required if GFX_USE_GADC is TRUE. It has been turned on for you."
		#endif
		#undef GFX_USE_GTIMER
		#define	GFX_USE_GTIMER		TRUE
	#endif
#endif

#if GFX_USE_GEVENT
#endif

#if GFX_USE_GTIMER
	#if GFX_USE_GDISP && !GDISP_NEED_MULTITHREAD && !GDISP_NEED_ASYNC
		#if GFX_DISPLAY_RULE_WARNINGS
			#warning "GTIMER: Neither GDISP_NEED_MULTITHREAD nor GDISP_NEED_ASYNC has been specified."
			#warning "GTIMER: Make sure you are not performing any GDISP/GWIN drawing operations in the timer callback!"
		#endif
	#endif
#endif

#if GFX_USE_GAUDOUT
#endif

#if GFX_USE_GQUEUE
#endif

#if GFX_USE_GMISC
#endif

#endif /* _GFX_H */
/** @} */
