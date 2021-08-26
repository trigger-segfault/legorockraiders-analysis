
#include <d3drmwin.h>

#include "..\Inc\Standard.h"
#include "..\Inc\Memory.h"
#include "..\Inc\Errors.h"
#include "..\Inc\Files.h"
#include "..\Inc\Utils.h"
#include "..\Inc\Main.h"
#include "..\Inc\Lws.h"
#include "..\Inc\3DSound.h"

#define _LWS_BUILDHIERARCHY

Lws_Globs lwsGlobs = { NULL };

lpLws_Info Lws_Parse(LPUCHAR fname, BOOL looping) {

	lpFile ifp;
	lpLws_Info scene = NULL;
	UCHAR path[FILE_MAXPATH];

#ifdef _DEBUG
	Error_Fatal(!lwsGlobs.initialised, "Lws_Initialise() has not been called");
#endif _DEBUG

	sprintf(path, "%s.%s", fname, LWS_FILESUFFIX);

	if (ifp = File_Open(path, "r")) {

		UCHAR line[LWS_MAXLINELEN];
		UCHAR lineSplit[LWS_MAXLINELEN];
		UWORD length;

		File_GetLine(line, sizeof(line), ifp);
		length = strlen(line) + 1;
		File_GetLine(&line[length], sizeof(line) - length, ifp);

		if (0 == strcmp(line, LWS_HEADER1) && 0 == strcmp(&line[length], LWS_HEADER2)) {

			LPUCHAR argv[LWS_MAXARGS];
			SLONG argc, loop;
			SLONG motionMode = 0, dissolveMode = 0;
			lpLws_Node currNode = NULL, parent;
			LPUWORD parentList;
			LPUCHAR s, t;

			for (s=t=path ; '\0'!=*s ; s++) if ('\\' == *s) t = s;
			*(t+(t==path?0:1)) = '\0';

			scene = Mem_Alloc(sizeof(Lws_Info));
			memset(scene, 0, sizeof(Lws_Info));
			if ('\0' != path[0]) scene->filePath = Util_StrCpy(path);
			else scene->filePath = NULL;

			scene->nodeListSize = LWS_NODELISTBLOCKSIZE;
			scene->referenceCount = 1;
			if (looping) scene->flags |= LWS_FLAG_LOOPING;

			scene->nodeList = Mem_Alloc(sizeof(Lws_Node) * scene->nodeListSize);
			parentList = Mem_Alloc(sizeof(UWORD) * scene->nodeListSize);

			while (File_GetLine(line, sizeof(line), ifp)){
				strcpy(lineSplit, line);
				if (argc = Util_WSTokenise(lineSplit, argv)) {
					if (NULL == currNode) {
						if (0 == strcmp("FirstFrame", argv[0])) scene->firstFrame = atoi(argv[1]);
						if (0 == strcmp("LastFrame", argv[0])) scene->lastFrame = atoi(argv[1]);
						if (0 == scene->lastFrame) scene->lastFrame = 1;
						if (0 == strcmp("FramesPerSecond", argv[0])) scene->fps = (REAL) atof(argv[1]);
						if (0 == strcmp("AddNullObject", argv[0]) || 0 == strcmp("LoadObject", argv[0])) {

							if (scene->nodeCount == scene->nodeListSize) {
								scene->nodeListSize += LWS_NODELISTBLOCKSIZE;
								scene->nodeList = Mem_ReAlloc(scene->nodeList, sizeof(Lws_Node) * scene->nodeListSize);
								parentList = Mem_ReAlloc(parentList, sizeof(UWORD) * scene->nodeListSize);
							}
							parentList[scene->nodeCount] = 0;
							currNode = &scene->nodeList[scene->nodeCount];
							memset(currNode, 0, sizeof(Lws_Node));

							if (0 == strcmp("AddNullObject", argv[0])) {
								currNode->flags |= LWSNODE_FLAG_NULL;
								currNode->name = Util_StrCpy(&line[strlen("AddNullObject") + 1]);
								if (0 == strnicmp(currNode->name, LWS_SOUNDTRIGGERPREFIX, strlen(LWS_SOUNDTRIGGERPREFIX)) &&
									0 == strnicmp(&currNode->name[strlen(LWS_SOUNDTRIGGERPREFIX)], LWS_SOUNDTRIGGERSEPERATOR, strlen(LWS_SOUNDTRIGGERSEPERATOR))){
									currNode->flags |= LWSNODE_FLAG_SOUNDTRIGGER;
									Error_Fatal(scene->triggerCount == 256, "Too many sound trigger frames");
									scene->triggerCount++;
								}

							} else {
								LPUCHAR lwoStr;
								strcpy(lineSplit, line);
								argc = Util_Tokenise(line, argv, "\\");
								if (lwoStr = Util_StrIStr(argv[argc-1], ".lwo")) lwoStr[0] = '\0';
								currNode->name = Util_StrCpy(argv[argc-1]);
							}

							for (loop=scene->nodeCount-1 ; loop>=0 ; loop--) {
								if (((scene->nodeList[loop].flags & LWSNODE_FLAG_NULL) && (currNode->flags & LWSNODE_FLAG_NULL)) ||
									(!(scene->nodeList[loop].flags & LWSNODE_FLAG_NULL) && !(currNode->flags & LWSNODE_FLAG_NULL))) {

									if (0 == strcmp(currNode->name, scene->nodeList[loop].name)) {
										currNode->reference = scene->nodeList[loop].reference + 1;
										break;
									}
								}
							}

						}
					} else if (motionMode) {

						// argv[1] is the first item as there is some white space at ther start of the line...

						if (1 == motionMode) { Error_Fatal(9 != atoi(argv[1]), "Scene file error");
						} else if (2 == motionMode) {
							currNode->keyCount = atoi(argv[1]);
//							currNode->keyPos = Mem_Alloc(sizeof(VECTOR3D) * (currNode->keyCount + 1));
//							currNode->keyHPB = Mem_Alloc(sizeof(VECTOR3D) * (currNode->keyCount + 1));
//							currNode->keyScale = Mem_Alloc(sizeof(VECTOR3D) * (currNode->keyCount + 1));
//							currNode->keyFrame = Mem_Alloc(sizeof(UWORD) * (currNode->keyCount + 1));
							currNode->keyList = Mem_Alloc(sizeof(Lws_KeyInfo) * (currNode->keyCount + 1));
						} else {
							UWORD key = (motionMode - 3) / 2;
							if (key < currNode->keyCount) {
								if (motionMode % 2) {
									currNode->keyList[key].position.x = (REAL) atof(argv[1]);
									currNode->keyList[key].position.y = (REAL) atof(argv[2]);
									currNode->keyList[key].position.z = (REAL) atof(argv[3]);
									currNode->keyList[key].hpb.x = ((REAL) atof(argv[4]) / 180.0f) * M_PI;
									currNode->keyList[key].hpb.y = ((REAL) atof(argv[5]) / 180.0f) * M_PI;
									currNode->keyList[key].hpb.z = ((REAL) atof(argv[6]) / 180.0f) * M_PI;
									currNode->keyList[key].scale.x = (REAL) atof(argv[7]);
									currNode->keyList[key].scale.y = (REAL) atof(argv[8]);
									currNode->keyList[key].scale.z = (REAL) atof(argv[9]);
								} else {
									currNode->keyList[key].frame = atoi(argv[1]);
								}
							}
						}

						motionMode++;

						if (0 == strcmp(argv[0], "EndBehavior")) motionMode = 0;

					} else if (dissolveMode) {

						// argv[1] is the first item as there is some white space at ther start of the line...

						if (1 == dissolveMode) { Error_Fatal(1 != atoi(argv[1]), "Scene file error");
						} else if (2 == dissolveMode) {
							currNode->dissolveCount = atoi(argv[1]);
							currNode->dissolveLevel = Mem_Alloc(sizeof(REAL) * (currNode->dissolveCount + 1));
							currNode->dissolveFrame = Mem_Alloc(sizeof(UWORD) * (currNode->dissolveCount + 1));
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

						if (0 == strcmp(argv[0], "ObjectMotion")) motionMode = 1;
						else if (0 == strcmp(argv[0], "ObjDissolve")) {
							if (0 == strcmp(argv[1], "(envelope)")) dissolveMode = 1;
							else {
								Error_Fatal(LWS_MAXSTATICDISSOLVES==lwsGlobs.staticDissolveCount, "LWS_MAXSTATICDISSOLVES too small");
								lwsGlobs.staticDissolveLevel[lwsGlobs.staticDissolveCount] = (REAL) atof(argv[1]);
								currNode->dissolveLevel = &lwsGlobs.staticDissolveLevel[lwsGlobs.staticDissolveCount];
								lwsGlobs.staticDissolveCount++;
								currNode->dissolveLevel = 0;
							}
						} else if (0 == strcmp(argv[0], "ParentObject")) parentList[scene->nodeCount] = atoi(argv[1]);
						else if (0 == strcmp(argv[0], "PivotPoint")) {
							currNode->pivotVector.x = (REAL) -atof(argv[1]);
							currNode->pivotVector.y = (REAL) -atof(argv[2]);
							currNode->pivotVector.z = (REAL) -atof(argv[3]);
						} else if (0 == strcmp(argv[0], "UnseenByCamera") && 1 == atoi(argv[1])) {
							currNode->flags |= LWSNODE_FLAG_FACECAMERA;
						} else if (0 == strcmp(argv[0], "ShadowOptions")) {
							currNode = NULL;
							scene->nodeCount++;
						}
					}
				}
			}

			// If there is more than one key and the last one is before the end of the animation
			// then create a duplicate of the last one at the end.
			// The arrays are over allocated by one to ensure that there is enough space.

			for (loop=0 ; loop<(SLONG)scene->nodeCount ; loop++) {
				currNode = &scene->nodeList[loop];
				if (1 != currNode->keyCount && currNode->keyList[currNode->keyCount-1].frame < scene->lastFrame) {
					currNode->keyList[currNode->keyCount].frame = scene->lastFrame;
					currNode->keyList[currNode->keyCount].position = currNode->keyList[currNode->keyCount-1].position;
					currNode->keyList[currNode->keyCount].hpb = currNode->keyList[currNode->keyCount-1].hpb;
					currNode->keyList[currNode->keyCount].scale = currNode->keyList[currNode->keyCount-1].scale;
					currNode->keyCount++;
				}
			}

			// Do the same for the dissolve level (assume that if an envelope is defined, more than one key
			// will be used)...

			for (loop=0 ; loop<(SLONG)scene->nodeCount ; loop++) {
				currNode = &scene->nodeList[loop];
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
				if (parentList[loop]) {
					parent = &scene->nodeList[parentList[loop] - 1];
					currNode->next = parent->childList;
					parent->childList = currNode;
				} else {
					currNode->next = scene->masterNode;
					scene->masterNode = currNode;
				}
			}

			Mem_Free(parentList);

			Lws_SetupSoundTriggers(scene);

		} else Error_Fatal(TRUE, "Invalid scene file");

		File_Close(ifp);
	}

	return scene;
}

//VOID Lws_Initialise(LPUCHAR sharedDir, BOOL (*FindSFXID)(LPUCHAR name, LPULONG id), ULONG (*PlaySFX)(ULONG id, BOOL loop, LPVECTOR3D pos), VOID (*StopSFX)(ULONG uid)) {
//VOID Lws_Initialise(LPUCHAR sharedDir, BOOL (*FindSound)(LPUCHAR name, lpSound *sound)) {
//VOID Lws_Initialise(LPUCHAR sharedDir, BOOL (*FindSFXID)(LPUCHAR name, LPULONG sfxID), SLONG (*GetSound)(ULONG id), BOOL (*SoundEnabled)(VOID)) {
VOID Lws_Initialise(LPUCHAR sharedDir, BOOL (*FindSFXID)(LPUCHAR name, LPULONG sfxID), SLONG (*PlaySample3D)(lpContainer cont, ULONG type, BOOL loop, BOOL onCont, LPVECTOR3D wPos), BOOL (*SoundEnabled)(VOID)) {

	if (sharedDir) {
		UWORD len = strlen(sharedDir);
		if ('\\' != sharedDir[len-1]) len++;
		lwsGlobs.sharedDir = Mem_Alloc(len+1);
		strcpy(lwsGlobs.sharedDir, sharedDir);
		lwsGlobs.sharedDir[len-1] = '\\';
		lwsGlobs.sharedDir[len] = '\0';
	}

//	Error_Fatal(FindSFXID && (NULL == PlaySFX || NULL == StopSFX), "If FindSFXID() is passed, so should PlaySFX() and StopSFX()");

//	lwsGlobs.FindSFXIDFunc = FindSFXID;
//	lwsGlobs.PlaySFXFunc = PlaySFX;
//	lwsGlobs.StopSFXFunc = StopSFX;

//	lwsGlobs.FindSoundFunc = FindSound;

	lwsGlobs.FindSFXIDFunc = FindSFXID;
	lwsGlobs.PlaySample3DFunc = PlaySample3D;
//	lwsGlobs.GetSoundFunc = GetSound;
	lwsGlobs.SoundEnabledFunc = SoundEnabled;

#ifdef _DEBUG
	lwsGlobs.initialised = TRUE;
#endif // _DEBUG
}

VOID Lws_Shutdown(VOID) {

	UWORD loop;
	for (loop=0 ; loop<lwsGlobs.meshPathCount; loop++) {
		lpLws_MeshPath mp = &lwsGlobs.meshPathList[loop];
		Mem_Free(mp->path);
	}
	for (loop=0 ; loop<lwsGlobs.meshPathCountShared ; loop++) {
		lpLws_MeshPath mp = &lwsGlobs.meshPathListShared[loop];
		Mem_Free(mp->path);
	}
}

ULONG Lws_GetFrameCount(lpLws_Info scene) {

	return scene->lastFrame;
}

static VOID Lws_SetupSoundTriggers(lpLws_Info scene) {

	if (lwsGlobs.FindSFXIDFunc) {
//	if (lwsGlobs.FindSoundFunc) {
		lpLws_Node node;
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
						if (mainGlobs.flags & MAIN_FLAG_REDUCESAMPLES) {
							Error_Warn(!result, Error_Format("Cannot match sound with %s", argv[1]));
							if (!result)
								st->sfxID=0;
						} else {
							Error_Fatal(!result, Error_Format("Cannot match sound with %s", argv[1]));
						}
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
}

VOID Lws_LoadMeshes(lpLws_Info scene, LPDIRECT3DRMFRAME3 parent) {

	// Generate the frame hierarchy and load in the meshes...
	// Must run through the hierarchy, not the array...

	lpLws_Node root;
	UWORD frameCount = 0;

	scene->frameList = Mem_Alloc(sizeof(LPDIRECT3DRMFRAME3) * scene->nodeCount);

	for (root=scene->masterNode ; root ; root=root->next) {
		Lws_CreateFrames(scene, root, parent, &frameCount);
		Lws_LoadNodes(scene, root);
	}
	Lws_SetTime(scene, 0.0f);
}

lpLws_Info Lws_Clone(lpLws_Info scene, LPDIRECT3DRMFRAME3 parent) {

	lpLws_Info clone = Mem_Alloc(sizeof(Lws_Info));
	lpLws_Node root, node;
	lpMesh mesh;
	UWORD frameCount = 0, loop;
	LPDIRECT3DRMFRAME3 nodeParent;
	MATRIX4D mat;

	if (scene->clonedFrom) scene = scene->clonedFrom;

	memset(clone, 0, sizeof(Lws_Info));
	*clone = *scene;
	clone->referenceCount = 1;

	clone->frameList = Mem_Alloc(sizeof(LPDIRECT3DRMFRAME3) * clone->nodeCount);

	for (root=clone->masterNode ; root ; root=root->next) {
		Lws_CreateFrames(clone, root, parent, &frameCount);
	}
	for (loop=0 ; loop<clone->nodeCount ; loop++) {
		node = &clone->nodeList[loop];

		// Copy the transformation...
		scene->frameList[loop]->lpVtbl->GetParent(scene->frameList[loop], &nodeParent);
		scene->frameList[loop]->lpVtbl->GetTransform(scene->frameList[loop], nodeParent, mat);
		nodeParent->lpVtbl->Release(nodeParent);
		clone->frameList[loop]->lpVtbl->AddTransform(clone->frameList[loop], D3DRMCOMBINE_REPLACE, mat);

		if (!(node->flags & LWSNODE_FLAG_NULL)) {
			mesh = Lws_GetNodeMesh(scene, node);
			Mesh_Clone(mesh, clone->frameList[node->frameIndex]);
		}
	}

	clone->clonedFrom = scene;
	scene->referenceCount++;

	Lws_SetTime(clone, 0.0f);
	return clone;
}

VOID Lws_SetTime(lpLws_Info scene, REAL time) {

	UWORD prev;
	UWORD loop;
	REAL delta;
	lpLws_Node node;

	scene->lastTime = scene->time;
	if (scene->flags & LWS_FLAG_LOOPING) scene->time = (REAL) fmod(time, (REAL) scene->lastFrame);
	else if (time > scene->lastFrame) scene->time = scene->lastFrame;
	else scene->time = time;

	for (loop=0 ; loop<scene->nodeCount ; loop++) {
		node = &scene->nodeList[loop];
		if (node->keyCount > 1) {
			delta = Lws_FindPrevKey(node, scene->time, &prev);
			Lws_InterpolateKeys(scene, node, prev, delta);
		}
		if (node->dissolveCount > 1) {
			delta = Lws_FindPrevDissolve(node, scene->time, &prev);
			Lws_InterpolateDissolve(scene, node, prev, delta);
		}
		Lws_AnimateTextures(scene, node);
		Lws_HandleTrigger(scene, node);
	}
}

/*
static VOID Lws_SetNodeTime(lpLws_Node node, REAL time) {

	lpLws_Node child;
	UWORD prev;
	REAL delta;

	if (1 == node->keyCount) Lws_SetAbsoluteKey(node, 0);
	else {
		delta = Lws_FindPrevKey(node, time, &prev);
		Lws_InterpolateKeys(node, prev, delta);
	}
//	if (node->dissolveCount) {
//		delta = Lws_FindPrevDissolve(node, time, &prev);
//		Lws_InterpolateDissolve(node, prev, delta);
//	}

	for (child=node->childList ; child ; child=child->next) {
		Lws_SetNodeTime(child, time);
	}
}
*/

/*
static REAL Lws_FindPrevKey(lpLws_Node node, REAL time, LPUWORD prev) {

	UWORD loop, frame;
	UWORD prevTime;

	for (loop=1 ; loop<node->keyCount ; loop++) {
		frame = node->keyFrame[loop];
		if (time <= (REAL) frame) {
			*prev = loop - 1;
			prevTime = node->keyFrame[*prev];
//			return (time - prevTime) / (frame - prevTime);
			return Maths_InterpolationDelta((REAL) prevTime, (REAL) frame, time);
		}
	}

	*prev = node->keyCount - 1;
	return 0.0f;
}
*/

static REAL Lws_FindPrevKey(lpLws_Node node, REAL time, LPUWORD prev) {

	UWORD low=0, middle, high=node->keyCount;
	UWORD frame;

	middle = high;

	while (1) {

		middle = (low + high) / 2;
		frame = node->keyList[middle].frame;

		if (middle == low) break;

		if (time < (REAL) frame) high = middle;
		else low = middle;
	}

	*prev = middle;
	return Maths_InterpolationDelta((REAL) frame, (REAL) node->keyList[middle+1].frame, time);
}

static VOID Lws_AnimateTextures(lpLws_Info scene, lpLws_Node node) {

	lpMesh mesh;
	if (!(node->flags & LWSNODE_FLAG_NULL)) {
		mesh = Lws_GetNodeMesh(scene, node);
		Mesh_SetTextureTime(mesh, scene->time);
	}
}

static VOID Lws_HandleTrigger(lpLws_Info scene, lpLws_Node node) {

	if (lwsGlobs.FindSFXIDFunc) {
		if (node->flags & LWSNODE_FLAG_SOUNDTRIGGER) {

			UWORD loop;
			BOOL loopMode;
			LPDIRECT3DRMFRAME3 frame = scene->frameList[node->frameIndex];
			lpLws_SoundTrigger st = &scene->triggerList[node->triggerIndex];


			for (loop=0 ; loop<st->count ; loop++) {
				loopMode = (st->frameStartList[loop] != st->frameEndList[loop]);
				if (Lws_KeyPassed(scene, st->frameStartList[loop])) {
	//				st->loopUID[loop] = Sound3D_PlayOnFrame(frame, st->sound, loopMode);
	//				if (lwsGlobs.SoundEnabledFunc()) st->loopUID[loop] = Sound3D_PlayOnFrame(frame, lwsGlobs.GetSoundFunc(st->sfxID), loopMode);

					{
						if (lwsGlobs.SoundEnabledFunc()) st->loopUID[loop] = lwsGlobs.PlaySample3DFunc(frame, st->sfxID, loopMode, TRUE, NULL);
					}
				}
				if (loopMode &&
					Lws_KeyPassed(scene, st->frameEndList[loop])) {
					Sound3D_StopSound(st->loopUID[loop]);
				}
			}
		}
	}
}

static BOOL Lws_KeyPassed(lpLws_Info scene, ULONG key) {

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

static VOID Lws_SetDissolveLevel(lpLws_Info scene, lpLws_Node node, REAL level) {

	lpMesh mesh;
	ULONG group, groupCount;

	mesh = Lws_GetNodeMesh(scene, node);

	groupCount = Mesh_GetGroupCount(mesh);
	for (group=0 ; group<groupCount ; group++) {
		Mesh_SetGroupAlpha(mesh, group, level);
	}
}

__inline static lpMesh Lws_GetNodeMesh(lpLws_Info scene, lpLws_Node node) {

	struct IUnknown *iunknown;
	LPDIRECT3DRMUSERVISUAL uv;
	lpMesh mesh;
	ULONG count;
	HRESULT r;
	LPDIRECT3DRMFRAME3 frame = scene->frameList[node->frameIndex];
	ULONG rc;

	frame->lpVtbl->GetVisuals(frame, &count, NULL);
	Error_Fatal(1!=count, Error_Format("Failed to obtain lwo mesh from lightwave scene.\nLws_GetNodeMesh() - Node name == '%s'", node->name));
	frame->lpVtbl->GetVisuals(frame, &count, &iunknown);
	r = iunknown->lpVtbl->QueryInterface(iunknown, &IID_IDirect3DRMUserVisual, &uv);
	Error_Fatal(D3DRM_OK != r, "Cannot get user visual");
	rc = iunknown->lpVtbl->Release(iunknown);
	mesh = (lpMesh) uv->lpVtbl->GetAppData(uv);
	Error_Fatal(NULL == mesh, "Cannot get mesh");
	rc = uv->lpVtbl->Release(uv);

	return mesh;
}

static REAL Lws_FindPrevDissolve(lpLws_Node node, REAL time, LPUWORD prev) {

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

static VOID Lws_InterpolateDissolve(lpLws_Info scene, lpLws_Node node, UWORD prev, REAL delta) {

	REAL level;

	if (prev == node->dissolveCount - 1) level = node->dissolveLevel[prev];
	else level = Maths_Interpolate(node->dissolveLevel[prev], node->dissolveLevel[prev+1], delta);

	Lws_SetDissolveLevel(scene, node, level);
}

static VOID Lws_InterpolateKeys(lpLws_Info scene, lpLws_Node node, UWORD key, REAL delta) {

	VECTOR3D pos, scale, rotation;

	Maths_Vector3DInterpolate(&pos, &node->keyList[key].position, &node->keyList[key+1].position, delta);
	Maths_Vector3DInterpolate(&scale, &node->keyList[key].scale, &node->keyList[key+1].scale, delta);
	Maths_Vector3DInterpolate(&rotation, &node->keyList[key].hpb, &node->keyList[key+1].hpb, delta);

	Lws_SetupNodeTransform(scene, node, &pos, &rotation, &scale);
}

static VOID Lws_SetupNodeTransform(lpLws_Info scene, lpLws_Node node, LPVECTOR3D pos, LPVECTOR3D hpb, LPVECTOR3D scale) {

	// Scale the object, rotate then translate...
	// Heading(.x) pitch(.y) and bank(.z) (y, x, z in world coordinates) must be multiplied as
	// bank then heading then pitch...

	LPDIRECT3DRMFRAME3 frame = scene->frameList[node->frameIndex];
	D3DRMMATRIX4D m;

	if (node->flags & LWSNODE_FLAG_FACECAMERA){

		LPDIRECT3DRMFRAME3 parent;
		frame->lpVtbl->GetParent(frame, &parent);

		frame->lpVtbl->GetTransform(frame, parent, m);
		parent->lpVtbl->Release(parent);
		parent = NULL;
		m[0][0] *= scale->x;
		m[1][1] *= scale->y;
		m[2][2] *= scale->z;
		m[3][0] = pos->x;
		m[3][1] = pos->y;
		m[3][2] = pos->z;
		frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, m);

	} else {
	/*	frame->lpVtbl->AddTranslation(frame, D3DRMCOMBINE_REPLACE, node->pivotVector.x, node->pivotVector.y, node->pivotVector.z);
		frame->lpVtbl->AddScale(frame, D3DRMCOMBINE_AFTER, scale->x, scale->y, scale->z);
		frame->lpVtbl->AddRotation(frame, D3DRMCOMBINE_AFTER, 0.0f, 0.0f, 1.0f, hpb->z);
		frame->lpVtbl->AddRotation(frame, D3DRMCOMBINE_AFTER, 1.0f, 0.0f, 0.0f, hpb->y);
		frame->lpVtbl->AddRotation(frame, D3DRMCOMBINE_AFTER, 0.0f, 1.0f, 0.0f, hpb->x);
		frame->lpVtbl->AddTranslation(frame, D3DRMCOMBINE_AFTER, pos->x, pos->y, pos->z);
	*/
		// Each of the sub terms
		REAL Cx = Maths_Cos(hpb->y);
		REAL Sx = Maths_Sin(hpb->y);
		REAL Cz = Maths_Cos(hpb->z);
		REAL Sz = Maths_Sin(hpb->z);
		REAL Cy = Maths_Cos(hpb->x);
		REAL Sy = Maths_Sin(hpb->x);

	/////////////////////////////////////////////////////////////////////
	// Formula - Unoptimised version
	//	m[0][0] = Cz * Cy + Sz * Sx * Sy;
	//	m[0][1] = Sz * Cx;
	//	m[0][2] = Sz * Sx * Cy - Cz * Sy;
	//	m[0][3] = 0.0f;
	//
	//	m[1][0] = Cz * Sx * Sy - Sz * Cy;
	//	m[1][1] = Cz * Cx;
	//	m[1][2] = Sz * Sy + Cz * Sx * Cy;
	//	m[1][3] = 0.0f;
	//
	//	m[2][0] = Cx * Sy;
	//	m[2][1] = -Sx;
	//	m[2][2] = Cx * Cy;
	//	m[2][3] = 0.0f;
	//
	//	m[3][0] = k->posx;
	//	m[3][1] = k->posy;
	//	m[3][2] = k->posz;
	//	m[3][3] = 1.0f;
	///////////////////////////////////////////////////////////////////
	/*
		// (Slightly) optimised sub terms - dont know if this is really worth it.
		REAL SxSy = Sx * Sy;
		REAL CzCy = Cz * Cy;

		m[0][0] =  ( ( CzCy ) + ( Sz * SxSy ) ) * scale->x;
		m[0][1] =  Sz * Cx * scale->x;
		m[0][2] =  ( ( Sz * Sx * Cy) - (Cz * Sy) ) * scale->x;
		m[0][3] =  0.0f;

		m[1][0] =  ( ( Cz * SxSy) - ( Sz * Cy) ) * scale->y;
		m[1][1] =  Cz * Cx * scale->y;
		m[1][2] =  ( ( Sz * Sy ) + ( CzCy * Sx) ) * scale->y;
		m[1][3] =  0.0f;

		m[2][0] =  Cx * Sy * scale->z;
		m[2][1] = -Sx * scale->z;
		m[2][2] =  Cx * Cy * scale->z;
		m[2][3] =  0.0f;

		m[3][0] =  pos->x;
		m[3][1] =  pos->y;
		m[3][2] =  pos->z;
		m[3][3] =  1.0f;

		frame->lpVtbl->AddTranslation(frame, D3DRMCOMBINE_REPLACE, node->pivotVector.x, node->pivotVector.y, node->pivotVector.z);
	*/
		REAL pVx = node->pivotVector.x;
		REAL pVy = node->pivotVector.y;
		REAL pVz = node->pivotVector.z;

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

		frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, m);
	}
}

static VOID Lws_SetAbsoluteKey(lpLws_Info scene, lpLws_Node node, UWORD key) {

	Lws_SetupNodeTransform(scene, node, &node->keyList[key].position, &node->keyList[key].hpb, &node->keyList[key].scale);
}

/*
static VOID Lws_SetAbsoluteKey(lpLws_Node node, UWORD key) {

	D3DRMMATRIX4D pos =
	{
		{ 1.0f,						0.0f,					0.0f,					0.0f },
		{ 0.0f,						1.0f,					0.0f,					0.0f },
		{ 0.0f,						0.0f,					1.0f,					0.0f },
		{ node->keyPos[key].x,		node->keyPos[key].y,	node->keyPos[key].z,	1.0f }
	};
	D3DRMMATRIX4D scale =
	{
		{ node->keyScale[key].x,	0.0f,					0.0f,					0.0f },
		{ 0.0f,						node->keyScale[key].y,	0.0f,					0.0f },
		{ 0.0f,						0.0f,					node->keyScale[key].z,	0.0f },
		{ 0.0f,						0.0f,					0.0f,					1.0f }
	};

	node->frame->lpVtbl->AddTransform(node->frame, D3DRMCOMBINE_REPLACE, scale);
	node->frame->lpVtbl->AddRotation(node->frame, D3DRMCOMBINE_AFTER, 0.0f, 1.0f, 0.0f, node->keyHPB[key].x);
	node->frame->lpVtbl->AddRotation(node->frame, D3DRMCOMBINE_AFTER, 1.0f, 0.0f, 0.0f, node->keyHPB[key].y);
	node->frame->lpVtbl->AddRotation(node->frame, D3DRMCOMBINE_AFTER, 0.0f, 0.0f, 1.0f, node->keyHPB[key].z);
	node->frame->lpVtbl->AddTransform(node->frame, D3DRMCOMBINE_AFTER, pos);
}
*/

static lpMesh Lws_SearchMeshPathList(lpLws_MeshPath list, ULONG count, LPUCHAR path) {

	UWORD loop;

	for (loop=0 ; loop<count ; loop++) {
		if (0 == stricmp(path, list[loop].path)) return list[loop].mesh;
	}

	return NULL;
}

static VOID Lws_AddMeshPathEntry(lpLws_MeshPath list, LPULONG count, LPUCHAR path, lpMesh mesh) {

	Error_Fatal(*count==LWS_MAXMESHFILES, "LWS_MAXMESHFILES too small");

	list[*count].path = Util_StrCpy(path);
	list[*count].mesh = mesh;
	(*count)++;
}

lpMesh Lws_LoadMesh(LPUCHAR baseDir, LPUCHAR fname, LPDIRECT3DRMFRAME3 frame, BOOL noTextures) {

	UCHAR path[FILE_MAXPATH];
	lpMesh mesh;

	if (baseDir) sprintf(path, "%s%s", baseDir, fname);
	else strcpy(path, fname);

	if (mesh = Lws_SearchMeshPathList(lwsGlobs.meshPathList, lwsGlobs.meshPathCount, path)) {
		Mesh_Clone(mesh, frame);
		return mesh;
	} else if (mesh = Mesh_Load(path, frame, noTextures)) {
		Lws_AddMeshPathEntry(lwsGlobs.meshPathList, &lwsGlobs.meshPathCount, path, mesh);
		return mesh;
	} else if (lwsGlobs.sharedDir) {

		sprintf(path, "%s%s", lwsGlobs.sharedDir, fname);

		if (mesh = Lws_SearchMeshPathList(lwsGlobs.meshPathListShared, lwsGlobs.meshPathCountShared, fname)) {
			Mesh_Clone(mesh, frame);
			return mesh;
		} else if (mesh = Mesh_Load(path, frame, noTextures)) {
			Lws_AddMeshPathEntry(lwsGlobs.meshPathListShared, &lwsGlobs.meshPathCountShared, fname, mesh);
			return mesh;
		}
	}

	Error_Warn(TRUE, Error_Format("Cannot find or load mesh >(%s\\)%s<", baseDir, fname));

	return NULL;
}

static VOID Lws_CreateFrames(lpLws_Info scene, lpLws_Node node, LPDIRECT3DRMFRAME3 parent, LPUWORD frameCount) {

	LPDIRECT3DRMFRAME3 frame;
	lpLws_Node child;

	lpD3DRM()->lpVtbl->CreateFrame(lpD3DRM(), parent, &frame);

	if (node->flags & LWSNODE_FLAG_FACECAMERA) {
		D3DRMMATRIX4D m;
		memset(m, 0, sizeof(D3DRMMATRIX4D));
		m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
		m[3][0] = m[3][1] = m[3][2] = 0.0f;
		frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, m);
	}

	scene->frameList[*frameCount] = frame;
	node->frameIndex = *frameCount;
	(*frameCount)++;

	{
		UCHAR name[1024];
		LPUCHAR s;
		sprintf(name, "%s_%0.2i", node->name, node->reference);
		for (s=name ; '\0'!=*s ; s++) if (!isprint(*s)) *s = '_';
		frame->lpVtbl->SetName(frame, name);
	}

	for (child=node->childList ; child ; child=child->next) {
		Lws_CreateFrames(scene, child, frame, frameCount);
	}
}

static VOID Lws_LoadNodes(lpLws_Info scene, lpLws_Node node) {

	LPDIRECT3DRMFRAME3 frame;
	lpLws_Node child;
	lpMesh mesh;

	frame = scene->frameList[node->frameIndex];

	// If there is only one keyframe, then set it now...
	if (1 == node->keyCount) Lws_SetAbsoluteKey(scene, node, 0);

	if (!(node->flags & LWSNODE_FLAG_NULL)) {

		if (mesh = Lws_LoadMesh(scene->filePath, node->name, frame, FALSE)) {
			if (node->flags & LWSNODE_FLAG_FACECAMERA) mesh->flags |= MESH_FLAG_FACECAMERA;
			if (NULL != node->dissolveLevel && 0 == node->dissolveCount) {
				Lws_SetDissolveLevel(scene, node, node->dissolveLevel[0]);
				node->dissolveLevel = NULL;
			}
		} else Error_Fatal(TRUE, Error_Format("Missing object file in lightwave scene \"%s\"", node->name));

/*		LPDIRECT3DRMMESHBUILDER3 testMesh;
		LPDIRECT3DRMMESH mesh;
		UCHAR path[256];

		sprintf(path, "%s.x", node->name);
	
		lpD3DRM()->lpVtbl->CreateMeshBuilder(lpD3DRM(), &testMesh);
		if (D3DRM_OK == testMesh->lpVtbl->Load(testMesh, path, NULL, D3DRMLOAD_FROMFILE, NULL, NULL)) {
			testMesh->lpVtbl->CreateMesh(testMesh, &mesh);
			frame->lpVtbl->AddVisual(frame, (struct IUnknown *) mesh);
		}// else Error_Fatal(TRUE, "Cannot find file");
		testMesh->lpVtbl->Release(testMesh);
*/	}

	for (child=node->childList ; child ; child=child->next) {
		Lws_LoadNodes(scene, child);
	}
}

VOID Lws_Debug_Dump(lpLws_Info scene) {

	lpLws_Node root;

	Error_Debug(Error_Format("FirstFrame\t%i\n", scene->firstFrame));
	Error_Debug(Error_Format("LastFrame\t%i\n", scene->lastFrame));
	Error_Debug(Error_Format("FPS\t%f\n", scene->fps));

	for (root=scene->masterNode ; root ; root=root->next) {
		Error_Debug(Error_Format("Root node: <%s> (%i)\n", root->name, root->reference));
		Lws_Debug_DumpChildren(root, 1);
	}
}

static VOID Lws_Debug_DumpChildren(lpLws_Node parent, ULONG level) {

	lpLws_Node child;
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

VOID Lws_Free(lpLws_Info scene) {

	lpLws_Node node;
	lpLws_Info clonedFrom;
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
			if (scene->triggerCount) Mem_Free(scene->triggerList);
		}

		Mem_Free(scene->frameList);
		Mem_Free(scene);
	}

	if (clonedFrom) Lws_Free(clonedFrom);
}

static VOID Lws_FreeNode(lpLws_Info scene, lpLws_Node node) {

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

/*
	char path[PATH_LEN];
	int n,lws=2;
	unsigned int objf=0,keyFrames,keyCount,kfp=0;
	float flt;
	LWSC scn={0};
	LWOBJ lwo={0};
	LWKEYFRAME lwk={0};

	sprintf(path,"%s.lws", file);
	if(openComm(path))
	{
		while(getCommLine(&n))
		{
			if(n)
			{
				if(!lws)
				{
					if(!objf)
					{
						if(compCom(0,"FirstFrame") && comFloat(1,&flt))
						{
							scn.lwsFrameFirst=flt;
						}
						else if(compCom(0,"LastFrame") && comFloat(1,&flt))
						{
							scn.lwsFrameLast=flt;
						}
						else if(compCom(0,"FrameStep") && comFloat(1,&flt))
						{
							scn.lwsFrameStep=flt;
						}
						else if(compCom(0,"FramesPerSecond") && comFloat(1,&flt))
						{
							scn.lwsFramePerSecond=flt;
						}
						else if((compCom(0,"AddNullObject") || compCom(0,"LoadObject")) && comExist(1))
						{
							int len;
							char objPath[PATH_LEN],loadPath[PATH_LEN],temp[PATH_LEN];

							objf=1;
							strcpy(objPath,com[1]);
							ZeroMemory(&lwo,sizeof(LWOBJ));
							if(compCom(0,"LoadObject"))
							{
								_splitpath(objPath,NULL,NULL,objPath,NULL);
								_splitpath(path,NULL,temp,NULL,NULL);
								sprintf(loadPath,"%s%s",temp,objPath);
								LoadLWOB(loadPath, &lwo.lwoSize, &lwo.lwoVerts, &lwo.lwoPolys, &lwo.lwoSurf, &lwo.lwoSurfList, dflag);
							}
							lwo.lwoParentObject=-1;
							len=strlen(objPath)+1;
							if(len&1)
								len++;
							lwo.lwoName=malloc(len);
							ZeroMemory(lwo.lwoName,len);
							strcpy(lwo.lwoName,objPath);
							if(comExist(2))
							{
								len=strlen(com[2])+1;
								if(len&1)
									len++;
								lwo.lwoName2=malloc(len);
								ZeroMemory(lwo.lwoName2,len);
								strcpy(lwo.lwoName2,com[2]);
							}
						}
					}
					else
					{
						LWKEYFRAME *lkfp,**lkfpp;
						if(objf==1)
						{
							unsigned int sf1,sf2;
							ZeroMemory(&lwk,sizeof(LWKEYFRAME));
							kfp=0;
							if(compCom(0,"ShowObject") && comInt(1,&sf1) && comInt(2,&sf2))
							{
								lwo.lwoShowFrame[0]=sf1;
								lwo.lwoShowFrame[1]=sf2;
								objf++;
							}
						}
						else if(objf==2)
						{
							int len;
							if(compCom(0,"ObjectMotion") && comExist(1))
							{
								len=strlen(com[1])+1;
								if(len&1)
									len++;
								lwo.lwoObjectMotion=malloc(len);
								ZeroMemory(lwo.lwoObjectMotion,len);
								strcpy(lwo.lwoObjectMotion,com[1]);
								objf++;
							}
						}
						else if(objf==3)
						{
							if(compCom(0,"9"))
								objf++;
						}
						else if(objf==4)
						{
							if(comInt(0,&keyFrames))
							{
								keyCount=0;
								objf++;
								kfp=0;
							}
						}
						else if(objf==5)
						{
							if(keyCount<keyFrames)
							{
								int kfpc;
								float *ft[]={&lwk.lwkfXpos,&lwk.lwkfYpos,&lwk.lwkfZpos,
								&lwk.lwkfHeading,&lwk.lwkfPitch,&lwk.lwkfBank,
								&lwk.lwkfXScale,&lwk.lwkfYScale,&lwk.lwkfZScale,
								&lwk.lwkfFrame,&lwk.lwkfLinear,
								&lwk.lwkfTension,&lwk.lwkfContinuity,&lwk.lwkfBias};

								kfpc=0;
								while (comFloat(kfpc,ft[kfp]) && (objf==5))
								{
									kfp++,kfpc++;
									if(kfp==14)
									{
										kfp=0;
										keyCount++;
										if(keyCount>=keyFrames)
										{
											objf++;
										}
										
										lkfp=(LWKEYFRAME *)malloc(sizeof(LWKEYFRAME));
										lkfpp=malloc((lwo.lwoFrameCount+1)*sizeof(LWKEYFRAME *));
										if(lwo.lwoFrameCount)
										{
											memcpy(lkfpp,lwo.lwoKeyFrames,lwo.lwoFrameCount*sizeof(LWKEYFRAME *));
											free(lwo.lwoKeyFrames);
										}
										memcpy(lkfp,&lwk,sizeof(LWKEYFRAME));
										*(lkfpp+lwo.lwoFrameCount)=lkfp;
										lwo.lwoKeyFrames=lkfpp;
										lwo.lwoFrameCount++;
									}
								}
							}
						}
						else if(objf==6)
						{
							if(compCom(0,"EndBehavior") && comInt(1,&lwo.lwoEndBehaviour))
							{
							}
							else if(compCom(0,"ParentObject") && comInt(1,&lwo.lwoParentObject))
							{
							}
							else if(compCom(0,"ShadowOptions") && comInt(1,&lwo.lwoShadowOptions))
							{
								LWOBJ *objp,**objpp;

								objp=(LWOBJ *)malloc(sizeof(LWOBJ));
								objpp=malloc((scn.lwsObjCount+1)*sizeof(LWOBJ *));
								if(scn.lwsObjCount)
								{
									memcpy(objpp,scn.lwsObjects,scn.lwsObjCount*sizeof(LWOBJ *));
									free(scn.lwsObjects);
								}
								memcpy(objp,&lwo,sizeof(LWOBJ));
								*(objpp+scn.lwsObjCount)=objp;
								scn.lwsObjects=objpp;
								scn.lwsObjCount++;
								objf=0;
							}
						}
					}
				}
				else if(lws==2)
				{
					if(compCom(0,"LWSC"))
						lws=1;
				}
				else if(lws==1)
				{
					if(compCom(0,"1"))
						lws=0;
				}
			}
		}
	}

	*scene=malloc(sizeof(LWSC));
	memcpy(*scene,&scn,sizeof(LWSC));
	return TRUE;
}
*/