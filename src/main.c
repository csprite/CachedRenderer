#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
#include "stb_truetype/stb_truetype.h"
#include "miniwin/miniwin.h"

typedef struct {
	stbtt_fontinfo fInfo;
	uint8_t* ttfRawBin;
} CFont;

int LoadFont(CFont* font, const char* filePath);
void FreeFont(CFont* font);

int main(int argc, char** argv) {
	CFont font = {};
	if (LoadFont(&font, "data/fonts/NotoSansMono.ttf") != 0) {
		return 1;
	}

	struct MiniWin win;
	win.title = "CachedRenderer";
	win.width = 320;
	win.height = 240;

	mwin_init(&win);

	int bW = 0, bH = 0;
	uint8_t* bitMap = stbtt_GetCodepointBitmap(&font.fInfo, 0, stbtt_ScaleForPixelHeight(&font.fInfo, 150), 'A', &bW, &bH, NULL, NULL);

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

		for (uint32_t y = 0; y < bH; y++) {
			for (uint32_t x = 0; x < bW; x++) {
				sRGBA bCol = { 255, 255, 255, 255 };
				bCol.a = bitMap[(y * bW) + x];
				sRGBA out = BlendAlpha(bCol, UINT32_TO_RGBA(win.pixels[(y * win.width) + x]), 255);
				win.pixels[(y * win.width) + x] = RGBA_TO_UINT32(out);
			}
		}


		// for (unsigned int i = 0; i < win.width * win.height; i++) {
			// win.pixels[i] = rand();
		// }

		mwin_swap(&win);
	}

	stbtt_FreeBitmap(bitMap, NULL);

	mwin_destroy(&win);
	FreeFont(&font);
	return 0;
}

void FreeFont(CFont* font) {
	free(font->ttfRawBin);
}

int LoadFont(CFont* font, const char* filePath) {
	FILE* f = fopen(filePath, "rb");
	if (f == NULL) return 1;

	fseek(f, 0, SEEK_END);
	size_t fileSize = ftell(f);
	fseek(f, 0, SEEK_SET);

	font->ttfRawBin = malloc(fileSize);
	if (font->ttfRawBin == NULL) {
		fclose(f);
		return 1;
	}

	if (fread(font->ttfRawBin, fileSize, 1, f) != 1) {
		free(font->ttfRawBin);
		fclose(f);
		return 1;
	}

	if (stbtt_InitFont(&font->fInfo, font->ttfRawBin, stbtt_GetFontOffsetForIndex(font->ttfRawBin, 0)) == 0) {
		free(font->ttfRawBin);
		fclose(f);
		return 1;
	}

	fclose(f);

	return 0;
}


