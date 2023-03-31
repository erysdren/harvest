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

Level world;

//
// Vec3 class
//

// constructor
Vec3::Vec3(int32_t x, int32_t y, int32_t z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

// constructor
Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

//
// Triangle class
//

// constructor
Triangle::Triangle(uint16_t x, uint16_t y, uint16_t z)
{
	this->indices[0] = x;
	this->indices[1] = y;
	this->indices[2] = z;
}

// constructor
Triangle::Triangle()
{
	this->indices[0] = 0;
	this->indices[1] = 0;
	this->indices[2] = 0;
}

//
// Vertex class
//

Vertex::Vertex(int32_t x, int32_t y, int32_t z)
{
	this->coordinates[0] = x * FRAC;
	this->coordinates[1] = y * FRAC;
	this->coordinates[2] = z * FRAC;
}

namespace World
{

//
// Init
//

bool Init()
{
	// variables
	Node node;
	Plane p1, p2, p3, p4;

	// box vertices
	world.vertices.push_back(Vertex(-8, 8, 8));
	world.vertices.push_back(Vertex(-8, -8, 8));
	world.vertices.push_back(Vertex(-8, 8, -8));
	world.vertices.push_back(Vertex(-8, -8, -8));
	world.vertices.push_back(Vertex(8, -8, 8));
	world.vertices.push_back(Vertex(8, 8, 8));
	world.vertices.push_back(Vertex(8, -8, -8));
	world.vertices.push_back(Vertex(8, 8, -8));

	// box triangles
	world.triangles.push_back(Triangle(2, 1, 0));
	world.triangles.push_back(Triangle(1, 2, 3));
	world.triangles.push_back(Triangle(6, 5, 4));
	world.triangles.push_back(Triangle(5, 6, 7));
	world.triangles.push_back(Triangle(7, 0, 5));
	world.triangles.push_back(Triangle(0, 7, 2));
	world.triangles.push_back(Triangle(3, 4, 1));
	world.triangles.push_back(Triangle(3, 6, 4));

	// planes
	p1.triangle_start_index = 0;
	p1.triangle_end_index = 2;

	p2.triangle_start_index = 2;
	p2.triangle_end_index = 4;

	p3.triangle_start_index = 4;
	p3.triangle_end_index = 6;

	p4.triangle_start_index = 6;
	p4.triangle_end_index = 8;

	world.planes.push_back(p1);
	world.planes.push_back(p2);
	world.planes.push_back(p3);
	world.planes.push_back(p4);

	// node
	node.plane_start_index = 0;
	node.plane_end_index = 4;
	world.nodes.push_back(node);

	// return true
	return true;
}

//
// Quit
//

void Quit()
{

}

} // namespace World
