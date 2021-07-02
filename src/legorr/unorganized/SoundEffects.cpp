

struct LegoSFXItem
{
	/*0,4*/ int sfxIndex;
	/*4,4*/ LegoSFXItem* sfxNext;
	/*8*/
};

enum LegoSFXFlags
{
	SFX_ISUSED   = 0x1,
	SFX_VOLUME   = 0x2, // '#%d#' specifier
	SFX_MULTIPLE = 0x4, // '*' specifier (and not '@' specifier)
	SFX_STREAMED = 0x8, // '@' specifier
};

struct LegoSFXData
{
	/*0,104*/ char filename[MAX_PATH /*260*/];       // 00507698
	/*104,4*/ unsigned int fileLength; // field_104; // 0050779c
	/*108,4*/ unsigned int avgBytesPerSec; // avgBytesPerSec // 005077a0
	/*10c,4*/ unsigned int field_10c;
	/*110,4*/ unsigned int num_pound;  // num_pound  // 005077a8
	/*114,4*/ unsigned int field_114;
	/*118,4*/ HGLOBAL field_118;
	/*11c,4*/ HGLOBAL field_11c;
	/*120,4*/ unsigned int field_120;
	/*124,4*/ unsigned int field_124;
	/*128,4*/ unsigned int field_128;
	/*12c,4*/ unsigned int field_12c;
	/*130,4*/ unsigned int sfxFlags; // 005077c8  (0x1 == isUsed)
	/*134*/
};

// lego::pool::ReservedPool<Struct_2c>__
// 0076be34
// UINT_0076dd74

// confirmed size of 495, see void __cdecl Main_Alloc_SFX_Names(void) <LegoRR.exe @00464a00>
// <LegoRR.exe @00502468>
static LegoSFXItem g_SFXProperty_TABLE[495];
// <LegoRR.exe @005033e0>
static LegoSFXItem g_SFXGroup_TABLE[200]; // unknown table size
// <LegoRR.exe @00507698 -> 00534878> g_SFXData_TABLE
static LegoSFXData g_SFXData_TABLE[600]; // unknown table size
// <LegoRR.exe @00503a28>
static int g_SFXGroup_COUNT; // unknown count

// <LegoRR.exe @00534878>
static BOOL g_DirectSoundEnabled;

// g_FILEPATH_DATADIR_1 0x005349a0


// <LegoRR.exe @00464f30>
BOOL __cdecl FUN_00464f30(char* param_1, int* out_index)
{
	uint uVar1;
	int iVar2;
	uint uVar3;
	int *piVar4;

	if (param_1 != NULL) {
		iVar2 = FUN_00477930(param_1, 0, 1);
		uVar3 = 0;
		uVar1 = DAT_00503a24 + 0x2d;
		piVar4 = DAT_00503a20;
		if (uVar1 != 0) {
			do {
			if (iVar2 == *piVar4) {
				*out_index = uVar3;
					return 1;
				}
				uVar3 += 1;
				piVar4 = piVar4 + 1;
			} while (uVar3 < uVar1);
		}
		if (((byte)g_UNKFLAGS__00503a2c & 2) != 0) {
			*out_index = uVar1;
			iVar2 = FUN_00477930(param_1, 0, 1);
			DAT_00503a20[uVar1] = iVar2;
			DAT_00503a24++;
			return true;
		}
	}
	return false;
}

// <LegoRR.exe @0047ab10>
BOOL __cdecl SFX_ValidateNumPound__0047ab10(int num_pound)
{
	
	if (num_pound >= -10000 && num_pound <= 0) {
		return true;
	}
	return false;
}

// <LegoRR.exe @00464fc0>
BOOL __cdecl SFX_LoadProperty__00464fc0(char* value, int index)
{
	LegoSFXItem* lastItem = NULL;
	LegoSFXItem* currentItem = g_SFXProperty_TABLE[index];
	currentItem->sfxNext = NULL; // 0

	bool success = true;
	bool flag_atsign = false; // flag '@' is global, once it's specified, it cannot be turned off
	                          // (however '@' can still be consumed for each item)
	int numParts = stringSplit(value, name_parts, ",");
	for (int i = 0; i < numParts; i++) {
		char* filename = name_parts[i];
		bool flag_asterisk = false; // flag '*' is local
		// FULL FORMAT: [*][#%d#][@]sound\path
		if (*filename == '*') { // FORMAT: *
			flag_asterisk = true;
			filename++; // skip '*' sign
		}
		int num_pound = 0; // number '#%d#' is local
		if (*filename == '#') { // FORMAT: #%d#
			filename++; // skip opening '#' sign
			char buffer_pound[64];
			for (int j = 0; *filename != '#'; filename++) {
				buffer_pound[j] = *filename;
			}
			num_pound = atoi(buffer_pound); // this is not null-terminated, WTF!?
			filename++; // skip closing '#' sign
		}
		if (*filename == '@') { // FORMAT: @
			flag_atsign = true;
			filename++; // skip '@' sign
		}
		int result = SFX_Load__0047ab30(filename, flag_atsign, flag_asterisk, num_pound);
		// during the second loop iteration, we will lose the index of the first sound
		currentItem->sfxIndex = result;
		if (result == -1) {
			success = false;
		}
		else {
			if (lastItem != NULL) {
				currentItem = g_SFXGroup_TABLE[g_SFXGroup_COUNT++];
				lastItem->sfxNext = currentItem;
				currentItem->sfxNext = NULL;
			}
			lastItem = currentItem;
		}
	}
	return success;
}
// 		else {
// 			nextItem = currentItem;
// 			if (lastItem != NULL) {
// 				currentItem = g_SFXGroup_TABLE[g_SFXGroup_COUNT++];
// 				lastItem->sfxNext = currentItem;
// 				currentItem->sfxNext = NULL;
// 				nextItem = currentItem;
// 			}
// 		}
// 		if (result == -1) {
// 			success = false;
// 			nextItem = lastItem;
// 		}
// 		else {
// 			nextItem = currentItem;
// 			if (lastItem != NULL) {
// 				currentItem = g_SFXGroup_TABLE[g_SFXGroup_COUNT++];
// 				lastItem->sfxNext = currentItem;
// 				currentItem->sfxNext = NULL;
// 				nextItem = currentItem;
// 			}
// 		}
// 		lastItem = nextItem;
// 		// *piVar5 = result;
// 		if (result == -1) {
// 			local_1d8 = 0;
// 			piVar2 = local_1d4;
// 		}
// 		else {
// 			piVar2 = piVar5;
// 			if (local_1d4 != (int *)NULL) {
// 				result = g_SFXGroup_COUNT * 8;
// 				piVar5 = (int *)(&g_SFXGroup_TABLE + result);
// 				g_SFXGroup_COUNT++;
// 				*(int **)(local_1d4 + 1) = piVar5;
// 				*(undefined4 *)(&DAT_005033e4 + result) = 0;
// 				piVar2 = piVar5;
// 			}
// 		}
// 		local_1d4 = piVar2;
// 	}
// 	if (local_1dc != 0) {
// 		char** part_ptr = name_parts;
// 		local_1e0 = name_parts;
// 		do {
// 			in_filename = *local_1e0;
// 			bool flag_asterisk = false;
// 			if (*in_filename == '*') {
// 				in_filename++;
// 				flag_asterisk = true;
// 			}
// 			int num_pound = 0;
// 			if (*in_filename == '#') {
// 				cVar3 = in_filename[1];
// 				in_filename++;
// 				if (cVar3 != '#') {
// 					pcVar4 = local_1d0;
// 					do {
// 						*pcVar4 = cVar3;
// 						cVar3 = in_filename[1];
// 						pcVar4++;
// 						in_filename++;
// 					} while (cVar3 != '#');
// 				}
// 				num_pound = atoi(local_1d0);
// 				in_filename++;
// 			}
// 			if (*in_filename == '@') {
// 				flag_atsign = true;
// 				in_filename++;
// 			}
// 			int result = SFX_Load__0047ab30(in_filename, flag_atsign, flag_asterisk, num_pound);
// 			*piVar5 = result;
// 			if (result == -1) {
// 				local_1d8 = 0;
// 				piVar2 = local_1d4;
// 			}
// 			else {
// 				piVar2 = piVar5;
// 				if (local_1d4 != (int *)NULL) {
// 					result = g_SFXGroup_COUNT * 8;
// 					piVar5 = (int *)(&g_SFXGroup_TABLE + result);
// 					g_SFXGroup_COUNT++;
// 					*(int **)(local_1d4 + 1) = piVar5;
// 					*(undefined4 *)(&DAT_005033e4 + result) = 0;
// 					piVar2 = piVar5;
// 				}
// 			}
// 			local_1d4 = piVar2;
// 			local_1e0 = local_1e0 + 1;
// 			local_1dc--;
// 		} while (local_1dc != 0);
// 	}
// 	return local_1d8;
// }



// <LegoRR.exe @0047ab10>
//SFX_ValidateNumPound__0047ab10

// <LegoRR.exe @0047ad90>
//SFX__Next

// <LegoRR.exe @0047b840>
//RIFF_OpenInMemory__0047b840

// <LegoRR.exe @00489130>
//RIFF_OpenStreamed__00489130

// <https://docs.microsoft.com/en-us/previous-versions//dd757334(v=vs.85)>

struct tWAVEFORMATEX {
    unsigned short wFormatTag;
    unsigned short nChannels;
    unsigned int nSamplesPerSec;
    unsigned int nAvgBytesPerSec;
    unsigned short nBlockAlign;
    unsigned short wBitsPerSample;
    unsigned short cbSize;
};

// <https://docs.microsoft.com/en-us/windows/win32/multimedia/performing-file-i-o-on-riff-files>

// <https://docs.microsoft.com/en-us/previous-versions//dd757331(v=vs.85)>
HMMIO mmioOpenA(
   LPTSTR     szFilename,
   LPMMIOINFO lpmmioinfo,
   DWORD      dwOpenFlags
);

// <https://docs.microsoft.com/en-us/previous-versions//dd757318(v=vs.85)>
MMRESULT mmioDescend(
   HMMIO      hmmio,
   LPMMCKINFO lpck,
   LPMMCKINFO lpckParent,
   UINT       wFlags
);

// <https://docs.microsoft.com/en-us/previous-versions//dd757334(v=vs.85)>
LONG mmioRead(
   HMMIO hmmio,
   HPSTR pch,
   LONG  cch
);

// <https://docs.microsoft.com/en-us/previous-versions//dd757316(v=vs.85)>
MMRESULT mmioClose(
   HMMIO hmmio,
   UINT  wFlags
);

// <https://docs.microsoft.com/en-us/previous-versions//dd757336(v=vs.85)>
LONG mmioSeek(
   HMMIO hmmio,
   LONG  lOffset,
   int   iOrigin
);

// <https://docs.microsoft.com/en-us/previous-versions//dd757315(v=vs.85)>
MMRESULT mmioAscend(
   HMMIO      hmmio,
   LPMMCKINFO lpck,
   UINT       wFlags
);

struct _MMCKINFO {
    FOURCC ckid;
    DWORD cksize;
    FOURCC fccType;
    DWORD dwDataOffset;
    DWORD dwFlags;
};

struct waveformat_tag {
    unsigned short wFormatTag;
    unsigned short nChannels;
    unsigned int nSamplesPerSec;
    unsigned int nAvgBytesPerSec;
    unsigned short nBlockAlign;
};

struct pcmwaveformat_tag {
    WAVEFORMAT wf;
    unsigned short wBitsPerSample;
};

// <LegoRR.exe @00534878>
static BOOL g_DirectSoundEnabled;

// <LegoRR.exe @0054586c>
static BOOL g_SoundEnabled;

// g_FILEPATH_DATADIR_1 0x005349a0

// <LegoRR.exe @0047ad90>
BOOL __cdecl SFX__Next(int* out_sfxIndex)
{
	for (int i = 0; i < 600; i++) {
		if ((g_SFXData_TABLE[i]->sfxFlags & 0x1) == 0) {
			*out_sfxIndex = i;
			return true;
		}
	}
	return false;

	// byte *pbVar1;
	// int iVar2;

	// iVar2 = 0;
	// pbVar1 = &DAT_005077c8;
	// do {
	// 	if ((*pbVar1 & 1) == 0) {
	// 		*out_sfxIndex = iVar2;
	// 		return true;
	// 	}
	// 	pbVar1 = pbVar1 + 0x134;
	// 	iVar2++;
	// } while (pbVar1 < g_FILEPATH_DATADIR_1 + 8); // 0x005349a0
	// return false;
}

// <LegoRR.exe @0047ab30>
int __cdecl SFX_Load__0047ab30(char *in_filename, BOOL flag_atsign, BOOL flag_asterisk, int num_pound)

{
	char cVar1;
	bool success;
	int iVar3;
	char *filename;
	// FILE *file;
	BOOL BVar4;
	undefined4 uVar5;
	uint uVar6;
	uint uVar7;
	LPCSTR filename_00;
	undefined4 *puVar8;
	char *pcVar9;
	undefined4 *puVar10;
	int sfxIndex;
	char wavFileBuffer[260];
	char cdromBuffer[260];
	
	bool success = false;
	if (g_DirectSoundEnabled != false && SFX__Next(&sfxIndex) != false) {
		*(undefined4 *)(&DAT_005077c8 + sfxIndex * 0x134) = 0;
		sprintf(wavFileBuffer, "%s.wav", in_filename);
		if (flag_atsign == false) {
			iVar3 = RIFF_OpenInMemory__0047b840((HMMIO)(&g_SFXData_TABLE + sfxIndex * 0x134), wavFileBuffer, flag_asterisk);
			if (iVar3 != 0) {
				uVar6 = *(uint *)(&DAT_005077c8 + sfxIndex * 0x134);
				*(uint *)(&DAT_005077c8 + sfxIndex * 0x134) = uVar6 & 0xfffffff7;
				if (flag_asterisk != false) {
					*(uint *)(&DAT_005077c8 + sfxIndex * 0x134) = uVar6 & 0xfffffff7 | 4;
				}
				success = true;
			}
		}
		else {
			const char* datadirFile = Path_JoinDataDir(wavFileBuffer);
			const char* finalFile = NULL;
			FILE* file = fopen(datadirFile, "r");
			if (file != NULL) {
				fclose(file);
				finalFile = datadirFile;
			}
			else if (Path_GetCDROMDataPath(cdromBuffer, wavFileBuffer) != false) {
				 // file doesn't exist, check CDROM path
				finalFile = cdromBuffer;
			}
			// if (file == NULL) { // file doesn't exist, check CDROM path
			// 	if (Path_GetCDROMDataPath(cdromBuffer, wavFileBuffer) != false) {
			// 		finalFile = cdromBuffer;
			// 	}
			// }
			// else {
			// 	fclose(file);
			// 	finalFile = datadirFile;
			// }
			if (finalFile != NULL) {
				file = fopen(finalFile, "r");
				if (file != NULL) { //&& (file = , file != (FILE *)NULL)) {
					fseek(file, 0, SEEK_END /*2*/);
					int fileLength = ftell(file);
					*(int *)(&DAT_0050779c + sfxIndex * 0x134) = fileLength;
					iVar3 = sfxIndex * 0x134;
					uVar5 = RIFF_OpenStreamed__00489130(finalFile);
					*(undefined4 *)(&DAT_005077a0 + iVar3) = uVar5;
					*(uint *)(&DAT_005077c8 + iVar3) |= 0x8;
					fclose(file);
					success = true;
				}
			}
		}
		if (success) {
			strcpy((&g_SFXData_TABLE + sfxIndex * 0x134), wavFileBuffer);
			if (SFX_ValidateNumPound__0047ab10(num_pound) == 0) {
				*(int *)(&DAT_005077a8 + sfxIndex * 0x134) = 0;
			}
			else {
				*(int *)(&DAT_005077a8 + sfxIndex * 0x134) = num_pound;
			}
			*(uint *)(&DAT_005077c8 + sfxIndex * 0x134) |= 0x3;
			return sfxIndex;
		}
	}
	return -1;
}



// <LegoRR.exe @00489130>
unsigned int __cdecl RIFF_OpenStreamed__00489130(LPSTR filename)
{
	HMMIO hmmio;
	MMRESULT MVar1;
	LONG LVar2;
	DWORD DVar3;
	PCMWAVEFORMAT waveFmt;
	MMCKINFO riffTag;
	MMCKINFO fmtTag;

	unsigned int avgBPS = 0;
	HMMIO hmmio = mmioOpenA(filename, NULL, MMIO_READ /*0*/);
	if (hmmio != NULL) {
		MMRESULT mmResult = mmioDescend(hmmio, &riffTag, NULL, 0);
		//                                                       /* "RIFF" */                     /* "WAVE" */
		if (mmResult == MMSYSERR_NOERROR /*0*/ && riffTag.ckid == 0x46464952 && riffTag.fccType == 0x45564157) {
			//           /* "fmt " */
			fmtTag.ckid = 0x20746d66;
			mmResult = mmioDescend(hmmio, &fmtTag, &riffTag, MMIO_FINDCHUNK /*0x10*/);
			if (mmResult == MMSYSERR_NOERROR /*0*/ && fmtTag.cksize >= 0x10) {
				int bytesRead = mmioRead(hmmio, (HPSTR)&waveFmt, 0x10);
				if (bytesRead == 0x10) {
					avgBPS = waveFmt.wf.nAvgBytesPerSec;
				}
			}
		}
		if (hmmio != NULL) {
			mmioClose(hmmio, 0);
		}
	}
	return avgBPS;
}

// <LegoRR.exe @00488f30>
MMRESULT __cdecl RIFF_OpenInMemory_A___00488f30(HPSTR fileData,LONG fileSize,HMMIO *out_hmmio,HGLOBAL *out_hGlobal,LPMMCKINFO riffTag)
{
  HMMIO hmmio;
  LONG LVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  MMRESULT MVar5;
  _MMIOINFO *p_Var6;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  MMCKINFO fmtTag;
  MMIOINFO local_48;
  
  *out_hGlobal = (HGLOBAL)0x0;
  iVar4 = 0x12;
  p_Var6 = &local_48;
  while (iVar4 != 0) {
    iVar4 += -1;
    p_Var6->dwFlags = 0;
    p_Var6 = (_MMIOINFO *)&p_Var6->fccIOProc;
  }
                    /* "MEM " */
  local_48.fccIOProc = 0x204d454d;
  local_48.pchBuffer = fileData;
  local_48.cchBuffer = fileSize;
  hmmio = mmioOpenA((LPSTR)0x0,(LPMMIOINFO)&local_48,0x10000);
  if (hmmio == (HMMIO)0x0) {
    MVar5 = 0xe100;
  }
  else {
    MVar5 = mmioDescend(hmmio,riffTag,(MMCKINFO *)0x0,0);
    if (MVar5 == 0) {
      if ((riffTag->ckid == 0x46464952) && (riffTag->fccType == 0x45564157)) {
        fmtTag.ckid = 0x20746d66;
        MVar5 = mmioDescend(hmmio,(LPMMCKINFO)&fmtTag,(MMCKINFO *)riffTag,0x10);
        if (MVar5 != 0) goto LAB_004890e9;
        if (fmtTag.cksize >= 0x10) {
          LVar1 = mmioRead(hmmio, (HPSTR)&local_6c, 0x10);
          if (LVar1 != 0x10) {
            MVar5 = 0xe102;
            goto LAB_004890e9;
          }
          if ((short)local_6c == 1) {
            fileData = (HPSTR)0x0;
          }
          else {
            LVar1 = mmioRead(hmmio, (HPSTR)&fileData, 2);
            if (LVar1 != 2) {
              MVar5 = 0xe102;
              goto LAB_004890e9;
            }
          }
          puVar2 = (undefined4 *)GlobalAlloc(0, ((uint)fileData & 0xffff) + 0x12);
          *(undefined4 **)out_hGlobal = puVar2;
          if (puVar2 == (undefined4 *)NULL) {
            MVar5 = 0xe000;
            goto LAB_004890e9;
          }
          *puVar2 = local_6c;
          puVar2[1] = local_68;
          puVar2[2] = local_64;
          puVar2[3] = local_60;
          *(short *)((int)*out_hGlobal + 0x10) = (short)fileData;
          if (((short)fileData == 0) ||
             (uVar3 = mmioRead(hmmio,(HPSTR)((int)*out_hGlobal + 0x12),(uint)fileData & 0xffff),
             uVar3 == ((uint)fileData & 0xffff))) {
            MVar5 = mmioAscend(hmmio, (LPMMCKINFO)&fmtTag, 0);
            if (MVar5 == 0) {
              *out_hmmio = hmmio;
              return 0;
            }
            goto LAB_004890e9;
          }
        }
      }
      MVar5 = 0xe101;
    }
  }
LAB_004890e9:
  if (*out_hGlobal != (HGLOBAL)0x0) {
    GlobalFree(*out_hGlobal);
    *out_hGlobal = (HGLOBAL)0x0;
  }
  if (hmmio != (HMMIO)0x0) {
    mmioClose(hmmio,0);
    hmmio = (HMMIO)0x0;
  }
  *out_hmmio = hmmio;
  return MVar5;
}


/* WARNING: Type propagation algorithm not settling */

// <LegoRR.exe @0047b840>
BOOL __cdecl RIFF_OpenInMemory__0047b840(LegoSFXData* item, const char* filename, BOOL flag_asterisk)
{
	HMMIO pHVar1;
	// byte *buffer;
	MMRESULT MVar2;
	HGLOBAL pvVar3;
	uint uVar4;
	int iVar5;
	HMMIO pHVar6;
	HMMIO__ local_2c;
	MMCKINFO local_28;
	MMCKINFO riffTag;

	// pHVar1 = param_1;
	// iVar5 = 0x4d;
	// pHVar6 = param_1;
	// while (iVar5 != 0) {
	// 	iVar5 += -1;
	// 	pHVar6->unused = 0;
	// 	pHVar6 = pHVar6 + 1;
	// }
	memset(item, 0, 0x134);
	unsigned int fileLength;
	unsigned char* buffer = File_ReadAllBytes(filename, &fileLength);
	if (buffer != NULL) {
		HMMIO hmmio;
		MMRESULT mresult = RIFF_OpenInMemory_A___00488f30((HPSTR)buffer, fileLength, &hmmio, &item->field_11c, &riffTag);
		if (mresult == 0) {
			int result2 = FUN_00489380(&hmmio, &local_28, &riffTag);
			if (result2 == 0) {
				// <https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalalloc>
				HGLOBAL hGlobal = GlobalAlloc(GMEM_FIXED /*0*/, local_28.cksize);
				item->field_118 = hGlobal;
				// *(HGLOBAL *)&pHVar1[0x46].unused = hGlobal;
				if (hGlobal != NULL) {
					uVar4 = FUN_004893c0(hmmio, local_28.cksize, (int)hGlobal, (int)&local_28, (uint*)&local_2c);
					if (uVar4 == 0) {
						*(HMMIO__ *)&pHVar1[0x41].unused = local_2c;
						if (hmmio != NULL) {
							mmioClose(hmmio, 0);
							hmmio = NULL;
						}
						if (FUN_0047b980((int)item) != 0) {
							if (FUN_0047ba50((int)item) != 0) {
								if (item->field_118 != (HGLOBAL)NULL) {
									GlobalFree(item->field_118);
									item->field_118 = NULL;
								}
								free(buffer);
								return true;
							}
						}
					}
				}
			}
		}
	}
	if (item->field_118 != (HGLOBAL)NULL) {
		GlobalFree((HGLOBAL)item->field_118);
		item->field_118 = NULL;
	}
	// if ((HGLOBAL)pHVar1[0x46].unused != (HGLOBAL)NULL) {
	// 	GlobalFree((HGLOBAL)pHVar1[0x46].unused);
	// 	pHVar1[0x46].unused = 0;
	// }
	return false;
}


// 			uVar6 = 0xffffffff;
// 			filename = wavFileBuffer;
// 			do {
// 				pcVar9 = filename;
// 				if (uVar6 == 0) break;
// 				uVar6 -= 1;
// 				pcVar9 = filename + 1;
// 				cVar1 = *filename;
// 				filename = pcVar9;
// 			} while (cVar1 != '\0');
// 			uVar6 = ~uVar6;
// 			uVar7 = uVar6 >> 2;
// 			puVar8 = (undefined4 *)(pcVar9 + -uVar6);
// 			puVar10 = (undefined4 *)(&g_SFXData_TABLE + sfxIndex * 0x134);
// 			while (uVar7 != 0) {
// 				uVar7 -= 1;
// 				*puVar10 = *puVar8;
// 				puVar8 = puVar8 + 1;
// 				puVar10 = puVar10 + 1;
// 			}
// 			uVar6 &= 3;
// 			while (uVar6 != 0) {
// 				uVar6 -= 1;
// 				*(undefined *)puVar10 = *(undefined *)puVar8;
// 				puVar8 = (undefined4 *)((int)puVar8 + 1);
// 				puVar10 = (undefined4 *)((int)puVar10 + 1);
// 			}
// 			// iVar3 = sfxIndex * 0x134;
// 			if (SFX_ValidateNumPound__0047ab10(num_pound) == 0) {
// 				*(int *)(&DAT_005077a8 + sfxIndex * 0x134) = 0;
// 			}
// 			else {
// 				*(int *)(&DAT_005077a8 + sfxIndex * 0x134) = num_pound;
// 			}
// 			// 	*(uint *)(&DAT_005077c8 + iVar3) |= 0x3;
// 			// 	return sfxIndex;
// 			// }
// 			// iVar3 = sfxIndex * 0x134;
// 			*(uint *)(&DAT_005077c8 + sfxIndex * 0x134) |= 0x3;
// 			return sfxIndex;
// 		}
// 	}
// 	return -1;
// }

