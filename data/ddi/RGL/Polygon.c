
#include "Standard.h"
#include "Maths.h"
#include "Polygon.h"
#include "Errors.h"

__inline BOOL Polygon_PointInside(VECTOR3D polygon[3], LPVECTOR3D normal, LPVECTOR3D point) {

	VECTOR2D pip, shapeList[4];
	ULONG loop, maxAxis;

	if (normal->x > normal->y) {
		if (normal->x > normal->z) maxAxis = 0;
		else maxAxis = 2;
	} else {
		if (normal->y > normal->z) maxAxis = 1;
		else maxAxis = 2;
	}

	for (loop=0 ; loop<3 ; loop++) {

		switch (maxAxis) {
		case 0:
		
			shapeList[loop].x = polygon[loop].y;
			shapeList[loop].y = polygon[loop].z;
			pip.x = point->y;
			pip.y = point->z;
			break;

		case 1:
			
			shapeList[loop].x = polygon[loop].x;
			shapeList[loop].y = polygon[loop].z;
			pip.x = point->x;
			pip.y = point->z;
			break;

		case 2:

			shapeList[loop].x = polygon[loop].x;
			shapeList[loop].y = polygon[loop].y;
			pip.x = point->x;
			pip.y = point->y;
			break;

		}
	} 

	shapeList[loop] = shapeList[0];

	if (Maths_PointInsidePoly(&pip, &shapeList[0], &shapeList[1], 3)) {

		return TRUE;
	}

	return FALSE;
}

/*

BOOL Polygon_FindIntersections(VECTOR3D intersection[2], VECTOR3D paper[3], LPVECTOR3D paperNormal, VECTOR3D razor[3]) {

	VECTOR3D ray;
	LPVECTOR3D razorEndList[3] = { &razor[1], &razor[2], &razor[0] };
	ULONG count, loop;

	for (count=loop=0 ; loop<3 ; loop++) {

		Maths_Vector3DSubtract(&ray, razorEndList[loop], &razor[loop]);
		Maths_Vector3DNormalise(&ray);

		if (Maths_RayPlaneIntersectionFast(&intersection[count], &razor[loop], &ray, &paper[0], paperNormal)) {
			if (2 == ++count) break;
		}
	}

	Error_Fatal(1 == count, "Something has gone wrong");

	return (count == 2);
}

ULONG Polygon_FindEdgeIntersectionPoints(VECTOR3D edgeIntersection[3], VECTOR3D paper[3], LPVECTOR3D paperNormal, VECTOR3D planePoints[2]) {

	ULONG loop;
	VECTOR3D ray, edgePolyNormal;
	LPVECTOR3D paperEndList[3] = { &paper[1], &paper[2], &paper[0] };
	VECTOR3D edgePoly[3];
	ULONG unCutEdge;

	Maths_Vector3DSubtract(&ray, &planePoints[1], &planePoints[0]);
	Maths_Vector3DNormalise(&ray);

	for (loop=0 ; loop<3 ; loop++) {
	
		edgePoly[0] = paper[loop];
		edgePoly[1] = *(paperEndList[loop]);
		Maths_Vector3DAdd(&edgePoly[2], &paper[loop], paperNormal);
		Maths_PlaneNormal(&edgePolyNormal, &edgePoly[0], &edgePoly[1], &edgePoly[2]);

		if (!Maths_RayPlaneIntersectionFast(&edgeIntersection[loop], &planePoints[0], &ray, &edgePoly[0], &edgePolyNormal) ||
			!Maths_PointOnLine(&edgeIntersection[loop], &edgePoly[0], &edgePoly[1])) {

			unCutEdge = loop;
		}
	}

	return unCutEdge;
}

VOID Polygon_Slice(VECTOR3D paper[3], VECTOR3D razor[3]) {

	VECTOR3D paperNormal;
	VECTOR3D planeIntersection[2];
	VECTOR3D edgeIntersection[3];
	ULONG unCutPaperEdge;
	BOOL inside[2], outside;

	Maths_PlaneNormal(&paperNormal, &paper[0], &paper[1], &paper[2]);
	
	if (Polygon_FindIntersections(planeIntersection, paper, &paperNormal, razor)) {
	
//		inside[0] = Polygon_PointInside(paper, &paperNormal, &planeIntersection[0]);
//		inside[1] = Polygon_PointInside(paper, &paperNormal, &planeIntersection[1]);
		unCutPaperEdge = Polygon_FindEdgeIntersectionPoints(edgeIntersection, paper, &paperNormal, planeIntersection);
		inside[0] = Maths_PointOnLine(&planeIntersection[0], &edgeIntersection[0], &edgeIntersection[1]);
		inside[1] = Maths_PointOnLine(&planeIntersection[1], &edgeIntersection[0], &edgeIntersection[1]);
		outside = Maths_PointOnLine(&edgeIntersection[0], &planeIntersection[0], &planeIntersection[1]);

		if (inside[0] || inside[1] || outside) {

		}
	}
}
*/

/*
static VOID Polygon_Triple_Quad(LPVECTOR3D pointList, ULONG pointCount, LPULONG faceData) {

	ULONG start, end, prev, next, loop;
	VECTOR3D normal, firstNormal;
	VECTOR3D vectorList[2][2];
	REAL dp[2];
	BOOL first;

	// Find an edge that can only form triangles that all face the same direction...

	for (end=1 ; end<pointCount ; end++) {
		start = end-1;
		first = TRUE;
		for (loop=0 ; loop<pointCount ; loop++) {
			if (loop < start || loop > end) {
				Maths_PlaneNormal(&normal, &pointList[start], &pointList[end], &pointList[loop]);
				if (first) {
					firstNormal = normal;
					first = FALSE;
				} else {
					if (Maths_Vector3DDotProduct(&firstNormal, &normal) < 0.0f) break;
				}
			}
		}
		if (loop == pointCount) break;
	}

	prev = ((start + pointCount) - 1) % pointCount;
	next = (end + 1) % pointCount;

	Maths_Vector3DSubtract(&vectorList[0][0], &pointList[prev], &pointList[start]);
	Maths_Vector3DSubtract(&vectorList[0][1], &pointList[end], &pointList[start]);
	Maths_Vector3DSubtract(&vectorList[1][0], &pointList[start], &pointList[end]);
	Maths_Vector3DSubtract(&vectorList[1][1], &pointList[next], &pointList[end]);

	dp[0] = Maths_Vector3DDotProduct(&vectorList[0][0], &vectorList[0][1]);
	dp[1] = Maths_Vector3DDotProduct(&vectorList[1][0], &vectorList[1][1]);

	if (dp[0] < dp[1]) {

		faceData[0] = prev;		faceData[1] = start;	faceData[2] = end;
		faceData[3] = prev;		faceData[4] = end;		faceData[5] = next;

	} else {

		faceData[0] = prev;		faceData[1] = start;	faceData[2] = next;
		faceData[3] = start;	faceData[4] = end;		faceData[5] = next;
	}
}
*/

VOID Polygon_Triple(LPVECTOR3D pointList, ULONG pointCount, LPULONG faceData) {

	// 'pointList' is an ordered list of points that define the polygon...
	// 'faceData' must be large enough to hold 3 * (pointCount - 2)...
	
	ULONG loop;

	if (3 == pointCount) {
		for (loop=0 ; loop<pointCount ; loop++) faceData[loop] = loop;
	} else if (4 == pointCount) {
//		Polygon_Triple_Quad(pointList, pointCount, faceData);
		faceData[0] = 0;
		faceData[1] = 1;
		faceData[2] = 2;
		faceData[3] = 0;
		faceData[4] = 2;
		faceData[5] = 3;
	} else Error_Fatal(TRUE, "Only quads supported");
}
