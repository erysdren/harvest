/*
ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)

Copyright © 2022-2023 erysdren (it/they/she)

This is anti-capitalist software, released for free use by individuals
and organizations that do not operate by capitalist principles.

Permission is hereby granted, free of charge, to any person or
organization (the "User") obtaining a copy of this software and
associated documentation files (the "Software"), to use, copy, modify,
merge, distribute, and/or sell copies of the Software, subject to the
following conditions:

  1. The above copyright notice and this permission notice shall be
  included in all copies or modified versions of the Software.

  2. The User is one of the following:
    a. An individual person, laboring for themselves
    b. A non-profit organization
    c. An educational institution
    d. An organization that seeks shared profit for all of its members,
    and allows non-members to set the cost of their labor

  3. If the User is an organization with owners, then all owners are
  workers and all workers are owners with equal equity and/or equal vote.

  4. If the User is an organization, then the User is not law enforcement
  or military, or working for or under either.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT EXPRESS OR IMPLIED WARRANTY OF
ANY KIND, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
 *
 * harvest engine
 *
 */

/*
 * headers
 */

/* std */
#include <stdio.h>
#include <stdlib.h>

/* harvest engine */
#include "h_defs.h"

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

#define S3L_PIXEL_FUNCTION _pixel

/* tinyfish */
#include "small3dlib.h"

/*
 * globals
 */

/* test box vertices */
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

/* test box indices */
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

/*
 * renderer_init
 */

void renderer_init()
{
	S3L_model3DInit(box_vertices, 24, box_indices, 8, &box_model);
	S3L_sceneInit(&box_model, 1, &scene);
	scene.camera.transform.translation.z = -16 * S3L_F;
	scene.camera.transform.translation.y = S3L_F / 16;
}

/*
 * renderer_renderscene
 */

void renderer_renderscene()
{
	S3L_newFrame();
	S3L_drawScene(scene);
}

/*
 * _pixel
 */

void _pixel(S3L_PixelInfo *p)
{
	platform_pixel(p->x, p->y, ARGB(
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		(p->modelIndex + 1) * 16 + (p->triangleIndex + 1) * 16,
		255));
}
