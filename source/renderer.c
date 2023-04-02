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
#define S3L_RESOLUTION_X SCR_W
#define S3L_RESOLUTION_Y SCR_H
#define S3L_PIXEL_FUNCTION S3L_Pixel
#define S3L_Z_BUFFER 1
#define S3L_NEAR_CROSS_STRATEGY 3
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
	platform_draw_pixel(pixel->x, pixel->y, RGB(255, 255, 255));
	
}

/*
 * renderer_init
 */

void renderer_init()
{
	/* variables */
	S3L_Vec4 origin;

	/* init origin */
	S3L_vec4Init(&origin);

	/* init scene */
	S3L_sceneInit(NULL, 0, &scene);

	/* init camera */
	scene.camera.focalLength = 0;
	S3L_lookAt(origin, &scene.camera.transform);
	scene.camera.transform.translation.z = -16 * S3L_F;
	scene.camera.transform.scale.x = S3L_F / 8;
	scene.camera.transform.scale.y = S3L_F / 8;
}

/*
 * renderer_frame_start
 */

void renderer_frame_start()
{
	/* variables */
	int dx, dy;

	/* clear zbuffer */
	S3L_newFrame();

	/* update camera */
	platform_mouse(NULL, NULL, &dx, &dy);

	scene.camera.transform.translation.x += dx * SENSITIVITY;
	scene.camera.transform.translation.y -= dy * SENSITIVITY;
}

/*
 * renderer_draw_square
 */

void renderer_draw_square(int x, int y, int w, int h)
{
	/* variables */
	S3L_Model3D model;
	S3L_Index triangles[6];
	S3L_Unit vertices[12];

	/* fixed */
	x *= S3L_F;
	y *= S3L_F;
	w *= S3L_F;
	h *= S3L_F;

	/* init vertices */
	vertices[0] = x - (w / 2);
	vertices[1] = y + (h / 2);
	vertices[2] = 0;

	vertices[3] = x + (w / 2);
	vertices[4] = y + (h / 2);
	vertices[5] = 0;

	vertices[6] = x + (w / 2);
	vertices[7] = y - (h / 2);
	vertices[8] = 0;

	vertices[9] = x - (w / 2);
	vertices[10] = y - (h / 2);
	vertices[11] = 0;

	/* init triangles */
	triangles[0] = 0;
	triangles[1] = 1;
	triangles[2] = 2;

	triangles[3] = 0;
	triangles[4] = 3;
	triangles[5] = 2;

	/* init model */
	S3L_model3DInit(vertices, 4, triangles, 2, &model);
	model.config.backfaceCulling = 0;

	/* set model */
	scene.models = &model;
	scene.modelCount = 1;

	/* draw */
	S3L_drawScene(scene);
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
