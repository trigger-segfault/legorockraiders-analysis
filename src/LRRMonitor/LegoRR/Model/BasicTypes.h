#pragma once


#pragma pack(push, 1)

namespace lego {

#pragma region Colour

struct ColourRGBI
{
	/*0,4*/ unsigned int red;
	/*4,4*/ unsigned int green;
	/*8,4*/ unsigned int blue;
	/*c*/
};
static_assert(sizeof(ColourRGBI) == 0xc, "");

struct ColourRGBF
{
	/*0,4*/ float red;
	/*4,4*/ float green;
	/*8,4*/ float blue;
	/*c*/
};
static_assert(sizeof(ColourRGBF) == 0xc, "");

// (used as short hand for D3DRMIMAGE mask channels)
struct ColourRGBAI
{
	/*00,4*/ unsigned int red;
	/*04,4*/ unsigned int green;
	/*08,4*/ unsigned int blue;
	/*0c,4*/ unsigned int alpha;
	/*10*/
};
static_assert(sizeof(ColourRGBAI) == 0x10, "");

// never observed
struct ColourRGBAF
{
	/*00,4*/ float red;
	/*04,4*/ float green;
	/*08,4*/ float blue;
	/*0c,4*/ float alpha;
	/*10*/
};
static_assert(sizeof(ColourRGBAF) == 0x10, "");

struct ColourRGBPacked
{
	union {
		struct {
			/*0,1*/ unsigned char red;
			/*1,1*/ unsigned char green;
			/*2,1*/ unsigned char blue;
			/*3,1*/ unsigned char reserved;
			/*4*/
		};
		/*0,4*/ unsigned int rgbColor;
		/*4*/
	};
};
static_assert(sizeof(ColourRGBPacked) == 0x4, "");

struct ColourRGBAPacked
{
	union {
		struct {
			/*0,1*/ unsigned char red;
			/*1,1*/ unsigned char green;
			/*2,1*/ unsigned char blue;
			/*3,1*/ unsigned char alpha;
			/*4*/
		};
		/*0,4*/ unsigned int rgbaColor;
		/*4*/
	};
};
static_assert(sizeof(ColourRGBAPacked) == 0x4, "");

#pragma endregion


#pragma region Geometry

//struct RenderStateItem
//{
//	/*0,4*/ unsigned int value; // not guaranteed to be uint, sometimes signed int, sometimes BOOL, etc...
//	/*4,4*/ BOOL isUsed;
//	/*8*/
//};

//POINT
struct Point2I
{
	/*0,4*/ int x;
	/*4,4*/ int y;
	/*8*/
};
static_assert(sizeof(Point2I) == 0x8, "");

struct Point2F
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8*/
};
static_assert(sizeof(Point2F) == 0x8, "");

//TD3DVector
struct Vector3F
{
	/*0,4*/ float x;
	/*4,4*/ float y;
	/*8,4*/ float z;
	/*c*/
};
static_assert(sizeof(Vector3F) == 0xc, "");

//TD3DRMVector4D
struct Vector4F
{
	/*00,4*/ float x;
	/*04,4*/ float y;
	/*08,4*/ float z;
	/*0c,4*/ float w;
	/*10*/
};
static_assert(sizeof(Vector4F) == 0x10, "");

struct Size2I
{
	/*0,4*/ int width;
	/*4,4*/ int height;
	/*8*/
};
static_assert(sizeof(Size2I) == 0x8, "");

struct Size2F
{
	/*0,4*/ float width;
	/*4,4*/ float height;
	/*8*/
};
static_assert(sizeof(Size2F) == 0x8, "");

struct Rect2I
{
	union {
		struct {
			/*00,4*/ int x;
			/*04,4*/ int y;
			/*08,4*/ int width;
			/*0c,4*/ int height;
			/*10*/
		};
		struct {
			/*00,8*/ Point2I point;
			/*08,8*/ Size2I  size;
			/*10*/
		};
	};
};
static_assert(sizeof(Rect2I) == 0x10, "");

struct Rect2F
{
	union {
		struct {
			/*00,4*/ float x;
			/*04,4*/ float y;
			/*08,4*/ float width;
			/*0c,4*/ float height;
			/*10*/
		};
		struct {
			/*00,8*/ Point2F point;
			/*08,8*/ Size2F  size;
			/*10*/
		};
	};
};
static_assert(sizeof(Rect2F) == 0x10, "");

struct P1P2Rect2I
{
	union {
		struct {
			/*00,4*/ int x1;
			/*04,4*/ int y1;
			/*08,4*/ int x2;
			/*0c,4*/ int y2;
			/*10*/
		};
		struct {
			/*00,8*/ Point2I p1;
			/*08,8*/ Point2I p2;
			/*10*/
		};
	};
};
static_assert(sizeof(P1P2Rect2I) == 0x10, "");

struct P1P2Rect2F
{
	union {
		struct {
			/*00,4*/ float x1;
			/*04,4*/ float y1;
			/*08,4*/ float x2;
			/*0c,4*/ float y2;
			/*10*/
		};
		struct {
			/*00,8*/ Point2F p1;
			/*08,8*/ Point2F p2;
			/*10*/
		};
	};
};
static_assert(sizeof(P1P2Rect2F) == 0x10, "");

//RECT
struct LTRBRect2I
{
	/*00,4*/ int left;
	/*04,4*/ int top;
	/*08,4*/ int right;
	/*0c,4*/ int bottom;
	/*10*/
};
static_assert(sizeof(LTRBRect2I) == 0x10, "");

struct LTRBRect2F
{
	/*00,4*/ float left;
	/*04,4*/ float top;
	/*08,4*/ float right;
	/*0c,4*/ float bottom;
	/*10*/
};
static_assert(sizeof(LTRBRect2F) == 0x10, "");

#pragma endregion


#pragma region D3D Geometry

//TD3DRMMatrix4D
//struct Matrix4F
//{
//	/*00,40*/ float values[4][4];
//	/*40*/
//};
//TD3DRMMatrix4D
typedef float Matrix4F[4][4];
static_assert(sizeof(Matrix4F) == 0x40, "");

//TD3DRMQuaternion
struct Quaternion3F
{
	/*00,4*/ float s;
	/*04,c*/ Vector3F v;
	/*10*/
};
static_assert(sizeof(Quaternion3F) == 0x10, "");

//TD3DRMRay
struct Ray3F
{
	/*00,c*/ Vector3F dir;
	/*0c,c*/ Vector3F pos;
	/*18*/
};
static_assert(sizeof(Ray3F) == 0x18, "");

//TD3DRMBox
struct Box3F
{
	/*00,c*/ Vector3F min;
	/*0c,c*/ Vector3F max;
	/*18*/
};
static_assert(sizeof(Box3F) == 0x18, "");

//TD3DHVertex
struct D3DHVertex
{
	/*00,4*/ unsigned int dwFlags; // Homogeneous clipping flags
	/*04,4*/ float hx;
	/*08,4*/ float hy;
	/*0c,4*/ float hz;
	/*10*/
};
static_assert(sizeof(D3DHVertex) == 0x10, "");

//TD3DTLVertex
struct D3DTLVertex
{
	/*00,4*/ float sx; // Screen coordinates
	/*04,4*/ float sy;
	/*08,4*/ float sz;
	/*0c,4*/ float rhw; // Reciprocal of homogeneous w
	/*10*/
};
static_assert(sizeof(D3DTLVertex) == 0x10, "");

#pragma endregion

}
#pragma pack(pop)

