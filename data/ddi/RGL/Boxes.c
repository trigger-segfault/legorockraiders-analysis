
#include "Standard.h"
#include "Viewports.h"
#include "Frames.h"
#include "Errors.h"
#include "Maths.h"
#include "Utils.h"
#include "Draw.h"
#include "Boxes.h"

struct boxGlobs {

	lpViewport vp;

} boxGlobs = { 0 };

__inline BOOL Box_LineIntersection(LPBOX3D box, LPVECTOR3D start, LPVECTOR3D end) {

	VECTOR3D hit;

	if (Box_ThroughSideX(box->min.x, start, end, &hit.y, &hit.z)){
		if (hit.y >= box->min.y && hit.y <= box->max.y && hit.z >= box->min.z && hit.z <= box->max.z) return TRUE;
	}
	if (Box_ThroughSideX(box->max.x, start, end, &hit.y, &hit.z)){
		if (hit.y >= box->min.y && hit.y <= box->max.y && hit.z >= box->min.z && hit.z <= box->max.z) return TRUE;
	}
	if (Box_ThroughSideY(box->min.y, start, end, &hit.x, &hit.z)){
		if (hit.x >= box->min.x && hit.x <= box->max.x && hit.z >= box->min.z && hit.z <= box->max.z) return TRUE;
	}
	if (Box_ThroughSideY(box->max.y, start, end, &hit.x, &hit.z)){
		if (hit.x >= box->min.x && hit.x <= box->max.x && hit.z >= box->min.z && hit.z <= box->max.z) return TRUE;
	}
	if (Box_ThroughSideZ(box->min.z, start, end, &hit.x, &hit.y)){
		if (hit.x >= box->min.x && hit.x <= box->max.x && hit.y >= box->min.y && hit.y <= box->max.y) return TRUE;
	}
	if (Box_ThroughSideZ(box->max.z, start, end, &hit.x, &hit.y)){
		if (hit.x >= box->min.x && hit.x <= box->max.x && hit.y >= box->min.y && hit.y <= box->max.y) return TRUE;
	}
	return FALSE;
}

__inline static REAL Box_SquareDistance(LPVECTOR3D a, LPVECTOR3D b) {

	return ((a->x - b->x) * (a->x - b ->x)) + ((a->y - b->y) * (a->y - b->y)) + ((a->z - b->z) * (a->z - b->z));
}

BOOL Box_LineIntersectionEx(LPBOX3D box, LPVECTOR3D start, LPVECTOR3D end, LPVECTOR3D hit, LPREAL delta, enum BoxSide *side) {

	VECTOR3D intersection[BoxSide_Count];
	REAL distSquared, minDistSquared = MAX_REAL;
	enum BoxSide index, minIndex = BoxSide_Count;

	index = BoxSide_Left;
	if (Box_ThroughSideX(box->min.x, start, end, &intersection[index].y, &intersection[index].z)){
		if (intersection[index].y >= box->min.y && intersection[index].y <= box->max.y && intersection[index].z >= box->min.z && intersection[index].z <= box->max.z) {
			intersection[index].x = box->min.x;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}

	index = BoxSide_Right;
	if (Box_ThroughSideX(box->max.x, start, end, &intersection[index].y, &intersection[index].z)){
		if (intersection[index].y >= box->min.y && intersection[index].y <= box->max.y && intersection[index].z >= box->min.z && intersection[index].z <= box->max.z) {
			intersection[index].x = box->max.x;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}

	index = BoxSide_Bottom;
	if (Box_ThroughSideY(box->min.y, start, end, &intersection[index].x, &intersection[index].z)){
		if (intersection[index].x >= box->min.x && intersection[index].x <= box->max.x && intersection[index].z >= box->min.z && intersection[index].z <= box->max.z) {
			intersection[index].y = box->min.y;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}

	index = BoxSide_Top;
	if (Box_ThroughSideY(box->max.y, start, end, &intersection[index].x, &intersection[index].z)){
		if (intersection[index].x >= box->min.x && intersection[index].x <= box->max.x && intersection[index].z >= box->min.z && intersection[index].z <= box->max.z) {
			intersection[index].y = box->max.y;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}

	index = BoxSide_Front;
	if (Box_ThroughSideZ(box->min.z, start, end, &intersection[index].x, &intersection[index].y)){
		if (intersection[index].x >= box->min.x && intersection[index].x <= box->max.x && intersection[index].y >= box->min.y && intersection[index].y <= box->max.y) {
			intersection[index].z = box->min.z;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}

	index = BoxSide_Back;
	if (Box_ThroughSideZ(box->max.z, start, end, &intersection[index].x, &intersection[index].y)){
		if (intersection[index].x >= box->min.x && intersection[index].x <= box->max.x && intersection[index].y >= box->min.y && intersection[index].y <= box->max.y) {
			intersection[index].z = box->max.z;
			distSquared = Box_SquareDistance(&intersection[index], start);
			if (distSquared < minDistSquared) {
				minDistSquared = distSquared;
				minIndex = index;
			}
		}
	}
	
	if (BoxSide_Count != minIndex) {

		*delta = Maths_InterpolationDelta(0.0f, Maths_Vector3DDistance(end, start), Maths_Sqrt(minDistSquared));
		*hit = intersection[minIndex];
		*side = minIndex;

		return TRUE;

	} else return FALSE;
}

__inline BOOL Box_ThroughSideX(REAL planeX, LPVECTOR3D a, LPVECTOR3D b, LPREAL yHit, LPREAL zHit) {

	REAL xDist;
	VECTOR3D line;

	if ((a->x <= planeX && b->x >= planeX) || (a->x >= planeX && b->x <= planeX))  {
		Maths_Vector3DSubtract(&line, b, a);
		xDist = planeX - a->x;
		*yHit = a->y + ((xDist / line.x) * line.y);
		*zHit = a->z + ((xDist / line.x) * line.z);
		return TRUE;
	}

	return FALSE;
}

__inline BOOL Box_ThroughSideY(REAL planeY, LPVECTOR3D a, LPVECTOR3D b, LPREAL xHit, LPREAL zHit) {

	REAL yDist;
	VECTOR3D line;

	if ((a->y <= planeY && b->y >= planeY) || (a->y >= planeY && b->y <= planeY))  {
		Maths_Vector3DSubtract(&line, b, a);
		yDist = planeY - a->y;
		*xHit = a->x + ((yDist / line.y) * line.x);
		*zHit = a->z + ((yDist / line.y) * line.z);
		return TRUE;
	}

	return FALSE;
}

__inline BOOL Box_ThroughSideZ(REAL planeZ, LPVECTOR3D a, LPVECTOR3D b, LPREAL xHit, LPREAL yHit) {

	REAL zDist;
	VECTOR3D line;

	if ((a->z <= planeZ && b->z >= planeZ) || (a->z >= planeZ && b->z <= planeZ))  {
		Maths_Vector3DSubtract(&line, b, a);
		zDist = planeZ - a->z;
		*xHit = a->x + ((zDist / line.z) * line.x);
		*yHit = a->y + ((zDist / line.z) * line.y);
		return TRUE;
	}

	return FALSE;
}

__inline BOOL Box_PointInside(LPBOX3D box, LPVECTOR3D point) {

	if (point->x >= box->min.x && point->x <= box->max.x &&
		point->y >= box->min.y && point->y <= box->max.y &&
		point->z >= box->min.z && point->z <= box->max.z) {

		return TRUE;
	}

	return FALSE;
}

__inline BOOL Box_IntersectionImpossible(LPBOX3D aBox, LPBOX3D bBox) {

	if (aBox->max.x < bBox->min.x) return TRUE;
	if (aBox->max.y < bBox->min.y) return TRUE;
	if (aBox->max.z < bBox->min.z) return TRUE;
	if (aBox->min.x > bBox->max.x) return TRUE;
	if (aBox->min.y > bBox->max.y) return TRUE;
	if (aBox->min.z > bBox->max.z) return TRUE;

	return FALSE;
}

VOID Box_Draw(LPBOX3D box, lpViewport vp, lpFrame refFrame, lpFrame camera, COLOUR colour) {

	ULONG loop;
	VECTOR3D vectorList[8];
	struct DrawCoord coordList[8];
	UWORD indexList[24] = { 0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 1, 5, 2, 6, 3, 7, 4, 5, 5, 6, 6, 7, 7, 4 };

	Box_BuildVectorList(box, vectorList);

	for (loop=0 ; loop<8 ; loop++) {
		coordList[loop].position = vectorList[loop];
		coordList[loop].colour = colour;
	}

	Draw_LineList(vp, refFrame, camera, coordList, 8, indexList, 24);
}

__inline VOID Box_SetupVisibiltyCheck(lpViewport vp, lpFrame refFrame, lpFrame camera) {

	Viewport_SetupBatchTransform(vp, refFrame, camera);
	boxGlobs.vp = vp;
}

__inline BOOL Box_CornerVisibile(LPBOX3D box) {

	// This is a really bad way of doing this check...

	ULONG loop;
	VECTOR3D point;
	VECTOR3D src[8] = {
		{ box->min.x, box->max.y, box->min.z },
		{ box->max.x, box->max.y, box->min.z },
		{ box->max.x, box->min.y, box->min.z },
		{ box->min.x, box->min.y, box->min.z },
		{ box->min.x, box->max.y, box->max.z },
		{ box->max.x, box->max.y, box->max.z },
		{ box->max.x, box->min.y, box->max.z },
		{ box->min.x, box->min.y, box->max.z }
	};

	Error_Fatal(NULL == boxGlobs.vp, "Box_SetupVisibiltyCheck() not called");

	for (loop=0 ; loop<8 ; loop++) {
		Viewport_BatchTransform(boxGlobs.vp, &point, &src[loop]);
		if (point.x >= 0.0f && point.x <= Viewport_GetWidth(boxGlobs.vp) &&
			point.y >= 0.0f && point.y <= Viewport_GetHeight(boxGlobs.vp) &&
			point.z >= 0.0f && point.z <= 1.0f) {

			return TRUE;
		}
	}

	return FALSE;
}

VOID Box_FromString(LPBOX3D box, LPUCHAR minString, LPUCHAR maxString) {

	// Will destroy the strings...

	LPUCHAR argv[3];
	ULONG argc;

	if (3 == (argc = Util_Tokenise(minString, argv, sizeof(argv) / sizeof(argv[0]), ",", FALSE))) {

		box->min.x = (REAL) atof(argv[0]);
		box->min.y = (REAL) atof(argv[1]);
		box->min.z = (REAL) atof(argv[2]);

		if (3 == (argc = Util_Tokenise(maxString, argv, sizeof(argv) / sizeof(argv[0]), ",", FALSE))) {

			box->max.x = (REAL) atof(argv[0]);
			box->max.y = (REAL) atof(argv[1]);
			box->max.z = (REAL) atof(argv[2]);

		}
	}
}

VOID Box_Scale(LPBOX3D box, LPVECTOR3D scale) {

	box->min.x *= scale->x;
	box->max.x *= scale->x;
	box->min.y *= scale->y;
	box->max.y *= scale->y;
	box->min.z *= scale->z;
	box->max.z *= scale->z;
}

VOID Box_GetCenter(LPBOX3D box, LPVECTOR3D center) {

	Maths_Vector3DAdd(center, &box->min, &box->max);
	Maths_Vector3DScale(center, center, 0.5f);
}

VOID Box_Get(LPBOX3D box, LPVECTOR3D pointList, ULONG pointCount) {

	ULONG loop;

	box->min = box->max = pointList[0];

	for (loop=1 ; loop<pointCount ; loop++) {

		box->min.x = min(box->min.x, pointList[loop].x);
		box->min.y = min(box->min.y, pointList[loop].y);
		box->min.z = min(box->min.z, pointList[loop].z);
		box->max.x = max(box->max.x, pointList[loop].x);
		box->max.y = max(box->max.y, pointList[loop].y);
		box->max.z = max(box->max.z, pointList[loop].z);
	}
}

VOID Box_BuildVectorList(LPBOX3D box, VECTOR3D list[8]) {
	
	list[0].x = box->min.x; list[0].y = box->max.y; list[0].z = box->min.z;
	list[1].x = box->max.x; list[1].y = box->max.y; list[1].z = box->min.z;
	list[2].x = box->max.x; list[2].y = box->min.y; list[2].z = box->min.z;
	list[3].x = box->min.x; list[3].y = box->min.y; list[3].z = box->min.z;
	list[4].x = box->min.x; list[4].y = box->max.y; list[4].z = box->max.z;
	list[5].x = box->max.x; list[5].y = box->max.y; list[5].z = box->max.z;
	list[6].x = box->max.x; list[6].y = box->min.y; list[6].z = box->max.z;
	list[7].x = box->min.x; list[7].y = box->min.y; list[7].z = box->max.z;
}
