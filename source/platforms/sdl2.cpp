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

// std
#include <iostream>
#include <stdint.h>

// sdl2
#include <SDL2/SDL.h>

// harvest engine
#include "harvest.hpp"

//
// macros
//

#define ASPECT1 (float)(SCR_W) / (float)(SCR_H)
#define ASPECT2 (float)(SCR_H) / (float)(SCR_W)

//
// globals
//

SDL_Window *window;
SDL_Texture *texture;
SDL_Renderer *renderer;
void *pixels;
bool should_quit;
int width;
int height;

struct mouse_t
{
	int x;		/* x pos */
	int y;		/* y pos */
	int dx;		/* delta x */
	int dy;		/* delta y */
	int b;		/* button mask */
} mouse;

bool keys[256];

//
// Platform_Init
//

bool Platform_Init()
{
	should_quit = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

//
// Platform_InitScreen
//

bool Platform_InitScreen(int w, int h, const char *title)
{
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_RESIZABLE
	);

	if (window == NULL) return false;

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC
	);

	if (renderer == NULL) return false;

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		w,
		h
	);

	if (texture == NULL) return false;

	pixels = malloc(w * h * sizeof(uint32_t));

	if (pixels == NULL) return false;

	width = w;
	height = h;

	return 1;
}

//
// Platform_Quit
//

void Platform_Quit()
{
	if (texture != NULL) SDL_DestroyTexture(texture);
	if (renderer != NULL) SDL_DestroyRenderer(renderer);
	if (window != NULL) SDL_DestroyWindow(window);
	if (pixels) free(pixels);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_Quit();
}

//
// Platform_ShouldQuit
//

bool Platform_ShouldQuit()
{
	return should_quit;
}

//
// Platform_StartFrame
//

void Platform_StartFrame()
{
	/* variables */
	SDL_Event event;

	/* event poll loop */
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				should_quit = true;
				break;

			case SDL_MOUSEMOTION:
				mouse.x = event.motion.x;
				mouse.y = event.motion.y;
				mouse.dx = event.motion.xrel;
				mouse.dy = event.motion.yrel;
				break;

			case SDL_KEYDOWN:
				keys[event.key.keysym.scancode] = true;
				break;

			case SDL_KEYUP:
				keys[event.key.keysym.scancode] = false;
				break;
		}
	}
}

//
// CalcScreenSize
//

void CalcScreenSize(int x, int y, SDL_Rect *rect)
{
	if (y < x && (y * ASPECT1) < x)
	{
		rect->w = y * ASPECT1;
		rect->h = y;
	}
	else if ((x / y) == ASPECT1)
	{
		rect->w = x;
		rect->h = y;
	}
	else
	{
		rect->w = x;
		rect->h = x * ASPECT2;
	}
}

//
// CalcScreenPos
//

void CalcScreenPos(int x, int y, SDL_Rect *rect)
{
	if (y < x && (y * ASPECT1) < x)
	{
		rect->x = (x / 2) - ((y * ASPECT1) / 2);
		rect->y = 0;
	}
	else if (x / y == ASPECT1)
	{
		rect->x = 0;
		rect->y = 0;
	}
	else
	{
		rect->x = 0;
		rect->y = (y / 2) - ((x * ASPECT2) / 2);
	}
}

//
// Platform_EndFrame
//

void Platform_EndFrame()
{
	int x, y;
	SDL_Rect rect;

	SDL_GetWindowSize(window, &x, &y);
	CalcScreenPos(x, y, &rect);
	CalcScreenSize(x, y, &rect);

	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);
}

//
// Platform_ClearScreen
//

void Platform_ClearScreen(uint32_t c)
{
	Memset32(pixels, c, width * height);
}

//
// Platform_KeyDown
//

bool Platform_KeyDown(int sc)
{
	return keys[sc];
}

//
// Platform_PlotPixel
//

void Platform_PlotPixel(uint32_t x, uint32_t y, uint32_t c)
{
	((uint32_t *)pixels)[(y * width) + x] = c;
}

//
// Platform_GetMouse
//

void Platform_GetMouse(int *x, int *y, int *dx, int *dy)
{
	if (x) *x = mouse.x;
	if (y) *y = mouse.y;
	if (dx) *dx = mouse.dx;
	if (dy) *dy = mouse.dy;

	mouse.dx = 0;
	mouse.dy = 0;
}
