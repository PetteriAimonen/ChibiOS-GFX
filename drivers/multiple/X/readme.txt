To use this driver:

This driver is special in that it implements both the gdisp low level driver
and a touchscreen driver.

1. Add in your gfxconf.h:
	a) #define GFX_USE_GDISP			TRUE
	b) #define GFX_USE_GINPUT			TRUE
		#define GINPUT_USE_MOUSE		TRUE
	c) Any optional high level driver defines (see gdisp.h) eg: GDISP_NEED_MULTITHREAD
	d) Optionally the following (with appropriate values):
		#define GDISP_SCREEN_WIDTH	640
		#define GDISP_SCREEN_HEIGHT	480
	e) Optionally change the threading model to POSIX (instead of ChibiOS)
		#define GDISP_THREAD_CHIBIOS	FALSE

2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/multiple/X/gdisp_lld.mk

3. Modify your makefile to add -lX11 to the DLIBS line. i.e.
	DLIBS = -lX11

3. If you changed your threading model to POSIX modify your makefile
		to add -pthread to the CC (or DDEFS) line. i.e.
	CC = $(TRGT)gcc -pthread

