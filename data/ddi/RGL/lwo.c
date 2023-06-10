
#include "Standard.h"
#include "Errors.h"
#include "Files.h"
#include "Mesh.h"
#include "Mem.h"
#include "Lwo.h"

lpLwo Lwo_Load(LPUCHAR fname) {

	LPULONG fileData, chunk;
	ULONG size, bytepos, chunkSize;
	UCHAR path[FILE_MAXPATH];
	lpLwo lwo;

	{
		ULONG flen = strlen(fname);
		ULONG slen = strlen(LWO_FILESUFFIX);
		if (flen < slen || 0 != stricmp(&fname[flen-slen], LWO_FILESUFFIX)) sprintf(path, "%s%s", fname, LWO_FILESUFFIX);
		else strcpy(path, fname);
	}

	if (fileData = File_LoadBinary(path, &size)) {
		Error_Fatal(size<8||LWO_MAGIC_FORM!=fileData[0]||LWO_ULONG(fileData[1])!=size-8, "Invalid IFF header in file");
		Error_Fatal(size<12||LWO_MAGIC_LWOB!=fileData[2], "File is not an lwo");

		lwo = Mem_AllocClear(sizeof(*lwo));

		bytepos = 3 * 4;

		while (bytepos < size) {
			chunk = (LPULONG) (&((LPUCHAR) fileData)[bytepos]);
			Error_Fatal(bytepos+8>size, "Invalid chunk");
			chunkSize = LWO_ULONG(chunk[1]);
			Error_Fatal(bytepos+8+chunkSize>size, "Chunk size passes end of file");
			switch(chunk[0]) {
			case LWO_MAGIC_PNTS:	Lwo_ParsePoints(lwo, &chunk[2], chunkSize);					break;
			case LWO_MAGIC_SRFS:	Lwo_ParseSurfaceNames(lwo, (LPUCHAR) &chunk[2], chunkSize);	break;
			case LWO_MAGIC_SURF:	Lwo_ParseSurfaceInfo(lwo, (LPUCHAR) &chunk[2], chunkSize);	break;
			case LWO_MAGIC_CRVS:	break;
			case LWO_MAGIC_POLS:	Lwo_ParsePolys(lwo, (LPUWORD) &chunk[2], chunkSize);		break;
			default:				Error_Warn(TRUE, Error_Format("Unknown chunk \"%.4s\" type in lwo file", &chunk[0]));		break;
			}
			bytepos += chunkSize + 8;
		}

		Mem_Free(fileData);

		{	// Assign the 'path' element of the object to the directory which contains it...
			LPUCHAR s, t;
			for (s=t=path ; '\0'!=*s ; s++) if ('\\' == *s) t = s;
			*t = '\0';
			if ('\0' == path[0]) lwo->path = NULL;
			else lwo->path = Mem_CopyString(path);
		}

		return lwo;
	}

	return NULL;
}

VOID Lwo_Free(lpLwo lwo) {

	ULONG loop;

	if (lwo->pointList) Mem_Free(lwo->pointList);
	if (lwo->normalList) Mem_Free(lwo->normalList);
	if (lwo->polyData) Mem_Free(lwo->polyData);
	if (lwo->polyList) Mem_Free(lwo->polyList);
	for (loop=0 ; loop<lwo->surfaceCount ; loop++) {
		if (lwo->surfaceList[loop].texture) Mem_Free(lwo->surfaceList[loop].texture);
	}
	if (lwo->surfaceList) Mem_Free(lwo->surfaceList);
	if (lwo->nameData) Mem_Free(lwo->nameData);
	if (lwo->path) Mem_Free(lwo->path);
	Mem_Free(lwo);
}

static VOID Lwo_ParsePoints(lpLwo lwo, LPULONG list, ULONG chunkSize) {

	ULONG loop;

	// Format:		[xpos][ypos][zpos]
	//				[IEEE][IEEE][IEEE]

	Error_Fatal(NULL!=lwo->pointList, "Points already parsed");
	Error_Fatal(0==chunkSize, "No points specified in lwo file");
	Error_Fatal(0!=chunkSize%(3*sizeof(ULONG)), "Invalid chunk size");

	lwo->pointCount = chunkSize / (3*sizeof(ULONG));
	lwo->pointList = Mem_Alloc(sizeof(VECTOR3D) * lwo->pointCount);

	for (loop=0 ; loop<lwo->pointCount ; loop++) {
		lwo->pointList[loop].x = LWO_REAL(list[(loop*3)+0]);
		lwo->pointList[loop].y = LWO_REAL(list[(loop*3)+1]);
		lwo->pointList[loop].z = LWO_REAL(list[(loop*3)+2]);
	}
}

static VOID Lwo_ParsePolys(lpLwo lwo, LPUWORD list, ULONG chunkSize) {

	ULONG loop, sub, index, polyDataIndex;
	lpLwoPoly poly;

	// Format:		[vcount][point0][point1][point2][...   ][surface]
	//				[UWORD ][UWORD ][UWORD ][UWORD ][UWORD ][UWORD  ]

	Error_Fatal(NULL!=lwo->polyList, "Polys already parsed");
	Error_Fatal(0==chunkSize, "No polygons specified in lwo file");
	Error_Fatal(0!=chunkSize%(sizeof(UWORD)), "Invalid chunk size");

	// First, run through and get a count of the polygons and edges.
	for (loop=0 ; loop<chunkSize/(sizeof(UWORD)) ; loop++) {
		lwo->polyDataSize += LWO_UWORD(list[loop]);
		lwo->polyCount++;
		loop += LWO_UWORD(list[loop]) + 1;		// Skip the face data and the surface index...
	}

	lwo->polyList = Mem_Alloc(sizeof(lwo->polyList[0]) * lwo->polyCount);
	lwo->polyData = Mem_Alloc(sizeof(lwo->polyData[0]) * lwo->polyDataSize);

	// Now fill in the data...
	polyDataIndex = index = 0;
	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		poly = &lwo->polyList[loop];
		poly->pointCount = LWO_UWORD(list[index]);
		index++;
		poly->polyIndex = polyDataIndex;
		for (sub=0 ; sub<poly->pointCount ; sub++) {
			lwo->polyData[polyDataIndex++] = LWO_UWORD(list[index]);
			index++;
		}
		poly->surface = LWO_UWORD(list[index]) - 1;			// Remap the surface index...

		Error_Fatal(lwo->surfaceList && poly->surface > lwo->surfaceCount, "Surface index does not exist");

		index++;
	}

	Error_Fatal(lwo->polyDataSize!=polyDataIndex, "PolyDataSize incorrect");
}

static VOID Lwo_ParseSurfaceNames(lpLwo lwo, LPUCHAR list, ULONG chunkSize) {

	ULONG loop, sindex = 0, nindex = 0;
	lpLwoSurface surface;

	Error_Fatal(NULL!=lwo->surfaceList, "Surface names already parsed");
	Error_Fatal(0==chunkSize, "No surfaces specified in lwo file");

	lwo->nameData = Mem_Alloc(chunkSize);
	Mem_Copy(lwo->nameData, list, chunkSize);

	// Count the number of surface in the object and create the buffer for them...
	// If the length of the string is even (odd with '\0'), then another '\0' will be added.
	for (loop=0 ; loop<chunkSize ; loop++) {
		if ('\0' == lwo->nameData[loop]) {
			lwo->surfaceCount++;
			if (0 == (loop %2)) {
				loop++;
				Error_Fatal('\0'!=lwo->nameData[loop], "Error in object file - missing padding");
			}
		}
	}
	lwo->surfaceList = Mem_AllocClear(sizeof(lwo->surfaceList[0]) * lwo->surfaceCount);

	// Point the name element of the surface structure into the name data...
	for (loop=0 ; loop<chunkSize ; loop++) {
		if ('\0' == lwo->nameData[loop]) {
			surface = &lwo->surfaceList[sindex++];
			surface->name = &lwo->nameData[nindex];
			if (0 == (loop % 2)) loop++;
			surface->nameSkip = (loop - nindex) + 1;
			nindex = loop+1;
		}
	}
}

static VOID Lwo_ParseSurfaceInfo(lpLwo lwo, LPUCHAR list, ULONG chunkSize) {

	LPULONG subChunk;
	ULONG loop, subIndex;
	lpLwoSurface surface;

	Error_Fatal(NULL==lwo->surfaceList, "Surface names have not been parsed");
	Error_Fatal(0==chunkSize, "No surface info specified in lwo file");

	// Assume that the 'Default' surface is index [0] and also may not
	// be included in the file, so fill in the data now...

	surface = &lwo->surfaceList[0];
//	surface->colour = 0x00c8c8c8;

	for (loop=0 ; loop<lwo->surfaceCount ; loop++) {
		surface = &lwo->surfaceList[loop];
		if (0 == strcmp(surface->name, list)) {
			for (subIndex=surface->nameSkip ; subIndex<chunkSize ; ) {
				subChunk = (LPULONG) &list[subIndex];
				Lwo_ParseSurfaceSubChunk(surface, subChunk[0], &subChunk[1]);

				// [sub chunk name skip] + [sub chunk len skip] + [sub chunk len]
				subIndex += sizeof(ULONG) + sizeof(UWORD) + LWO_UWORD(*((LPUWORD) &subChunk[1]));
/*				{
					UWORD temp = (LWO_ULONG(subChunk[1]) >> 16);
					subIndex += sizeof(ULONG) + sizeof(UWORD) + temp;
				}*/
			}
			break;		// Found it, so finish up...
		}
	}
}

static VOID Lwo_ParseSurfaceSubChunk(lpLwoSurface surface, ULONG type, LPULONG data) {

	LPUWORD uwData = (LPUWORD) data;
	UWORD size = LWO_UWORD(uwData[0]);

	switch (type) {
	case LWO_MAGIC_COLR:
		{	// convert the reversed rgba to argb
			ULONG alpha;
			surface->colour = LWO_ULONG(*((LPULONG) &uwData[1]));
			alpha = surface->colour & 0x000000ff;
			surface->colour = surface->colour >> 8;
			surface->colour |= alpha << 24;
		} break;

	case LWO_MAGIC_FLAG:	surface->flags = LWO_UWORD(uwData[1]);				break;
	case LWO_MAGIC_TFLG:
		{
			Error_Warn(surface->textureFlags & LWO_TEXTUREFLAG_WORLDCOORD, "World coordinate textures are not supported");
			surface->textureFlags = LWO_UWORD(uwData[1]);
		} break;

	case LWO_MAGIC_TSIZ:
		{
			surface->textureSize.x = LWO_REAL(((LPULONG) &uwData[1])[0]);
			surface->textureSize.y = LWO_REAL(((LPULONG) &uwData[1])[1]);
			surface->textureSize.z = LWO_REAL(((LPULONG) &uwData[1])[2]);
		} break;

	case LWO_MAGIC_TCTR:
		{
			surface->textureCenter.x = LWO_REAL(((LPULONG) &uwData[1])[0]);
			surface->textureCenter.y = LWO_REAL(((LPULONG) &uwData[1])[1]);
			surface->textureCenter.z = LWO_REAL(((LPULONG) &uwData[1])[2]);
		} break;

	case LWO_MAGIC_TIMG:
		{
//			surface->texture = Mem_Alloc(size);
//			Mem_Copy(surface->texture, (LPUCHAR) &uwData[1], size);

			LPUCHAR s, t = (LPUCHAR) &uwData[1];
			for (s=t ; '\0'!=*s ; s++) if ('\\' == *s) t = s+1;
			surface->texture = Mem_CopyString(t);

		} break;

	case LWO_MAGIC_TREF:	Error_Warn(TRUE, "Texture reference objects are not supported.");	break;

//	default:				Error_Warn(TRUE, Error_Format("Unused surface sub chunk '%c%c%c%c'", ((LPUCHAR) &type)[0], ((LPUCHAR) &type)[1], ((LPUCHAR) &type)[2], ((LPUCHAR) &type)[3]));
	}
}

static VOID Lwo_GenerateFaceNormals(lpLwo lwo) {

	ULONG loop;
	lpLwoPoly poly;

	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		poly = &lwo->polyList[loop];
		Maths_PlaneNormal(&poly->normal, &lwo->pointList[lwo->polyData[poly->polyIndex+0]], &lwo->pointList[lwo->polyData[poly->polyIndex+1]], &lwo->pointList[lwo->polyData[poly->polyIndex+2]]);
	}

}

VOID Lwo_GenerateNormals(lpLwo lwo) {

	ULONG loop, sub;
	lpLwoPoly poly;

	Error_Fatal(NULL!=lwo->normalList, "Normals already calculated");

	lwo->normalList = Mem_AllocClear(sizeof(lwo->normalList[0]) * lwo->pointCount);
	Lwo_GenerateFaceNormals(lwo);

	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		poly = &lwo->polyList[loop];
		for (sub=0 ; sub<poly->pointCount ; sub++) {
			Maths_Vector3DAdd(&lwo->normalList[lwo->polyData[poly->polyIndex+sub]], &lwo->normalList[lwo->polyData[poly->polyIndex+sub]], &poly->normal);
		}
	}

	// This gives an inaccurate vertex normal. If there are a large number of polygons with similar normals
	// all sharing the vertex, then the normal will be greatly stacked towards that normal...

	for (loop=0 ; loop<lwo->pointCount ; loop++) {
		Maths_Vector3DNormalise(&lwo->normalList[loop]);
	}
}

VOID Lwo_GetUV(lpLwoSurface surface, LPVECTOR3D point, LPREAL tu, LPREAL tv) {

	// Calculate the uv pair for any position from the surface data.
	VECTOR3D pos = { 0.0f, 0.0f, 0.0f };
	VECTOR2D textureSize = { 1.0f, 1.0f };

	Maths_Vector3DSubtract(&pos, point, &surface->textureCenter);
	pos.x /= surface->textureSize.x;
	pos.y /= surface->textureSize.y;
	pos.z /= surface->textureSize.z;

	// Determine which axis we are wrapping through.
	if (surface->textureFlags & LWO_TEXTUREFLAG_XAXIS) {
		*tu = pos.z;
		*tv = pos.y;
	} else if (surface->textureFlags & LWO_TEXTUREFLAG_YAXIS) {
		*tu = pos.x;
		*tv = pos.z;
	} else if (surface->textureFlags & LWO_TEXTUREFLAG_ZAXIS) {
		*tu = pos.x;
		*tv = pos.y;
	} else return;

	*tu += 0.5f;
	*tv += 0.5f;
	*tv = 1.0f - *tv;
}

static VOID Lwo_GetUV_Old(lpLwoSurface surface, LPVECTOR3D point, LPREAL tu, LPREAL tv) {

	// Calculate the uv pair for any position from the surface data.
	VECTOR3D pos = { 0.0f, 0.0f, 0.0f };
	VECTOR2D textureSize = { 1.0f, 1.0f };

	// Determine which axis we are wrapping through.
	if (surface->textureFlags & LWO_TEXTUREFLAG_XAXIS) {
		pos.x = point->z;
		pos.y = point->y;
		textureSize.x = surface->textureSize.z;
		textureSize.y = surface->textureSize.y;
	} else if (surface->textureFlags & LWO_TEXTUREFLAG_YAXIS) {
		pos.x = point->x;
		pos.y = point->z;
		textureSize.x = surface->textureSize.x;
		textureSize.y = surface->textureSize.z;
	} else if (surface->textureFlags & LWO_TEXTUREFLAG_ZAXIS) {
		pos.x = point->x;
		pos.y = point->y;
		textureSize.x = surface->textureSize.x;
		textureSize.y = surface->textureSize.y;
	} else return;

	Maths_Vector3DSubtract(&pos, &pos, &surface->textureCenter);
	pos.x /= textureSize.x;
	pos.y /= textureSize.y;
	pos.x += 0.5f;
	pos.y += 0.5f;
	pos.y = 1.0f - pos.y;

	*tu = pos.x;
	*tv = pos.y;
}

/*
lpMesh Lwo_BuildMesh(lpLwo lwo, ULONG blendLevels) {

	struct MeshVertexInfo vertexInfo;
	lpLwoSurface surface;
	lpLwoPoly poly;
	struct { LPULONG indexList; ULONG pointCount; } *pointData;
	ULONG vertexCount, surfaceID, loop, sub, point;
	lpMesh mesh;

	pointData = Mem_Alloc(sizeof(pointData[0]) * lwo->surfaceCount);
	for (surfaceID=0 ; surfaceID<lwo->surfaceCount ; surfaceID++) {
		pointData[surfaceID].indexList = Mem_Alloc(sizeof(pointData[surfaceID].indexList[0]) * lwo->pointCount);
		Mem_Set(pointData[surfaceID].indexList, 0xff, sizeof(pointData[surfaceID].indexList[0]) * lwo->pointCount);
		pointData[surfaceID].pointCount = 0;
	}

	// Remap the vertex data to split vertices that are in two ore more surfaces...

	for (surfaceID=0 ; surfaceID<lwo->surfaceCount ; surfaceID++) {
		surface = &lwo->surfaceList[loop];
		for (loop=0 ; loop<lwo->polyCount ; loop++) {
			poly = &lwo->polyList[loop];
			if (poly->surface == surfaceID) {
				if (3 == poly->pointCount) {
					for (sub=0 ; sub<poly->pointCount ; sub++) {
						point = lwo->polyData[poly->polyIndex + sub];
						if (-1 == pointData[surfaceID].indexList[point]) {
							pointData[surfaceID].indexList[point] = pointData[surfaceID].pointCount++;
						}
					}
				}
			}
		}
	}

	// Get the new vertex count and build the mesh...

	for (surfaceID=0 ; surfaceID<lwo->surfaceCount ; surfaceID++) vertexCount += pointData[surfaceID].pointCount;
	Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, MESH_VERTEXFLAG_NORMAL);
	mesh = Mesh_Create(lwo->polyCount, vertexCount, 0, &vertexInfo);

	// Set the vertex positions...

	vertexCount = 0;
	Mesh_LockVertices(mesh, TRUE);
	for (surfaceID=0 ; surfaceID<lwo->surfaceCount ; surfaceID++) {
		for (loop=0 ; loop<pointData[surfaceID].pointCount ; loop++) {
			if (-1 != pointData[surfaceID].listIndex[loop]) {
				Mesh_SetVertexPosition(mesh, vertexCount++, 
			}
		}
	}
	Mesh_LockVertices(mesh, FALSE);

	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		if (3 == lwo->polyCount) {
			ULONG list[3];
			for (sub=0 ; sub<3 ; sub++) {
				point = lwo->polyData[poly->polyIndex + sub];
				list[sub] = pointData[poly->surface].listIndex[point];
			}
			poly = &lwo->polyList[loop];
			Mesh_AddTriangle(mesh, poly->surface, &list);
		}
	}

	for (surfaceID=0 ; surfaceID<lwo->surfaceCount ; surfaceID++) Mem_Free(pointData[surfaceID].indexList);
	Mem_Free(pointData);

	return mesh;
}
*/

/*
lpMesh Lwo_BuildMesh(lpLwo lwo, ULONG maxVertexShare, ULONG blendLevels) {

	if (maxVertexShare) return Lwo_BuildMeshPolyUV(lwo, maxVertexShare, blendLevels);
	else return Lwo_BuildMeshVertexUV(lwo, blendLevels);

}

lpMesh Lwo_BuildMeshVertexUV(lpLwo lwo, ULONG blendLevels) {

	struct MeshVertexInfo vertexInfo;
	LPUWORD remapList = Mem_Alloc(sizeof(remapList[0]) * lwo->surfaceCount * lwo->pointCount);
	LPUWORD surfaceRemapList;
	ULONG loop, sub, point;
	UWORD totalPointCount = 0;
	lpLwoPoly poly;
	lpMesh mesh;

	memset(remapList, 0xff, sizeof(remapList[0]) * lwo->surfaceCount * lwo->pointCount);

	for (loop=0 ; loop<lwo->polyCount ; loop++) {

		poly = &lwo->polyList[loop];
		surfaceRemapList = &remapList[poly->surface * lwo->pointCount];

		for (sub=0 ; sub<poly->pointCount ; sub++) {

			point = lwo->polyData[poly->polyIndex + sub];
			if (0xffff == surfaceRemapList[point]) surfaceRemapList[point] = totalPointCount;
			totalPointCount++;
		}
	}

	Mesh_GetVertexInfo(&vertexInfo, FALSE, 0, blendLevels, MESH_VERTEXFLAG_NORMAL);
	mesh = Mesh_Create(lwo->polyCount, 0);
	Mesh_AddVertexList(mesh, totalPointCount, &vertexInfo);

	Mesh_LockVertices(mesh, TRUE);

	for (loop=0 ; loop<lwo->surfaceCount ; loop++) {
		for (sub=0 ; sub<lwo->pointCount ; sub++) {

			point = remapList[(loop * lwo->pointCount) + sub];
			
			if (0xffff != point) {
				Mesh_SetVertexPosition(mesh, 0, point, &lwo->pointList[sub]);
				Mesh_SetVertexNormal(mesh, 0, point, &lwo->normalList[sub]);
			}
		}
	}

	Mesh_LockVertices(mesh, FALSE);

	Mem_Free(remapList);

	return NULL;
}
*/

/*
lpMesh Lwo_BuildMeshVertexUV(lpLwo lwo, ULONG blendLevels) {

	REAL tu, tv;
	ULONG surface;
	UWORD sub, groupID, vcount, loop, groupPolys, basePoly, checkedPolys;
	ULONG vertexListID;
	LPUWORD vertexIndexBuffer = Mem_Alloc(sizeof(vertexIndexBuffer[0]) * lwo->pointCount);
	lpLwoPoly poly;
	lpMesh mesh;

	mesh = Mesh_Create(lwo->polyCount, 0, TRUE);

	for (surface=0 ; surface<lwo->surfaceCount ; surface++) {

		basePoly = 0;
		
		while (basePoly < lwo->polyCount) {

			// Clear the list that indicates which verticies in the lwo are going to be used by this group...
			memset(vertexIndexBuffer, 0xff, sizeof(UWORD) * lwo->pointCount);

			// Count the number of vertices that will be used by the group, then create it...
			groupPolys = 0;
			for (loop=basePoly ; loop<lwo->polyCount ; loop++) {
				poly = &lwo->polyList[loop];
				
				if (poly->surface == surface) {

					for (sub=0 ; sub<3 ; sub++) vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]] = 0;

					// If the limit has been reached on the number of polys allowed, then stop here...
					groupPolys++;
				}
			}
			checkedPolys = loop + 1;
			
			// Count how many vertices where referenced by the faces of this surface type.
			// While we're at it, store what the index number of the new vertex is going to be...
			for (vcount=loop=0 ; loop<lwo->pointCount ; loop++) if (0xffff != vertexIndexBuffer[loop]) vertexIndexBuffer[loop] = vcount++;
			
			{ // Create the new group on the mesh...

				struct MeshVertexInfo vertexInfo;
			
//				Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, MESH_VERTEXFLAG_NORMAL|MESH_VERTEXFLAG_DIFFUSE);
//				Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, MESH_VERTEXFLAG_NORMAL);
				Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, MESH_VERTEXFLAG_DIFFUSE);
//				Mesh_GetVertexInfo(&vertexInfo, FALSE, 1, blendLevels, 0);
				vertexListID = Mesh_AddVertexList(mesh, vcount, &vertexInfo);
				groupID = Mesh_CreateGroup(mesh, vertexListID, 3, groupPolys);
			}
	
			if (lwo->surfaceList[surface].texture) {

				UCHAR path[FILE_MAXPATH];
				
				if (lwo->path) sprintf(path, "%s\\%s", lwo->path, lwo->surfaceList[surface].texture);
				else sprintf(path, "%s", lwo->surfaceList[surface].texture);

#pragma message ( "Using .bmp instead of .tim" )
			
				if (File_GetSuffix(path) && 0 == stricmp(File_GetSuffix(path), "tim")) {
					sprintf(&path[strlen(path) - 4], ".bmp");
				}

				Mesh_SetTexture(mesh, groupID, 0, Texture_Load(path, TRUE));

			} else {
//				Mesh_SetGroupColour(mesh, groupID,
//					COLOUR_GETREALRED(lwo->surfaceList[surface].colour), 
//					COLOUR_GETREALGREEN(lwo->surfaceList[surface].colour), 
//					COLOUR_GETREALBLUE(lwo->surfaceList[surface].colour));
			}

			Mesh_LockVertices_Index(mesh, vertexListID, TRUE);
			
			// Set the vertex positions (and normals) in the mesh group...
			for (loop=0 ; loop<lwo->pointCount ; loop++) {
				if (0xffff != vertexIndexBuffer[loop]) {

					lpTexture texture;

					if (lwo->surfaceList[surface].texture) {
						Mesh_SetVertexColour(mesh, vertexListID, vertexIndexBuffer[loop], 0xffffffff);
					} else {
						Mesh_SetVertexColour(mesh, vertexListID, vertexIndexBuffer[loop], lwo->surfaceList[surface].colour);
					}


					Mesh_SetVertexPosition(mesh, vertexListID, vertexIndexBuffer[loop], &lwo->pointList[loop]);
//					Mesh_SetVertexNormal(mesh, vertexListID, vertexIndexBuffer[loop], &lwo->normalList[loop]);

//					{
//						COLOUR colour = ((rand() << 16) | rand()) | 0xa0a0a0a0;
//						Mesh_SetVertexColour(mesh, vertexListID, vertexIndexBuffer[loop], colour);
//					}
					
					Lwo_GetUV(&lwo->surfaceList[surface], &lwo->pointList[loop], &tu, &tv);
					if (texture = Mesh_GetTexture(mesh, groupID, 0)) {

						VECTOR2D offset = { (1.0f / Texture_GetWidth(texture)) / 2.0f, (1.0f / Texture_GetHeight(texture)) / 2.0f };

						tu = Maths_Interpolate(offset.x, 1.0f - offset.x, tu);
						tv = Maths_Interpolate(offset.y, 1.0f - offset.y, tv);
					}
					Mesh_SetVertexUV(mesh, vertexListID, vertexIndexBuffer[loop], 0, tu, tv);

				}
			}

			Mesh_LockVertices_Index(mesh, vertexListID, FALSE);

			// Go through the polygons adding them to the mesh group...
			groupPolys = 0;
			for (loop=basePoly ; loop<lwo->polyCount ; loop++) {
				UWORD face[3];
				poly = &lwo->polyList[loop];
				if (poly->surface == surface) {
					for (sub=0 ; sub<3 ; sub++) face[sub] = vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]];
					Mesh_AddTriangle(mesh, groupID, face);
					groupPolys++;
				}
			}

			basePoly = checkedPolys;
		}
	}

	Mem_Free(vertexIndexBuffer);

	return mesh;
}

lpMesh Lwo_BuildMeshPolyUV(lpLwo lwo, ULONG maxVertexShare, ULONG blendLevels) {

#pragma message ( "Incorrect meshes generate by this method in non-debug builds" )

	// Generate the mesh using multiple uv's per vertex...
	// Use SetTextureStageState() with D3DTSS_TEXCOORDINDEX to select set of uv's to use for the poly.

	REAL tu[3], tv[3];
	ULONG surface;
	UWORD sub, loop;
	lpLwoPoly poly;
	struct MeshVertexInfo vertexInfo;
	lpMesh mesh;

	Mesh_GetVertexInfo(&vertexInfo, FALSE, maxVertexShare, blendLevels, MESH_VERTEXFLAG_NORMAL);
	mesh = Mesh_Create(lwo->polyCount, maxVertexShare, FALSE);
	Mesh_AddVertexList(mesh, lwo->pointCount, &vertexInfo);
	Mesh_LockVertices(mesh, TRUE);

	for (loop=0 ; loop<lwo->pointCount ; loop++) {
		Mesh_SetVertexPosition(mesh, 0, loop, &lwo->pointList[loop]);
		Mesh_SetVertexNormal(mesh, 0, loop, &lwo->normalList[loop]);
	}

	for (surface=0 ; surface<lwo->surfaceCount ; surface++) {

		UWORD polyCount = 0;

		for (loop=0 ; loop<lwo->polyCount ; loop++) {
			poly = &lwo->polyList[loop];
			if (poly->surface == surface) polyCount++;
		}

		Mesh_CreateGroup(mesh, 0, 3, polyCount);

		if (lwo->surfaceList[surface].texture) {

			UCHAR path[FILE_MAXPATH];
			
			if (lwo->path) sprintf(path, "%s\\%s", lwo->path, lwo->surfaceList[surface].texture);
			else sprintf(path, "%s", lwo->surfaceList[surface].texture);
			Mesh_SetTexture(mesh, surface, 0, Texture_Load(path, TRUE));
		}
	}

	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		poly = &lwo->polyList[loop];
		Mesh_AddTriangle(mesh, poly->surface, &lwo->polyData[poly->polyIndex]);
		for (sub=0 ; sub<3 ; sub++) Lwo_GetUV(&lwo->surfaceList[poly->surface], &lwo->pointList[lwo->polyData[poly->polyIndex + sub]], &tu[sub], &tv[sub]);

#pragma message ( "Need to assign the index of the UV set to use" )
		Mesh_SetPolyUV(mesh, 0, loop, 0, tu, tv);
	}

	Mesh_LockVertices(mesh, FALSE);

	return mesh;
}
*/

/*
lpMesh Lwo_BuildMesh(lpLwo lwo, ULONG polysPerGroup) {

	REAL tu, tv;
	ULONG surface;
	UWORD sub, groupID, vcount, loop, groupPolys, basePoly, checkedPolys;
	LPUWORD vertexIndexBuffer = Mem_Alloc(sizeof(UWORD) * lwo->pointCount);
	lpLwoPoly poly;
	lpMesh mesh = Mesh_Create(lwo->polyCount, 0);		// A non-uv mapped object (one uv per vertex)

	for (surface=0 ; surface<lwo->surfaceCount ; surface++) {
		basePoly = 0;
		while (basePoly < lwo->polyCount) {

			// Clear the list that indicates which verticies in the lwo are going to be used by this group...
			memset(vertexIndexBuffer, 0xff, sizeof(UWORD) * lwo->pointCount);

			// Count the number of vertices that will be used by the group, then create it...
			groupPolys = 0;
			for (loop=basePoly ; loop<lwo->polyCount ; loop++) {
				poly = &lwo->polyList[loop];
				Error_Fatal(3!=poly->pointCount, "Non-triangulated polygons not supported");
				if (poly->surface == surface) {
					for (sub=0 ; sub<3 ; sub++) vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]] = 0;

					// If the limit has been reached on the number of polys allowed, then stop here...
					groupPolys++;
					if (0 != polysPerGroup && groupPolys == polysPerGroup) break;
				}
			}
			checkedPolys = loop + 1;
			
			// Count how many vertices where referenced by the faces of this surface type.
			// While we're at it, store what the index number of the new vertex is going to be...
			for (vcount=loop=0 ; loop<lwo->pointCount ; loop++) if (0xffff != vertexIndexBuffer[loop]) vertexIndexBuffer[loop] = vcount++;
			
			// Create the new group on the mesh...
			groupID = Mesh_CreateGroup(mesh, 3, vcount, groupPolys);
			if (lwo->surfaceList[surface].texture) {
				UCHAR path[FILE_MAXPATH];
				if (lwo->path) sprintf(path, "%s\\%s", lwo->path, lwo->surfaceList[surface].texture);
				else sprintf(path, "%s", lwo->surfaceList[surface].texture);
				Mesh_SetTexture(mesh, groupID, Texture_Load(path, TRUE));
			}
			
			// Set the vertex positions (and normals) in the mesh group...
			for (loop=0 ; loop<lwo->pointCount ; loop++) {
				if (0xffff != vertexIndexBuffer[loop]) {
					Mesh_SetVertexPosition(mesh, groupID, vertexIndexBuffer[loop], &lwo->pointList[loop]);
					Mesh_SetVertexNormal(mesh, groupID, vertexIndexBuffer[loop], &lwo->normalList[loop]);
					Lwo_GetUV(&lwo->surfaceList[surface], &lwo->pointList[loop], &tu, &tv);
					Mesh_SetVertexUV(mesh, groupID, vertexIndexBuffer[loop], tu, tv);

//					{
//						UCHAR r = rand() | 0x80;
//						UCHAR g = rand() | 0x80;
//						UCHAR b = rand() | 0x80;
//						Mesh_SetVertexColour(mesh, groupID, vertexIndexBuffer[loop], (r<<16)|(g<<8)|b);
//					}
				}
			}

			// Go through the polygons adding them to the mesh group...
			groupPolys = 0;
			for (loop=basePoly ; loop<lwo->polyCount ; loop++) {
				UWORD face[3];
				poly = &lwo->polyList[loop];
				if (poly->surface == surface) {
					for (sub=0 ; sub<3 ; sub++) face[sub] = vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]];
					Mesh_AddTriangle(mesh, groupID, face);
					groupPolys++;
					if (0 != polysPerGroup && groupPolys == polysPerGroup) break;
				}
			}

			basePoly = checkedPolys;
		}
	}

	Mem_Free(vertexIndexBuffer);

//	Mesh_GenerateFaceNormals(mesh);
	return mesh;
}
*/


/*
lpMesh Lwo_BuildMesh(lpLwo lwo, ULONG polysPerGroup) {

	ULONG basePoly = 0;
	UWORD sub, groupID, vcount, loop, groupPolys;
	LPUWORD vertexIndexBuffer = Mem_Alloc(sizeof(UWORD) * lwo->pointCount);
	lpLwoPoly poly;
	lpMesh mesh = Mesh_Create(lwo->polyCount, 0);

	while (basePoly < lwo->polyCount) {
		memset(vertexIndexBuffer, 0xff, sizeof(UWORD) * lwo->pointCount);
		groupPolys = (UWORD) min(polysPerGroup, lwo->polyCount - basePoly);

		// Count the number of vertices that will be used by the group, the create it...
		for (loop=0 ; loop<groupPolys ; loop++) {
			poly = &lwo->polyList[basePoly + loop];
			Error_Fatal(3!=poly->pointCount, "Non-triangulated polygons not supported");
			for (sub=0 ; sub<3 ; sub++) vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]] = 0;
		}
		for (vcount=loop=0 ; loop<lwo->pointCount ; loop++) if (0xffff != vertexIndexBuffer[loop]) vertexIndexBuffer[loop] = vcount++;
		groupID = Mesh_CreateGroup(mesh, 3, vcount, groupPolys);

		// Set the vertex positions (and normals) in the mesh group...
		for (loop=0 ; loop<lwo->pointCount ; loop++) {
			if (0xffff != vertexIndexBuffer[loop]) {
				Mesh_SetVertexPosition(mesh, groupID, vertexIndexBuffer[loop], &lwo->pointList[loop]);
				Mesh_SetVertexNormal(mesh, groupID, vertexIndexBuffer[loop], &lwo->normalList[loop]);
//				Mesh_SetVertexColour(mesh, groupID, vertexIndexBuffer[loop], 0x00ffffff);
			}
		}

		// Go through the polygons adding them to the mesh group...
		for (loop=0 ; loop<groupPolys ; loop++) {
			UWORD face[3];
			poly = &lwo->polyList[basePoly + loop];
			for (sub=0 ; sub<3 ; sub++) face[sub] = vertexIndexBuffer[lwo->polyData[poly->polyIndex + sub]];
			Mesh_AddTriangle(mesh, groupID, face);
		}

		basePoly += groupPolys;
	}

	Mesh_GenerateFaceNormals(mesh);
	Mem_Free(vertexIndexBuffer);

	return mesh;
}
*/




// no need to do this, just build up the mesh splitting vertices by copying...
// need to bunch textured surfaces together into groups though....

/*
VOID Lwo_SplitSurfaces(lpLwo lwo, ULONG maxSharedUVs) {

	// Spilt the surfaces of the object up, retaining the current vertex normals...
	// If 'plainColoursOnly' is specified, only split out non-textured surfaces,
	// otherwise, split all the surfaces up...

	ULONG loop, sub, check, vindex, sharedUVs, remapTo, vlistend = lwo->pointCount;
//	lpLwo_SplitSurfaceData data;
	lpLwoSurface surface;
	lpLwoPoly poly;
	BOOL already;

	// Allocate enough memory for every polygon to have its own set of vertices...
	LPVECTOR3D vBuffer = Mem_Alloc(sizeof(VECTOR3D) * lwo->polyDataSize);
	LPVECTOR3D nBuffer = Mem_Alloc(sizeof(VECTOR3D) * lwo->polyDataSize);

	// Allocate a list of which surfaces use each vertex...
//	data = Mem_AllocClear(sizeof(Lwo_SplitSurfaceData) * lwo->pointCount);

	Lwo_SplitSurfaceData data[10];
	{
		memset(data, 0, sizeof(data));
	}

	for (loop=0 ; loop<lwo->polyCount ; loop++) {
		poly = &lwo->polyList[loop];
		for (sub=0 ; sub<poly->pointCount ; sub++) {
			vindex = lwo->polyData[poly->polyIndex + sub];
			already = FALSE;
			for (check=0 ; check<data[vindex].sharingCount ; check++) {
				if (data[vindex].sharingSurfaces[check] == poly->surface) already = TRUE;
			}
			if (!already) {
				Error_Overflow(data[vindex].sharingCount, LWO_MAXVERTEXSURFACE);
				data[vindex].sharingSurfaces[data[vindex].sharingCount] = poly->surface;
				data[vindex].sharingCount++;
			}
		}
	}

	// Set the data up to reflect which points need to be split and where to...
	for (vindex=0 ; vindex<lwo->pointCount ; vindex++) {
		sharedUVs = 0;
		remapTo = 0;
		for (check=0 ; check<data[vindex].sharingCount ; check++) {
			surface = &lwo->surfaceList[data[vindex].sharingSurfaces[check]];
			if (NULL == surface->texture) {
				if (0 == check) remapTo = vlistend++;
				else data[vindex].remapVertex[check] = vlistend++;			// No texture (solid colour) - force splitting...
			} else {
				if (sharedUVs++ == maxSharedUVs) {
					remapTo = vlistend++;
					sharedUVs = 0;
				}
				data[vindex].remapVertex[check] = remapTo;
			}
		}
	}

	// Duplicate the vertices and normals...

	// Remap the polygons...

	// Free up the temporary buffers...
//	Mem_Free(data);
}
*/