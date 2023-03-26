/*
ANTI-CAPITALIST SOFTWARE LICENSE (v 1.4)

Copyright © 2022-2023 Erysdren Media

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
 * types
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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

/*
 * dh_rend.c
 */

void renderer_renderscene();
void renderer_init();

/*
 * dh_util.c
 */

void error(const char *s);
void warn(const char *s);

/*
 * dh_mem.c
 */

void *memset32(void *d, u32 c, size_t n);

/*
 * platform
 */

int platform_init();
int platform_open(int w, int h, const char *title);
void platform_close();
int platform_should_close();
void platform_frame_start();
void platform_frame_end();
void platform_clear(u32 c);
int platform_key(int sc);
void platform_pixel(u32 x, u32 y, u32 c);
