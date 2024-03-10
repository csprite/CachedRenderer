#include <stdlib.h>
#include "miniwin/miniwin.h"

int main(int argc, char** argv) {
	struct MiniWin win;
	win.title = "CachedRenderer";
	win.width = 320;
	win.height = 240;

	mwin_init(&win);

	int isRunning = 1;
	while (isRunning) {
		MW_Event ev;
		while (mwin_poll(&win, &ev)) {
			switch (ev.type) {
				case MW_EVENT_WINDOW_CLOSE: {
					isRunning = 0;
					break;
				}
				default: break;
			}
		}

		for (unsigned int i = 0; i < win.width * win.height; i++) {
			win.pixels[i] = rand();
		}

		mwin_swap(&win);
	}

	mwin_destroy(&win);
	return 0;
}

