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
 * headers
 */

/* sdl2 */
#include <SDL2/SDL.h>

/* harvest engine */
#include "harvest.h"

/*
 * macros
 */

#define ASPECT1 (float)(context.width) / (float)(context.height)
#define ASPECT2 (float)(context.height) / (float)(context.width)

/*
 * globals
 */

/* platform context */
struct
{

	/* variables */
	SDL_Window *window;
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	u8 running;
	u32 *pixels;
	int width;
	int height;

	struct
	{
		int x;		/* x pos */
		int y;		/* y pos */
		int dx;		/* delta x */
		int dy;		/* delta y */
		int b;		/* button mask */
	} mouse;

	/* keys */
	u8 keys[256];

} context;

/*
 * platform_init
 */

int platform_init(int w, int h, const char *title)
{
	/* init everything */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return SDL_FALSE;

	/* turn on relative mouse */
	SDL_SetRelativeMouseMode(SDL_TRUE);

	/* create window */
	context.window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_RESIZABLE
	);

	if (context.window == NULL) return SDL_FALSE;

	/* create screen renderer */
	context.renderer = SDL_CreateRenderer(
		context.window,
		-1,
		SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC
	);

	if (context.renderer == NULL) return SDL_FALSE;

	/* create screen texture */
	context.texture = SDL_CreateTexture(
		context.renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		w,
		h
	);

	if (context.texture == NULL) return SDL_FALSE;

	/* allocate pixels */
	context.pixels = (u32 *)malloc(w * h * sizeof(u32));
	if (context.pixels == NULL) return SDL_FALSE;

	/* set values */
	context.width = w;
	context.height = h;
	context.running = SDL_TRUE;

	/* return success */
	return SDL_TRUE;
}

/*
 * platform_quit
 */

void platform_quit()
{
	/* free memory */
	if (context.texture != NULL) SDL_DestroyTexture(context.texture);
	if (context.renderer != NULL) SDL_DestroyRenderer(context.renderer);
	if (context.window != NULL) SDL_DestroyWindow(context.window);
	if (context.pixels != NULL) free(context.pixels);

	/* sdl2 */
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_Quit();
}

/*
 * platform_running
 */

int platform_running()
{
	return context.running;
}

/*
 * platform_frame_start
 */

void platform_frame_start()
{
	/* variables */
	SDL_Event event;

	/* event poll loop */
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				context.running = SDL_FALSE;
				break;

			case SDL_MOUSEMOTION:
				context.mouse.x = event.motion.x;
				context.mouse.y = event.motion.y;
				context.mouse.dx = event.motion.xrel;
				context.mouse.dy = event.motion.yrel;
				break;

			case SDL_KEYDOWN:
				context.keys[event.key.keysym.scancode] = SDL_TRUE;
				break;

			case SDL_KEYUP:
				context.keys[event.key.keysym.scancode] = SDL_FALSE;
				break;
		}
	}
}

/*
 * calc_screen_size
 */

void calc_screen_size(int x, int y, SDL_Rect *rect)
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

/*
 * calc_screen_pos
 */

void calc_screen_pos(int x, int y, SDL_Rect *rect)
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

/*
 * platform_frame_end
 */

void platform_frame_end()
{
	int x, y;
	SDL_Rect rect;

	SDL_GetWindowSize(context.window, &x, &y);
	calc_screen_pos(x, y, &rect);
	calc_screen_size(x, y, &rect);

	SDL_UpdateTexture(context.texture, NULL, context.pixels, context.width * sizeof(u32));
	SDL_RenderClear(context.renderer);
	SDL_RenderCopy(context.renderer, context.texture, NULL, &rect);
	SDL_RenderPresent(context.renderer);
}

/*
 * platform_screen_clear
 */

void platform_screen_clear(u32 c)
{
	sys_memset32(context.pixels, c, context.width * context.height);
}

/*
 * platform_key
 */

int platform_key(int sc)
{
	return context.keys[sc];
}

/*
 * platform_draw_pixel
 */

void platform_draw_pixel(u16 x, u16 y, u32 c)
{
	context.pixels[(y * context.width) + x] = c;
}

/*
 * platform_mouse
 */

void platform_mouse(int *x, int *y, int *dx, int *dy)
{
	/* set ptrs */
	if (x) *x = context.mouse.x;
	if (y) *y = context.mouse.y;
	if (dx) *dx = context.mouse.dx;
	if (dy) *dy = context.mouse.dy;

	/* reset delta after each read? */
	context.mouse.dx = 0;
	context.mouse.dy = 0;
}
