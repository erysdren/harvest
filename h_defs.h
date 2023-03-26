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

#pragma once
#ifndef __HARVEST_H__
#define __HARVEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 * harvest engine
 *
 */

/*
 * types
 */

#if __SIZEOF_POINTER__ == 4

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#elif __SIZEOF_POINTER__ == 8

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#else

#error cant determine processor architechture, sorry

#endif

/*
 * macros
 */

/* rgb */
#define ARGB(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))
#define RGBA(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))

/* screen width */
#define SCR_W 640
#define SCR_H 480

/* title */
#define SCR_TITLE "Harvest Engine"

/* bpp */
#define SCR_BPP 32

/*
 * r_main.c
 */

void R_Render();
void R_Init();
void R_Quit();

/*
 * u_main.c
 */

void U_Error(const char *s);
void U_Warning(const char *s);

/*
 * u_mem.c
 */

void *U_Memset32(void *d, u32 c, size_t n);

/*
 * r_text.c
 */

extern u8 scratch[256];
void R_DrawTextF(int x, int y, u32 c, char *fmt, ...);

/*
 * w_main.c
 */

#define MAX_SECTOR 32
#define MAX_PORTAL 64
#define MAX_WALL 128

/* portal struct */
typedef struct portal_t
{
	short sectors[2];
} portal_t;

/* wall struct */
typedef struct wall_t
{
	short indices[4];
	short portal;
} wall_t;

/* only cubes for now */
typedef struct sector_t
{
	short walls[6];
} sector_t;

/* global stack buffers */
extern sector_t sectors[MAX_SECTOR];
extern u8 sectors_rendered[MAX_SECTOR];
extern portal_t portals[MAX_PORTAL];
extern wall_t walls[MAX_WALL];

void W_Init();

/*
 * p_sdl.c
 */

int P_Init();
int P_Open(int w, int h, const char *title);
void P_Quit();
int P_ShouldClose();
void P_StartFrame();
void P_EndFrame();
void P_ClearScreen(u32 c);
int P_KeyDown(int sc);
void P_Pixel(u32 x, u32 y, u32 c);
void P_GetMouse(int *x, int *y, int *dx, int *dy);

#ifdef __cplusplus
}
#endif

#endif /* __HARVEST_H__ */
