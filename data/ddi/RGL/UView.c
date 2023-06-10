
#include "Standard.h"
#include "Errors.h"
#include "Files.h"
#include "Utils.h"
#include "Mem.h"
#include "Lwo.h"
#include "Mesh.h"
#include "UView.h"
#include "Render.h"
#include "Polygon.h"

#define UView_Error(c,m,l)		Error_Fatal((c),Error_Format("Incorrect/invalid uview file (line %d): \"%s\"",(l),(m)))

BOOL UView_UVEqual(REAL ua, REAL va, REAL ub, REAL vb) {

	if (fabs(ua - ub) <= UVIEW_UVTOLERANCE &&
		fabs(va - vb) <= UVIEW_UVTOLERANCE) return TRUE;

	return FALSE;
}

BOOL UView_NormalEqual(LPVECTOR3D a, LPVECTOR3D b) {

	REAL dp = Maths_Vector3DDotProduct(a, b);

	if (dp <= 1.0f - UVIEW_NORMALTOLERANCE) return FALSE;

	return TRUE;
}

BOOL UView_PositionEqual(LPVECTOR3D a, LPVECTOR3D b, REAL tolerance) {

	if (fabs(a->x - b->x) <= tolerance &&
		fabs(a->y - b->y) <= tolerance &&
		fabs(a->z - b->z) <= tolerance) return TRUE;

	return FALSE;
}

static VOID UView_CompleteData(lpUView uView, lpLwo lwo) {

	// Fill in the missing data within the UViewVertex structure...

	ULONG polyIndex, vertexIndex, surfaceIndex;
	lpUViewVertex vertex;
	lpUViewPoly poly;
	lpLwoPoly lwoPoly;
	lpLwoSurface surface;
	ULONG lwoVertexIndex;

	for (surfaceIndex=0 ; surfaceIndex<uView->surfaceCount ; surfaceIndex++) {

		surface = &lwo->surfaceList[surfaceIndex];

		if (surface->flags & LWO_SURFACEFLAG_ADDITIVE) {
			uView->surfaceList[surfaceIndex][0].flags |= UVIEWSURFACE_FLAG_ADDITIVE;
		} else if (surface->flags & LWO_SURFACEFLAG_SHARPTERMINATOR) {
			uView->surfaceList[surfaceIndex][0].flags |= UVIEWSURFACE_FLAG_SUBTRACTIVE;
		}
	}

	for (polyIndex=0 ; polyIndex<uView->polyCount ; polyIndex++) {
		
		poly = &uView->polyList[polyIndex];
		lwoPoly = &lwo->polyList[polyIndex];
		surface = &lwo->surfaceList[poly->surface];

		for (vertexIndex=0 ; vertexIndex<poly->vertexCount ; vertexIndex++) {
			vertex = &uView->vertexGlobalList[poly->vertexListIndex + vertexIndex];

			lwoVertexIndex = lwo->polyData[lwoPoly->polyIndex + vertexIndex];

			vertex->position = lwo->pointList[lwoVertexIndex];
			if (!(vertex->flags & UVIEWVERTEX_FLAG_UV)) Lwo_GetUV(surface, &vertex->position, &vertex->u, &vertex->v);
			if (!(vertex->flags & UVIEWVERTEX_FLAG_NORMAL)) vertex->normal = lwo->normalList[lwoVertexIndex];
//			if (!(vertex->flags & UVIEWVERTEX_FLAG_COLOUR)) vertex->colour = surface->colour;
//			if (Dialog_GetOption(DialogOption_NoTextures)) {
// 				if (!(vertex->flags & UVIEWVERTEX_FLAG_COLOUR)) vertex->colour = COLOUR_FROMREAL(Maths_RandRange(0.5f, 1.0f), Maths_RandRange(0.5f, 1.0f), Maths_RandRange(0.5f, 1.0f));
	//		} else {

			if (!(vertex->flags & UVIEWVERTEX_FLAG_COLOUR)) vertex->colour = COLOUR_FROMCHARA(127, 255, 255, 255);

			//		}
//			if (!(vertex->flags & UVIEWVERTEX_FLAG_COLOUR)) vertex->colour = COLOUR_FROMCHAR(127, 127, 127);
		}
	}
}

static VOID UView_RepointVertices(lpUView uView, BOOL anySurface, BOOL ignoreNormals) {

	ULONG loop, sub;
	ULONG loopSurface, subSurface;
	lpUViewVertex loopVertex, subVertex;

	for (loop=0 ; loop<uView->vertexGlobalCount ; loop++) {
		loopVertex = &uView->vertexGlobalList[loop];

		loopVertex->useVertex = loop;
	}

	for (loop=0 ; loop<uView->vertexGlobalCount ; loop++) {

		loopVertex = &uView->vertexGlobalList[loop];
		loopSurface = uView->polyList[loopVertex->polyIndex].surface;

		if (loop == loopVertex->useVertex) {
			for (sub=loop+1 ; sub<uView->vertexGlobalCount ; sub++) {

				subVertex = &uView->vertexGlobalList[sub];
				subSurface = uView->polyList[subVertex->polyIndex].surface;

				if ((UView_UVEqual(subVertex->u, subVertex->v, loopVertex->u, loopVertex->v)) &&
					(UView_PositionEqual(&subVertex->position, &loopVertex->position, 0.0f)) &&
					(subVertex->colour == loopVertex->colour) &&
					(ignoreNormals || UView_NormalEqual(&subVertex->normal, &loopVertex->normal)) &&
					(anySurface || subSurface == loopSurface)) {

					subVertex->useVertex = loop;
				}
			}
		}
	}
}

static VOID UView_LoadTextures(lpUView uView) {

	ULONG surfaceIndex;

	if (uView->surfaceList) {

		for (surfaceIndex=0 ; surfaceIndex<uView->surfaceCount ; surfaceIndex++) {

			if (uView->surfaceList[surfaceIndex][0].fileName) {

				UCHAR path[FILE_MAXPATH];

				if (uView->path) sprintf(path, "%s\\%s", uView->path, uView->surfaceList[surfaceIndex][0].fileName);
				else sprintf(path, "%s", uView->surfaceList[surfaceIndex][0].fileName);

#pragma message ( "Using .bmp instead of .tim" )
			
				if (File_GetSuffix(path) && 0 == stricmp(File_GetSuffix(path), "tim")) {
					sprintf(&path[strlen(path) - 4], ".bmp");
				}

				uView->surfaceList[surfaceIndex][0].texture = Texture_Load(path, TRUE);
			}
		}

	}
}

static VOID UView_AdjustUVs(lpUView uView) {

	ULONG vertexIndex;
	lpUViewVertex vertex;
	lpUViewPoly poly;
	lpTexture texture;

	for (vertexIndex=0 ; vertexIndex<uView->vertexGlobalCount ; vertexIndex++) {

		vertex = &uView->vertexGlobalList[vertexIndex];
		poly = &uView->polyList[vertex->polyIndex];

		if (texture = uView->surfaceList[poly->surface][0].texture) {

			VECTOR2D offset = { (1.0f / Texture_GetWidth(texture)) / 2.0f, (1.0f / Texture_GetHeight(texture)) / 2.0f };

			vertex->u = Maths_Interpolate(offset.x, 1.0f - offset.x, vertex->u);
			vertex->v = Maths_Interpolate(offset.y, 1.0f - offset.y, vertex->v);
		}
	}
}

static lpMesh UView_BuildMesh(lpUView uView, ULONG blendLevels, BOOL useNormals) {

	// Build a mesh using one set of uv's per vertex...
	// Use one vertex list per group to allow the mesh to be referenced multiple times...

	ULONG loop, surfaceIndex, polyIndex, vertexIndex, vli;
	ULONG vertexCount, polyCount;
	lpUViewPoly poly, usePoly;
	lpUViewVertex vertex, useVertex;
	struct MeshVertexInfo vertexInfo;
	LPULONG indexList = Mem_Alloc(sizeof(indexList[0]) * uView->vertexGlobalCount);
	LPULONG reverseIndexList = Mem_Alloc(sizeof(reverseIndexList[0]) * uView->vertexGlobalCount);
	lpMesh mesh;
	ULONG flags;
	
	for (polyCount=polyIndex=0 ; polyIndex<uView->polyCount ; polyIndex++) {

		poly = &uView->polyList[polyIndex];

		if (3 == poly->vertexCount) polyCount++;
		else if (4 == poly->vertexCount) polyCount += 2;
	}

	mesh = Mesh_Create(polyCount, 0, TRUE);

	for (surfaceIndex=0 ; surfaceIndex<uView->surfaceCount ; surfaceIndex++) {

		vertexCount = 0;
		polyCount = 0;

#ifdef _DEBUG
		Mem_Set(indexList, 0xcd, sizeof(indexList[0]) * uView->vertexGlobalCount);
		Mem_Set(reverseIndexList, 0xcd, sizeof(reverseIndexList[0]) * uView->vertexGlobalCount);
#endif // _DEBUG

		for (vertexIndex=0 ; vertexIndex<uView->vertexGlobalCount ; vertexIndex++) {

			vertex = &uView->vertexGlobalList[vertexIndex];
			poly = &uView->polyList[vertex->polyIndex];
			useVertex = &uView->vertexGlobalList[vertex->useVertex];
			usePoly = &uView->polyList[useVertex->polyIndex];

			if (poly->surface == surfaceIndex) {
				if (vertex->useVertex == vertexIndex) {
					indexList[vertexCount] = vertexIndex;
					reverseIndexList[vertexIndex] = vertexCount;
					vertexCount++;
				}
			}
		}

		if (vertexCount) {

			for (polyIndex=0 ; polyIndex<uView->polyCount ; polyIndex++) {

				poly = &uView->polyList[polyIndex];

				if (poly->surface == surfaceIndex) {
					if (3 == poly->vertexCount) polyCount++;
					else if (4 == poly->vertexCount) polyCount += 2;
				}
			}

			flags = MESH_VERTEXFLAG_DIFFUSE;
			if (useNormals) flags |= MESH_VERTEXFLAG_NORMAL;

			Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, flags);
			vli = Mesh_AddVertexList(mesh, vertexCount, &vertexInfo);
			Mesh_CreateGroup(mesh, vli, 3, polyCount);

			Mesh_SetTexture(mesh, vli, 0, uView->surfaceList[surfaceIndex][0].texture);
			if (uView->surfaceList[surfaceIndex][0].flags & UVIEWSURFACE_FLAG_ADDITIVE) {
				Mesh_SetGroupRenderFlags(mesh, vli, RENDER_FLAG_ADDITIVE, TRUE);
			} else if (uView->surfaceList[surfaceIndex][0].flags & UVIEWSURFACE_FLAG_SUBTRACTIVE) {
				Mesh_SetGroupRenderFlags(mesh, vli, RENDER_FLAG_SUBTRACTIVE, TRUE);
			}

			Mesh_LockVertices(mesh, TRUE);
			for (vertexIndex=0 ; vertexIndex<vertexCount ; vertexIndex++) {

				vertex = &uView->vertexGlobalList[indexList[vertexIndex]];

				Mesh_SetVertexPosition(mesh, vli, vertexIndex, &vertex->position);
				Mesh_SetVertexColour(mesh, vli, vertexIndex, vertex->colour);
				Mesh_SetVertexUV(mesh, vli, vertexIndex, 0, vertex->u, vertex->v);
				if (useNormals) Mesh_SetVertexNormal(mesh, vli, vertexIndex, &vertex->normal);
			}
			Mesh_LockVertices(mesh, FALSE);

			for (polyIndex=0 ; polyIndex<uView->polyCount ; polyIndex++) {
				
				poly = &uView->polyList[polyIndex];
				if (poly->surface == surfaceIndex && (3 == poly->vertexCount || 4 == poly->vertexCount)) {

					UWORD polyData[3];
					ULONG shapeList[3 * (UVIEW_MAXPOLYSIDES - 2)];
					VECTOR3D pointList[UVIEW_MAXPOLYSIDES];

					Error_Fatal(poly->vertexCount > UVIEW_MAXPOLYSIDES, "Polygon has more sides than UVIEW_MAXPOLYSIDES allows");

					for (loop=0 ; loop<poly->vertexCount ; loop++) {
						vertex = &uView->vertexGlobalList[poly->vertexListIndex + loop];
						pointList[loop] = vertex->position;
					}

					Polygon_Triple(pointList, poly->vertexCount, shapeList);

					for (loop=0 ; loop<poly->vertexCount-2 ; loop++) {
						for (vertexIndex=0 ; vertexIndex<3 ; vertexIndex++) {

							vertex = &uView->vertexGlobalList[poly->vertexListIndex + shapeList[(3 * loop) + vertexIndex]];

							polyData[vertexIndex] = (UWORD) reverseIndexList[vertex->useVertex];
						}

						Mesh_AddTriangle(mesh, vli, polyData);
					}
				}
			}
		}
	}

	Mem_Free(reverseIndexList);
	Mem_Free(indexList);

	return mesh;
}

VOID UView_MergeSurfaces(lpUView uView) {

	ULONG loop, sub, polyIndex;
	lpUViewPoly poly;

	for (loop=0 ; loop<uView->surfaceCount ; loop++) {
		for (sub=loop+1 ; sub<uView->surfaceCount ; sub++) {
			if (uView->surfaceList[loop][0].fileName && uView->surfaceList[sub][0].fileName) {
				if (0 == stricmp(uView->surfaceList[loop][0].fileName, uView->surfaceList[sub][0].fileName)) {
					for (polyIndex=0 ; polyIndex<uView->polyCount ; polyIndex++) {

						poly = &uView->polyList[polyIndex];

						if (poly->surface == sub) poly->surface = loop;
					}
					Mem_Free(uView->surfaceList[sub][0].fileName);
					uView->surfaceList[sub][0].fileName = NULL;
				}
			}
		}
	}
}

lpUView UView_GenerateFromLwo(lpLwo lwo) {

	lpUView uView = Mem_AllocClear(sizeof(*uView));
	lpUViewVertex vertex;
	lpUViewPoly poly;
	lpLwoPoly lwoPoly;
	ULONG loop, sub, usedVertexCount;

	uView->path = lwo->path;
	uView->polyCount = lwo->polyCount;

	for (usedVertexCount=loop=0 ; loop<uView->polyCount ; loop++) {

		lwoPoly = &lwo->polyList[loop];

		usedVertexCount += lwoPoly->pointCount;
	}

	uView->vertexGlobalListSize = uView->vertexGlobalCount = usedVertexCount;
	uView->polyList = Mem_Alloc(sizeof(uView->polyList[0]) * uView->polyCount);
	uView->vertexGlobalList = Mem_Alloc(sizeof(uView->vertexGlobalList[0]) * uView->vertexGlobalCount);
	
	for (usedVertexCount=loop=0 ; loop<uView->polyCount ; loop++) {

		lwoPoly = &lwo->polyList[loop];
		poly = &uView->polyList[loop];
		
		poly->surface = lwoPoly->surface;
		poly->vertexCount = lwoPoly->pointCount;
		poly->vertexListIndex = usedVertexCount;

		for (sub=0 ; sub<poly->vertexCount ; sub++) {
			
			vertex = &uView->vertexGlobalList[poly->vertexListIndex + sub];
				
			vertex->polyIndex = loop;
			vertex->flags = 0;
		}

		usedVertexCount += poly->vertexCount;
	}

	uView->surfaceCount = lwo->surfaceCount;

	uView->surfaceList = Mem_AllocClear(sizeof(uView->surfaceList[0]) * uView->surfaceCount);
	for (loop=0 ; loop<uView->surfaceCount ; loop++) {
		if (lwo->surfaceList[loop].texture) uView->surfaceList[loop][0].fileName = Mem_CopyString(lwo->surfaceList[loop].texture);
	}

	return uView;
}

lpMesh UView_MakeMesh(lpLwo lwo, LPUCHAR fname, ULONG blendLevels, BOOL useNormals) {

	lpUView uView;
	lpMesh mesh = NULL;

	if (NULL == (uView = UView_ParseFile(lwo, fname))) {
		uView = UView_GenerateFromLwo(lwo);
	}

	UView_CompleteData(uView, lwo);
	UView_RepointVertices(uView, FALSE, !useNormals);
	UView_MergeSurfaces(uView);
	UView_LoadTextures(uView);
	UView_AdjustUVs(uView);

	mesh = UView_BuildMesh(uView, blendLevels, useNormals);

	UView_Free(uView);

	return mesh;
}

static VOID UView_GetVertexList(lpUView uView, lpUViewPoly poly) {

	ULONG newSize;

	if (uView->vertexGlobalCount + poly->vertexCount > uView->vertexGlobalListSize) {
		newSize = uView->vertexGlobalListSize + UVIEW_VERTEXLISTBLOCKSIZE;
		uView->vertexGlobalList = Mem_ReAllocClear(uView->vertexGlobalList, sizeof(uView->vertexGlobalList[0]) * newSize);
		uView->vertexGlobalListSize = newSize;
	}

	poly->vertexListIndex = uView->vertexGlobalCount;
	uView->vertexGlobalCount += poly->vertexCount;
}

static BOOL UView_ParseV2(lpUView uView, lpLwo lwo, lpFile uvfp) {

	UCHAR line[1024];
	ULONG loop, sub, argc, polyIndex, lineNum = 1;
	LPUCHAR s, t, argv[UVIEW_MAXARGS];
	lpUViewVertex vertex;
	lpUViewPoly poly;
	LPULONG surfaceRemapList;

	File_GetLine(line, sizeof(line), uvfp);

	uView->surfaceCount = atol(line);
	UView_Error(uView->surfaceCount != lwo->surfaceCount, "Surface count mismatch", lineNum);

	surfaceRemapList = Mem_Alloc(sizeof(surfaceRemapList[0]) * uView->surfaceCount);

	for (loop=0 ; loop<uView->surfaceCount ; loop++) {
		File_GetLine(line, sizeof(line), uvfp);
//		for (sub=0 ; sub<lwo->surfaceCount ; sub++) {
//			if (0 == stricmp(line, lwo->surfaceList[sub].name)) {
//				surfaceRemapList[loop] = sub;
//				break;
//			}
//		}
		Error_Fatal(0 != stricmp(line, lwo->surfaceList[loop].name), "Surface order mismatch");
//		Error_Fatal(sub == lwo->surfaceCount, "Cannot find surface");
	}

	uView->surfaceList = Mem_AllocClear(sizeof(uView->surfaceList[0]) * uView->surfaceCount);

	for (loop=0 ; loop<uView->surfaceCount ; loop++) {
		File_GetLine(line, sizeof(line), uvfp);
		if (0 != stricmp("NULL", line)) {
			for (s=t=line ; '\0'!=*s ; s++) if ('\\' == *s) t = s+1;
//			uView->surfaceList[surfaceRemapList[loop]][0].fileName = Mem_CopyString(t);
			uView->surfaceList[loop][0].fileName = Mem_CopyString(t);
		}
	}

	File_GetLine(line, sizeof(line), uvfp);
	uView->polyCount = atol(line);
	UView_Error(uView->polyCount != lwo->polyCount, "Polygon count mismatch", lineNum);
	uView->polyList = Mem_Alloc(sizeof(uView->polyList[0]) * uView->polyCount);

	for (loop=0 ; loop<uView->polyCount ; loop++) {
		
		File_GetLine(line, sizeof(line), uvfp);
		argc = Util_WSTokenise(line, argv, UVIEW_MAXARGS, TRUE);

		polyIndex = atol(argv[0]);

		UView_Error(polyIndex > uView->polyCount, "Polygon is out of range", lineNum);
		poly = &uView->polyList[polyIndex];

		poly->surface = lwo->polyList[polyIndex].surface;
		poly->vertexCount = atol(argv[1]);
		UView_GetVertexList(uView, poly);

		for (sub=0 ; sub<poly->vertexCount ; sub++) {

			File_GetLine(line, sizeof(line), uvfp);
			argc = Util_WSTokenise(line, argv, UVIEW_MAXARGS, TRUE);

			vertex = &uView->vertexGlobalList[poly->vertexListIndex + sub];

			vertex->u = (REAL) atof(argv[0]);
			vertex->v = (REAL) atof(argv[1]);
			vertex->flags |= UVIEWVERTEX_FLAG_UV;
			vertex->polyIndex = polyIndex;
		}
	}

	Mem_Free(surfaceRemapList);

	return TRUE;
}

static BOOL UView_ParseV4(lpUView uView, lpLwo lwo, lpFile uvfp) {

	UCHAR line[1024];
	LPUCHAR argv[UVIEW_MAXARGS];
	ULONG argc, lineNum;

	if (File_GetLine(line, sizeof(line), uvfp)) {
		
		argc = Util_WSTokenise(line, argv, UVIEW_MAXARGS, FALSE);

		if (2 == argc && 0 == strcmp("VERSION", argv[0]) && 4 == atol(argv[1])) {

			ULONG currSurface, currChannel, currPoly;
			BOOL surfaceFileMode = FALSE;
			lpUViewPoly poly;
			lpUViewVertex vertex;
			
			for (lineNum=3 ; File_GetLine(line, sizeof(line), uvfp) ; lineNum++) {
				
				if (surfaceFileMode) {
					
					LPUCHAR s, t;

					UView_Error(0 == uView->surfaceCount, "No surface count specified", lineNum);
					UView_Error(NULL != uView->surfaceList[currSurface][currChannel].fileName, "Surface/channel has multiple texture image files", lineNum);

					if (0 != strcmp("NULL", line)) {
						for (s=t=line ; '\0'!=*s ; s++) if ('\\' == *s) t = s+1;
						uView->surfaceList[currSurface][currChannel].fileName = Mem_CopyString(t);
					}
					
					surfaceFileMode = FALSE;
					
				} else {
					
					argc = Util_WSTokenise(line, argv, UVIEW_MAXARGS, FALSE);

					if (0 == strcmp("SURFACE_COUNT", argv[0])) {
						
						uView->surfaceCount = atol(argv[1]);
						UView_Error(uView->surfaceCount != lwo->surfaceCount, "Surface count mismatch", lineNum);
						
						uView->surfaceList = Mem_AllocClear(sizeof(uView->surfaceList[0]) * uView->surfaceCount);

					} else if (0 == strcmp("CHANNEL", argv[0])) {
						
						currChannel = atol(argv[1]);
						UView_Error(currChannel > UVIEW_MAXCHANNELS, "Channel is out of range", lineNum);
						
					} else if (0 == strcmp("SURFACE", argv[0])) {
						
						currSurface = atol(argv[1]);
						UView_Error(currSurface > uView->surfaceCount, "Surface is out of range", lineNum);
						
					} else if (0 == strcmp("SURFACE_IMAGE_FILE", argv[0])) {
						
						surfaceFileMode = TRUE;
						
					} else if (0 == strcmp("POLY_COUNT", argv[0])) {
						
						uView->polyCount = atol(argv[1]);
						UView_Error(uView->polyCount != lwo->polyCount, "Polygon count mismatch", lineNum);
						uView->polyList = Mem_Alloc(sizeof(uView->polyList[0]) * uView->polyCount);
						
					} else if (0 == strcmp("POLY", argv[0])) {
						
						currPoly = atol(argv[1]);
						UView_Error(currPoly > uView->polyCount, "Polygon is out of range", lineNum);
						poly = &uView->polyList[currPoly];
						
					} else if (0 == strcmp("POLY_SURF", argv[0])) {
						
						poly->surface = atol(argv[1]);
						UView_Error(poly->surface > uView->surfaceCount, "Polygon surface is out of range", lineNum);
						
					} else if (0 == strcmp("POLY_VERT_COUNT", argv[0])) {
						
						poly->vertexCount = atol(argv[1]);
						UView_GetVertexList(uView, poly);
						
					} else if (0 == strcmp("VERT", argv[0])) {
						
						ULONG currVertex = atol(argv[1]);
						UView_Error(currVertex > poly->vertexCount, "Vertex is out of range of polygon", lineNum);
						vertex = &uView->vertexGlobalList[poly->vertexListIndex + currVertex];
						vertex->polyIndex = currPoly;

					} else if (0 == strcmp("VERT_CUV", argv[0])) {		// I think 'C' is the channel???
						
						vertex->u = (REAL) atof(argv[2]);
						vertex->v = (REAL) atof(argv[3]);
						vertex->flags |= UVIEWVERTEX_FLAG_UV;
						
					} else if (0 == strcmp("VERT_RGB", argv[0])) {
						
						vertex->colour = COLOUR_FROMREAL((REAL) atof(argv[1]), (REAL) atof(argv[2]), (REAL) atof(argv[3]));
						vertex->flags |= UVIEWVERTEX_FLAG_COLOUR;
						
					} else if (0 == strcmp("VERT_NORMAL", argv[0])) {
						
						vertex->normal.x = (REAL) atof(argv[1]);
						vertex->normal.y = (REAL) atof(argv[2]);
						vertex->normal.z = (REAL) atof(argv[3]);
						vertex->flags |= UVIEWVERTEX_FLAG_NORMAL;
						
					}
				}
			}

			return TRUE;

		} else Error_Fatal(TRUE, "Invalid UViewV4 file");
	}

	return FALSE;
}

static lpUView UView_ParseFile(lpLwo lwo, LPUCHAR fname) {

	lpUView uView = NULL;
	lpFile uvfp;
	UCHAR path[FILE_MAXPATH];
	ULONG flen = strlen(fname);
	ULONG slen = strlen(LWO_FILESUFFIX);
	UCHAR line[1024];
	BOOL result = FALSE;
	
	if (flen < slen || 0 != stricmp(&fname[flen-slen], LWO_FILESUFFIX)) sprintf(path, "%s%s", fname, UVIEW_FILESUFFIX);
	else {
		sprintf(path, "%s", fname);
		sprintf(&path[flen-slen], "%s", UVIEW_FILESUFFIX);
	}

	if (uvfp = File_Open(path, "r")) {
		if (uView = Mem_AllocClear(sizeof(*uView))) {

			uView->path = lwo->path;

			if (File_GetLine(line, sizeof(line), uvfp)) {

				switch(atol(line)) {
				case 4: result = UView_ParseV4(uView, lwo, uvfp); break;
				case 2: result = UView_ParseV2(uView, lwo, uvfp); break;
				default: Error_Fatal(TRUE, "Invalid/unsupported uview file");
				}

			}
			if (!result) {
				Mem_Free(uView);
				uView = NULL;
				Error_Fatal(TRUE, Error_Format("Cannot parse UView file \"%s\"", fname));
			}
		}
		File_Close(uvfp);
	}

	return uView;
}

static VOID UView_Free(lpUView uView) {
	
	ULONG channel, surface;

	if (uView->surfaceList) {
		for (surface=0 ; surface<uView->surfaceCount ; surface++) {
			for (channel=0 ; channel<UVIEW_MAXCHANNELS ; channel++) {
				if (uView->surfaceList[surface][channel].fileName) {
					Mem_Free(uView->surfaceList[surface][channel].fileName);
				}
			}
		}
		Mem_Free(uView->surfaceList);
	}

	Mem_Free(uView->vertexGlobalList);
	Mem_Free(uView->polyList);
	Mem_Free(uView);
}