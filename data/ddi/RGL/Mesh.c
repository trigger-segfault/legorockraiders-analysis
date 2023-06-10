
#include "Standard.h"
#include "Textures.h"
#include "DirectX.h"
#include "Errors.h"
#include "Render.h"
#include "Frames.h"
#include "Files.h"
#include "Lists.h"
#include "Lwo.h"
#include "Lws.h"
#include "Mem.h"
#include "Mesh.h"
#include "UView.h"
#include "Lights.h"
#include "ModelClip.h"

struct MeshGlobs {

	struct List *list;
	struct List *sharedObjectList;

	struct MeshRenderEntry renderList[MESH_RENDERLISTSIZE];
	ULONG renderCount;

} meshGlobs = { 0 };

VOID Mesh_Initialise(VOID) {

	meshGlobs.list = List_Create(sizeof(struct Mesh));
	meshGlobs.sharedObjectList = File_CreateSharedObjectList();
}

#ifdef _DEBUG
BOOL Mesh_ShutdownCallback(lpMesh mesh, LPVOID data) {

	Error_Warn(TRUE, Error_Format("Unremoved mesh 0x%0.8x (%d reference%s)", mesh, mesh->referenceCount, (1==mesh->referenceCount)?"":"s"));

	return FALSE;
}
#endif // _DEBUG

VOID Mesh_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(meshGlobs.list, Mesh_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(meshGlobs.list);
	meshGlobs.list = NULL;
	File_RemoveSharedObjectList(meshGlobs.sharedObjectList);
	meshGlobs.sharedObjectList = NULL;
}

VOID Mesh_GetVertexInfo(lpMeshVertexInfo info, BOOL transformed, ULONG textureCount, ULONG blendCount, ULONG flags) {

	info->size = 0;
	info->srcFlags = 0;
	info->destFlags = 0;
	info->blendCount = blendCount;
	info->uvCount = textureCount;
	
	if (transformed) {
		Error_Fatal(blendCount, "Cannot have blended transformed vertices");
		Error_Fatal(flags & MESH_VERTEXFLAG_NORMAL, "Transformed vertices cannot have a normal");
		info->srcFlags |= D3DFVF_XYZRHW;
		info->size += sizeof(VECTOR4D);
		info->destFlags |= 0xffffffff;		// Cannot transform transformed vertices...
	} else {
		switch (blendCount) {
		case 0: info->srcFlags |= D3DFVF_XYZ;	break;
		case 1: info->srcFlags |= D3DFVF_XYZB1;	break;
		case 2: info->srcFlags |= D3DFVF_XYZB2;	break;
		case 3: info->srcFlags |= D3DFVF_XYZB3;	break;
		case 4: info->srcFlags |= D3DFVF_XYZB4;	break;
		case 5: info->srcFlags |= D3DFVF_XYZB5;	break;
		default: Error_Fatal(TRUE, "Too many blending levels");
		}
		info->destFlags |= D3DFVF_XYZRHW;
		info->size += sizeof(VECTOR3D);
		info->blendPos = info->size;
		info->size += sizeof(REAL) * blendCount;
	}

	if (flags & MESH_VERTEXFLAG_NORMAL) {
		info->srcFlags |= D3DFVF_NORMAL;
		info->destFlags |= D3DFVF_DIFFUSE;
		info->normalPos = info->size;
		info->size += sizeof(VECTOR3D);
	}
	if (flags & MESH_VERTEXFLAG_DIFFUSE) {
		info->srcFlags |= D3DFVF_DIFFUSE;
		info->destFlags |= D3DFVF_DIFFUSE;
		info->diffusePos = info->size;
		info->size += sizeof(ULONG);
	}
	if (flags & MESH_VERTEXFLAG_SPECULAR) {
		info->srcFlags |= D3DFVF_SPECULAR;
		info->destFlags |= D3DFVF_SPECULAR;
		info->specularPos = info->size;
		info->size += sizeof(ULONG);
	}

	switch (textureCount) {
	case 0: info->srcFlags |= D3DFVF_TEX0; info->destFlags |= D3DFVF_TEX0;		break;
	case 1: info->srcFlags |= D3DFVF_TEX1; info->destFlags |= D3DFVF_TEX1;		break;
	case 2: info->srcFlags |= D3DFVF_TEX2; info->destFlags |= D3DFVF_TEX2;		break;
	case 3: info->srcFlags |= D3DFVF_TEX3; info->destFlags |= D3DFVF_TEX3;		break;
	case 4: info->srcFlags |= D3DFVF_TEX4; info->destFlags |= D3DFVF_TEX4;		break;
	case 5: info->srcFlags |= D3DFVF_TEX5; info->destFlags |= D3DFVF_TEX5;		break;
	case 6: info->srcFlags |= D3DFVF_TEX6; info->destFlags |= D3DFVF_TEX6;		break;
	case 7: info->srcFlags |= D3DFVF_TEX7; info->destFlags |= D3DFVF_TEX7;		break;
	case 8: info->srcFlags |= D3DFVF_TEX8; info->destFlags |= D3DFVF_TEX8;		break;
	default: Error_Fatal(TRUE, "Maximum of 8 textures allowed");
	}
	info->uvPos = info->size;
	info->size += sizeof(VECTOR2D) * textureCount;
}

ULONG Mesh_AddVertexList(lpMesh mesh, ULONG vertexCount, lpMeshVertexInfo vertexInfo) {

	lpMeshVertexList list;
	D3DVERTEXBUFFERDESC vbDesc;
	ULONG index;
	HRESULT r;

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexCount > MAX_UWORD, "Too many vertices specified");

	index = mesh->vertexListCount++;
	mesh->vertexListList = Mem_ReAlloc(mesh->vertexListList, sizeof(mesh->vertexListList[0]) * mesh->vertexListCount);
	
	list = &mesh->vertexListList[index];
	Mem_Set(list, 0, sizeof(*list));

	list->totalVertexCount = (UWORD) vertexCount;
	if (mesh->maxVertexShare) list->totalVertexCount *= 8;
	list->usedVertexCount = (UWORD) vertexCount;
	list->internallyUsedVertexCount = (UWORD) vertexCount;
	list->visibleVertexCount = 0;

	if (mesh->maxVertexShare) {
		list->vertexRefCount = Mem_AllocClear(sizeof(list->vertexRefCount[0]) * list->totalVertexCount);
		list->vertexRemapData = Mem_AllocClear(sizeof(list->vertexRemapData[0]) * list->totalVertexCount);
	}

	DirectX_InitStruct(&vbDesc);
	if (!DirectX_HardwareTnL()) vbDesc.dwCaps = D3DVBCAPS_SYSTEMMEMORY;
	vbDesc.dwFVF = vertexInfo->srcFlags;
	vbDesc.dwNumVertices = list->totalVertexCount;

	r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &list->vertexBuffer, 0);
	Error_DirectX(r, "CreateVertexBuffer");

	DirectX_InitStruct(&vbDesc);
	if (!DirectX_HardwareTnL()) vbDesc.dwCaps = D3DVBCAPS_SYSTEMMEMORY;
	vbDesc.dwFVF = vertexInfo->destFlags;
	vbDesc.dwNumVertices = list->totalVertexCount;
	r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &list->transformedVertexBuffer, 0);
	Error_DirectX(r, "CreateVertexBuffer");

	list->vertexInfo = *vertexInfo;

	return index;
}

VOID Mesh_Optimise(lpMesh mesh) {

	if (!(mesh->flags & MESH_FLAG_OPTIMISED)) {

		lpMeshVertexList meshVertexList;
		ULONG loop;
		HRESULT r;

		List_CheckItem(meshGlobs.list, mesh);

		for (loop=0 ; loop<mesh->vertexListCount ; loop++) {
			
			meshVertexList = &mesh->vertexListList[loop];
		
			r = meshVertexList->vertexBuffer->lpVtbl->Optimize(meshVertexList->vertexBuffer, DirectX_Device(), 0);
			Error_DirectX(r, "Optimize");
		}

		mesh->flags |= MESH_FLAG_OPTIMISED;

	}
}

/*
lpMesh Mesh_Create(ULONG totalFaceCount, ULONG vertexCount, ULONG maxVertexShare, lpMeshVertexInfo vertexInfo) {
*/

lpMesh Mesh_Create(ULONG totalFaceCount, ULONG maxVertexShare, BOOL multiReference) {

	lpMesh mesh = List_ObtainItem(meshGlobs.list);

	Error_Fatal(totalFaceCount > MAX_UWORD, "Too many faces specified");

	mesh->referenceCount = 1;
	if (multiReference) mesh->flags |= MESH_FLAG_MULTIREFERENCE;

	mesh->totalFaceCount = (UWORD) totalFaceCount;
	mesh->faceArray = Mem_AllocClear(sizeof(mesh->faceArray[0]) * mesh->totalFaceCount);

	mesh->maxVertexShare = maxVertexShare;

	return mesh;
}

static BOOL Mesh_CopyVertexBuffer(LPDIRECT3DVERTEXBUFFER7 dest, LPDIRECT3DVERTEXBUFFER7 src, lpMeshVertexInfo info, ULONG destStart, ULONG srcStart, ULONG count) {

	LPUCHAR srcData, destData;
	ULONG srcSize, destSize;
	BOOL ok = FALSE;
	ULONG flags;

	Error_Fatal(dest == src && (0 == count || 
		!((destStart >= srcStart + count) || (destStart + count <= srcStart))), 
		"Source and destination overlap");

	flags = DDLOCK_WAIT;
	if (dest != src) flags |= DDLOCK_READONLY;

	if (D3D_OK == src->lpVtbl->Lock(src, flags, &srcData, &srcSize)) {

		flags = DDLOCK_WAIT|DDLOCK_WRITEONLY;
		if (0 == count) flags |= DDLOCK_DISCARDCONTENTS;

		if (dest == src || D3D_OK == dest->lpVtbl->Lock(dest, flags, &destData, &destSize)) {

			ULONG copySrcStart, copyDestStart, copySize;
			
			if (dest == src) destData = srcData;

			copySrcStart = (srcStart * info->size);
			copyDestStart = (destStart * info->size);

			if (count) copySize = count * info->size;
			else copySize = srcSize - copySrcStart;

			if (copySrcStart + copySize <= srcSize &&
				copyDestStart + copySize <= destSize) {

				Mem_Copy(&destData[copyDestStart], &srcData[copySrcStart], copySize);
				ok = TRUE;
			}

			dest->lpVtbl->Unlock(dest);
		}
		src->lpVtbl->Unlock(src);
	}

	return ok;
}

lpMesh Mesh_Clone(lpMesh original, ULONG flags) {

	// Creates a partial or complete clone of a mesh depending upon the flags specified:
	// MESH_CLONEFLAG_HIDDENFACEDATA		-		Create new hidden face data. i.e. Allow both the objects to be clipped independantly.
	// MESH_CLONEFLAG_GROUPS				-		Create a copy of the group data (Allow texture/attribute changes).
	// MESH_CLONEFLAG_FACEDATA				-		Create a copy of the face data (probably no use without MESH_CLONEFLAG_VERTICES set).
	// MESH_CLONEFLAG_VERTICES				-		Create a copy of all the vertex data.
	// MESH_CLONEFLAG_TRANSFORMEDVERTICES	-		Create a copy of the transformed vertex data.
	// MESH_CLONEFLAG_ADDFACES				-		Allows new faces to be added (copys everything but the hidden face data).
	// MESH_CLONEFLAG_COMPLETE				-		Create a complete copy of the entire object.
	// MESH_CLONEFLAG_VERTEXLISTLIST		-		Copy the vertexListList (internal)

	lpMesh mesh = List_ObtainItem(meshGlobs.list);
	lpMeshGroup group, originalGroup;
	lpMeshVertexList originalVertexList, meshVertexList;
	D3DVERTEXBUFFERDESC vbDesc;
	ULONG loop;
	HRESULT r;
	BOOL ok;

	List_CheckItem(meshGlobs.list, original);
	Error_Warn(NULL!=original->clonedFrom, "Cloning an already cloned mesh - hope you understand what you are doing");
	Error_Fatal(0==flags, "No flags specified");
	Error_Fatal(NULL==original->faceArray||NULL==original->groupList, "Mesh to be duplicated doesn't appear to be initialised");
	Error_Fatal((flags & MESH_CLONEFLAG_ADDFACES) && (flags & MESH_CLONEFLAG_HIDDENFACEDATA), "Use MESH_CLONEFLAG_COMPLETE instead of (MESH_CLONEFLAG_ADDFACES|MESH_CLONEFLAG_HIDDENFACEDATA)");
	Error_Fatal((flags & MESH_CLONEFLAG_TRANSFORMEDVERTICES) && 1 == mesh->groupCount, "No need to clone transformed vertices on meshes with only one group");

	if (flags & MESH_CLONEFLAG_COMPLETE) flags |= (MESH_CLONEFLAG_HIDDENFACEDATA|MESH_CLONEFLAG_GROUPS|MESH_CLONEFLAG_FACEDATA|MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES);
	if (flags & MESH_CLONEFLAG_ADDFACES) flags |= (MESH_CLONEFLAG_GROUPS|MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES|MESH_CLONEFLAG_FACEDATA);
	if (flags & MESH_CLONEFLAG_HIDDENFACEDATA) flags |= MESH_CLONEFLAG_GROUPS;

	if ((flags & MESH_CLONEFLAG_HIDDENFACEDATA) ||
		(flags & MESH_CLONEFLAG_VERTICES) ||
		(flags & MESH_CLONEFLAG_TRANSFORMEDVERTICES) ||
		(flags & MESH_CLONEFLAG_ADDFACES)) flags |= MESH_CLONEFLAG_VERTEXLISTLIST;

	*mesh = *original;
	mesh->referenceCount = 1;

	if (flags & MESH_CLONEFLAG_VERTEXLISTLIST) mesh->vertexListList = Mem_Duplicate(original->vertexListList);

	if (flags & MESH_CLONEFLAG_HIDDENFACEDATA) {
		mesh->faceArray = Mem_Duplicate(original->faceArray);
		for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

			originalVertexList = &original->vertexListList[loop];
			meshVertexList = &mesh->vertexListList[loop];

			if (originalVertexList->vertexIncludedData) meshVertexList->vertexIncludedData = Mem_Duplicate(originalVertexList->vertexIncludedData);
		}
	}

	if (flags & MESH_CLONEFLAG_VERTICES) {

		for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

			originalVertexList = &original->vertexListList[loop];
			meshVertexList = &mesh->vertexListList[loop];

			DirectX_InitStruct(&vbDesc);
			r = originalVertexList->vertexBuffer->lpVtbl->GetVertexBufferDesc(originalVertexList->vertexBuffer, &vbDesc);
			Error_DirectX(r, "GetVertexBufferDesc");
			r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &meshVertexList->vertexBuffer, 0);
			Error_DirectX(r, "CreateVertexBuffer");
			ok = Mesh_CopyVertexBuffer(meshVertexList->vertexBuffer, originalVertexList->vertexBuffer, &meshVertexList->vertexInfo, 0, 0, 0);
			Error_Fatal(!ok, "Vertex buffer copy failed");

			if (originalVertexList->visibleVertexBuffer) {
				DirectX_InitStruct(&vbDesc);
				r = originalVertexList->visibleVertexBuffer->lpVtbl->GetVertexBufferDesc(originalVertexList->visibleVertexBuffer, &vbDesc);
				Error_DirectX(r, "GetVertexBufferDesc");
				r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &meshVertexList->visibleVertexBuffer, 0);
				Error_DirectX(r, "CreateVertexBuffer");
				ok = Mesh_CopyVertexBuffer(meshVertexList->visibleVertexBuffer, originalVertexList->visibleVertexBuffer, &meshVertexList->vertexInfo, 0, 0, 0);
				Error_Fatal(!ok, "Vertex buffer copy failed");
			}
		}

	} else {
		for (loop=0 ; loop<original->vertexListCount ; loop++) {
			
			originalVertexList = &original->vertexListList[loop];

			originalVertexList->vertexBuffer->lpVtbl->AddRef(originalVertexList->vertexBuffer);
			if (originalVertexList->visibleVertexBuffer) originalVertexList->visibleVertexBuffer->lpVtbl->AddRef(originalVertexList->visibleVertexBuffer);
		}
	}

	for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

		originalVertexList = &original->vertexListList[loop];
		meshVertexList = &mesh->vertexListList[loop];

		if (originalVertexList->transformedVertexBuffer) {
			if (flags & MESH_CLONEFLAG_TRANSFORMEDVERTICES) {
				DirectX_InitStruct(&vbDesc);
				r = originalVertexList->transformedVertexBuffer->lpVtbl->GetVertexBufferDesc(originalVertexList->transformedVertexBuffer, &vbDesc);
				Error_DirectX(r, "GetVertexBufferDesc");
				r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &meshVertexList->transformedVertexBuffer, 0);
				Error_DirectX(r, "CreateVertexBuffer");
			} else {
				originalVertexList->transformedVertexBuffer->lpVtbl->AddRef(originalVertexList->transformedVertexBuffer);
			}
		}
	}
	
	if ((flags & MESH_CLONEFLAG_ADDFACES) && mesh->maxVertexShare) {
		for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

			originalVertexList = &original->vertexListList[loop];
			meshVertexList = &mesh->vertexListList[loop];

			meshVertexList->vertexRemapData = Mem_Duplicate(originalVertexList->vertexRemapData);
			meshVertexList->vertexRefCount = Mem_Duplicate(originalVertexList->vertexRefCount);
		}
	}

	if (flags & MESH_CLONEFLAG_GROUPS) {

		mesh->groupList = Mem_Duplicate(original->groupList);

		for (loop=0 ; loop<mesh->groupCount ; loop++) {

			group = &mesh->groupList[loop];
			originalGroup = &original->groupList[loop];

			// Mem_Duplicate() will copy the contents of the original group list. The following must be changes though..
//			group->mesh = mesh;

			if (flags & MESH_CLONEFLAG_FACEDATA) group->faceData = Mem_Duplicate(originalGroup->faceData);

			if (flags & MESH_CLONEFLAG_HIDDENFACEDATA) {
				if (originalGroup->visibleFaceData) group->visibleFaceData = Mem_Duplicate(originalGroup->visibleFaceData);
			}
		}
	}

	if (!(flags & MESH_CLONEFLAG_COMPLETE)) {				// Retain a chain of all the clones of this object
		mesh->cloneChainNext = original->cloneChainNext;
		mesh->clonedFrom = original;
		original->cloneChainNext = mesh;
		original->referenceCount++;
	} else {
		mesh->cloneChainNext = NULL;
		mesh->clonedFrom = NULL;
	}

	mesh->cloneFlags = (UCHAR) flags;

	return mesh;
}

VOID Mesh_Restore(lpMesh clone, BOOL attributes) {

	lpMesh original = clone->clonedFrom;
	lpMeshGroup group, originalGroup;
	lpMeshVertexList originalVertexList, cloneVertexList;
	ULONG loop;

	List_CheckItem(meshGlobs.list, clone);
	Error_Fatal(NULL==original, "Mesh is not a clone");
	Error_Fatal(clone->cloneFlags & MESH_CLONEFLAG_ADDFACES, "Cannot restore a MESH_CLONEFLAG_ADDFACES type clone");

	if (clone->cloneFlags & MESH_CLONEFLAG_HIDDENFACEDATA) {
		Mem_CopyDuplicate(clone->faceArray, original->faceArray);
		for (loop=0 ; loop<clone->vertexListCount ; loop++) {

			cloneVertexList = &clone->vertexListList[loop];
			originalVertexList = &original->vertexListList[loop];

			if (cloneVertexList->visibleVertexBuffer) Mesh_CopyVertexBuffer(cloneVertexList->visibleVertexBuffer, originalVertexList->visibleVertexBuffer, &cloneVertexList->vertexInfo, 0, 0, 0);
			if (cloneVertexList->vertexIncludedData) Mem_CopyDuplicate(cloneVertexList->vertexIncludedData, originalVertexList->vertexIncludedData);
		}
	}

	for (loop=0 ; loop<clone->vertexListCount ; loop++) {

		cloneVertexList = &clone->vertexListList[loop];
		originalVertexList = &original->vertexListList[loop];

		if (clone->cloneFlags & MESH_CLONEFLAG_VERTICES) Mesh_CopyVertexBuffer(cloneVertexList->vertexBuffer, originalVertexList->vertexBuffer, &cloneVertexList->vertexInfo, 0, 0, 0);
	}
	
	if (clone->cloneFlags & MESH_CLONEFLAG_GROUPS) {

		Error_Fatal(clone->groupCount != original->groupCount, "Group count differs");

		for (loop=0 ; loop<clone->groupCount ; loop++) {

			group = &clone->groupList[loop];
			originalGroup = &original->groupList[loop];

			if (clone->cloneFlags & MESH_CLONEFLAG_FACEDATA) Mem_CopyDuplicate(group->faceData, originalGroup->faceData);
			if (clone->cloneFlags & MESH_CLONEFLAG_HIDDENFACEDATA) {
				if (group->visibleFaceData) Mem_CopyDuplicate(group->visibleFaceData, originalGroup->visibleFaceData);
			}

			if (attributes) {
				/************************************
				 **** TODO: Copy attributes here ****
				 ************************************/
				Error_Fatal(TRUE, "Boo!");
			}
		}
	}
}

static VOID Mesh_RemoveClone(lpMesh clone) {

	lpMesh mesh, prev = clone->clonedFrom;
	lpMeshVertexList cloneVertexList;
	lpMeshGroup group;
	lpMesh clonedFrom = clone->clonedFrom;
	ULONG loop;

	List_CheckItem(meshGlobs.list, clone);
	Error_Fatal(NULL == clone->clonedFrom, "Non-cloned mesh passed to Mesh_RemoveClone()");

	for (mesh=clone->clonedFrom ; mesh ; mesh=mesh->cloneChainNext) {
		if (mesh == clone) {
			prev->cloneChainNext = mesh->cloneChainNext;
			break;
		}
		prev = mesh;
	}

	for (loop=0 ; loop<clone->vertexListCount ; loop++) {

		cloneVertexList = &clone->vertexListList[loop];

		cloneVertexList->vertexBuffer->lpVtbl->Release(cloneVertexList->vertexBuffer);

		if (cloneVertexList->visibleVertexBuffer) cloneVertexList->visibleVertexBuffer->lpVtbl->Release(cloneVertexList->visibleVertexBuffer);
		if (cloneVertexList->transformedVertexBuffer) cloneVertexList->transformedVertexBuffer->lpVtbl->Release(cloneVertexList->transformedVertexBuffer);
	}

	if (clone->cloneFlags & MESH_CLONEFLAG_HIDDENFACEDATA) {
		Mem_Free(clone->faceArray);
		for (loop=0 ; loop<clone->vertexListCount ; loop++) {

			cloneVertexList = &clone->vertexListList[loop];

			if (cloneVertexList->vertexIncludedData) Mem_Free(cloneVertexList->vertexIncludedData);
		}
	}

	if ((clone->cloneFlags & MESH_CLONEFLAG_ADDFACES) && clone->maxVertexShare) {
		for (loop=0 ; loop<clone->vertexListCount ; loop++) {

			cloneVertexList = &clone->vertexListList[loop];

			Mem_Free(cloneVertexList->vertexRemapData);
			Mem_Free(cloneVertexList->vertexRefCount);
		}
	}
	
	if (clone->cloneFlags & MESH_CLONEFLAG_GROUPS) {

		for (loop=0 ; loop<clone->groupCount ; loop++) {
			group = &clone->groupList[loop];
			if (clone->cloneFlags & MESH_CLONEFLAG_FACEDATA) Mem_Free(group->faceData);
			if (clone->cloneFlags & MESH_CLONEFLAG_HIDDENFACEDATA) {
				if (group->visibleFaceData) Mem_Free(group->visibleFaceData);
			}
		}

		Mem_Free(clone->groupList);
	}

	if (clone->cloneFlags & MESH_CLONEFLAG_VERTEXLISTLIST) Mem_Free(clone->vertexListList);

	List_ReturnItem(meshGlobs.list, clone);

	Mesh_Remove(clonedFrom, TRUE);
}

BOOL Mesh_Remove(lpMesh dead, BOOL removeTextures) {

	ULONG loop, sub;
	lpMeshGroup group;
	lpMeshVertexList deadVertexList;

	List_CheckItem(meshGlobs.list, dead);
	Error_Fatal(NULL == dead, "NULL passed to Mesh_Remove()");

	if (dead->referenceCount) dead->referenceCount--;

	if (File_ReleaseSharedObject(meshGlobs.sharedObjectList, dead)) {

		if (dead->clonedFrom) {
			
			Mesh_RemoveClone(dead);
			return TRUE;

		} else if (0 == dead->referenceCount) {

			Error_Fatal(NULL != dead->cloneChainNext, "Mesh has clones. Remove them with Mesh_RemoveClone()");

			Mem_Free(dead->faceArray);

			for (loop=0 ; loop<dead->vertexListCount ; loop++) {

				deadVertexList = &dead->vertexListList[loop];

				deadVertexList->vertexBuffer->lpVtbl->Release(deadVertexList->vertexBuffer);
				if (deadVertexList->visibleVertexBuffer) deadVertexList->visibleVertexBuffer->lpVtbl->Release(deadVertexList->visibleVertexBuffer);

				if (dead->maxVertexShare) {
					Mem_Free(deadVertexList->vertexRemapData);
					Mem_Free(deadVertexList->vertexRefCount);
				}
				if (deadVertexList->vertexIncludedData) Mem_Free(deadVertexList->vertexIncludedData);

			}
			
			for (loop=0 ; loop<dead->groupCount ; loop++) {
			
				group = &dead->groupList[loop];

				Mem_Free(group->faceData);
				if (group->visibleFaceData) Mem_Free(group->visibleFaceData);
				if (removeTextures) {
					for (sub=0 ; sub<D3DDP_MAXTEXCOORD ; sub++) {
						if (group->texture[sub]) Texture_Remove(group->texture[sub]);
					}
				}

			}
			Mem_Free(dead->groupList);
			Mem_Free(dead->vertexListList);

			List_ReturnItem(meshGlobs.list, dead);

			return TRUE;
		}
	}

	return FALSE;
}

lpMesh Mesh_Load(LPUCHAR fname, ULONG maxVertexShare, ULONG blendLevels, BOOL useNormals, BOOL useShared, LPBOOL original) {

//lpMesh Mesh_Load2(LPUCHAR fname, ULONG maxPolysPerGroup, ULONG BOOL useShared, LPBOOL original) {

	lpLwo lwo;
	lpMesh mesh = NULL;

//	if (FALSE == useShared || NULL == (mesh = File_FindSharedObject(fname, FileObjectType_Mesh))) {
	if (FALSE == useShared || NULL == (mesh = File_FindSharedObject(meshGlobs.sharedObjectList, fname))) {
		if (lwo = Lwo_Load(fname)) {
			Lwo_GenerateNormals(lwo);
//			if (NULL == (
			mesh = UView_MakeMesh(lwo, fname, blendLevels, useNormals);//)) {
//				mesh = Lwo_BuildMesh(lwo, maxVertexShare, blendLevels);
//			}
//			if (useShared) File_RegisterSharedObject(fname, mesh, FileObjectType_Mesh);
			Lwo_Free(lwo);
			if (useShared) File_RegisterSharedObject(meshGlobs.sharedObjectList, fname, mesh);
			if (original) *original = TRUE;
		} //else Error_Fatal(TRUE, "File not found or unsupported file type");
	} else {
		if (original) *original = FALSE;
	}

	return mesh;
}

VOID Mesh_SetZBufferMode(lpMesh mesh, ULONG groupIndex, BOOL test, BOOL write) {

	lpMeshGroup group = &mesh->groupList[groupIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(groupIndex >= mesh->groupCount, "Group is out of range");

	if (test) group->flags &= ~MESH_GROUPFLAG_ZTESTDISABLED;
	else group->flags |= MESH_GROUPFLAG_ZTESTDISABLED;

	if (write) group->flags &= ~MESH_GROUPFLAG_ZWRITEDISABLED;
	else group->flags |= MESH_GROUPFLAG_ZWRITEDISABLED;
}

VOID Mesh_SetZBias(lpMesh mesh, ULONG groupIndex, ULONG bias) {

	lpMeshGroup group = &mesh->groupList[groupIndex];

	Error_Fatal(bias >= 16, "Z-Bias value out of range (0-15)");

	group->flags &= ~MESH_GROUPFLAG_ZBIASMASK;
	group->flags |= (bias << MESH_GROUPFLAG_ZBIASSHIFT);
}

static ULONG Mesh_ZBias(lpMeshGroup group) {

	return (group->flags & MESH_GROUPFLAG_ZBIASMASK) >> MESH_GROUPFLAG_ZBIASSHIFT;
}

ULONG Mesh_GetZBias(lpMesh mesh, ULONG groupIndex) {

	lpMeshGroup group = &mesh->groupList[groupIndex];

	return Mesh_ZBias(group);
}

VOID Mesh_SetGroupRenderFlags(lpMesh mesh, ULONG groupIndex, ULONG flags, BOOL set) {

	lpMeshGroup group = &mesh->groupList[groupIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(groupIndex >= mesh->groupCount, "Group is out of range");

	if (set) group->renderFlags |= flags;
	else group->renderFlags &= ~flags;
}

/*
VOID Mesh_SetGroupColour(lpMesh mesh, ULONG groupID, REAL r, REAL g, REAL b) {

	lpMeshGroup group = &mesh->groupList[groupID];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(groupID >= mesh->groupCount, "Group is out of range");

	group->material.dcvDiffuse.r = r;
	group->material.dcvDiffuse.g = g;
	group->material.dcvDiffuse.b = b;
	group->material.dcvAmbient.r = 0.5f;
	group->material.dcvAmbient.g = 0.5f;
	group->material.dcvAmbient.b = 0.5f;
}
*/

/*
VOID Mesh_SetGroupAlpha(lpMesh mesh, ULONG groupID, REAL a) {

	lpMeshGroup group = &mesh->groupList[groupID];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(groupID >= mesh->groupCount, "Group is out of range");

	group->material.dcvDiffuse.a = a;
	group->material.dcvDiffuse.r = a;
	group->material.dcvDiffuse.g = a;
	group->material.dcvDiffuse.b = a;
	group->material.dcvAmbient.r = 0.0;
	group->material.dcvAmbient.g = 0.0;
	group->material.dcvAmbient.b = 0.0;
}
*/

UWORD Mesh_CreateGroup(lpMesh mesh, ULONG vertexListIndex, ULONG vPerFace, ULONG faces) {

	UWORD groupID;
	lpMeshGroup group;

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal((vPerFace<MESH_MINPOLYSIDES)||(vPerFace>MESH_MAXPOLYSIDES), Error_Format("Only %i to %i sided faces allowed", MESH_MINPOLYSIDES, MESH_MAXPOLYSIDES));
	Error_Fatal(faces > MAX_UWORD, "Too many faces specified");

	groupID = mesh->groupCount++;
	mesh->groupList = Mem_ReAllocClear(mesh->groupList, sizeof(mesh->groupList[0]) * mesh->groupCount);
	group = &mesh->groupList[groupID];

	group->totalFaceDataSize = (UWORD) (faces * vPerFace);
	group->usedFaceDataSize = 0;
	group->visibleFaceDataSize = 0;
	group->vPerFace = (UWORD) vPerFace;
	group->vertexListIndex = vertexListIndex;

	group->material.dcvDiffuse.r = 1.0f;
	group->material.dcvDiffuse.g = 1.0f;
	group->material.dcvDiffuse.b = 1.0f;
	group->material.dcvAmbient.r = 1.0f;
	group->material.dcvAmbient.g = 1.0f;
	group->material.dcvAmbient.b = 1.0f;
	group->material.dcvSpecular.r = 1.0f;
	group->material.dcvSpecular.g = 1.0f;
	group->material.dcvSpecular.b = 1.0f;
	group->material.dcvEmissive.r = 0.0f;
	group->material.dcvEmissive.g = 0.0f;
	group->material.dcvEmissive.b = 0.0f;
	group->material.dvPower = 0.0f;

	group->faceData = Mem_Alloc(sizeof(group->faceData[0]) * group->totalFaceDataSize);

	return groupID;
}

VOID Mesh_AllocateHideInfo(lpMesh mesh, LPULONG maxVisibleVertices) {

	ULONG loop;
	lpMeshGroup group;
	lpMeshVertexList meshVertexList;
	D3DVERTEXBUFFERDESC vbDesc;
	HRESULT r;

	List_CheckItem(meshGlobs.list, mesh);

	for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

		meshVertexList = &mesh->vertexListList[loop];

		DirectX_InitStruct(&vbDesc);
		r = meshVertexList->vertexBuffer->lpVtbl->GetVertexBufferDesc(meshVertexList->vertexBuffer, &vbDesc);
		Error_DirectX(r, "GetVertexBufferDesc");
		vbDesc.dwNumVertices = maxVisibleVertices[loop];
		r = DirectX_Direct3D()->lpVtbl->CreateVertexBuffer(DirectX_Direct3D(), &vbDesc, &meshVertexList->visibleVertexBuffer, 0);
		Error_DirectX(r, "CreateVertexBuffer");

		meshVertexList->vertexIncludedData = Mem_Alloc(sizeof(meshVertexList->vertexIncludedData[0]) * meshVertexList->totalVertexCount);

	}

	for (loop=0 ; loop<mesh->groupCount ; loop++) {
		group = &mesh->groupList[loop];
		group->visibleFaceData = Mem_Alloc(sizeof(group->visibleFaceData[0]) * group->totalFaceDataSize);
	}
}

/*
UWORD Mesh_CreateGroup(lpMesh mesh, UWORD vPerFace, UWORD vertices, UWORD faces) {

	UWORD groupID = mesh->groupCount;
	lpMesh_Group group;

	Error_Fatal((vPerFace<MESH_MINPOLYSIDES)||(vPerFace>MESH_MAXPOLYSIDES), Error_Format("Only %i to %i sided faces allowed"));

	if (groupID == mesh->groupListSize) {
		mesh->groupListSize += MESH_GROUPBLOCKLENGTH;
		mesh->groupList = Mem_ReAlloc(mesh->groupList, sizeof(Mesh_Group) * mesh->groupListSize);
		memset(&mesh->groupList[groupID], 0, sizeof(Mesh_Group) * MESH_GROUPBLOCKLENGTH);
	}

	group = &mesh->groupList[groupID];
	group->totalFaceDataSize = faces * vPerFace;
	group->usedFaceDataSize = 0;
	group->visibleFaceDataSize = 0;
	group->vPerFace = vPerFace;
	group->totalVertexCount = vertices * 4;	// Double the amount of allocated vertices to allow for splitting.
	group->usedVertexCount = vertices;
	group->visibleVertexCount = vertices;

	group->faceData = Mem_Alloc(sizeof(UWORD) * group->totalFaceDataSize);
	group->vertices = Mem_AllocClear(sizeof(Mesh_Vertex) * group->totalVertexCount);
	group->vertexFlags = Mem_AllocClear(sizeof(UCHAR) * group->totalVertexCount);
	group->vertexRefCount = Mem_AllocClear(sizeof(UCHAR) * group->totalVertexCount);
	group->linkBackData = Mem_Alloc(sizeof(ULONG) * faces);

	group->vertexRemapData = Mem_Alloc(sizeof(UWORD) * group->totalVertexCount);
	return mesh->groupCount++;
}
*/

__inline BOOL Mesh_LockVertices(lpMesh mesh, BOOL lock) {

	SLONG loop;

	List_CheckItem(meshGlobs.list, mesh);

	Error_Fatal(mesh->flags & MESH_FLAG_OPTIMISED, "Cannot lock the vertices of an optimised mesh");

	for (loop=0 ; loop<(SLONG) mesh->vertexListCount ; loop++) {
		if (!Mesh_LockVertices_Index(mesh, loop, lock)) break;
	}

	// Couldn't lock them all, so put those that did back in the state that they were...

	if (loop < (SLONG) mesh->vertexListCount) {
		for (loop-- ; loop >= 0 ; loop--) {
			Mesh_LockVertices_Index(mesh, loop, !lock);
		}
	} else return TRUE;

	return FALSE;
}

BOOL Mesh_LockVertices_Index(lpMesh mesh, ULONG index, BOOL lock) {

	if (mesh->clonedFrom && !(mesh->cloneFlags & MESH_CLONEFLAG_VERTICES)) return Mesh_LockVertices_Index(mesh->clonedFrom, index, lock);
	else {
		
		HRESULT r;
		BOOL makeCall;
		lpMeshVertexList meshVertexList = &mesh->vertexListList[index];

		List_CheckItem(meshGlobs.list, mesh);
		Error_Fatal(index >= mesh->vertexListCount, "index is out of range");

		if (lock) makeCall = (NULL == meshVertexList->vertexBufferMemory);
		else makeCall = (NULL != meshVertexList->vertexBufferMemory && 0 == --meshVertexList->vertexBufferLockCount);

		if (makeCall) {

			if (lock) {
				r = meshVertexList->vertexBuffer->lpVtbl->Lock(meshVertexList->vertexBuffer, DDLOCK_WAIT, &meshVertexList->vertexBufferMemory, NULL);
				meshVertexList->vertexBufferLockCount = 1;
			} else {
				r = meshVertexList->vertexBuffer->lpVtbl->Unlock(meshVertexList->vertexBuffer);
				meshVertexList->vertexBufferMemory = NULL;
			}

			if (D3D_OK == r) {

				lpMesh clone;

				for (clone=mesh->cloneChainNext ; clone ; clone=clone->cloneChainNext) {

					lpMeshVertexList cloneVertexList = &clone->vertexListList[index];
					
					if (!(clone->cloneFlags & MESH_CLONEFLAG_VERTICES)) cloneVertexList->vertexBufferMemory = meshVertexList->vertexBufferMemory;
				}

				return TRUE;
			}

		} else {
			if (lock) meshVertexList->vertexBufferLockCount++;
			return TRUE;
		}
	}

	return FALSE;
}

__inline VOID Mesh_SetVertexScreenPosition(lpMesh mesh, ULONG index, UWORD vertex, LPVECTOR4D position) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[index];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(index > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	((LPVECTOR4D) &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex])[0] = *position;

	if (mesh->maxVertexShare) {
		while (vertex = meshVertexList->vertexRemapData[vertex]) {
			((LPVECTOR4D) &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex])[0] = *position;
		}
	}
}

__inline VOID Mesh_SetVertexPosition(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, LPVECTOR3D position) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	((LPVECTOR3D) &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex])[0] = *position;

	if (mesh->maxVertexShare) {
		while (vertex = meshVertexList->vertexRemapData[vertex]) {
			((LPVECTOR3D) &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex])[0] = *position;
		}
	}
}

__inline LPVOID Mesh_GetVertexBuffer(lpMesh mesh, ULONG vertexListIndex, ULONG vertex) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	return &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex];
}

__inline LPVECTOR3D Mesh_GetVertexPosition(lpMesh mesh, ULONG vertexListIndex, ULONG vertex) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	return &(((LPVECTOR3D) &meshVertexList->vertexBufferMemory[meshVertexList->vertexInfo.size * vertex])[0]);
}

__inline VOID Mesh_SetBlendLevel(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, ULONG blendIndex, REAL level) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");
	Error_Fatal(blendIndex > meshVertexList->vertexInfo.blendCount, "Blend index out of range");

	((LPREAL) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.blendPos])[blendIndex] = level;

	if (mesh->maxVertexShare) {
		while (vertex = meshVertexList->vertexRemapData[vertex]) {
			((LPREAL) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.blendPos])[blendIndex] = level;
		}
	}
}

__inline REAL Mesh_GetBlendLevel(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, ULONG blendIndex) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");
	Error_Fatal(blendIndex > meshVertexList->vertexInfo.blendCount, "Blend index out of range");

	return ((LPREAL) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.blendPos])[blendIndex];
}

__inline VOID Mesh_SetVertexNormal(lpMesh mesh, ULONG index, ULONG vertex, LPVECTOR3D normal) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[index];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(!(meshVertexList->vertexInfo.srcFlags & D3DFVF_NORMAL), "Mesh does not have any normal data");
	Error_Fatal(index > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	((LPVECTOR3D) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.normalPos])[0] = *normal;

	if (mesh->maxVertexShare) {
		while (vertex = meshVertexList->vertexRemapData[vertex]) {
			((LPVECTOR3D) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.normalPos])[0] = *normal;
		}
	}
}

__inline VOID Mesh_SetVertexColour(lpMesh mesh, ULONG index, ULONG vertex, COLOUR colour) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[index];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(!(meshVertexList->vertexInfo.srcFlags & D3DFVF_DIFFUSE), "Mesh does not have any diffuse data");
	Error_Fatal(index > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(NULL == meshVertexList->vertexBufferMemory, "Vertices have not been locked");

	((LPULONG) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.diffusePos])[0] = colour;

	if (mesh->maxVertexShare) {
		while (vertex = meshVertexList->vertexRemapData[vertex]) {
			((LPULONG) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.diffusePos])[0] = colour;
		}
	}
}

__inline VOID Mesh_SetVertexUV(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, ULONG uvIndex, REAL tu, REAL tv) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];
	LPVECTOR2D vertexUV = &(((LPVECTOR2D) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.uvPos])[uvIndex]);

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");

	Error_Fatal(mesh->maxVertexShare, "Only supported on meshes with maxVertexShare set as zero (use Mesh_SetPolyUV() instead)");
	Error_Fatal(uvIndex > meshVertexList->vertexInfo.uvCount, "UV index out of range");

	vertexUV->x = tu;
	vertexUV->y = tv;
}

__inline VOID Mesh_GetVertexUV(lpMesh mesh, ULONG vertexListIndex, ULONG vertex, ULONG uvIndex, REAL *tu, REAL *tv) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];
	LPVECTOR2D vertexUV = &(((LPVECTOR2D) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.uvPos])[uvIndex]);

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");

	Error_Fatal(mesh->maxVertexShare, "Only supported on meshes with maxVertexShare set as zero (use Mesh_SetPolyUV() instead)");
	Error_Fatal(uvIndex > meshVertexList->vertexInfo.uvCount, "UV index out of range");

	*tu = vertexUV->x;
	*tv = vertexUV->y;
}

__inline VOID Mesh_SetPolyUV(lpMesh mesh, ULONG vertexListIndex, ULONG poly, ULONG uvIndex, REAL tu[3], REAL tv[3]) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];
	lpMeshFace face = &mesh->faceArray[poly];
	lpMeshGroup group = &mesh->groupList[face->group];
	LPVECTOR2D vertexUV;
	ULONG loop, vertex;

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");
	Error_Fatal(uvIndex > meshVertexList->vertexInfo.uvCount, "UV index out of range");
	Error_Fatal(0 == mesh->maxVertexShare, "Only supported on meshes with maxVertexShare set as non-zero (use Mesh_SetVertexUV() instead)");

	for (loop=0 ; loop<3 ; loop++) {
		vertex = group->faceData[face->listIndex + loop];
		vertexUV = &(((LPVECTOR2D) &meshVertexList->vertexBufferMemory[(meshVertexList->vertexInfo.size * vertex) + meshVertexList->vertexInfo.uvPos])[uvIndex]);
		vertexUV->x = tu[loop];
		vertexUV->y = tv[loop];
	}
	
}

__inline VOID Mesh_SetTexture(lpMesh mesh, ULONG groupID, ULONG textureIndex, lpTexture texture) {

	lpMeshGroup group = &mesh->groupList[groupID];

	List_CheckItem(meshGlobs.list, mesh);
	group->texture[textureIndex] = texture;
}

__inline lpTexture Mesh_GetTexture(lpMesh mesh, ULONG groupID, ULONG textureIndex) {

	lpMeshGroup group = &mesh->groupList[groupID];

	List_CheckItem(meshGlobs.list, mesh);
	return group->texture[textureIndex];
}

/*
VOID Mesh_SetVertexColour(lpMesh mesh, UWORD groupID, UWORD vertex, ULONG colour) {

	lpMesh_Group group = &mesh->groupList[groupID];

	if (mesh->maxVertexShare) {
		while (1) {
			group->vertices[vertex].diffuseColour = colour;
			if (group->vertexRemapData[vertex]) vertex = group->vertexRemapData[vertex];
			else break;
		}
	} else group->vertices[vertex].diffuseColour = colour;
}
*/

__inline VOID Mesh_Hide(lpMesh mesh, BOOL hide) {

	List_CheckItem(meshGlobs.list, mesh);

	if (hide) mesh->flags |= MESH_FLAG_HIDDEN;
	else mesh->flags &= ~MESH_FLAG_HIDDEN;
}

__inline VOID Mesh_HidePoly(lpMesh mesh, UWORD poly, BOOL hide) {

	lpMeshFace face = &mesh->faceArray[poly];

	List_CheckItem(meshGlobs.list, mesh);
	mesh->flags |= MESH_FLAG_HIDEPOLYCALLED;

	if (hide) {
		face->flags |= MESH_FACEFLAG_HIDDEN;
	} else {
		face->flags &= ~MESH_FACEFLAG_HIDDEN;
		face->flags |= MESH_FACEFLAG_FRESH;
	}
}

/*
VOID Mesh_HidePoly(lpMesh mesh, UWORD poly, BOOL hide) {

	lpMesh_Face primaryFace = &mesh->faceArray[poly];
	lpMesh_Group group = &mesh->groupList[primaryFace->group];
//	BOOL hiddenOld = (primaryFace->flags & MESH_FACEFLAG_HIDDEN);
	BOOL hidden = (primaryFace->listIndex >= group->visibleFaceDataSize);

//	Error_Fatal((hiddenOld&&!hidden)||(!hiddenOld&&hidden), "");

	// If the face is flagged to be shown then flag it a being fresh regardless...
	if (!hide) primaryFace->flags |= MESH_FACEFLAG_FRESH;

	if ((hide && !hidden) || (!hide && hidden)) {

		lpMesh_Face destinationFace;
		UWORD buffer[MESH_MAXPOLYSIDES];
		UWORD destinationLoc;
		ULONG destinationID;
		UWORD primaryLoc = primaryFace->listIndex;
		UWORD loop, vertexID;

		if (hide) {

			Error_Fatal(group->visibleFaceDataSize < group->vPerFace, "hide face");
			group->visibleFaceDataSize -= group->vPerFace;
			destinationLoc = group->visibleFaceDataSize;
//			primaryFace->flags |= MESH_FACEFLAG_HIDDEN;

			// Flag the vertices that the hidden polygon is no longer using them...
			for (loop=0 ; loop<group->vPerFace ; loop++) {
				vertexID = group->faceData[primaryFace->listIndex + loop];
//				if ((group->vertexFlags[vertexID] & MESH_VERTEXFLAG_SINGLE) ||
//					(group->vertexFlags[vertexID] & MESH_VERTEXFLAG_UNLINKED)) {


				Error_Fatal(0==group->vertexRefCount[vertexID], "vertex was previously hidden even though it was still being used");
				group->vertexRefCount[vertexID]--;

				if (0 == group->vertexRefCount[vertexID]) {

					// The vertex is no longer used by any polygon...
					Mesh_VertexSwap(mesh, group, vertexID, TRUE);
				}

//				} else group->vertexFlags[vertexID] |= MESH_VERTEXFLAG_UNLINKED;
			}

		} else {

			destinationLoc = group->visibleFaceDataSize;
			group->visibleFaceDataSize += group->vPerFace;
//			primaryFace->flags &= ~MESH_FACEFLAG_HIDDEN;

			// Reintroduce and hidden vertices that are required for this polygon...
			for (loop=0 ; loop<group->vPerFace ; loop++) {
				vertexID = group->faceData[primaryFace->listIndex + loop];

				// Increment the usedCount
				group->vertexRefCount[vertexID]++;

				if (vertexID >= group->visibleVertexCount) {

					// The vertex is outside the range of visible vertices, so bring it back in...
					Mesh_VertexSwap(mesh, group, vertexID, FALSE);

//				} else group->vertexFlags[vertexID] &= ~MESH_VERTEXFLAG_UNLINKED;	// If it was unlinked, but still in the list remove the flag.

				}
			}
		}

		destinationID = group->linkBackData[destinationLoc / group->vPerFace];
		destinationFace = &mesh->faceArray[destinationID];

		Error_Fatal(destinationFace->listIndex != destinationLoc, "Mesh_HidePoly()");

		// Swap over the face definitions.
		Mem_Copy(buffer, &group->faceData[destinationLoc], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[destinationLoc], &group->faceData[primaryLoc], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[primaryLoc], buffer, sizeof(UWORD) * group->vPerFace);

		// Remap the pointers to where in the list the face definitions are located.
		destinationFace->listIndex = primaryLoc;
		primaryFace->listIndex = destinationLoc;

		// Adjust the link back data to reflect which face belongs to the position in the face data...
		group->linkBackData[destinationLoc / group->vPerFace] = poly;
		group->linkBackData[primaryLoc / group->vPerFace] = destinationID;
	}

}

static VOID Mesh_VertexSwap(lpMesh mesh, lpMesh_Group group, UWORD primaryVertex, BOOL unused) {

	Mesh_Vertex buffer[MESH_MAXPOLYSIDES];
	UWORD loop, destinationVertex;
	UCHAR flagsSwap, refCountSwap;

	if (unused) {
		Error_Fatal(primaryVertex>=group->visibleVertexCount, "hiding hidden vertex");
		group->visibleVertexCount--;
		destinationVertex = group->visibleVertexCount;
	} else {
		Error_Fatal(primaryVertex<group->visibleVertexCount, "unhiding unhidden vertex");
		destinationVertex = group->visibleVertexCount;
		group->visibleVertexCount++;
	}

	Mem_Copy(buffer, &group->vertices[destinationVertex], sizeof(Mesh_Vertex));
	Mem_Copy(&group->vertices[destinationVertex], &group->vertices[primaryVertex], sizeof(Mesh_Vertex));
	Mem_Copy(&group->vertices[primaryVertex], buffer, sizeof(Mesh_Vertex));

	flagsSwap = group->vertexFlags[destinationVertex];
	group->vertexFlags[destinationVertex] = group->vertexFlags[primaryVertex];
	group->vertexFlags[primaryVertex] = flagsSwap;

	refCountSwap = group->vertexRefCount[destinationVertex];
	group->vertexRefCount[destinationVertex] = group->vertexRefCount[primaryVertex];
	group->vertexRefCount[primaryVertex] = refCountSwap;


	if (mesh->maxVertexShare) {		// This makes a very very minimal speed increase...

		ULONG hits = 0, reqHits = mesh->maxVertexShare * 2;

		for (loop=0 ; loop<group->usedFaceDataSize ; loop++) {

			if (hits == reqHits) break;

			if (group->faceData[loop] == primaryVertex) {
				group->faceData[loop] = destinationVertex;
				hits++;
			} else if (group->faceData[loop] == destinationVertex) {
				group->faceData[loop] = primaryVertex;
				hits++;
			}
		}
	} else {
		for (loop=0 ; loop<group->usedFaceDataSize ; loop++) {
			if (group->faceData[loop] == primaryVertex) group->faceData[loop] = destinationVertex;
			else if (group->faceData[loop] == destinationVertex) group->faceData[loop] = primaryVertex;
		}
	}
}
*/

__inline UWORD Mesh_GetGroupCount(lpMesh mesh) {

	List_CheckItem(meshGlobs.list, mesh);
	return mesh->groupCount;
}

__inline ULONG Mesh_GetVertexListIndex(lpMesh mesh, ULONG groupID) {

	Error_Fatal(groupID > mesh->groupCount, "GroupID is out of range");
	List_CheckItem(meshGlobs.list, mesh);

	return mesh->groupList[groupID].vertexListIndex;
}

__inline ULONG Mesh_GetVertexListCount(lpMesh mesh) {

	List_CheckItem(meshGlobs.list, mesh);
	return mesh->vertexListCount;
}

__inline UWORD Mesh_GetVertexCount(lpMesh mesh, ULONG vertexListIndex) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(vertexListIndex > mesh->vertexListCount, "Index is out of range");

	return meshVertexList->usedVertexCount;
}

VOID Mesh_GetBox(lpMesh mesh, LPBOX3D box) {

	UWORD loop;
	ULONG index;
	lpMeshVertexList meshVertexList;

	List_CheckItem(meshGlobs.list, mesh);

	Mesh_LockVertices(mesh, TRUE);

	box->min = box->max = *Mesh_GetVertexPosition(mesh, 0, 0);

	for (index=0 ; index<mesh->vertexListCount ; index++) {

		meshVertexList = &mesh->vertexListList[index];

		// Use 'usedVertexCount' as tho ones from there up to 'internallyUsedVertexCount' are all duplicates.
		for (loop=0 ; loop<meshVertexList->usedVertexCount ; loop++) {
			box->min.x = min(box->min.x, Mesh_GetVertexPosition(mesh, index, loop)->x);
			box->min.y = min(box->min.y, Mesh_GetVertexPosition(mesh, index, loop)->y);
			box->min.z = min(box->min.z, Mesh_GetVertexPosition(mesh, index, loop)->z);
			box->max.x = max(box->max.x, Mesh_GetVertexPosition(mesh, index, loop)->x);
			box->max.y = max(box->max.y, Mesh_GetVertexPosition(mesh, index, loop)->y);
			box->max.z = max(box->max.z, Mesh_GetVertexPosition(mesh, index, loop)->z);
		}

	}

	Mesh_LockVertices(mesh, FALSE);
}

VOID Mesh_Translate(lpMesh mesh, LPVECTOR3D offset) {

	UWORD loop;
	ULONG index;
	VECTOR3D newPos;
	lpMeshVertexList meshVertexList;

	List_CheckItem(meshGlobs.list, mesh);

	Mesh_LockVertices(mesh, TRUE);

	for (index=0 ; index<mesh->vertexListCount ; index++) {

		meshVertexList = &mesh->vertexListList[index];

		for (loop=0 ; loop<meshVertexList->internallyUsedVertexCount ; loop++) {
			Maths_Vector3DAdd(&newPos, Mesh_GetVertexPosition(mesh, index, loop), offset);
			Mesh_SetVertexPosition(mesh, index, loop, &newPos);
		}
	}

	Mesh_LockVertices(mesh, FALSE);
}

VOID Mesh_Scale(lpMesh mesh, LPVECTOR3D scale) {

	UWORD loop;
	ULONG index;
	VECTOR3D newPos;
	lpMeshVertexList meshVertexList;

	List_CheckItem(meshGlobs.list, mesh);

	Mesh_LockVertices(mesh, TRUE);

	for (index=0 ; index<mesh->vertexListCount ; index++) {

		meshVertexList = &mesh->vertexListList[index];

		for (loop=0 ; loop<meshVertexList->internallyUsedVertexCount ; loop++) {
			newPos = *Mesh_GetVertexPosition(mesh, index, loop);
			newPos.x *= scale->x;
			newPos.y *= scale->y;
			newPos.z *= scale->z;
			Mesh_SetVertexPosition(mesh, index, loop, &newPos);
		}
	}

	Mesh_LockVertices(mesh, FALSE);
}

__inline ULONG Mesh_GetTotalFaceCount(lpMesh mesh) {

	List_CheckItem(meshGlobs.list, mesh);

	return mesh->faceCount;
}

__inline ULONG Mesh_GetFaceDataSize(lpMesh mesh, ULONG groupID) {

	Error_Fatal(groupID > mesh->groupCount, "GroupID is out of range");
	List_CheckItem(meshGlobs.list, mesh);

	return mesh->groupList[groupID].usedFaceDataSize;
}

__inline LPUWORD Mesh_GetFaceData(lpMesh mesh, ULONG groupID) {

	Error_Fatal(groupID > mesh->groupCount, "GroupID is out of range");
	List_CheckItem(meshGlobs.list, mesh);

	return mesh->groupList[groupID].faceData;
}

LPVECTOR3D Mesh_GetPolyVertex(lpMesh mesh, ULONG poly, ULONG index) {
	
	lpMeshFace face = &mesh->faceArray[poly];
	lpMeshGroup group = &mesh->groupList[face->group];

	List_CheckItem(meshGlobs.list, mesh);

	return Mesh_GetVertexPosition(mesh, group->vertexListIndex, group->faceData[face->listIndex + index]);
}

LPVECTOR3D Mesh_CalculatePolyNormal(lpMesh mesh, ULONG poly, LPVECTOR3D normal) {

	lpMeshFace face = &mesh->faceArray[poly];
	lpMeshGroup group = &mesh->groupList[face->group];
	LPVECTOR3D vertices[3];
	ULONG loop;

	List_CheckItem(meshGlobs.list, mesh);

	// Take the normal of the first three points...

	for (loop=0 ; loop<3 ; loop++) {
		vertices[loop] = Mesh_GetVertexPosition(mesh, group->vertexListIndex, group->faceData[face->listIndex + loop]);
	}

	return Maths_PlaneNormal(normal, vertices[0], vertices[1], vertices[2]);
}

UWORD Mesh_GetPolyShape(lpMesh mesh, ULONG poly, LPVECTOR3D shape) {

	lpMeshFace face = &mesh->faceArray[poly];
	lpMeshGroup group = &mesh->groupList[face->group];
	UWORD index, loop;

	List_CheckItem(meshGlobs.list, mesh);

	for (loop=0 ; loop<group->vPerFace ; loop++) {
		index = group->faceData[face->listIndex + loop];
		shape[loop] = *Mesh_GetVertexPosition(mesh, group->vertexListIndex, index);
	}

	return group->vPerFace;
}

VOID Mesh_AddTriangle(lpMesh mesh, ULONG groupID, UWORD index[3]) {

	lpMeshGroup group = &mesh->groupList[groupID];
	ULONG loop;
	UWORD useIndex;
	lpMeshFace face = &mesh->faceArray[mesh->faceCount];
	lpMeshVertexList meshVertexList = &mesh->vertexListList[group->vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Overflow(mesh->faceCount, mesh->totalFaceCount);

	for (loop=0 ; loop<3 ; loop++) {

		useIndex = index[loop];

		Error_Fatal(useIndex > meshVertexList->totalVertexCount, "Vertex is out of range");

		if (mesh->maxVertexShare) {		// If more than two triangles share a vertex, need to split it...

			LPUCHAR lpRefCount;

			// Find the last entry in the remap chain...
			while (meshVertexList->vertexRemapData[useIndex]) useIndex = meshVertexList->vertexRemapData[useIndex];

			lpRefCount = &meshVertexList->vertexRefCount[useIndex];
			(*lpRefCount)++;

			if ((*lpRefCount) == (UCHAR) mesh->maxVertexShare) {

				// The vertex is shared too many time, so duplicate it and remap this face to use the new vertex...

				Error_Fatal(meshVertexList->internallyUsedVertexCount==meshVertexList->totalVertexCount, "Run out of vertices");

				meshVertexList->vertexRemapData[useIndex] = meshVertexList->internallyUsedVertexCount;

				// Copy the vertex to the end of the list
				Mesh_CopyVertexBuffer(meshVertexList->vertexBuffer, meshVertexList->vertexBuffer, &meshVertexList->vertexInfo, meshVertexList->internallyUsedVertexCount, useIndex, 1);

				meshVertexList->internallyUsedVertexCount++;
			}
		}

		Error_Overflow(group->usedFaceDataSize, group->totalFaceDataSize);

		group->faceData[group->usedFaceDataSize] = useIndex;
		group->usedFaceDataSize++;
	}

	group->visibleFaceDataSize = group->usedFaceDataSize;

	// Register the face (and its position within the face data) in the mesh...
	face->group = (UWORD) groupID;
	face->listIndex = group->usedFaceDataSize - 3;
	mesh->faceCount++;
}

/*
VOID Mesh_AddTriangle(lpMesh mesh, UWORD groupID, UWORD index[3]) {

	lpMesh_Group group = &mesh->groupList[groupID];
	ULONG loop;
	UWORD useIndex;
	lpMesh_Face face = &mesh->faceArray[mesh->faceCount];

//	face->flags |= MESH_FACEFLAG_PRIMARY;

	for (loop=0 ; loop<3 ; loop++) {

		lpMesh_Vertex vertex;
		LPUCHAR flags, refCount;
//		UCHAR temp;

		// If more than two triangles share a vertex, need to split it...
		useIndex = index[loop];

		// Find the last entry in the remap chain...
		while (group->vertexFlags[useIndex] & MESH_VERTEXFLAG_REMAPPED) {
			useIndex = group->vertexRemapData[useIndex];
		}

		vertex = &group->vertices[useIndex];
		flags = &group->vertexFlags[useIndex];
		refCount = &group->vertexRefCount[useIndex];

//		if ((*flags) & MESH_VERTEXFLAG_REFERENCED) {
//			if ((*flags) & MESH_VERTEXFLAG_SINGLE) {
//				(*flags) &= ~MESH_VERTEXFLAG_SINGLE;
//			} else {

//		if (((*flags) & MESH_VERTEXFLAG_SHAREDCOUNTMASK) == (UCHAR) mesh->maxVertexShare) {
		if (mesh->maxVertexShare && (*(refCount) == (UCHAR) mesh->maxVertexShare)) {

			Error_Fatal(group->usedVertexCount==group->totalVertexCount, "Run out of vertices");

			// There are already two faces using this vertex so duplicate it and
			// remap this face to use the new vertex...

			group->vertexRemapData[useIndex] = group->usedVertexCount;
			group->vertexFlags[useIndex] |= MESH_VERTEXFLAG_REMAPPED;

			useIndex = group->usedVertexCount;
			group->vertices[useIndex] = *vertex;
			flags = &group->vertexFlags[useIndex];
			refCount = &group->vertexRefCount[useIndex];

//			vertex = &group->vertices[useIndex];
//			flags = &group->vertexFlags[useIndex];
//			(*flags) |= (MESH_VERTEXFLAG_REFERENCED|MESH_VERTEXFLAG_SINGLE);

			group->usedVertexCount++;
			group->visibleVertexCount++;
//			}
//		} else (*flags) |= (MESH_VERTEXFLAG_REFERENCED|MESH_VERTEXFLAG_SINGLE);

		}

		Error_Fatal(0xff==*refCount, "Too many faces share one vertex");

		(*refCount)++;
//		temp = (*flags) & MESH_VERTEXFLAG_SHAREDCOUNTMASK;
//		temp++;
//		(*flags) &= ~MESH_VERTEXFLAG_SHAREDCOUNTMASK;
//		(*flags) |= temp;

		group->faceData[group->usedFaceDataSize] = useIndex;
		group->usedFaceDataSize++;
	}

	group->linkBackData[group->visibleFaceDataSize / group->vPerFace] = mesh->faceCount;
	group->visibleFaceDataSize = group->usedFaceDataSize;
//	group->linkBackData[mesh->faceCount] = mesh->faceCount;

	// Register the face (and its position within the face data) in the mesh...
	face->group = groupID;
	face->listIndex = group->usedFaceDataSize - 3;
//	face->flags = 0;
	mesh->faceCount++;

	// TODO:	Allow for meshes that use single uv's per vertex (disable vertex splitting)..
	//			Assign 'primary' flags to the appropriate face...
}
*/

//VOID Mesh_Update(lpMesh mesh, BOOL hideUnfresh, lpFrame frame, lpFrame camera) {
VOID Mesh_Update(lpMesh mesh, BOOL hideUnfresh) {

	UWORD loop;
	lpMeshFace face;
	lpMeshGroup group;
	lpMeshVertexList meshVertexList;
//	VECTOR3D camPos, camDir;

//	Frame_GetRelativePosition(camera, frame, &camPos);
//	Frame_GetRelativeOrientation(camera, frame, &camDir, NULL);

	List_CheckItem(meshGlobs.list, mesh);

	if (mesh->flags & MESH_FLAG_HIDEPOLYCALLED) {

		for (loop=0 ; loop<mesh->groupCount ; loop++) {
			group = &mesh->groupList[loop];
			group->visibleFaceDataSize = 0;
		}

		for (loop=0 ; loop<mesh->vertexListCount ; loop++) {

			meshVertexList = &mesh->vertexListList[loop];

			meshVertexList->visibleVertexCount = 0;
			memset(meshVertexList->vertexIncludedData, 0xff, sizeof(meshVertexList->vertexIncludedData[0]) * meshVertexList->internallyUsedVertexCount);
		}

		if (hideUnfresh) {
			for (loop=0 ; loop<mesh->faceCount ; loop++) {
				face = &mesh->faceArray[loop];
				group = &mesh->groupList[face->group];
				if (!(face->flags & MESH_FACEFLAG_HIDDEN) && (face->flags & MESH_FACEFLAG_FRESH)) {
//					if (Mesh_PolyFrontFacing(group, face, &camPos, &camDir)) {
						Mesh_IncludePoly(mesh, group, face);
//					}
				}
				face->flags &= ~MESH_FACEFLAG_FRESH;
			}
		} else {
			for (loop=0 ; loop<mesh->faceCount ; loop++) {
				face = &mesh->faceArray[loop];
				group = &mesh->groupList[face->group];
				if (!(face->flags & MESH_FACEFLAG_HIDDEN)) {
//					if (Mesh_PolyFrontFacing(group, face, &camPos, &camDir)) {
						Mesh_IncludePoly(mesh, group, face);
//					}
				}
			}
		}

		for (loop=0 ; loop<mesh->groupCount ; loop++) {
			group = &mesh->groupList[loop];
			if (0 == group->visibleFaceDataSize) group->flags |= MESH_GROUPFLAG_NONEVISIBLE;
		}

	}
}

VOID Mesh_Reset(lpMesh mesh) {

	UWORD loop;
	lpMeshGroup group;
	lpMeshVertexList meshVertexList;

	List_CheckItem(meshGlobs.list, mesh);

	for (loop=0 ; loop<mesh->groupCount ; loop++) {
		group = &mesh->groupList[loop];
		group->flags &= ~MESH_GROUPFLAG_NONEVISIBLE;
	}
	mesh->flags &= ~MESH_FLAG_HIDEPOLYCALLED;

	for (loop=0 ; loop<mesh->vertexListCount ; loop++) {
		
		meshVertexList = &mesh->vertexListList[loop];

		meshVertexList->flags &= ~MESH_VERTEXLISTFLAG_TRANSFORMED;
	}
}

/*
// Still slower...
__inline static BOOL Mesh_PolyFrontFacing(lpMesh_Group group, lpMesh_Face face, LPVECTOR3D camPos, LPVECTOR3D camDir) {

	VECTOR3D cpVec, normal;
	LPVECTOR3D pointZero = &group->vertices[group->faceData[face->listIndex+0]].position;
	REAL dp;

	Maths_PlaneNormal(&normal, pointZero, &group->vertices[group->faceData[face->listIndex+1]].position, &group->vertices[group->faceData[face->listIndex+2]].position);
	Maths_Vector3DSubtract(&cpVec, camPos, pointZero);
	Maths_Vector3DNormalise(&cpVec);
	dp = Maths_Vector3DDotProduct(&cpVec, &normal);

	if (dp < 0.0f) return FALSE;
	else return TRUE;
}
*/

static VOID Mesh_IncludePoly(lpMesh mesh, lpMeshGroup group, lpMeshFace face) {

	UWORD loop, vertex;
	lpMeshVertexList meshVertexList = &mesh->vertexListList[group->vertexListIndex];

	List_CheckItem(meshGlobs.list, mesh);
	Error_Fatal(3!=group->vPerFace, "Triangles only...");

	for (loop=0 ; loop<3 ; loop++) {
		vertex = group->faceData[face->listIndex + loop];

		if (0xffff == meshVertexList->vertexIncludedData[vertex]) {
			group->visibleFaceData[group->visibleFaceDataSize++] = meshVertexList->visibleVertexCount;
			meshVertexList->vertexIncludedData[vertex] = meshVertexList->visibleVertexCount;
//			Mem_Copy(&group->visibleVertices[group->visibleVertexCount], &group->vertices[group->faceData[face->listIndex + loop]], sizeof(Mesh_Vertex));
			Mesh_CopyVertexBuffer(meshVertexList->visibleVertexBuffer, meshVertexList->vertexBuffer, &meshVertexList->vertexInfo, meshVertexList->visibleVertexCount, group->faceData[face->listIndex + loop], 1);
			meshVertexList->visibleVertexCount++;
		} else {
			group->visibleFaceData[group->visibleFaceDataSize++] = meshVertexList->vertexIncludedData[vertex];
		}
	}
}

/*
VOID Mesh_HideUnfresh(lpMesh mesh) {

	UWORD loop;
	lpMesh_Face face;
	
	for (loop=0 ; loop<mesh->faceCount ; loop++) {
		face = &mesh->faceArray[loop];
		if (!(face->flags & MESH_FACEFLAG_FRESH)) Mesh_HidePoly(mesh, loop, TRUE);
		face->flags &= ~MESH_FACEFLAG_FRESH;
	}
}
*/

VOID Mesh_SetBoneList(lpMesh mesh, lpLws lws, lpLwsBone boneList) {

	List_CheckItem(meshGlobs.list, mesh);

	mesh->boneScene = lws;
	mesh->boneList = boneList;
}

VOID Mesh_AddToRenderList(lpMesh mesh, lpFrame frame) {

	ULONG loop;
	lpMeshGroup group;

	List_CheckItem(meshGlobs.list, mesh);

	for (loop=0 ; loop<mesh->vertexListCount ; loop++) {
		Error_Fatal(NULL != mesh->vertexListList[loop].vertexBufferMemory, "Mesh with locked vertices passed to Mesh_AddToRenderList()");
	}

	if (!(mesh->flags & MESH_FLAG_HIDDEN) && !(frame->flags & FRAME_FLAG_HIDDEN)) {
		for (loop=0 ; loop<mesh->groupCount ; loop++) {
			group = &mesh->groupList[loop];
			if (!(group->flags & MESH_GROUPFLAG_HIDDEN) && !(group->flags & MESH_GROUPFLAG_NONEVISIBLE)) {

//				Error_Overflow(meshGlobs.renderCount, MESH_RENDERLISTSIZE);
//				meshGlobs.renderList[meshGlobs.renderCount].frame = frame;
//				meshGlobs.renderList[meshGlobs.renderCount].group = group;
//				meshGlobs.renderList[meshGlobs.renderCount].mesh = mesh;
//				meshGlobs.renderCount++;

				Render_AddMeshEntry(mesh, group, frame);
			
			}
		}
	}
}

#ifdef _DEBUG
lpMesh debugStopMesh = NULL;
#endif // _DEBUG

ULONG Mesh_RenderGroup(lpMesh mesh, lpMeshGroup group, lpFrame frame, lpFrame lastRenderedFrame) {

	lpMeshVertexList meshVertexList = &mesh->vertexListList[group->vertexListIndex];
	ULONG textureIndex, transformFlags, verticesTransformed = 0, polysDrawn = 0;
	LPDIRECTDRAWSURFACE7 setTextureSurface;
	LPD3DMATRIX m;
	HRESULT r;

	// Setup the alpha blending/zbuffer modes...

//	if (Dialog_GetOption(DialogOption_NoPersCorr)) {
//		Render_SetState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);
//	} else {
		Render_SetState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
//	}

	if (!Render_SetupAlphaStates(group->renderFlags)) {

		Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

		if (group->flags & MESH_GROUPFLAG_ZTESTDISABLED) Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
		else Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);

		if (group->flags & MESH_GROUPFLAG_ZWRITEDISABLED) Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
		else Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

		Render_SetState(D3DRENDERSTATE_ZBIAS, Mesh_ZBias(group));
	}

	// Setup the world transformation/blending matrices if the frame is different from last time...

	if (frame != lastRenderedFrame) {
		
		if (mesh->boneList) {

			ULONG blendCount = 0;
			D3DVERTEXBLENDFLAGS vertexBlendFlags;

			Lws_SetBoneTransforms(mesh->boneScene, mesh->boneList, &blendCount);

			switch (blendCount) {
			case 1:	vertexBlendFlags = D3DVBLEND_DISABLE;	break;
			case 2:	vertexBlendFlags = D3DVBLEND_1WEIGHT;	break;
			case 3:	vertexBlendFlags = D3DVBLEND_2WEIGHTS;	break;
			case 4:	vertexBlendFlags = D3DVBLEND_3WEIGHTS;	break;
			default: Error_Fatal(TRUE, "Too many bones to blend");
			}

			Render_SetState(D3DRENDERSTATE_VERTEXBLEND, vertexBlendFlags);

		} else {
		
			m = Maths_GetD3DMATRIX(frame->worldMatrix);
			DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_WORLD, m);
			Render_SetState(D3DRENDERSTATE_VERTEXBLEND, D3DVBLEND_DISABLE);

		}
		
	}

	for (textureIndex=0 ; textureIndex<D3DDP_MAXTEXCOORD ; textureIndex++) {

//		if (group->texture[textureIndex]) setTextureSurface = group->texture[textureIndex]->surface;
		if (group->texture[textureIndex]) setTextureSurface = Texture_GetSurface(group->texture[textureIndex]);
		else setTextureSurface = NULL;

		Render_SetTexture(textureIndex, setTextureSurface);

		if (group->texture[textureIndex]) {

//			r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), textureIndex, D3DTSS_MINFILTER, Texture_GetMinFilter(group->texture[textureIndex]));
//			r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), textureIndex, D3DTSS_MAGFILTER, Texture_GetMagFilter(group->texture[textureIndex]));
			Render_SetTextureStageState(textureIndex, D3DTSS_MINFILTER, Texture_GetMinFilter(group->texture[textureIndex]));
			Render_SetTextureStageState(textureIndex, D3DTSS_MAGFILTER, Texture_GetMagFilter(group->texture[textureIndex]));

			if (Texture_AllFlagsSet(group->texture[textureIndex], TEXTURE_FLAG_COLOURKEYED)) Render_SetState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
			else Render_SetState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

		}

	}

	r = DirectX_Device()->lpVtbl->SetMaterial(DirectX_Device(), &group->material);

	transformFlags = D3DVOP_CLIP | D3DVOP_TRANSFORM;
	if (meshVertexList->vertexInfo.srcFlags & D3DFVF_NORMAL) transformFlags |= D3DVOP_LIGHT;

	if (mesh->flags & MESH_FLAG_HIDEPOLYCALLED) {

		if ((mesh->flags & MESH_FLAG_MULTIREFERENCE) ||
			!(meshVertexList->flags & MESH_VERTEXLISTFLAG_TRANSFORMED)) {

			r = meshVertexList->transformedVertexBuffer->lpVtbl->ProcessVertices(meshVertexList->transformedVertexBuffer, transformFlags, 0, meshVertexList->visibleVertexCount, meshVertexList->visibleVertexBuffer, 0, DirectX_Device(), 0);
			meshVertexList->flags |= MESH_VERTEXLISTFLAG_TRANSFORMED;
			verticesTransformed += meshVertexList->visibleVertexCount;
		}

		r = DirectX_Device()->lpVtbl->DrawIndexedPrimitiveVB(DirectX_Device(), D3DPT_TRIANGLELIST, meshVertexList->transformedVertexBuffer, 0, meshVertexList->visibleVertexCount, group->visibleFaceData, group->visibleFaceDataSize, 0);
		polysDrawn += group->visibleFaceDataSize / group->vPerFace;

	} else {

		if ((mesh->flags & MESH_FLAG_MULTIREFERENCE) || !(meshVertexList->flags & MESH_VERTEXLISTFLAG_TRANSFORMED)) {

			{
				D3DVERTEXBUFFERDESC desc;

				DirectX_InitStruct(&desc);
				meshVertexList->vertexBuffer->lpVtbl->GetVertexBufferDesc(meshVertexList->vertexBuffer, &desc);
				
				DirectX_InitStruct(&desc);
				meshVertexList->transformedVertexBuffer->lpVtbl->GetVertexBufferDesc(meshVertexList->transformedVertexBuffer, &desc);
			}

			r = meshVertexList->transformedVertexBuffer->lpVtbl->ProcessVertices(meshVertexList->transformedVertexBuffer, transformFlags, 0, meshVertexList->internallyUsedVertexCount, meshVertexList->vertexBuffer, 0, DirectX_Device(), 0);
			Error_DirectX(r, "ProcessVertices");
			meshVertexList->flags |= MESH_VERTEXLISTFLAG_TRANSFORMED;
			verticesTransformed += meshVertexList->internallyUsedVertexCount;
		}

		r = DirectX_Device()->lpVtbl->DrawIndexedPrimitiveVB(DirectX_Device(), D3DPT_TRIANGLELIST, meshVertexList->transformedVertexBuffer, 0, meshVertexList->internallyUsedVertexCount, group->faceData, group->usedFaceDataSize, 0);
		polysDrawn += group->usedFaceDataSize / group->vPerFace;
	}

	return polysDrawn;
}

/*
ULONG Mesh_RenderList(ULONG ambientColour) {

	ULONG loop, polysDrawn = 0, verticesTransformed = 0, textureIndex;
	LPDIRECTDRAWSURFACE7 setTextureSurface;//, lastTextureSurface[D3DDP_MAXTEXCOORD];
	lpMeshRenderEntry entry;
	lpFrame lastFrame = NULL;
	lpMeshGroup group;
	lpMeshVertexList meshVertexList;
	ULONG transformFlags;
	lpMesh mesh;
	LPD3DMATRIX m;
	HRESULT r;

	qsort(meshGlobs.renderList, meshGlobs.renderCount, sizeof(meshGlobs.renderList[0]), Mesh_RenderListSortCallback);

//	r = DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
//	Error_DirectX(r, "BeginScene");
	Render_BeginScene();

//	for (textureIndex=0 ; textureIndex<D3DDP_MAXTEXCOORD ; textureIndex++) {
//		r = DirectX_Device()->lpVtbl->GetTexture(DirectX_Device(), textureIndex, &lastTextureSurface[textureIndex]);
//		Error_DirectX(r, "GetTexture");
//	}

	r = DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_AMBIENT, ambientColour);
//	if (Dialog_GetOption(DialogOption_NoPersCorr)) {
//		r = DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_TEXTUREPERSPECTIVE, FALSE);
//	} else {
		r = DirectX_Device()->lpVtbl->SetRenderState(DirectX_Device(), D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
//	}

	for (loop=0 ; loop<meshGlobs.renderCount ; loop++) {

		entry = &meshGlobs.renderList[loop];
		group = entry->group;
		mesh = entry->mesh;
		meshVertexList = &mesh->vertexListList[group->vertexListIndex];

#ifdef _DEBUG
		if (mesh == debugStopMesh) {
			ULONG a = 10;
		}
#endif // _DEBUG

		if (group->flags & MESH_GROUPFLAG_SUBTRACTIVE) {
 
			Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ZERO);
			Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCCOLOR);

			Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);

		} else if (group->flags & MESH_GROUPFLAG_ADDITIVE1) {

			Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
			Render_SetState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
			Render_SetState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

			Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);			

		} else {

			Render_SetState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

			if (group->flags & MESH_GROUPFLAG_ZTESTDISABLED) Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
			else Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);

			if (group->flags & MESH_GROUPFLAG_ZWRITEDISABLED) Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
			else Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

			Render_SetState(D3DRENDERSTATE_ZBIAS, Mesh_ZBias(group));
		}

		if (entry->frame != lastFrame) {

			if (lastFrame) Light_EnableLights(lastFrame, FALSE);
			Light_EnableLights(entry->frame, TRUE);
			
			if (mesh->boneList) {
				ULONG blendCount = 0;
				D3DVERTEXBLENDFLAGS vertexBlendFlags;

				Lws_SetBoneTransforms(mesh->boneScene, mesh->boneList, &blendCount);

				switch (blendCount) {
				case 1:	vertexBlendFlags = D3DVBLEND_DISABLE;	break;
				case 2:	vertexBlendFlags = D3DVBLEND_1WEIGHT;	break;
				case 3:	vertexBlendFlags = D3DVBLEND_2WEIGHTS;	break;
				case 4:	vertexBlendFlags = D3DVBLEND_3WEIGHTS;	break;
				default: Error_Fatal(TRUE, "Too many bones to blend");
				}
				Render_SetState(D3DRENDERSTATE_VERTEXBLEND, vertexBlendFlags);
			} else {
				m = Maths_GetD3DMATRIX(entry->frame->worldMatrix);
				DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_WORLD, m);
				Render_SetState(D3DRENDERSTATE_VERTEXBLEND, D3DVBLEND_DISABLE);
			}
			
			lastFrame = entry->frame;
		}

		for (textureIndex=0 ; textureIndex<D3DDP_MAXTEXCOORD ; textureIndex++) {

			if (group->texture[textureIndex]) setTextureSurface = group->texture[textureIndex]->surface;
			else setTextureSurface = NULL;

//			if (setTextureSurface != lastTextureSurface[textureIndex]) {

//				if (Dialog_GetOption(DialogOption_NoTextures)) {
//					r = DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), textureIndex, NULL);
//					Render_SetTexture(textureIndex, NULL);
//				} else {
//					r = DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), textureIndex, setTextureSurface);
					Render_SetTexture(textureIndex, setTextureSurface);
//				}
//				lastTextureSurface[textureIndex] = setTextureSurface;

				if (group->texture[textureIndex]) {

					r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), textureIndex, D3DTSS_MINFILTER, Texture_GetMinFilter(group->texture[textureIndex]));
					r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), textureIndex, D3DTSS_MAGFILTER, Texture_GetMagFilter(group->texture[textureIndex]));
//					r = DirectX_Device()->lpVtbl->SetTextureStageState(DirectX_Device(), textureIndex, D3DTSS_MIPFILTER, Texture_GetMipFilter(group->texture[textureIndex]));

					if (Texture_AllFlagsSet(group->texture[textureIndex], TEXTURE_FLAG_COLOURKEYED)) Render_SetState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
					else Render_SetState(D3DRENDERSTATE_COLORKEYENABLE, FALSE);

				}

//				r = Render_SetState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
//				Error_DirectX(r, "SetRenderState");

//			}
		}

		r = DirectX_Device()->lpVtbl->SetMaterial(DirectX_Device(), &group->material);

		transformFlags = D3DVOP_CLIP | D3DVOP_TRANSFORM;
		if (meshVertexList->vertexInfo.srcFlags & D3DFVF_NORMAL) transformFlags |= D3DVOP_LIGHT;

		if (mesh->flags & MESH_FLAG_HIDEPOLYCALLED) {

			if ((mesh->flags & MESH_FLAG_MULTIREFERENCE) ||
				!(meshVertexList->flags & MESH_VERTEXLISTFLAG_TRANSFORMED)) {

				r = meshVertexList->transformedVertexBuffer->lpVtbl->ProcessVertices(meshVertexList->transformedVertexBuffer, transformFlags, 0, meshVertexList->visibleVertexCount, meshVertexList->visibleVertexBuffer, 0, DirectX_Device(), 0);
				meshVertexList->flags |= MESH_VERTEXLISTFLAG_TRANSFORMED;
				verticesTransformed += meshVertexList->visibleVertexCount;
			}

			r = DirectX_Device()->lpVtbl->DrawIndexedPrimitiveVB(DirectX_Device(), D3DPT_TRIANGLELIST, meshVertexList->transformedVertexBuffer, 0, meshVertexList->visibleVertexCount, group->visibleFaceData, group->visibleFaceDataSize, 0);
			polysDrawn += group->visibleFaceDataSize / group->vPerFace;

		} else {

			if ((mesh->flags & MESH_FLAG_MULTIREFERENCE) || !(meshVertexList->flags & MESH_VERTEXLISTFLAG_TRANSFORMED)) {

				{
					D3DVERTEXBUFFERDESC desc;

					DirectX_InitStruct(&desc);
					meshVertexList->vertexBuffer->lpVtbl->GetVertexBufferDesc(meshVertexList->vertexBuffer, &desc);
					
					DirectX_InitStruct(&desc);
					meshVertexList->transformedVertexBuffer->lpVtbl->GetVertexBufferDesc(meshVertexList->transformedVertexBuffer, &desc);
				}

				r = meshVertexList->transformedVertexBuffer->lpVtbl->ProcessVertices(meshVertexList->transformedVertexBuffer, transformFlags, 0, meshVertexList->internallyUsedVertexCount, meshVertexList->vertexBuffer, 0, DirectX_Device(), 0);
				Error_DirectX(r, "ProcessVertices");
				meshVertexList->flags |= MESH_VERTEXLISTFLAG_TRANSFORMED;
				verticesTransformed += meshVertexList->internallyUsedVertexCount;
			}

			r = DirectX_Device()->lpVtbl->DrawIndexedPrimitiveVB(DirectX_Device(), D3DPT_TRIANGLELIST, meshVertexList->transformedVertexBuffer, 0, meshVertexList->internallyUsedVertexCount, group->faceData, group->usedFaceDataSize, 0);
			polysDrawn += group->usedFaceDataSize / group->vPerFace;
		}

//		r = Direct3D_Device()->lpVtbl->DrawIndexedPrimitive(Direct3D_Device(), D3DPT_TRIANGLELIST, MESH_VERTEX_FLAGS, group->vertices, group->visibleVertexCount, group->faceData, group->visibleFaceDataSize, 0);
//		Error_DirectX(r, "DrawIndexedPrimitive");

//		polysDrawn += group->visibleFaceDataSize / group->vPerFace;
	}

	if (lastFrame) Light_EnableLights(lastFrame, FALSE);

//	r = DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
//	Error_DirectX(r, "EndScene");
	Render_EndScene();

	Mesh_ClearRenderList();

	return polysDrawn;
}
*/
/*
static BOOL Mesh_ClearRenderListCallback(LPVOID item, LPVOID data) {

	lpMesh mesh = item;

	if (mesh->flags & MESH_FLAG_ADDED) {
		mesh->flags &= ~MESH_FLAG_ADDED;
		Mesh_Reset(mesh);
	}

	return FALSE;
}
*/
/*
static VOID Mesh_ClearRenderList(VOID) {

//	List_RunThrough(meshGlobs.list, Mesh_ClearRenderListCallback, NULL);
	lpMeshRenderEntry entry;
	lpMesh mesh;
	ULONG loop;

	for (loop=0 ; loop<meshGlobs.renderCount ; loop++) {
		entry = &meshGlobs.renderList[loop];
		mesh = entry->mesh;

		Mesh_Reset(mesh);
	}

	meshGlobs.renderCount = 0;
}

int __cdecl Mesh_RenderListSortCallback(const void *a, const void *b) {

	lpMeshRenderEntry entryA = (lpMeshRenderEntry) a;
	lpMeshRenderEntry entryB = (lpMeshRenderEntry) b;
	ULONG loop, count = sizeof(entryA->group->texture) / sizeof(entryA->group->texture[0]);

	// Sort the objects that have an absolute priority set.

	if ((entryA->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY) && !(entryB->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY)) return -1;
	if (!(entryA->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY) && (entryB->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY)) return 1;
	if ((entryA->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY) && (entryB->frame->flags & FRAME_FLAG_ABSOLUTEPRIORITY)) {
		if (entryA->frame->priority > entryB->frame->priority) return -1;
		if (entryA->frame->priority < entryB->frame->priority) return 1;
	}

	// Sort by transparency then by texture.

	if ((entryA->group->flags & MESH_GROUPFLAG_ADDITIVE1) && !(entryB->group->flags & MESH_GROUPFLAG_ADDITIVE1)) return 1;
	if (!(entryA->group->flags & MESH_GROUPFLAG_ADDITIVE1) && (entryB->group->flags & MESH_GROUPFLAG_ADDITIVE1)) return -1;
	if ((entryA->group->flags & MESH_GROUPFLAG_SUBTRACTIVE) && !(entryB->group->flags & MESH_GROUPFLAG_SUBTRACTIVE)) return 1;
	if (!(entryA->group->flags & MESH_GROUPFLAG_SUBTRACTIVE) && (entryB->group->flags & MESH_GROUPFLAG_SUBTRACTIVE)) return -1;

//	for (loop=0 ; loop<count ; loop++) {
//		if (entryA->group->texture[loop] && entryB->group->texture[loop]) {
//			if (Texture_GetPriority(entryA->group->texture[loop]) > Texture_GetPriority(entryB->group->texture[loop])) return -1;
//			if (Texture_GetPriority(entryA->group->texture[loop]) < Texture_GetPriority(entryB->group->texture[loop])) return 1;
//		}
//	}


//	for (loop=0 ; loop<count ; loop++) {
//		if ((ULONG) entryA->group->texture[loop] > (ULONG) entryB->group->texture[loop]) return 1;
//		if ((ULONG) entryA->group->texture[loop] < (ULONG) entryB->group->texture[loop]) return -1;
//	}

	for (loop=0 ; loop<count ; loop++) {
		if (entryA->group->texture[loop] != entryB->group->texture[loop]) {
			if (NULL == entryA->group->texture[loop]) return -1;
			if (NULL == entryB->group->texture[loop]) return 1;
			if (Texture_GetPriority(entryA->group->texture[loop]) > Texture_GetPriority(entryB->group->texture[loop])) return -1;
			if (Texture_GetPriority(entryA->group->texture[loop]) < Texture_GetPriority(entryB->group->texture[loop])) return 1;
			if ((ULONG) entryA->group->texture[loop] > (ULONG) entryB->group->texture[loop]) return -1;
			if ((ULONG) entryA->group->texture[loop] < (ULONG) entryB->group->texture[loop]) return 1;
		}
	}

	if ((ULONG) entryA->frame > (ULONG) entryB->frame) return 1;
	if ((ULONG) entryA->frame < (ULONG) entryB->frame) return -1;

//	if (entryA->frame->priority > entryB->frame->priority) return -1;
//	if (entryA->frame->priority < entryB->frame->priority) return 1;

	return 0;
}
*/

/*
VOID Mesh_TestCode_SetupRender(VOID) {

	LPDIRECT3DMATERIAL3 materialObject;
	D3DMATERIAL material;
	D3DMATERIALHANDLE materialHandle;
	HRESULT r;

	{
		static BOOL created = FALSE;
		if (!created) {
			r = DirectX_Direct3D()->lpVtbl->CreateMaterial(DirectX_Direct3D(), &materialObject, NULL);
			Error_DirectX(r, "CreateMaterial");

			memset(&material, 0, sizeof(D3DMATERIAL));
			material.dwSize = sizeof(D3DMATERIAL);
			material.dcvAmbient.r = 1.0f;
			material.dcvAmbient.g = 1.0f;
			material.dcvAmbient.b = 1.0f;
			material.dcvDiffuse.r = 1.0f;
			material.dcvDiffuse.g = 1.0f;
			material.dcvDiffuse.b = 1.0f;

			r = materialObject->lpVtbl->SetMaterial(materialObject, &material);
			Error_DirectX(r, "SetMaterial");
			r = materialObject->lpVtbl->GetHandle(materialObject, DirectX_Device(), &materialHandle);
			Error_DirectX(r, "GetHandle2);
			
			r = DirectX_Device()->lpVtbl->SetLightState(DirectX_Device(), D3DLIGHTSTATE_MATERIAL, materialHandle);
			Error_DirectX(r, "SetLightState");

			created = TRUE;
		}
	}

	r = DirectX_Device()->lpVtbl->SetLightState(DirectX_Device(), D3DLIGHTSTATE_AMBIENT, 0x00202020);
	Error_DirectX(r, "SetLightState");

	r = DirectX_Device()->lpVtbl->SetLightState(DirectX_Device(), D3DLIGHTSTATE_COLORVERTEX, TRUE);
	Error_DirectX(r, "SetLightState");

	r = Render_SetState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);
	Error_DirectX(r, "SetRenderState");
//	r = Render_SetState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
//	Error_DirectX(r, "SetRenderState");
	r = Render_SetState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
	Error_DirectX(r, "SetRenderState");
	r = Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	Error_DirectX(r, "SetRenderState");
	r = Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
	Error_DirectX(r, "SetRenderState");
}
*/

struct Mesh_TestCode_Vertex {

	VECTOR4D pos;
	ULONG colour;
};

VOID Mesh_TestCode_ClipTest(VOID) {

	static REAL x = 0.0f;
	struct Mesh_TestCode_Vertex vertices[3] =
	{
		{ { x, 100.0f, 0.5f, 1.0f }, 0x00ff0000 },
		{ { x + 100.0f, 150.0f + (x / 1.5f), 0.5f, 1.0f }, 0x0000ff00 },
		{ { x, 200.0f, 0.5f, 1.0f }, 0x000000ff }
	};

//	DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
	Render_BeginScene();
	DirectX_Device()->lpVtbl->DrawPrimitive(DirectX_Device(), D3DPT_TRIANGLELIST, D3DFVF_XYZRHW|D3DFVF_DIFFUSE, vertices, 3, D3DDP_DONOTCLIP);
//	DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
	Render_EndScene();

	if ((x += 1.0f) > 700) x = -100.0f;
}

/*
VOID Mesh_Render(lpMesh mesh, MATRIX4D mat) {

	HRESULT r;
	ULONG loop;
	lpMesh_Group group;
	LPD3DMATRIX m;
	LPDIRECT3DMATERIAL3 materialObject;
	D3DMATERIAL material;
	D3DMATERIALHANDLE materialHandle;

//	Mesh_CullFaces(mesh, camPos, camDir);		// This doesn't really make an improvement
												// and makes a massive loss if the object is in the scene twice...

	m = Maths_GetD3DMATRIX(mat);
	r = DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), D3DTRANSFORMSTATE_WORLD, m);
//	r = DirectX_Device()->lpVtbl->BeginScene(DirectX_Device());
	Render_BeginScene();

	{
		static BOOL created = FALSE;
		if (!created) {
			DirectX_Direct3D()->lpVtbl->CreateMaterial(DirectX_Direct3D(), &materialObject, NULL);
			memset(&material, 0, sizeof(D3DMATERIAL));
			material.dwSize = sizeof(D3DMATERIAL);
			material.dcvAmbient.r = 1.0f;
			material.dcvAmbient.g = 1.0f;
			material.dcvAmbient.b = 1.0f;
			material.dcvDiffuse.r = 1.0f;
			material.dcvDiffuse.g = 1.0f;
			material.dcvDiffuse.b = 1.0f;

			materialObject->lpVtbl->SetMaterial(materialObject, &material);
			materialObject->lpVtbl->GetHandle(materialObject, DirectX_Device(), &materialHandle);
			
			DirectX_Device()->lpVtbl->SetLightState(DirectX_Device(), D3DLIGHTSTATE_MATERIAL, materialHandle);

			created = TRUE;
		}
	}

	DirectX_Device()->lpVtbl->SetLightState(DirectX_Device(), D3DLIGHTSTATE_AMBIENT,  0x00202020);

	{
		ULONG renderCount=0;
		for (loop=0 ; loop<mesh->groupCount ; loop++) {
			group = &mesh->groupList[loop];
			renderCount += (group->visibleFaceDataSize / 3);
		}
		renderCount=0;
	}


	for (loop=0 ; loop<mesh->groupCount ; loop++) {

		group = &mesh->groupList[loop];

		r = DirectX_Device()->lpVtbl->SetTexture(DirectX_Device(), 0, group->texture);
		r = Render_SetState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);
//		r = Render_SetState(D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
		r = Render_SetState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
		r = Render_SetState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
		r = DirectX_Device()->lpVtbl->DrawIndexedPrimitive(DirectX_Device(), D3DPT_TRIANGLELIST, MESH_VERTEX_FLAGS, group->vertices, group->visibleVertexCount, group->faceData, group->visibleFaceDataSize, 0);

	}

//	r = DirectX_Device()->lpVtbl->EndScene(DirectX_Device());
	Render_EndScene();
}
*/

/*
#include "Viewports.h"

struct Debug_Vertex {

	VECTOR3D position;
	REAL tu, tv;
};

VOID Mesh_Debug_DrawViewFrustum(lpFrame root, lpFrame fakeCamera, lpFrame renderCamera, lpViewport vp) {

	REAL width = (REAL) Viewport_GetWidth(vp);
	REAL height = (REAL) Viewport_GetHeight(vp);
	ULONG loop;
	VECTOR3D box[8];
	VECTOR3D scrBox[8] = {
		{ 0.0f, 0.0f, 0.0f }, { width, 0.0f, 0.0f }, { width, height, 0.0f }, { 0.0f, height, 0.0f },
		{ 0.0f, 0.0f, 1.0f }, { width, 0.0f, 1.0f }, { width, height, 1.0f }, { 0.0f, height, 1.0f }
	};
	UWORD faceData[12] = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
	struct Debug_Vertex vertices[8];

	for (loop=0 ; loop<8 ; loop++) {
		Viewport_InverseTransform(vp, root, fakeCamera, &box[loop], &scrBox[loop]);
	}

	for (loop=0 ; loop<8 ; loop++) {
		Viewport_Transform(vp, root, renderCamera, &scrBox[loop], &box[loop]);
		vertices[loop].position = scrBox[loop];
	}

//	Direct3D_Device()->lpVtbl->SetRenderState(Direct3D_Device(), D3DRENDERSTATE_FILLMODE, D3DFILL_WIREFRAME);
	Direct3D_Device()->lpVtbl->DrawIndexedPrimitive(Direct3D_Device(), D3DPT_TRIANGLELIST, D3DFVF_XYZRHW|D3DFVF_TEX1, vertices, 8, faceData, 12, 0);
//	Direct3D_Device()->lpVtbl->SetRenderState(Direct3D_Device(), D3DRENDERSTATE_FILLMODE, D3DFILL_SOLID);
}
*/
/*
VOID Mesh_HidePoly(lpMesh mesh, UWORD poly, BOOL hide) {

	BOOL hidden = (mesh->faceArray[poly].flags & MESH_FACEFLAG_HIDDEN);
	UWORD buffer[MESH_MAXPOLYSIDES];
	UWORD loop, vertexID, swap;

	if (hide && !hidden) {

		UWORD hideIndex;
		UWORD swapIndex;
		lpMesh_Face hideFace;
		lpMesh_Face swapFace;
		lpMesh_Group group;

		// Need a 'face index' list that holds the face ID number so that list[position in array / vPerFace] == faceID..

		hideIndex = poly;
		swapIndex = group->visibleFaceDataSize / group->vPerFace;
		hideFace = &mesh->faceArray[hideIndex];
		group = &mesh->groupList[hideFace->group];

		// Swap the definition (a list of vertex indices) of the polygon to be hidden with
		// that of the LAST VISIBLE polygon in the list...

//		Error_Fatal(0==group->shownFaceCount, "shownFaceCount about to go sub zero!");
//		group->shownFaceCount--;
//		swapFace = &mesh->faceArray[group->shownFaceList[group->shownFaceCount]];

		group->visibleFaceDataSize -= group->vPerFace;
		swapFace = &mesh->faceArray[group->linkBackData[group->visibleFaceDataSize / group->vPerFace]];

		Mem_Copy(buffer, &group->faceData[swapFace->listIndex], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[swapFace->listIndex], &group->faceData[hideFace->listIndex], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[hideFace->listIndex], buffer, sizeof(UWORD) * group->vPerFace);

		// Swap the pointers to where these moved polys now lie in the list...
		swap = swapFace->listIndex;
		swapFace->listIndex = hideFace->listIndex;
		hideFace->listIndex = swap;

		// Update the link back data...
		group->linkBackData[group->visibleFaceDataSize / group->vPerFace] = poly;
		group->linkBackData[swapFace->listIndex / 3] = 

		// Flag the face as being hidden and reduce the size of the face data...
		hideFace->flags |= MESH_FACEFLAG_HIDDEN;
//		group->visibleFaceDataSize -= group->vPerFace;

		// Append this face to the hidden face list...
//		group->hiddenFaceList[group->hiddenFaceCount] = poly;
//		group->hiddenFaceCount++;

		// Flag the vertices that the hidden polygon is no longer using them...
		for (loop=0 ; loop<group->vPerFace ; loop++) {
			vertexID = group->faceData[hideFace->listIndex + loop];
			if ((group->vertexFlags[vertexID] & MESH_VERTEXFLAG_SINGLE) ||
				(group->vertexFlags[vertexID] & MESH_VERTEXFLAG_UNLINKED)) {

				// The vertex is no longer used by any polygon...
				Mesh_VertexUnused(mesh, group, vertexID);

			} else group->vertexFlags[vertexID] |= MESH_VERTEXFLAG_UNLINKED;
		}

	} else if (!hide && hidden) {

		lpMesh_Face showFace = &mesh->faceArray[poly];
		lpMesh_Face swapFace;
		lpMesh_Group group = &mesh->groupList[showFace->group];

//		Error_Fatal(0==group->hiddenFaceCount, "hiddenFaceCount about to go sub zero!");
//		group->hiddenFaceCount--;
//		swapFace = &mesh->faceArray[group->hiddenFaceList[group->hiddenFaceCount]];

		Mem_Copy(buffer, &group->faceData[swapFace->listIndex], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[swapFace->listIndex], &group->faceData[showFace->listIndex], sizeof(UWORD) * group->vPerFace);
		Mem_Copy(&group->faceData[showFace->listIndex], buffer, sizeof(UWORD) * group->vPerFace);

		swap = swapFace->listIndex;
		swapFace->listIndex = showFace->listIndex;
		showFace->listIndex = swap;

		showFace->flags &= ~MESH_FACEFLAG_HIDDEN;
		group->visibleFaceDataSize += group->vPerFace;

//		group->shownFaceList[group->shownFaceCount] = poly;
//		group->shownFaceCount++;

	}
}
*/









/*
// Shelved - neglegable speed improvement...
VOID Mesh_GenerateFaceNormals(lpMesh mesh) {

	ULONG loop;
	lpMesh_Face face;
	lpMesh_Group group;

	for (loop=0 ; loop<mesh->faceCount ; loop++) {
		face = &mesh->faceArray[loop];
		group = &mesh->groupList[face->group];
		Maths_PlaneNormal(&face->normal, &group->vertices[group->faceData[face->listIndex+0]].position, &group->vertices[group->faceData[face->listIndex+1]].position, &group->vertices[group->faceData[face->listIndex+2]].position);
	}
}
static VOID Mesh_CullFaces(lpMesh mesh, LPVECTOR3D camPos, LPVECTOR3D camDir) {

	UWORD loop;
	BOOL hidden;
	lpMesh_Face face;
	lpMesh_Group group;
	BOOL bfcOnly = !(mesh->flags & MESH_FLAG_BFCVISIBLE);

	if (bfcOnly) {			// No clever OctTree visible face insertion preceded this function...

		for (loop=0 ; loop<mesh->faceCount ; loop++) {
			face = &mesh->faceArray[loop];
			group = &mesh->groupList[face->group];
			Mesh_HidePoly(mesh, loop, Mesh_BackFaceCullTest(mesh, face, group, camPos, camDir));
		}

	} else {
		for (loop=0 ; loop<mesh->faceCount ; loop++) {

			face = &mesh->faceArray[loop];
			group = &mesh->groupList[face->group];
			hidden = (face->listIndex >= group->visibleFaceDataSize);
			
			if (!hidden) {
				if (!(face->flags & MESH_FACEFLAG_FRESH) || Mesh_BackFaceCullTest(mesh, face, group, camPos, camDir)) {
					Mesh_HidePoly(mesh, loop, TRUE);
				}
			}
			face->flags &= ~MESH_FACEFLAG_FRESH;
		}
	}
}
__inline static BOOL Mesh_BackFaceCullTest(lpMesh mesh, lpMesh_Face face, lpMesh_Group group, LPVECTOR3D camPos, LPVECTOR3D camDir) {

	REAL dp;
	VECTOR3D cpVec;

	Maths_Vector3DSubtract(&cpVec, camPos, &group->vertices[group->faceData[face->listIndex]].position);
	Maths_Vector3DNormalise(&cpVec);
	dp = Maths_Vector3DDotProduct(&cpVec, &face->normal);
	if (dp < 0.0f) return TRUE;
	else return FALSE;
}
*/
