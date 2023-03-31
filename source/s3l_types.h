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
 * types
 */

/* root types */
typedef s32 S3L_Unit;
typedef s16 S3L_ScreenCoord;
typedef u16 S3L_Index;

/* vec4 */
typedef struct
{
	S3L_Unit x;
	S3L_Unit y;
	S3L_Unit z;
	S3L_Unit w;
} S3L_Vec4;

/* 3d transform matrix */
typedef struct
{
	S3L_Vec4 translation;
	S3L_Vec4 rotation;
	S3L_Vec4 scale;
} S3L_Transform3D;

/* 4x4 matrix */
typedef S3L_Unit S3L_Mat4[4][4]; 

/* camera */
typedef struct
{
	S3L_Unit focalLength;
	S3L_Transform3D transform;
} S3L_Camera;

/* draw config for a model */
typedef struct
{
	u8 backfaceCulling;
	s8 visible;
} S3L_DrawConfig;

/* 3d model */
typedef struct
{
	const S3L_Unit *vertices;
	S3L_Index vertexCount;
	const S3L_Index *triangles;
	S3L_Index triangleCount;
	S3L_Transform3D transform;
	S3L_Mat4 *customTransformMatrix;
	S3L_DrawConfig config;
} S3L_Model3D;

/* 3d scene */
typedef struct
{
	S3L_Model3D *models;
	S3L_Index modelCount;
	S3L_Camera camera;
} S3L_Scene;

/* pixel info */
typedef struct
{
	S3L_ScreenCoord x;
	S3L_ScreenCoord y;
	S3L_Unit barycentric[3];
	S3L_Index modelIndex;
	S3L_Index triangleIndex;
	u32 triangleID;
	S3L_Unit depth;
	S3L_Unit previousZ;
	S3L_ScreenCoord triangleSize[2];
} S3L_PixelInfo;

/* fast lerp state */
typedef struct
{
	S3L_Unit valueScaled;
	S3L_Unit stepScaled;
} S3L_FastLerpState;
