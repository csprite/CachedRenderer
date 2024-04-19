#ifndef CRENDERER_RENDERER_H_INCLUDED_
#define CRENDERER_RENDERER_H_INCLUDED_ 1

#include <stdint.h>
#include "endian.h"

typedef struct {
#if defined(__LITTLE_ENDIAN__)
	uint8_t a, b, g, r;
#elif defined(__BIG_ENDIAN__)
	uint8_t r, g, b, a;
#else
	#error "Unknown Endian"
#endif
} sRGBA;

#define UINT32_TO_RGBA(val) (*((sRGBA*)&val))
#define RGBA_TO_UINT32(val) (*((uint32_t*)&val))

sRGBA BlendAlpha(sRGBA src, sRGBA backdrop, uint8_t opacity);

#endif // !CRENDERER_RENDERER_H_INCLUDED_

