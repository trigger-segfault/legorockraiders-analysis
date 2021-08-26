
#ifdef _DEBUG
//#define _HIERARCHY_DEBUG
#endif // _DEBUG

//#define CONTAINER_MATCHHIDDENHIERARCHY
//#define CONTAINER_DONTFLIPTEXTURES

#define CONTAINER_DISABLEFRAMESETTINGS

/**********************************************************************************
 **
 ** Containers.c:
 **
 ** Copyright (C) Data Design Interactive.
 **
 **
 ** Written by Robert Wilson 20/01/98
 **
 **********************************************************************************/

#include <d3drm.h>

#include "..\inc\Standard.h"

#ifdef LEGO_IMMEDIATEMODEMAP
#define CONTAINER_USEOWNTEXTURELOAD
#endif //LEGO_IMMEDIATEMODEMAP

#include "..\inc\Errors.h"
#include "..\inc\Maths.h"
#include "..\inc\Files.h"
#include "..\inc\Memory.h"
#include "..\inc\Utils.h"
#include "..\inc\Config.h"
#include "..\inc\Activities.h"
#include "..\inc\Main.h"
#include "..\inc\Images.h"
//#include "..\inc\Sound.h"
#include "..\inc\Lws.h"
#include "..\inc\AnimClone.h"
#include "..\inc\Mesh.h"
#include "..\inc\Containers.h"
#include "..\inc\Viewports.h"
#include "..\inc\Materials.h"
#include "..\inc\DirectDraw.h"
#include "..\inc\Bmp.h"
#include "..\inc\dxbug.h"

//#undef _DEBUG

/**********************************************************************************
 ******** Static function prototypes
 **********************************************************************************/

static HRESULT Container_TextureLoadCallback(char *name, void *data, LPDIRECT3DRMTEXTURE3 *texture);
VOID Container_Debug_NoteCreation(LPDIRECT3DRMOBJECT lpD3DRMobj, ULONG line);
ULONG Container_Debug_GetCreationLine(LPDIRECT3DRMOBJECT lpD3DRMobj);
VOID Container_Debug_DestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg);
VOID Container_Debug_DumpCreationInfo(VOID);

/**********************************************************************************
 ******** Global Definitions
 **********************************************************************************/

Container_Globs containerGlobs;

/**********************************************************************************
 ******** Container Global Library Functions
 **********************************************************************************/

lpContainer Container_Initialise(LPUCHAR gameName){

	ULONG loop;
	lpContainer root;

	if (containerGlobs.flags & CONTAINER_FLAG_INITIALISED) Error_Fatal(TRUE, "Containers already initialised");

	memset(&containerGlobs, 0, sizeof(Container_Globs));

	for (loop=0 ; loop<CONTAINER_MAXLISTS ; loop++){
		containerGlobs.listSet[loop] = NULL;
	}

	containerGlobs.typeName[Container_Null]					= CONTAINER_NULLSTRING;
	containerGlobs.typeName[Container_Mesh]					= CONTAINER_MESHSTRING;
	containerGlobs.typeName[Container_Frame]				= CONTAINER_FRAMESTRING;
	containerGlobs.typeName[Container_Anim]					= CONTAINER_ANIMSTRING;
	containerGlobs.typeName[Container_LWS]					= CONTAINER_LWSSTRING;
#pragma message ( "Are all 'Container_LWO' functions written?" )
	containerGlobs.typeName[Container_LWO]					= CONTAINER_LWOSTRING;
	containerGlobs.typeName[Container_FromActivity]			= CONTAINER_ACTIVITYSTRING;
	containerGlobs.typeName[Container_Light]				= NULL;

	containerGlobs.extensionName[Container_Null]			= "";
	containerGlobs.extensionName[Container_Mesh]			= "x";
	containerGlobs.extensionName[Container_Frame]			= "x";
	containerGlobs.extensionName[Container_Anim]			= "x";
	containerGlobs.extensionName[Container_FromActivity]	= ACTIVITY_FILESUFFIX;
	containerGlobs.extensionName[Container_Light]			= "";

	containerGlobs.gameName = gameName;
	containerGlobs.freeList = NULL;
	containerGlobs.listCount = 0;
	containerGlobs.flags = CONTAINER_FLAG_INITIALISED;

	containerGlobs.textureCount = 0;
	containerGlobs.sharedDir = NULL;

	containerGlobs.rootContainer = root = Container_Create(NULL);

	root->masterFrame->lpVtbl->SetSortMode(root->masterFrame, D3DRMSORT_NONE);

/*
#ifdef _DEBUG
	Container_Frame_FormatName(root->masterFrame, "Container Root Master Frame for %s", gameName);
#endif // _DEBUG
*/
	// Debuggy
//	scene->lpVtbl->AddChild(scene, CDF(root->masterFrame));

	return root;
}

VOID Container_Shutdown(VOID){

	ULONG loop, count, sub, unfreed=0;
	lpContainer testCont;

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	for (loop=0 ; loop<CONTAINER_MAXLISTS ; loop++){

		if (containerGlobs.listSet[loop]){

			count = 0x00000001 << loop;
		
			for (sub=0 ; sub<count ; sub++){
				if (testCont = &containerGlobs.listSet[loop][sub]){
					if (testCont->nextFree == testCont){
						Error_Debug(Error_Format("Warning: Unfreed Container type #%d\n", testCont->type));
						unfreed++;
						Container_Remove2(testCont, TRUE);
					} 
				}
			}

			Mem_Free(containerGlobs.listSet[loop]);
		}
	}

	containerGlobs.freeList = NULL;
	containerGlobs.flags = 0x00000000;

	for (loop=0 ; loop<containerGlobs.textureCount ; loop++){
		if (containerGlobs.textureSet[loop].fileName) {
			Error_Debug(Error_Format("Texture %s was not removed\n", containerGlobs.textureSet[loop].fileName));
			Mem_Free(containerGlobs.textureSet[loop].fileName);
		}
	}

	if( containerGlobs.sharedDir )
		Mem_Free( containerGlobs.sharedDir );

#ifdef _DEBUG
	if (unfreed) Error_Debug(Error_Format("Warning: %d Unremoved Container%s\n", unfreed, 1==unfreed?"":"s"));
#endif // _DEBUG

#ifdef _HIERARCHY_DEBUG
	Container_Debug_DumpCreationInfo();
#endif // _HIERARCHY_DEBUG

}

VOID Container_SetSharedTextureDirectory(LPUCHAR path) {

	containerGlobs.sharedDir = Util_StrCpy(path);
}

VOID Container_EnableSoundTriggers(BOOL on) {

	if (on) containerGlobs.flags |= CONTAINER_FLAG_TRIGGERENABLED;
	else containerGlobs.flags &= ~CONTAINER_FLAG_TRIGGERENABLED;
}

VOID Container_SetTriggerFrameCallback(VOID (*Callback)(lpContainer cont, LPVOID data), LPVOID data) {

	containerGlobs.triggerFrameCallback = Callback;
	containerGlobs.triggerFrameData = data;
}

VOID Container_SetSoundTriggerCallback(VOID (*Callback)(LPUCHAR fname, lpContainer cont, LPVOID data), LPVOID data) {

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	containerGlobs.soundTriggerCallback = Callback;
	containerGlobs.soundTriggerData = data;
	containerGlobs.flags |= CONTAINER_FLAG_TRIGGERENABLED;
}

lpContainer Container_GetRoot(VOID) {

	return containerGlobs.rootContainer;
}

__inline ULONG Container_GetRGBAColour(REAL r, REAL g, REAL b, REAL a) {

	if (r > 1.0f) r = 1.0f;
	if (g > 1.0f) g = 1.0f;
	if (b > 1.0f) b = 1.0f;
	if (a > 1.0f) a = 1.0f;
	if (r < 0.0f) r = 0.0f;
	if (g < 0.0f) g = 0.0f;
	if (b < 0.0f) b = 0.0f;
	if (a < 0.0f) a = 0.0f;

	return D3DRGBA(r, g, b, a);
}

__inline ULONG Container_GetRGBColour(REAL r, REAL g, REAL b) {

	return Container_GetRGBAColour(r, g, b, 1.0f);
}

lpContainer Container_Create(lpContainer parent){

	lpContainer newContainer;
	LPDIRECT3DRMFRAME3 parentFrame = NULL, hiddenParentFrame = NULL;

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	if (parent) {
		parentFrame = parent->masterFrame;
		hiddenParentFrame = parent->hiddenFrame;
	}

	if (NULL == containerGlobs.freeList) Container_AddList();
	
	newContainer = containerGlobs.freeList;
	containerGlobs.freeList = newContainer->nextFree;
	memset(newContainer, 0, sizeof(Container));
	newContainer->nextFree = newContainer;

	// Container Initialisation

/*	newContainer->masterFrame = NULL;
	newContainer->activityFrame = NULL;
	newContainer->hiddenFrame = NULL;
	newContainer->cloneData = NULL;
	newContainer->typeData = NULL;
	newContainer->type = Container_Null;
	newContainer->flags = 0x00000000;
	newContainer->activityCallback = NULL;
	newContainer->activityCallbackData = NULL;
	newContainer->userData = NULL;
*/
	
	if (lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), parentFrame, &newContainer->masterFrame) == D3DRM_OK){
		Container_NoteCreation(newContainer->masterFrame);
		if (lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), newContainer->masterFrame, &newContainer->activityFrame) == D3DRM_OK){
			Container_NoteCreation(newContainer->activityFrame);
			if (lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), hiddenParentFrame, &newContainer->hiddenFrame) == D3DRM_OK){
				Container_NoteCreation(newContainer->hiddenFrame);

				// These frames should all appear as the same part of the heirarchy
				// so set them up as all having newContainer as being their owner...
				// Getting the children of the Container will be tricky...

				Container_Frame_SetAppData(newContainer->masterFrame, newContainer, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				Container_Frame_SetAppData(newContainer->activityFrame, newContainer, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
				Container_Frame_SetAppData(newContainer->hiddenFrame, newContainer, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

				return newContainer;
			}
		}
	}

	Error_Fatal(TRUE, "Unable to Create Container Frames");
	Container_Remove(newContainer);
	return NULL;
}

VOID Container_Remove(lpContainer dead){

	Container_Remove2(dead, FALSE);
}

static VOID Container_Remove2(lpContainer dead, BOOL kill){

//	LPDIRECT3DRMFRAME tempFrame1;
	LPDIRECT3DRMFRAME3 parentFrame;
	HRESULT r;

	Container_DebugCheckOK(dead);

	Error_Fatal(!dead, "NULL passed to Container_Remove()");

/*	{
		ULONG loop;
		lpContainer_RotationData rot;
		for (loop=0 ; loop<containerGlobs.rotationCount ; loop++) {
			rot = &containerGlobs.rotationList[loop];
			if (dead == rot->container) rot->container = NULL;
		}
	}*/

	if (Container_Reference != dead->type) Container_SetParent(dead, NULL);		// Unparent it first...

	if (Container_FromActivity == dead->type || Container_Anim == dead->type){

		if (dead->cloneData) {
			if (kill){
				if (dead->cloneData->cloneTable) Mem_Free(dead->cloneData->cloneTable);
				Mem_Free(dead->cloneData);
			} else {
				dead->cloneData->used = FALSE;
				return;
			}
		}
	}

	// The Animation sets for the activity type object are not stored in the
	// typeData (as there are is an unlimited/unordered number of them) therefore
	// they are stored in the frames AppData section... So release them...

	if (Container_FromActivity == dead->type){
//		LPDIRECT3DRMANIMATIONSET *animSetList;
		lpAnimClone *animCloneList;
		LPDIRECT3DRMFRAME3 *frameList;
		ULONG loop, count;

		count = Container_GetActivities(dead, NULL, NULL, NULL);

		// Allocate two temporary buffers to be filled in with the list of
		// animation sets and frames (one for each activity)...
//		animSetList = Mem_Alloc(sizeof(LPDIRECT3DRMANIMATIONSET) * count);
		animCloneList = Mem_Alloc(sizeof(lpAnimClone) * count);
		frameList = Mem_Alloc(sizeof(LPDIRECT3DRMFRAME3) * count);
		Container_GetActivities(dead, frameList, animCloneList, NULL);

		for (loop=0 ; loop<count ; loop++){

			// Release the animation set,
//			r = animSetList[loop]->lpVtbl->Release(animSetList[loop]);
			AnimClone_Remove(animCloneList[loop]);
			// and free the string defining the frame's name,
			Container_Frame_FreeName(frameList[loop]);
			// Remove the appdata...
			Container_Frame_RemoveAppData(frameList[loop]);
			// Then release our reference to the frame...
			r = frameList[loop]->lpVtbl->Release(frameList[loop]);
		}

		// Free the temporary buffers...
		Mem_Free(animCloneList);
		Mem_Free(frameList);

	} else if (Container_Mesh == dead->type){
		
		lpContainer_MeshAppData appData;
		LPDIRECT3DRMMESH mesh, subMesh;
		lpMesh transmesh;
		ULONG loop;

		if (dead->typeData){
	
			if (transmesh = dead->typeData->transMesh)
				Mesh_Remove(dead->typeData->transMesh, dead->activityFrame);
			else {
				mesh = dead->typeData->mesh;
				// Free the seperate mesh groups if used...
				if (appData = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)){

					for (loop=0 ; loop<appData->usedCount ; loop++) {
						subMesh = appData->meshList[loop];
						dead->activityFrame->lpVtbl->DeleteVisual(dead->activityFrame, (struct IUnknown *) subMesh);
						r = subMesh->lpVtbl->Release(subMesh);
					}
					// Root mesh gets removed in Container_FreeTypeData()...

					Mem_Free(appData->meshList);
					Mem_Free(appData);
				}
			}

		}
	} else if (Container_Anim == dead->type){
		
//		LPDIRECT3DRMANIMATIONSET animSet = Container_Frame_GetAnimSet(dead->activityFrame);
//		r = animSet->lpVtbl->Release(animSet);
		lpAnimClone animClone;
		if (animClone = Container_Frame_GetAnimClone(dead->activityFrame)){
			AnimClone_Remove(animClone);
		}
	}

#ifdef _DEBUG
	if (Container_Reference != dead->type) {
		Container_Frame_FreeName(dead->masterFrame);
		Container_Frame_FreeName(dead->activityFrame);
	}
	Container_Frame_FreeName(dead->hiddenFrame);
#endif // _DEBUG

	// Remove the typeData from the container and the AppData from the frames...
	Container_FreeTypeData(dead);
	if (Container_Reference != dead->type || !(dead->flags & CONTAINER_FLAG_DEADREFERENCE)) Container_Frame_RemoveAppData(dead->masterFrame);
	if (Container_Reference != dead->type) Container_Frame_RemoveAppData(dead->activityFrame);
	Container_Frame_RemoveAppData(dead->hiddenFrame);

	// Remove the frames and all unreferenced decendants from the hierachy...
	

		// Special case... Don't remove the masterFrame if this is a reference Container.
//		dead->activityFrame->lpVtbl->GetParent(dead->activityFrame, &parentFrame);
//		if (parentFrame) {
//			parentFrame->lpVtbl->DeleteChild(parentFrame, dead->activityFrame);
//			parentFrame->lpVtbl->Release(parentFrame);
//		}
//		r = dead->activityFrame->lpVtbl->Release(dead->activityFrame);

	if (Container_Reference != dead->type){

		dead->masterFrame->lpVtbl->GetParent(dead->masterFrame, &parentFrame);
//		parentFrame = CUF(tempFrame1);
//		if (tempFrame1) tempFrame1->lpVtbl->Release(tempFrame1);
		if (parentFrame) {
			parentFrame->lpVtbl->DeleteChild(parentFrame, dead->masterFrame);
			parentFrame->lpVtbl->Release(parentFrame);
		}
		r = dead->masterFrame->lpVtbl->Release(dead->masterFrame);
		r = dead->activityFrame->lpVtbl->Release(dead->activityFrame);

	//	containerGlobs.rootFrame->lpVtbl->DeleteChild(containerGlobs.rootFrame, CDF(dead->hiddenFrame));
		dead->hiddenFrame->lpVtbl->GetParent(dead->hiddenFrame, &parentFrame);
	//	parentFrame = CUF(tempFrame1);
		if (parentFrame) {
			parentFrame->lpVtbl->DeleteChild(parentFrame, dead->hiddenFrame);
			parentFrame->lpVtbl->Release(parentFrame);
		}
		r = dead->hiddenFrame->lpVtbl->Release(dead->hiddenFrame);
	} else {
		dead->hiddenFrame->lpVtbl->Release(dead->hiddenFrame);
	}

	// Trash the container structure...
	Mem_DebugTrash(dead, CONTAINER_TRASHVALUE, sizeof(Container));

	// Link the freed Container in at the begining of the free list so it may be re-used...
	dead->nextFree = containerGlobs.freeList;
	containerGlobs.freeList = dead;
}

lpContainer Container_Load(lpContainer parent, LPUCHAR filename, LPUCHAR typestr, BOOL looping){

	enum Container_Type type;
	Config *rootConf, *conf;
	UCHAR tempString[UTIL_DEFSTRINGLEN];
	UCHAR name[UTIL_DEFSTRINGLEN], baseDir[UTIL_DEFSTRINGLEN];
	lpContainer cont = NULL;
	REAL scale;
	BOOL noTexture;

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	type = Container_ParseTypeString(typestr, &noTexture);

	strcpy(name, filename);

	if (Container_FromActivity == type){
		
		LPUCHAR argv[20];
		ULONG argc;

		Error_Fatal(!containerGlobs.gameName, "Need to set game name in Container_Initialise() in order to load from Activity File");
		
		// The name of the 'FromActivity' container defines the directory
		// in which all of the files will be located.

		strcpy(baseDir, name);
		argc = Util_Tokenise(name, argv, "\\");
		sprintf(tempString, "%s\\%s.%s", baseDir, argv[argc-1], containerGlobs.extensionName[Container_FromActivity]);

		Error_Debug(Error_Format("Loading activity file \"%s\"\n", tempString));

		if (rootConf = Config_Load(tempString)){

			UCHAR tempString2[UTIL_DEFSTRINGLEN];
			
			sprintf(tempString, "%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, ACTIVITY_ACTIVITYSTRING);
			Error_Debug(Error_Format("Searching for \"%s\" in activity file\n", tempString));
			if (conf = Config_FindArray(rootConf, tempString)){
				
				cont = Container_Create(parent);
				cont->type = type;

				while(conf){

					LPUCHAR fileStr, sampleStr;
					REAL transCo;
					ULONG trigger;
					BOOL lws = FALSE, looping;
					LPUCHAR itemName = conf->itemName;
//					lpSound sample;

					if (('!' != *itemName) || !(mainGlobs.flags & MAIN_FLAG_REDUCEANIMATION)) {
						if ('!' == *itemName) itemName++; 

						sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, ACTIVITY_FILESTRING);

						if (fileStr = Config_GetTempStringValue(rootConf, tempString2)){
							sprintf(tempString, "%s\\%s", baseDir, fileStr);
							sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, ACTIVITY_TRANSCOSTRING);
	//						if (Config_FindItem(rootConf, tempString2)){
								transCo = Config_GetRealValue(rootConf, tempString2);
								sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, ACTIVITY_TRIGGERSTRING);
								trigger = Config_GetIntValue(rootConf, tempString2);
								sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, "LWSFILE");
								lws = 1==Config_GetBoolValue(rootConf, tempString2);
								sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, "LOOPING");
								if (0 == Config_GetBoolValue(rootConf, tempString2)) looping = FALSE;
								else looping = TRUE;

								// Get the activity sample...

								sprintf(tempString2, "%s%s%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, conf->dataString, CONFIG_SEPARATOR, ACTIVITY_SAMPLESTRING);
	//							if (
								sampleStr = Config_GetStringValue(rootConf, tempString2);
	//							){
	//								sprintf(tempString2, "%s\\%s", baseDir, fileStr);
	//								if (NULL == (sample = Sound_Load(tempString2))) Error_Fatal(TRUE, "Cannot load sample");
	//							} else sample = NULL;

								if (Container_AddActivity(cont, tempString, itemName, transCo, trigger, sampleStr, NULL, lws, looping)){

									if (!cont->typeData) Container_SetActivity(cont, itemName);

								} else Error_Fatal(TRUE, Error_Format("Unable to load Activity \"%s\" from \"%s\"", itemName, tempString));

	//						} else Error_Fatal(TRUE, Error_Format("Cannot get \"%s\" value from activity file", tempString2));
						} else Error_Fatal(TRUE, Error_Format("Unable to get item \"%s\" from activity file", tempString2));
					}

					conf = Config_GetNextItem(conf);
				}

			} else Error_Fatal(TRUE, Error_Format("Cannot Find Activity List %s", tempString));

			sprintf(tempString, "%s%s%s", containerGlobs.gameName, CONFIG_SEPARATOR, CONTAINER_SCALESTRING);
			scale = Config_GetRealValue(rootConf, tempString);
			if (0.0f != scale) cont->activityFrame->lpVtbl->AddScale(cont->activityFrame, D3DRMCOMBINE_REPLACE, scale, scale, scale);

			Config_Free(rootConf);
		} else Error_Warn(TRUE, Error_Format("Cannot Find File %s", tempString));

	} else if (Container_Frame == type){

		cont = Container_Create(parent);
		cont->type = type;
		// Just add it onto the activity frame...
		sprintf(tempString, "%s.%s", name, containerGlobs.extensionName[type]);
		if (Container_FrameLoad(tempString, cont->activityFrame));
		else Error_Warn(TRUE, Error_Format("Cannot Load File \"%s\".\n", tempString));

	} else if (Container_Mesh == type){

		LPDIRECT3DRMMESH mesh;
		LPVOID fdata;
		ULONG fsize;

		// Create a meshbuilder, retrieve the mesh object
		// then attach it to the activity frame...
		sprintf(tempString, "%s.%s", name, containerGlobs.extensionName[type]);
		if (fdata = File_LoadBinary(tempString, &fsize)){
			cont = Container_Create(parent);
			cont->type = type;
			if (mesh = Container_MeshLoad(fdata, fsize, tempString, cont->activityFrame, noTexture)){
				Container_SetTypeData(cont, NULL, NULL, mesh, NULL);
			} //else Error_Warn(TRUE, Error_Format("Cannot Load File \"%s\"", tempString));
			Mem_Free(fdata);
		}

	} else if (Container_Anim == type || Container_LWS == type){

//		LPDIRECT3DRMANIMATIONSET animSet;
		lpAnimClone animClone;
		ULONG frameCount;

		cont = Container_Create(parent);
		cont->type = Container_Anim;
		sprintf(tempString, "%s.%s", name, containerGlobs.extensionName[Container_Anim]);
		if (animClone = Container_LoadAnimSet(tempString, cont->activityFrame, &frameCount, (Container_LWS == type)?TRUE:FALSE, looping)){
			Container_Frame_SetAppData(cont->activityFrame, cont, animClone, name, &frameCount, NULL, NULL, NULL, NULL, NULL, NULL);
		} else {
			Error_Warn(TRUE, Error_Format("Cannot Load File \"%s\".\n", tempString));
			Container_Remove(cont);
			cont = NULL;
		}

	} else if (Container_LWO == type){

		lpMesh mesh;
		cont = Container_Create(parent);
		cont->type = type;

//		sprintf(tempString, "%s.lwo", name);
		//if( mesh = Lws_LoadMesh(NULL, name, cont->activityFrame, noTexture) )
		if( mesh = Mesh_Load(name, cont->activityFrame, noTexture) )
			Container_SetTypeData(cont, NULL, NULL, NULL, mesh);
		else
		{	Error_Warn(TRUE, Error_Format("Cannot Load File \"%s\".", tempString));
			Container_Remove(cont);
			cont = NULL;
		}
		
	} else if (Container_Invalid == type){

		Error_Fatal(TRUE, "Do not recognise container type");

	} else {

		Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", type));

	}

#ifdef _DEBUG
	if (cont){
		Container_Frame_FormatName(cont->masterFrame, "Master Frame (%s:%s)", name, typestr);
		Container_Frame_FormatName(cont->activityFrame, "Activity Frame (%s:%s)", name, typestr);
		Container_Frame_FormatName(cont->hiddenFrame, "Hidden Frame (%s:%s)", name, typestr);
	}
#endif // _DEBUG

	return cont;
}

__inline enum Container_Type Container_GetType(lpContainer cont) {

	return cont->type;
}

__inline BOOL Container_AddActivity(lpContainer cont, LPUCHAR fname, LPUCHAR actname, REAL transCo, ULONG trigger, LPUCHAR sample, lpAnimClone animClone, BOOL lws, BOOL looping){

	return Container_AddActivity2(cont, fname, actname, transCo, trigger, sample, animClone, lws, looping);
}

BOOL Container_IsCurrentActivity(lpContainer cont, LPUCHAR actname){

	LPDIRECT3DRMFRAME3 frame;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type) {
		if (frame = Container_Frame_Find(cont, actname, 0)) return TRUE;
	}

	return FALSE;
}

BOOL Container_SetActivity(lpContainer cont, LPUCHAR actname){

	LPDIRECT3DRMFRAME3 frame, currFrame;
	BOOL result = FALSE;
	LPUCHAR currAnimName, name, freeAddr = NULL;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type) {
		if (frame = Container_Frame_Find(cont, actname, 1)){
			if (NULL != cont->typeData) {
				if (NULL != cont->typeData->name) {
					currAnimName = cont->typeData->name;
					if (currFrame = Container_Frame_Find(cont, currAnimName, 0)){
						
						Container_Frame_SafeAddChild(cont->hiddenFrame, currFrame);
						
					}
					freeAddr = currAnimName;
				} else Error_Warn(TRUE, "container has no typedata name");
			}

			Container_Frame_SafeAddChild(cont->activityFrame, frame);
			name = Mem_Alloc(strlen(actname)+1);
			strcpy(name, actname);
			Container_SetTypeData(cont, name, NULL, NULL, NULL);

			result = TRUE;

			// Flag that the sample should be played on the next SetTime...
			cont->flags |= CONTAINER_FLAG_TRIGGERSAMPLE;

			if (freeAddr) Mem_Free(freeAddr);

		} else {
			result = FALSE;
			Error_Warn(!Container_Frame_Find(cont, actname, 0), Error_Format("Unknown activity (\"%s\") passed to Container_SetActivity()", actname));
		}

		// Notify the game that the activity has changed...

	#pragma message ( "Is the activity change callback required?" )
		if (cont->activityCallback) cont->activityCallback(cont, cont->activityCallbackData);
	}

	return result;
}

BOOL Container_Light_SetSpotPenumbra(lpContainer spotlight, REAL angle){

	Container_DebugCheckOK(spotlight);
	Error_Fatal(Container_Light != spotlight->type, "Container is not a light");
	
	if (spotlight->typeData->light->lpVtbl->SetPenumbra(spotlight->typeData->light, angle) == D3DRM_OK){
		return TRUE;
	} else return FALSE;
}

BOOL Container_Light_SetSpotUmbra(lpContainer spotlight, REAL angle){

	Container_DebugCheckOK(spotlight);

	Error_Fatal(Container_Light != spotlight->type, "Container is not a light");
	
	if (spotlight->typeData->light->lpVtbl->SetUmbra(spotlight->typeData->light, angle) == D3DRM_OK){
		return TRUE;
	} else return FALSE;
}

BOOL Container_Light_SetSpotRange(lpContainer spotlight, REAL dist){

	Container_DebugCheckOK(spotlight);
	Error_Fatal(Container_Light != spotlight->type, "Container is not a light");
		
	if (spotlight->typeData->light->lpVtbl->SetRange(spotlight->typeData->light, dist) == D3DRM_OK){
		return TRUE;
	} else return FALSE;
}

REAL Container_Light_GetSpotRange(lpContainer spotlight){

	Container_DebugCheckOK(spotlight);
	Error_Fatal(Container_Light != spotlight->type, "Container is not a light");

	return spotlight->typeData->light->lpVtbl->GetRange(spotlight->typeData->light);
}

REAL Container_Light_GetConstantAttenuation(lpContainer light){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	return light->typeData->light->lpVtbl->GetConstantAttenuation(light->typeData->light);
}

REAL Container_Light_GetLinearAttenuation(lpContainer light){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	return light->typeData->light->lpVtbl->GetLinearAttenuation(light->typeData->light);
}

REAL Container_Light_GetQuadraticAttenuation(lpContainer light){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	return light->typeData->light->lpVtbl->GetQuadraticAttenuation(light->typeData->light);
}

VOID Container_Light_SetConstantAttenuation(lpContainer light, REAL att){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	light->typeData->light->lpVtbl->SetConstantAttenuation(light->typeData->light, att);
}

VOID Container_Light_SetLinearAttenuation(lpContainer light, REAL att){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	light->typeData->light->lpVtbl->SetLinearAttenuation(light->typeData->light, att);
}

VOID Container_Light_SetQuadraticAttenuation(lpContainer light, REAL att){

	Container_DebugCheckOK(light);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	light->typeData->light->lpVtbl->SetQuadraticAttenuation(light->typeData->light, att);
}

VOID Container_Light_SetEnableContainer(lpContainer light, lpContainer enable){

	LPDIRECT3DRMFRAME enableFrame;
	Container_DebugCheckOK(light||enable);
	Error_Fatal(Container_Light != light->type, "Container is not a light");

	enable->masterFrame->lpVtbl->QueryInterface(enable->masterFrame, &IID_IDirect3DRMFrame, &enableFrame);
	light->typeData->light->lpVtbl->SetEnableFrame(light->typeData->light, enableFrame);
}

lpContainer Container_MakeLight(lpContainer parent, ULONG type, REAL r, REAL g, REAL b){

	lpContainer cont = Container_Create(parent);
	LPDIRECT3DRMLIGHT light;
	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	if (cont){

		cont->type = Container_Light;
		if (Container_Light_Ambient == type) Mesh_SetAmbientLight(r, g, b);

		if (lpD3DRM()->lpVtbl->CreateLightRGB(lpD3DRM(), type, r, g, b, &light) == D3DRM_OK){
			Container_NoteCreation(light);
			
			cont->activityFrame->lpVtbl->AddLight(cont->activityFrame, light);
			Container_SetTypeData(cont, NULL, light, NULL, NULL);
		} else Error_Fatal(TRUE, "Unable to create light");

#ifdef _DEBUG
	Container_Frame_FormatName(cont->masterFrame, "Light type #%d (%0.2f,%0.2f,%0.2f)", type, r, g, b);
#endif // _DEBUG
	
	}

	return cont;
}

lpContainer Container_MakeMesh2(lpContainer parent, ULONG type){

	lpContainer cont = Container_Create(parent);
	LPDIRECT3DRMMESH mesh;

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	if (cont) {
		cont->type = Container_Mesh;

		if (Container_MeshType_Transparent == type ||
			Container_MeshType_Immediate == type ||
			Container_MeshType_Additive == type ||
			Container_MeshType_Subtractive) {

			ULONG flags = MESH_FLAG_TRANSFORM_PARENTPOS;
			lpMesh transmesh;

			switch (type) {
			case Container_MeshType_Transparent:	flags |= MESH_FLAG_RENDER_ALPHATRANS;		break;
			case Container_MeshType_Additive:		flags |= MESH_FLAG_RENDER_ALPHASA1;			break;
			case Container_MeshType_Subtractive:	flags |= MESH_FLAG_RENDER_ALPHASA0;			break;
			}

			transmesh = Mesh_CreateOnFrame(cont->activityFrame, NULL, flags, NULL, Mesh_Type_Norm);
			Container_SetTypeData(cont, NULL, NULL, NULL, transmesh);

		} else {
			if (lpD3DRM()->lpVtbl->CreateMesh(lpD3DRM(), &mesh) == D3DRM_OK){
				Container_NoteCreation(mesh);

				cont->activityFrame->lpVtbl->AddVisual(cont->activityFrame, (struct IUnknown *) mesh);
				Container_SetTypeData(cont, NULL, NULL, mesh, NULL);

				if (Container_MeshType_SeperateMeshes == type) {

					lpContainer_MeshAppData appdata = Mem_Alloc(sizeof(Container_MeshAppData));
					appdata->listSize = CONTAINER_MESHGROUPBLOCKSIZE;
					appdata->usedCount = 0;
					appdata->meshList = Mem_Alloc(sizeof(LPDIRECT3DRMMESH) * appdata->listSize);
					appdata->groupZeroHidden = FALSE;
					appdata->firstAddGroup = TRUE;
					mesh->lpVtbl->SetAppData(mesh, (ULONG) appdata);

				} else mesh->lpVtbl->SetAppData(mesh, 0);
					
			} else Error_Fatal(TRUE, "Cannot create mesh object");
		}

#ifdef _DEBUG
		Container_Frame_FormatName(cont->masterFrame, "Mesh");
#endif // _DEBUG

	}

	return cont;
}

__inline LPVOID Container_GetMasterFrame(lpContainer cont) {

	return cont->masterFrame;
}

lpContainer Container_Clone(lpContainer orig){
	
	lpContainer cont = NULL, useOldClone = NULL;
	D3DRMMATRIX4D mat;
	ULONG loadRef = 0;
	
	Container_DebugCheckOK(orig);	
	
	if (Container_Mesh == orig->type) {
		
		// Special case - Don't allow cloning of separated group meshes...
		
		LPDIRECT3DRMMESH mesh = orig->typeData->mesh;
		Error_Fatal(!mesh, "TypeData missing on Object");
		if (mesh->lpVtbl->GetAppData(mesh)) Error_Fatal(TRUE, "Cannot clone separated mesh objects");
	}
	
	if (Container_FromActivity == orig->type || Container_Anim == orig->type){
		
		// If the object being cloned is a clone itself then use the original
		if (orig->cloneData) if (orig->cloneData->clonedFrom) orig = orig->cloneData->clonedFrom;
		
		if (orig->cloneData) {
			
			lpContainer testClone;
			ULONG loop;
			
			// If the original clone is unused then return that...
			if (!orig->cloneData->used) useOldClone = orig;
			else {
				
				// Find an unused clone...
				for (loop=0 ; loop<orig->cloneData->cloneCount ; loop++) {
					if (testClone = orig->cloneData->cloneTable[loop]){
						if (!testClone->cloneData->used) {
							useOldClone = testClone;
							break;
						}
					}
				}
			}
			
			if (useOldClone){
				useOldClone->cloneData->used = TRUE;
				cont = useOldClone;
				Container_SetParent(cont, Container_GetParent(orig));
				Container_SetAnimationTime(cont, 0.0f);
				Error_Debug(Error_Format("Reusing freed clone\n"));
			} else {
				cont = Container_Create(Container_GetParent(orig));
				loadRef = orig->cloneData->cloneCount++;
				orig->cloneData->cloneTable = Mem_ReAlloc(orig->cloneData->cloneTable, sizeof(lpContainer) * orig->cloneData->cloneCount);
				orig->cloneData->cloneTable[loadRef] = cont;
			}
		
		} else {
			cont = Container_Create(Container_GetParent(orig));
			orig->cloneData = Mem_Alloc(sizeof(Container_CloneData));
			orig->cloneData->cloneCount = 1;
			orig->cloneData->cloneTable = Mem_Alloc(sizeof(lpContainer));
			orig->cloneData->cloneTable[0] = cont;
			orig->cloneData->clonedFrom = NULL;
			orig->cloneData->cloneNumber = 0;
			orig->cloneData->used = TRUE;
			loadRef = 0;
		}
	} else cont = Container_Create(Container_GetParent(orig));
	
	{
		// Duplicate the activity frames transformation matrix
		LPDIRECT3DRMFRAME3 parent;
		orig->activityFrame->lpVtbl->GetParent(orig->activityFrame, &parent);
		orig->activityFrame->lpVtbl->GetTransform(orig->activityFrame, parent, mat);
		cont->activityFrame->lpVtbl->AddTransform(cont->activityFrame, D3DRMCOMBINE_REPLACE, mat);
		parent->lpVtbl->Release(parent);
	}
	
	if (useOldClone) return cont;
	
	// Copy across any data to the clone here..
	cont->type = orig->type;
	if (orig->typeData){
		cont->typeData = Mem_Alloc(sizeof(Container_TypeData));
		memcpy(cont->typeData, orig->typeData, sizeof(Container_TypeData));
		if (orig->typeData->name) {
			cont->typeData->name = Mem_Alloc(strlen(orig->typeData->name)+1);
			strcpy(cont->typeData->name, orig->typeData->name);
		}
	} else cont->typeData = NULL;
	
	if (Container_FromActivity == orig->type || Container_Anim == orig->type){
		
		// The new container obviously will have no cloneData.
		cont->cloneData = Mem_Alloc(sizeof(Container_CloneData));
		cont->cloneData->cloneTable = NULL;
		cont->cloneData->cloneCount = 0;
		cont->cloneData->clonedFrom = orig;
		cont->cloneData->cloneNumber = loadRef;
		cont->cloneData->used = TRUE;
		loadRef++;
	}
	
	if (Container_Mesh == cont->type) {
		
		LPDIRECT3DRMMESH mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "TypeData missing on Object");
		cont->activityFrame->lpVtbl->AddVisual(cont->activityFrame, (struct IUnknown *) mesh);
		mesh->lpVtbl->AddRef(mesh);
		
#ifdef _DEBUG
		Container_Frame_FormatName(cont->masterFrame, "Master Frame Mesh Clone (0x%0.8x)", orig->masterFrame);
#endif // _DEBUG
		
		
	} else if (Container_FromActivity == cont->type){
		
		ULONG loop, count;
		LPDIRECT3DRMFRAME3 *frameList;
		LPUCHAR *actNameList;
		LPUCHAR fname;
		REAL transCo;
		ULONG trigger;
		LPUCHAR sample;
		lpAnimClone origClone;//, newClone;
		
		count = Container_GetActivities(orig, NULL, NULL, NULL);
		frameList = Mem_Alloc(sizeof(LPDIRECT3DRMFRAME3) * count);
		actNameList = Mem_Alloc(sizeof(LPUCHAR) * count);
		
		Container_GetActivities(orig, frameList, NULL, actNameList);
		for (loop=0 ; loop<count ; loop++){
			fname = Container_Frame_GetAnimSetFileName(frameList[loop]);
			transCo = Container_Frame_GetTransCo(frameList[loop]);
			sample = Container_Frame_GetSample(frameList[loop]);
			origClone = Container_Frame_GetAnimClone(frameList[loop]);
			trigger = Container_Frame_GetTrigger(frameList[loop]);
			Container_Frame_SetAppData(frameList[loop], NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
//			Container_AddActivity2(cont, fname, &actNameList[loop][strlen(CONTAINER_ACTIVITYFRAMEPREFIX)+1], transCo, loadRef, sample);
			Container_AddActivity2(cont, fname, &actNameList[loop][strlen(CONTAINER_ACTIVITYFRAMEPREFIX)+1], transCo, trigger, sample, origClone, FALSE, FALSE);		// Last two parameters are ignored durng cloning...
			Mem_Free(actNameList[loop]);

			//UPDATE SOUND HERE TO ENSURE STREAMING BUFFER IS UPDATED PROPERLY
			//THIS IS DUE TO CLONING TAKING A LONG TIME
			//ONLY CHECK EVERY 25 ANIMATIONS BECAUSE STREAMING SOUND IS QUITE INTENSIVE?
			if( 0 == (loop % 25) )
				Sound3D_Update();
		}
		Mem_Free(frameList);
		Mem_Free(actNameList);
		
		if (cont->typeData) Container_SetActivity(cont, cont->typeData->name);
		
#ifdef _DEBUG
		Container_Frame_FormatName(cont->masterFrame, "Master Frame Clone (0x%0.8x)", orig->masterFrame);
		Container_Frame_FormatName(cont->activityFrame, "Activity Frame Clone (0x%0.8x)", orig->activityFrame);
		Container_Frame_FormatName(cont->hiddenFrame, "Hidden Frame Clone (0x%0.8x)", orig->hiddenFrame);
#endif // _DEBUG
		
	} else if (Container_Anim == cont->type){
		
//		LPDIRECT3DRMANIMATIONSET animSet;
		LPUCHAR fname;
		ULONG frameCount;
		lpAnimClone origClone, newClone;
		
		fname = Container_Frame_GetAnimSetFileName(orig->activityFrame);
		
//		if (animSet = Container_LoadAnimSet(fname, cont->activityFrame, loadRef, &frameCount)){
//			Container_Frame_SetAppData(cont->activityFrame, cont, animSet, fname, &frameCount, NULL, NULL, NULL, NULL);
//		} else Error_Fatal(TRUE, Error_Format("Cannot clone from reference %i of file \"%s\" (too few copies specified in xwave?).\n", loadRef, fname));

		origClone = Container_Frame_GetAnimClone(orig->activityFrame);
		newClone = AnimClone_Make(origClone, cont->activityFrame, &frameCount);
		Container_Frame_SetAppData(cont->activityFrame, cont, newClone, fname, &frameCount, NULL, NULL, NULL, NULL, NULL, NULL);

	} else if (Container_LWO == cont->type) {
		
		lpMesh mesh = cont->typeData->transMesh;
		Error_Fatal(!mesh, "TypeData missing on Object");
		cont->typeData->transMesh = Mesh_Clone( mesh, cont->activityFrame );
		
	} else {
		Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", orig->type));
	}
	
	return cont;
}

VOID Container_Hide2(lpContainer cont, BOOL hide) {

	if (hide) cont->flags |= CONTAINER_FLAG_HIDDEN2;
	else cont->flags &= ~CONTAINER_FLAG_HIDDEN2;
}

VOID Container_Hide(lpContainer cont, BOOL hide){

	// Move the activity frame onto the hidden frame (will not hide any children attached
	// to the master frame)...

	BOOL hidden;

	if (cont == NULL)		return;

	hidden = cont->flags & CONTAINER_FLAG_HIDDEN;
	Container_DebugCheckOK(cont);

//	if (Container_Mesh == cont->type) {
//		lpMesh transmesh;
//		Error_Fatal(NULL==cont->typeData, "Mesh has no typeData");
//		if (transmesh = cont->typeData->transMesh) {
//			Mesh_Hide(transmesh, hide);
//		}
//	} else {
		if (hide && !hidden) {
			Container_Frame_SafeAddChild(cont->hiddenFrame, cont->activityFrame);
			cont->flags |= CONTAINER_FLAG_HIDDEN;
		} else if (!hide && hidden) {
			Container_Frame_SafeAddChild(cont->masterFrame, cont->activityFrame);
			cont->flags &= ~CONTAINER_FLAG_HIDDEN;
		}
//	}
}

BOOL Container_IsHidden(lpContainer cont)
{
	if( cont->flags & CONTAINER_FLAG_HIDDEN )
		return TRUE;
	else
		return FALSE;

}

lpContainer Container_SearchTree(lpContainer root, LPUCHAR name, enum Container_SearchMode mode, LPULONG count){

	Container_SearchData search;

	Container_DebugCheckOK(root);

	search.string = name;
	search.stringLen = strlen(name);
	search.caseSensitive = FALSE;
	search.resultFrame = NULL;
	search.count = 0;
	search.mode = mode;

	if (count) search.matchNumber = *count;
	else search.matchNumber = 0;

#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	if (root->flags & CONTAINER_FLAG_HIDDEN) {
		Container_Frame_WalkTree(root->activityFrame, 0, Container_Frame_SearchCallback, &search);
	} else {
#endif // CONTAINER_MATCHHIDDENHIERARCHY

	Container_Frame_WalkTree(root->masterFrame, 0, Container_Frame_SearchCallback, &search);

#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	}
#endif // CONTAINER_MATCHHIDDENHIERARCHY

	if (Container_SearchMode_FirstMatch == mode || Container_SearchMode_NthMatch == mode) {
		if (search.resultFrame) return Container_Frame_GetContainer(search.resultFrame);
	} else if (Container_SearchMode_MatchCount == mode) *count = search.count;

	return NULL;
}

LPUCHAR Container_FormatPartName(lpContainer cont, LPUCHAR partname, LPULONG instance){		// Pass NULL as instance for any...

	// e.g. xf_????????_lphead_stationary_00_DDc_00 <- clone number (redundant (always zero))
	//         ^uid     ^part  ^filename  ^instance

	static UCHAR name[1024];
	UCHAR tempString[1024];
	LPDIRECT3DRMFRAME3 frame;
	LPUCHAR fname, s;
	lpAnimClone animClone;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type) {
		Error_Fatal(!cont->typeData, "Container has no typeData");
		frame = Container_Frame_Find(cont, cont->typeData->name, 0);
		Error_Fatal(NULL==frame, "Cannot locate current activities frame");
	} else if (Container_Anim == cont->type) {
		frame = cont->activityFrame;
	} else {
		Error_Fatal(TRUE, "Calling this function with a non-animation type Container serves no purpose");
	}

	animClone = Container_Frame_GetAnimClone(frame);
	// ^^^^^^ If animClone is NULL then you have probably misspelled the animation filename. Duh!

	if (AnimClone_IsLws(animClone)){
		if (instance) sprintf(name, "%s_%0.2i", partname, *instance);
		else sprintf(name, "%s_??", partname);
	} else {
		sprintf(tempString, "%s", Container_Frame_GetAnimSetFileName(frame));
		strlwr(tempString);
		for (fname=s=tempString ; '\0'!=*s ; s++) if ('\\' == *s) fname = s+1;
	//		sprintf(name, "xf_????_%s_%s_%0.2d_DDIclone_%0.2d", partname, fname, instance, Container_GetCloneNumber(cont));
	//		sprintf(name, "xf_????????_%s_%s_%0.2d_DDc_%0.2d", partname, fname, instance, Container_GetCloneNumber(cont));
		if (instance) sprintf(name, "xf_????????_%s_%s_%0.2d_DDc_00", partname, fname, *instance);
		else sprintf(name, "xf_????????_%s_%s_??_DDc_00", partname, fname);
	}

	return name;
}

VOID Container_SetActivityChangeCallback(lpContainer cont, VOID (*callback)(lpContainer cont, LPVOID data), LPVOID data){

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type){
		cont->activityCallback = callback;
		cont->activityCallbackData = data;
	} else Error_Warn(TRUE, "Pointless adding an activity change callback to a non-activity Container");
}

/*
BOOL Container_Pick(lpViewport vp, ULONG x, ULONG y, lpContainer *pickCont){

	LPDIRECT3DRMPICKEDARRAY pickarray;
	ULONG numpicks, loop;
	BOOL found = FALSE;

	Container_DebugCheckOK(pickCont);

	if (D3DRM_OK == vp->lpVP->lpVtbl->Pick(vp->lpVP, x, y, &pickarray)){

		LPDIRECT3DRMVISUAL visual;
		LPDIRECT3DRMFRAMEARRAY framearray;
		D3DRMPICKDESC pickdesc;

		numpicks = pickarray->lpVtbl->GetSize(pickarray);

		for (loop=0 ; loop<numpicks ; loop++){
			if (D3DRM_OK == pickarray->lpVtbl->GetPick(pickarray, loop, (IDirect3DRMVisual **) &visual, &framearray, &pickdesc)){

				ULONG framecount, sub;
				LPDIRECT3DRMFRAME frame1;
				LPDIRECT3DRMFRAME3 frame2;
				lpContainer cont;

				framecount = framearray->lpVtbl->GetSize(framearray);
				for (sub=0 ; sub<framecount ; sub++){
					framearray->lpVtbl->GetElement(framearray, sub, &frame1);
					frame1->lpVtbl->QueryInterface(frame1, &IID_IDirect3DRMFrame2, &frame2);

					if (cont = Container_SearchOwner(frame2)) {
						if (cont != containerGlobs.rootContainer){
							*pickCont = cont;
							found = TRUE;
							break;
						}
					}

					frame2->lpVtbl->Release(frame2);
					frame1->lpVtbl->Release(frame1);
				}

				visual->lpVtbl->Release(visual);
				framearray->lpVtbl->Release(framearray);

				if (found) break;
			}
		}

		pickarray->lpVtbl->Release(pickarray);

	}

	return found;
}
*/

VOID Container_SetUserData(lpContainer cont, LPVOID data){

	Container_DebugCheckOK(cont);

	cont->userData = data;
}

LPVOID Container_GetUserData(lpContainer cont){

	Container_DebugCheckOK(cont);

	return cont->userData;
}

VOID Container_SetBackgroundColour(REAL r, REAL g, REAL b) {
	
	ULONG colour = Container_GetRGBColour(r, g, b);	
	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneBackground(containerGlobs.rootContainer->masterFrame, colour);
}

VOID Container_EnableFog(BOOL on){

	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneFogEnable(containerGlobs.rootContainer->masterFrame, on);
	if (on) containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneBackground(containerGlobs.rootContainer->masterFrame, containerGlobs.fogColour);
	else containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneBackground(containerGlobs.rootContainer->masterFrame, 0);
}

VOID Container_SetFogColour(REAL r, REAL g, REAL b){

	containerGlobs.fogColour = Container_GetRGBColour(r, g, b);
	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneFogColor(containerGlobs.rootContainer->masterFrame, containerGlobs.fogColour);
}

VOID Container_GetFogColour(LPREAL r, LPREAL g, LPREAL b){

	*r = RGB_GETRED(containerGlobs.fogColour) / 255.0f;
	*g = RGB_GETGREEN(containerGlobs.fogColour) / 255.0f;
	*b = RGB_GETBLUE(containerGlobs.fogColour) / 255.0f;
}

VOID Container_SetFogMode(ULONG mode){

	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneFogMode(containerGlobs.rootContainer->masterFrame, mode);
	// 3Dfx requires table fog and software requires vertex fog...
	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneFogMethod(containerGlobs.rootContainer->masterFrame, Main_GetFogMethod());
}

VOID Container_SetFogParams(REAL start, REAL end, REAL density){

	containerGlobs.rootContainer->masterFrame->lpVtbl->SetSceneFogParams(containerGlobs.rootContainer->masterFrame, start, end, density);
}

/*VOID Container_EnableFog(BOOL on){
	Main_ChangeRenderState(D3DRENDERSTATE_FOGENABLE, on);
	//Main_ChangeRenderState(D3DRENDERSTATE_RANGEFOGENABLE, on);
}

VOID Container_SetFogColour(REAL r, REAL g, REAL b){
	containerGlobs.fogColour = Container_GetRGBColour(r, g, b);
	Main_ChangeRenderState(D3DRENDERSTATE_FOGCOLOR, containerGlobs.fogColour);
}

VOID Container_GetFogColour(LPREAL r, LPREAL g, LPREAL b){
	*r = RGB_GETRED(containerGlobs.fogColour) / 255.0f;
	*g = RGB_GETGREEN(containerGlobs.fogColour) / 255.0f;
	*b = RGB_GETBLUE(containerGlobs.fogColour) / 255.0f;
}

VOID Container_SetFogMode(ULONG mode){
	Main_ChangeRenderState(D3DRENDERSTATE_FOGVERTEXMODE, mode);
}

VOID Container_SetFogParams(REAL start, REAL end, REAL density){
	Main_ChangeRenderState(D3DRENDERSTATE_FOGSTART, (*((LPDWORD)(&start))));
	Main_ChangeRenderState(D3DRENDERSTATE_FOGEND, (*((LPDWORD)(&end))));
	Main_ChangeRenderState(D3DRENDERSTATE_FOGDENSITY, (*((LPDWORD)(&density))));
}*/

VOID Container_SetPerspectiveCorrection(lpContainer cont, BOOL on){

	ULONG count, loop;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type){

		// Set on every group of every mesh of every frame of every activity of the object...

		LPDIRECT3DRMFRAME3 *frameList;

		count = Container_GetActivities(cont, NULL, NULL, NULL);
		frameList = Mem_Alloc(sizeof(LPDIRECT3DRMFRAME3) * count);
		
		Container_GetActivities(cont, frameList, NULL, NULL);
		for (loop=0 ; loop<count ; loop++){
			Container_Frame_WalkTree(frameList[loop], 0, Container_SetPerspectiveCorrectionCallback, &on);
		}
		Mem_Free(frameList);

	} else if (Container_Mesh == cont->type) {

		// Set on every group of the mesh...

		count = Container_Mesh_GetGroupCount(cont);
		for (loop=0 ; loop<count ; loop++){
			Container_Mesh_SetPerspectiveCorrection(cont, loop, on);
		}
	}
}

static BOOL Container_SetPerspectiveCorrectionCallback(LPDIRECT3DRMFRAME3 frame, LPVOID data){

	// Only simple group meshes here...

	BOOL on = *((LPBOOL)data);
	ULONG visualCount, groupCount, loop, sub;
	LPDIRECT3DRMVISUAL *visualArray;
	LPDIRECT3DRMVISUAL visual;
	LPDIRECT3DRMMESHBUILDER2 builder;
	LPDIRECT3DRMMESH mesh;

	frame->lpVtbl->GetVisuals(frame, &visualCount, NULL);
	if (visualCount) {
//		visualArray = Mem_Alloc(sizeof(LPDIRECT3DRMVISUAL) * visualCount);
		Error_Fatal(visualCount>=CONTAINER_MAXVISUALS, "CONTAINER_MAXVISUALS too small");
		visualArray = containerGlobs.visualArray;
		frame->lpVtbl->GetVisuals(frame, &visualCount, (struct IUnknown **) visualArray);

		for (loop=0 ; loop<visualCount ; loop++) {

			visual = visualArray[loop];

			if (D3DRM_OK == visual->lpVtbl->QueryInterface(visual, &IID_IDirect3DRMMeshBuilder2, &builder)){
				builder->lpVtbl->SetPerspective(builder, on);
			} else if (D3DRM_OK == visual->lpVtbl->QueryInterface(visual, &IID_IDirect3DRMMesh, &mesh)){
				groupCount = mesh->lpVtbl->GetGroupCount(mesh);
				for (sub=0 ; sub<groupCount ; sub++){
					if (on) mesh->lpVtbl->SetGroupMapping(mesh, sub, D3DRMMAP_PERSPCORRECT);
					else mesh->lpVtbl->SetGroupMapping(mesh, sub, 0);
				}
			}
		}
		
//		Mem_Free(visualArray);
	}

	return FALSE;
}

/**********************************************************************************
 ******** Texture Functions...
 **********************************************************************************/

static BOOL Container_GetDecalColour(LPUCHAR fname, LPULONG colour) {

	LPUCHAR s, t;

	for (s=t=fname ; '\0'!=*t ; t++) if ('\\' == *t) s = t+1;
	if (('a' == *s || 'A' == *s) && isdigit(*(s+1)) && isdigit(*(s+2)) && isdigit(*(s+3)) && '_' == *(s+4)) {
		*colour = atoi(s+1);
		return TRUE;
	}
	return FALSE;
}

LPDIRECTDRAWSURFACE4 Container_LoadTextureSurface(LPUCHAR fname, BOOL managed, LPULONG width, LPULONG height, LPBOOL trans ){

	LPUCHAR fileData;
	ULONG size;
	D3DRMIMAGE image;
	LPDIRECTDRAWSURFACE4 surface = NULL;
	DDSURFACEDESC2 desc, descBak;
	LPDIRECTDRAWPALETTE palette;
	BOOL copy = FALSE;
	HRESULT result;
	
	if (fileData = File_LoadBinary(fname, &size)){
		BMP_Parse(fileData, size, &image);

		if (FALSE == image.rgb && 8 == image.depth){
			
			memset(&desc, 0, sizeof(desc));
			desc.dwSize = sizeof(DDSURFACEDESC2);
			desc.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT | DDSD_PIXELFORMAT;
			desc.dwWidth = image.width;
			desc.dwHeight = image.height;
			desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;

//#ifndef _GODS98_VIDEOMEMTEXTURES
	if (!(mainGlobs.flags & MAIN_FLAG_DONTMANAGETEXTURES)) {
			if (managed)
				desc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
			else
				desc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	} else {
//#else //_GODS98_VIDEOMEMTEXTURES
			desc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
	}
//#endif //_GODS98_VIDEOMEMTEXTURES

			// Find the prefered 8 bit palettized format...
			desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
			if (D3DRM_OK != lpDevice()->lpVtbl->FindPreferredTextureFormat(lpDevice(), DDBD_8, D3DRMFPTF_PALETTIZED, &desc.ddpfPixelFormat)) {

				memcpy(&descBak, &desc, sizeof(descBak));

				// If the card doesn't like this the create a standard 8 bit surface and then blit it to one it does like...
				memset(&desc.ddpfPixelFormat, 0, sizeof(desc.ddpfPixelFormat));

				desc.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
				desc.ddpfPixelFormat.dwFlags = DDPF_PALETTEINDEXED8|DDPF_RGB;
				desc.ddpfPixelFormat.dwRGBBitCount = 8;

				desc.ddsCaps.dwCaps &= ~DDSCAPS_TEXTURE;
				desc.ddsCaps.dwCaps &= ~DDSCAPS_VIDEOMEMORY;
				desc.ddsCaps.dwCaps2 &= ~DDSCAPS2_TEXTUREMANAGE;

				desc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
				desc.ddsCaps.dwCaps |= DDSCAPS_OFFSCREENPLAIN;

				copy = TRUE;
			}

			if (DD_OK == DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), &desc, &surface, NULL)) {

				memset(&desc, 0, sizeof(desc));
				desc.dwSize = sizeof(desc);

				if (DD_OK == (result = surface->lpVtbl->Lock(surface, NULL, &desc, DDLOCK_WAIT, NULL))) {
					SLONG y;
					LPUCHAR surfaceMem = desc.lpSurface, imageMem = image.buffer1;
					for (y=0 ; y<image.height ; y++){
						memcpy(surfaceMem, imageMem, image.bytes_per_line);
						surfaceMem += desc.lPitch;
						imageMem += image.bytes_per_line;
					}
					surface->lpVtbl->Unlock(surface, NULL);

					if (D3DRM_OK == DirectDraw()->lpVtbl->CreatePalette(DirectDraw(), DDPCAPS_INITIALIZE|DDPCAPS_8BIT|DDPCAPS_ALLOW256, (LPPALETTEENTRY) image.palette, &palette, NULL)){
						if (D3DRM_OK == surface->lpVtbl->SetPalette(surface, palette)){

							ULONG r, g, b;
							ULONG decalColour;

							if (copy) {		// Find the cards preferred texture format...

 								memset(&descBak.ddpfPixelFormat, 0, sizeof(descBak.ddpfPixelFormat));
								descBak.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
								if (D3DRM_OK == lpDevice()->lpVtbl->FindPreferredTextureFormat(lpDevice(), DDBD_16, 0, &descBak.ddpfPixelFormat)){

									// Replace 'surface' with one of a format that the card will accept...
									
									LPDIRECTDRAWSURFACE4 oldSurface = surface;
									if (D3DRM_OK == DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), &descBak, &surface, NULL)){

										if (16 == descBak.ddpfPixelFormat.dwRGBBitCount) DirectDraw_Blt8To16(surface, oldSurface, (LPPALETTEENTRY) image.palette);

										oldSurface->lpVtbl->Release(oldSurface);

									} else Error_Fatal(TRUE, "Error creating new texture surface");
								}
							}

							if( trans )
							{	
								if (Container_GetDecalColour(fname, &decalColour)){
									DDCOLORKEY ddck;

//									if(desc.ddpfPixelFormat.dwRGBBitCount > 8)
									if (copy) {
										r = image.palette[decalColour].red;
										g = image.palette[decalColour].green;
										b = image.palette[decalColour].blue;
										decalColour = DirectDraw_GetColour(surface, RGB_MAKE(r, g, b));
									}

									ddck.dwColorSpaceLowValue = ddck.dwColorSpaceHighValue = decalColour;
									surface->lpVtbl->SetColorKey(surface, DDCKEY_SRCBLT, &ddck);

									*trans = TRUE;
									
								} else *trans = FALSE;

							}

							if (width) *width = image.width;
							if (height) *height = image.height;

							surface->lpVtbl->AddRef(surface);
						}
						palette->lpVtbl->Release(palette);
					} else Error_Fatal(TRUE, "Cannot create Palette");
				} else {
#ifdef _DEBUG
					UCHAR error[128];

					sprintf(error, "Texture file %s : Cannot lock surface ", fname);

					switch (result) {
					case DDERR_INVALIDOBJECT:	strcat(error, "(DDERR_INVALIDOBJECT) ");	break;
					case DDERR_INVALIDPARAMS:	strcat(error, "(DDERR_INVALIDPARAMS) ");	break;
					case DDERR_OUTOFMEMORY:		strcat(error, "(DDERR_OUTOFMEMORY) ");		break;
					case DDERR_SURFACEBUSY:		strcat(error, "(DDERR_SURFACEBUSY) ");		break;
					case DDERR_SURFACELOST:		strcat(error, "(DDERR_SURFACELOST) ");		break;
					case DDERR_WASSTILLDRAWING:	strcat(error, "(DDERR_WASSTILLDRAWING) ");	break;
					case DDERR_LOCKEDSURFACES:	strcat(error, "(DDERR_LOCKEDSURFACES) ");	break;
					default:					CHKDD(result);								break;
					}

					{
						ULONG refCount;
						surface->lpVtbl->AddRef(surface);
						refCount = surface->lpVtbl->Release(surface);
						sprintf(&error[strlen(error)], "- Reference count == %i", refCount);
					}

					Error_Fatal(TRUE, error);
#endif // _DEBUG
		
				}
				if (0 == surface->lpVtbl->Release(surface)) surface = NULL;
			}
		} else Error_Warn(TRUE, Error_Format("Non 8bit/palettised texture %s", fname));

		BMP_Cleanup(&image);
		Mem_Free(fileData);
	}

	return surface;
}
/*
lpContainer_Texture Container_LoadTextureDDS(LPUCHAR fname, LPULONG width, LPULONG height){

	LPDIRECT3DRMTEXTURE3 texture = NULL;
	LPUCHAR fileData;
	ULONG size;
	LPDIRECTDRAWSURFACE4 surface;
	LPDIRECTDRAWSURFACE surface1;
	LPDDSURFACEDESC2 fileDesc;
	DDSURFACEDESC2 surfDesc;
	LPUCHAR surfaceMem;

	if (fileData = File_LoadBinary(fname, &size)){
		if (CONTAINER_DDSFILEMAGIC == ((LPULONG)fileData)[0]) {
			fileDesc = (LPDDSURFACEDESC2) &fileData[sizeof(ULONG)];
			surfaceMem = &fileData[sizeof(ULONG) + sizeof(DDSURFACEDESC2)];

			if (D3DRM_OK == DirectDraw()->lpVtbl->CreateSurface(DirectDraw(), fileDesc, &surface, NULL)){
				memset(&surfDesc, 0, sizeof(surfDesc));
				surfDesc.dwSize = sizeof(surfDesc);
				if (D3DRM_OK == surface->lpVtbl->Lock(surface, NULL, &surfDesc, DDLOCK_WAIT, 0)){
			        if(surfDesc.dwFlags & DDSD_LINEARSIZE) {
						memcpy(surfDesc.lpSurface, surfaceMem, surfDesc.dwLinearSize);
					} else {
						DWORD yp;
						BYTE* pbDest = (BYTE*) surfDesc.lpSurface;
						LONG dataBytesPerRow = surfDesc.dwWidth * surfDesc.ddpfPixelFormat.dwRGBBitCount / 8;
						for(yp=0; yp<surfDesc.dwHeight; yp++) {
							memcpy(pbDest, surfaceMem, dataBytesPerRow);
							pbDest += surfDesc.lPitch;
							surfaceMem += dataBytesPerRow;
						}
			        }
					surface->lpVtbl->Unlock(surface, NULL);

					if (D3DRM_OK == surface->lpVtbl->QueryInterface(surface, &IID_IDirectDrawSurface, &surface1)){
						if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateTextureFromSurface(lpD3DRM(), surface1, &texture)){

						}
						surface1->lpVtbl->Release(surface1);
					}
				}
			}
		}
		Mem_Free(fileData);
	}

	return (lpContainer_Texture) surface;
}
*/

lpContainer_Texture Container_LoadTexture2(LPUCHAR fname, BOOL immediate, LPULONG width, LPULONG height){

	LPDIRECT3DRMTEXTURE3 texture = NULL;

	LPUCHAR path = File_VerifyFilename(fname);
//	LPUCHAR s, t;
	lpContainer_Texture newText;
	ULONG decalColour;
//#ifndef CONTAINER_USEOWNTEXTURELOAD
	HRESULT r;
//#endif
	
	// This malloc() (not Mem_Alloc()) is deliberate...
	if (newText = malloc(sizeof(Container_Texture))){
		
//#ifdef CONTAINER_USEOWNTEXTURELOAD
		if (immediate) {
		
		LPDIRECTDRAWSURFACE surf1;
		LPDIRECTDRAWSURFACE4 surf;
		PALETTEENTRY entry;
		
		if (surf = Container_LoadTextureSurface(fname, immediate, width, height, NULL)){
			
			Error_Debug(Error_Format("Loaded texture %s\n", path));
			
			if (D3DRM_OK == surf->lpVtbl->QueryInterface(surf, &IID_IDirectDrawSurface, &surf1)){
				if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateTextureFromSurface(lpD3DRM(), surf1, &texture)){
					Container_NoteCreation(texture);
					surf1->lpVtbl->Release(surf1);
					
//					for (s=t=fname ; '\0'!=*t ; t++) if ('\\' == *t) s = t+1;
//					if ('a' == *s && isdigit(*(s+1)) && isdigit(*(s+2)) && isdigit(*(s+3)) && '_' == *(s+4)) {

					if (Container_GetDecalColour(fname, &decalColour)) {
						
						LPDIRECTDRAWPALETTE palette;
						surf->lpVtbl->GetPalette(surf, &palette);
						
						palette->lpVtbl->GetEntries(palette, 0, decalColour, 1, &entry);
						palette->lpVtbl->Release(palette);
						
						texture->lpVtbl->SetDecalTransparency(texture, TRUE);
						texture->lpVtbl->SetDecalTransparentColor(texture, RGB_MAKE(entry.peRed, entry.peGreen, entry.peBlue));
					}
					
					newText->texture = texture;
					newText->surface = surf;
					texture->lpVtbl->SetAppData(texture, (ULONG) newText);
					
					return newText;
				}
				surf1->lpVtbl->Release(surf1);
			}
			surf->lpVtbl->Release(surf);
		}

		} else {
//#else // CONTAINER_USEOWNTEXTURELOAD
		
		if (D3DRM_OK == ( r = lpD3DRM()->lpVtbl->LoadTexture(lpD3DRM(), path, &texture) ) ){
			LPD3DRMIMAGE image;
			ULONG r, g, b;//, i;
			Container_NoteCreation(texture);
			
			Error_Debug(Error_Format("Loaded texture %s\n", path));
			Error_LogLoad( TRUE, path );
			
			if (image = texture->lpVtbl->GetImage(texture)){	
//				for (s=t=fname ; '\0'!=*t ; t++) if ('\\' == *t) s = t+1;
//				if ('a' == *s && isdigit(*(s+1)) && isdigit(*(s+2)) && isdigit(*(s+3)) && '_' == *(s+4)) {

				if (Container_GetDecalColour(fname, &decalColour)) {

//					i = atoi(s+1);
					r = image->palette[decalColour].red;
					g = image->palette[decalColour].green;
					b = image->palette[decalColour].blue;
					texture->lpVtbl->SetDecalTransparency(texture, TRUE);
					texture->lpVtbl->SetDecalTransparentColor(texture, RGB_MAKE(r, g, b));
				}
				if (width) *width = image->width;
				if (height) *height = image->height;
			}
			
			newText->texture = texture;
			newText->surface = NULL;
			texture->lpVtbl->SetAppData(texture, (ULONG) newText);
			
			return newText;
			
		} else {
			
			if( r = D3DRMERR_FILENOTFOUND )
			{
				Error_Warn(TRUE, Error_Format("Invalid filename specified \"%s\"", path));
				Error_LogLoadError( TRUE, Error_Format("%d\t%s", Error_LoadError_InvalidFName, path));
			}
			else
			{
				Error_LogLoadError( TRUE, Error_Format("%d\t%s", Error_LoadError_RMTexture, path));
				Error_Warn(TRUE, Error_Format("Cannot open file %s", path));
			}
			
		}

		}
//#endif // CONTAINER_USEOWNTEXTURELOAD

		free(newText);
	}
	return NULL;
}


VOID Container_FreeTexture(lpContainer_Texture text){

	if (text) {		// Wrench out the textures because of the vast video memory sucking hole that is Mesh.c
		if (text->surface) while(text->surface->lpVtbl->Release(text->surface));
		if (text->texture) while(text->texture->lpVtbl->Release(text->texture));
			// This will call free(text) (Not Mem_Free()) if there are no more references to the texture...
	}
}

VOID Container_Texture_SetDecalTransparency(lpContainer_Texture text, BOOL on){

	if (text) text->texture->lpVtbl->SetDecalTransparency(text->texture, on);
}

/*
VOID Container_Texture_CyclePalette(lpContainer_Texture text, ULONG low, ULONG high) {

	LPD3DRMIMAGE image;
	D3DRMPALETTEENTRY swap;
	ULONG loop;

	Error_Fatal(low>=high||high>255, "Values out of range");

	if (image = text->texture->lpVtbl->GetImage(text->texture)){
		Error_Fatal(image->rgb, "Texture had no palette");

		swap = image->palette[high];
		for (loop=high ; loop>low ; loop--){
			image->palette[loop] = image->palette[loop-1];
		}
		image->palette[low] = swap;

	} else Error_Warn(TRUE, "Cannot get image from texture");

	text->texture->lpVtbl->Changed(text->texture, D3DRMTEXTURE_CHANGEDPALETTE, 0, NULL);
}
*/
/**********************************************************************************
 ******** Mesh Functions
 **********************************************************************************/

/*
ULONG Container_Mesh_AddGroup(lpContainer cont, ULONG vertexCount, ULONG faceCount, ULONG vPerFace, LPULONG faceData){

	ULONG groupID;
	LPDIRECT3DRMMESH mesh;

	Container_DebugCheckOK(cont);

	if (Container_Mesh == cont->type){

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		if (mesh->lpVtbl->AddGroup(mesh, vertexCount, faceCount, vPerFace, faceData, &groupID) == D3DRM_OK){

			return groupID;

		} else {
			Error_Fatal(TRUE, "Unable to AddGroup");
			return -1;
		}

	} else Error_Warn(TRUE, "Container_Mesh_AddGroup() called with non mesh object");
}*/

/*VOID Container_Mesh_HighZBias(lpContainer cont, ULONG groupID, BOOL on) {

	lpMesh mesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_GetGroupCount() called with non mesh object");
	Error_Fatal(!cont->typeData, "Container has no typeData");

	if (mesh = cont->typeData->transMesh) {
		if (on) mesh->groupList[groupID].renderFlags |= MESH_FLAG_HIGHZBIAS;
		else mesh->groupList[groupID].renderFlags &= ~MESH_FLAG_HIGHZBIAS;
	}
}*/

VOID Container_Mesh_Swap(lpContainer target, lpContainer origin, BOOL restore){

	// If not restoring then move any visuals on the container onto its hidden frame
	// and add the mesh from the origin container onto the target contianer...
	// Otherwise, restore the original visuals...

	LPDIRECT3DRMMESH mesh;
	LPDIRECT3DRMVISUAL *visuals;
	LPDIRECT3DRMVISUAL visual;
	LPDIRECT3DRMFRAME3 frame;
	ULONG count, loop;
	lpMesh transmesh;

	Container_DebugCheckOK(target);
	Error_Fatal(Container_Reference != target->type && Container_Mesh != target->type, "Container_Mesh_Swap() can only be used with a reference or mesh object as the 'target' container");
	Error_Fatal((target->flags & CONTAINER_FLAG_MESHSWAPPED) && !restore, "Container_Mesh_Swap() called without restoring previous swap");
	Error_Fatal(!(target->flags & CONTAINER_FLAG_MESHSWAPPED) && restore, "Container_Mesh_Swap() called with restore without a previous swap");
	
	if (Container_Reference == target->type) frame = target->masterFrame;
	else frame = target->activityFrame;

	if (!restore) {	// Move all the existing visuals onto the hidden frame...

		frame->lpVtbl->GetVisuals(frame, &count, NULL);
		if (count) {
//			visuals = Mem_Alloc(sizeof(LPDIRECT3DRMVISUAL) * count);
			Error_Fatal(count>=CONTAINER_MAXVISUALS, "CONTAINER_MAXVISUALS too small");
			visuals = containerGlobs.visualArray;
			frame->lpVtbl->GetVisuals(frame, &count, (struct IUnknown **) visuals);

	//		Error_Debug(Error_Format("Moving %i visuals to the hidden frame\n", count));
			for (loop=0 ; loop<count ; loop++){

				visual = visuals[loop];

				target->hiddenFrame->lpVtbl->AddVisual(target->hiddenFrame, (struct IUnknown *) visual);
				frame->lpVtbl->DeleteVisual(frame, (struct IUnknown *) visual);
			}
//			Mem_Free(visuals);
		}

/*		if (origin) {
			Error_Fatal(Container_Mesh != origin->type, "Container_Mesh_Swap() called with non-mesh object as 'origin' container");
			mesh = origin->typeData->mesh;
			Error_Fatal(!mesh, "Container has no mesh object");
			Error_Fatal(mesh->lpVtbl->GetAppData(mesh), "Not yet supported with separate mesh groups");

			// Add the origin's mesh as the new visual...
			frame->lpVtbl->AddVisual(frame, (struct IUnknown *) mesh);
		}
*/

		if (origin) {
//			Error_Fatal(Container_Mesh != origin->type, "Container_Mesh_Swap() called with non-mesh object as 'origin' container");
			if (NULL == (mesh = origin->typeData->mesh)) {
				transmesh = origin->typeData->transMesh;
				Error_Fatal(NULL==transmesh, "Container has no mesh object");
				frame->lpVtbl->AddVisual(frame, (struct IUnknown *) transmesh->uv);
			} else {
				Error_Fatal(mesh->lpVtbl->GetAppData(mesh), "Not yet supported with separate mesh groups");
				// Add the origin's mesh as the new visual...
				frame->lpVtbl->AddVisual(frame, (struct IUnknown *) mesh);
			}

		}


		target->flags |= CONTAINER_FLAG_MESHSWAPPED;

	} else {

		// Delete the visual (will still be used by the origin container) then restore the original visuals...

		frame->lpVtbl->GetVisuals(frame, &count, NULL);
		if (count) {
//			visuals = Mem_Alloc(sizeof(LPDIRECT3DRMVISUAL) * count);
			Error_Fatal(count>=CONTAINER_MAXVISUALS, "CONTAINER_MAXVISUALS too small");
			visuals = containerGlobs.visualArray;
			frame->lpVtbl->GetVisuals(frame, &count, (struct IUnknown **) visuals);

	//		Error_Debug(Error_Format("Deleting %i visuals...\n", count));
			for (loop=0 ; loop<count ; loop++){
				visual = visuals[loop];
				frame->lpVtbl->DeleteVisual(frame, (struct IUnknown *) visual);
			}
//			Mem_Free(visuals);
		}
		
		target->hiddenFrame->lpVtbl->GetVisuals(target->hiddenFrame, &count, NULL);
		if (count) {
//			visuals = Mem_Alloc(sizeof(LPDIRECT3DRMVISUAL) * count);
			Error_Fatal(count>=CONTAINER_MAXVISUALS, "CONTAINER_MAXVISUALS too small");
			visuals = containerGlobs.visualArray;
			target->hiddenFrame->lpVtbl->GetVisuals(target->hiddenFrame, &count, (struct IUnknown **) visuals);

//			Error_Debug(Error_Format("Restoring %i visuals from the hidden frame...\n", count));
			for (loop=0 ; loop<count ; loop++){
				visual = visuals[loop];
				frame->lpVtbl->AddVisual(frame, (struct IUnknown *) visual);
				target->hiddenFrame->lpVtbl->DeleteVisual(target->hiddenFrame, (struct IUnknown *) visual);
			}

//			Mem_Free(visuals);
		}

		target->flags &= ~CONTAINER_FLAG_MESHSWAPPED;

	}

}

ULONG Container_Mesh_AddGroup(lpContainer cont, ULONG vertexCount, ULONG faceCount, ULONG vPerFace, LPULONG faceData){

	ULONG groupID;
	LPDIRECT3DRMMESH mesh;
	lpContainer_MeshAppData appdata;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);

	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_AddGroup() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		groupID = Mesh_AddGroup(transmesh, vertexCount, faceCount, vPerFace, faceData);

		return groupID;

	} else {

		Error_Fatal(0 == vertexCount, "Don't know if that will work!!!");

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");
		
		if (appdata = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)){
			
			if (!appdata->firstAddGroup){
				
				// Make sure it doesn't crash...
				if (appdata->usedCount == appdata->listSize) return -1;
				
				// Using seperate meshes instead of groups...
				if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateMesh(lpD3DRM(), &mesh)){
					Container_NoteCreation(mesh);
					
					appdata->meshList[appdata->usedCount++] = mesh;
					cont->activityFrame->lpVtbl->AddVisual(cont->activityFrame, (struct IUnknown *) mesh);
					
					{
						// Set the msb if the group is added as a visual...
						ULONG value = appdata->usedCount;
						value |= 0x80000000;
						mesh->lpVtbl->SetAppData(mesh, value);
					}
					
					if (appdata->usedCount == appdata->listSize){
						LPDIRECT3DRMMESH *newList;
						if (newList = Mem_ReAlloc(appdata->meshList, sizeof(LPDIRECT3DRMMESH) * (appdata->listSize + CONTAINER_MESHGROUPBLOCKSIZE))){
							appdata->listSize += CONTAINER_MESHGROUPBLOCKSIZE;
							appdata->meshList = newList;
						}
					}
					
				} else {
					return -1;
					Error_Warn(TRUE, "Cannot add seperated mesh as group");
				}
			} else appdata->firstAddGroup = FALSE;
			
		}
		
		if (mesh->lpVtbl->AddGroup(mesh, vertexCount, faceCount, vPerFace, faceData, &groupID) == D3DRM_OK){
			
			if (appdata) return appdata->usedCount;
			else return groupID;
			
		} else {
			Error_Fatal(TRUE, "Unable to AddGroup");
			return -1;
		}
	}
	return -1;
}

ULONG Container_Mesh_GetGroupCount(lpContainer cont){

	LPDIRECT3DRMMESH mesh;
	lpContainer_MeshAppData appdata;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_GetGroupCount() called with non mesh object");
	Error_Fatal(!cont->typeData, "Container has no typeData");

	if (transmesh = cont->typeData->transMesh) {

		return Mesh_GetGroupCount(transmesh);

	} else {

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		if (appdata = (lpContainer_MeshAppData) cont->typeData->mesh->lpVtbl->GetAppData(cont->typeData->mesh)){
			return appdata->usedCount+1;
		} else {
			return cont->typeData->mesh->lpVtbl->GetGroupCount(cont->typeData->mesh);
		}
	}
}

VOID Container_Mesh_SetQuality(lpContainer cont, ULONG groupID, ULONG quality){

	ULONG d3drmqual;
	LPDIRECT3DRMMESH mesh;
	lpMesh transmesh;

	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_SetQuality() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Error_Warn(TRUE, "Not supported yet");

	} else {

		if (Container_Quality_Wireframe == quality) d3drmqual = D3DRMRENDER_WIREFRAME;
		if (Container_Quality_UnlitFlat == quality) d3drmqual = D3DRMRENDER_UNLITFLAT;
		if (Container_Quality_Flat == quality) d3drmqual = D3DRMRENDER_FLAT;
		if (Container_Quality_Gouraud == quality) d3drmqual = D3DRMRENDER_GOURAUD;

		Container_DebugCheckOK(cont);
		Error_Fatal(!cont->typeData, "Container has no typeData");

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);
		cont->typeData->mesh->lpVtbl->SetGroupQuality(mesh, groupID, d3drmqual);
	}
}

BOOL Container_Mesh_IsGroupHidden(lpContainer cont, ULONG group){

	BOOL hidden;
	LPDIRECT3DRMMESH mesh, groupmesh;
	lpContainer_MeshAppData appdata;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);	
	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_IsGroupHidden() called with non mesh object");
	Error_Fatal(!cont->typeData, "Container has no typeData");

	if (transmesh = cont->typeData->transMesh) {

		hidden = Mesh_IsGroupHidden(transmesh, group);

	} else {
		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, group);

		if (appdata = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)){
			
			if (0 != group) {
				groupmesh = appdata->meshList[group-1];
				hidden = !(groupmesh->lpVtbl->GetAppData(groupmesh) & 0x80000000);
			} else hidden = appdata->groupZeroHidden;

		} else Error_Fatal(TRUE, "Wrong mesh type");

	}
	return hidden;
}

VOID Container_Mesh_HideGroup(lpContainer cont, ULONG group, BOOL hide){

	BOOL hidden;
	LPDIRECT3DRMMESH mesh, groupmesh;
	LPDIRECT3DRMVISUAL visual;
	lpContainer_MeshAppData appdata;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);	
	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_HideGroup() called with non mesh object");
	Error_Fatal(!cont->typeData, "Container has no typeData");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_HideGroup(transmesh, group, hide);

	} else {

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, group);

		if (appdata = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)){
			
			if (0 != group) {
				groupmesh = appdata->meshList[group-1];
				hidden = !(groupmesh->lpVtbl->GetAppData(groupmesh) & 0x80000000);
				visual = (LPDIRECT3DRMVISUAL) groupmesh;
				group = 0;
			} else {
				groupmesh = NULL;
				hidden = appdata->groupZeroHidden;
				visual = (LPDIRECT3DRMVISUAL) mesh;
			}

			if (hide && !hidden) cont->activityFrame->lpVtbl->DeleteVisual(cont->activityFrame, (struct IUnknown *) visual);
			else if (!hide && hidden) cont->activityFrame->lpVtbl->AddVisual(cont->activityFrame, (struct IUnknown *) visual);

			if (groupmesh) {
				ULONG keep = groupmesh->lpVtbl->GetAppData(groupmesh) & 0x7fffffff;
				if (hide) groupmesh->lpVtbl->SetAppData(groupmesh, keep);
				else groupmesh->lpVtbl->SetAppData(groupmesh, keep | 0x80000000);
			}
			else appdata->groupZeroHidden = hide;
		}// else Error_Fatal(TRUE, "Wrong mesh type");
	}
}

static BOOL Container_Mesh_HandleSeperateMeshGroups(LPDIRECT3DRMMESH *mesh, LPULONG group){

	lpContainer_MeshAppData appdata;

	if (appdata = (lpContainer_MeshAppData) (*mesh)->lpVtbl->GetAppData(*mesh)){

		// Leave the default mesh if the group is zero and the (group-1)'th off the
		// list if not...
		
		if (0 != (*group)) *mesh = appdata->meshList[(*group)-1];
		(*group) = 0;

		return TRUE;
	}

	return FALSE;
}

BOOL Container_Mesh_GetGroup(lpContainer cont, ULONG groupID, LPULONG vertexCount, LPULONG faceCount, LPULONG vPerFace, LPULONG faceDataSize, LPULONG faceData){

	LPDIRECT3DRMMESH mesh;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	
	Error_Fatal(Container_Mesh != cont->type&&Container_LWO!=cont->type, "Container_Mesh_GetGroup() called with non mesh object");
	Error_Fatal(!cont->typeData, "Container has no typeData");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_GetGroup(transmesh, groupID, vertexCount, faceCount, vPerFace, faceDataSize, faceData);
		return TRUE;

	} else {
		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		if (mesh->lpVtbl->GetGroup(mesh, groupID, vertexCount, faceCount, vPerFace, faceDataSize, faceData) == D3DRM_OK){

			return TRUE;

		} else {
			Error_Warn(TRUE, "Unable to GetGroup()");
			return FALSE;
		}
	}
}

ULONG Container_Mesh_GetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D retArray){

	LPDIRECT3DRMMESH mesh;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);

	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_GetVertices() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_GetVertices(transmesh, groupID, index, count, retArray);

	} else {

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		if (mesh->lpVtbl->GetVertices(mesh, groupID, index, count, (LPD3DRMVERTEX) retArray) == D3DRM_OK){

		} else {
			Error_Fatal(TRUE, "Unable to GetVertices");
			return CONTAINER_ULONG_NULL;
		}
	}

	return 0;
}

ULONG Container_Mesh_SetVertices(lpContainer cont, ULONG groupID, ULONG index, ULONG count, LPVERTEX3D values){

	LPDIRECT3DRMMESH mesh;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);

	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_SetVertices() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_SetVertices(transmesh, groupID, index, count, values);

	} else {

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		if (D3DRM_OK == mesh->lpVtbl->SetVertices(mesh, groupID, index, count, (LPD3DRMVERTEX) values)){

		} else {
			Error_Fatal(TRUE, "Unable to SetVertices");
			return CONTAINER_ULONG_NULL;
		}
	}

	return 0;
}

VOID Container_Mesh_SetTexture(lpContainer cont, ULONG groupID, lpContainer_Texture itext){

	LPDIRECT3DRMTEXTURE3 texture;
	LPDIRECT3DRMMESH mesh;
	LPDIRECT3DRMTEXTURE text1;
	HRESULT r;
	lpMesh transmesh;

	if (itext) texture = itext->texture;
	else texture = NULL;

	Container_DebugCheckOK(cont);

	Error_Fatal(Container_Mesh != cont->type && Container_LWO != cont->type, "Container_Mesh_SetTexture() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Error_Fatal(itext&&NULL!=itext->surface&&NULL==itext->texture, "Texture is required to be created by Mesh_LoadTexture()");
		Mesh_SetGroupTexture(transmesh, groupID, itext);

	} else {
		
		Container_Mesh_DebugCheckOK(cont, groupID);
		
		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");
		
		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);
		
		if (texture) {
			r = texture->lpVtbl->QueryInterface(texture, &IID_IDirect3DRMTexture, &text1);
			Error_Fatal(r, "Unable to query texture1");
		} else text1 = NULL;
		
		if (D3DRM_OK == mesh->lpVtbl->SetGroupTexture(mesh, groupID, text1)){
#ifndef CONTAINER_DISABLEFRAMESETTINGS
			cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMMESH);
#endif // CONTAINER_DISABLEFRAMESETTINGS
		} else Error_Fatal(TRUE, "Unable to SetGroupTexture");
		
		if (text1) text1->lpVtbl->Release(text1);
	}
}

lpContainer_Texture Container_Mesh_GetTexture(lpContainer cont, ULONG groupID){

	LPDIRECT3DRMTEXTURE texture;
	LPDIRECT3DRMMESH mesh;
	lpContainer_Texture text = NULL;

	Container_DebugCheckOK(cont);

	Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_GetTexture() called with non mesh object");

	mesh = cont->typeData->mesh;
	Error_Fatal(!mesh, "Container has no mesh object");

	Container_Mesh_DebugCheckOK(cont, groupID);

	Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

	if (D3DRM_OK == mesh->lpVtbl->GetGroupTexture(mesh, groupID, &texture)){
		if (texture) {
			text = (lpContainer_Texture) texture->lpVtbl->GetAppData(texture);
			texture->lpVtbl->Release(texture);
			Error_Fatal(NULL==text, "Texture is not part of a Container_Texture");
		}
	} else Error_Fatal(TRUE, "Unable to GetGroupTexture");
		
	return text;
}

VOID Container_Mesh_SetPerspectiveCorrection(lpContainer cont, ULONG groupID, BOOL on){

	LPDIRECT3DRMMESH mesh;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh != cont->type&&Container_LWO!=cont->type, "Container_Mesh_SetPerspectiveCorrection() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Error_Warn(TRUE, "Not yet implemented for immediate mode meshes");

	} else {

		mesh = cont->typeData->mesh;
		
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		if (on) mesh->lpVtbl->SetGroupMapping(mesh, groupID, D3DRMMAP_PERSPCORRECT);
		else mesh->lpVtbl->SetGroupMapping(mesh, groupID, 0);
	}
}

VOID Container_Mesh_SetMaterial(lpContainer cont, ULONG groupID, lpMaterial material){

	LPDIRECT3DRMMESH mesh;
	LPDIRECT3DRMMATERIAL2 mat2 = (LPDIRECT3DRMMATERIAL2) material;
	LPDIRECT3DRMMATERIAL mat;

	if (D3DRM_OK == mat2->lpVtbl->QueryInterface(mat2, &IID_IDirect3DRMMaterial, &mat)){

		Container_DebugCheckOK(cont);
		Error_Fatal(Container_Mesh != cont->type, "Container_Mesh_SetMaterial() called with non mesh object");

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);
		mesh->lpVtbl->SetGroupMaterial(mesh, groupID, mat);

		mat->lpVtbl->Release(mat);

	} else Error_Fatal(TRUE, "Cannot get material");
}

/*
ULONG Container_Mesh_CreateTexture(lpContainer cont, ULONG groupID, lpImage image, LPAREA2D area){

	LPDIRECT3DRMMESH mesh;
	LPDIRECT3DRMTEXTURE3 texture;
	ULONG status;

	Error_Warn(TRUE, "Redundant code Container_Mesh_CreateTexture()");

	Container_DebugCheckOK(cont&&image);

	if (Container_Mesh == cont->type){

		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		if (texture = Image_CreateTexture(image, area, &status)){
			if (D3DRM_OK == mesh->lpVtbl->SetGroupTexture(mesh, groupID, (LPDIRECT3DRMTEXTURE) texture)){
				
				texture->lpVtbl->Release(texture);
				return TRUE;

			} else Error_Fatal(TRUE, "Unable to SetGroupTexture");
			texture->lpVtbl->Release(texture);
		}
	} else Error_Warn(TRUE, "Container_Mesh_CreateTexture() called with non mesh object");
	
	return FALSE;
}

BOOL Container_Mesh_CopyTexture(lpContainer to, ULONG toGroupID, lpContainer from, ULONG fromGroupID){

	LPDIRECT3DRMMESH mesh;
	LPDIRECT3DRMTEXTURE texture;

	Container_DebugCheckOK(to&&from);

	if (Container_Mesh == from->type){

		mesh = from->typeData->mesh;
		Error_Fatal(!mesh, "'From' Container has no mesh object");
		
		if (D3DRM_OK == mesh->lpVtbl->GetGroupTexture(mesh, fromGroupID, &texture)){
			mesh = to->typeData->mesh;
			Error_Fatal(!mesh, "'To' Container has no mesh object");
			
			if (D3DRM_OK == mesh->lpVtbl->SetGroupTexture(mesh, toGroupID, texture)){

				return TRUE;

			} else Error_Fatal(TRUE, "Unable to SetGroupTexture");
		} else Error_Fatal(TRUE, "Unable to GetGroupTexture");
	} else Error_Warn(TRUE, "Container_Mesh_CreateTexture() called with non mesh object");

	return FALSE;
}
*/

BOOL Container_Mesh_Scale(lpContainer cont, REAL x, REAL y, REAL z){

	lpContainer_MeshAppData appdata;
	ULONG loop;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_Scale() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_Scale(transmesh, x, y, z);
		
	} else {
		
		LPDIRECT3DRMMESH mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "'From' Container has no mesh object");
		
		mesh->lpVtbl->Scale(mesh, x, y, z);
		
		if (appdata = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)) {
			// Scale all the other meshes...
			for (loop=0 ; loop<appdata->usedCount ; loop++){
				mesh = appdata->meshList[loop];
				mesh->lpVtbl->Scale(mesh, x, y, z);
			}
		}
	}
		
	return FALSE;
}
	
BOOL Container_Mesh_GetBox(lpContainer cont, LPBOX3D box){

	LPDIRECT3DRMMESH mesh = cont->typeData->mesh;
	lpContainer_MeshAppData appdata;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type, "Container_Mesh_GetBox() called with non mesh object");
	Error_Fatal(!mesh, "'From' Container has no mesh object");
	mesh->lpVtbl->GetBox(mesh, (LPD3DRMBOX) box);

	if (appdata = (lpContainer_MeshAppData) mesh->lpVtbl->GetAppData(mesh)) {

		D3DRMBOX subbox;
		ULONG loop;

		// Find if any of the others span outside this box...
		for (loop=0 ; loop<appdata->usedCount ; loop++){
			mesh = appdata->meshList[loop];
			mesh->lpVtbl->GetBox(mesh, &subbox);
			if (subbox.min.x < box->min.x) box->min.x = subbox.min.x;
			if (subbox.min.y < box->min.y) box->min.y = subbox.min.y;
			if (subbox.min.z < box->min.z) box->min.z = subbox.min.z;
			if (subbox.max.x > box->max.x) box->max.x = subbox.max.x;
			if (subbox.max.y > box->max.y) box->max.y = subbox.max.y;
			if (subbox.max.z > box->max.z) box->max.z = subbox.max.z;
		}
	}

	return FALSE;
}

VOID Container_Mesh_SetEmissive(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b){

#ifndef CONTAINER_DISABLEFRAMESETTINGS
	LPDIRECT3DRMMATERIAL2 material2;
	LPDIRECT3DRMMATERIAL material;
	LPDIRECT3DRMMESH mesh;
#endif // CONTAINER_DISABLEFRAMESETTINGS
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_SetEmissive() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_SetGroupEmissive(transmesh, groupID, r, g, b);
			
	} else {
#ifndef CONTAINER_DISABLEFRAMESETTINGS
		mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		mesh->lpVtbl->GetGroupMaterial(mesh, groupID, &material);
		if (NULL == material) {
			lpD3DRM()->lpVtbl->CreateMaterial(lpD3DRM(), 0.0f, &material2);
			Container_NoteCreation(material);
			material2->lpVtbl->QueryInterface(material2, &IID_IDirect3DRMMaterial, &material);
			material2->lpVtbl->Release(material2);
			mesh->lpVtbl->SetGroupMaterial(mesh, groupID, material);
		}

		material->lpVtbl->SetEmissive(material, r, g, b);
		material->lpVtbl->Release(material);
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMMESH);
#endif // CONTAINER_DISABLEFRAMESETTINGS
	}
}

VOID Container_Mesh_SetColourAlpha(lpContainer cont, ULONG groupID, REAL r, REAL g, REAL b, REAL a){

	D3DCOLOR colour;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type&&Container_LWO!=cont->type, "Container_Mesh_SetColourAlpha() called with non mesh object");

	colour = Container_GetRGBAColour(r, g, b, a);

	if (transmesh = cont->typeData->transMesh) {

		Mesh_SetGroupDiffuse(transmesh, groupID, r, g, b);
		Mesh_SetGroupAlpha(transmesh, groupID, a);

	} else {

#ifndef CONTAINER_DISABLEFRAMESETTINGS

		LPDIRECT3DRMMESH mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);

		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);

		mesh->lpVtbl->SetGroupColor(mesh, groupID, colour);
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMMESH);

#endif // CONTAINER_DISABLEFRAMESETTINGS

	}
}

VOID Container_Mesh_GetColourAlpha(lpContainer cont, ULONG groupID, LPREAL r, LPREAL g, LPREAL b, LPREAL a){

	D3DCOLOR colour;
	lpMesh transmesh;

	Container_DebugCheckOK(cont);
	Error_Fatal(Container_Mesh!=cont->type, "Container_Mesh_GetColourAlpha() called with non mesh object");

	if (transmesh = cont->typeData->transMesh) {

		Mesh_GetGroupDiffuse(transmesh, groupID, r, g, b);
		if (NULL != a) Mesh_GetGroupAlpha(transmesh, groupID, a);

	} else {

		LPDIRECT3DRMMESH mesh = cont->typeData->mesh;
		Error_Fatal(!mesh, "Container has no mesh object");

		Container_Mesh_DebugCheckOK(cont, groupID);
		Container_Mesh_HandleSeperateMeshGroups(&mesh, &groupID);
		colour = mesh->lpVtbl->GetGroupColor(mesh, groupID);

		*r = RGB_GETRED(colour) / 255.0f;
		*g = RGB_GETGREEN(colour) / 255.0f;
		*b = RGB_GETBLUE(colour) / 255.0f;
		if (NULL != a) *a = RGBA_GETALPHA(colour) / 255.0f;
	}
}

/**********************************************************************************
 ******** 'Almost' Direct Mapping of D3D Functions...
 **********************************************************************************/

VOID Container_Transform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src){

 	Container_DebugCheckOK(cont);

	cont->masterFrame->lpVtbl->Transform(cont->masterFrame, (LPD3DVECTOR) dest, (LPD3DVECTOR) src);
}

VOID Container_InverseTransform(lpContainer cont, LPVECTOR3D dest, LPVECTOR3D src){

 	Container_DebugCheckOK(cont);

	cont->masterFrame->lpVtbl->InverseTransform(cont->masterFrame, (LPD3DVECTOR) dest, (LPD3DVECTOR) src);
}
/*
VOID Container_GetBox(lpContainer cont, LPBOX3D box){

	Container_DebugCheckOK(cont);

	if (cont->typeData){
		if (Container_Mesh == cont->type){
			cont->typeData->mesh->lpVtbl->GetBox(cont->typeData->mesh, (LPD3DRMBOX) box);
		} else Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", cont->type));
	} else Error_Fatal(TRUE, "Container has no typeData");
}
*/

VOID Container_SetColourAlpha(lpContainer cont, REAL r, REAL g, REAL b, REAL a){

	D3DCOLOR colour;

	Container_DebugCheckOK(cont);
	Error_Fatal(!cont->typeData, "Container has no typeData");
	
	colour = Container_GetRGBAColour(r, g, b, a);

	if (Container_Light == cont->type){
		Error_Fatal(!cont->typeData->light, "typedata has no light");
		cont->typeData->light->lpVtbl->SetColor(cont->typeData->light, colour);
		if (D3DRMLIGHT_AMBIENT == cont->typeData->light->lpVtbl->GetType(cont->typeData->light)) Mesh_SetAmbientLight(r, g, b);

	} else {
#ifndef CONTAINER_DISABLEFRAMESETTINGS
		cont->activityFrame->lpVtbl->SetColor(cont->activityFrame, colour);
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMFRAME);
#endif // CONTAINER_DISABLEFRAMESETTINGS
	}

	/*
	if (Container_Light == cont->type){
		Error_Fatal(!cont->typeData->light, "typedata has no light");
		cont->typeData->light->lpVtbl->SetColor(cont->typeData->light, colour);
	} else if (Container_Mesh == cont->type){
//		Error_Fatal(!cont->typeData->mesh, "typedata has no mesh");
		cont->activityFrame->lpVtbl->SetColor(cont->activityFrame, colour);
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMFRAME);
//		cont->typeData->mesh->lpVtbl->SetGroupColor(cont->typeData->mesh, groupID, colour);
//	} else if (Container_Mesh == cont->type){
//		Error_Fatal(!cont->typeData->meshbuilder, "typedata has no meshbuilder");
//		cont->typeData->meshbuilder->lpVtbl->SetColor(cont->typeData->meshbuilder, colour);
//	} else if (Container_FromActivity == cont->type){
//		Error_Fatal(!cont->typeData->name, "typedata has no activity name");
	} else Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", cont->type));*/
}

VOID Container_GetColourAlpha(lpContainer cont, LPREAL r, LPREAL g, LPREAL b, LPREAL a){

	D3DCOLOR colour;

	Container_DebugCheckOK(cont);
	Error_Fatal(!cont->typeData, "Container has no typeData");
	
	if (Container_Light == cont->type){
		Error_Fatal(!cont->typeData->light, "typedata has no light");
		colour = cont->typeData->light->lpVtbl->GetColor(cont->typeData->light);
	} else if (Container_Mesh == cont->type){
//		Error_Fatal(!cont->typeData->mesh, "typedata has no mesh");
//		colour = cont->typeData->mesh->lpVtbl->GetGroupColor(cont->typeData->mesh, groupID);
		colour = cont->activityFrame->lpVtbl->GetColor(cont->activityFrame);
//	} else if (Container_Mesh == cont->type){
//		Error_Fatal(!cont->typeData->meshbuilder, "typedata has no meshbuilder");
//		colour = cont->typeData->meshbuilder->lpVtbl->GetColor(cont->typeData->meshbuilder);
	} else Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", cont->type));

	*r = RGB_GETRED(colour) / 255.0f;
	*g = RGB_GETGREEN(colour) / 255.0f;
	*b = RGB_GETBLUE(colour) / 255.0f;

	if (NULL != a) *a = RGBA_GETALPHA(colour) / 255.0f;
}

VOID Container_SetEmissive(lpContainer cont, REAL r, REAL g, REAL b){

#ifndef CONTAINER_DISABLEFRAMESETTINGS
	LPDIRECT3DRMMATERIAL2 material;
#endif // CONTAINER_DISABLEFRAMESETTINGS

	Container_DebugCheckOK(cont);
	Error_Fatal(!cont->typeData, "Container has no typeData");

//	if (Container_Mesh == cont->type){
#ifndef CONTAINER_DISABLEFRAMESETTINGS
		cont->activityFrame->lpVtbl->GetMaterial(cont->activityFrame, &material);
		if (NULL == material) {
			lpD3DRM()->lpVtbl->CreateMaterial(lpD3DRM(), 0.0f, &material);
			cont->activityFrame->lpVtbl->SetMaterial(cont->activityFrame, material);
		}

		material->lpVtbl->SetEmissive(material, r, g, b);
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMFRAME);
#endif // CONTAINER_DISABLEFRAMESETTINGS

		//	} else Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", cont->type));
}

VOID Container_SetTexture(lpContainer cont, lpContainer_Texture itext){

	LPDIRECT3DRMTEXTURE3 texture;
	
	if (itext) texture = itext->texture;
	else texture = NULL;

	Container_DebugCheckOK(cont);

#ifndef CONTAINER_DISABLEFRAMESETTINGS
	if (D3DRM_OK == cont->activityFrame->lpVtbl->SetTexture(cont->activityFrame, texture)){
		cont->activityFrame->lpVtbl->SetMaterialMode(cont->activityFrame, D3DRMMATERIAL_FROMFRAME);
	} else Error_Fatal(TRUE, "Unable to SetGroupTexture");
#endif // CONTAINER_DISABLEFRAMESETTINGS

}

lpContainer_Texture Container_GetTexture(lpContainer cont){

	LPDIRECT3DRMTEXTURE3 texture;

	Container_DebugCheckOK(cont);

	if (D3DRM_OK == cont->activityFrame->lpVtbl->GetTexture(cont->activityFrame, &texture)){

		return (lpContainer_Texture) texture;

	} else Error_Fatal(TRUE, "Unable to GetGroupTexture");

	return NULL;
}

REAL Container_MoveAnimation(lpContainer cont, REAL delta){

	REAL time = Container_GetAnimationTime(cont);
	return Container_SetAnimationTime(cont, time + delta);
}

REAL Container_SetAnimationTime(lpContainer cont, REAL time){

	LPDIRECT3DRMFRAME3 frame;
//	LPDIRECT3DRMANIMATIONSET animSet = NULL;
	LPUCHAR currAnimName;
	ULONG frameCount;
	lpAnimClone animClone = NULL;
	REAL overrun = 0.0f;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type){
		Error_Fatal(!cont->typeData, "Container has no typeData");

		currAnimName = cont->typeData->name;
		if (frame = Container_Frame_Find(cont, currAnimName, 0)){
//			animSet = Container_Frame_GetAnimSet(frame);
			animClone = Container_Frame_GetAnimClone(frame);
	
/*			if (cont->flags & CONTAINER_FLAG_TRIGGERSAMPLE){
#pragma message ( "Trigger the sample half way through if the SetTime is half way in" )
				// Trigger the sample... (The sample may be longer than the animset!)
				lpSound sound;
				if (sound = Container_Frame_GetSample(frame)){
					Sound_Play(sound, Sound_Once);
				}
			}*/

			if (cont->flags & CONTAINER_FLAG_TRIGGERSAMPLE){
				LPUCHAR sound;
				if (sound = Container_Frame_GetSample(frame)){
					if (containerGlobs.soundTriggerCallback && (containerGlobs.flags & CONTAINER_FLAG_TRIGGERENABLED)) containerGlobs.soundTriggerCallback(sound, cont, containerGlobs.soundTriggerData);
				}
				cont->flags &= ~CONTAINER_FLAG_TRIGGERSAMPLE;
			}

		} else Error_Warn(TRUE, "Couldn't find frame (thus AnimationSet) to SetTime() on");

	} else if (Container_Anim == cont->type) {

//		animSet = Container_Frame_GetAnimSet(cont->activityFrame);
		animClone = Container_Frame_GetAnimClone(cont->activityFrame);
		frame = cont->activityFrame;

	}// else Error_Fatal(TRUE, "Container_SetTime() called with non-animation type Object");

	if (animClone) {

		BOOL skipSetTime = (cont->flags & CONTAINER_FLAG_HIDDEN);
		REAL oldTime = Container_GetAnimationTime(cont);

		// If the container is hidden then don't bother updating the animation
		// unless the animation has ended...

		frameCount = Container_Frame_GetFrameCount(frame);
		Container_Frame_SetAppData(frame, NULL, NULL, NULL, NULL, NULL, &time, NULL, NULL, NULL, NULL);
		if (frameCount){
			frameCount--;
			if (time > frameCount) {
				overrun = (time - frameCount);
				skipSetTime = FALSE;
			}
		}

		if (FALSE == skipSetTime) {
			REAL triggerFrame = (REAL) Container_Frame_GetTrigger(frame);
#pragma message ( "Not restoring the time on original animation set" )
			if (1 != frameCount) {
				AnimClone_SetTime(animClone, time, NULL);//&oldTime);
				if (containerGlobs.triggerFrameCallback && triggerFrame) {
					if (oldTime < triggerFrame && time >= triggerFrame) {
						containerGlobs.triggerFrameCallback(cont, containerGlobs.triggerFrameData);
					}
				}
			}
		} else {
			cont->flags |= CONTAINER_FLAG_ANIMATIONSKIPPED;
		}

	}

	return overrun;
}

VOID Container_ForceAnimationUpdate(lpContainer cont) {

	if (cont->flags & CONTAINER_FLAG_ANIMATIONSKIPPED) {

		lpAnimClone animClone;
		LPDIRECT3DRMFRAME3 frame;
		REAL time;

		if (Container_FromActivity == cont->type){
			Error_Fatal(!cont->typeData, "Container has no typeData");
			if (frame = Container_Frame_Find(cont, cont->typeData->name, 0)){
				animClone = Container_Frame_GetAnimClone(frame);
				time = Container_Frame_GetCurrTime(frame);
			} else Error_Warn(TRUE, "Couldn't find frame (thus AnimationSet) to SetTime() on");
		} else if (Container_Anim == cont->type) {
			animClone = Container_Frame_GetAnimClone(cont->activityFrame);
			time = Container_Frame_GetCurrTime(cont->activityFrame);
		}

		if (animClone) AnimClone_SetTime(animClone, time, NULL);
	}
}

REAL Container_GetAnimationTime(lpContainer cont){

	LPDIRECT3DRMFRAME3 frame;
	LPUCHAR currAnimName;
	REAL time = 0.0f;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type){
		Error_Fatal(!cont->typeData, "Container has no typeData");

		currAnimName = cont->typeData->name;
		if (frame = Container_Frame_Find(cont, currAnimName, 0)){
			time = Container_Frame_GetCurrTime(frame);
		} else Error_Warn(TRUE, "Couldn't find frame (thus AnimationSet) to SetTime() on");

	} else if (Container_Anim == cont->type) {

		time = Container_Frame_GetCurrTime(cont->activityFrame);

	} //else Error_Fatal(TRUE, "Container_SetTime() called with non-animation type container");

	return time;
}

ULONG Container_GetAnimationFrames(lpContainer cont){

	LPDIRECT3DRMFRAME3 frame = NULL;
	LPUCHAR currAnimName;

	if (Container_FromActivity == cont->type){
		Error_Fatal(!cont->typeData, "Container has no typeData");
		currAnimName = cont->typeData->name;
		frame = Container_Frame_Find(cont, currAnimName, 0);
	} else if (Container_Anim == cont->type) {
		frame = cont->activityFrame;
	}

	if (frame) return Container_Frame_GetFrameCount(frame);
	else return 0;
}

/*
VOID Container_Move(lpContainer root, REAL delta){

	ULONG loop;
	lpContainer_RotationData rot;

	for (loop=0 ; loop<containerGlobs.rotationCount ; loop++) {
		rot = &containerGlobs.rotationList[loop];
		if (rot->container) {
			Container_AddRotation(rot->container, rot->combine, rot->vector.x, rot->vector.y, rot->vector.z, rot->angle * delta);
		}
	}

	// Slow, slow, slow, slow, slow...
//	if (root->masterFrame->lpVtbl->Move(root->masterFrame, delta) == D3DRM_OK){

//	} else Error_Warn(TRUE, "Unable to move scene");
}

VOID Container_SetRotation(lpContainer cont, enum Container_Combine_Type combine, REAL x, REAL y, REAL z, REAL angle){

	lpContainer_RotationData rot = &containerGlobs.rotationList[containerGlobs.rotationCount];

	Error_Fatal(CONTAINER_MAXROTATION==containerGlobs.rotationCount, "CONTAINER_MAXROTATION too small - no recycle function for items. Please do not use this function.");

	rot->container = cont;
	rot->combine = combine;
	rot->vector.x = x;
	rot->vector.y = y;
	rot->vector.z = z;
	rot->angle = angle;
	containerGlobs.rotationCount++;

	// Slow, slow, slow, slow, slow...
//	LPDIRECT3DRMFRAME3 refFrame, frame;
//	Container_GetFrames(cont, ref, &frame, &refFrame);
//	frame->lpVtbl->SetRotation(frame, refFrame, x, y, z, angle);
//#ifdef CONTAINER_MATCHHIDDENHIERARCHY
//	Container_GetFramesHidden(cont, ref, &frame, &refFrame);
//	frame->lpVtbl->SetRotation(frame, refFrame, x, y, z, angle);
//#endif // CONTAINER_MATCHHIDDENHIERARCHY
}
*/

VOID Container_SetPosition(lpContainer cont, lpContainer ref, REAL x, REAL y, REAL z){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->SetPosition(frame, refFrame, x, y, z);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	Container_GetFramesHidden(cont, ref, &frame, &refFrame);
	frame->lpVtbl->SetPosition(frame, refFrame, x, y, z);
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_LookAt(lpContainer cont, lpContainer target, lpContainer ref, ULONG constraint){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->LookAt(frame, target->masterFrame, refFrame, constraint);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	Container_GetFramesHidden(cont, ref, &frame, &refFrame);
	frame->lpVtbl->LookAt(frame, target->masterFrame, refFrame, constraint);
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}	

VOID Container_SetOrientation(lpContainer cont, lpContainer ref, REAL dirx, REAL diry, REAL dirz, REAL upx, REAL upy, REAL upz){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->SetOrientation(frame, refFrame, dirx, diry, dirz, upx, upy, upz);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	Container_GetFramesHidden(cont, ref, &frame, &refFrame);
	frame->lpVtbl->SetOrientation(frame, refFrame, dirx, diry, dirz, upx, upy, upz);
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_GetRotation(lpContainer cont, lpContainer ref, LPVECTOR3D axis, LPREAL angle){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->GetRotation(frame, refFrame, (LPD3DVECTOR) axis, angle);
}

VOID Container_GetPosition(lpContainer cont, lpContainer ref, LPVECTOR3D pos){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->GetPosition(frame, refFrame, (LPD3DVECTOR) pos);
}

VOID Container_GetOrientation(lpContainer cont, lpContainer ref, LPVECTOR3D dir, LPVECTOR3D up){

	LPDIRECT3DRMFRAME3 refFrame, frame;
	VECTOR3D vdir, vup;

	Container_GetFrames(cont, ref, &frame, &refFrame);
	frame->lpVtbl->GetOrientation(frame, refFrame, (LPD3DVECTOR) &vdir, (LPD3DVECTOR) &vup);
	if (dir) *dir = vdir;
	if (up) *up = vup;
}

VOID Container_AddRotation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z, REAL angle){

	LPDIRECT3DRMFRAME3 frame;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->AddRotation(frame, combine, x, y, z, angle);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	if (Container_Reference != cont->type) {
		frame = cont->hiddenFrame;
		frame->lpVtbl->AddRotation(frame, combine, x, y, z, angle);
	}
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_AddScale(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z){

	LPDIRECT3DRMFRAME3 frame;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->AddScale(frame, combine, x, y, z);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	if (Container_Reference != cont->type) {
		frame = cont->hiddenFrame;
		frame->lpVtbl->AddScale(frame, combine, x, y, z);
	}
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_AddTranslation(lpContainer cont, ULONG combine, REAL x, REAL y, REAL z){

	LPDIRECT3DRMFRAME3 frame;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->AddTranslation(frame, combine, x, y, z);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	if (Container_Reference != cont->type) {
		frame = cont->hiddenFrame;
		frame->lpVtbl->AddTranslation(frame, combine, x, y, z);
	}
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_ClearTransform(lpContainer cont) {

	MATRIX4D mat;
	mat[0][0] = 1.0f;	mat[1][0] = 0.0f;	mat[2][0] = 0.0f;	mat[3][0] = 0.0f;
	mat[0][1] = 0.0f;	mat[1][1] = 1.0f;	mat[2][1] = 0.0f;	mat[3][1] = 0.0f;
	mat[0][2] = 0.0f;	mat[1][2] = 0.0f;	mat[2][2] = 1.0f;	mat[3][2] = 0.0f;
	mat[0][3] = 0.0f;	mat[1][3] = 0.0f;	mat[2][3] = 0.0f;	mat[3][3] = 1.0f;

	Container_AddTransform(cont, Container_Combine_Replace, mat);
}

VOID Container_AddTransform(lpContainer cont, ULONG combine, MATRIX4D mat){

	LPDIRECT3DRMFRAME3 frame;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->AddTransform(frame, combine, mat);
#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	if (Container_Reference != cont->type) {
		frame = cont->hiddenFrame;
		frame->lpVtbl->AddTransform(frame, combine, mat);
	}
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_GetTransform(lpContainer cont, MATRIX4D mat){

	LPDIRECT3DRMFRAME3 frame, parent;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->GetParent(frame, &parent);
	frame->lpVtbl->GetTransform(frame, parent, mat);
	parent->lpVtbl->Release(parent);
}

REAL Container_GetZXRatio(lpContainer cont){

	LPDIRECT3DRMFRAME3 frame, parent;
	MATRIX4D mat;
	Container_DebugCheckOK(cont);

	frame = cont->masterFrame;
	Error_Fatal(!frame, "Container has no masterFrame");

	frame->lpVtbl->GetParent(frame, &parent);
	frame->lpVtbl->GetTransform(frame, parent, mat);
	parent->lpVtbl->Release(parent);

	return mat[2][2] / mat[0][0];
}

VOID Container_CopyTransform(lpContainer cont, lpContainer ref){

	LPDIRECT3DRMFRAME3 refFrame, frame, parent;
	D3DRMMATRIX4D mat;

	Container_GetFrames(cont, ref, &frame, &refFrame);
	refFrame->lpVtbl->GetParent(refFrame, &parent);
	refFrame->lpVtbl->GetTransform(refFrame, parent, mat);
	parent->lpVtbl->Release(parent);
	frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, mat);

#ifdef CONTAINER_MATCHHIDDENHIERARCHY
	Container_GetFramesHidden(cont, ref, &frame, &refFrame);
	frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, mat);
#endif // CONTAINER_MATCHHIDDENHIERARCHY
}

VOID Container_SetParent(lpContainer child, lpContainer parent){

	// Pass NULL as the parent to unhook the Container...

	LPDIRECT3DRMFRAME3 parentFrame, childFrame, childFrameHidden;
//	LPDIRECT3DRMFRAME tempFrame1;
	Container_DebugCheckOK(child);

	childFrame = child->masterFrame;
	childFrameHidden = child->hiddenFrame;
	Error_Fatal(!childFrame||!childFrameHidden, "Child has no master/hiddenFrame");
	
	if (NULL == parent) {

		// Delete the Child from its existing parent...
		childFrame->lpVtbl->GetParent(childFrame, &parentFrame);
//		parentFrame = CUF(tempFrame1);
		if (parentFrame) {
			parentFrame->lpVtbl->DeleteChild(parentFrame, childFrame);
			parentFrame->lpVtbl->Release(parentFrame);
		}
		// else Frame was already unparented...

		// Do the same with the hidden frame...
		childFrame->lpVtbl->GetParent(childFrameHidden, &parentFrame);
//		parentFrame = CUF(tempFrame1);
		if (parentFrame) {
			parentFrame->lpVtbl->DeleteChild(parentFrame, childFrameHidden);
			parentFrame->lpVtbl->Release(parentFrame);
		}

	} else {
	
		parentFrame = parent->masterFrame;
		Error_Fatal(!parentFrame, "Parent has no masterFrame");
//		if (parentFrame->lpVtbl->AddChild(parentFrame, CDF(childFrame)) == D3DRM_OK){
//		} else Error_Fatal(TRUE, "Unable to add childFrame to parentFrame");

		Container_Frame_SafeAddChild(parentFrame, childFrame);

		// Do the same with the hidden frame...
		parentFrame = parent->hiddenFrame;
		Container_Frame_SafeAddChild(parentFrame, childFrameHidden);
	}
}

lpContainer Container_GetParent(lpContainer child){

	LPDIRECT3DRMFRAME3 childFrame, parentFrame;
//	LPDIRECT3DRMFRAME tempFrame1;
	lpContainer parent;

	Container_DebugCheckOK(child);

	// Special condition - Root frame 'may' have a parent with no container attached
	// (one that is at a level above the Containers hierarchy scope)...
	if (child == containerGlobs.rootContainer) return NULL;

	childFrame = child->masterFrame;
	Error_Fatal(!childFrame, "Child has no masterFrame");

	childFrame->lpVtbl->GetParent(childFrame, &parentFrame);

	if (parentFrame) {
		parent = Container_Frame_GetContainer(parentFrame);
		parentFrame->lpVtbl->Release(parentFrame);
	}
	else parent = NULL;

	return parent;
}

REAL Container_GetTransCoef(lpContainer cont){

	LPDIRECT3DRMFRAME3 actframe;

	Container_DebugCheckOK(cont);

	if (Container_FromActivity == cont->type){

		if (NULL != cont->typeData) {
			if (NULL != cont->typeData->name) {
				if (actframe = Container_Frame_Find(cont, cont->typeData->name, 0)){
					return Container_Frame_GetTransCo(actframe);
				}
			}
		}
	} else Error_Warn(TRUE, "Container_GetTransCoef() called with non-activity object");

	return 0.0f;
}

/**********************************************************************************
 ******** Container Static Library Function
 **********************************************************************************/

static VOID Container_YFlipTexture(LPDIRECT3DRMTEXTURE3 texture){

	LPD3DRMIMAGE image;
	LPUCHAR buffer, topline, bottomline;
	SLONG y, byteWidth;

	if (image = texture->lpVtbl->GetImage(texture)){
		byteWidth = (image->depth * image->width) / 8;
		if (buffer = Mem_Alloc(byteWidth)){
			topline = (LPUCHAR) image->buffer1;
			bottomline = &((LPUCHAR) image->buffer1)[(image->height-1) * image->bytes_per_line];
			
			for (y=0 ; y<image->height/2 ; y++){
				memcpy(buffer, bottomline, byteWidth);
				memcpy(bottomline, topline, byteWidth);
				memcpy(topline, buffer, byteWidth);
				topline += image->bytes_per_line;
				bottomline -= image->bytes_per_line;
			}

			Mem_Free(buffer);
		} else Error_Warn(TRUE, "Cannot allocate buffer for yflip");
	}
}

lpContainer Container_SearchOwner(LPDIRECT3DRMFRAME3 frame){

	// Search upwards from a frame until a non-reference container is found...

	lpContainer owner = NULL, test;
	LPDIRECT3DRMFRAME3 parent;
	HRESULT r;

	while (NULL == owner && NULL != frame){
		if (test = Container_Frame_GetOwner(frame)){
			if (Container_Reference != test->type) owner = test;
		}
		frame->lpVtbl->GetParent(frame, &parent);
		if (parent) {
			frame = parent;
			r = parent->lpVtbl->Release(parent);
		} else frame = NULL;
	}

	return owner;
}

#pragma message ( "Redunant function" )

static ULONG Container_GetCloneNumber(lpContainer cont){

	if (cont->cloneData){
		if (cont->cloneData->clonedFrom) return cont->cloneData->cloneNumber + 1;
		else return 0;
	}// else Error_Warn(TRUE, "Container has no cloneData");

	return 0;
}

static lpContainer Container_Frame_GetContainer(LPDIRECT3DRMFRAME3 frame){

	// Unlike Container_Frame_GetOwner() this will create a Container if there is
	// none already assigned...

	lpContainer cont;
	HRESULT r;

	Container_DebugCheckOK(frame);

	if (NULL == (cont = Container_Frame_GetOwner(frame))){

		// Create a new Container (along with redundant master frame).
		if (cont = Container_Create(NULL)){

			/*
			// Then move over the activity frame to the 'real' master frame,	
			Container_Frame_SafeAddChild(frame, cont->activityFrame);
			// Release the unused master frame and replace it with the correct one.
			Container_Frame_RemoveAppData(cont->masterFrame);
*/
			// Remove the redundant frames from the container...
			r = cont->masterFrame->lpVtbl->Release(cont->masterFrame);
			r = cont->activityFrame->lpVtbl->Release(cont->activityFrame);
//			r = cont->hiddenFrame->lpVtbl->Release(cont->hiddenFrame);

			cont->masterFrame = frame;
//			cont->hiddenFrame = NULL;
			cont->activityFrame = NULL;

			cont->type = Container_Reference;

			frame->lpVtbl->AddDestroyCallback(frame, Container_Frame_ReferenceDestroyCallback, NULL);

			Container_Frame_SetAppData(frame, cont, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

		} else Error_Warn(TRUE, "Couldn't create Container to surround frame");

	}

	return cont;
}

#ifdef CONTAINER_MATCHHIDDENHIERARCHY
static VOID Container_GetFrames(lpContainer cont, lpContainer ref, LPDIRECT3DRMFRAME3 *contFrame, LPDIRECT3DRMFRAME3 *refFrame){

	Container_DebugCheckOK(cont);
	*contFrame = cont->masterFrame;
	Error_Fatal(!(*contFrame), "Container has no masterFrame");
	if (NULL == ref) {
		(*contFrame)->lpVtbl->GetScene(*contFrame, refFrame);
		(*refFrame)->lpVtbl->Release(*refFrame);
	}
	else *refFrame = ref->masterFrame;
}
#else  // CONTAINER_MATCHHIDDENHIERARCHY
static VOID Container_GetFrames(lpContainer cont, lpContainer ref, LPDIRECT3DRMFRAME3 *contFrame, LPDIRECT3DRMFRAME3 *refFrame){

	Container_DebugCheckOK(cont);
	*contFrame = cont->masterFrame;
	Error_Fatal(!(*contFrame), "Container has no masterFrame");
	if (NULL == ref) *refFrame = containerGlobs.rootContainer->masterFrame;
	else *refFrame = ref->masterFrame;
}
#endif // CONTAINER_MATCHHIDDENHIERARCHY

#ifdef CONTAINER_MATCHHIDDENHIERARCHY
static VOID Container_GetFramesHidden(lpContainer cont, lpContainer ref, LPDIRECT3DRMFRAME3 *contFrame, LPDIRECT3DRMFRAME3 *refFrame){

	Container_DebugCheckOK(cont);
	*contFrame = cont->hiddenFrame;
	Error_Fatal(!(*contFrame), "Container has no hiddenFrame");
	if (NULL == ref) *refFrame = containerGlobs.rootContainer->hiddenFrame;
	else *refFrame = ref->hiddenFrame;
}
#endif // CONTAINER_MATCHHIDDENHIERARCHY

static enum Container_Type Container_ParseTypeString(LPUCHAR str, LPBOOL noTexture){

	// For now, just check against one type...

	ULONG loop, argc;
	LPUCHAR argv[10];
	UCHAR string[40];

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	if (NULL != str){
		strcpy(string, str);
		argc = Util_Tokenise(string, argv, ":");
		if (argc > 1 && 0 == stricmp(argv[1], "NOTEXTURE")) *noTexture = TRUE;
		else *noTexture = FALSE;

		for (loop=0 ; loop<Container_TypeCount ; loop++){
			if (NULL != containerGlobs.typeName[loop]){
				if (0 == stricmp(containerGlobs.typeName[loop], string)) {
					return loop;
				}
			}
		}
	} else Error_Fatal(TRUE, "Null string passed to Container_ParseTypeString()");
	return Container_Invalid;
}

static VOID Container_AddList(VOID){

	lpContainer list;
	ULONG loop, count;

	Container_DebugCheckOK(CONTAINER_DEBUG_NOTREQUIRED);

	Error_Fatal(containerGlobs.listCount+1 >= CONTAINER_MAXLISTS, "Run out of lists");

	count = 0x00000001 << containerGlobs.listCount;

	if (list = containerGlobs.listSet[containerGlobs.listCount] = 
		Mem_Alloc(sizeof(Container) * count)){

		containerGlobs.listCount++;

		for (loop=1 ; loop<count ; loop++){

//			list[loop-1].flags = CONTAINER_FLAG_INITIALISED;

			list[loop-1].nextFree = &list[loop];
		}
		list[count-1].nextFree = containerGlobs.freeList;
		containerGlobs.freeList = list;

	} else Error_Fatal(TRUE, Error_Format("Unable to allocate %d bytes of memory for new list.\n", sizeof(Container) * count));
}

//static ULONG Container_GetActivities(lpContainer cont, LPDIRECT3DRMFRAME3 *frameList, LPDIRECT3DRMANIMATIONSET *asList, LPUCHAR *nameList){
static ULONG Container_GetActivities(lpContainer cont, LPDIRECT3DRMFRAME3 *frameList, lpAnimClone *acList, LPUCHAR *nameList){

	// Either as List or nameList may be passed as NULL in which case they will not
	// be filled in (if both are NULL the result is the size of array required to hold them)...
	// If nameList is not passed as NULL, the LPUCHAR pointers returned MUST BE FREED
	// AFTER USE!!!!

	LPDIRECT3DRMFRAMEARRAY children;
	LPDIRECT3DRMFRAME3 sourceFrame, childFrame;
	LPDIRECT3DRMFRAME frame1;
	ULONG count, loop, source, nameLen=0, listSize=0;
	LPUCHAR name;
	HRESULT r;

	if (Container_FromActivity == cont->type){
		for (source=0 ; source<2 ; source++){

			if (0 == source) sourceFrame = cont->activityFrame;
			if (1 == source) sourceFrame = cont->hiddenFrame;

			if (sourceFrame->lpVtbl->GetChildren(sourceFrame, &children) == D3DRM_OK){
				count = children->lpVtbl->GetSize(children);
//				Error_Warn(!count, "Can't find any children on frame");
				for (loop=0 ; loop<count ; loop++){
					children->lpVtbl->GetElement(children, loop, &frame1);

					r = frame1->lpVtbl->QueryInterface(frame1, &IID_IDirect3DRMFrame3, &childFrame);
					Error_Fatal(r, "Cannot query frame3");
					frame1->lpVtbl->Release(frame1);

					childFrame->lpVtbl->GetName(childFrame, &nameLen, NULL);
					if (nameLen){
						name = Mem_Alloc(nameLen);
						childFrame->lpVtbl->GetName(childFrame, &nameLen, name);

						if (0 == strnicmp(name, CONTAINER_ACTIVITYFRAMEPREFIX, strlen(CONTAINER_ACTIVITYFRAMEPREFIX))){
							if (NULL != frameList) frameList[listSize] = childFrame;
							if (NULL != acList) acList[listSize] = Container_Frame_GetAnimClone(childFrame);
							if (NULL != nameList) nameList[listSize] = name;
							listSize++;
		
							if (NULL == nameList) Mem_Free(name);
						} else Mem_Free(name);
					}
					r = childFrame->lpVtbl->Release(childFrame);
				}
				r = children->lpVtbl->Release(children);

			} else Error_Fatal(TRUE, "GetChildren() call failed");
		}
	} else Error_Fatal(TRUE, "Container_GetActivities() supplied with a non-activity object");

	return listSize;
}

static VOID Container_SetTypeData(lpContainer cont, LPUCHAR name, LPDIRECT3DRMLIGHT light, LPDIRECT3DRMMESH mesh, lpMesh transMesh){

	Container_DebugCheckOK(cont);
	
	if (cont->typeData) {
		if (NULL != name) cont->typeData->name = name;
		if (NULL != light) cont->typeData->light = light;
		if (NULL != mesh) cont->typeData->mesh = mesh;
		if (NULL != transMesh) cont->typeData->transMesh = transMesh;
	} else {
		cont->typeData = Mem_Alloc(sizeof(Container_TypeData));
		cont->typeData->name = name;
		cont->typeData->light = light;
		cont->typeData->mesh = mesh;
		cont->typeData->transMesh = transMesh;
	}
}

static VOID Container_FreeTypeData(lpContainer cont){

	HRESULT r;

	if (cont->typeData){
		if (Container_FromActivity == cont->type) {
			Mem_Free(cont->typeData->name);
		} else if (Container_Light == cont->type) {
			r = cont->typeData->light->lpVtbl->Release(cont->typeData->light);
		} else if (Container_Mesh == cont->type) {
			if (cont->typeData->mesh) {
				cont->activityFrame->lpVtbl->DeleteVisual(cont->activityFrame, (struct IUnknown *) cont->typeData->mesh);
				r = cont->typeData->mesh->lpVtbl->Release(cont->typeData->mesh);
			}
		} else if (Container_LWO == cont->type) {
			if (cont->typeData->transMesh)
				Mesh_Remove(cont->typeData->transMesh, cont->activityFrame);
		} else Error_Warn(TRUE, Error_Format("Code not implemented for Container type #%d", cont->type));
		Mem_Free(cont->typeData);
		cont->typeData = NULL;
	}
}

//static BOOL Container_AddActivity2(lpContainer cont, LPUCHAR filename, LPUCHAR actname, REAL transCo, ULONG fref, lpSound sample){
static BOOL Container_AddActivity2(lpContainer cont, LPUCHAR filename, LPUCHAR actname, REAL transCo, ULONG trigger, LPUCHAR sample, lpAnimClone origClone, BOOL lws, BOOL looping){

	LPDIRECT3DRMFRAME3 newFrame;
//	LPDIRECT3DRMANIMATIONSET animSet;
	UCHAR xFile[UTIL_DEFSTRINGLEN];
	ULONG frameCount;
	lpAnimClone animClone;

	sprintf(xFile, "%s.%s", filename, containerGlobs.extensionName[Container_Anim]);

	if (lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), cont->hiddenFrame, &newFrame) == D3DRM_OK){
		Container_NoteCreation(newFrame);

		// Set the name of the parent to the animation set.
		// Freed when the container is destroyed

		// This will also set the appData's pointer to the name... 
		Container_Frame_FormatName(newFrame, "%s_%s", CONTAINER_ACTIVITYFRAMEPREFIX, actname);

		// Load in the AnimationSet.
//		if (animSet = Container_LoadAnimSet(xFile, newFrame, fref, &frameCount)){
		if (NULL == origClone) {
			animClone = Container_LoadAnimSet(xFile, newFrame, &frameCount, lws, looping);
		} else {
			animClone = AnimClone_Make(origClone, newFrame, &frameCount);
		}

			Container_Frame_SetAppData(newFrame, cont, animClone, filename, &frameCount, NULL, NULL, &transCo, sample, NULL, &trigger);

			return TRUE;
			
//		} else Error_Warn(TRUE, Error_Format("Unable to load animset %s", xFile));
		
	} else Error_Warn(TRUE, "Unable to create frame for new activity");

	return FALSE;
}

/**********************************************************************************
 ******** Container Static Functions on Frames
 **********************************************************************************/
/*
static LPDIRECT3DRMFRAME Container_Frame_CastDown(LPDIRECT3DRMFRAME3 f){

	LPDIRECT3DRMFRAME f1;
	HRESULT r;

	if (f){
		f->lpVtbl->QueryInterface(f, &IID_IDirect3DRMFrame, &f1);
		r = f1->lpVtbl->Release(f1);
		return f1;
	} else return NULL;
}

static LPDIRECT3DRMFRAME3 Container_Frame_CastUp(LPDIRECT3DRMFRAME f){

	LPDIRECT3DRMFRAME3 f1;
	HRESULT r;

	if (f){
		f->lpVtbl->QueryInterface(f, &IID_IDirect3DRMFrame2, &f1);
		r = f1->lpVtbl->Release(f1);
		return f1;
	} else return NULL;
}
*/
static VOID Container_Frame_ReferenceDestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg){

	LPDIRECT3DRMFRAME3 frame = (LPDIRECT3DRMFRAME3) lpD3DRMobj;
	lpContainer cont;

	Error_Warn(TRUE, "Reference container's frame is being destroyed");

	if (cont = Container_Frame_GetOwner(frame)){
		cont->flags |= CONTAINER_FLAG_DEADREFERENCE;
		Container_Frame_RemoveAppData(frame);
	}
}

static LPDIRECT3DRMFRAME3 Container_Frame_Find(lpContainer cont, LPUCHAR findName, ULONG hidden){

	LPDIRECT3DRMFRAME3 frame, childFrame, foundFrame = NULL;
	LPDIRECT3DRMFRAME frame1;
	LPDIRECT3DRMFRAMEARRAY children;
	ULONG count, loop, nameLen;
	UCHAR tempString[UTIL_DEFSTRINGLEN];
	LPUCHAR name;
	HRESULT r;

	if (hidden) frame = cont->hiddenFrame;
	else frame = cont->activityFrame;

	if (frame->lpVtbl->GetChildren(frame, &children) == D3DRM_OK){
		count = children->lpVtbl->GetSize(children);
		Error_Warn(!count, "Can't find any children on frame");
		for (loop=0 ; loop<count ; loop++){
			children->lpVtbl->GetElement(children, loop, &frame1);

			r = frame1->lpVtbl->QueryInterface(frame1, &IID_IDirect3DRMFrame3, &childFrame);
			Error_Fatal(r, "Error getting frame3");
			frame1->lpVtbl->Release(frame1);

			childFrame->lpVtbl->GetName(childFrame, &nameLen, NULL);
			if (nameLen) {
				name = Mem_Alloc(nameLen+1);
				childFrame->lpVtbl->GetName(childFrame, &nameLen, name);

				sprintf(tempString, "%s_%s", CONTAINER_ACTIVITYFRAMEPREFIX, findName);
				if (0 == stricmp(name, tempString)) foundFrame = childFrame;
				Mem_Free(name);
			}

			r = childFrame->lpVtbl->Release(childFrame);

			if (foundFrame) break;
		}
		r = children->lpVtbl->Release(children);

	} else Error_Fatal(TRUE, "GetChildren() call failed");

	return foundFrame;
}

VOID Container_Frame_SetAppData(LPDIRECT3DRMFRAME3 frame, lpContainer owner, lpAnimClone animClone, LPUCHAR asfname, LPULONG frameCount, LPUCHAR frameName, LPREAL currTime, LPREAL transCo, LPUCHAR actSample, LPVOID soundRecord, LPULONG trigger) {

	Container_AppData *appData;

	// If the AppData already exists then change the data (if specified)
	// Otherwise, create the new AppData and set the values..

#pragma message ( "Sound3D removal changes" )

	if (appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame)){
		if (NULL != owner) appData->ownerContainer = owner;
		if (NULL != animClone) appData->animClone = animClone;
		if (NULL != asfname && NULL != appData->animSetFileName) Mem_Free(appData->animSetFileName);
		if (NULL != frameCount) appData->frameCount = *frameCount;
		if (NULL != frameName) appData->frameName = frameName;
		if (NULL != currTime) appData->currTime = *currTime;
		if (NULL != transCo) appData->transCo = *transCo;
		if (NULL != actSample) appData->activitySample = actSample;
//		if (NULL != soundRecord) appData->soundList = soundRecord;
		if (NULL != trigger) appData->trigger = *trigger;
	} else {
		appData = Mem_Alloc(sizeof(Container_AppData));
		appData->ownerContainer = owner;
		appData->animClone = animClone;
		appData->animSetFileName = NULL;
		if (frameCount) appData->frameCount = *frameCount;
		else appData->frameCount = 0;
		appData->frameName = frameName;
		if (currTime) appData->currTime = *currTime;
		else appData->currTime = 0.0f;
		if (transCo) appData->transCo = *transCo;
		else appData->transCo = 0.0f;
		if (trigger) appData->trigger = *trigger;
		else appData->trigger = 0;
		appData->activitySample = actSample;
//		appData->soundList = soundRecord;
		frame->lpVtbl->SetAppData(frame, (DWORD) appData);
	}

	if (NULL != asfname){
		appData->animSetFileName = Mem_Alloc(strlen(asfname)+1);
		strcpy(appData->animSetFileName, asfname);
	}
}

static VOID Container_Frame_RemoveAppData(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData){
		if (NULL != appData->animSetFileName) Mem_Free(appData->animSetFileName);
		Mem_Free(appData);
	}
	frame->lpVtbl->SetAppData(frame, (DWORD) NULL);
}

static lpContainer Container_Frame_GetOwner(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
//	Error_Warn(!appData, Error_Format("AppData not set on frame 0x%0.8x", frame));
	if (appData) return appData->ownerContainer;
	return NULL;
}

static LPUCHAR Container_Frame_GetAnimSetFileName(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->animSetFileName;
	return NULL;
}

static lpAnimClone Container_Frame_GetAnimClone(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->animClone;
	return NULL;
}

static ULONG Container_Frame_GetFrameCount(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->frameCount;
	return 0;
}

static LPUCHAR Container_Frame_GetName(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->frameName;
	return NULL;
}

static REAL Container_Frame_GetCurrTime(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->currTime;
	return 0.0f;
}

static REAL Container_Frame_GetTransCo(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->transCo;
	return 0.0f;
}

static LPUCHAR Container_Frame_GetSample(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->activitySample;
	return NULL;
}

static ULONG Container_Frame_GetTrigger(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->trigger;
	return 0;
}

/*
static lpSound3D_Sound3DRecord Container_Frame_Get3DSound(LPDIRECT3DRMFRAME3 frame){
	
	Container_AppData *appData = (Container_AppData*) frame->lpVtbl->GetAppData(frame);
	Error_Fatal(!appData, "AppData not set on frame");
	if (appData) return appData->soundList;
	return NULL;
}
*/
static VOID Container_Frame_SafeAddChild(LPDIRECT3DRMFRAME3 parent, LPDIRECT3DRMFRAME3 child){

	// Stop addchild from corrupting the transformation matrix...
	D3DRMMATRIX4D mat;
	LPDIRECT3DRMFRAME3 oldParent;

	child->lpVtbl->GetParent(child, &oldParent);
	child->lpVtbl->GetTransform(child, oldParent, mat);
	if (oldParent) oldParent->lpVtbl->Release(oldParent);
	parent->lpVtbl->AddChild(parent, child);
	child->lpVtbl->AddTransform(child, D3DRMCOMBINE_REPLACE, mat);
}

static VOID Container_Frame_FormatName(LPDIRECT3DRMFRAME3 frame, LPUCHAR msg, ...){

	UCHAR buffer[1024];
	LPUCHAR name;
	ULONG len;
	va_list args;
	
	va_start(args, msg);
	len = vsprintf(buffer, msg, args);
	va_end(args);

	name = Mem_Alloc(len+1);
	va_start(args, msg);
	vsprintf(name, msg, args);
	va_end(args);

	frame->lpVtbl->SetName(frame, name);
	Container_Frame_SetAppData(frame, NULL, NULL, NULL, NULL, name, NULL, NULL, NULL, NULL, NULL);
}

static VOID Container_Frame_FreeName(LPDIRECT3DRMFRAME3 frame){

	LPUCHAR name;
	
	if (name = Container_Frame_GetName(frame)){
		Mem_Free(name);
	}
}

static BOOL Container_Frame_WalkTree(LPDIRECT3DRMFRAME3 frame, ULONG level, BOOL (*Callback)(LPDIRECT3DRMFRAME3 frame, LPVOID data), LPVOID data){

	LPDIRECT3DRMFRAMEARRAY children;
	LPDIRECT3DRMFRAME3 child;
	LPDIRECT3DRMFRAME child1;
	ULONG count, loop;
	BOOL finished = FALSE;
	HRESULT r;

	if (Callback(frame, data)) return TRUE;

	frame->lpVtbl->GetChildren(frame, &children);
	count = children->lpVtbl->GetSize(children);
	for (loop=0 ; loop<count ; loop++){
		children->lpVtbl->GetElement(children, loop, &child1);
		child1->lpVtbl->QueryInterface(child1, &IID_IDirect3DRMFrame3, &child);
		child1->lpVtbl->Release(child1);
		if (Container_Frame_WalkTree(child, level+1, Callback, data)) {
			finished = TRUE;
			r = child->lpVtbl->Release(child);
			break;
		}
		r = child->lpVtbl->Release(child);
	}
	r = children->lpVtbl->Release(children);

	return finished;
}

static BOOL Container_Frame_SearchCallback(LPDIRECT3DRMFRAME3 frame, LPVOID data){

	Container_SearchData *search = data;
	LPUCHAR name;
	ULONG len, loop;

	frame->lpVtbl->GetName(frame, &len, NULL);

	if (len-1 == search->stringLen){
		name = Mem_Alloc(len);
		name[0] = '\0';
		frame->lpVtbl->GetName(frame, &len, name);

		// Replace any characters in the name string with '?' if their position
		// corresponds to a '?' in the search string...
		for (loop=0 ; loop<len ; loop++) if ('?' == search->string[loop]) name[loop] = '?';

		if (Container_SearchMode_FirstMatch == search->mode) {
			search->resultFrame = NULL;
			if (search->caseSensitive) {
				if (0 == strcmp(name, search->string)) search->resultFrame = frame;
			} else {
				if (0 == stricmp(name, search->string)) search->resultFrame = frame;
			}
		} else if (Container_SearchMode_MatchCount == search->mode) {
			if (search->caseSensitive) {
				if (0 == strcmp(name, search->string)) search->count++;
			} else {
				if (0 == stricmp(name, search->string)) search->count++;
			}
		} else if (Container_SearchMode_NthMatch == search->mode){
			search->resultFrame = NULL;
			if (search->caseSensitive) {
				if (0 == strcmp(name, search->string)) search->count++;
			} else {
				if (0 == stricmp(name, search->string)) search->count++;
			}
			if (search->count == search->matchNumber + 1) search->resultFrame = frame;
		} else Error_Fatal(TRUE, "Unknown search type");

		Mem_Free(name);

		if (search->resultFrame) return TRUE;

	}
	return FALSE;
}


/**********************************************************************************
 ******** File load functions.
 **********************************************************************************/

static lpAnimClone Container_LoadAnimSet(LPUCHAR fname, LPDIRECT3DRMFRAME3 frame, LPULONG frameCount, BOOL lws, BOOL looping){

	LPDIRECT3DRMANIMATIONSET2 animSet = NULL;
	LPDIRECT3DRMFRAME3 rootFrame;
	D3DRMLOADMEMORY buffer;
	Container_TextureData tData;
	lpAnimClone animClone = NULL;
	ULONG fc;

#ifdef _DEBUG
/*	{
		static UCHAR nameList[1024][128];
		static ULONG nameCount = 0;
		ULONG loop;
		Error_Fatal(strlen(fname) > 128, "Name too long");
		Error_Fatal(nameCount > 1024, "name list overflowed");
		for (loop=0 ; loop<nameCount ; loop++) {
			Error_Fatal(0 == stricmp(fname, nameList[loop]), Error_Format("Cannot load the same x animation file twice\n(%s)", fname));
		}
		strcpy(nameList[nameCount++], fname);
	}*/
#endif // _DEBUG

	Error_Debug(Error_Format("Attempting to load animation from xfile \"%s\"\n", fname));


	if (lws) {

		lpLws_Info scene;
		UCHAR file[FILE_MAXPATH];

		strcpy(file, fname);
		file[strlen(file)-2] = '\0';
		if (scene = Lws_Parse(file, looping)) {
			Lws_LoadMeshes(scene, frame);
			Lws_SetTime(scene, 0.0f);
			if (frameCount) *frameCount = Lws_GetFrameCount(scene);
			animClone = AnimClone_RegisterLws(scene, frame, *frameCount);
		} else Error_Warn(TRUE, "Cannot load file");

	} else {

		if (buffer.lpMemory = File_LoadBinary(fname, &buffer.dSize)){
			if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), frame, &rootFrame)){
				Container_NoteCreation(rootFrame);
				if (lpD3DRM()->lpVtbl->CreateAnimationSet(lpD3DRM(), &animSet) == D3DRM_OK){
					Container_NoteCreation(animSet);
					
					tData.xFileName = fname;
					tData.flags = 0;
					
					if (animSet->lpVtbl->Load(animSet, &buffer, NULL, D3DRMLOAD_FROMMEMORY, Container_TextureLoadCallback, &tData, rootFrame) == D3DRM_OK){
	//				if (animSet->lpVtbl->Load(animSet, &buffer, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL, rootFrame) == D3DRM_OK){
						animSet->lpVtbl->SetTime(animSet, 0.0f);

	/*					{	// Set the animations to use linear interpolation...
							LPDIRECT3DRMANIMATIONARRAY anims;
							LPDIRECT3DRMANIMATION2 anim;
							D3DRMANIMATIONOPTIONS options;
							ULONG animCount, loop;
							if (D3DRM_OK == animSet->lpVtbl->GetAnimations(animSet, &anims)){
								animCount = anims->lpVtbl->GetSize(anims);
								for (loop=0 ; loop<animCount ; loop++) {
									anims->lpVtbl->GetElement(anims, loop, &anim);
									options = anim->lpVtbl->GetOptions(anim);
									anim->lpVtbl->SetOptions(anim, D3DRMANIMATION_LINEARPOSITION|D3DRMANIMATION_OPEN|D3DRMANIMATION_POSITION);
									anim->lpVtbl->Release(anim);
								}
								anims->lpVtbl->Release(anims);
							}
						}*/

						fc = Container_GetAnimFileFrameCount(buffer.lpMemory);
						if (frameCount) *frameCount = fc;
						animClone = AnimClone_Register(animSet, rootFrame, fc);
					}
					Mem_Free(buffer.lpMemory);
				}
				rootFrame->lpVtbl->Release(rootFrame);
			}
		}
	}

	return animClone;
}

static ULONG Container_GetAnimFileFrameCount(LPUCHAR fileData){

	ULONG count = 0;

	if (fileData = strstr(fileData, "DDiScene")){
		while(!isdigit(*fileData)) fileData++;
		count = atoi(fileData);
	}

	if (0 == count) count = 1;
	return count;
}

static BOOL Container_FrameLoad(LPUCHAR fname, LPDIRECT3DRMFRAME3 frame){

	BOOL res = FALSE;
	D3DRMLOADMEMORY buffer;
	Container_TextureData tData;

	if (buffer.lpMemory = File_LoadBinary(fname, &buffer.dSize)){

		tData.xFileName = fname;
		tData.flags = 0;

		if (D3DRM_OK == frame->lpVtbl->Load(frame, &buffer, NULL, D3DRMLOAD_FROMMEMORY, Container_TextureLoadCallback, &tData)){
//		if (D3DRM_OK == frame->lpVtbl->Load(frame, &buffer, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL)){
			res = TRUE;
		}
		Mem_Free(buffer.lpMemory);
	}

	return res;
}

static LPDIRECT3DRMMESH Container_MeshLoad(LPVOID file_data, ULONG file_size, LPUCHAR file_name, LPDIRECT3DRMFRAME3 frame, BOOL noTexture){
	
	LPDIRECT3DRMMESHBUILDER3 mb;
	LPDIRECT3DRMMESH mesh;
	HRESULT r;
	D3DRMLOADMEMORY buffer;
	Container_TextureData tData;

	buffer.lpMemory = file_data;
	buffer.dSize = file_size;

	if (D3DRM_OK == lpD3DRM()->lpVtbl->CreateMeshBuilder(lpD3DRM(), &mb)){
		Container_NoteCreation(mb);

		tData.xFileName = file_name;
		tData.flags = 0;
		if (noTexture) tData.flags |= CONTAINER_TEXTURE_NOLOAD;

		if (D3DRM_OK == mb->lpVtbl->Load(mb, &buffer, NULL, D3DRMLOAD_FROMMEMORY, Container_TextureLoadCallback, &tData)){
//		if (D3DRM_OK == mb->lpVtbl->Load(mb, &buffer, NULL, D3DRMLOAD_FROMMEMORY, NULL, NULL)){
			mb->lpVtbl->CreateMesh(mb, &mesh);
			Container_NoteCreation(mesh);
			r = mb->lpVtbl->Release(mb);
			if (D3DRM_OK == frame->lpVtbl->AddVisual(frame, (struct IUnknown *) mesh)){

				return mesh;

			} else Error_Fatal(TRUE, "Unable to add visual to frame");
		} else Error_Fatal(TRUE, Error_Format("Unable to load MeshBuilder from memory (%s)", file_name));
		r = mb->lpVtbl->Release(mb);
	} else Error_Fatal(TRUE, "Unable create MeshBuilder");

	return NULL;
}

static HRESULT Container_TextureLoadCallback(char *name, void *data, LPDIRECT3DRMTEXTURE3 *texture){

	lpContainer_TextureData textureData = data;
	lpContainer_Texture text;

	if (!(textureData->flags & CONTAINER_TEXTURE_NOLOAD)){

		UCHAR path[1024];
		LPUCHAR s, p, tag = NULL;
	//	lpImage image;
	//	LPDIRECT3DRMTEXTURE3 text;
		ULONG loop;
		SLONG location;

		s = textureData->xFileName;
		p = path;

		for (location=0 ; location<(containerGlobs.sharedDir?2:1) ; location++) {

			if (0 == location) {
				// Strip the xfilename off the end of the path...
				while ('\0' != *s) {
					if ('\\' == *s) {
						if (tag) *tag = '\\';
						*p = '\0';
						tag = p;
					} else *p = *s;
					s++;
					p++;
				}
				if (tag){
					strcat(path, "\\");
					strcat(path, name);
				} else strcpy(path, name);
			} else {
				sprintf(path, "%s\\%s", containerGlobs.sharedDir, name);
			}

			*texture = NULL;

			for (loop=0 ; loop<containerGlobs.textureCount ; loop++){

				if (containerGlobs.textureSet[loop].fileName && (0 == strcmp(containerGlobs.textureSet[loop].fileName, path))){
					*texture = containerGlobs.textureSet[loop].texture;
					(*texture)->lpVtbl->AddRef(*texture);

					return D3DRM_OK;
				}
			}

			if (text = Container_LoadTexture(path, NULL, NULL)){

				*texture = text->texture;

	#ifndef CONTAINER_DONTFLIPTEXTURES
				Container_YFlipTexture(*texture);
	#endif
				if (Main_MIPMapEnabled()) {
					HRESULT r = (*texture)->lpVtbl->GenerateMIPMap(*texture, 0);
				}

				if (containerGlobs.textureCount == CONTAINER_MAXTEXTURES) {

					Error_Warn(TRUE, "Sorting texture list");
					qsort(containerGlobs.textureSet, containerGlobs.textureCount, sizeof(Container_TextureRef), Container_TextureSetSort);
					for ( ; containerGlobs.textureCount>=0 ; containerGlobs.textureCount--){
						if (containerGlobs.textureSet[containerGlobs.textureCount-1].fileName) break;
					}
					Error_Fatal(containerGlobs.textureCount == CONTAINER_MAXTEXTURES, "CONTAINER_MAXTEXTURES overflowed");

				}

				if (containerGlobs.textureCount < CONTAINER_MAXTEXTURES) {
					lpContainer_TextureRef textRef = &containerGlobs.textureSet[containerGlobs.textureCount];
					
					(*texture)->lpVtbl->AddDestroyCallback(*texture, Container_TextureDestroyCallback, textRef);

					textRef->fileName = Mem_Alloc(strlen(path)+1);
					strcpy(textRef->fileName, path);
					textRef->texture = *texture;

					containerGlobs.textureCount++;
				}
				return D3DRM_OK;
			}
		}
	}

	return D3DRMERR_NOTFOUND;
}

static int __cdecl Container_TextureSetSort(const void *a, const void *b){

	if (NULL != ((lpContainer_TextureRef) a)->fileName && NULL == ((lpContainer_TextureRef) b)->fileName) return -1;
	if (NULL == ((lpContainer_TextureRef) a)->fileName && NULL != ((lpContainer_TextureRef) b)->fileName) return 1;
	return 0;
}

static VOID Container_TextureDestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg){

	lpContainer_TextureRef textRef = lpArg;
	lpContainer_Texture text;

	Error_Debug(Error_Format("Removing %s from texture list\n", textRef->fileName));

	text = (lpContainer_Texture) textRef->texture->lpVtbl->GetAppData(textRef->texture);
	// This is deliberatly not Mem_Free()
	free(text);

	Mem_Free(textRef->fileName);
	textRef->fileName = NULL;
	textRef->texture = NULL;

}

/**********************************************************************************
 ******** Debug Code
 **********************************************************************************/

#ifdef _DEBUG

VOID Container_Debug_DumpActivityNames(lpContainer cont){

	LPUCHAR *name;
	ULONG loop, count = Container_GetActivities(cont, NULL, NULL, NULL);

	name = Mem_Alloc(count * sizeof(LPUCHAR));
	Container_GetActivities(cont, NULL, NULL, name);
	for (loop=0 ; loop<count ; loop++){
		Error_Debug(Error_Format("%s\n", name[loop]));
		Mem_Free(name[loop]);
	}

	Mem_Free(name);
}

VOID Container_Debug_DumpFrameHierarchy(LPDIRECT3DRMFRAME3 frame, ULONG level, LPBOOL end, lpFile file){

	LPDIRECT3DRMFRAMEARRAY children;
	LPDIRECT3DRMFRAME3 child;
	LPDIRECT3DRMFRAME child1;
	ULONG count, loop, len, references;
	LPUCHAR name;
	HRESULT r;

	if (file) {
		for (loop=0 ; loop<level ; loop++) {
			if (loop==level-1) File_PrintF(file, "|___");
			else {
				if (end[loop]) File_PrintF(file, "    ");
				else File_PrintF(file, "|   ");
			}
		}
	} else {
		for (loop=0 ; loop<level ; loop++) {
			if (loop==level-1) Error_Debug(Error_Format("|___"));
			else {
				if (end[loop]) Error_Debug(Error_Format("       "));
				else Error_Debug(Error_Format("|      "));
			}
		}
	}

	if (file) File_PrintF(file, "0x%0.8x ", frame);
	else Error_Debug(Error_Format("0x%0.8x ", frame));

	frame->lpVtbl->GetName(frame, &len, NULL);
	name = Mem_Alloc(len+1);
	name[0] = '\0';
	frame->lpVtbl->GetName(frame, &len, name);

	frame->lpVtbl->AddRef(frame);
	references = frame->lpVtbl->Release(frame);

	if (file) File_PrintF(file, "\"%s\" (%i reference%s)\n", name, references, 1==references?"":"s");
	else Error_Debug(Error_Format("\"%s\" (%i reference%s)\n", name, references, 1==references?"":"s"));

	Mem_Free(name);

	frame->lpVtbl->GetChildren(frame, &children);
	count = children->lpVtbl->GetSize(children);
	for (loop=0 ; loop<count ; loop++){
		children->lpVtbl->GetElement(children, loop, &child1);
		child1->lpVtbl->QueryInterface(child1, &IID_IDirect3DRMFrame3, &child);
		child1->lpVtbl->Release(child1);
		if (loop==count-1) end[level] = TRUE;
		else end[level] = FALSE;
		Container_Debug_DumpFrameHierarchy(child, level+1, end, file);
		r = child->lpVtbl->Release(child);
	}
	r = children->lpVtbl->Release(children);
}

VOID Container_Debug_CheckMesh(lpContainer cont, ULONG group){
	
	lpContainer_MeshAppData appdata;
	ULONG groups;
	
	if (appdata = (lpContainer_MeshAppData) cont->typeData->mesh->lpVtbl->GetAppData(cont->typeData->mesh)){
		Error_Fatal(group > appdata->usedCount, Error_Format("Group %i is out of range", group));
	} else {
		groups = cont->typeData->mesh->lpVtbl->GetGroupCount(cont->typeData->mesh);
		Error_Fatal(group >= groups, Error_Format("Group %i is out of range", group));
	}
}

VOID Container_Debug_Check(LPUCHAR file, ULONG line){

	static ULONG oldref = 0;
	ULONG newref;

	if (containerGlobs.rootContainer){
		containerGlobs.rootContainer->masterFrame->lpVtbl->AddRef(containerGlobs.rootContainer->masterFrame);
		newref = containerGlobs.rootContainer->masterFrame->lpVtbl->Release(containerGlobs.rootContainer->masterFrame);

		if (newref != oldref) Error_Debug(Error_Format("reference count changed %i\n", line));
		newref = oldref;
	}
}

lpContainer Container_Debug_MakeCamera(lpContainer parent){

	lpContainer cont = Container_Create(parent);
	Container_Frame_FormatName(cont->masterFrame, "Camera Master");
	Container_Frame_FormatName(cont->activityFrame, "Camera Activity");
	Container_Frame_FormatName(cont->hiddenFrame, "Camera Hidden");

	return cont;
}

#endif // _DEBUG

#ifdef _HIERARCHY_DEBUG

ULONG containerDebugCreationCount = 0;
ULONG containerDebugDestructionCount = 0;
ULONG containerDebugCreationLineTable[20480] = { 0 };
LPDIRECT3DRMOBJECT containerDebugCreationObjectTable[20480] = { NULL };

VOID Container_Debug_NoteCreation(LPDIRECT3DRMOBJECT lpD3DRMobj, ULONG line){
	
	lpD3DRMobj->lpVtbl->AddDestroyCallback(lpD3DRMobj, Container_Debug_DestroyCallback, &containerDebugCreationLineTable[containerDebugCreationCount]);
	containerDebugCreationLineTable[containerDebugCreationCount] = line;
	containerDebugCreationObjectTable[containerDebugCreationCount] = lpD3DRMobj;
	
	if (18 == containerDebugCreationCount) {
		containerDebugCreationCount = 18;
	}

	containerDebugCreationCount++;
}

ULONG Container_Debug_GetCreationLine(LPDIRECT3DRMOBJECT lpD3DRMobj) {

	ULONG loop;

	for (loop=0 ; loop<containerDebugCreationCount ; loop++) {
		if (containerDebugCreationObjectTable[loop] == lpD3DRMobj) return containerDebugCreationLineTable[loop];
	}

	return 0;
}

VOID Container_Debug_DestroyCallback(LPDIRECT3DRMOBJECT lpD3DRMobj, LPVOID lpArg){
	
	LPUCHAR className;
	ULONG len;
	LPULONG entry = lpArg;
	
	lpD3DRMobj->lpVtbl->GetClassName(lpD3DRMobj, &len, NULL);
	className = Mem_Alloc(len);
	lpD3DRMobj->lpVtbl->GetClassName(lpD3DRMobj, &len, className);
	
	Error_Debug(Error_Format("Object of class %s destroyed (line %i)\n", className, *entry));
	containerDebugDestructionCount++;
	
	*entry = 0;
	Mem_Free(className);
}

VOID Container_Debug_DumpCreationInfo(VOID){
	
	ULONG loop, len, ref;
	UCHAR className[1024], objName[1024];
	LPDIRECT3DRMOBJECT lpD3DRMobj;
	
	Error_Debug(Error_Format("%i objects created, %i objects destroyed: %i lost\n", containerDebugCreationCount, containerDebugDestructionCount, containerDebugCreationCount - containerDebugDestructionCount));
	
	for (loop=0 ; loop<containerDebugCreationCount ; loop++){
		if (containerDebugCreationLineTable[loop]) {
			if (lpD3DRMobj = containerDebugCreationObjectTable[loop]){
				lpD3DRMobj->lpVtbl->GetClassName(lpD3DRMobj, &len, NULL);
				if (len) lpD3DRMobj->lpVtbl->GetClassName(lpD3DRMobj, &len, className);
				else className[0] = '\0';
				lpD3DRMobj->lpVtbl->GetName(lpD3DRMobj, &len, NULL);
				if (len) lpD3DRMobj->lpVtbl->GetName(lpD3DRMobj, &len, objName);
				else objName[0] = '\0';
				lpD3DRMobj->lpVtbl->AddRef(lpD3DRMobj);
				ref = lpD3DRMobj->lpVtbl->Release(lpD3DRMobj);
			} else {
				sprintf(className, "Error");
				sprintf(objName, "NULL object");
			}
			Error_Debug(Error_Format("Offending line: %i entry %i (%s (%s)) (%i reference%s)\n", containerDebugCreationLineTable[loop], loop, className, objName, ref, 1==ref?"":"s"));
		}
	}
}

#endif // _HIERARCHY_DEBUG

VOID Container_Debug_SetViewportBlueBackground( lpViewport view )
{	D3DMATERIALHANDLE handle;
	LPDIRECT3DVIEWPORT imview1;
	LPDIRECT3DVIEWPORT3 imview;
	LPDIRECT3D3 imd3d;
	D3DMATERIAL material =
	{
		sizeof(D3DMATERIAL),
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		0.0f,
		0,
		0
	};
	LPDIRECT3DMATERIAL3 imMat;


	lpIMDevice()->lpVtbl->GetDirect3D( lpIMDevice(), &imd3d );
	
	imd3d->lpVtbl->CreateMaterial( imd3d, &imMat, NULL );
	imMat->lpVtbl->GetHandle( imMat, lpIMDevice(), &handle );
	imMat->lpVtbl->SetMaterial( imMat, &material );

	view->lpVP->lpVtbl->GetDirect3DViewport( view->lpVP, &imview1 );
	imview1->lpVtbl->QueryInterface( imview1, &IID_IDirect3DViewport3, &imview );
	
	imview1->lpVtbl->SetBackground( imview1, handle );

}

lpMesh Container_GetMesh( lpContainer cont )
{
	return Container_GetMesh2(cont->masterFrame);
}

lpMesh Container_GetMesh2( LPDIRECT3DRMFRAME3 frame)
{	
	LPUNKNOWN *visuals;
	ULONG visNum, numOfVisuals, numOfMeshes = 0;
	LPDIRECT3DRMUSERVISUAL userVisual;
	lpMesh mesh;

	
	frame->lpVtbl->GetVisuals( frame, &numOfVisuals, NULL );

	if( numOfVisuals )
	{	visuals = Mem_Alloc( sizeof(LPUNKNOWN) * numOfVisuals );
		frame->lpVtbl->GetVisuals( frame, &numOfVisuals, visuals );

		for( visNum = 0; visNum < numOfVisuals; visNum++ )
			if( D3DRM_OK == visuals[visNum]->lpVtbl->QueryInterface(visuals[visNum], &IID_IDirect3DRMUserVisual, (VOID**)&userVisual) )
				if( mesh = (lpMesh) userVisual->lpVtbl->GetAppData(userVisual) )
					numOfMeshes++;

		Mem_Free( visuals );

		if( numOfMeshes == 1 )
			return mesh;
		else if( numOfMeshes > 1 )
		{	Error_Warn( TRUE, "Container contains more than one mesh... returning last found." );
			return mesh;
		}

	}


	return NULL;

}

void Container_SetCallbackForPartName(lpContainer cont, int instance, LPUCHAR name, LPVOID renderCallback, LPVOID data)
{
LPUCHAR						partname;
lpMesh						transmesh;
int							count, l;
LPDIRECT3DRMFRAME3			*list;
Container_SearchData		search;

	if (!(partname = Container_FormatPartName(cont, name, &instance))) return;


	search.string			= partname;
	search.stringLen		= strlen(partname);
	search.caseSensitive	= FALSE;
	search.count			= 0;
	search.mode				= Container_SearchMode_FirstMatch;
	search.matchNumber		= 0;


	count = Container_GetActivities(cont, NULL, NULL, NULL);

	list = Mem_Alloc(count*sizeof(list[0]));

	count = Container_GetActivities(cont, list, NULL, NULL);


	for (l = 0 ; l < count ; l ++)
	{
		search.resultFrame		= NULL;

		Container_Frame_WalkTree(list[l], 0, Container_Frame_SearchCallback, &search);

//		Container_Frame_WalkTree(root->masterFrame, 0, Container_Frame_SearchCallback, &search);

		if (search.resultFrame != NULL)
		{
			if (transmesh = Container_GetMesh2(search.resultFrame))
			{
				transmesh->textureRenderCallback		= renderCallback;
				transmesh->textureRenderCallbackData	= data;
			}
		}
	}

	Mem_Free(list);
}


