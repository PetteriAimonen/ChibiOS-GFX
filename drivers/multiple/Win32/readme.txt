To use this driver:

This driver is special in that it implements both the gdisp low level driver
and a touchscreen driver.

1. Add in your halconf.h:
	a) #define GFX_USE_GDISP			TRUE
	b) #define GFX_USE_GINPUT			TRUE
		#define GINPUT_USE_MOUSE		TRUE
	c) Any optional high level driver defines (see gdisp.h) eg: GDISP_NEED_MULTITHREAD
	d) All of the following (with appropriate values):
		#define GDISP_SCREEN_WIDTH	640
		#define GDISP_SCREEN_HEIGHT	480


2. To your makefile add the following lines:
	include $(GFXLIB)/gfx.mk
	include $(GFXLIB)/drivers/multiple/Win32/gdisp_lld.mk

3. Modify your makefile to add -lgdi32 to the DLIBS line. i.e.
	DLIBS = -lws2_32 -lgdi32

