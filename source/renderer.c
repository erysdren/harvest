/*
 * ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)
 *
 * Copyright © 2023 erysdren (it/they/she)
 *
 * This is anti-capitalist software, released for free use by individuals
 * and organizations that do not operate by capitalist principles.
 *
 * Permission is hereby granted, free of charge, to any person or
 * organization (the "User") obtaining a copy of this software and
 * associated documentation files (the "Software"), to use, copy, modify,
 * merge, distribute, and/or sell copies of the Software, subject to the
 * following conditions:
 *
 *   1. The above copyright notice and this permission notice shall be
 *   included in all copies or modified versions of the Software.
 *
 *   2. The User is one of the following:
 *     a. An individual person, laboring for themselves
 *     b. A non-profit organization
 *     c. An educational institution
 *     d. An organization that seeks shared profit for all of its members,
 *     and allows non-members to set the cost of their labor
 *
 *   3. If the User is an organization with owners, then all owners are
 *   workers and all workers are owners with equal equity and/or equal vote.
 *
 *   4. If the User is an organization, then the User is not law enforcement
 *   or military, or working for or under either.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT EXPRESS OR IMPLIED WARRANTY OF
 * ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 *
 * harvest engine
 *
 */

/*
 *
 * headers
 *
 */

/* harvest engine */
#include "harvest.h"

/* font8x8 */
#include "font8x8_basic.h"

/* drummyfish */
#define S3L_RESOLUTION_X 640
#define S3L_RESOLUTION_Y 480
#define S3L_PIXEL_FUNCTION S3L_Pixel
#define S3L_SORT 1
#define S3L_NEAR_CROSS_STRATEGY 1
#include "small3dlib.h"

/*
 *
 * globals
 *
 */

S3L_Scene scene;

/*
 *
 * functions
 *
 */

/*
 * S3L_Pixel
 */

static inline void S3L_Pixel(S3L_PixelInfo *pixel)
{
	platform_draw_pixel(pixel->x, pixel->y, RGB(
		(pixel->modelIndex + 1) * 16 + (pixel->triangleIndex + 1) * 16,
		(pixel->modelIndex + 1) * 16 + (pixel->triangleIndex + 1) * 16,
		(pixel->modelIndex + 1) * 16 + (pixel->triangleIndex + 1) * 16));
}

/*
 * renderer_draw_font8x8
 */

void renderer_draw_font8x8(int x, int y, uint32_t c, uint8_t *bitmap)
{
	/* variables */
	int xx, yy;

	/* plot loop */
	for (yy = 0; yy < 8; yy++)
	{
		for (xx = 0; xx < 8; xx++)
		{
			if (x + xx > SCR_W - 1 || y + yy > SCR_H - 1) return;

			if (bitmap[yy] & 1 << xx)
				platform_draw_pixel(x + xx, y + yy, c);
		}
	}
}

/*
 * renderer_draw_text
 */

void renderer_draw_text(int x, int y, uint32_t c, const char *fmt, ...)
{
	/* variables */
	int i, p, n;
	va_list va;

	/* process vargs */
	va_start(va, fmt);
	vsnprintf(scratch, sizeof(scratch), fmt, va);
	va_end(va);

	/* plot loop */
	p = 0;
	for (i = 0; i < strlen(scratch); i++)
	{
		/* check for newlines */
		if (scratch[i] == '\n')
		{
			y += 8;
			x -= (p + 1) * 8;
			p = 0;
			continue;
		}

		p++;

		n = scratch[i];
		renderer_draw_font8x8(x + (i * 8), y, c, font8x8_basic[n]);
	}
}
