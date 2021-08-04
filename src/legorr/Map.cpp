
#include "Common.h"


struct MapFileInfo
{
	/*00,4*/ char Signature[4]; // "MAP "
	/*04,4*/ unsigned int fileSize;
	/*08,4*/ int width;
	/*0c,4*/ int height;
	/*10,*/  unsigned short blocks[1]; // dummy accessor
};

struct LevelBlock
{
	 // 4:?,5:cryore,6:erode
	/*04,4*/ undefined4 blockpointers_4;
	/*08,4*/ undefined4 path_8;
	/*0c,4*/ unsigned int flags_c;


	/*34,4*/ undefined4 ai_34;
	/*38,4*/ undefined4 fallin_38;
	/*3c,4*/ undefined4 fallin_3c;
	/*48*/
};

struct SurfaceTextureGrid
{
	/*0,4*/ int width;
	/*4,4*/ int height;
	/*8,4*/ IDirectDrawSurface4* grid; // allocated as width * height * sizeof(IDirectDrawSurface4*)
	/*c*/
};

// <LegoRR.exe @0040b240>
SurfaceTextureGrid* __cdecl lego::game::Level_LoadTextureBaseName(const char* textureBaseName, unsigned int width, unsigned int height)
{
	// SurfaceTextureGrid* texGrid; // uint *buffer;
	void *pvVar1;
	undefined **ppuVar2;
	unsigned int uVar3;
	unsigned int uVar4;
	int iVar5;
	int local_404;
	char local_400[1024];
	
	SurfaceTextureGrid* texGrid = (SurfaceTextureGrid*)msvc::malloc(0xc /*sizeof(SurfaceTextureGrid)*/);
	if (!texGrid)
		return NULL;
	
	IDirectDrawSurface4* grid = (IDirectDrawSurface4*)msvc::malloc(height * width * sizeof(IDirectDrawSurface4*));
	texGrid->grid = grid;
	if (grid == NULL) {
		msvc::free(texGrid);
		// texGrid = NULL;
		return NULL;
	}

	texGrid->width  = width;
	texGrid->height = height;
	unsigned int uVar3 = 0;
	if (height != 0) {
		local_404 = 0;
		for (unsigned int y = 0; y < height; y++) {
			for (unsigned int x = 0; x < width; x++) {
				// find files in the format: Texture//Path//BaseName##.bmp, where X is # is a single hex digit.
				//  The formatting only coordinates digits to a single,
				//  so this cannot contain both a width and height > 16 (0xf is the max digit used with 16).
				msvc::sprintf(local_400, "%s%0.1x%0.1x.bmp", textureBaseName, x, y);
			}
		}
		do {
			uVar4 = 0;
			iVar5 = local_404;
			if (width != 0) {
				do {
					msvc::sprintf(local_400, "%s%0.1x%0.1x.bmp", textureBaseName, uVar4, uVar3);
					ppuVar2 = FUN_004747b0(local_400, (undefined4 *)0x1, (undefined4 *)0x0, 0);
					uVar4++;
					*(undefined ***)((buffer[2] - 4) + iVar5 + 4) = ppuVar2;
					iVar5 += 4;
				} while (uVar4 < width);
			}
			uVar3 += 1;
			local_404 += width * 4;
		} while (uVar3 < height);
		return texGrid;
	}


	if (texGrid != NULL) {
		void* grid = msvc::malloc(height * width * 0x4 /*sizeof(unsigned int)*/);
		texGrid->grid = grid;
		if (grid == NULL) {
			msvc::free(texGrid);
			// texGrid = NULL;
			return NULL;
		}
		else {
			texGrid->width  = width;
			texGrid->height = height;
			unsigned int uVar3 = 0;
			if (height != 0) {
				local_404 = 0;
				do {
					uVar4 = 0;
					iVar5 = local_404;
					if (width != 0) {
						do {
							msvc::sprintf(local_400, "%s%0.1x%0.1x.bmp", textureBaseName, uVar4, uVar3);
							ppuVar2 = FUN_004747b0(local_400, (undefined4 *)0x1, (undefined4 *)0x0, 0);
							uVar4++;
							*(undefined ***)((buffer[2] - 4) + iVar5 + 4) = ppuVar2;
							iVar5 += 4;
						} while (uVar4 < width);
					}
					uVar3 += 1;
					local_404 += width * 4;
				} while (uVar3 < height);
				return texGrid;
			}
		}
	}
	return texGrid;
}

// <LegoRR.exe @004333f0>
void __cdecl Map_GetDimensions(int sharedIndex, int* out_width, int* out_height)
{
	MapFileInfo* mapData = (MapFileInfo*)File_SharedGetData(sharedIndex);
	*out_width  = mapData->width;
	*out_height = mapData->height;
}

// <LegoRR.exe @00431910>
unsigned short __cdecl Map_GetCoordinate(int sharedIndex, int x, int y)
{
	
	MapFileInfo* mapData = (MapFileInfo*)File_SharedGetData(sharedIndex);
	int width, height;
	Map_GetDimensions(sharedIndex, &width, &height);
	return mapData->blocks[width * y + x];
	/*uint sharedIndex;
	void *pvVar1;
	int local_4;

	void* mapData = File_SharedGetData(sharedIndex);
	int width, height;
	Map_GetDimensions(sharedIndex, &width, &height);
	return *(unsigned short*)((int)mapData + 0x10 + (width * y + x) * sizeof(unsigned short));*/
}

// <LegoRR.exe @0042ba90>
BOOL __cdecl FUN_0042ba90(LevelData* level, const char* keyBasePath)
{
	CFGProperty *root;
	char *pcVar1;
	int iVar2;
	int iVar3;
	uint *puVar4;
	BOOL result;
	
	root = globals::g_Game.LegoCfgRoot;
	result = false /*0*/;
	const char* keyValue;
	const char* keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "surftextwidth", NULL);
	if (!CFG_getPropertyValue(root, keyPath)) {
		keyValue = ""/*EMPTYSTR*/;
	}
	else {
		keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "surftextwidth", NULL);
		keyValue = (char *)CFG_getPropertyValue(root, keyPath);
	}
	int surfaceTextureWidth = msvc::atoi(keyValue);
	if (surfaceTextureWidth != 0) {
		keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "surftextheight", NULL);
		if (!CFG_getPropertyValue(root, keyPath)) {
			keyValue = ""/*EMPTYSTR*/;
		}
		else {
			keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "surftextheight", NULL);
			keyValue = (char *)CFG_getPropertyValue(root, keyPath);
		}
		int surfaceTextureHeight = msvc::atoi(keyValue);
		if (surfaceTextureHeight != 0) {
			level->surfTextSize.width  = surfaceTextureWidth;
			level->surfTextSize.height = surfaceTextureHeight;
			FUN_0042b780(level->surfaceMap);
			FUN_0044eb40(level->surfaceMap);
			keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "meshbasename", NULL);
			const char* meshBaseName = CFG_getPropertyValue(root, keyPath);
			if (meshBaseName != 0) {
				keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "texturebasename", NULL);
				const char* textureBaseName = CFG_getPropertyValue(root, keyPath);
				if (textureBaseName != 0) {
					void* pVar4 = FUN_0040b240(textureBaseName, level->surfTextSize.width, level->surfTextSize.height);
					level->field_0x7c = pVar4; // texture?
					if (pVar4 != NULL) {
						FUN_0044f4e0(level->surfaceMap, pVar4);
						BVar5 = FUN_0042b260(level, meshBaseName);
						if (BVar5 != 0) {
							keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "rooftexture", NULL);
							const char* roofTexture = CFG_getPropertyValue(root, keyPath);
							if (roofTexture != NULL) {
								BVar5 = FUN_00463120(roofTexture);
								if (BVar5 != 0) {
									result = true /*1*/;
								}
							}
						}
					}
				}
			}
			keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "meshbasename", NULL);
			iVar2 = CFG_getPropertyValue(root, keyPath);
			if (iVar2 != 0) {
				keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "texturebasename", NULL);
				iVar2 = CFG_getPropertyValue(root, keyPath);
				if (iVar2 != 0) {
					puVar4 = FUN_0040b240(iVar2,level->field_0x74, level->field_0x78);
					level->field_0x7c = puVar4;
					if (puVar4 != (uint *)NULL) {
						FUN_0044f4e0((int)level->surfaceMap, puVar4);
						iVar2 = FUN_0042b260((int)level);
						if (iVar2 != 0) {
							keyPath = CFG_joinPath(globals::g_Game.CfgRootName, keyBasePath, "rooftexture", NULL);
							pcVar1 = (char *)CFG_getPropertyValue(root, keyPath);
							if (pcVar1 != (char *)NULL) {
								iVar2 = FUN_00463120(pcVar1);
								if (iVar2 != 0) {
									result = true /*1*/;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}

// <LegoRR.exe @0042b440>
BOOL __cdecl Level_LoadMapFiles(LevelData* level, const char* surfaceMap, const char* predugMap,int param_4, const char* terrainMap, int param_6, const char* blockPointersMap, undefined4 param_8, const char* cryOreMap, char param_10, char *erodeMap, const char* pathMap, int param_13, const char* textureSet, const char* emergeMap, const char* aiMap, char *fallinMap)
{
	short sVar1;
	LevelSurfaceMap *pLVar2;
	LevelStruct_3c *pLVar3;
	BOOL BVar4;
	uint uVar5;
	int iVar6;
	uint uVar7;
	int *piVar8;
	uint uVar9;
	int *piVar10;
	
	pLVar2 = (LevelSurfaceMap *)
			FUN_0044e380(globals::g_Game.ptr_18,surfaceMap,level->BlockSize,level->RoughLevel);
	level->surfaceMap = pLVar2;
	if (pLVar2 != (LevelSurfaceMap *)NULL) {
		pLVar3 = (LevelStruct_3c *)
				FUN_0045dd50((int)pLVar2,(int *)&globals::g_Game.float_324,
							(int)globals::g_Game.float_334);
		level->struct3c_84 = pLVar3;
		FUN_0044f750((uint *)level->surfaceMap,1);
		FUN_0044e970((int)level->surfaceMap,0x70);
		FUN_0044e970((int)level->surfaceMap,0x70);
		FUN_0044e970((int)level->surfaceMap,0x70);
		FUN_0044e970((int)level->surfaceMap,0x70);
		FUN_0044e970((int)level->surfaceMap,0x70);
		FUN_0044e970((int)level->surfaceMap,0x70);
		pLVar2 = level->surfaceMap;
		(level->dimensions).width = (pLVar2->dimensions).width;
		(level->dimensions).height = (pLVar2->dimensions).height;
		FUN_0040cdb0((int)level);
		FUN_004664f0((int)level);
		if (level->UseRoof != BOOL3_FALSE) {
		FUN_00463060(globals::g_Game.ptr_18,(level->dimensions).width,(level->dimensions).height);
		FUN_00463770(1);
		}
		pLVar2 = (LevelSurfaceMap *)FUN_0042ba90((int)level, textureSet);
		if (pLVar2 != (LevelSurfaceMap *)NULL) {
			pLVar2 = (LevelSurfaceMap *)malloc((level->dimensions).height * (level->dimensions).width * 0x48);
			level->blocks = (LevelBlock *)pLVar2;
			if (pLVar2 != (LevelSurfaceMap *)NULL) {
				uVar7 = 0;
				for (uVar5 = (uint)((level->dimensions).height * (level->dimensions).width * 0x48) >> 2; uVar5 != 0; uVar5 -= 1) {
					pLVar2->field_0x0 = 0;
					pLVar2 = (LevelSurfaceMap *)&pLVar2->field_0x4;
				}
				for (iVar6 = 0; iVar6 != 0; iVar6 += -1) {
					*(undefined *)&pLVar2->field_0x0 = 0;
					pLVar2 = (LevelSurfaceMap *)((int)&pLVar2->field_0x0 + 1);
				}
				if ((level->dimensions).height != 0) {
					do {
						uVar5 = (level->dimensions).width;
						uVar9 = 0;
						if (uVar5 != 0) {
						do {
							*(undefined *)&level->blocks[uVar7 * uVar5 + uVar9].field_0 = 0;
							*(undefined *)
							((int)&level->blocks[uVar7 * (level->dimensions).width + uVar9].field_0 + 1) = 0;
							*(undefined *)
							((int)&level->blocks[uVar7 * (level->dimensions).width + uVar9].field_0 + 2) = 0;
							level->blocks[uVar7 * (level->dimensions).width + uVar9].path_8 = 0;
							*(undefined *)
							((int)&level->blocks[uVar7 * (level->dimensions).width + uVar9].field_0 + 3) = 0;
							level->blocks[uVar7 * (level->dimensions).width + uVar9].field_18 = 0;
							level->blocks[uVar7 * (level->dimensions).width + uVar9].field_14 = 0;
							sVar1 = util::randomInt16();
							iVar6 = uVar7 * (level->dimensions).width + uVar9;
							uVar9 += 1;
							*(short *)&level->blocks[iVar6].field_20 = sVar1;
							uVar5 = (level->dimensions).width;
						} while (uVar9 < uVar5);
						}
						uVar7 += 1;
					} while (uVar7 < (uint)(level->dimensions).height);
				}
				pLVar2 = (LevelSurfaceMap *)Level_LoadPredugMap(level,predugMap,param_4);
				if (pLVar2 != (LevelSurfaceMap *)NULL) {
					pLVar2 = (LevelSurfaceMap *)Level_LoadTerrainMap(level,terrainMap,param_6);
					if (pLVar2 != (LevelSurfaceMap *)NULL) {
						Level_LoadCryOreMap(level,cryOreMap,param_10);
						Level_LoadErodeMap(level,erodeMap);
						Level_LoadPathMap(level,pathMap,param_13);
						Level_LoadEmergeMap(level,emergeMap);
						Level_LoadAIMap(level,aiMap);
						Level_LoadFallinMap(level,fallinMap);
						BVar4 = Level_LoadBlockPointersMap(level,blockPointersMap,param_8);
						if (BVar4 != 0) {
							level->hasBlockPointers = 1;
						}
						piVar8 = (int *)NULL;
						if ((level->dimensions).height != 0) {
							do {
								piVar10 = (int *)NULL;
								if ((level->dimensions).width != 0) {
									do {
										FUN_0042f620((int)level,piVar10,piVar8);
										piVar10 = (int *)((int)piVar10 + 1);
									} while (piVar10 < (int *)(level->dimensions).width);
								}
								piVar8 = (int *)((int)piVar8 + 1);
							} while (piVar8 < (int *)(level->dimensions).height);
						}
						FUN_0044eb40((uint *)level->surfaceMap);
						FUN_0046de50(globals::g_Game.ptr_18,(int)level);
						pLVar2 = (LevelSurfaceMap *)0x1;
					}
				}
			}
		}
	}
	return (BOOL)pLVar2;
}

// <LegoRR.exe @0042cbc0>
BOOL __cdecl Level_LoadBlockPointersMap(LevelData* level, const char* filename, unsigned char modifierValue)
{
	if (!filename)
		return false;
	int sharedIndex = File_SharedOpen(filename, NULL);
	if (sharedIndex == -1)
		return false;
	
	int width, height;
	Map_GetDimensions(sharedIndex, &width, &height);
	if (width == level->dimensions.width && height == level->dimensions.height) {
		for (int y = 0; i < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char block = (unsigned char)Map_GetCoordinate(sharedIndex, x, y);
				// Local width can be used in-place of level->dimensions.width,
				//  since it's already checked to be the same above.
				*(unsigned char *)&level->blocks[x + y * width].blockpointers_4 = block - modifierValue;
				// *(unsigned char *)&level->blocks[x + y * level->dimensions.width].blockpointers_4 = block - modifierValue;
			}
		}
		File_SharedClose(sharedIndex);
		return true;
	}
	File_SharedClose(sharedIndex);
	return false;
}



// <LegoRR.exe @0042c900>
BOOL __cdecl lego::game::Level_LoadFallinMap(LevelData* level, const char* filename)
{
	globals::g_Game.hasFallins = false /*0*/;  // has fallins map?

	if (!filename)
		return false;
	int sharedIndex = File_SharedOpen(filename, NULL);
	if (sharedIndex == -1)
		return false;

	int width, height;
	Map_GetDimensions(sharedIndex, &width, &height);
	if (width == level->dimensions.width && height == level->dimensions.height) {
		for (int y = 0; i < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned int intensity = Map_GetCoordinate(sharedIndex, x, y);
				int idx = x + y * level->dimensions.width;
				level->blocks[idx].fallin_3c = 0;
				if (intensity != 0) {
					level->blocks[idx].fallin_3c = intensity;
					int multiplier = level->blocks[idx].field_20 % (intensity * globals::g_Game.FallinMultiplier * 25);
					level->blocks[idx].float_40 = (float)(unsigned long long)multiplier;
					level->blocks[idx].fallin_38 = false /*0*/;
					if (intensity > 4) {
						// (???) Is the fallin intensity severe? Allow caveins maybe?
						level->blocks[idx].fallin_3c = intensity - 4; // essentially set intensity from 5-8 to 1-4 regardless?
						level->blocks[idx].fallin_38 = true /*1*/; // higher intensity
					}
				}
			}
		}
		globals::g_Game.hasFallins = true /*1*/;  // has fallins map?
		File_SharedClose(sharedIndex);
		return true;
	}
	File_SharedClose(sharedIndex);
	return false;
}


// <LegoRR.exe @0042c5d0>
BOOL __cdecl lego::game::Level_LoadCryOreMap(LevelData* level, const char* filename, char modifierValue)
{
	if (!filename)
		return false;
	int sharedIndex = File_SharedOpen(filename, NULL);
	if (sharedIndex == -1)
		return false;
	
	int width, height;
	Map_GetDimensions(sharedIndex, &width, &height);
	if (width == level->dimensions.width && height == level->dimensions.height) {
		for (int y = 0; i < height; y++) {
			for (int x = 0; x < width; x++) {
				unsigned char block = (unsigned char)Map_GetCoordinate(sharedIndex, x, y);
				// Local width can be used in-place of level->dimensions.width,
				//  since it's already checked to be the same above.
							*(char *)((int)&level->blocks[(int)pcVar2].blockpointers_4 + 1) =
								(char)uVar1 - param_3;
				*(unsigned char *)&level->blocks[x + y * width].blockpointers_4 = block - modifierValue;
				// *(unsigned char *)&level->blocks[x + y * level->dimensions.width].blockpointers_4 = block - modifierValue;
			}
		}
		File_SharedClose(sharedIndex);
		return true;
	}
	File_SharedClose(sharedIndex);
	return false;

	uint sharedIndex;
	uint uVar1;
	char *pcVar2;
	char *x;
	uint y;
	uint local_4;
	
	sharedIndex = lego::file::File_SharedOpen(filename,(uint *)NULL);
	if (sharedIndex != 0xffffffff) {
		Map_GetDimensions(sharedIndex,(int *)&filename,(int *)&local_4);
		if ((filename == (char *)(level->dimensions).width) && (local_4 == (level->dimensions).height))
		{
			y = 0;
			pcVar2 = filename;
			uVar1 = local_4;
			if (local_4 != 0) {
				do {
					x = (char *)NULL;
					if (pcVar2 != (char *)NULL) {
						do {
							uVar1 = Map_GetCoordinate(sharedIndex,(int)x,y);
							pcVar2 = x + y * (level->dimensions).width;
							x = x + 1;
							*(char *)((int)&level->blocks[(int)pcVar2].blockpointers_4 + 1) =
								(char)uVar1 - param_3;
							pcVar2 = filename;
							uVar1 = local_4;
						} while (x < filename);
					}
					y += 1;
				} while (y < uVar1);
			}
			lego::file::File_SharedClose(sharedIndex);
			return 1;
		}
		lego::file::File_SharedClose(sharedIndex);
	}
	return 0;
}