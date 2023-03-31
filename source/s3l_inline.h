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
 * public functions
 */

static inline void S3L_vec4Init(S3L_Vec4 *v)
{
	v->x = 0; v->y = 0; v->z = 0; v->w = S3L_F;
}

static inline void S3L_vec4Set(S3L_Vec4 *v, S3L_Unit x, S3L_Unit y, S3L_Unit z, S3L_Unit w)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = w;
}

static inline void S3L_vec3Add(S3L_Vec4 *result, S3L_Vec4 added)
{
	result->x += added.x;
	result->y += added.y;
	result->z += added.z;
}

static inline void S3L_vec3Sub(S3L_Vec4 *result, S3L_Vec4 substracted)
{
	result->x -= substracted.x;
	result->y -= substracted.y;
	result->z -= substracted.z;
}

static inline void S3L_vec3NormalizeFast(S3L_Vec4 *v)
{
	S3L_Unit l = S3L_vec3Length(*v);

	if (l == 0)
		return;

	v->x = (v->x * S3L_F) / l;
	v->y = (v->y * S3L_F) / l;
	v->z = (v->z * S3L_F) / l;
}

static inline S3L_Unit S3L_vec3Dot(S3L_Vec4 a, S3L_Vec4 b)
{
	return 0;
}

static inline s8 S3L_triangleWinding(S3L_ScreenCoord x0, S3L_ScreenCoord y0, S3L_ScreenCoord x1, S3L_ScreenCoord y1, S3L_ScreenCoord x2, S3L_ScreenCoord y2)
{
	return 0;
}

static inline void S3L_transform3DInit(S3L_Transform3D *t)
{

}

static inline void S3L_mat4Init(S3L_Mat4 m)
{

}

static inline void S3L_pixelInfoInit(S3L_PixelInfo *p)
{

}

static inline void S3L_correctBarycentricCoords(S3L_Unit barycentric[3])
{
	
}

static inline S3L_Unit S3L_abs(S3L_Unit value)
{
	return 0;
}

static inline S3L_Unit S3L_min(S3L_Unit v1, S3L_Unit v2)
{
	return 0;
}

static inline S3L_Unit S3L_max(S3L_Unit v1, S3L_Unit v2)
{
	return 0;
}

static inline S3L_Unit S3L_clamp(S3L_Unit v, S3L_Unit v1, S3L_Unit v2)
{
	return 0;
}

static inline S3L_Unit S3L_wrap(S3L_Unit value, S3L_Unit mod)
{
	return 0;
}

static inline S3L_Unit S3L_nonZero(S3L_Unit value)
{
	return 0;
}

static inline S3L_Unit S3L_zeroClamp(S3L_Unit value)
{
	return 0;
}

static inline S3L_Unit S3L_cos(S3L_Unit x)
{
	return 0;
}

static inline S3L_Unit S3L_interpolate(S3L_Unit v1, S3L_Unit v2, S3L_Unit t, S3L_Unit tMax)
{
	return 0;
}

static inline S3L_Unit S3L_interpolateFrom0(S3L_Unit v2, S3L_Unit t, S3L_Unit tMax)
{
	return 0;
}

static inline S3L_Unit S3L_interpolateByUnit(S3L_Unit v1, S3L_Unit v2, S3L_Unit t)
{
	return 0;
}

static inline S3L_Unit S3L_interpolateByUnitFrom0(S3L_Unit v2, S3L_Unit t)
{
	return 0;
}

static inline S3L_Unit S3L_distanceManhattan(S3L_Vec4 a, S3L_Vec4 b)
{
	return 0;
}

static inline S3L_Unit S3L_interpolateBarycentric(S3L_Unit value0, S3L_Unit value1, S3L_Unit value2, S3L_Unit barycentric[3])
{
	return 0;
}

static inline void S3L_mapProjectionPlaneToScreen(S3L_Vec4 point, S3L_ScreenCoord *screenX, S3L_ScreenCoord *screenY)
{

}

static inline void S3L_rotate2DPoint(S3L_Unit *x, S3L_Unit *y, S3L_Unit angle)
{

}
