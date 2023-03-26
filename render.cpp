//
// ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)
//
// Copyright © 2023 erysdren (it/they/she)
//
// This is anti-capitalist software, released for free use by individuals
// and organizations that do not operate by capitalist principles.
//
// Permission is hereby granted, free of charge, to any person or
// organization (the "User") obtaining a copy of this software and
// associated documentation files (the "Software"), to use, copy, modify,
// merge, distribute, and/or sell copies of the Software, subject to the
// following conditions:
//
//   1. The above copyright notice and this permission notice shall be
//   included in all copies or modified versions of the Software.
//
//   2. The User is one of the following:
//     a. An individual person, laboring for themselves
//     b. A non-profit organization
//     c. An educational institution
//     d. An organization that seeks shared profit for all of its members,
//     and allows non-members to set the cost of their labor
//
//   3. If the User is an organization with owners, then all owners are
//   workers and all workers are owners with equal equity and/or equal vote.
//
//   4. If the User is an organization, then the User is not law enforcement
//   or military, or working for or under either.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT EXPRESS OR IMPLIED WARRANTY OF
// ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

//
//
// harvest engine
//
//

//
// headers
//

// harvest engine
#include "harvest.hpp"

// font8x8
#include "thirdparty/font8x8_basic.h"

// small3dlib
#if SCR_W
#define S3L_RESOLUTION_X SCR_W
#else
#define S3L_RESOLUTION_X 320
#endif
#if SCR_H
#define S3L_RESOLUTION_Y SCR_H
#else
#define S3L_RESOLUTION_Y 200
#endif
#define S3L_PIXEL_FUNCTION S3L_Pixel
#define S3L_Z_BUFFER 1
#define S3L_NEAR_CROSS_STRATEGY 3
#include "thirdparty/small3dlib.h"

//
// globals
//

// stencil buffer
uint8_t *stencil;

// scratch buffer
char scratch[256];

// test box vertices
S3L_Unit box_vertices[] =
{
	-S3L_F*8, S3L_F*8, S3L_F*8,
	-S3L_F*8, -S3L_F*8, S3L_F*8,
	-S3L_F*8, S3L_F*8, -S3L_F*8,
	-S3L_F*8, -S3L_F*8, -S3L_F*8,

	S3L_F*8, -S3L_F*8, S3L_F*8,
	S3L_F*8, S3L_F*8, S3L_F*8,
	S3L_F*8, -S3L_F*8, -S3L_F*8,
	S3L_F*8, S3L_F*8, -S3L_F*8
};

// test box indices
S3L_Index box_indices[] =
{
	2, 1, 0,
	1, 2, 3,

	6, 5, 4,
	5, 6, 7,

	7, 0, 5,
	0, 7, 2,

	3, 4, 1,
	3, 6, 4
};

S3L_Model3D box_model;
S3L_Scene scene;

//
// Renderer_Init
//

bool Renderer_Init()
{
	S3L_model3DInit(box_vertices, 24, box_indices, 8, &box_model);
	S3L_sceneInit(&box_model, 1, &scene);
	scene.camera.transform.translation.z = -16 * S3L_F;
	scene.camera.transform.translation.y = S3L_F / 16;

	stencil = (uint8_t *)malloc(SCR_W * SCR_H * sizeof(uint8_t));

	return true;
}

//
// Renderer_Quit
//

void Renderer_Quit()
{
	if (stencil) free(stencil);
}

//
// Renderer_DrawScene
//

void Renderer_DrawScene()
{
	// variables
	int dx, dy;

	// get mouse
	Platform_GetMouse(NULL, NULL, &dx, &dy);

	// update camera
	scene.camera.transform.rotation.x -= dy;
	scene.camera.transform.rotation.y -= dx;

	// clamp camera pitch
	scene.camera.transform.rotation.x =
		S3L_clamp(scene.camera.transform.rotation.x, -128, 128);

	// clamp camera yaw
	if (scene.camera.transform.rotation.y < -256)
		scene.camera.transform.rotation.y += 512;
	if (scene.camera.transform.rotation.y > 256)
		scene.camera.transform.rotation.y -= 512;

	// render frame
	S3L_newFrame();
	S3L_drawScene(scene);
}

//
// Renderer_DrawSector
//

void Renderer_DrawSector(int sector_id)
{
	return;
}

//
// S3L_Pixel
//

void S3L_Pixel(S3L_PixelInfo *p)
{
	Platform_PlotPixel(p->x, p->y, ARGB(
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		255));
}

//
// Renderer_DrawFont8x8
//

void Renderer_DrawFont8x8(int x, int y, uint32_t c, unsigned char *bitmap)
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
				Platform_PlotPixel(x + xx, y + yy, c);
		}
	}
}

//
// Renderer_DrawText
//

void Renderer_DrawText(int x, int y, uint32_t c, const char *fmt, ...)
{
	/* variables */
	int i, p;
	va_list va;

	/* process vargs */
	va_start(va, fmt);
	vsnprintf(scratch, sizeof(scratch), fmt, va);
	va_end(va);

	/* plot loop */
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

		Renderer_DrawFont8x8(x + (i * 8), y, c, font8x8_basic[scratch[i]]);
	}
}
