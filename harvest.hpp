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

// std
#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
using namespace std;

//
// macros
//

// rgb
#define ARGB(r, g, b, a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))
#define RGBA(r, g, b, a) (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))

// screen
#define SCR_W 640
#define SCR_H 480
#define SCR_TITLE "Harvest Engine"
#define SCR_BPP 32

//
// utilities
//

// functions
void Error(const char *s);
void Warning(const char *s);
void *Memset8(void *d, uint8_t c, size_t n);
void *Memset16(void *d, uint16_t c, size_t n);
void *Memset32(void *d, uint32_t c, size_t n);

//
// renderer
//

// globals
extern char scratch[256];

// functions
void Renderer_DrawText(int x, int y, uint32_t c, const char *fmt, ...);
void Renderer_DrawScene();
bool Renderer_Init();
void Renderer_Quit();
void Renderer_Draw();

//
// platform
//

// functions
bool Platform_Init();
bool Platform_InitScreen(int w, int h, const char *title);
void Platform_Quit();
bool Platform_ShouldQuit();
void Platform_StartFrame();
void Platform_EndFrame();
void Platform_ClearScreen(uint32_t c);
bool Platform_KeyDown(int sc);
void Platform_PlotPixel(uint32_t x, uint32_t y, uint32_t c);
void Platform_GetMouse(int *x, int *y, int *dx, int *dy);

//
// world
//

// triangle class
class Triangle
{
	public:
		uint32_t x, y, z;

		Triangle(uint32_t x, uint32_t y, uint32_t z);
};

// vertex class
class Vertex
{
	public:
		int32_t x, y, z;

		Vertex(int32_t x, int32_t y, int32_t z);
};

// wall class
class Wall
{
	public:

		// vertex indices in the level mesh
		vector<uint16_t> indices;

		// sectors this wall is touching
		// if both are valid indices, it's a portal
		int16_t sectors[2];
};

// sector class
class Sector
{
	public:

		// wall indices in the global wall buffer
		vector<uint16_t> walls;
};

// globals
extern vector<Vertex> vertices;
extern vector<Triangle> triangles;
extern vector<Wall> walls;
extern vector<Sector> sectors;

// functions
bool World_Init();
