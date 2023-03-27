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

// harvest engine
#include "harvest.hpp"

//
// main
//

int main(int argc, char **argv)
{
	// init
	if (!Platform_Init()) Error("failed to init platform");
	if (!World_Init()) Error("failed to init world");
	if (!Renderer_Init()) Error("failed to init renderer");
	if (!Platform_InitScreen(SCR_W, SCR_H, SCR_TITLE)) Error("failed to init platform screen");

	// main loop
	while (!Platform_ShouldQuit())
	{
		// poll events
		Platform_StartFrame();

		// clear screen
		Platform_ClearScreen(ARGB(0, 0, 0, 0));

		// render 3d scene
		Renderer_Draw();

		// draw some text
		Renderer_DrawText(4, 4, ARGB(255, 255, 255, 255), "hello world!");

		// put frame to screen
		Platform_EndFrame();
	}

	// quit
	Renderer_Quit();
	Platform_Quit();

	// exit gracefully
	return 0;
}
