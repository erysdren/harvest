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
 * macros
 */

#define S3L_FRACTIONS_PER_UNIT 512
#define S3L_F S3L_FRACTIONS_PER_UNIT

#define S3L_logVec4(v) printf("Vec4: %d %d %d %d\n",((v).x),((v).y),((v).z),((v).w))

#define S3L_logTransform3D(t)\
  printf("Transform3D: T = [%d %d %d], R = [%d %d %d], S = [%d %d %d]\n",\
    (t).translation.x,(t).translation.y,(t).translation.z,\
    (t).rotation.x,(t).rotation.y,(t).rotation.z,\
    (t).scale.x,(t).scale.y,(t).scale.z)

#define S3L_logMat4(m)\
  printf("Mat4:\n  %d %d %d %d\n  %d %d %d %d\n  %d %d %d %d\n  %d %d %d %d\n"\
   ,(m)[0][0],(m)[1][0],(m)[2][0],(m)[3][0],\
    (m)[0][1],(m)[1][1],(m)[2][1],(m)[3][1],\
    (m)[0][2],(m)[1][2],(m)[2][2],(m)[3][2],\
    (m)[0][3],(m)[1][3],(m)[2][3],(m)[3][3])

/*
 * public functions
 */

S3L_Unit S3L_vec3Length(S3L_Vec4 v);
void S3L_vec3Normalize(S3L_Vec4 *v);
S3L_Unit S3L_vec2Length(S3L_Vec4 v);
void S3L_vec3Cross(S3L_Vec4 a, S3L_Vec4 b, S3L_Vec4 *result);
void S3L_reflect(S3L_Vec4 toLight, S3L_Vec4 normal, S3L_Vec4 *result);
void S3L_lookAt(S3L_Vec4 pointTo, S3L_Transform3D *t);
void S3L_transform3DSet(S3L_Unit tx, S3L_Unit ty, S3L_Unit tz, S3L_Unit rx, S3L_Unit ry, S3L_Unit rz, S3L_Unit sx, S3L_Unit sy, S3L_Unit sz, S3L_Transform3D *t);
void S3L_rotationToDirections(S3L_Vec4 rotation,S3L_Unit length, S3L_Vec4 *forw, S3L_Vec4 *right, S3L_Vec4 *up);
void S3L_mat4Copy(S3L_Mat4 src, S3L_Mat4 dst);
void S3L_mat4Transpose(S3L_Mat4 m);
void S3L_makeTranslationMat(S3L_Unit offsetX, S3L_Unit offsetY, S3L_Unit offsetZ, S3L_Mat4 m);
void S3L_makeScaleMatrix(S3L_Unit scaleX, S3L_Unit scaleY, S3L_Unit scaleZ, S3L_Mat4 m);
void S3L_makeRotationMatrixZXY(S3L_Unit byX, S3L_Unit byY, S3L_Unit byZ, S3L_Mat4 m);
void S3L_makeWorldMatrix(S3L_Transform3D worldTransform, S3L_Mat4 m);
void S3L_makeCameraMatrix(S3L_Transform3D cameraTransform, S3L_Mat4 m);
void S3L_vec4Xmat4(S3L_Vec4 *v, S3L_Mat4 m);
void S3L_vec3Xmat4(S3L_Vec4 *v, S3L_Mat4 m);
void S3L_mat4Xmat4(S3L_Mat4 m1, S3L_Mat4 m2);
void S3L_cameraInit(S3L_Camera *camera);
void S3L_drawConfigInit(S3L_DrawConfig *config);
void S3L_model3DInit(const S3L_Unit *vertices, S3L_Index vertexCount, const S3L_Index *triangles, S3L_Index triangleCount, S3L_Model3D *model);
void S3L_sceneInit(S3L_Model3D *models, S3L_Index modelCount, S3L_Scene *scene);
S3L_Unit S3L_sin(S3L_Unit x);
S3L_Unit S3L_asin(S3L_Unit x);
S3L_Unit S3L_sqrt(S3L_Unit value);
void S3L_project3DPointToScreen(S3L_Vec4 point, S3L_Camera camera, S3L_Vec4 *result);
void S3L_triangleNormal(S3L_Vec4 t0, S3L_Vec4 t1, S3L_Vec4 t2, S3L_Vec4 *n);
void S3L_getIndexedTriangleValues(S3L_Index triangleIndex, const S3L_Index *indices, const S3L_Unit *values, u8 numComponents, S3L_Vec4 *v0, S3L_Vec4 *v1, S3L_Vec4 *v2);
void S3L_computeModelNormals(S3L_Model3D model, S3L_Unit *dst, s8 transformNormals);
void S3L_drawTriangle(S3L_Vec4 point0, S3L_Vec4 point1, S3L_Vec4 point2, S3L_Index modelIndex, S3L_Index triangleIndex);
void S3L_newFrame(void);
void S3L_zBufferClear(void);
void S3L_stencilBufferClear(void);
void S3L_zBufferWrite(S3L_ScreenCoord x, S3L_ScreenCoord y, S3L_Unit value);
S3L_Unit S3L_zBufferRead(S3L_ScreenCoord x, S3L_ScreenCoord y);
