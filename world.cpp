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

// fractions per unit - S3L
#define FRAC 512

//
// globals
//

vector<Vertex> vertices;
vector<Triangle> triangles;
vector<Wall> walls;
vector<Sector> sectors;

//
// Triangle class
//

Triangle::Triangle(uint32_t x, uint32_t y, uint32_t z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//
// Vertex class
//

Vertex::Vertex(int32_t x, int32_t y, int32_t z)
{
	this->x = x * FRAC;
	this->y = y * FRAC;
	this->z = z * FRAC;
}

//
// World_Init
//

bool World_Init()
{
	// box vertices
	vertices.push_back(Vertex(-8, 8, 8));
	vertices.push_back(Vertex(-8, -8, 8));
	vertices.push_back(Vertex(-8, 8, -8));
	vertices.push_back(Vertex(-8, -8, -8));
	vertices.push_back(Vertex(8, -8, 8));
	vertices.push_back(Vertex(-8, 8, 8));
	vertices.push_back(Vertex(8, -8, -8));
	vertices.push_back(Vertex(8, 8, -8));

	// box triangles
	triangles.push_back(Triangle(2, 1, 0));
	triangles.push_back(Triangle(1, 2, 3));
	triangles.push_back(Triangle(6, 5, 4));
	triangles.push_back(Triangle(5, 6, 7));
	triangles.push_back(Triangle(7, 0, 5));
	triangles.push_back(Triangle(0, 7, 2));
	triangles.push_back(Triangle(3, 4, 1));
	triangles.push_back(Triangle(3, 6, 4));

	return true;
}
