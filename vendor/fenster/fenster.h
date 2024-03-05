#ifndef FENSTER_H
#define FENSTER_H

#if defined(__APPLE__)
	#include <CoreGraphics/CoreGraphics.h>
	#include <objc/NSObjCRuntime.h>
	#include <objc/objc-runtime.h>
#elif defined(_WIN32)
	#include <windows.h>
#else
	#define _DEFAULT_SOURCE 1
	#include <X11/XKBlib.h>
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
#endif

#include <stdint.h>

struct fenster {
	const char* title;
	const int width;
	const int height;
	uint32_t* buf;
	int keys[256]; // keys are mostly ASCII, but arrows are 17..20
	int mod;       // mod is 4 bits mask, ctrl=1, shift=2, alt=4, meta=8
	int x;
	int y;
	int mouse;
#if defined(__APPLE__)
	id wnd;
#elif defined(_WIN32)
	HWND hwnd;
#else
	Display *dpy;
	Window w;
	GC gc;
	XImage *img;
#endif
};

#ifndef FENSTER_API
	#define FENSTER_API extern
#endif

FENSTER_API int fenster_open(struct fenster *f);
FENSTER_API int fenster_loop(struct fenster *f);
FENSTER_API void fenster_close(struct fenster *f);
FENSTER_API void fenster_sleep(int64_t ms);
FENSTER_API int64_t fenster_time(void);
#define fenster_pixel(f, x, y) ((f)->buf[((y) * (f)->width) + (x)])

#endif /* FENSTER_H */

