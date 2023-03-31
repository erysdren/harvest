
typedef int32_t S3L_Unit;
typedef int16_t S3L_ScreenCoord;
typedef uint16_t S3L_Index;

typedef struct
{
	S3L_Unit x;
	S3L_Unit y;
	S3L_Unit z;
	S3L_Unit w;
} S3L_Vec4;

typedef struct
{
	S3L_Vec4 translation;
	S3L_Vec4 rotation;
	S3L_Vec4 scale;
} S3L_Transform3D;

typedef S3L_Unit S3L_Mat4[4][4]; 

typedef struct
{
	S3L_Unit focalLength;
	S3L_Transform3D transform;
} S3L_Camera;

typedef struct
{
	uint8_t backfaceCulling;
	int8_t visible;
} S3L_DrawConfig;

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

typedef struct
{
	S3L_Model3D *models;
	S3L_Index modelCount;
	S3L_Camera camera;
} S3L_Scene;

typedef struct
{
	S3L_ScreenCoord x;
	S3L_ScreenCoord y;
	S3L_Unit barycentric[3];
	S3L_Index modelIndex;
	S3L_Index triangleIndex;
	uint32_t triangleID;
	S3L_Unit depth;
	S3L_Unit previousZ;
	S3L_ScreenCoord triangleSize[2];
} S3L_PixelInfo;

typedef struct
{
	S3L_Unit valueScaled;
	S3L_Unit stepScaled;
} S3L_FastLerpState;
