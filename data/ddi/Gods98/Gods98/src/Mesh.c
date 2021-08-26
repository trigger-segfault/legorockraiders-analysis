

#include <d3drm.h>


#include "..\Inc\Memory.h"
#include "..\Inc\Errors.h"
#include "..\Inc\Main.h"
#include "..\Inc\Viewports.h"
#include "..\Inc\Mesh.h"
#include "..\Inc\Containers.h"
#include "..\Inc\Bmp.h"
#include "..\Inc\DirectDraw.h"
#include "..\Inc\Maths.h"
#include "..\Inc\Utils.h"



#define RELEASE(x) {if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}}



Mesh_Globs meshGlobs = { NULL };



static BOOL Mesh_SetMaterial( LPD3DMATERIAL newMaterial )
{
	Mesh_Debug_CheckIMDevice_Int();

	if( D3D_OK != meshGlobs.imMat->lpVtbl->SetMaterial(meshGlobs.imMat, newMaterial) )
	{	
		Error_Warn( TRUE, "Cannot 'SetMaterial'." );

		return FALSE;
	}

	return TRUE;
}


static BOOL Mesh_CreateGlobalMaterial( VOID )
{
	LPDIRECT3D3 imd3d;
	D3DMATERIAL material =
	{
		sizeof(D3DMATERIAL),
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		0.0f,
		0,
		0
	};


	Mesh_Debug_CheckIMDevice_Int();
	
	lpIMDevice()->lpVtbl->GetDirect3D( lpIMDevice(), &imd3d );
	
	if( D3D_OK != imd3d->lpVtbl->CreateMaterial( imd3d, &meshGlobs.imMat, NULL ) )
	{	
		Error_Warn( TRUE, "Cannot 'CreateMaterial'." );
		RELEASE( imd3d );

		return FALSE;
	}

	if( D3D_OK != meshGlobs.imMat->lpVtbl->GetHandle(meshGlobs.imMat, lpIMDevice(), &meshGlobs.matHandle) )
	{	
		Error_Warn( TRUE, "Cannot 'GetHandle' for material." );
		RELEASE( imd3d );

		return FALSE;
	}

	//SET UP ANY MATERIAL AS DEFAULT
	Mesh_SetMaterial( &material );

	RELEASE( imd3d );

	return TRUE;
}


BOOL Mesh_Initialise(LPUCHAR sharedTextureDir)
{
	ULONG len;
	ULONG loop;

	meshGlobs.postRenderMeshList = NULL;

	Mesh_ClearPostRenderList();
	
	if (sharedTextureDir){
		len = strlen(sharedTextureDir);
		if ('\\' != sharedTextureDir[len-1]) len++;
		meshGlobs.sharedTextureDir = Mem_Alloc(len+1);
		strcpy(meshGlobs.sharedTextureDir, sharedTextureDir);
		meshGlobs.sharedTextureDir[len-1] = '\\';
		meshGlobs.sharedTextureDir[len] = '\0';
	}

	for (loop=0 ; loop<MESH_MAXLISTS ; loop++){
		meshGlobs.listSet[loop] = NULL;
	}

	meshGlobs.freeList = NULL;
	meshGlobs.listCount = 0;

	Mesh_CreateGlobalMaterial();

	return TRUE;
}

lpMesh Mesh_ObtainFromList(VOID){

	lpMesh newMesh;

	if (NULL == meshGlobs.freeList) Mesh_AddList();
	
	newMesh = meshGlobs.freeList;
	meshGlobs.freeList = newMesh->nextFree;
	memset(newMesh, 0, sizeof(Mesh));
	newMesh->nextFree = newMesh;

	// Initialise any elements of your structure here...

	return newMesh;
}

VOID Mesh_ReturnToList(lpMesh dead){

	Error_Fatal(!dead, "NULL passed to Mesh_Remove()");

	dead->nextFree = meshGlobs.freeList;
	meshGlobs.freeList = dead;
}

static VOID Mesh_AddList(VOID){

	lpMesh list;
	ULONG loop, count;

	Error_Fatal(meshGlobs.listCount+1 >= MESH_MAXLISTS, "Run out of lists");

	count = 0x00000001 << meshGlobs.listCount;

	if (list = meshGlobs.listSet[meshGlobs.listCount] = 
		Mem_Alloc(sizeof(Mesh) * count)){

		meshGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = meshGlobs.freeList;
		meshGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Mesh) * count));
}

static VOID Mesh_RunThroughLists(VOID){

	ULONG list, count, loop;
	lpMesh tempMesh;

	for (list=0 ; list<meshGlobs.listCount ; list++){
		if (meshGlobs.listSet[list]){
			count = 0x00000001 << list;
			for (loop=0 ; loop<count ; loop++){
				if (tempMesh = &meshGlobs.listSet[list][loop]){
					if (tempMesh->nextFree == tempMesh){

						// This is a valid unremoved mesh....
	
					}
				}
			}
		}
	}
}

lpMesh Mesh_CreateOnFrame( LPDIRECT3DRMFRAME3 frame, VOID (*renderFunc)( lpMesh mesh, LPVOID data, lpViewport vp ), ULONG renderFlags, LPVOID data, ULONG type ) 
{	
//	lpMesh mesh = Mem_Alloc( sizeof(Mesh) );
	lpMesh mesh = Mesh_ObtainFromList();
	lpContainer rootCont = Container_GetRoot();


	Mesh_Debug_CheckIMDevice_Ptr();

//	memset( mesh, 0, sizeof(Mesh) );

	lpD3DRM()->lpVtbl->CreateUserVisual( lpD3DRM(), Mesh_RenderCallback, mesh, &mesh->uv );
	Container_NoteCreation( mesh->uv );
	frame->lpVtbl->AddVisual( frame, (struct IUnknown *) mesh->uv );
	mesh->uv->lpVtbl->SetAppData( mesh->uv, (DWORD) mesh );
	mesh->frameCreatedOn = frame;

	mesh->renderDesc.renderCallback = renderFunc;
	mesh->renderDesc.renderCallbackData = data;
	mesh->renderDesc.renderFlags = renderFlags;

	if( Mesh_Type_PostEffect == type )
		mesh->flags |= MESH_FLAG_POSTEFFECT;
	else if( Mesh_Type_LightWaveObject == type )
		mesh->flags |= MESH_FLAG_LWO;

	mesh->numOfRefs = 1;

	mesh->textureRenderCallback = NULL;

	return mesh;
}


lpMesh Mesh_Clone(lpMesh mesh, LPDIRECT3DRMFRAME3 frame){

	ULONG loop;
//	lpMesh newMesh = Mem_Alloc(sizeof(Mesh));
	lpMesh newMesh = Mesh_ObtainFromList();
	HRESULT r;

	if (mesh->clonedFrom) mesh = mesh->clonedFrom;

	*newMesh = *mesh;
	newMesh->clonedFrom = mesh;

	newMesh->listSize = newMesh->groupCount;
	newMesh->groupList = Mem_Alloc(sizeof(Mesh_Group) * newMesh->groupCount);
	memcpy(newMesh->groupList, mesh->groupList, sizeof(Mesh_Group) * newMesh->groupCount);

	for (loop=0 ; loop<newMesh->groupCount ; loop++) {
		Mesh_CreateGroupMaterial(newMesh, loop);
		Mesh_SetGroupMaterial(newMesh, loop, &mesh->groupList[loop].material);
	}

	r = lpD3DRM()->lpVtbl->CreateUserVisual(lpD3DRM(), Mesh_RenderCallback, newMesh, &newMesh->uv);
	Container_NoteCreation(newMesh->uv);
	frame->lpVtbl->AddVisual(frame, (struct IUnknown *) newMesh->uv);
	newMesh->uv->lpVtbl->SetAppData(newMesh->uv, (DWORD) newMesh);
	newMesh->frameCreatedOn = frame;

	mesh->numOfRefs++;
	mesh->flags |= MESH_FLAG_HASBEENCLONED;

	newMesh->numOfRefs = 0;

	return newMesh;
}


VOID Mesh_AddToContainer( lpContainer cont, lpMesh mesh )
{
	cont->activityFrame->lpVtbl->AddVisual( cont->activityFrame, (struct IUnknown *) mesh->uv );

	//REGISTER THE CLONE - SHOULD THERE BE A LIMIT?
	mesh->numOfRefs++;

}


lpMesh Mesh_Load( LPUCHAR fname, LPDIRECT3DRMFRAME3 frame , BOOL noTextures)
{	APPOBJ *lightWaveObject;
	lpMesh mesh;
	UCHAR path[FILE_MAXPATH];
	LPUCHAR s, t;


	strcpy( path, fname );
	for( s = t = path; '\0' != *s; s++ )
	{
		if( '\\' == *s )
			t = s;
	}
	*( t + (t != path ? 1 : 0) ) = '\0';

//	if( LoadAppObj(fname, &lightWaveObject, TRUE) )
	if( LoadAppObj(fname, &lightWaveObject, FALSE) )
	{
		mesh = Mesh_CreateOnFrame( frame, NULL, MESH_RENDERFLAGS_LWOALPHA, NULL, Mesh_Type_LightWaveObject );
		Mesh_ParseLWO( path, mesh, lightWaveObject, noTextures );
		FreeLWOB( lightWaveObject );

		return mesh;
	} 

	return NULL;
}

	
BOOL Mesh_ParseLWO(LPUCHAR basePath, lpMesh mesh, APPOBJ *lightWaveObject, BOOL noTextures )
{	
	ULONG face, vertex;
	VECTOR3D pos[3];
	ULONG faceDataQuad[] = { 0, 1, 2, 0, 2, 3 };
	REAL textCoords[][2] = {
		{0,1}, {0,0}, {1,0}, {1,1}
	};
	ULONG group, loop, newFlags;
	LPULONG surfVertexRef;
	LPVECTOR3D surfVertices;
	LPVECTOR3D *surfVerticesNorm;
	LPULONG surfFaceData;
	LPULONG surfVertexCount;
	LPULONG surfFaceDataCount;
	LPVECTOR3D faceNorm;
	LPVECTOR3D vertexNorm;
	LPVECTOR2D vertexUVs = NULL;
	LPVECTOR2D surfTextCoords;
	ULONG size = lightWaveObject->aoSize.lwVertCount*2;
	ULONG fDSize = lightWaveObject->aoSize.lwPolyCount*6;
//	BOOL first = TRUE;
	ULONG vertexIndex, surfArraySize, surfFDArraySize;


	Error_Fatal( !lightWaveObject->aoSize.lwSurfaceCount, "LightWave object must contain at least one surface." );

#define MESH_MAXPOLYSPERVETEX		20

	//GET TEXTURE AND TEXTURE COORDINATES FOR VERTICES IF UVIEW FILE EXISTS
	//NEED TO CALL THIS FIRST BECAUSE THE LIGHTWAVE STRUCTURE MAY BE ALTERED
	if( lightWaveObject->aoFileUV )
	{	vertexUVs = Mem_Alloc( sizeof(VECTOR2D) * size * MESH_MAXPOLYSPERVETEX);
		Mesh_UViewMesh( lightWaveObject, vertexUVs );
		Error_Fatal(size * MESH_MAXPOLYSPERVETEX < lightWaveObject->aoSize.lwVertCount, "MESH_MAXPOLYSPERVETEX too small");

		size = lightWaveObject->aoSize.lwVertCount*2;
		surfTextCoords = Mem_Alloc( sizeof(VECTOR2D) * lightWaveObject->aoSize.lwSurfaceCount * size );
	}
	else
		surfTextCoords = Mem_Alloc( sizeof(VECTOR2D) * size );


	//ALLOCATE MEMORY FOR OBJECT
	surfArraySize = lightWaveObject->aoSize.lwSurfaceCount*size;

	surfVertices = Mem_Alloc( sizeof(VECTOR3D) * surfArraySize );
	surfVerticesNorm = Mem_Alloc( sizeof(LPVECTOR3D) * surfArraySize );
	surfVertexCount = Mem_Alloc( sizeof(ULONG) * lightWaveObject->aoSize.lwSurfaceCount );
	surfVertexRef = Mem_Alloc( sizeof(ULONG) * surfArraySize );
	surfFaceData = Mem_Alloc( sizeof(ULONG) * (lightWaveObject->aoSize.lwSurfaceCount*fDSize) );
	surfFaceDataCount = Mem_Alloc( sizeof(ULONG) * lightWaveObject->aoSize.lwSurfaceCount );
	faceNorm = Mem_Alloc( sizeof(VECTOR3D) * lightWaveObject->aoSize.lwPolyCount );
	vertexNorm = Mem_Alloc( sizeof(VECTOR3D) * size );
	
	memset( surfVertexCount, 0, sizeof(ULONG) * lightWaveObject->aoSize.lwSurfaceCount );
	memset( surfVertexRef, -1, sizeof(ULONG) * surfArraySize );
	memset( surfFaceDataCount, 0, sizeof(ULONG) * lightWaveObject->aoSize.lwSurfaceCount );
	memset( vertexNorm, 0, sizeof(VECTOR3D) * size );
	

	mesh->lightWaveSurf = Mem_Alloc( sizeof( Mesh_LightWave_Surface ) * lightWaveObject->aoSize.lwSurfaceCount );
	memset(mesh->lightWaveSurf, 0, sizeof( Mesh_LightWave_Surface ) * lightWaveObject->aoSize.lwSurfaceCount );


	//STORE FACE NORMALS FOR GOURAUD SHADING - ASSUMES ALL POLYS ARE PLANAR
	for( face = 0; face < lightWaveObject->aoSize.lwPolyCount; face++ )
	{	
		for( vertex = 0; vertex < 3; vertex++ )
		{	
			vertexIndex = lightWaveObject->aoPoly[face].plyData[vertex] * 3;
			
			pos[vertex].x = lightWaveObject->aoVerts[ vertexIndex ];
			pos[vertex].y = lightWaveObject->aoVerts[ vertexIndex + 1 ];
			pos[vertex].z = lightWaveObject->aoVerts[ vertexIndex + 2 ];

		}
			
		Maths_PlaneNormal( &faceNorm[face], &pos[0], &pos[1], &pos[2] );

	}


//	//GET TEXTURE AND TEXTURE COORDINATES FOR VERTICES IF UVIEW FILE EXISTS
//	if( lightWaveObject->aoFileUV )
//	{	vertexUVs = Mem_Alloc( sizeof(VECTOR2D) * size );
//		surfTextCoords = Mem_Alloc( sizeof(VECTOR2D) * (lightWaveObject->aoSize.lwSurfaceCount*size) );
//
//		Mesh_UViewMesh( lightWaveObject, vertexUVs );
//	}
//	else
//		surfTextCoords = Mem_Alloc( sizeof(VECTOR2D) * size );


	//READ SURFACE INFORMATION
	Mesh_GetSurfInfo( basePath, lightWaveObject, mesh->lightWaveSurf, noTextures);


	//READ VERTEX INFORMATION
	for( face = 0; face < lightWaveObject->aoSize.lwPolyCount; face++ )
	{
		surfArraySize = lightWaveObject->aoPoly[face].plySurface * size;
		surfFDArraySize = lightWaveObject->aoPoly[face].plySurface * fDSize;

		if( lightWaveObject->aoPoly[face].plyCount == 3 )
		{
			for( vertex = 0; vertex < 3; vertex++ )
			{	
				vertexIndex = lightWaveObject->aoPoly[face].plyData[vertex] * 3;

				if( surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[vertex] ] == -1 )
				{	
					//STORE NEW VERTEX IN SURFACE LIST
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].x
						= lightWaveObject->aoVerts[ vertexIndex ];
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].y
						= lightWaveObject->aoVerts[ vertexIndex + 1 ];
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].z
						= lightWaveObject->aoVerts[ vertexIndex + 2 ];

					if( lightWaveObject->aoFileUV )
						surfTextCoords[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ] = vertexUVs[ lightWaveObject->aoPoly[face].plyData[vertex] ];
					
//					if(	first )
//					{	mesh->boundingBox.min = surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ];
//						mesh->boundingBox.max = surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ];
//						first = FALSE;
//					}
//					else
//						Mesh_UpdateBoundingBox( &mesh->boundingBox, &surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ] );
					
					//ADD VERTEX FACE NORMAL TO CURRENT VERTEX NORMAL
					Maths_Vector3DAdd( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ],
						&vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ],
						&faceNorm[ face ] );
					Maths_Vector3DNormalise( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ] );
					surfVerticesNorm[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ] 
						= &vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ];

					//STORE NEW VERTEX IN FACE DATA
					surfFaceData[ surfFDArraySize + surfFaceDataCount[lightWaveObject->aoPoly[face].plySurface]++ ] 
						= surfVertexCount[lightWaveObject->aoPoly[face].plySurface];

					//STORE NEW VERTEX REFERENCE IN VERTEX LIST
					surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[vertex] ] 
						= surfVertexCount[lightWaveObject->aoPoly[face].plySurface]++;

				}
				else
				{
					//ADD VERTEX FACE NORMAL TO CURRENT VERTEX NORMAL
					Maths_Vector3DAdd( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ],
						&vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ],
						&faceNorm[ face ] );
					Maths_Vector3DNormalise( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[vertex] ] );
					
					//GET VERTEX REFERENCE AND COPY TO FACE DATA
					surfFaceData[ surfFDArraySize + surfFaceDataCount[lightWaveObject->aoPoly[face].plySurface]++ ] 
						= surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[vertex] ];

				}

			}

		}
//		else if( lightWaveObject->aoPoly[face].plyCount == 4 )
		else
		{
			Error_Warn( ( (lightWaveObject->aoPoly[face].plyCount != 4) && (lightWaveObject->aoPoly[face].plyCount != 3) ),
				"Mesh contains polys which are not triples or quads." );

			surfArraySize = lightWaveObject->aoPoly[face].plySurface * size;

			for( vertex = 0; vertex < 6; vertex++ )
			{
				if( surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ] == -1 )
				{	
					vertexIndex = lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] * 3;

					//STORE NEW VERTEX IN SURFACE LIST
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].x
						= lightWaveObject->aoVerts[ vertexIndex ];
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].y
						= lightWaveObject->aoVerts[ vertexIndex + 1 ];
					surfVertices[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ].z
						= lightWaveObject->aoVerts[ vertexIndex + 2 ];

					if( lightWaveObject->aoFileUV )
						surfTextCoords[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ] = vertexUVs[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ];

//					if(	first )
//					{	mesh->boundingBox.min = surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ];
//						mesh->boundingBox.max = surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ];
//						first = FALSE;
//					}
//					else
//						Mesh_UpdateBoundingBox( &mesh->boundingBox, &surfVertices[ (surfArraySize) + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ] );
				
					//ADD VERTEX FACE NORMAL TO CURRENT VERTEX NORMAL
					Maths_Vector3DAdd( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ],
						&vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ],
						&faceNorm[ face ] );
					Maths_Vector3DNormalise( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ] );
					surfVerticesNorm[ surfArraySize + surfVertexCount[lightWaveObject->aoPoly[face].plySurface] ]
						= &vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ];

					//STORE NEW VERTEX IN FACE DATA
					surfFaceData[ surfFDArraySize + surfFaceDataCount[lightWaveObject->aoPoly[face].plySurface]++ ] 
						= surfVertexCount[lightWaveObject->aoPoly[face].plySurface];

					//STORE NEW VERTEX REFERENCE IN VERTEX LIST
					surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ] 
						= surfVertexCount[lightWaveObject->aoPoly[face].plySurface]++;

				}
				else
				{
					//ADD VERTEX FACE NORMAL TO CURRENT VERTEX NORMAL
					Maths_Vector3DAdd( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ],
						&vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ],
						&faceNorm[ face ] );
					Maths_Vector3DNormalise( &vertexNorm[ lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ] );
					
					//GET VERTEX REFERENCE AND COPY TO FACE DATA
					surfFaceData[ surfFDArraySize + surfFaceDataCount[lightWaveObject->aoPoly[face].plySurface]++ ] 
						= surfVertexRef[ surfArraySize + lightWaveObject->aoPoly[face].plyData[ faceDataQuad[vertex] ] ];

				}

			}
			
		} 
//		else Error_Fatal( TRUE, "LightWave object contains corrupt data. Use only triples or quads." );

	}


	//ADD A GROUP FOR EACH SURFACE IN OBJECT
	for( loop = 0; loop < lightWaveObject->aoSize.lwSurfaceCount; loop++ )
	{	
		surfArraySize = loop * size;
		surfFDArraySize = loop * fDSize;

		group = Mesh_AddGroup( mesh, surfFaceDataCount[loop], surfFaceDataCount[loop]/3, 3, &surfFaceData[surfFDArraySize] );

		//SET NORMALS
		if( !lightWaveObject->aoFileUV )
		{	Mesh_GetTextureUVsWrap( surfVertexCount[loop], &surfVertices[surfArraySize], surfTextCoords,
				lightWaveObject->aoSurface[loop].srfTexSize.tdX, lightWaveObject->aoSurface[loop].srfTexSize.tdY, lightWaveObject->aoSurface[loop].srfTexSize.tdZ,
				lightWaveObject->aoSurface[loop].srfTexCentre.tdX, lightWaveObject->aoSurface[loop].srfTexCentre.tdY, lightWaveObject->aoSurface[loop].srfTexCentre.tdZ,
				lightWaveObject->aoSurface[loop].srfTexFlags );
			
			Mesh_SetVertices_VNT( mesh, group, 0, surfVertexCount[loop], &surfVertices[surfArraySize], &surfVerticesNorm[surfArraySize], surfTextCoords );
		}
		else
			Mesh_SetVertices_VNT( mesh, group, 0, surfVertexCount[loop], &surfVertices[surfArraySize], &surfVerticesNorm[surfArraySize], &surfTextCoords[surfArraySize] );

		//ONLY ALTER RENDERING FLAGS FOR GROUP IF NEEDED
		newFlags = MESH_RENDERFLAGS_LWONORM;

		if( mesh->lightWaveSurf[loop].flags & SFM_ADDITIVE )
		{	newFlags |= MESH_FLAG_RENDER_ALPHASA1;
			Mesh_AlterGroupRenderFlags( mesh, group, newFlags );
		}
		else
			newFlags |= MESH_FLAG_RENDER_ALPHATRANS;

		if (mesh->lightWaveSurf[loop].flags & SFM_DOUBLESIDED) {
			newFlags |= MESH_FLAG_RENDER_DOUBLESIDED;
			Mesh_AlterGroupRenderFlags( mesh, group, newFlags );
		}

//		if( !(mesh->lightWaveSurf[loop].texFlags & TFM_PIXEL_BLENDING) )
//		{	newFlags |= MESH_FLAG_RENDER_FILTERNEAREST;
			Mesh_AlterGroupRenderFlags( mesh, group, newFlags );
//		}

		//SET TEXTURE
		if( (lightWaveObject->aoSurface[loop].srfTexFlags & TFM_SEQUENCE) )
		{	if( mesh->lightWaveSurf[loop].textureSeq )
				Mesh_SetGroupTexture( mesh, group, mesh->lightWaveSurf[loop].textureSeq[0] );
		}
		else
			if( mesh->lightWaveSurf[loop].texture )
				Mesh_SetGroupTexture( mesh, group, mesh->lightWaveSurf[loop].texture );

		//SET COLOUR
		Mesh_SetGroupDiffuse( mesh, group,
			mesh->lightWaveSurf[loop].colour.x * mesh->lightWaveSurf[loop].diffuse,
			mesh->lightWaveSurf[loop].colour.y * mesh->lightWaveSurf[loop].diffuse,
			mesh->lightWaveSurf[loop].colour.z * mesh->lightWaveSurf[loop].diffuse );
		Mesh_SetGroupEmissive( mesh, group,
			mesh->lightWaveSurf[loop].colour.x * mesh->lightWaveSurf[loop].emissive,
			mesh->lightWaveSurf[loop].colour.y * mesh->lightWaveSurf[loop].emissive,
			mesh->lightWaveSurf[loop].colour.z * mesh->lightWaveSurf[loop].emissive );
		if( mesh->lightWaveSurf[loop].flags & SFM_COLORHIGHLIGHTS )
			Mesh_SetGroupSpecular( mesh, group,
				mesh->lightWaveSurf[loop].colour.x * mesh->lightWaveSurf[loop].specular,
				mesh->lightWaveSurf[loop].colour.y * mesh->lightWaveSurf[loop].specular,
				mesh->lightWaveSurf[loop].colour.z * mesh->lightWaveSurf[loop].specular );
		else
			Mesh_SetGroupSpecular( mesh, group,
				mesh->lightWaveSurf[loop].specular,
				mesh->lightWaveSurf[loop].specular,
				mesh->lightWaveSurf[loop].specular );
		Mesh_SetGroupPower( mesh, group, mesh->lightWaveSurf[loop].power * 10.0f );
		Mesh_SetGroupAlpha( mesh, group, 1.0f - mesh->lightWaveSurf[loop].transparency );

		//STORE SURFACE INFORMATION FOR GROUP
		mesh->groupList[group].lightWaveSurfaceInfo = &mesh->lightWaveSurf[loop];

	}

	//FREE ALLOCATED MEMORY
	Mem_Free(surfVertices);
	Mem_Free(surfVerticesNorm);
	Mem_Free(surfTextCoords);
	Mem_Free(surfVertexCount);
	Mem_Free(surfVertexRef);
	Mem_Free(surfFaceData);
	Mem_Free(surfFaceDataCount);
	Mem_Free(faceNorm);
	Mem_Free(vertexNorm);
	if (vertexUVs) Mem_Free(vertexUVs);

	return TRUE;

}


static VOID Mesh_GetSurfInfo( LPUCHAR basePath, APPOBJ *lightWaveObject, Mesh_LightWave_Surface lightWaveSurf[] , BOOL noTextures)
{
	ULONG loopSurf;
	UCHAR drive[_MAX_DRIVE];
	UCHAR dir[_MAX_DIR];
	UCHAR fname[_MAX_FNAME];
	UCHAR ext[_MAX_EXT];
	UCHAR path[_MAX_PATH];
	//ULONG frame;
	ULONG tempNum;


	for( loopSurf = 0; loopSurf < lightWaveObject->aoSize.lwSurfaceCount; loopSurf++ )
	{	
		if( lightWaveObject->aoSurface[loopSurf].srfPath && !noTextures )
		{				
			_splitpath( lightWaveObject->aoSurface[loopSurf].srfPath, drive, dir, fname, ext );

			if( lightWaveObject->aoSurface[loopSurf].srfTexFlags & TFM_SEQUENCE )
			{	
				UCHAR baseName[_MAX_FNAME], textName[_MAX_FNAME];
				ULONG textNum, numOfDigits, numInTexSeq = 0;
			

				//FIND NUM OF TEXTURES IN SEQUENCE
				if( Mesh_GetTextureSeqInfo(fname, baseName, &textNum, &numOfDigits) )
				{
					tempNum = textNum;
						
					/*do
					{	Mesh_GetNextInSequence( baseName, textName, &textNum, numOfDigits );
						sprintf( path, "%s%s%s", basePath, textName, ext );

						numInTexSeq++;
					} while( File_Exists(path) );
					
					if( --numInTexSeq )
					{
						//LOAD TEXTURE SEQUENCE
						lightWaveSurf[loopSurf].textureSeq = Mem_Alloc( sizeof(lpMesh_Texture) * (numInTexSeq) );
					
						for( frame = 0; frame < numInTexSeq; frame++ )
						{	Mesh_GetNextInSequence( baseName, textName, &tempNum, numOfDigits );
							sprintf( path, "%s%s", textName, ext );
							lightWaveSurf[loopSurf].textureSeq[frame] = Mesh_LoadTexture(basePath, path, NULL, NULL );
						}

					} else {
						lightWaveSurf[loopSurf].textureSeq = NULL;
						Error_Fatal(TRUE, Error_Format("No textures found in sequence (%s)", path));
					}*/

					lightWaveSurf[loopSurf].textureSeq = Mem_Alloc(sizeof(lpMesh_Texture) * MESH_MAXTEXTURESEQENCE);
					for (numInTexSeq=0 ; numInTexSeq<MESH_MAXTEXTURESEQENCE ; numInTexSeq++) {

						Mesh_GetNextInSequence(baseName, textName, &textNum, numOfDigits);
						sprintf(path, "%s%s", textName, ext);
						if (NULL == (lightWaveSurf[loopSurf].textureSeq[numInTexSeq] = Mesh_LoadTexture(basePath, path, NULL, NULL))) {
							break;
						}
					}

					// Mem_Realloc() will set 'textureSeq' to NULL if 'numInTexSeq' is zero...
					lightWaveSurf[loopSurf].numInTexSeq = numInTexSeq;
					lightWaveSurf[loopSurf].textureSeq = Mem_ReAlloc(lightWaveSurf[loopSurf].textureSeq, sizeof(lpMesh_Texture) * numInTexSeq);
				}
				else
					Error_Fatal( TRUE, Error_Format("Error loading texture sequence \"%s\".", fname) );
			}
			else
			{
				//LOAD SINGLE TEXTURE
				sprintf( path, "%s%s",  fname, ext );

				lightWaveSurf[loopSurf].texture = Mesh_LoadTexture( basePath, path, NULL, NULL );
			}

			if( lightWaveObject->aoSurface[loopSurf].srfFlags & SFM_SHARPTERMINATOR )
			{
				//IF SHARP TERMINATOR FLAG IS SET THEN MIX TEXTURE COLOUR WITH DIFFUSE
				lightWaveSurf[loopSurf].colour.x = lightWaveObject->aoSurface[loopSurf].srfCol.colRed / 256.0f;
				lightWaveSurf[loopSurf].colour.y = lightWaveObject->aoSurface[loopSurf].srfCol.colGreen / 256.0f;
				lightWaveSurf[loopSurf].colour.z = lightWaveObject->aoSurface[loopSurf].srfCol.colBlue / 256.0f;
				//lightWaveSurf[loopSurf].color.w = lightWaveObject->aoSurface[loopSurf].srfCol.colAlpha / 256.0f;
			}
			else
			{
				lightWaveSurf[loopSurf].colour.x = 1.0f;
				lightWaveSurf[loopSurf].colour.y = 1.0f;
				lightWaveSurf[loopSurf].colour.z = 1.0f;
				//lightWaveSurf[loopSurf].colour.w = 1.0f;
			}
		}
		else
		{
			lightWaveSurf[loopSurf].colour.x = lightWaveObject->aoSurface[loopSurf].srfCol.colRed / 256.0f;
			lightWaveSurf[loopSurf].colour.y = lightWaveObject->aoSurface[loopSurf].srfCol.colGreen / 256.0f;
			lightWaveSurf[loopSurf].colour.z = lightWaveObject->aoSurface[loopSurf].srfCol.colBlue / 256.0f;
			//lightWaveSurf[loopSurf].color.w = lightWaveObject->aoSurface[loopSurf].srfCol.colAlpha / 256.0f;
		}

		lightWaveSurf[loopSurf].emissive = lightWaveObject->aoSurface[loopSurf].srfLuminous;
		lightWaveSurf[loopSurf].transparency = lightWaveObject->aoSurface[loopSurf].srfTransparent;
		lightWaveSurf[loopSurf].diffuse = lightWaveObject->aoSurface[loopSurf].srfDiffuse;
		lightWaveSurf[loopSurf].specular = lightWaveObject->aoSurface[loopSurf].srfSpecular;
		lightWaveSurf[loopSurf].power = lightWaveObject->aoSurface[loopSurf].srfSpecPower;
		lightWaveSurf[loopSurf].flags = lightWaveObject->aoSurface[loopSurf].srfFlags;
		lightWaveSurf[loopSurf].texFlags = lightWaveObject->aoSurface[loopSurf].srfTexFlags;
	}
}


VOID Mesh_UpdateBoundingBox( LPBOX3D box, LPVECTOR3D pos )
{
	if( pos->x < box->min.x )
		box->min.x = pos->x;
	else if( pos->x > box->max.x )
		box->max.x = pos->x;

	if( pos->y < box->min.y )
		box->min.y = pos->y;
	else if( pos->y > box->max.y )
		box->max.y = pos->y;

	if( pos->z < box->min.z )
		box->min.z = pos->z;
	else if( pos->z > box->max.z )
		box->max.z = pos->z;
}


BOOL Mesh_GetTextureSeqInfo( LPUCHAR tname, LPUCHAR tfname, LPULONG tstart, LPULONG tnumlen )
{
	ULONG len, n, indx = 1,val = 0;
	UCHAR c;


	len = strlen(tname);
	c = tname[len-1];
	if( (c < '0') || (c > '9') )
		return FALSE;

	for( n = len-1; n > 0; n-- )
	{
		c = tname[n];
		if( (c < '0') || (c > '9') )
			break;
		else
			val += (c-'0') * indx;
		
		indx *= 10;
	}

	if( n == 0 )
		return FALSE;

	strcpy( tfname,tname );
	tfname[n+1] = 0;
	*tnumlen = len - n - 1;
	*tstart = val;
	return TRUE;
}


VOID Mesh_GetNextInSequence( LPUCHAR baseName, LPUCHAR nextTextName, LPULONG texNum, ULONG tnumlen)
{	UCHAR numBuff[16];
	ULONG k;


	strcpy( nextTextName, baseName );

	sprintf( numBuff, "%d", (*texNum) );
	k = tnumlen - strlen(numBuff);
	while( k>=1 )
	{	strcat( nextTextName,"0" );
		k--;
	}

	(*texNum)++;

	strcat( nextTextName, numBuff );

}

#define MESH_UVREALLOCSIZE		10

static VOID Mesh_HandleUViewUV(APPOBJ *lwo, VECTOR2D textCoords[], LPBOOL uvSet, LPULONG addedCount, ULONG currPoly, ULONG currPolyVertex, REAL u, REAL v) {

	// Copy of the code from within the original Mesh_UViewMesh()

	ULONG vertexIndex, newIndex;

	if (0 == uvSet[lwo->aoPoly[currPoly].plyData[currPolyVertex]]) {

		textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].x = u;
		textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].y = v;
		uvSet[lwo->aoPoly[currPoly].plyData[currPolyVertex]] = 1;

	} else if ((textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].x != u) ||
		(textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].y != v)) {

		//THE SHARED VERTEX HAS MORE THEN ONE TEXTURE COORDINATE
		//COPY THE VERTEX AND ALTER THE FACE DATA FOR THE GROUP
		//ADD THE NEW UV INFORMATION TO THE NEW VERTEX
		
		//THIS ALTERS THE STRUCTURE OF 'lwo'
		//REFERENCES BEFORE THIS FUNCTION WILL BE DIFFERENT TO THOSE AFTER

		if (0 == *addedCount) lwo->aoVerts = Mem_ReAlloc(lwo->aoVerts, (sizeof(REAL) * 3) * (lwo->aoSize.lwVertCount + MESH_UVREALLOCSIZE + 1));

		vertexIndex = lwo->aoPoly[currPoly].plyData[currPolyVertex] * 3;
		newIndex = lwo->aoSize.lwVertCount * 3;

		//ADD A COPY OF VERTEX TO LIST
		lwo->aoVerts[newIndex + 0] = lwo->aoVerts[vertexIndex + 0];
		lwo->aoVerts[newIndex + 1] = lwo->aoVerts[vertexIndex + 1];
		lwo->aoVerts[newIndex + 2] = lwo->aoVerts[vertexIndex + 2];

		//POINT THE FACE DATA TO POINT TO THE NEW VERTEX
		lwo->aoPoly[currPoly].plyData[currPolyVertex] = (WORD)lwo->aoSize.lwVertCount;

		//STORE THE NEW UV INFORMATION
		textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].x = u;
		textCoords[lwo->aoPoly[currPoly].plyData[currPolyVertex]].y = v;

		lwo->aoSize.lwVertCount++;

		if (++(*addedCount) >= MESH_UVREALLOCSIZE) *addedCount = 0;
	}
}

VOID Mesh_UViewMeshV4(APPOBJ *lwo, VECTOR2D textCoords[]) {

	UCHAR line[1024];
	LPUCHAR argv[10];
	ULONG argc;
	ULONG surfaceCount, currSurface, polyCount, currPoly;
	ULONG polyVertexCount, currPolyVertex, currChannel;
	BOOL surfaceFileMode = FALSE;
	LPBOOL uvSet;
	ULONG addedCount = 0;

	uvSet = Mem_Alloc(sizeof(LPBOOL) * lwo->aoSize.lwVertCount * 2);
	memset(uvSet, 0, sizeof(LPBOOL) * lwo->aoSize.lwVertCount * 2);

	File_GetLine(line, sizeof(line), lwo->aoFileUV);
	while (File_GetLine(line, sizeof(line), lwo->aoFileUV)) {

		if (surfaceFileMode) {
			if (0 == currChannel) lwo->aoSurface[currSurface].srfPath = Util_StrCpy(line);
			surfaceFileMode = FALSE;
		} else {
			if (argc = Util_WSTokenise(line, argv)) {

				if (0 == strcmp("VERSION", argv[0])) {
					Error_Fatal(4 != atol(argv[1]), "Incorrect UView file version");
				} else if (0 == strcmp("SURFACE_COUNT", argv[0])) {
					surfaceCount = atol(argv[1]);				
					Error_Fatal(lwo->aoSize.lwSurfaceCount!=surfaceCount, "Invalid/Incorrect UView file (Surface count mismatch)");
				} else if (0 == strcmp("SURFACE", argv[0])) {
					currSurface = atol(argv[1]);
				} else if (0 == strcmp("SURFACE_IMAGE_FILE", argv[0])) {
					surfaceFileMode = TRUE;
				} else if (0 == strcmp("POLY_COUNT", argv[0])) {
					polyCount = atol(argv[1]);
					Error_Fatal(lwo->aoSize.lwPolyCount!=polyCount, "Invalid/Incorrect UView file (Poly count mismatch)");
				} else if (0 == strcmp("POLY", argv[0])) {
					currPoly = atol(argv[1]);
				} else if (0 == strcmp("POLY_VERT_COUNT", argv[0])) {
					polyVertexCount = atol(argv[1]);
					Error_Fatal(lwo->aoPoly[currPoly].plyCount!=polyVertexCount, "Invalid/Incorrect UView file (Poly vertex count mismatch)");
				} else if (0 == strcmp("VERT", argv[0])) {
					currPolyVertex = atol(argv[1]);
				} else if (0 == strcmp("VERT_CUV", argv[0])) {
					Mesh_HandleUViewUV(lwo, textCoords, uvSet, &addedCount, currPoly, currPolyVertex, (REAL) atof(argv[2]), (REAL) -atof(argv[3]));
				} else if (0 == strcmp("CHANNEL", argv[0])) {
					currChannel = atoi(argv[1]);
				}
			}
		}
	}

	Mem_Free(uvSet);
}

VOID Mesh_UViewMesh( APPOBJ *lightWaveObject, VECTOR2D textCoords[] )
{	UCHAR line[1024];
	UCHAR lineSplit[1024];
	ULONG groupID;
	LPUCHAR argv[5];
	SLONG argc, lineNum = 0;
	SLONG polyRead = -2;
	SLONG surfRead = -1;
	SLONG vertexRead = -1;
	lpFile fileUV = lightWaveObject->aoFileUV;
	LPULONG uvSet;
	ULONG addedCount = 0;
	BOOL notSame;
	REAL uvX, uvY;
	ULONG vertexIndex, newIndex;

	if (File_GetLine(line, sizeof(line), fileUV)) {
		if (File_GetLine(line, sizeof(line), fileUV)) {
			File_Seek(fileUV, 0, File_SeekSet);
			if (0 == strcmp("VERSION 4", line)) {
				Mesh_UViewMeshV4(lightWaveObject, textCoords);
				return;
			}
		}
	}

	uvSet = Mem_Alloc( sizeof(ULONG) * lightWaveObject->aoSize.lwVertCount * 2 );
	memset( uvSet, 0, sizeof(ULONG)  * lightWaveObject->aoSize.lwVertCount * 2 );

	while( File_GetLine(line, sizeof(line), fileUV) )
	{
		strcpy( lineSplit, line );

		if( argc = Util_WSTokenise(lineSplit, argv) )
		{
			//MAYBE CHECK VERSION NUMBER ON FIRST LINE - SHOULD BE 2

			//CHECK SURFACE COUNT IS SAME AS OBJECT
			Error_Fatal( (1 == lineNum) && (lightWaveObject->aoSize.lwSurfaceCount != (ULONG)atoi( argv[0] )), "UView file corrupt." );

			if( 2 == lineNum )
				surfRead = 0;

			//READ SURFACE INFORMATION
			if( -1 != surfRead )
			{	
				if( surfRead >= (SLONG)(lightWaveObject->aoSize.lwSurfaceCount*2) )
				{	polyRead = -1;
					surfRead = -1;
				}
				else if( surfRead >= (SLONG)lightWaveObject->aoSize.lwSurfaceCount )
				{	//OVERWRITE EXISTING IMAGE FILE NAME ON SURFACE
					lightWaveObject->aoSurface[ surfRead - lightWaveObject->aoSize.lwSurfaceCount ].srfPath = Util_StrCpy( argv[0] );

					surfRead++;
				}
				else
					surfRead++;				
				
			}

			//RUN THROUGH POLYGONS
			if( -2 != polyRead )
			{				
				if( -1 == polyRead )
				{	//CHECK POLY COUNT IS THE SAME AS OBJECT
					Error_Fatal( (lightWaveObject->aoSize.lwPolyCount != (ULONG)atoi( argv[0] )), "UView file corrupt." );
					polyRead = 0;
				}
				else if( polyRead < (SLONG)lightWaveObject->aoSize.lwPolyCount )
				{
					if( (-1 != vertexRead) && (vertexRead < (SLONG)lightWaveObject->aoPoly[groupID].plyCount) )
					{	
						notSame = FALSE;

						//READ UV INFORMATION FOR EACH VERTEX
						uvX = (REAL) atof( argv[0] );
						uvY = -(REAL) atof( argv[1] );

						if( (textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].x != uvX) ||
							(textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].y != uvY) )
							notSame = TRUE;

						if( 0 == uvSet[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ] )
						{	textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].x = uvX;
							textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].y = uvY;

							uvSet[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ] = 1;
						}
						else if( notSame )
						{	//THE SHARED VERTEX HAS MORE THEN ONE TEXTURE COORDINATE
							//COPY THE VERTEX AND ALTER THE FACE DATA FOR THE GROUP
							//ADD THE NEW UV INFORMATION TO THE NEW VERTEX
							
							//THIS ALTERS THE STRUCTURE OF 'lightWaveObject'
							//REFERENCES BEFORE THIS FUNCTION WILL BE DIFFERENT TO THOSE AFTER

							if( 0 == addedCount )
								lightWaveObject->aoVerts = Mem_ReAlloc( lightWaveObject->aoVerts, (sizeof(REAL) * (lightWaveObject->aoSize.lwVertCount + MESH_UVREALLOCSIZE + 1) * 3));

							vertexIndex = lightWaveObject->aoPoly[groupID].plyData[vertexRead] * 3;
							newIndex = lightWaveObject->aoSize.lwVertCount * 3;

							//ADD A COPY OF VERTEX TO LIST
							lightWaveObject->aoVerts[ newIndex ] = lightWaveObject->aoVerts[ vertexIndex  ];
							lightWaveObject->aoVerts[ newIndex + 1 ] = lightWaveObject->aoVerts[ vertexIndex + 1 ];
							lightWaveObject->aoVerts[ newIndex + 2 ] = lightWaveObject->aoVerts[ vertexIndex + 2 ];

							//POINT THE FACE DATA TO POINT TO THE NEW VERTEX
							lightWaveObject->aoPoly[groupID].plyData[vertexRead] = (WORD)lightWaveObject->aoSize.lwVertCount;

							//STORE THE NEW UV INFORMATION
							textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].x = uvX;
							textCoords[ lightWaveObject->aoPoly[groupID].plyData[vertexRead] ].y = uvY;

							lightWaveObject->aoSize.lwVertCount++;

							if( ++addedCount >= MESH_UVREALLOCSIZE )
								addedCount = 0;
						}

						vertexRead++;
					}
					else if( polyRead < (SLONG)lightWaveObject->aoSize.lwPolyCount - 1 )
					{	//CHECK POLY VERTEX COUNT IS SAME AS OBJECT
						groupID = atoi( argv[0] );
						Error_Fatal( (lightWaveObject->aoPoly[groupID].plyCount != (ULONG)atoi( argv[1] )), "UView file corrupt." );
					
						if( -1 != vertexRead )
							polyRead++;

						vertexRead = 0;
					}

				}
				else 
				{	polyRead = -2;

					//RETURN HERE BECAUSE REST OF FILE IS UNUSED
					return;
				}

			}

			lineNum++;

		}

	}

	Mem_Free( uvSet );

}


VOID Mesh_GetTextureUVsWrap( ULONG vertexCount, VECTOR3D vertices[], VECTOR2D coords[],
							REAL sx, REAL sy, REAL sz, REAL px, REAL py, REAL pz, ULONG flags )
{
	REAL x, y, z;
	ULONG vertex;

	
	for( vertex = 0; vertex < vertexCount; vertex++ )
	{
		x = vertices[vertex].x - px;
		y = vertices[vertex].y - py;
		z = vertices[vertex].z - pz;

		coords[vertex].x = ( flags & TFM_AXIS_X ) ? (z/sz) + 0.5f : (x/sx) + 0.5f;
		coords[vertex].y = ( flags & TFM_AXIS_Y ) ? (z/sz) + 0.5f : (y/sy) + 0.5f;

	}

}
							
BOOL Mesh_SetTextureTime( lpMesh mesh, REAL frame )
{
	if (mesh->textureRenderCallback == NULL) return Mesh_SetTextureTime2(mesh, frame);
	return FALSE;
}

BOOL Mesh_SetTextureTime2( lpMesh mesh, REAL frame )
{	ULONG texNum;
	ULONG groupNum;
	SLONG groupTexNum;
	lpMesh_Group group;

	texNum = (ULONG)( frame - (REAL)fmod(frame,1) );

	if( mesh->flags & MESH_FLAG_LWO )
	{	
		for( groupNum = 0; groupNum < mesh->groupCount; groupNum++ )
		{
			group = &mesh->groupList[groupNum];
		
			if( (group->lightWaveSurfaceInfo->texFlags & TFM_SEQUENCE) && (group->lightWaveSurfaceInfo->numInTexSeq) )
			{	groupTexNum = (group->lightWaveSurfaceInfo->texSeqOffset + (SLONG)texNum) % (SLONG)group->lightWaveSurfaceInfo->numInTexSeq;
	
				if( groupTexNum < 0 )
					groupTexNum = 0;

				Mesh_SetGroupTexture( mesh, groupNum, group->lightWaveSurfaceInfo->textureSeq[groupTexNum] );
			}

		}

		return TRUE;

	}
	else
		Error_Warn( TRUE, "Cannot set texture time on non LightWave mesh." );

	return FALSE;

}


VOID Mesh_Remove(lpMesh mesh, LPDIRECT3DRMFRAME3 frame) {
	
	ULONG loop;
	lpMesh_Group group;
	
	Mesh_Debug_CheckIMDevice_Void();
	
	frame->lpVtbl->DeleteVisual(frame, (struct IUnknown *) mesh->uv);
	
	if (mesh->clonedFrom) {

		lpMesh clonedFrom = mesh->clonedFrom;

		RELEASE(mesh->uv);
		for (loop=0 ; loop<mesh->groupCount ; loop++) {
			group = &mesh->groupList[loop];
			//if (group->imMat) RELEASE(group->imMat);
		}
		Mem_Free(mesh->groupList);
//		Mem_Free(mesh);
		Mesh_ReturnToList(mesh);

		mesh = clonedFrom;

	}

	mesh->numOfRefs--;

	if (mesh->numOfRefs == 0)
	{
		RELEASE(mesh->uv);
		
		for( loop = 0; loop < mesh->groupCount; loop++ )
		{
			group = &mesh->groupList[loop];
			
//			if( group->imMat )
//				RELEASE(group->imMat);
//			if( group->imText )
//				RELEASE(group->imText);
			Mesh_RemoveGroupTexture(mesh, loop);
			Mem_Free(group->faceData);
			Mem_Free(group->vertices);
//			Mem_Free(group);
			
		}
		
		if (mesh->lightWaveSurf) Mem_Free(mesh->lightWaveSurf);
		Mem_Free(mesh->groupList);
//		Mem_Free(mesh);
		Mesh_ReturnToList(mesh);
		
	}
}


//#pragma message ( "Mesh_GetGroup() required for Detail_Setup()" )

VOID Mesh_GetGroup(lpMesh mesh, ULONG groupID, LPULONG vertexCount, LPULONG faceCount, LPULONG vPerFace, LPULONG faceDataSize, LPULONG faceData) {

	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		ULONG loop;

		if (vertexCount) *vertexCount = group->vertexCount;
		if (vPerFace) *vPerFace = 3;
		if (faceDataSize) *faceDataSize = group->faceDataSize;
		if (faceData) {
			for (loop=0 ; loop<group->faceDataSize ; loop++) {
				faceData[loop] = group->faceData[loop];
			}
		}
	}
}

ULONG Mesh_GetGroupCount(lpMesh mesh) {

	return mesh->groupCount;
}


SLONG Mesh_AddGroup(lpMesh mesh, ULONG vertexCount, ULONG faceCount, ULONG vPerFace, LPULONG faceData) {

	ULONG size, loop;
	lpMesh_Group group;
	
	Mesh_Debug_CheckIMDevice_Int();
	Error_Fatal( (vPerFace != 3), "Only triangles supported so far." );
	Error_Fatal((NULL!=mesh->clonedFrom)||(mesh->flags&MESH_FLAG_HASBEENCLONED), "Cannot AddGroup() to a cloned mesh");
	
/*
	if( NULL == mesh->groupList )
	{
		mesh->listSize = MESH_DEFLISTSIZE;
		mesh->groupCount = 1;
		mesh->groupList = Mem_Alloc( mesh->listSize * sizeof(Mesh_Group) );
		
	}
	else
	{

		////


		if( ++mesh->groupCount == mesh->listSize )
		{	lpMesh_Group newList;
			ULONG newSize = (mesh->listSize*MESH_LISTINCREASE) / 100;
			
			
			if( newList = Mem_ReAlloc( mesh->groupList, newSize * sizeof(Mesh_Group) ) )
			{
				mesh->groupList = newList;
				mesh->listSize = newSize;
				
			}
			else
			{	Error_Fatal( TRUE, "Memory allocation error" );
			
				return -1;
			}
		}
		
	}

	group = &mesh->groupList[mesh->groupCount-1];
*/

	if (mesh->groupCount == mesh->listSize) {
		mesh->listSize = max(MESH_DEFLISTSIZE, (mesh->listSize * MESH_LISTINCREASE) / 100);
		mesh->groupList = Mem_ReAlloc(mesh->groupList, sizeof(mesh->groupList[0]) * mesh->listSize);
	}
	group = &mesh->groupList[mesh->groupCount++];
	memset(group, 0, sizeof(*group));

//	group = Mem_Alloc( sizeof(Mesh_Group) );
//	memset( group, 0, sizeof(Mesh_Group) );
	
	size = sizeof(UWORD) * faceCount * vPerFace;
	group->faceData = Mem_Alloc(size);
	group->faceDataSize = faceCount * vPerFace;
	for( loop = 0; loop < group->faceDataSize; loop++ )
		group->faceData[loop] = (UWORD) faceData[loop];
	
	size = sizeof(Mesh_Vertex) * vertexCount;
	group->vertices = Mem_Alloc(size);
	memset( group->vertices, 0, size );
	
	group->vertexCount = vertexCount;
	group->flags = 0x00000000;
	
//	mesh->groupList[mesh->groupCount-1] = group;
	
	Mesh_CreateGroupMaterial( mesh, (mesh->groupCount-1) );
	
	
	return mesh->groupCount-1;
}


VOID Mesh_AlterGroupRenderFlags( lpMesh mesh, ULONG groupID, ULONG newFlags )
{
	if (groupID < mesh->groupCount) {
		mesh->groupList[groupID].renderFlags = newFlags;
	}
}


VOID Mesh_Scale(lpMesh mesh, REAL x, REAL y, REAL z) {

	ULONG loop, sub;
	lpMesh_Group group;

	Mesh_Debug_CheckIMDevice_Void();

	for( loop = 0; loop < mesh->groupCount; loop++ )
	{
		group = &mesh->groupList[loop];
		
		for( sub = 0; sub < group->vertexCount; sub++ )
		{
			group->vertices[sub].position.x *= x;
			group->vertices[sub].position.y *= y;
			group->vertices[sub].position.z *= z;

		}
	}
}


VOID Mesh_SetVertices(lpMesh mesh, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D vertices) {

	if (groupID < mesh->groupCount) {
		ULONG loop;
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();
		group = &mesh->groupList[groupID];

		for( loop = 0; loop < count; loop++ )
		{
			group->vertices[loop+index].position = vertices[loop].position;
			group->vertices[loop+index].normal = vertices[loop].normal;
			group->vertices[loop+index].tu = vertices[loop].tu;
			group->vertices[loop+index].tv = vertices[loop].tv;
	//		group->vertices[loop+index].colour = vertices[loop].colour;
	//		group->vertices[loop+index].specular = 0;

		}
	}
}


VOID Mesh_GetVertices(lpMesh mesh, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D vertices) {

	if (groupID < mesh->groupCount) {
		ULONG loop;
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();
		group = &mesh->groupList[groupID];

		for( loop = 0; loop < count; loop++ )
		{
			vertices[loop].position = group->vertices[loop+index].position;
			vertices[loop].normal = group->vertices[loop+index].normal;
			vertices[loop].tu = group->vertices[loop+index].tu;
			vertices[loop].tv = group->vertices[loop+index].tv;

		}
	}
}


VOID Mesh_SetVertices_PointNormalAt(lpMesh mesh, ULONG groupID, ULONG index, ULONG count, VECTOR3D vertices[], LPVECTOR3D position, REAL textCoords[][2]) {

	if (groupID < mesh->groupCount) {
		ULONG loop;
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();
		group = &mesh->groupList[groupID];

		for( loop = 0; loop < count; loop++ )
		{
			group->vertices[loop+index].position.x = vertices[loop].x;
			group->vertices[loop+index].position.y = vertices[loop].y;
			group->vertices[loop+index].position.z = vertices[loop].z;
			Maths_Vector3DSubtract(&group->vertices[loop+index].normal, position, &group->vertices[loop+index].position);
			Maths_Vector3DNormalise(&group->vertices[loop+index].normal);
			group->vertices[loop+index].tu = textCoords[loop][0];
			group->vertices[loop+index].tv = textCoords[loop][1];

		}
	}
}


VOID Mesh_SetVertices_SameNormal( lpMesh mesh, ULONG groupID, ULONG index, ULONG count,
						 VECTOR3D vertices[], LPVECTOR3D normal, REAL textCoords[][2] )
{
	
	if (groupID < mesh->groupCount) {
		ULONG loop;
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();

		group = &mesh->groupList[groupID];

		for( loop = 0; loop < count; loop++ )
		{
			group->vertices[loop+index].position.x = vertices[loop].x;
			group->vertices[loop+index].position.y = vertices[loop].y;
			group->vertices[loop+index].position.z = vertices[loop].z;
			group->vertices[loop+index].normal = (*normal);
			group->vertices[loop+index].tu = textCoords[loop][0];
			group->vertices[loop+index].tv = textCoords[loop][1];

		}
	}
}


VOID Mesh_SetVertices_VNT( lpMesh mesh, ULONG groupID, ULONG index, ULONG count,
						 VECTOR3D vertices[], LPVECTOR3D normal[], VECTOR2D textCoords[] )
{
	if (groupID < mesh->groupCount) {
		ULONG loop;
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();

		group = &mesh->groupList[groupID];

		for( loop = 0; loop < count; loop++ )
		{
			group->vertices[loop+index].position.x = vertices[loop].x;
			group->vertices[loop+index].position.y = vertices[loop].y;
			group->vertices[loop+index].position.z = vertices[loop].z;
			group->vertices[loop+index].normal.x = normal[loop]->x;
			group->vertices[loop+index].normal.y = normal[loop]->y;
			group->vertices[loop+index].normal.z = normal[loop]->z;
			group->vertices[loop+index].tu = textCoords[loop].x;
			group->vertices[loop+index].tv = textCoords[loop].y;

		}
	}
}


BOOL Mesh_IsGroupHidden(lpMesh mesh, ULONG groupID) {

	if (groupID < mesh->groupCount) {
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Int();
		group = &mesh->groupList[groupID];

		return group->flags & MESH_FLAG_HIDDEN;
	}

	return TRUE;
}


VOID Mesh_HideGroup(lpMesh mesh, ULONG groupID, BOOL hide) {

	if (groupID < mesh->groupCount) {
		lpMesh_Group group;

		Mesh_Debug_CheckIMDevice_Void();
		group = &mesh->groupList[groupID];

		if (hide) group->flags |= MESH_FLAG_HIDDEN;
		else group->flags &= ~MESH_FLAG_HIDDEN;
	}
}


VOID Mesh_Hide(lpMesh mesh, BOOL hide) {

	Mesh_Debug_CheckIMDevice_Void();

	if (hide) mesh->flags |= MESH_FLAG_HIDDEN;
	else mesh->flags &= ~MESH_FLAG_HIDDEN;
}


static BOOL Mesh_RenderCallback(LPDIRECT3DRMUSERVISUAL lpD3DRMUV, LPVOID lpArg, D3DRMUSERVISUALREASON lpD3DRMUVreason, LPDIRECT3DRMDEVICE lpD3DRMDev, LPDIRECT3DRMVIEWPORT lpD3DRMview) {

	lpMesh mesh = lpArg;
	lpViewport vp;
	D3DMATRIX matWorld;


	if (D3DRMUSERVISUAL_CANSEE == lpD3DRMUVreason) {

		if (lpIMDevice()){
			if (mesh->flags & MESH_FLAG_HIDDEN) return FALSE;

/*			{
				lpContainer cont;
				if (cont = Container_SearchOwner(mesh->frameCreatedOn)) {
					if (cont->flags & CONTAINER_FLAG_HIDDEN2) return FALSE;
				}
			}*/

			if ((mesh->flags & MESH_FLAG_FACECAMERA) && !(mesh->flags & MESH_FLAG_FACECAMERADONE)) {
				LPDIRECT3DRMFRAME3 camera, scene;
				vp = (lpViewport) lpD3DRMview->lpVtbl->GetAppData(lpD3DRMview);
				if (vp->rendering) {
					mesh->frameCreatedOn->lpVtbl->GetScene(mesh->frameCreatedOn, &scene);
					vp->lpVP->lpVtbl->GetCamera(vp->lpVP, &camera);
					mesh->frameCreatedOn->lpVtbl->LookAt(mesh->frameCreatedOn, camera, scene, 0);
//					mesh->frameCreatedOn->lpVtbl->SetOrientation(mesh->frameCreatedOn, camera, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
					mesh->flags |= MESH_FLAG_FACECAMERADONE;
				}
			}

			return TRUE;
		} else return FALSE;

	} else if (D3DRMUSERVISUAL_RENDER == lpD3DRMUVreason) {

		if (lpIMDevice()){
			
			LPDIRECT3DRMVIEWPORT2 view;
			lpMesh_Group group;
			ULONG loop;
			BOOL postRender = FALSE;
			BOOL renderStateSet = FALSE;
			

			mesh->flags &= ~MESH_FLAG_FACECAMERADONE;

			//GET THE CURRENT RM WORLD MATRIX FOR POST RENDER
			lpIMDevice()->lpVtbl->GetTransform( lpIMDevice(), D3DTRANSFORMSTATE_WORLD, &matWorld );

			Mesh_SetCurrentViewport( lpD3DRMview );
			lpD3DRMview->lpVtbl->QueryInterface( lpD3DRMview, &IID_IDirect3DRMViewport2, &view );
			
			vp = (lpViewport)view->lpVtbl->GetAppData(view);
	
			if( mesh->flags & MESH_FLAG_POSTEFFECT )
			{	
				//POST RENDER MESH
				Mesh_AddToPostRenderList( mesh, &matWorld );
			} 
			else if( mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALLALPHA )
			{
				//RENDER ALL GROUPS WITHOUT FLAGS CHANGED FISRT
				for( loop = 0; loop < mesh->groupCount; loop++ )
				{
					group = &mesh->groupList[loop];

					if( Mesh_CanRenderGroup(group) )
					{	
						if( group->flags & MESH_FLAG_ALPHAENABLE )
						{	
							//POST RENDER MESH
							//DO NOT RENDER GROUP NOW
							postRender = TRUE;
							continue;
						}

						if( 0 == group->renderFlags )
						{
							//GROUP OPAQUE SO RENDER NOW
							if( !renderStateSet )
							{	
								Mesh_StoreTextureAndMat();
								Mesh_SetMeshRenderDesc( mesh, vp, &matWorld, FALSE );
								renderStateSet = TRUE;
							}

							Mesh_RenderGroup( mesh, group, &matWorld, FALSE );
						}
					}
				}

				//RENDER ALL GROUPS WITH FLAGS CHANGED FISRT
				for( loop = 0; loop < mesh->groupCount; loop++ )
				{
					group = &mesh->groupList[loop];

					if( Mesh_CanRenderGroup(group) )
					{	
						if( group->flags & MESH_FLAG_ALPHAENABLE )
						{	
							//POST RENDER MESH
							//DO NOT RENDER GROUP NOW
							postRender = TRUE;
							continue;
						}

						if( group->renderFlags )
						{
							//GROUP OPAQUE SO RENDER NOW
							if( !renderStateSet )
							{	
								Mesh_StoreTextureAndMat();
								Mesh_SetMeshRenderDesc( mesh, vp, &matWorld, FALSE );
								renderStateSet = TRUE;
							}

							Mesh_RenderGroup( mesh, group, &matWorld, FALSE );
						}
					}
				}

				if( postRender )
					Mesh_AddToPostRenderList( mesh, &matWorld );
			}
			else
			{	
				//NOTE IS SOME OF THE GROUPS IN THIS MESH USE ALPHA BLENDING THEY WILL NOT APPEAR
				//IF YOU SUSPECT THAT ONE OR MORE GROUPS WILL USE ALPHA BLENDING SET 'MESH_FLAG_RENDER_ALPHATRANS' ON THE MESH RENDER DESC.
				Mesh_StoreTextureAndMat();
				Mesh_SetMeshRenderDesc( mesh, vp, &matWorld, FALSE );
				renderStateSet = TRUE;

				Mesh_RenderMesh( mesh, &matWorld, FALSE );
			}

			if( renderStateSet )
			{	
				//RESTORE STATES
				Main_RestoreStates(FALSE);
				//Mesh_RestoreTextureStageStates();
				Mesh_RestoreTextureAndMat();
			}
			
			RELEASE( view );
		}

		return TRUE;
	}

	return FALSE;
}


static VOID Mesh_SetMeshRenderDesc( lpMesh mesh, lpViewport vp, LPD3DMATRIX matWorld, BOOL alphaBlend )
{	
	//CALL MESH SPECIFIC RENDER FUNCTION
	if( mesh->renderDesc.renderCallback )
		mesh->renderDesc.renderCallback( mesh, mesh->renderDesc.renderCallbackData, vp );

	//ADD DEFAULT STATES HERE
	Main_ChangeRenderState( D3DRENDERSTATE_SPECULARENABLE,		FALSE );
	Main_ChangeRenderState( D3DRENDERSTATE_SHADEMODE,			D3DSHADE_GOURAUD );
	Main_ChangeRenderState( D3DRENDERSTATE_DITHERENABLE,		TRUE );
	
	if( !(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) )
	{
		Mesh_ChangeTextureStageState( D3DTSS_COLORARG1,	D3DTA_TEXTURE );
		Mesh_ChangeTextureStageState( D3DTSS_COLORARG2,	D3DTA_DIFFUSE );
		Mesh_ChangeTextureStageState( D3DTSS_ALPHAARG1,	D3DTA_TEXTURE );
		Mesh_ChangeTextureStageState( D3DTSS_ALPHAARG2,	D3DTA_DIFFUSE );
	}

	Mesh_SetRenderDesc( mesh->renderDesc.renderFlags, matWorld, alphaBlend );
}


static VOID Mesh_SetRenderDesc( ULONG flags, LPD3DMATRIX matWorld, BOOL alphaBlend )
{	
	MATRIX4D temp;


	//CHECK MESH IS ALPHA BLENDED
	if( (flags & MESH_FLAG_RENDER_ALLALPHA) && alphaBlend )
		Main_ChangeRenderState( D3DRENDERSTATE_FOGENABLE,	FALSE );	// Don't fog alpha efects...
	/*else {
		Main_ChangeRenderState( D3DRENDERSTATE_FOGENABLE,	TRUE );
		Container_EnableFog(TRUE);
		Container_SetFogMode(D3DFOG_LINEAR);
		Container_SetFogParams(100, 1000, 0.5f);
	}*/

	//ALPHA STATES
	if( (flags & MESH_FLAG_RENDER_ALLALPHA) && !alphaBlend )
		Main_ChangeRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );
	else if( flags & MESH_FLAG_RENDER_ALPHA11 )
		Mesh_SetAlphaRender( D3DBLEND_ONE, D3DBLEND_ONE );
	else if( flags & MESH_FLAG_RENDER_ALPHASA1 )
		Mesh_SetAlphaRender( D3DBLEND_SRCALPHA, D3DBLEND_ONE );
	else if( flags & MESH_FLAG_RENDER_ALPHATRANS )
		Mesh_SetAlphaRender( D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA );
	else if( flags & MESH_FLAG_RENDER_ALPHASA0 )
		Mesh_SetAlphaRender( D3DBLEND_ZERO, D3DBLEND_INVSRCCOLOR);
	else
		Main_ChangeRenderState( D3DRENDERSTATE_ALPHABLENDENABLE, FALSE );

	if (flags & MESH_FLAG_RENDER_DOUBLESIDED) Main_ChangeRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	else Main_ChangeRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CCW);

	if( !(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) )
	{
		//ALPHA CHANNEL
		if( flags & MESH_FLAG_RENDER_ALPHATEX )
			Mesh_ChangeTextureStageState( D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		else if( flags & MESH_FLAG_RENDER_ALPHADIFFUSE )
			Mesh_ChangeTextureStageState( D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );
		else
			Mesh_ChangeTextureStageState( D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	}
	
	//Z BUFFER CHECK
	Main_ChangeRenderState( D3DRENDERSTATE_ZENABLE, TRUE );

	//Z BUFFER WRITE
	if( (flags & MESH_FLAG_RENDER_ALLALPHA) && alphaBlend )
		Main_ChangeRenderState( D3DRENDERSTATE_ZWRITEENABLE, FALSE );
	else
		Main_ChangeRenderState( D3DRENDERSTATE_ZWRITEENABLE, TRUE );

//	if (flags & MESH_FLAG_HIGHZBIAS) Main_ChangeRenderState(D3DRENDERSTATE_ZBIAS, 1);
//	else Main_ChangeRenderState(D3DRENDERSTATE_ZBIAS, 0);

	//WORLD TRANSORMATION
	if( flags & MESH_FLAG_TRANSFORM_PARENTPOS )
		Mesh_SetTransform( D3DTRANSFORMSTATE_WORLD, (MATRIX4D*)matWorld );
	else if( flags & MESH_FLAG_TRANSFORM_IDENTITY )
	{	
		Mesh_SetIdentityMatrix( temp );
		Mesh_SetTransform( D3DTRANSFORMSTATE_WORLD, &temp );

	}

	if( flags & MESH_FLAG_RENDER_FILTERNEAREST )
	{	
		Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_NEAREST );
		Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_NEAREST );
	}
	else
	{	
		Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREMAG, D3DFILTER_LINEAR );
//		Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_MIPLINEAR );
		Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREMIN, D3DFILTER_LINEAR );
	}
}

static VOID Mesh_SetAlphaRender( D3DBLEND src, D3DBLEND dest )
{
	Main_ChangeRenderState( D3DRENDERSTATE_ALPHABLENDENABLE,	TRUE );
	Main_ChangeRenderState( D3DRENDERSTATE_SRCBLEND,			src );
	Main_ChangeRenderState( D3DRENDERSTATE_DESTBLEND,			dest );
}


static BOOL Mesh_SetGroupRenderDesc( lpMesh mesh, lpMesh_Group group, LPD3DMATRIX matWorld, BOOL alphaBlend )
{
	if( !(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) )
	{
		if( (group->flags & MESH_FLAG_TEXTURECOLOURONLY) && group->imText )
			Mesh_ChangeTextureStageState( D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
		else
			Mesh_ChangeTextureStageState( D3DTSS_COLOROP, D3DTOP_MODULATE );
	}

	if( group->flags & MESH_FLAG_TRANSTEXTURE )
		Main_ChangeRenderState( D3DRENDERSTATE_COLORKEYENABLE, TRUE );
	else
		Main_ChangeRenderState( D3DRENDERSTATE_COLORKEYENABLE, FALSE );

	if( group->renderFlags )
	{	
		Mesh_SetRenderDesc( group->renderFlags, matWorld, alphaBlend );

		return TRUE;
	}

	return FALSE;
}


static VOID Mesh_AddToPostRenderList( lpMesh mesh, LPD3DMATRIX matWorld )
{
	lpMesh_PostRenderInfo info;


	info = Mem_Alloc( sizeof(Mesh_PostRenderInfo) );
	memset( info, 0, sizeof(Mesh_PostRenderInfo) );

	info->mesh = mesh;
	if( matWorld )
		info->matWorld = (*matWorld);

	//ADD TO LINKED LIST
	info->next = meshGlobs.postRenderMeshList;
	meshGlobs.postRenderMeshList = info;
}


static VOID Mesh_ClearPostRenderList( VOID )
{	
	lpMesh_PostRenderInfo info = meshGlobs.postRenderMeshList;
	lpMesh_PostRenderInfo infoNext;


	while( info )
	{
		infoNext = info->next;

		Mem_Free( info );

		info = infoNext;
	}

	meshGlobs.postRenderMeshList = NULL;
}


VOID Mesh_PostRenderAll( lpViewport vp )
{	
	lpMesh_PostRenderInfo info = meshGlobs.postRenderMeshList;
	lpMesh_Group group;
	ULONG loop;


	Mesh_Debug_CheckIMDevice_Void();

	if( info )
	{	
		Mesh_SetCurrentGODSViewport( vp );

		Mesh_StoreTextureAndMat();

		while( info )
		{
			if( !(info->mesh->flags & MESH_FLAG_HIDDEN) )
			{	
				Mesh_SetMeshRenderDesc( info->mesh, vp, &info->matWorld, TRUE );

				if( info->mesh->flags & MESH_FLAG_POSTEFFECT )
					Mesh_RenderMesh( info->mesh, &info->matWorld, TRUE );
				else
				{
					//RUN THROUGH GROUPS AND ONLY RENDER TRANSPARENT GROUPS
					
					//RENDER ALL GROUPS WITHOUT FLAGS CHANGED FISRT
					for( loop = 0; loop < info->mesh->groupCount; loop++ )
					{
						group = &info->mesh->groupList[loop];

						if( Mesh_CanRenderGroup(group) )
						{
							if( group->flags & MESH_FLAG_ALPHAENABLE )
							{
								if( 0 == group->renderFlags )
									Mesh_RenderGroup( info->mesh, group, &info->matWorld, TRUE );
							}
						}
					}

					//RENDER ALL GROUPS WITH FLAGS CHANGED
					for( loop = 0; loop < info->mesh->groupCount; loop++ )
					{
						group = &info->mesh->groupList[loop];

						if( Mesh_CanRenderGroup(group) )
						{
							if( group->flags & MESH_FLAG_ALPHAENABLE )
							{
								if( group->renderFlags )
									Mesh_RenderGroup( info->mesh, group, &info->matWorld, TRUE );
							}
						}
					}
				}
			}

			info = info->next;
		}

		Mesh_ClearPostRenderList();

		//RESTORE STATES
		Main_RestoreStates(FALSE);
		//Mesh_RestoreTextureStageStates();
		Mesh_RestoreTextureAndMat();
	}
}



lpMesh_Texture Mesh_LoadTexture(LPUCHAR baseDir, LPUCHAR name, LPULONG width, LPULONG height) {

	UCHAR path[FILE_MAXPATH];
	lpMesh_Texture texture = Mem_Alloc(sizeof(Container_Texture));
	LPDIRECTDRAWSURFACE4 surface = NULL;
	lpMesh_TextureReference ref;
	BOOL trans;

	Mesh_Debug_CheckIMDevice_Ptr();

	if (baseDir) sprintf(path, "%s%s", baseDir, name);
	else strcpy(path, name);

	if (ref = Mesh_SearchTexturePathList(meshGlobs.textureList, meshGlobs.textureCount, path)) {
		if( surface = ref->surface )
			surface->lpVtbl->AddRef(surface);
		trans = ref->trans;

	} else if (surface = Container_LoadTextureSurface(path, TRUE, width, height, &trans)) {
		Mesh_AddTexturePathEntry(meshGlobs.textureList, &meshGlobs.textureCount, path, surface, trans);

	} else if (meshGlobs.sharedTextureDir) {

		sprintf(path, "%s%s", meshGlobs.sharedTextureDir, name);

		if (ref = Mesh_SearchTexturePathList(meshGlobs.textureListShared, meshGlobs.textureCountShared, path)) {
			if( surface = ref->surface )
				surface->lpVtbl->AddRef(surface);
			trans = ref->trans;

		} else if (surface = Container_LoadTextureSurface(path, TRUE, width, height, &trans)) {
			Mesh_AddTexturePathEntry(meshGlobs.textureListShared, &meshGlobs.textureCountShared, path, surface, trans);
		}
	}

	if (surface) {
		texture->texture = NULL;
		texture->surface = surface;
		texture->colourKey = trans;
	} else {
		Mem_Free(texture);
		texture = NULL;
//		Error_Fatal(TRUE, Error_Format("Cannot find or load texture >(%s\\)%s<", baseDir, name));
	}

	return texture;

}

static lpMesh_TextureReference Mesh_SearchTexturePathList(lpMesh_TextureReference list, ULONG count, LPUCHAR path) {

	ULONG loop;

	for (loop=0 ; loop<count ; loop++) {
		if (0 == stricmp(path, list[loop].path)) return &list[loop];
	}

	return NULL;
}

static VOID Mesh_AddTexturePathEntry(lpMesh_TextureReference list, LPULONG count, LPUCHAR path, LPDIRECTDRAWSURFACE4 surface, BOOL trans) {

	Error_Fatal(*count==MESH_TEXTURELISTSIZE, "MESH_TEXTURELISTSIZE too small");

	list[*count].path = Util_StrCpy(path);
	list[*count].surface = surface;
	list[*count].trans = trans;
	(*count)++;
}

VOID Mesh_SetGroupTextureIM(lpMesh mesh, ULONG groupID, LPDIRECT3DTEXTURE2 texture) {

	if (groupID < mesh->groupCount) {
		Mesh_Debug_CheckIMDevice_Void();
		mesh->groupList[groupID].imText = texture;
	}
}

static ULONG Mesh_ReplaceTextureImages2(lpMesh_TextureReference list, ULONG count, LPUCHAR fromDirectory, LPUCHAR toDirectory, LPUCHAR prefix) {

	ULONG loop, length, changed = 0;
	LPDIRECTDRAWSURFACE4 surface;
	lpMesh_TextureReference entry;
	UCHAR path[FILE_MAXPATH];
	UCHAR prefixString[1024] = "";
	ULONG width, height;
	DDCOLORKEY colourKey;
	DDPIXELFORMAT pixelFormat[2];
	BOOL trans;
	LPDIRECTDRAWPALETTE palette[2];
	PALETTEENTRY entries[256];

	length = strlen(fromDirectory);
	if (prefix) sprintf(prefixString, "%s", prefix);

	for (loop=0 ; loop<count ; loop++) {
		entry = &list[loop];
		if (0 == strnicmp(entry->path, fromDirectory, length)) {
			sprintf(path, "%s\\%s%s", toDirectory, prefixString, &entry->path[length+1]);
			if (surface = Container_LoadTextureSurface(path, TRUE, &width, &height, &trans)) {

				memset(&pixelFormat[0], 0, sizeof(pixelFormat[0]));
				memset(&pixelFormat[1], 0, sizeof(pixelFormat[1]));
				pixelFormat[0].dwSize = sizeof(pixelFormat[0]);
				pixelFormat[1].dwSize = sizeof(pixelFormat[1]);
				surface->lpVtbl->GetPixelFormat(surface, &pixelFormat[0]);
				entry->surface->lpVtbl->GetPixelFormat(entry->surface, &pixelFormat[1]);

				if (0 == memcmp(&pixelFormat[0], &pixelFormat[1], sizeof(pixelFormat[0]))) {

					if (DD_OK == surface->lpVtbl->GetPalette(surface, &palette[0])) {
						if (DD_OK == entry->surface->lpVtbl->GetPalette(entry->surface, &palette[1])) {
							palette[0]->lpVtbl->GetEntries(palette[0], 0, 0, 256, entries);
							palette[1]->lpVtbl->SetEntries(palette[1], 0, 0, 256, entries);
							palette[1]->lpVtbl->Release(palette[1]);
						}
						palette[0]->lpVtbl->Release(palette[0]);
					}

					entry->surface->lpVtbl->Blt(entry->surface, NULL, surface, NULL, DDBLT_WAIT, NULL);
					surface->lpVtbl->GetColorKey(surface, DDCKEY_SRCBLT, &colourKey);
					entry->surface->lpVtbl->SetColorKey(entry->surface, DDCKEY_SRCBLT, &colourKey);
					surface->lpVtbl->Release(surface);
					changed++;
				}
			}
		}
	}

	return changed;
}

ULONG Mesh_ReplaceTextureImages(LPUCHAR fromDirectory, LPUCHAR toDirectory, LPUCHAR prefix) {

	return Mesh_ReplaceTextureImages2(meshGlobs.textureList, meshGlobs.textureCount, fromDirectory, toDirectory, prefix);
}

VOID Mesh_SetGroupTexture(lpMesh mesh, ULONG groupID, lpMesh_Texture mt) {	

	if (groupID < mesh->groupCount) {
		Mesh_Debug_CheckIMDevice_Void();

	//	Mesh_RemoveGroupTexture(mesh, groupID);

		if (mt) {

			if (mt->surface) mt->surface->lpVtbl->QueryInterface(mt->surface, &IID_IDirect3DTexture2, &mesh->groupList[groupID].imText);
			if (mt->colourKey) mesh->groupList[groupID].flags |= MESH_FLAG_TRANSTEXTURE;
			else mesh->groupList[groupID].flags &= ~MESH_FLAG_TRANSTEXTURE;

		} //else mesh->groupList[groupID].imText = NULL;
	}
}


VOID Mesh_RemoveGroupTexture( lpMesh mesh, ULONG groupID )
{
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];


		Mesh_Debug_CheckIMDevice_Void();

		if( group->imText )
		{
			RELEASE( group->imText )
		
			group->imText = NULL;
		}
	}
}


BOOL Mesh_CreateGroupMaterial( lpMesh mesh, ULONG groupID )
{
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		D3DMATERIAL material =
		{
			sizeof(D3DMATERIAL),
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 1.0f, 1.0f, 1.0f, 1.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			0.0f,
			0,
			0
		};


		Mesh_Debug_CheckIMDevice_Int();

		group->material = material;

		return TRUE;
	}
	return FALSE;
}


static BOOL Mesh_SetGroupMaterial( lpMesh mesh, ULONG groupID, LPD3DMATERIAL mat )
{
	if (groupID < mesh->groupCount) {
		Mesh_Debug_CheckIMDevice_Int();

		mesh->groupList[groupID].material = (*mat);

		return TRUE;
	}
	return FALSE;
}


static LPD3DMATERIAL Mesh_GetGroupMaterial( lpMesh mesh, ULONG groupID )
{	
	if (groupID < mesh->groupCount) {
		Mesh_Debug_CheckIMDevice_Ptr();

		return &mesh->groupList[groupID].material;
	}

	return FALSE;
}


BOOL Mesh_SetGroupColour( lpMesh mesh, ULONG groupID, REAL r, REAL g, REAL b, ULONG type )
{
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		LPD3DMATERIAL material;


		Mesh_Debug_CheckIMDevice_Int();

		material = Mesh_GetGroupMaterial( mesh, groupID );

		if( r < 0.0f )
			r = 0.0f;
		if( g < 0.0f )
			g = 0.0f;
		if( b < 0.0f )
			b = 0.0f;
		if( r > 1.0f )
			r = 1.0f;
		if( g > 1.0f )
			g = 1.0f;
		if( b > 1.0f )
			b = 1.0f;

		if( type == Mesh_Colour_Diffuse )
		{
			material->diffuse.r = r;
			material->diffuse.g = g;
			material->diffuse.b = b;

			if( (r == 1.0f) && (g == 1.0f) && (b == 1.0f) )
				group->flags |= MESH_FLAG_TEXTURECOLOURONLY;
			else
				group->flags &= ~MESH_FLAG_TEXTURECOLOURONLY;

			//Mesh_HideGroup( mesh, groupID, FALSE );
			//if( (r == 0.0f) && (g == 0.0f) && (b == 0.0f) )
			//{	
			//	if( group->renderFlags )
			//	{
			//		if( group->renderFlags & MESH_FLAG_RENDER_ALLALPHA );
			//			Mesh_HideGroup( mesh, groupID, TRUE );
			//	}
			//	else if( mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALLALPHA )
			//		Mesh_HideGroup( mesh, groupID, TRUE );
			//}
		}
		else if( type == Mesh_Colour_Ambient )
		{	
			material->ambient.r = r;
			material->ambient.g = g;
			material->ambient.b = b;
		}
		else if( type == Mesh_Colour_Emissive )
		{	
			material->emissive.r = r;
			material->emissive.g = g;
			material->emissive.b = b;
		}
		else if( type == Mesh_Colour_Specular )
		{	
			material->specular.r = r;
			material->specular.g = g;
			material->specular.b = b;
		}

		return TRUE;
	}

	return FALSE;
}


BOOL Mesh_SetGroupMaterialValues( lpMesh mesh, ULONG groupID, REAL value, ULONG type )
{	
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		LPD3DMATERIAL material;


		Mesh_Debug_CheckIMDevice_Int();

		material = Mesh_GetGroupMaterial( mesh, groupID );

		if( value < 0.0f )
			value = 0.0f;
		if( value > 1.0f )
			value = 1.0f;

		if( type == Mesh_Colour_Alpha )
		{	
			group->flags &= ~MESH_FLAG_ALPHAHIDDEN;
			group->flags &= ~MESH_FLAG_ALPHAENABLE;

			if( 0.0f == value )
			{
				if( group->renderFlags )
				{	
					if( group->renderFlags & MESH_FLAG_RENDER_ALLALPHA );
						group->flags |= MESH_FLAG_ALPHAHIDDEN;
				}
				else if( mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALLALPHA )
					group->flags |= MESH_FLAG_ALPHAHIDDEN;
			}
			else if( 1.0f != value )
			{
				if( group->renderFlags )
				{	
					if( group->renderFlags & MESH_FLAG_RENDER_ALLALPHA );
						group->flags |= MESH_FLAG_ALPHAENABLE;
				}
				else if( mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALLALPHA )
					group->flags |= MESH_FLAG_ALPHAENABLE;
			}

			//COLOUR ADDITION CAN OCCUR EVEN IF ALPHA VALUE IS 1.0f
			if( group->renderFlags )
			{
				if( (group->renderFlags & MESH_FLAG_RENDER_ALPHA11) ||
					(group->renderFlags & MESH_FLAG_RENDER_ALPHASA1) ||
					(group->renderFlags & MESH_FLAG_RENDER_ALPHASA0))
				{
					//group->flags &= ~MESH_FLAG_ALPHAHIDDEN;
					group->flags |= MESH_FLAG_ALPHAENABLE;
				}
			}
			else if( (mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALPHA11) ||
				(mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALPHASA1) ||
				(mesh->renderDesc.renderFlags & MESH_FLAG_RENDER_ALPHASA0) )
			{
				//group->flags &= ~MESH_FLAG_ALPHAHIDDEN;
				group->flags |= MESH_FLAG_ALPHAENABLE;
			}

			material->diffuse.a = value;
		}
		else if( type == Mesh_Colour_Power )
			material->power = value;

		return TRUE;
	}

	return FALSE;
}


VOID Mesh_GetGroupColour( lpMesh mesh, ULONG groupID, LPREAL r, LPREAL g, LPREAL b, ULONG type )
{
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		LPD3DMATERIAL material;


		Mesh_Debug_CheckIMDevice_Void();

		material = Mesh_GetGroupMaterial( mesh, groupID );

		if( type == Mesh_Colour_Diffuse )
		{	
			*r = material->diffuse.r;
			*g = material->diffuse.g;
			*b = material->diffuse.b;
		}
		else if( type == Mesh_Colour_Ambient )
		{	
			*r = material->ambient.r;
			*g = material->ambient.g;
			*b = material->ambient.b;
		}
		else if( type == Mesh_Colour_Emissive )
		{	
			*r = material->emissive.r;
			*g = material->emissive.g;
			*b = material->emissive.b;
		}
		else if( type == Mesh_Colour_Specular )
		{	
			*r = material->specular.r;
			*g = material->specular.g;
			*b = material->specular.b;
		}
	}
}


VOID Mesh_GetGroupMaterialValues( lpMesh mesh, ULONG groupID, LPREAL value, ULONG type )
{
	if (groupID < mesh->groupCount) {
		lpMesh_Group group = &mesh->groupList[groupID];
		LPD3DMATERIAL material;


		Mesh_Debug_CheckIMDevice_Void();

		material = Mesh_GetGroupMaterial( mesh, groupID );

		if( type == Mesh_Colour_Alpha )
			*value = material->diffuse.a;
		else if( type == Mesh_Colour_Power )
			*value = material->power;
	}
}


VOID Mesh_SetIdentityMatrix( MATRIX4D m )
{
    m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = 0.0f;
    m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.0f;
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}


VOID Mesh_SetTranslationMatrix( MATRIX4D m, LPD3DVECTOR t )
{
	Mesh_SetIdentityMatrix(m);
	
	m[3][0] = t->x;
	m[3][1] = t->y;
	m[3][2] = t->z;
}


static BOOL Mesh_SetCurrentViewport( LPDIRECT3DRMVIEWPORT view )
{
	LPDIRECT3DVIEWPORT imview1;
	LPDIRECT3DVIEWPORT3 imview;


	if( D3DRM_OK != view->lpVtbl->GetDirect3DViewport(view, &imview1) )
	{
		Error_Warn( TRUE, "Cannot 'GetDirect3DViewport'." );
		return FALSE;
	}

	if( D3DRM_OK != imview1->lpVtbl->QueryInterface(imview1, &IID_IDirect3DViewport3, &imview) )
	{	
		Error_Warn( TRUE, "Cannot 'QueryInterface' 'IID_IDirect3DViewport3'." );
		RELEASE( imview1 );		
		return FALSE;
	}

	RELEASE( imview1 );

	if( D3D_OK != lpIMDevice()->lpVtbl->SetCurrentViewport(lpIMDevice(), imview) )
	{	
		Error_Warn( TRUE, "Cannot 'SetCurrentViewport'." );
		RELEASE( imview );
		return FALSE;
	}

	RELEASE( imview );

	return TRUE;
}


static BOOL Mesh_SetCurrentGODSViewport( lpViewport vp )
{
	LPDIRECT3DVIEWPORT imview1;
	LPDIRECT3DVIEWPORT3 imview;


	if( D3DRM_OK != vp->lpVP->lpVtbl->GetDirect3DViewport(vp->lpVP, &imview1) )
	{	
		Error_Warn( TRUE, "Cannot 'GetDirect3DViewport'." );
		return FALSE;
	}

	if( D3DRM_OK != imview1->lpVtbl->QueryInterface(imview1, &IID_IDirect3DViewport3, &imview) )
	{	
		Error_Warn( TRUE, "Cannot 'QueryInterface' 'IID_IDirect3DViewport3'." );
		RELEASE( imview1 );		
		return FALSE;
	}

	RELEASE( imview1 );

	if( D3D_OK != lpIMDevice()->lpVtbl->SetCurrentViewport(lpIMDevice(), imview) )
	{	
		Error_Warn( TRUE, "Cannot 'SetCurrentViewport'." );
		RELEASE( imview );
		return FALSE;
	}

	RELEASE( imview );

	return TRUE;
}


static BOOL Mesh_SetTransform( D3DTRANSFORMSTATETYPE state, MATRIX4D* matrix )
{	
	D3DMATRIX oldMatrix;
	D3DMATRIX newMatrix = *((LPD3DMATRIX)matrix);


	//DIRECTX DOCUMENTATION STATES CALLS TO 'SetTransform' SHOULD BE MINIMISED
	if( D3D_OK != lpIMDevice()->lpVtbl->GetTransform(lpIMDevice(), state, &oldMatrix) )
		Error_Warn( TRUE, "Cannot 'GetTransform'." );

	//MAYBE PUT != COMPARISON AS A GLOBAL FUNCTION?
	if( (oldMatrix._11 != newMatrix._11) || (oldMatrix._12 != newMatrix._12) || (oldMatrix._13 != newMatrix._13) || (oldMatrix._14 != newMatrix._14) ||
		(oldMatrix._21 != newMatrix._21) || (oldMatrix._22 != newMatrix._22) || (oldMatrix._23 != newMatrix._23) || (oldMatrix._24 != newMatrix._24) ||
		(oldMatrix._31 != newMatrix._31) || (oldMatrix._32 != newMatrix._32) || (oldMatrix._33 != newMatrix._33) || (oldMatrix._34 != newMatrix._34) ||
		(oldMatrix._41 != newMatrix._41) || (oldMatrix._42 != newMatrix._42) || (oldMatrix._43 != newMatrix._43) || (oldMatrix._44 != newMatrix._44) )
	{	
		if( D3D_OK != lpIMDevice()->lpVtbl->SetTransform(lpIMDevice(), state, (LPD3DMATRIX)matrix) )
		{	
			Error_Warn( TRUE, "Cannot 'SetTransform'." );

			return FALSE;
		}
	}

	return TRUE;
}


static BOOL Mesh_ChangeTextureStageState(D3DTEXTURESTAGESTATETYPE dwRenderStateType, DWORD dwRenderState) {

	lpMesh_TextureStateChangeData data;
	DWORD currValue;

	Error_Fatal(dwRenderStateType>=MESH_MAXTEXTURESTAGESTATES, "TextureStageState type is out of range");

	data = &meshGlobs.stateData[dwRenderStateType];
	if( D3D_OK != lpIMDevice()->lpVtbl->GetTextureStageState(lpIMDevice(), 0, dwRenderStateType, &currValue) )
	{	Error_Warn( TRUE, "Cannot 'GetTextureStageState'." );

		currValue = -1;
		//return FALSE;
	}

	if (currValue != dwRenderState){

		if( D3D_OK != lpIMDevice()->lpVtbl->SetTextureStageState( lpIMDevice(), 0, dwRenderStateType, dwRenderState ) )
		{	Error_Warn( TRUE, "Cannot 'SetTextureStageState'." );

			return FALSE;
		}
		else
		{	if (data->changed) {
				if (data->origValue == currValue) data->changed = FALSE;
			} else {	
				data->origValue = currValue;
				data->changed = TRUE;
			}
		}
		
	}

	return TRUE;

}


static VOID Mesh_RestoreTextureStageStates(VOID) {

//#ifndef _GODS98_VIDEOMEMTEXTURES
	if (!(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES)) {
	ULONG loop;
	lpMesh_TextureStateChangeData data;


	for (loop=0 ; loop<MESH_MAXTEXTURESTAGESTATES ; loop++)
	{
		data = &meshGlobs.stateData[loop];
		if (data->changed) {
			if( D3D_OK != lpIMDevice()->lpVtbl->SetTextureStageState( lpIMDevice(), 0, loop, data->origValue ) )
				Error_Warn( TRUE, "Cannot 'SetTextureStageState'." );
			data->changed = FALSE;
		}

	}
	}
//#endif //_GODS98_VIDEOMEMTEXTURES
}


static VOID Mesh_StoreTextureAndMat( VOID )
{	BOOL ok = TRUE;


	//GET OLD MATERIAL
	if( D3D_OK != lpIMDevice()->lpVtbl->GetLightState( lpIMDevice(), D3DLIGHTSTATE_MATERIAL, &meshGlobs.oldMatIM ) )
	{	Error_Warn( TRUE, "Cannot 'GetLightState' for current D3DIM material." );

		ok = FALSE;
	}
	meshGlobs.currMatIM = meshGlobs.oldMatIM;

//#ifndef  _GODS98_VIDEOMEMTEXTURES
	if (!(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES)) {
	//GET OLD TEXTURE
	if( D3D_OK != lpIMDevice()->lpVtbl->GetTexture( lpIMDevice(), 0, &meshGlobs.oldTextureIM ) )
	{	Error_Warn( TRUE, "Cannot 'GetTexture' for current D3DIM texture." );

		ok = FALSE;
	}
	meshGlobs.currTextureIM = meshGlobs.oldTextureIM;

	//GET OLD RM TEXTURE
	lpIMDevice()->lpVtbl->GetRenderState( lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, &meshGlobs.oldTextureRM );
	//CLEAR RETAINED MODE TEXTURE HANDLE
	if( 0 != meshGlobs.oldTextureRM )
		lpIMDevice()->lpVtbl->SetRenderState( lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, 0 );
	} else {
//#else //_GODS98_VIDEOMEMTEXTURES
	lpIMDevice()->lpVtbl->GetRenderState( lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, &meshGlobs.oldTextureRM );
	meshGlobs.currTextureRM = meshGlobs.oldTextureRM;
	}
//#endif //_GODS98_VIDEOMEMTEXTURES

}


static VOID Mesh_RestoreTextureAndMat( VOID )
{	//D3DMATERIALHANDLE oldMatHandle;
	//LPDIRECT3DTEXTURE2 oldTexture;
	BOOL ok = TRUE;
	

/*	//GET OLD MATERIAL
	if( D3D_OK != lpIMDevice()->lpVtbl->GetLightState( lpIMDevice(), D3DLIGHTSTATE_MATERIAL, &oldMatHandle ) )
	{	Error_Warn( TRUE, "Cannot 'GetLightState' for current D3DIM material." );

		ok = FALSE;
	}
	//GET OLD TEXTURE
	if( D3D_OK != lpIMDevice()->lpVtbl->GetTexture( lpIMDevice(), 0, &oldTexture ) )
	{	Error_Warn( TRUE, "Cannot 'GetTexture' for current D3DIM texture." );

		ok = FALSE;
	}
*/

	if( meshGlobs.currMatIM != meshGlobs.oldMatIM )
		//SET OLD MATERIAL
		if( D3D_OK != lpIMDevice()->lpVtbl->SetLightState( lpIMDevice(), D3DLIGHTSTATE_MATERIAL, meshGlobs.oldMatIM ) )
		{	Error_Warn( TRUE, "Cannot 'SetLightState' for old D3DIM material." );

			ok = FALSE;
		}

//#ifndef _GODS98_VIDEOMEMTEXTURES
if (!(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES)) {

	if( meshGlobs.currTextureIM != meshGlobs.oldTextureIM )
		//SET OLD TEXTURE
		if( D3D_OK != lpIMDevice()->lpVtbl->SetTexture( lpIMDevice(), 0, meshGlobs.oldTextureIM ) )
		{	Error_Warn( TRUE, "Cannot 'SetTexture' for old D3DIM texture." );

			ok = FALSE;
		}

	//SET OLD RETAINED MODE TEXTURE
	if( 0 != meshGlobs.oldTextureRM )
		lpIMDevice()->lpVtbl->SetRenderState( lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, meshGlobs.oldTextureRM );
} else {
//#else //_GODS98_VIDEOMEMTEXTURES
	lpIMDevice()->lpVtbl->SetRenderState( lpIMDevice(), D3DRENDERSTATE_TEXTUREHANDLE, meshGlobs.oldTextureRM );
//#endif //_GODS98_VIDEOMEMTEXTURES
}


}


static BOOL Mesh_RenderMesh( lpMesh mesh, LPD3DMATRIX matWorld, BOOL alphaBlend )
{	
	BOOL ok = TRUE;
	lpMesh_Group group;
	ULONG loop;


	//RENDER ALL GROUPS WITHOUT FLAGS CHANGED FISRT
	for( loop = 0; loop < mesh->groupCount; loop++ )
	{
		group = &mesh->groupList[loop];

		if( Mesh_CanRenderGroup(group) )
		{
			if( 0 == group->renderFlags )
			{
				if( !Mesh_RenderGroup(mesh, group, matWorld, alphaBlend) )
					ok = FALSE;
			}
		}
	}

	//RENDER ALL GROUPS WITH FLAGS CHANGED
	for( loop = 0; loop < mesh->groupCount; loop++ )
	{
		group = &mesh->groupList[loop];

		if( Mesh_CanRenderGroup(group) )
		{
			if( group->renderFlags )
			{
				if( !Mesh_RenderGroup(mesh, group, matWorld, alphaBlend) )
					ok = FALSE;
			}
		}
	}

	return ok;
}

VOID Mesh_SetAmbientLight(REAL r, REAL g, REAL b) {

	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;
	if (r < 0.0f) r = 0.0f;
	if (g < 0.0f) g = 0.0f;
	if (b < 0.0f) b = 0.0f;

	meshGlobs.ambientLight = ((ULONG) (r * 255.0f) << 16) | ((ULONG) (g * 255.0f) << 8) | ((ULONG) (b * 255.0f));
}

static BOOL Mesh_CanRenderGroup( lpMesh_Group group )
{
	return ( !(group->flags & MESH_FLAG_HIDDEN) && !(group->flags & MESH_FLAG_ALPHAHIDDEN) );
}

static BOOL Mesh_RenderGroup( lpMesh mesh, lpMesh_Group group, LPD3DMATRIX matWorld, BOOL alphaBlend )
{	
	//BOOL flagsChanged;
	BOOL ok = TRUE;
	int frame;

	//COULD RUN THROUGH ALL GROUPS WITHOUT INDIVIDUAL RENDERING FLAGS
	//THEN RENDER GROUPS WITH RENDERING FLAGS ALTERED

	//flagsChanged = Mesh_SetGroupRenderDesc( mesh, group, matWorld, alphaBlend );

	Mesh_SetGroupRenderDesc( mesh, group, matWorld, alphaBlend );

	//if( !Mesh_RenderTriangleList(group->matHandle, group->imText, MESH_DEFAULTRENDERFLAGS, 
	//	group->vertices, group->vertexCount, group->faceData, group->faceDataSize) )
	//	ok = FALSE;

	//SET THE MATERIAL FOR RENDER - SEE END OF FILE
	if( !Mesh_SetMaterial(&group->material) )
		ok = FALSE;


	if (mesh->textureRenderCallback) 
	{
		frame = (mesh->textureRenderCallback(mesh->textureRenderCallbackData));
		if (frame != -1) Mesh_SetTextureTime2( mesh, (float)frame);

	}

	if( !Mesh_RenderTriangleList(meshGlobs.matHandle, group->imText, MESH_DEFAULTRENDERFLAGS, 
		group->vertices, group->vertexCount, group->faceData, group->faceDataSize) )
		ok = FALSE;

	//if( flagsChanged )
		//RESTORE PARENT MESH STATES
	//	Mesh_SetRenderDesc( mesh->renderDesc.renderFlags, matWorld, alphaBlend );

	return ok;
}

static BOOL Mesh_RenderTriangleList( D3DMATERIALHANDLE matHandle, LPDIRECT3DTEXTURE2 texture, DWORD renderFlags,
									Mesh_Vertex vertices[], DWORD vertexCount, UWORD faceData[], DWORD indexCount )
{	
	BOOL ok = TRUE;
	ULONG textureHandle;
	LPDIRECT3DDEVICE2 device2;
	ULONG oldAmbientLightState;

	//TEXTURES
	if( !(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES) )
	{
		if( texture != meshGlobs.currTextureIM )
		{
			//SET NEW TEXTURE
			if( D3D_OK != lpIMDevice()->lpVtbl->SetTexture(lpIMDevice(), 0, texture) )
			{
				Error_Warn( TRUE, "Cannot 'SetTexture' for new D3DIM texture." );
				ok = FALSE;
			}
			else
				meshGlobs.currTextureIM = texture;
		}	
	} 
	else
	{	
		textureHandle = 0;

		if( texture )
		{	
			//QUERY INTERFACE FOR OLD DEVICE AND GET HANDLE
			lpIMDevice()->lpVtbl->QueryInterface( lpIMDevice(), &IID_IDirect3DDevice2, &device2 );
			texture->lpVtbl->GetHandle( texture, device2, &textureHandle );
			RELEASE( device2 );
		}

		if( textureHandle != meshGlobs.currTextureRM )
		{
			//SET NEW TEXTURE
			Main_ChangeRenderState( D3DRENDERSTATE_TEXTUREHANDLE, textureHandle );
			meshGlobs.currTextureRM = textureHandle;
		}
	}

	//MATERIAL
	if( matHandle != meshGlobs.currMatIM )
	{
		//SET NEW MATERIAL
		if( D3D_OK != lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_MATERIAL, matHandle) )
		{	
			Error_Warn( TRUE, "Cannot 'SetLightState' for new D3DIM material." );
			ok = FALSE;
		}
		else
			meshGlobs.currMatIM = matHandle;
	}

	lpIMDevice()->lpVtbl->GetLightState(lpIMDevice(), D3DLIGHTSTATE_AMBIENT, &oldAmbientLightState);
	lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_AMBIENT, meshGlobs.ambientLight);
	
	//RENDER PRIMITIVE   
	if( D3D_OK != lpIMDevice()->lpVtbl->DrawIndexedPrimitive(lpIMDevice(), D3DPT_TRIANGLELIST, renderFlags,
		vertices, vertexCount, faceData, indexCount, 0) )
	{	
		Error_Warn( TRUE, "Cannot 'DrawIndexedPrimitive'." );
		ok = FALSE;
	}

	lpIMDevice()->lpVtbl->SetLightState(lpIMDevice(), D3DLIGHTSTATE_AMBIENT, oldAmbientLightState);

	return ok;
}
