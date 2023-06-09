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
// world
//

// vec3 class
class Vec3
{
	public:
		int32_t x, y, z;

		// constructors
		Vec3(int32_t x, int32_t y, int32_t z);
		Vec3();
};

// triangle class
class Triangle
{
	public:

		// vertices that make up this triangle
		uint16_t indices[3];

		// constructors
		Triangle(uint16_t x, uint16_t y, uint16_t z);
		Triangle();
};

// vertex class
class Vertex
{
	public:

		// vertex coordinates
		// (512 fractions per unit)
		int32_t coordinates[3];

		// constructor
		Vertex(int32_t x, int32_t y, int32_t z);
};

// plane class
class Plane
{
	public:

		// the four vertices that make up this plane
		uint16_t vertex_indices[4];

		// the nodes that contains this plane
		uint16_t node_indices[2];

		// triangles contained in this plane
		uint16_t triangle_start_index;
		uint16_t triangle_end_index;
};

// node class
class Node
{
	public:

		// planes contained in this node
		uint16_t plane_start_index;
		uint16_t plane_end_index;

		// rendered flag
		bool rendered;
};

// level class
class Level
{
	public:

		// level buffers
		vector<Vertex> vertices;
		vector<Triangle> triangles;
		vector<Plane> planes;
		vector<Node> nodes;
};

// globals
extern Level world;

namespace World
{

// functions
bool Init();
void Quit();

} // namespace World
