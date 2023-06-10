
#include "Standard.h"
#include "Viewports.h"
#include "DirectX.h"
#include "Errors.h"
#include "Utils.h"
#include "UView.h"
#include "Files.h"
#include "Maths.h"
#include "Lists.h"
#include "Mesh.h"
#include "Mem.h"
#include "Lwo.h"
#include "Lws.h"

#define LWS_DEBUGBONEMESH

struct LwsGlobs {

	REAL staticDissolveLevel[LWS_MAXSTATICDISSOLVES];
	ULONG staticDissolveCount;

	BOOL (*addObjectCallback)(LPUCHAR command, LPUCHAR name, LPVOID data);
	LPVOID addObjectCallbackData;

	struct List *list;
	struct List *sharedObjectList;

} lwsGlobs = { 0.0f };

VOID Lws_Initialise(VOID) {

	lwsGlobs.list = List_Create(sizeof(struct Lws));
	lwsGlobs.sharedObjectList = File_CreateSharedObjectList();
}

VOID Lws_SetAddObjectCallback(BOOL (*addObjectCallback)(LPUCHAR command, LPUCHAR name, LPVOID data), LPVOID addObjectCallbackData) {

	lwsGlobs.addObjectCallback = addObjectCallback;
	lwsGlobs.addObjectCallbackData = addObjectCallbackData;
}

#ifdef _DEBUG
BOOL Lws_ShutdownCallback(lpLws lws, LPVOID data) {

	Error_Fatal(TRUE, Error_Format("Unremoved lws from \"%s\"", lws->filePath));

	return FALSE;
}
#endif // _DEBUG

VOID Lws_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(lwsGlobs.list, Lws_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(lwsGlobs.list);
	File_RemoveSharedObjectList(lwsGlobs.sharedObjectList);

}

static VOID Lws_FreeNode(lpLws lws, lpLwsNode node) {

	lpMesh mesh;
	lpFrame frame = lws->frameList[node->frameIndex];

	if (!(node->flags & LWSNODE_FLAG_NULL)) {
		if (mesh = Frame_GetMesh(frame)) {
			Mesh_Remove(mesh, TRUE);
		}
	}

	if (NULL == lws->clonedFrom && 0 == lws->referenceCount) {

		Mem_Free(node->keyList);

		if (node->dissolveCount > 1) {
			Mem_Free(node->dissolveLevel);
			Mem_Free(node->dissolveFrame);
		}

	}
}

static VOID Lws_FreeBone(lpLws lws, lpLwsBone bone) {

	if (NULL == lws->clonedFrom && 0 == lws->referenceCount) {

		Mem_Free(bone->keyList);

	}
}

VOID Lws_Remove(lpLws lws) {

	if (File_ReleaseSharedObject(lwsGlobs.sharedObjectList, lws)) {

		lpLws clonedFrom = lws->clonedFrom;
		lpLwsNode node;
		lpLwsBone bone;
		lpFrame frame;
		ULONG loop;

		lws->referenceCount--;

		if (0 == lws->referenceCount) {
		
			for (loop=0 ; loop<lws->nodeCount ; loop++) {
			
				node = &lws->nodeList[loop];

				Lws_FreeNode(lws, node);
			}

			for (loop=0 ; loop<lws->boneCount ; loop++) {
			
				bone = &lws->boneList[loop];

				Lws_FreeBone(lws, bone);
			}

			for (loop=0 ; loop<(ULONG) (lws->nodeCount + lws->boneCount) ; loop++) {

				frame = lws->frameList[loop];

				Frame_Remove(frame, FALSE);
			}

			if (NULL == clonedFrom) {
				Mem_Free(lws->nodeList);
				Mem_Free(lws->filePath);
			}

			Mem_Free(lws->frameList);
			if (lws->boneList) Mem_Free(lws->boneList);
			if (lws->boneMatrixList) Mem_Free(lws->boneMatrixList);

			List_ReturnItem(lwsGlobs.list, lws);
		}

		if (clonedFrom) Lws_Remove(clonedFrom);
	}
}

lpLws Lws_Load(LPUCHAR fname, lpFrame parentFrame, ULONG loadFlags, BOOL useShared) {

	lpFile ifp;
	lpLws scene = NULL;
	UCHAR filepath[FILE_MAXPATH], path[FILE_MAXPATH];
	BOOL looping = (LWSLOAD_FLAG_LOOPING == (loadFlags & LWSLOAD_FLAG_LOOPING));
	BOOL useNormals = (LWSLOAD_FLAG_USENORMALS == (loadFlags & LWSLOAD_FLAG_USENORMALS));
	BOOL addCamera = (LWSLOAD_FLAG_ADDCAMERA == (loadFlags & LWSLOAD_FLAG_ADDCAMERA));
	BOOL addLights = (LWSLOAD_FLAG_ADDLIGHTS == (loadFlags & LWSLOAD_FLAG_ADDLIGHTS));
	BOOL optimise = (LWSLOAD_FLAG_OPTIMISE == (loadFlags & LWSLOAD_FLAG_OPTIMISE));

	{
		ULONG flen = strlen(fname);
		ULONG slen = strlen(LWS_FILESUFFIX);
		if (flen < slen || 0 != stricmp(&fname[flen-slen], LWS_FILESUFFIX)) sprintf(filepath, "%s%s", fname, LWS_FILESUFFIX);
		else strcpy(filepath, fname);
	}

	if (useShared && (scene = File_FindSharedObject(lwsGlobs.sharedObjectList, filepath))) {
		return Lws_Clone(scene, parentFrame);
	}

	if (ifp = File_Open(filepath, "r")) {

		UCHAR line[LWS_MAXLINELEN];
		UCHAR lineSplit[LWS_MAXLINELEN];
		UWORD length;

		File_GetLine(line, sizeof(line), ifp);
		length = strlen(line) + 1;
		File_GetLine(&line[length], sizeof(line) - length, ifp);

		if (0 == strcmp(line, LWS_HEADER1) && 0 == strcmp(&line[length], LWS_HEADER2)) {

			LPUCHAR argv[LWS_MAXARGS];
			SLONG argc, loop;
			SLONG motionMode = 0, dissolveMode = 0, boneMotionMode = 0;
			lpLwsBone currBone = NULL;
			lpLwsNode currNode = NULL;
			lpLwsNodeSetupInfo currNodeSetup = NULL, parent;
			ULONG nodeBoneIndex;
			LPUWORD parentList = NULL;
			LPULONG boneParentList = NULL;
			LPUCHAR s, t;
			LPUWORD keyCount;
			lpLwsKeyInfo *keyList;

			strcpy(path, filepath);
			for (s=t=path ; '\0'!=*s ; s++) if ('\\' == *s) t = s;
//			*(t+(t==path?0:1)) = '\0';
			*t = '\0';

//			scene = Mem_AllocClear(sizeof(*scene));
			scene = List_ObtainItem(lwsGlobs.list);
			if ('\0' != path[0]) scene->filePath = Mem_CopyString(path);
			else scene->filePath = NULL;

//			scene->nodeListSize = LWS_BLOCKSIZE;
			scene->referenceCount = 1;
			if (looping) scene->flags |= LWS_FLAG_LOOPING;

			scene->cameraNodeIndex = -1;

//			scene->nodeList = Mem_AllocClear(sizeof(Lws_Node) * scene->nodeListSize);
//			scene->nodeSetupList = Mem_AllocClear(sizeof(Lws_NodeSetupInfo) * scene->nodeListSize);
//			parentList = Mem_Alloc(sizeof(UWORD) * scene->nodeListSize);

			while (File_GetLine(line, sizeof(line), ifp)){
				strcpy(lineSplit, line);
				if (argc = Util_WSTokenise(lineSplit, argv, LWS_MAXARGS, FALSE)) {
					if (NULL == currNode) {
						if (0 == strcmp("PreviewFirstFrame", argv[0])) scene->firstFrame = atoi(argv[1]);
						if (0 == strcmp("PreviewLastFrame", argv[0])) scene->lastFrame = atoi(argv[1]);
						if (0 == strcmp("FramesPerSecond", argv[0])) scene->fps = (REAL) atof(argv[1]);

						if (0 == strcmp("AddNullObject", argv[0]) ||
							0 == strcmp("LoadObject", argv[0]) ||
							(addCamera && 0 == strcmp("ShowCamera", argv[0])) ||
							(addLights && 0 == strcmp("AddLight", argv[0]))) {

							if (NULL == lwsGlobs.addObjectCallback || lwsGlobs.addObjectCallback(argv[0], argv[1], lwsGlobs.addObjectCallbackData)) {

								if (scene->nodeCount == scene->nodeListSize) {
									ULONG oldSize = scene->nodeListSize;
									scene->nodeListSize += LWS_BLOCKSIZE;
									scene->nodeList = Mem_ReAllocClear(scene->nodeList, sizeof(scene->nodeList[0]) * scene->nodeListSize);
									scene->nodeSetupList = Mem_ReAllocClear(scene->nodeSetupList, sizeof(scene->nodeSetupList[0]) * scene->nodeListSize);
									parentList = Mem_ReAllocClear(parentList, sizeof(UWORD) * scene->nodeListSize);
								}

								parentList[scene->nodeCount] = 0;
								currNode = &scene->nodeList[scene->nodeCount];
								currNodeSetup = &scene->nodeSetupList[scene->nodeCount];
								Mem_Set(currNode, 0, sizeof(*currNode));

								if (0 == strcmp("AddNullObject", argv[0])) {
									currNode->flags |= LWSNODE_FLAG_NULL;
									currNodeSetup->name = Mem_CopyString(&line[strlen("AddNullObject") + 1]);
									if (0 == strnicmp(currNodeSetup->name, LWS_SOUNDTRIGGERPREFIX, strlen(LWS_SOUNDTRIGGERPREFIX)) &&
										0 == strnicmp(&currNodeSetup->name[strlen(LWS_SOUNDTRIGGERPREFIX)], LWS_SOUNDTRIGGERSEPERATOR, strlen(LWS_SOUNDTRIGGERSEPERATOR))){
										currNode->flags |= LWSNODE_FLAG_SOUNDTRIGGER;
										Error_Fatal(scene->triggerCount == 256, "Too many sound trigger frames");
										scene->triggerCount++;
									}

								} else if (0 == strcmp("ShowCamera", argv[0])) {

									Error_Fatal(-1 != scene->cameraNodeIndex, "Scene has more than one camera");
									currNode->flags |= (LWSNODE_FLAG_NULL|LWSNODE_FLAG_CAMERA);
									currNodeSetup->name = Mem_CopyString(LWS_CAMERANAME);
									scene->cameraNodeIndex = scene->nodeCount;

								} else if (0 == strcmp("AddLight", argv[0])) {

									currNode->flags |= (LWSNODE_FLAG_NULL|LWSNODE_FLAG_LIGHT);
									currNodeSetup->name = Mem_CopyString(LWS_LIGHTNAME);
	//								currNode->chainNext = scene->lightChain;
									scene->flags |= LWS_FLAG_HASLIGHT;

								} else {
									LPUCHAR lwoStr;
									strcpy(lineSplit, line);
									argc = Util_Tokenise(line, argv, LWS_MAXARGS, "\\", FALSE);
									if (lwoStr = Util_StrIStr(argv[argc-1], ".lwo")) lwoStr[0] = '\0';
									currNodeSetup->name = Mem_CopyString(argv[argc-1]);
								}

								for (loop=scene->nodeCount-1 ; loop>=0 ; loop--) {
									if (((scene->nodeList[loop].flags & LWSNODE_FLAG_NULL) && (currNode->flags & LWSNODE_FLAG_NULL)) ||
										(!(scene->nodeList[loop].flags & LWSNODE_FLAG_NULL) && !(currNode->flags & LWSNODE_FLAG_NULL))) {

										if (0 == strcmp(currNodeSetup->name, scene->nodeSetupList[loop].name)) {
											currNodeSetup->reference = scene->nodeSetupList[loop].reference + 1;
											break;
										}
									}
								}
							}
						}
					} else if (motionMode) {

						// argv[1] is the first item as there is some white space at ther start of the line...

						if (1 == motionMode) {
							Error_Fatal(9 != atoi(argv[1]), "Scene file error");
						} else if (2 == motionMode) {
							(*keyCount) = atoi(argv[1]);
							(*keyList) = Mem_Alloc(sizeof((*keyList)[0]) * ((*keyCount) + 1));
						} else {
							UWORD key = (motionMode - 3) / 2;
							if (key < (*keyCount)) {
								if (motionMode % 2) {
									(*keyList)[key].position.x = (REAL) atof(argv[1]);
									(*keyList)[key].position.y = (REAL) atof(argv[2]);
									(*keyList)[key].position.z = (REAL) atof(argv[3]);
									(*keyList)[key].hpb.x = ((REAL) atof(argv[4]) / 180.0f) * M_PI;
									(*keyList)[key].hpb.y = ((REAL) atof(argv[5]) / 180.0f) * M_PI;
									(*keyList)[key].hpb.z = ((REAL) atof(argv[6]) / 180.0f) * M_PI;
									(*keyList)[key].scale.x = (REAL) atof(argv[7]);
									(*keyList)[key].scale.y = (REAL) atof(argv[8]);
									(*keyList)[key].scale.z = (REAL) atof(argv[9]);
								} else {
									(*keyList)[key].frame = atoi(argv[1]);
									(*keyList)[key].tension = (REAL) atof(argv[3]);
								}
							}
						}

						motionMode++;

						if (0 == strcmp(argv[0], "EndBehavior")) {
							keyList = NULL;
							keyCount = NULL;
							motionMode = 0;
						}

					} else if (dissolveMode) {

						// argv[1] is the first item as there is some white space at ther start of the line...

						if (1 == dissolveMode) {
							Error_Fatal(1 != atoi(argv[1]), "Scene file error");
						} else if (2 == dissolveMode) {
							currNode->dissolveCount = atoi(argv[1]);
							currNode->dissolveLevel = Mem_Alloc(sizeof(currNode->dissolveLevel[0]) * (currNode->dissolveCount + 1));
							currNode->dissolveFrame = Mem_Alloc(sizeof(currNode->dissolveFrame[0]) * (currNode->dissolveCount + 1));
						} else {

							UWORD key = (dissolveMode - 3) / 2;
							if (key < currNode->dissolveCount) {
								if (dissolveMode % 2) {
									currNode->dissolveLevel[key] = (REAL) atof(argv[1]);
									if (currNode->dissolveLevel[key] < 0.0f) currNode->dissolveLevel[key] = 0.0f;
									if (currNode->dissolveLevel[key] > 1.0f) currNode->dissolveLevel[key] = 1.0f;
									currNode->dissolveLevel[key] = 1.0f - currNode->dissolveLevel[key];
								} else currNode->dissolveFrame[key] = atoi(argv[1]);
							}
						}

						dissolveMode++;

						if (0 == strcmp(argv[0], "EndBehavior")) dissolveMode = 0;

					} else {

						if (0 == strcmp(argv[0], "AddBone")) {

							lpLwsBone prev;

/*							if (scene->boneCount == scene->boneListSize) {
								ULONG oldSize = scene->boneListSize;
								scene->boneListSize += LWS_BLOCKSIZE;
								scene->boneList = Mem_ReAllocClear(scene->boneList, sizeof(scene->boneList[0]) * scene->boneListSize);
								boneParentList = Mem_ReAllocClear(boneParentList, sizeof(boneParentList[0]) * scene->boneListSize);
							}
*/
							Error_Overflow(scene->boneCount, LWS_MAXBONES);

							if (NULL == scene->boneList) {
								scene->boneList = Mem_AllocClear(sizeof(scene->boneList[0]) * LWS_MAXBONES);
								boneParentList = Mem_AllocClear(sizeof(boneParentList[0]) * LWS_MAXBONES);
							}

							currBone = &scene->boneList[scene->boneCount];

							if (prev = currNode->boneList) {
								while (prev->next) prev = prev->next;
								prev->next = currBone;
							} else {
								currNode->boneList = currBone;
								nodeBoneIndex = scene->boneCount;
							}

							scene->boneCount++;

						} else if (0 == strcmp(argv[0], "BoneActive")) {
							if (atoi(argv[1])) currBone->flags |= LWSBONE_FLAG_ACTIVE;
						} else if (0 == strcmp(argv[0], "BoneRestPosition")) {
							Error_Fatal(4!=argc, "Scene file");
							currBone->restPosition.x = (REAL) atof(argv[1]);
							currBone->restPosition.y = (REAL) atof(argv[2]);
							currBone->restPosition.z = (REAL) atof(argv[3]);
						} else if (0 == strcmp(argv[0], "BoneRestDirection")) {
							Error_Fatal(4!=argc, "Scene file");
							currBone->restDirection.x = ((REAL) atof(argv[1]) / 180.0f) * M_PI;
							currBone->restDirection.y = ((REAL) atof(argv[2]) / 180.0f) * M_PI;
							currBone->restDirection.z = ((REAL) atof(argv[3]) / 180.0f) * M_PI;
						} else if (0 == strcmp(argv[0], "BoneRestLength")) {
							Error_Fatal(2!=argc, "Scene file");
							currBone->restLength = (REAL) atof(argv[1]);
						} else if (0 == strcmp(argv[0], "ScaleBoneStrength")) {
							if (atoi(argv[1])) currBone->flags |= LWSBONE_FLAG_SCALESTRENGTH;
						} else if (0 == strcmp(argv[1], "BoneStrength")) {
							Error_Fatal(2!=argc, "Scene file");
							currBone->strength = (REAL) atof(argv[1]);
						} else if (0 == strcmp(argv[0], "BoneMotion")) {
							Error_Fatal(2!=argc, "Scene file");
							keyList = &currBone->keyList;
							keyCount = &currBone->keyCount;
							motionMode = 1;

						} else if (0 == strcmp(argv[0], "BoneFalloffType")) {
							Error_Fatal(2!=argc, "Scene file");
							switch (atol(argv[1])) {
							case 1: currNode->boneFalloffPower = 1.0f; break;
							case 2: currNode->boneFalloffPower = 2.0f; break;
							case 3: currNode->boneFalloffPower = 4.0f; break;
							case 4: currNode->boneFalloffPower = 8.0f; break;
							case 5: currNode->boneFalloffPower = 16.0f; break;
							default: Error_Fatal(TRUE, "Unknown BoneFalloffType");
							}

						} else if (0 == strcmp(argv[0], "CameraMotion") && (currNode->flags & LWSNODE_FLAG_CAMERA)) {
							keyList = &currNode->keyList;
							keyCount = &currNode->keyCount;
							motionMode = 1;
						} else if (0 == strcmp(argv[0], "ZoomFactor") && (currNode->flags & LWSNODE_FLAG_CAMERA)) scene->cameraZoom = (REAL) atof(argv[1]);

						else if (0 == strcmp(argv[0], "LightMotion") && (currNode->flags & LWSNODE_FLAG_LIGHT)) {
							keyList = &currNode->keyList;
							keyCount = &currNode->keyCount;
							motionMode = 1;
						} else if (0 == strcmp(argv[0], "LightColor"))	currNodeSetup->lightColour = COLOUR_FROMCHAR(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
						else if (0 == strcmp(argv[0], "LgtIntensity"))	currNodeSetup->lightIntensity = (REAL) atof(argv[1]);
						else if (0 == strcmp(argv[0], "LightType"))		currNodeSetup->lightType = atoi(argv[1]);
						else if (0 == strcmp(argv[0], "LightFalloff"))	currNodeSetup->lightFalloff = atoi(argv[1]);
						else if (0 == strcmp(argv[0], "LightRange"))	currNodeSetup->lightRange = (REAL) atof(argv[1]);
						else if (0 == strcmp(argv[0], "ConeAngle"))		currNodeSetup->lightConeAngle = (REAL) atof(argv[1]);
						else if (0 == strcmp(argv[0], "EdgeAngle"))		currNodeSetup->lightEdgeAngle = (REAL) atof(argv[1]);

						else if (0 == strcmp(argv[0], "ObjectMotion")) {
							keyList = &currNode->keyList;
							keyCount = &currNode->keyCount;
							motionMode = 1;
						} else if (0 == strcmp(argv[0], "ObjDissolve")) {
							if (0 == strcmp(argv[1], "(envelope)")) dissolveMode = 1;
							else {
								Error_Fatal(LWS_MAXSTATICDISSOLVES==lwsGlobs.staticDissolveCount, "LWS_MAXSTATICDISSOLVES too small");
								lwsGlobs.staticDissolveLevel[lwsGlobs.staticDissolveCount] = (REAL) atof(argv[1]);
								currNode->dissolveLevel = &lwsGlobs.staticDissolveLevel[lwsGlobs.staticDissolveCount];
								lwsGlobs.staticDissolveCount++;
//								currNode->dissolveLevel = 0;
							}
						} else if (0 == strcmp(argv[0], "ParentObject")) {
							if (currNode->boneList) boneParentList[scene->boneCount-1] = nodeBoneIndex + atoi(argv[1]);
							else parentList[scene->nodeCount] = atoi(argv[1]);
						} else if (0 == strcmp(argv[0], "PivotPoint")) {
							currNode->pivotVector.x = (REAL) -atof(argv[1]);
							currNode->pivotVector.y = (REAL) -atof(argv[2]);
							currNode->pivotVector.z = (REAL) -atof(argv[3]);
//						} else if (0 == strcmp(argv[0], "UnseenByCamera") && 1 == atoi(argv[1])) {
//							currNode->flags |= LWSNODE_FLAG_FACECAMERA;
						}
					}
				} else if (NULL != currNode) {
					currNode = NULL;
					currNodeSetup = NULL;
					scene->nodeCount++;
				}
			}

			// ReAlloc the node list to the correct length (leave the setup list as it will most probably be thrown away).
			scene->nodeListSize = scene->nodeCount;
			scene->nodeList = Mem_ReAlloc(scene->nodeList, sizeof(scene->nodeList[0]) * scene->nodeListSize);

			// Same for the bone list...
//			scene->boneListSize = scene->boneCount;
//			scene->boneList = Mem_ReAlloc(scene->boneList, sizeof(scene->boneList[0]) * scene->boneListSize);

			{
				lpLwsBone bone;

				for (loop=0 ; loop<scene->boneCount ; loop++) {

					bone = &scene->boneList[loop];

					if (1 != bone->keyCount && bone->keyList[bone->keyCount-1].frame < scene->lastFrame) {
						bone->keyList[bone->keyCount] = bone->keyList[bone->keyCount-1];
						bone->keyList[bone->keyCount].frame = scene->lastFrame;
						bone->keyCount++;
					}
				}
			}

			for (loop=0 ; loop<(SLONG)scene->nodeCount ; loop++) {

				currNode = &scene->nodeList[loop];
				currNodeSetup = &scene->nodeSetupList[loop];

				currNodeSetup->node = currNode;		// Link the two list together...

				// If there is more than one key and the last one is before the end of the animation
				// then create a duplicate of the last one at the end.
				// The arrays are over allocated by one to ensure that there is enough space.
				
				if (1 != currNode->keyCount && currNode->keyList[currNode->keyCount-1].frame < scene->lastFrame) {
					currNode->keyList[currNode->keyCount] = currNode->keyList[currNode->keyCount-1];
					currNode->keyList[currNode->keyCount].frame = scene->lastFrame;
					currNode->keyCount++;
				}

				// Do the same for the dissolve level (assume that if an envelope is defined, more than one key
				// will be used)...

				if (currNode->dissolveCount) {
					if (currNode->dissolveFrame[currNode->dissolveCount-1] < scene->lastFrame) {
						currNode->dissolveFrame[currNode->dissolveCount] = scene->lastFrame;
						currNode->dissolveLevel[currNode->dissolveCount] = currNode->dissolveLevel[currNode->dissolveCount-1];
						currNode->dissolveCount++;
					}
				}
			}

			// Link the hierarchy from the node and parent lists...
			// New links are added to the front of the list, so reverse through the array to preserve the order...

			for (loop=scene->nodeCount-1 ; loop>=0 ; loop--) {
				currNode = &scene->nodeList[loop];
				currNodeSetup = &scene->nodeSetupList[loop];
				if (parentList[loop]) {
					parent = &scene->nodeSetupList[parentList[loop] - 1];
					currNodeSetup->next = parent->childList;
					parent->childList = currNodeSetup;
				} else {
					currNodeSetup->next = scene->masterNodeSetup;
					scene->masterNodeSetup = currNodeSetup;
				}
			}

			// Allocate a list for all the frames required in the scene (simplifies cloning).
			scene->frameList = Mem_Alloc(sizeof(scene->frameList[0]) * (scene->nodeCount + scene->boneCount));
			if (scene->boneCount) scene->boneMatrixList = Mem_Alloc(sizeof(scene->boneMatrixList[0]) * scene->boneCount);

			Lws_SetupSoundTriggers(scene);
			Lws_SetupFrames(scene, parentFrame);
			Lws_LoadMeshes(scene, useNormals, optimise);
			Lws_SetupBones(scene, parentFrame, boneParentList);

			Mem_Free(parentList);
			if (boneParentList) Mem_Free(boneParentList);

			Lws_SetTime(scene, 0.0f);

			if (useShared) File_RegisterSharedObject(lwsGlobs.sharedObjectList, filepath, scene);

		} else Error_Fatal(TRUE, "Invalid scene file");

		File_Close(ifp);
	}

	return scene;
}

VOID Lws_SetBoneTransforms(lpLws scene, lpLwsBone firstChild, LPULONG count) {

	lpLwsBone bone;
	D3DTRANSFORMSTATETYPE transformType;
	LPD3DMATRIX m;

	for (bone=firstChild ; bone ; bone=bone->nextSibling) {
		
		switch (bone->blendIndex) {
		case 0: transformType = D3DTRANSFORMSTATE_WORLD;	break;
		case 1: transformType = D3DTRANSFORMSTATE_WORLD1;	break;
		case 2: transformType = D3DTRANSFORMSTATE_WORLD2;	break;
		case 3: transformType = D3DTRANSFORMSTATE_WORLD3;	break;
		default: Error_Fatal(TRUE, "Blend index out of range");
		}

		m = Maths_GetD3DMATRIX(scene->boneMatrixList[bone->index]);
		DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), transformType, m);

		Lws_SetBoneTransforms(scene, bone->children, count);

		(*count)++;
	}
}

/*
ULONG Lws_SetBoneMatrices(lpLws scene, lpLwsBone firstChild, LPVECTOR3D restPos, LPVECTOR3D restDir) {

	/////////////////////////////////////////////////////////////
	//// Move the matrix generation to the SetTime() function...
	/////////////////////////////////////////////////////////////

	lpLwsBone bone;
	D3DTRANSFORMSTATETYPE transformType;
	MATRIX4D mat, offsetMatrix, boneMatrix;
	LPD3DMATRIX m;
	ULONG count = 0;

	for (bone=firstChild ; bone ; bone=bone->nextSibling) {

		VECTOR3D restPosition = { -bone->restPosition.x, -bone->restPosition.y, -bone->restPosition.z };
		VECTOR3D restDirection = { -bone->restDirection.x, -bone->restDirection.y, -bone->restDirection.z };
		VECTOR3D scale = { 1.0f, 1.0f, 1.0f }, pivot = { 0.0f, 0.0f, 0.0f };

		if (restPos) Maths_Vector3DSubtract(&restPosition, &restPosition, restPos);
		if (restDir) Maths_Vector3DSubtract(&restDirection, &restDirection, restDir);

		Lws_GenerateMatrix(offsetMatrix, &restPosition, &restDirection, &scale, &pivot);
		
		switch (bone->blendIndex) {
		case 0: transformType = D3DTRANSFORMSTATE_WORLD;	break;
		case 1: transformType = D3DTRANSFORMSTATE_WORLD1;	break;
		case 2: transformType = D3DTRANSFORMSTATE_WORLD2;	break;
		case 3: transformType = D3DTRANSFORMSTATE_WORLD3;	break;
		default: Error_Fatal(TRUE, "Blend index out of range");
		}

		Frame_GetWorldTransform(Lws_GetBoneFrame(scene, bone), mat);

		Maths_MultiplyMatrix(boneMatrix, offsetMatrix, mat);

		m = Maths_GetD3DMATRIX(boneMatrix);
		DirectX_Device()->lpVtbl->SetTransform(DirectX_Device(), transformType, m);

		count++;
		count += Lws_SetBoneMatrices(scene, bone->children, &bone->restPosition, &bone->restDirection);
	}

	return count;
}
*/

#ifdef _DEBUG
//#define _RGL_BONEDUMP
#endif // _DEBUG

static BOOL Lws_LoadPGLFile(lpLws lws, lpLwsNode node, lpLwsNodeSetupInfo nodeSetup) {

	lpFile fp;
	UCHAR line[1024], pglfname[FILE_MAXPATH];
	BOOL vertexMode = FALSE, result = FALSE;
	ULONG loop, count, boneIndex, boneCount;
	ULONG vertexListIndex;
	VECTOR3D vertexPos;
	lpLwsBone bone;
	lpMesh mesh;

	mesh = Frame_GetMesh(lws->frameList[node->frameIndex]);

	sprintf(pglfname, "%s\\%s.pgl", lws->filePath, nodeSetup->name);

	if (fp = File_Open(pglfname, "r")) {

		count = 0;
		boneCount = 0;

		for (bone=node->boneList ; bone ; bone=bone->next) bone->blendIndex = boneCount++;

		Mesh_LockVertices(mesh, TRUE);

		while (File_GetLine(line, sizeof(line), fp)) {
			if ('#' != line[0] && '\0' != line[0]) {

				if (vertexMode) {

					LPUCHAR argv[10];
					ULONG argc;

					argc = Util_WSTokenise(line, argv, sizeof(argv) / sizeof(argv[0]), TRUE);
					Error_Fatal(4 != argc, Error_Format("Invalid PGL file \"%s\"", pglfname));
					boneIndex = atol(argv[0]) - 1;
					argc = Util_Tokenise(argv[3], argv, sizeof(argv) / sizeof(argv[0]), ",", TRUE);
					Error_Fatal(3 != argc, Error_Format("Invalid PGL file \"%s\"", pglfname));
					vertexPos.x = (REAL) atof(argv[0]);
					vertexPos.y = (REAL) atof(argv[1]);
					vertexPos.z = (REAL) atof(argv[2]);

					if (boneIndex < (boneCount - 1)) {
						for (vertexListIndex=0 ; vertexListIndex<Mesh_GetVertexListCount(mesh) ; vertexListIndex++) {
							for (loop=0 ; loop<Mesh_GetVertexCount(mesh, vertexListIndex) ; loop++) {
								if (UView_PositionEqual(&vertexPos, Mesh_GetVertexPosition(mesh, vertexListIndex, loop), 0.0001f)) {
									Mesh_SetBlendLevel(mesh, vertexListIndex, loop, boneIndex, 1.0f);
								}
							}
						}
					}

					count++;
	
				} else {

					count++;

					switch (count) {
					case 1: Error_Fatal(0 != stricmp(line, "PGLFILE"), Error_Format("Invalid PGL file \"%s\"", pglfname));	break;
					case 2: break;
					case 3: break;
					case 4: Error_Fatal((ULONG) atol(line) != boneCount, Error_Format("Invalid PGL file \"%s\", incorrect bone count", pglfname)); break;
					case 5: count = 0; vertexMode = TRUE; result = TRUE; break;
					}
				}
			}
		}

		Mesh_LockVertices(mesh, FALSE);

		File_Close(fp);
	}

	return result;
}

static VOID Lws_BuildBoneInfluenceList(lpLws scene, lpFrame rootFrame, lpLwsNode node) {

	VECTOR3D bonePos, boneEnd, vertexPos, /*meshOrigin, */restOffset;
	ULONG vertexCount, vertex;
	lpLwsBone bone;
	lpMesh mesh;
	REAL dist, minDist = MAX_REAL, maxDist = 0.0f;
	lpFrame boneFrame;
	LPREAL lastInfluenceList;
	REAL level, power;
	ULONG blendIndex;
	ULONG vertexListIndex;

	mesh = Frame_GetMesh(scene->frameList[node->frameIndex]);

	Mesh_LockVertices(mesh, TRUE);

	for (vertexListIndex=0 ; vertexListIndex<Mesh_GetVertexListCount(mesh) ; vertexListIndex++) {

		vertexCount = Mesh_GetVertexCount(mesh, vertexListIndex);
		lastInfluenceList = Mem_Alloc(sizeof(lastInfluenceList[0]) * vertexCount);
		blendIndex = 0;

		for (bone=node->boneList ; bone ; bone=bone->next) {

			boneFrame = Lws_GetBoneFrame(scene, bone);

			bone->blendIndex = blendIndex++;

			restOffset.x = 0.0f;
			restOffset.y = 0.0f;
			restOffset.z = bone->restLength;
				
			Frame_GetRelativePosition(boneFrame, rootFrame, &bonePos);
			Frame_GetRelativeOffset(boneFrame, rootFrame, &boneEnd, &restOffset);

			for (vertex=0 ; vertex<vertexCount ; vertex++) {

				Frame_GetRelativeOffset(scene->frameList[node->frameIndex], rootFrame, &vertexPos, Mesh_GetVertexPosition(mesh, vertexListIndex, vertex));

				dist = Maths_PointLineDistance(&vertexPos, &bonePos, &boneEnd);

				if (NULL == bone->next) lastInfluenceList[vertex] = dist;
				else Mesh_SetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex, dist);

				minDist = min(dist, minDist);
				maxDist = max(dist, maxDist);

			}
		}

		// minDist and maxDist are the minimum and maximum distances from any of the bones to any of the vertices in the mesh.
		dist = (minDist + maxDist) / 2.0f;
		dist = Maths_Power(dist, node->boneFalloffPower);

		for (bone=node->boneList ; bone ; bone=bone->next) {
			
			for (vertex=0 ; vertex<vertexCount ; vertex++) {			

				if (NULL == bone->next) {
					power = Maths_Power(lastInfluenceList[vertex], node->boneFalloffPower);
					lastInfluenceList[vertex] = dist / power;
				} else {
					level = Mesh_GetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex);
					power = Maths_Power(level, node->boneFalloffPower);
					Mesh_SetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex, dist / power);
				}
			}
		}

		for (vertex=0 ; vertex<vertexCount ; vertex++) {
		
			REAL total = lastInfluenceList[vertex];
		
			for (bone=node->boneList ; bone->next ; bone=bone->next) {
				total += Mesh_GetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex);
			}

			for (bone=node->boneList ; bone->next ; bone=bone->next) {
				level = Mesh_GetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex);
				Mesh_SetBlendLevel(mesh, vertexListIndex, vertex, bone->blendIndex, level / total);
			}

		}

		Mem_Free(lastInfluenceList);
	}

	Mesh_LockVertices(mesh, FALSE);
}

lpFrame Lws_FindFrame(lpLws lws, LPUCHAR name, ULONG instance) {

	UCHAR frameName[1024];
	ULONG loop;

	sprintf(frameName, "%s_%0.2d", name, instance);

	for (loop=0 ; loop<lws->nodeCount ; loop++) {
		if (0 == stricmp(frameName, Frame_GetName(lws->frameList[loop]))) return lws->frameList[loop];
	}

	return NULL;
}

lpFrame Lws_FindFrame2(lpLws lws, LPUCHAR name, ULONG compareLength, ULONG occurance) {

	ULONG loop, count = 0;

	for (loop=0 ; loop<lws->nodeCount ; loop++) {

		if (0 == strncmp(Frame_GetName(lws->frameList[loop]), name, compareLength)) {
			if (count++ == occurance) {
				return lws->frameList[loop];
			}
		}
	}

	return NULL;
}


#ifdef LWS_DEBUGBONEMESH
extern lpMesh debugBoneMesh;
#endif LWS_DEBUGBONEMESH

__inline lpFrame Lws_GetBoneFrame(lpLws lws, lpLwsBone bone) {

	return lws->frameList[lws->nodeCount + bone->index];
}

static VOID Lws_SetupBones(lpLws scene, lpFrame rootFrame, LPULONG parentList) {

	ULONG loop, index, reLinkIndex;
	lpLwsNode currNode;
	lpLwsNodeSetupInfo currNodeSetup;
	lpLwsBone boneList, bone, next;
	lpFrame frame, parent;
	VECTOR3D pivotVector = { 0.0f, 0.0f, 0.0f };
	VECTOR3D scale = { 1.0f, 1.0f, 1.0f };
	MATRIX4D m;

	// Create an array of frames for the bones...
	for (loop=0 ; loop<scene->boneCount ; loop++) {
		bone = &scene->boneList[loop];
		bone->index = loop;
		scene->frameList[scene->nodeCount + bone->index] = Frame_Create(NULL);
	}

	// Link the frames up into the scene hierarchy...
	reLinkIndex = index = 0;
	for (loop=0 ; loop<scene->nodeCount ; loop++) {			// Run through the nodes rather than the bones so that we know
															// which is the parent node of the root bone...
		currNode = &scene->nodeList[loop];
		currNodeSetup = &scene->nodeSetupList[loop];

		if (currNode->boneList) {
			for (bone=currNode->boneList ; bone ; bone=bone->next) {

				frame = Lws_GetBoneFrame(scene, bone);

				if (0 == parentList[index]) parent = scene->frameList[currNode->frameIndex];
				else parent = Lws_GetBoneFrame(scene, &scene->boneList[parentList[index]-1]);

				Frame_SetParent(frame, parent);
				
#ifdef LWS_DEBUGBONEMESH
				// Add the debug mesh...
				if (debugBoneMesh) Frame_SetMesh(frame, Mesh_Clone(debugBoneMesh, MESH_CLONEFLAG_TRANSFORMEDVERTICES));
#endif LWS_DEBUGBONEMESH

//				Lws_SetAbsoluteKey(frame, bone->keyList, 0, &pivotVector);

				// Let each bone know which frame/mesh it is part of...
				bone->rootFrameIndex = currNode->frameIndex;

				// Set the initial transformation of the bone to its rest position.
				Lws_GenerateMatrix(m, &bone->restPosition, &bone->restDirection, &scale, &pivotVector);
				Frame_SetTransform(Lws_GetBoneFrame(scene, bone), m);

				index++;
			}

			if (!Lws_LoadPGLFile(scene, currNode, currNodeSetup)) {
				Lws_BuildBoneInfluenceList(scene, rootFrame, currNode);
			}

			// Build the bone hierarchy structure (Trashing the existing linear linked list in the process)...

			boneList = currNode->boneList;
			currNode->boneList = NULL;

			for (bone=boneList ; bone ; bone=next) {

				next = bone->next;

				if (parentList[reLinkIndex]) {
					bone->nextSibling = scene->boneList[parentList[reLinkIndex] - 1].children;
					scene->boneList[parentList[reLinkIndex] - 1].children = bone;
				} else {
					bone->nextSibling = currNode->boneList;
					currNode->boneList = bone;
				}

				reLinkIndex++;
			}

			Mesh_SetBoneList(Frame_GetMesh(scene->frameList[currNode->frameIndex]), scene, currNode->boneList);

			{
				MATRIX4D identity;
				Maths_IdentityMatrix(identity);
				Lws_SetupRestMatrices2(scene, currNode->boneList, identity);
			}
		}
	}
}

static VOID Lws_SetupFrames(lpLws scene, lpFrame parent) {

	lpLwsNodeSetupInfo root;
	UWORD frameCount = 0;
//	ULONG loop;

	for (root=scene->masterNodeSetup ; root ; root=root->next) {
		Lws_CreateFrames(scene, root, parent, &frameCount);
	}

//	for (loop=0 ; loop<scene->nodeCount ; loop++) {
//		Frame_IdentityCheck(scene->frameList[loop]);
//	}
}

ULONG Lws_GetFrameCount(lpLws scene) {

	return scene->lastFrame;
}

lpFrame Lws_GetCamera(lpLws scene, LPREAL fov) {

	Error_Fatal(NULL==scene->frameList, "Lws_LoadMeshes() must be called before the camera frame is created.");

	if (-1 != scene->cameraNodeIndex) {
		if (fov) *fov = Maths_ATan(1.0f / scene->cameraZoom) * 2.0f;
		return scene->frameList[scene->nodeList[scene->cameraNodeIndex].frameIndex];
	} else return NULL;
}

static VOID Lws_SetupSoundTriggers(lpLws scene) {

	/*
	if (lwsGlobs.FindSFXIDFunc) {
//	if (lwsGlobs.FindSoundFunc) {
		lpLwsNode node;
		UCHAR line[LWS_MAXLINELEN];
		UWORD loop;
		ULONG argc, index;
		LPUCHAR argv[256];
		UCHAR triggerIndex = 0;
		lpLws_SoundTrigger st;

		if (scene->triggerCount) {
			scene->triggerList = Mem_Alloc(sizeof(Lws_SoundTrigger) * scene->triggerCount);
			for (loop=0 ; loop<scene->nodeCount ; loop++) {
				node = &scene->nodeList[loop];
				if (node->flags & LWSNODE_FLAG_SOUNDTRIGGER) {
					st = &scene->triggerList[triggerIndex];
					node->triggerIndex = triggerIndex;
					triggerIndex++;
					strcpy(line, node->name);
					argc = Util_Tokenise(line, argv, LWS_SOUNDTRIGGERSEPERATOR);
					st->count = (UWORD) argc - 2;
					Error_Fatal(st->count >= LWS_MAXTRIGGERKEYS, "LWS_MAXTRIGGERKEYS too small");
					Error_Fatal(0 == st->count, "No trigger frames specified");
					{
						BOOL result = lwsGlobs.FindSFXIDFunc(argv[1], &st->sfxID);
//						BOOL result = lwsGlobs.FindSoundFunc(argv[1], &st->sound);
						Error_Fatal(!result, Error_Format("Cannot match sound with %s", argv[1]));
					}
					for (index=0 ; index<st->count ; index++) {
						LPUCHAR end = strstr(argv[index+2], "-");
						st->frameStartList[index] = atoi(argv[index+2]);
						if (end) st->frameEndList[index] = atoi(&end[1]);
						else st->frameEndList[index] = st->frameStartList[index];
					}
				}
			}
		}
	} else scene->triggerCount = 0;

  */
}

static VOID Lws_LoadMeshes(lpLws scene, BOOL useNormals, BOOL optimise) {

	lpLwsNodeSetupInfo root;

	for (root=scene->masterNodeSetup ; root ; root=root->next) {
		Lws_LoadNodes(scene, root, useNormals, optimise);
	}
}

VOID Lws_EnableLights(lpLws scene, lpFrame enableFrame, lpViewport vp) {

	if (scene->flags & LWS_FLAG_HASLIGHT) {

		ULONG loop;
		lpLwsNode node;
		lpLight light;
		
		for (loop=0 ; loop<scene->nodeCount ; loop++) {
			node = &scene->nodeList[loop];

			if (node->flags & LWSNODE_FLAG_LIGHT) {
				light = scene->lightList[loop];
				Light_FrameEnable(light, enableFrame, TRUE, TRUE);
				Light_ViewportEnable(light, vp, TRUE);
			}
		}
	}
}

VOID Lws_CreateLights(lpLws scene) {

	if (scene->flags & LWS_FLAG_HASLIGHT) {

		ULONG loop;
		lpLwsNodeSetupInfo nodeSetup;
		lpLwsNode node;
		lpFrame frame;
		lpLight light;
		enum Light_Type type;
		NCOLOUR colour;
		
		Error_Fatal(NULL != scene->lightList, "Lights have already been created");

		scene->lightList = Mem_Alloc(sizeof(scene->lightList[0]) * scene->nodeCount);

		for (loop=0 ; loop<scene->nodeCount ; loop++) {
			nodeSetup = &scene->nodeSetupList[loop];
			node = &scene->nodeList[loop];
			frame = scene->frameList[loop];
			if (node->flags & LWSNODE_FLAG_LIGHT) {

				switch (nodeSetup->lightType) {
				case LwsLight_Distant:		type = LightType_Directional;		break;
				case LwsLight_Point:		type = LightType_Point;				break;
				case LwsLight_Spot:			type = LightType_Spot;				break;
				default: Error_Fatal(TRUE, "Unsupported light type");
				}

				colour.r = ((REAL) COLOUR_GETRED(nodeSetup->lightColour) / 255.0f) * nodeSetup->lightIntensity;
				colour.g = ((REAL) COLOUR_GETGREEN(nodeSetup->lightColour) / 255.0f) * nodeSetup->lightIntensity;
				colour.b = ((REAL) COLOUR_GETBLUE(nodeSetup->lightColour) / 255.0f) * nodeSetup->lightIntensity;

				light = Light_Create(frame, type);
				Light_SetDiffuse(light, &colour);
				if (LightType_Spot == type) Light_SetSpot(light, Maths_Deg2Rad((nodeSetup->lightConeAngle - nodeSetup->lightEdgeAngle) * 2.0f), Maths_Deg2Rad(nodeSetup->lightConeAngle * 2.0f), 1.0f);

				scene->lightList[loop] = light;
			}
		}
	}
}

static VOID Lws_CreateFrames(lpLws scene, lpLwsNodeSetupInfo nodeSetup, lpFrame parent, LPUWORD frameCount) {

	lpFrame frame;
	lpLwsNodeSetupInfo child;

	frame = Frame_Create(parent);
	scene->frameList[*frameCount] = frame;
	nodeSetup->node->frameIndex = *frameCount;
	(*frameCount)++;

	{
		UCHAR name[1024];
		LPUCHAR s;
		sprintf(name, "%s_%0.2i", nodeSetup->name, nodeSetup->reference);
		for (s=name ; '\0'!=*s ; s++) if (!isprint(*s)) *s = '_';
		Frame_SetName(frame, name);
	}

	for (child=nodeSetup->childList ; child ; child=child->next) {
		Lws_CreateFrames(scene, child, frame, frameCount);
	}
}

static VOID Lws_LoadNodes(lpLws scene, lpLwsNodeSetupInfo nodeSetup, BOOL useNormals, BOOL optimise) {

	lpFrame frame;
	lpLwsNodeSetupInfo child;
	lpMesh mesh;
	ULONG cloneFlags;
	BOOL original;
	ULONG boneCount = 0;
	lpLwsBone bone;

	for (bone=nodeSetup->node->boneList ; bone ; bone=bone->next) boneCount++;
	if (boneCount) boneCount--;

	frame = scene->frameList[nodeSetup->node->frameIndex];

	Lws_SetAbsoluteKey(scene->frameList[nodeSetup->node->frameIndex], nodeSetup->node->keyList, 0, &nodeSetup->node->pivotVector);

	if (!(nodeSetup->node->flags & LWSNODE_FLAG_NULL)) {

		UCHAR path[FILE_MAXPATH];
		if (scene->filePath) sprintf(path, "%s\\%s", scene->filePath, nodeSetup->name);
		else sprintf(path, "%s", nodeSetup->name);

		if (mesh = Mesh_Load(path, 0, boneCount, useNormals, TRUE, &original)) {

			if (optimise) Mesh_Optimise(mesh);

/*			{
				UWORD loop, vCount = Mesh_GetVertexCount(mesh, 0);
				REAL real[2] = { 0.0f, 1.0f };
				for (loop=0 ; loop<vCount ; loop++) {
					Mesh_SetVertexUV(mesh, 0, loop, real[rand()%2], real[rand()%2]);
				}
			}*/

//			Lwo_GenerateNormals(lwo);
//			mesh = Lwo_BuildMesh(lwo, LWS_MAXGROUPPOLYS);

//			if (nodeSetup->node->boneList) Frame_SetMesh(frame, Mesh_Clone(mesh, MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES));
//			else Frame_SetMesh(frame, mesh);

			if (original) {
				Frame_SetMesh(frame, mesh);
			} else {
				//if (nodeSetup->node->boneList) cloneFlags = MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES;
				//else cloneFlags = MESH_CLONEFLAG_TRANSFORMEDVERTICES;

				//Frame_SetMesh(frame, Mesh_Clone(mesh, cloneFlags));

				if (nodeSetup->node->boneList) {
					cloneFlags = MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES;
					Frame_SetMesh(frame, Mesh_Clone(mesh, cloneFlags));
				} else {
					Frame_SetMesh(frame, mesh);
				}

			}

//			if (node->flags & LWSNODE_FLAG_FACECAMERA) mesh->flags |= MESH_FLAG_FACECAMERA;
			if (NULL != nodeSetup->node->dissolveLevel && 0 == nodeSetup->node->dissolveCount) {
				Lws_SetDissolveLevel(scene, nodeSetup->node, nodeSetup->node->dissolveLevel[0]);
				nodeSetup->node->dissolveLevel = NULL;
			}
		}
	}

	for (child=nodeSetup->childList ; child ; child=child->next) {
		Lws_LoadNodes(scene, child, useNormals, optimise);
	}
}

VOID Lws_ClearSetup(lpLws scene) {

	ULONG loop;
	lpLwsNodeSetupInfo nodeSetup;

	if (scene->nodeSetupList) {
	
		for (loop=0 ; loop<scene->nodeCount ; loop++) {
			nodeSetup = &scene->nodeSetupList[loop];
			Mem_Free(nodeSetup->name);
		}

		Mem_Free(scene->nodeSetupList);
		scene->nodeSetupList = NULL;
	}
}

static VOID Lws_SetupRestMatrices2(lpLws scene, lpLwsBone firstBone, MATRIX4D parentMatrix) {

	lpLwsBone bone;
	MATRIX4D mat;
	VECTOR3D scale = { 1.0f, 1.0f, 1.0f };
	VECTOR3D pivot = { 0.0f, 0.0f, 0.0f };

	for (bone=firstBone ; bone ; bone=bone->nextSibling) {

//		Lws_GenerateRestMatrix(mat, &bone->restPosition, &bone->restDirection);
		Lws_GenerateMatrix(mat, &bone->restPosition, &bone->restDirection, &scale, &pivot);
		Maths_MultiplyMatrix(bone->restMatrix, mat, parentMatrix);

		Lws_SetupRestMatrices2(scene, bone->children, bone->restMatrix);
	}
}

static VOID Lws_UpdateBoneHierarchy2(lpLws scene, lpLwsBone firstBone) {

	lpLwsBone bone;
	MATRIX4D worldMatrix;
	MATRIX4D invRestMatrix;

	for (bone=firstBone; bone ; bone=bone->nextSibling) {

		Frame_GetWorldTransform(Lws_GetBoneFrame(scene, bone), worldMatrix);
		Maths_InvertMatrixQuick(invRestMatrix, bone->restMatrix);
		Maths_MultiplyMatrix(scene->boneMatrixList[bone->index], invRestMatrix, worldMatrix);

		Lws_UpdateBoneHierarchy2(scene, bone->children);
	}
}

static VOID Lws_SetBoneTime(lpLws scene, REAL time) {

	VECTOR3D pivotVector = { 0.0f, 0.0f, 0.0f };
	lpLwsBone bone;
	REAL delta;
	UWORD prev;
	ULONG loop;

	for (loop=0 ; loop<scene->boneCount ; loop++) {
		bone = &scene->boneList[loop];
		if (bone->keyCount > 1) {
			delta = Lws_FindPrevKey(bone->keyList, bone->keyCount, time, &prev);
			Lws_InterpolateKeys(Lws_GetBoneFrame(scene, bone), bone->keyList, prev, delta, &pivotVector);		
		}
	}

/*	{
		ULONG x, y;
		for (y=0 ; y<4 ; y++) {
			for (x=0 ; x<4 ; x++) {
				debugFrame->worldMatrix[x][y] = ((debugInfluenceFrame[0]->worldMatrix[x][y] * 4.0f) + debugInfluenceFrame[1]->worldMatrix[x][y]) / 5.0f;
			}
		}
	}*/
}

REAL Lws_GetTime(lpLws scene) {

	return scene->time;
}

lpLwsNode Lws_FindNode(lpLws scene, lpFrame frame) {

	ULONG loop;
	lpLwsNode node;

	for (loop=0 ; loop<scene->nodeCount ; loop++) {

		node = &scene->nodeList[loop];

		if (scene->frameList[node->frameIndex] == frame) {
			return node;
		}
	}

	return NULL;
}

REAL Lws_GetKeyInfo(lpLws scene, lpLwsNode node, REAL time, lpLwsKeyInfo *prevKey, lpLwsKeyInfo *nextKey) {
	
	UWORD prev;
	REAL delta = Lws_FindPrevKey(node->keyList, node->keyCount, time, &prev);

	if (prevKey) (*prevKey) = &node->keyList[prev];
	if (nextKey) (*nextKey) = &node->keyList[prev + 1];

	return delta;
}

VOID Lws_SetTime(lpLws scene, REAL time) {

	UWORD prev;
	UWORD loop;
	REAL delta;
	lpLwsNode node;

	scene->lastTime = scene->time;
	if (scene->flags & LWS_FLAG_LOOPING) scene->time = (REAL) fmod(time, (REAL) scene->lastFrame + M_EPSILON);
	else if (time > scene->lastFrame) scene->time = scene->lastFrame;
	else scene->time = time;

	Lws_SetBoneTime(scene, scene->time);

	for (loop=0 ; loop<scene->nodeCount ; loop++) {
		node = &scene->nodeList[loop];
		if (node->keyCount > 1) {
			delta = Lws_FindPrevKey(node->keyList, node->keyCount, scene->time, &prev);
			Lws_InterpolateKeys(scene->frameList[node->frameIndex], node->keyList, prev, delta, &node->pivotVector);
		}
		if (node->dissolveCount > 1) {
			delta = Lws_FindPrevDissolve(node, scene->time, &prev);
			Lws_InterpolateDissolve(scene, node, prev, delta);
		}

		if (node->boneList) Lws_UpdateBoneHierarchy2(scene, node->boneList);
		
//		Lws_SetBoneTime(scene, node, scene->time);
//		Lws_AnimateTextures(scene, node);
//		Lws_HandleTrigger(scene, node);
	}

}

static VOID Lws_SetAbsoluteKey(lpFrame frame, lpLwsKeyInfo keyList, UWORD key, LPVECTOR3D pivot) {

	MATRIX4D m;

	Lws_GenerateMatrix(m, &keyList[key].position, &keyList[key].hpb, &keyList[key].scale, pivot);
	Frame_SetTransform(frame, m);
}

static VOID Lws_GenerateMatrix(MATRIX4D m, LPVECTOR3D pos, LPVECTOR3D hpb, LPVECTOR3D scale, LPVECTOR3D pivot) {

	REAL Cx = Maths_Cos(hpb->y);
	REAL Sx = Maths_Sin(hpb->y);
	REAL Cz = Maths_Cos(hpb->z);
	REAL Sz = Maths_Sin(hpb->z);
	REAL Cy = Maths_Cos(hpb->x);
	REAL Sy = Maths_Sin(hpb->x);
	REAL pVx = pivot->x;
	REAL pVy = pivot->y;
	REAL pVz = pivot->z;

	m[0][0] = (((((1.0f * scale->x) *  Cz) * 1.0f) *  Cy) + ((((1.0f * scale->x) *  Sz) *  Sx) *  Sy) * 1.0f);
	m[0][1] = (((((1.0f * scale->x) *  Sz) *  Cx) * 1.0f) * 1.0f);
	m[0][2] = (((((1.0f * scale->x) *  Cz) * 1.0f) * -Sy) + ((((1.0f * scale->x) *  Sz) *  Sx) *  Cy) * 1.0f);
	m[0][3] = 0.0f;
	m[1][0] = (((((1.0f * scale->y) * -Sz) * 1.0f) *  Cy) + ((((1.0f * scale->y) *  Cz) *  Sx) *  Sy) * 1.0f);
	m[1][1] = (((((1.0f * scale->y) *  Cz) *  Cx) * 1.0f) * 1.0f);
	m[1][2] = (((((1.0f * scale->y) * -Sz) * 1.0f) * -Sy) + ((((1.0f * scale->y) *  Cz) *  Sx) *  Cy) * 1.0f);
	m[1][3] = 0.0f;
	m[2][0] = (((((1.0f * scale->z) * 1.0f) *  Cx) *  Sy) * 1.0f);
	m[2][1] = (((((1.0f * scale->z) * 1.0f) * -Sx) * 1.0f) * 1.0f);
	m[2][2] = (((((1.0f * scale->z) * 1.0f) *  Cx) *  Cy) * 1.0f);
	m[2][3] = 0.0f;
	m[3][0] = (m[0][0] * pVx) + (m[1][0] * pVy) + (m[2][0] * pVz) + pos->x;
	m[3][1] = (m[0][1] * pVx) + (m[1][1] * pVy) + (m[2][1] * pVz) + pos->y;
	m[3][2] = (m[0][2] * pVx) + (m[1][2] * pVy) + (m[2][2] * pVz) + pos->z;
	m[3][3] = 1.0f;
}

/*
static VOID Lws_GenerateRestMatrix(MATRIX4D m, LPVECTOR3D pos, LPVECTOR3D hpb) {

	REAL Cx = Maths_Cos(-hpb->y);
	REAL Sx = Maths_Sin(-hpb->y);
	REAL Cz = Maths_Cos(-hpb->z);
	REAL Sz = Maths_Sin(-hpb->z);
	REAL Cy = Maths_Cos(-hpb->x);
	REAL Sy = Maths_Sin(-hpb->x);

	m[0][0] = ((( Cy * 1.0f) *  Cz) + ((-Sy * -Sx) * -Sz) * 1.0f);
	m[0][1] = ((( Cy * 1.0f) *  Sz) + ((-Sy * -Sx) *  Cz) * 1.0f);
	m[0][2] = (((-Sy *  Cx) * 1.0f) * 1.0f);
	m[0][3] = 0.0f;
	m[1][0] = (((1.0f *  Cx) * -Sz) * 1.0f);
	m[1][1] = (((1.0f *  Cx) *  Cz) * 1.0f);
	m[1][2] = (((1.0f *  Sx) * 1.0f) * 1.0f);
	m[1][3] = 0.0f;
	m[2][0] = ((( Sy * 1.0f) *  Cz) + (( Cy * -Sx) * -Sz) * 1.0f);
	m[2][1] = ((( Sy * 1.0f) *  Sz) + (( Cy * -Sx) *  Cz) * 1.0f);
	m[2][2] = ((( Cy *  Cx) * 1.0f) * 1.0f);
	m[2][3] = 0.0f;
	m[3][0] = (((1.0f * 1.0f) * 1.0f) * -pos->x);
	m[3][1] = (((1.0f * 1.0f) * 1.0f) * -pos->y);
	m[3][2] = (((1.0f * 1.0f) * 1.0f) * -pos->z);
	m[3][3] = (((1.0f * 1.0f) * 1.0f) * 1.0f);
}
*/

static VOID Lws_SetDissolveLevel(lpLws scene, lpLwsNode node, REAL level) {

	lpMesh mesh;
	ULONG group, groupCount;

	mesh = Frame_GetMesh(scene->frameList[node->frameIndex]);

	groupCount = Mesh_GetGroupCount(mesh);
	for (group=0 ; group<groupCount ; group++) {
//		Mesh_SetGroupAlpha(mesh, group, level);
	}
}

static REAL Lws_FindPrevDissolve(lpLwsNode node, REAL time, LPUWORD prev) {

	// Assume that there will be a small number of these keys...

	UWORD loop;
	UWORD frame, prevTime;

	for (loop=1 ; loop<node->dissolveCount ; loop++) {
		frame = node->dissolveFrame[loop];
		if (time <= (REAL) frame) {
			*prev = loop - 1;
			prevTime = node->dissolveFrame[*prev];
			return Maths_InterpolationDelta((REAL) prevTime, (REAL) frame, time);
		}
	}

	*prev = node->dissolveCount - 1;

	return 0.0f;
}

static VOID Lws_InterpolateDissolve(lpLws scene, lpLwsNode node, UWORD prev, REAL delta) {

	REAL level;

	if (prev == node->dissolveCount - 1) level = node->dissolveLevel[prev];
	else level = Maths_Interpolate(node->dissolveLevel[prev], node->dissolveLevel[prev+1], delta);

	Lws_SetDissolveLevel(scene, node, level);
}

static REAL Lws_FindPrevKey(lpLwsKeyInfo keyList, UWORD keyCount, REAL time, LPUWORD prev) {

	UWORD low = 0, middle, high = keyCount - 1;
	UWORD frame;

	while (1) {

		middle = (low + high) / 2;
		frame = keyList[middle].frame;

		if (middle == low) break;

		if (time < (REAL) frame) high = middle;
		else low = middle;
	}

	*prev = middle;

	return Maths_InterpolationDelta((REAL) frame, (REAL) keyList[middle + 1].frame, time);
}

static VOID Lws_InterpolateKeys(lpFrame frame, lpLwsKeyInfo keyList, UWORD key, REAL delta, LPVECTOR3D pivot) {

	VECTOR3D pos, scale, rotation;
	MATRIX4D m;

	Maths_Vector3DInterpolate(&pos, &keyList[key].position, &keyList[key + 1].position, delta);
	Maths_Vector3DInterpolate(&scale, &keyList[key].scale, &keyList[key + 1].scale, delta);
	Maths_Vector3DInterpolate(&rotation, &keyList[key].hpb, &keyList[key + 1].hpb, delta);

	Lws_GenerateMatrix(m, &pos, &rotation, &scale, pivot);
	Frame_SetTransform(frame, m);
}

static BOOL Lws_FindFrameIndex(lpLws lws, lpFrame frame, LPULONG index) {

	ULONG loop;

	for (loop=0 ; loop<lws->nodeCount ; loop++) {
		if (frame == lws->frameList[loop]) {

			*index = loop;
			return TRUE;

		}
	}

	return FALSE;
}

static VOID Lws_CloneFrame(lpLws lws, lpLws clone, lpFrame cloneRoot, ULONG index) {

	ULONG parentIndex;
	lpFrame parent = Frame_GetParent(lws->frameList[index]);

	if (Lws_FindFrameIndex(lws, parent, &parentIndex)) {

		if (NULL == clone->frameList[parentIndex]) Lws_CloneFrame(lws, clone, cloneRoot, parentIndex);

		if (NULL == clone->frameList[index]) clone->frameList[index] = Frame_Create(clone->frameList[parentIndex]);

	} else {
		
		if (NULL == clone->frameList[index]) clone->frameList[index] = Frame_Create(cloneRoot);

	}
}

lpLws Lws_Clone(lpLws scene, lpFrame parent) {

	lpLws clone = List_ObtainItem(lwsGlobs.list);
	UWORD frameCount = 0, loop;
	lpLwsNode node;
	lpMesh mesh;

	if (scene->clonedFrom) scene = scene->clonedFrom;

	*clone = *scene;
	clone->referenceCount = 1;

	clone->frameList = Mem_AllocClear(sizeof(clone->frameList[0]) * (clone->nodeCount + clone->boneCount));
	if (clone->boneCount) clone->boneMatrixList = Mem_AllocClear(sizeof(clone->boneMatrixList[0]) * clone->boneCount);
	clone->lightList = NULL;

	for (loop=0 ; loop<clone->nodeCount + clone->boneCount ; loop++) Lws_CloneFrame(scene, clone, parent, loop);

	for (loop=0 ; loop<clone->nodeCount ; loop++) {

		node = &clone->nodeList[loop];

		if (!(node->flags & LWSNODE_FLAG_NULL)) {

			mesh = Frame_GetMesh(scene->frameList[node->frameIndex]);

			if (node->boneList) {
				Frame_SetMesh(clone->frameList[node->frameIndex], Mesh_Clone(mesh, MESH_CLONEFLAG_VERTICES|MESH_CLONEFLAG_TRANSFORMEDVERTICES));
			} else {
				Frame_SetMesh(clone->frameList[node->frameIndex], mesh);
			}
		}
	}

	clone->clonedFrom = scene;
	scene->referenceCount++;

	Lws_SetTime(clone, 0.0f);
	return clone;
}

/*
static VOID Lws_AnimateTextures(lpLws scene, lpLwsNode node) {

	lpMesh mesh;
	if (!(node->flags & LWSNODE_FLAG_NULL)) {
		mesh = Lws_GetNodeMesh(scene, node);
		Mesh_SetTextureTime(mesh, scene->time);
	}
}

static VOID Lws_HandleTrigger(lpLws scene, lpLwsNode node) {

	if (node->flags & LWSNODE_FLAG_SOUNDTRIGGER) {

		UWORD loop;
		BOOL loopMode;
		LPDIRECT3DRMFRAME3 frame = scene->frameList[node->frameIndex];
		lpLws_SoundTrigger st = &scene->triggerList[node->triggerIndex];


		for (loop=0 ; loop<st->count ; loop++) {
			loopMode = (st->frameStartList[loop] != st->frameEndList[loop]);
			if (Lws_KeyPassed(scene, st->frameStartList[loop])) {
//				st->loopUID[loop] = Sound3D_PlayOnFrame(frame, st->sound, loopMode);
				st->loopUID[loop] = Sound3D_PlayOnFrame(frame, lwsGlobs.GetSoundFunc(st->sfxID), loopMode);
			}
			if (loopMode &&
				Lws_KeyPassed(scene, st->frameEndList[loop])) {
				Sound3D_StopSound(st->loopUID[loop]);
			}
		}
	}
}

static BOOL Lws_KeyPassed(lpLws scene, ULONG key) {

	REAL keyTime, lastTime, currTime, totalTime, maxTime, minTime;

	keyTime = (REAL) key;
	lastTime = scene->lastTime;
	currTime = scene->time;
	totalTime = (REAL) Lws_GetFrameCount(scene);

	maxTime = max(lastTime, currTime);
	minTime = min(lastTime, currTime);

	if ((maxTime - minTime) / totalTime < 0.5f) {
		if (keyTime <= maxTime && keyTime >= minTime) return TRUE;
	} else {
		if (keyTime >= maxTime || keyTime <= minTime) return TRUE;
	}

	return FALSE;

//	if (scene->lastTime < (REAL) key && scene->time >= (REAL) key) return TRUE;
//	return FALSE;
}

__inline static lpMesh Lws_GetNodeMesh(lpLws scene, lpLwsNode node) {

	struct IUnknown *iunknown;
	LPDIRECT3DRMUSERVISUAL uv;
	lpMesh mesh;
	ULONG count;
	HRESULT r;
	LPDIRECT3DRMFRAME3 frame = scene->frameList[node->frameIndex];

	frame->lpVtbl->GetVisuals(frame, &count, NULL);
	Error_Fatal(1!=count, "Incorrect visual count");
	frame->lpVtbl->GetVisuals(frame, &count, &iunknown);
	r = iunknown->lpVtbl->QueryInterface(iunknown, &IID_IDirect3DRMUserVisual, &uv);
	Error_Fatal(D3DRM_OK != r, "Cannot get user visual");
	mesh = (lpMesh) uv->lpVtbl->GetAppData(uv);
	Error_Fatal(NULL == mesh, "Cannot get mesh");

	return mesh;
}

static lpMesh Lws_SearchMeshPathList(lpLws_MeshPath list, ULONG count, LPUCHAR path) {

	UWORD loop;

	for (loop=0 ; loop<count ; loop++) {
		if (0 == stricmp(path, list[loop].path)) return list[loop].mesh;
	}

	return NULL;
}

static VOID Lws_AddMeshPathEntry(lpLws_MeshPath list, LPULONG count, LPUCHAR path, lpMesh mesh) {

	Error_Fatal(*count==LWS_MAXMESHFILES, "LWS_MAXMESHFILES too small");

	list[*count].path = Mem_CopyString(path);
	list[*count].mesh = mesh;
	(*count)++;
}

lpMesh Lws_LoadMesh(LPUCHAR baseDir, LPUCHAR fname, LPDIRECT3DRMFRAME3 frame) {

	UCHAR path[FILE_MAXPATH];
	lpMesh mesh;

	if (baseDir) sprintf(path, "%s%s", baseDir, fname);
	else strcpy(path, fname);

	if (mesh = Lws_SearchMeshPathList(lwsGlobs.meshPathList, lwsGlobs.meshPathCount, path)) {
		Mesh_Clone(mesh, frame);
		return mesh;
	} else if (mesh = Mesh_Load(path, frame)) {
		Lws_AddMeshPathEntry(lwsGlobs.meshPathList, &lwsGlobs.meshPathCount, path, mesh);
		return mesh;
	} else if (lwsGlobs.sharedDir) {

		sprintf(path, "%s%s", lwsGlobs.sharedDir, fname);

		if (mesh = Lws_SearchMeshPathList(lwsGlobs.meshPathListShared, lwsGlobs.meshPathCountShared, fname)) {
			Mesh_Clone(mesh, frame);
			return mesh;
		} else if (mesh = Mesh_Load(path, frame)) {
			Lws_AddMeshPathEntry(lwsGlobs.meshPathListShared, &lwsGlobs.meshPathCountShared, fname, mesh);
			return mesh;
		}
	}

	Error_Warn(TRUE, Error_Format("Cannot find or load mesh >(%s\\)%s<", baseDir, fname));

	return NULL;
}

VOID Lws_Debug_Dump(lpLws scene) {

	lpLwsNode root;

	Error_Debug(Error_Format("FirstFrame\t%i\n", scene->firstFrame));
	Error_Debug(Error_Format("LastFrame\t%i\n", scene->lastFrame));
	Error_Debug(Error_Format("FPS\t%f\n", scene->fps));

	for (root=scene->masterNode ; root ; root=root->next) {
		Error_Debug(Error_Format("Root node: <%s> (%i)\n", root->name, root->reference));
		Lws_Debug_DumpChildren(root, 1);
	}
}

static VOID Lws_Debug_DumpChildren(lpLwsNode parent, ULONG level) {

	lpLwsNode child;
	UWORD loop, key;

	for (child=parent->childList ; child ; child=child->next) {
		for (loop=0 ; loop<level ; loop++) Error_Debug("\t");
		Error_Debug(Error_Format("<%s> (%i)\n", child->name, child->reference));
		for (key=0 ; key<child->keyCount ; key++) {
			for (loop=0 ; loop<level ; loop++) Error_Debug("\t");
			Error_Debug(Error_Format("%i\t%0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f\n", child->keyList[key].frame, child->keyList[key].position.x, child->keyList[key].position.y, child->keyList[key].position.z, child->keyList[key].hpb.x, child->keyList[key].hpb.y, child->keyList[key].hpb.z, child->keyList[key].scale.x, child->keyList[key].scale.y, child->keyList[key].scale.z));
		}
		Lws_Debug_DumpChildren(child, level + 1);
	}
}

VOID Lws_Free(lpLws scene) {

	lpLwsNode node;
	lpLws clonedFrom;
	UWORD loop;

	clonedFrom = scene->clonedFrom;
	scene->referenceCount--;

	if (0 == scene->referenceCount) {
		for (loop=0 ; loop<scene->nodeCount ; loop++) {
			node = &scene->nodeList[loop];
			Lws_FreeNode(scene, node);
		}

		if (NULL == scene->clonedFrom) {
			Mem_Free(scene->nodeList);
			Mem_Free(scene->filePath);
		}

		if (scene->triggerCount) Mem_Free(scene->triggerList);

		Mem_Free(scene->frameList);
		Mem_Free(scene);
	}

	if (clonedFrom) Lws_Free(clonedFrom);
}

static VOID Lws_FreeNode(lpLws scene, lpLwsNode node) {

	if (!(node->flags & LWSNODE_FLAG_NULL)) {
		Mesh_Remove(Lws_GetNodeMesh(scene, node), scene->frameList[node->frameIndex]);
	}

	if (NULL == scene->clonedFrom && 0 == scene->referenceCount) {
		Mem_Free(node->name);
		Mem_Free(node->keyList);
		if (node->dissolveCount) {
			Mem_Free(node->dissolveLevel);
			Mem_Free(node->dissolveFrame);
		}
	}
}
*/


























/*
typedef LPUCHAR StringMatrix[4][4];

VOID MultiplyStringMatrix(StringMatrix r, StringMatrix a, StringMatrix b) {
	
	ULONG i, j, k;
	UCHAR string[1024];
//	BOOL a1, b1;
		
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) {
			for (k=0; k<4; k++) {
				if (NULL != a[i][k] && NULL != b[k][j]) {
//					a1 = (0 == strcmp("1.0f", a[i][k]));
//					b1 = (0 == strcmp("1.0f", b[k][j]));
					string[0] = '\0';
//					if (a1 && b1) strcat(string, "1.0f");
//					else {
//						if (!a1 && !b1)
					strcat(string, "(");
//						if (!a1)
					strcat(string, a[i][k]);
//						if (!a1 && !b1)
					strcat(string, " * ");
//						if (!b1)
					strcat(string, b[k][j]);
//						if (!a1 && !b1)
					strcat(string, ")");
//					}
					if (NULL == r[i][j]) {
						r[i][j] = Mem_Alloc(strlen(string) + 1);
						strcpy(r[i][j], string);
					} else {
						r[i][j] = Mem_ReAlloc(r[i][j], strlen(r[i][j]) + strlen(string) + 4);
						strcat(r[i][j], " + ");
						strcat(r[i][j], string);
					}
				}
			}
		}
	}
}

VOID PrintStringMatrix(StringMatrix r, lpFile dfp) {
	
	ULONG i, j;
		
	for (i=0; i<4; i++) {
		for (j=0; j<4; j++) {
			fprintf(dfp, "m[%i][%i] = ", i, j);
			if (NULL != r[i][j]) {
				if ('\0' == r[i][j][0]) fprintf(dfp, "1.0f");
				else fprintf(dfp, "%s", r[i][j]);
			} else fprintf(dfp, "0.0f");
			fprintf(dfp, ";\n");
		}
	}
}

VOID TransposeStringMatrix(StringMatrix m) {

	ULONG i, j;
	LPUCHAR swap;

	for (i=0 ; i<4 ; i++){
		for (j=0 ; j<4 ; j++){
			swap = m[i][j];
			m[i][j] = m[j][i];
			m[j][i] = swap;
		}
	}
}

VOID FreeStringMatrix(StringMatrix m) {

	ULONG i, j;

	for (i=0 ; i<4 ; i++){
		for (j=0 ; j<4 ; j++){
			if (NULL != m[i][j]) Mem_Free(m[i][j]);
		}
	}
}

VOID Test(VOID) {

	// Offset by the pivot point, scale the object, rotate and then translate...
	// Heading(.x) pitch(.y) and bank(.z) (y, x, z in world coordinates) must be multiplied as
	// bank then heading then pitch...

	lpFile dfp;

	StringMatrix scale = {
		{ "scale->x", NULL, NULL, NULL },
		{ NULL, "scale->y", NULL, NULL },
		{ NULL, NULL, "scale->z", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};

	StringMatrix translation = {
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ "pos->x", "pos->y", "pos->z", "1.0f" }
	};

	StringMatrix xRotation = {
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, " Cx", " Sx", NULL },
		{ NULL, "-Sx", " Cx", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	
	StringMatrix yRotation = {
		{ " Cy", NULL, "-Sy", NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ " Sy", NULL, " Cy", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};

	StringMatrix zRotation = {
		{ " Cz", " Sz", NULL, NULL },
		{ "-Sz", " Cz", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};

	StringMatrix pivotPoint = {
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ "pVx", "pVy", "pVz", "1.0f" }
	};

	StringMatrix m1 = { NULL };
	StringMatrix m2 = { NULL };
	StringMatrix m3 = { NULL };
	StringMatrix m4 = { NULL };
	StringMatrix m5 = { NULL };

	TransposeStringMatrix(pivotPoint);
	TransposeStringMatrix(scale);
	TransposeStringMatrix(translation);
	TransposeStringMatrix(xRotation);
	TransposeStringMatrix(yRotation);
	TransposeStringMatrix(zRotation);

	MultiplyStringMatrix(m1, pivotPoint, scale);
	MultiplyStringMatrix(m2, m1, zRotation);
	MultiplyStringMatrix(m3, m2, xRotation);
	MultiplyStringMatrix(m4, m3, yRotation);
	MultiplyStringMatrix(m5, m4, translation);

	if (dfp = File_Open("lwsformula.txt", "w")) {
		PrintStringMatrix(m5, dfp);
		File_Close(dfp);
	}
}

VOID Test2(VOID) {

	// For bones:
	// Rotate in the reverse order the opposite of the input rotations then translate by the reverse of the vector.
	// Heading(.x) pitch(.y) and bank(.z) (y, x, z in world coordinates) must be multiplied as
	// pitch then heading then bank

	lpFile dfp;

	StringMatrix translation = {
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ "-pos->x", "-pos->y", "-pos->z", "1.0f" }
	};

	StringMatrix xRotation = {
		{ "1.0f", NULL, NULL, NULL },
		{ NULL, " Cx", " Sx", NULL },
		{ NULL, "-Sx", " Cx", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};
	
	StringMatrix yRotation = {
		{ " Cy", NULL, "-Sy", NULL },
		{ NULL, "1.0f", NULL, NULL },
		{ " Sy", NULL, " Cy", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};

	StringMatrix zRotation = {
		{ " Cz", " Sz", NULL, NULL },
		{ "-Sz", " Cz", NULL, NULL },
		{ NULL, NULL, "1.0f", NULL },
		{ NULL, NULL, NULL, "1.0f" }
	};

	StringMatrix m1 = { NULL };
	StringMatrix m2 = { NULL };
	StringMatrix m3 = { NULL };

	TransposeStringMatrix(translation);
	TransposeStringMatrix(xRotation);
	TransposeStringMatrix(yRotation);
	TransposeStringMatrix(zRotation);

	MultiplyStringMatrix(m1, yRotation, xRotation);
	MultiplyStringMatrix(m2, m1, zRotation);
	MultiplyStringMatrix(m3, m2, translation);

	if (dfp = File_Open("lwsboneformula.txt", "w")) {
		PrintStringMatrix(m3, dfp);
		File_Close(dfp);
	}
}
*/