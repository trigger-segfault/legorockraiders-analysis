
#pragma region /// TYPES ////////////////////////////////


typedef void (__cdecl *MusicCallbackFuncPtr)(void);

typedef BOOL (__cdecl *GameInitFuncPtr)(void);
typedef BOOL (__cdecl *GameUpdateFuncPtr)(float);
typedef void (__cdecl *GameCleanupFuncPtr)(void);

struct GameFunctions
{
	/*0,4*/ GameInitFuncPtr* init;
	/*4,4*/ GameUpdateFuncPtr* update;
	/*8,4*/ GameCleanupFuncPtr* cleanup;
	/*c*/
};

#pragma endregion

// def uuid(b):
//   from struct import unpack
//   def u4(d,o): return f'{unpack("<I",d[o:o+4])[0]:08x}'
//   def u2(d,o): return f'{unpack("<H",d[o:o+2])[0]:04x}'
//   return f'{{{u4(b,0)}-{u2(b,4)}-{u2(b,6)}-{b[8:10].hex()}-{b[10:16].hex()}}}'

// 9C59509A-39BD-11D1

//                              IID_004a0338                                    XREF[2]:     FUN_004747b0:00474819(*), 
//                                                                                           Main_Direct3DRMCreate:00478513(*
// 81 db 14 6c 33 a7 ce 11 a5

// 81 db 14 6c 33 a7 ce 11 a5 21 00 20 af 0b e5 60

// // <https://github.com/github/VisualStudio/blob/master/tools/Debugging%20Tools%20for%20Windows/winext/manifest/ddraw.h>
// 6C14DB81-A733-11CE-A521-0020AF0BE560
// "{6c14db81-a733-11ce-a521-0020af0be560}"
// // uuid("6C14DB81-A733-11CE-A521-0020AF0BE560")) IDirectDrawSurface     ;


IDirectDraw4 {9c59509a-39bd-11d1-8c4a-00c04fd930c5}

// <LegoRR.exe @004a0328>
static IID UUID__IDirectDraw4 = uuid("9c59509a-39bd-11d1-8c4a-00c04fd930c5");

// <https://github.com/github/VisualStudio/blob/master/tools/Debugging%20Tools%20for%20Windows/winext/manifest/ddraw.h>
// <LegoRR.exe @004a0338>
static IID UUID__IDirectDrawSurface = uuid("6c14db81-a733-11ce-a521-0020af0be560");

// https://github.com/Krakean/lightalloy/blob/master/Source/Common/DirectShow/Direct3DRM.pas
//   "{4516ec83-8f20-11d0-9b6d-0000c0781bc3}"
// IID 4516EC83 8F20 11D0 9B6D 0000C0781BC3
// <LegoRR.exe @004a0bd8>
static IID UUID__IDirect3DRM3 = uuid("4516ec83-8f20-11d0-9b6d-0000c0781bc3");
// <LegoRR.exe @00506914>
static IDirect3DRM3* g_IDirect3DRM3;

// <LegoRR.exe @00545a00>
static int g_MusicTrackIndex;
// <LegoRR.exe @00545a04>
static BOOL g_MusicState;
// <LegoRR.exe @00545a08>
static MusicCallbackFuncPtr* g_MusicCallback;

// <LegoRR.exe @00545a10>
static unsigned int g_MusicUpdateTime;

// <LegoRR.exe @00545a1c>
static MCIERROR g_mciLastError;

// <LegoRR.exe @00577500 -> 005775c8>
static char g_mciErrorText[200];


// <LegoRR.exe @00506800>
static HWND g_hWnd;
// <LegoRR.exe @00506804>
static HINSTANCE g_hInstance;
// <LegoRR.exe @00506808>
static BOOL g_IsFocused;
// <LegoRR.exe @0050680c>
static BOOL g_IsClosing;
// <LegoRR.exe @00506810>
static const char* g_WindowClassName;
// <LegoRR.exe @00506814 -> 00506914>
static char g_ExeName[256];
// <LegoRR.exe @00506924>
static unsigned int g_RESOLUTION_width;
// <LegoRR.exe @00506928>
static unsigned int g_RESOLUTION_height;
// <LegoRR.exe @0050692c>
static GameFunctions g_GameFunctions;
// <LegoRR.exe @00506938>
static BOOL g_GameFunctions_ISINIT;
// <LegoRR.exe @0050693c>
static float g_FPSLOCK_VSYNC;

// <LegoRR.exe @0076bcbc>
static BOOL g_ScreenIsFullScreen;

// <LegoRR.exe @0053499c>
static void* g_AVIFileData; //???





// LegoRR.exe RESOURCES:
//
// Icon:
//  1 : 2057 (main 32x32 icon)
// Icon Group:
//  113 : 2057 (main icon group consisting of the only icon, 1 : 2057)
//
// Dialog:
//  101 : 1033 (mode selection dialog)
//
// 101 DIALOG 0, 0, 242, 166
// STYLE DS_SETFONT | DS_MODALFRAME | WS_POPUP | WS_CAPTION | WS_SYSMENU
// CAPTION "Mode Selection"
// LANGUAGE LANG_ENGLISH, SUBLANG_ENGLISH_US
// FONT 8, "MS Sans Serif"
// {
//    CONTROL "OK", 1, BUTTON, BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 65, 145, 50, 14 
//    CONTROL "Cancel", 2, BUTTON, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 125, 145, 50, 14 
//    CONTROL "", 1000, LISTBOX, LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP, 5, 15, 230, 30 
//    CONTROL "", 1002, LISTBOX, LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP, 5, 60, 230, 35 
//    CONTROL "", 1003, LISTBOX, LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP, 100, 100, 135, 40 
//    CONTROL "Device", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 5, 50, 230, 8 
//    CONTROL "Driver", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 5, 5, 230, 8 
//    CONTROL "Screen Modes", 1006, STATIC, SS_RIGHT | WS_CHILD | WS_VISIBLE | WS_GROUP, 5, 100, 89, 8 
//    CONTROL "Full Screen", 1004, BUTTON, BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, 5, 115, 51, 10 
//    CONTROL "Window", 1005, BUTTON, BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE, 5, 125, 42, 10 
// }

enum LegoRRResources {
	LEGORR_MAIN_ICON            = 1,
	LEGORR_MODESELECTION_DIALOG = 101,
	LEGORR_MAIN_ICONGROUP       = 113,

	CLGEN_MAIN_ICON             = 1,
	CLGEN_SELECTOR_DIALOG       = 101,
	CLGEN_MAIN_ICONGROUP        = 103,
};
enum LegoRRDialogControls {
	LEGORR_ID_OK_BUTTON              = 1,
	LEGORR_ID_CANCEL_BUTTON          = 2,
	LEGORR_ID_DRIVER_LISTBOX         = 1000,
	LEGORR_ID_DEVICE_LISTBOX         = 1002,
	LEGORR_ID_SCREENMODES_LISTBOX    = 1003,
	LEGORR_ID_FULLSCREEN_RADIOBUTTON = 1004,
	LEGORR_ID_WINDOW_RADIOBUTTON     = 1005,
	LEGORR_ID_SCREENMODES_LABEL      = 1006,
	LEGORR_ID_DEVICE_LABEL           = -1,
	LEGORR_ID_DRIVER_LABEL           = -1,

	CLGEN_ID_OK_BUTTON           = 1,
	CLGEN_ID_CANCEL_BUTTON       = 2,
	CLGEN_ID_SELECT_DROPDOWNLIST = 1001,
	CLGEN_ID_SELECT_LABEL        = 1006,
};


// #define RSRC__MAIN_ICON 1
// #define RSRC__MAIN_ICONGROUP 113
// #define RSRC__MODESELECTION_DIALOG 101

// #define RSRC__ID_OK_BUTTON 1
// #define RSRC__ID_CANCEL_BUTTON 2
// #define RSRC__ID_DRIVER_LISTBOX 1000
// #define RSRC__ID_DEVICE_LISTBOX 1002
// #define RSRC__ID_SCREENMODES_LISTBOX 1003
// #define RSRC__ID_DEVICE_LABEL -1
// #define RSRC__ID_DRIVER_LABEL -1
// #define RSRC__ID_SCREENMODES_LABEL 1006
// #define RSRC__ID_FULLSCREEN_RADIOBUTTON 1004
// #define RSRC__ID_WINDOW_RADIOBUTTON 1005

// <LegoRR.exe @00569058>
static BOOL g_FullScreenMode;

// <LegoRR.exe @005774f4>
static BOOL g_IsFullScreen;



struct LegoScreenMode
{
	/*000,4*/ int screenWidth;
	/*004,4*/ int screenHeight;
	/*008,4*/ int bitDepth;

	/*110*/
};


// <LegoRR.exe @00569060>
static LegoScreenMode DAT_00569060[0 /*?*/]; // till DAT_00569170 ???

// <LegoRR.exe @005764e0>
static unsigned int g_ScreenModes_COUNT;

// <LegoRR.exe @0055bbd4>
static undefined0x110 DAT_0055bbd4[0 /*?*/];


struct _STARTUPINFOA {
		/*00,4*/ DWORD cb;
		/*04,4*/ LPSTR lpReserved;
		/*08,4*/ LPSTR lpDesktop;
		/*0c,4*/ LPSTR lpTitle;
		/*10,4*/ DWORD dwX;
		/*14,4*/ DWORD dwY;
		/*18,4*/ DWORD dwXSize;
		/*1c,4*/ DWORD dwYSize;
		/*20,4*/ DWORD dwXCountChars;
		/*24,4*/ DWORD dwYCountChars;
		/*28,4*/ DWORD dwFillAttribute;
		/*2c,4*/ DWORD dwFlags;
		/*30,4*/ WORD wShowWindow;
		/*32,4*/ WORD cbReserved2;
		/*34,4*/ LPBYTE lpReserved2;
		/*38,4*/ HANDLE hStdInput;
		/*3c,4*/ HANDLE hStdOutput;
		/*40,4*/ HANDLE hStdError;
	/*44*/
};

// <https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getversion>
	// 	DWORD dwVersion = 0; 
	// 	DWORD dwMajorVersion = 0;
	// 	DWORD dwMinorVersion = 0; 
	// 	DWORD dwBuild = 0;

	// 	dwVersion = GetVersion();
 
	// 	// Get the Windows version.

	// 	dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	// 	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	
	// 	if (dwVersion < 0x80000000)              
	// 			dwBuild = (DWORD)(HIWORD(dwVersion));

	// DVar2 = GetVersion();
	// _DAT_0054a0e8 = DVar2 >> 8 & 0xff; // dwMinorVersion
	// _DAT_0054a0e4 = DVar2 & 0xff; // dwMajorVersion
	// _DAT_0054a0e0 = _DAT_0054a0e4 * 0x100 + _DAT_0054a0e8;
	// _DAT_0054a0dc = DVar2 >> 0x10;

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// <LegoRR.exe @0048f2c0>
void entry(void)
{
	byte bVar1;
	DWORD DVar2;
	int iVar3;
	uint nShowCmd;
	HMODULE hInstance;
	byte *pbVar4;
	undefined4 *in_FS_OFFSET;
	HINSTANCE hPrevInstance;
	byte *local_68;
	STARTUPINFOA local_60;
	undefined4 local_14;
	undefined *puStack16;
	undefined *puStack12;
	undefined4 local_8;
	
	local_8 = 0xffffffff;
	puStack12 = &DAT_0049fb20;
	puStack16 = &LAB_00496a98;
	local_14 = *in_FS_OFFSET;
	*in_FS_OFFSET = &local_14;
	DVar2 = GetVersion();
	_DAT_0054a0e8 = DVar2 >> 8 & 0xff;
	_DAT_0054a0e4 = DVar2 & 0xff;
	_DAT_0054a0e0 = _DAT_0054a0e4 * 0x100 + _DAT_0054a0e8;
	_DAT_0054a0dc = DVar2 >> 0x10;
	iVar3 = FUN_00491820();
	if (iVar3 == 0) {
		__amsg_exit(0x1c);
	}
	local_8 = 0;
	FUN_00496890();
	FUN_00496880();
	msvc::g_GetCommandLineA = GetCommandLineA();
	DAT_0054a11c = FUN_00496450();
	if ((DAT_0054a11c == (undefined4 *)0x0) || (msvc::g_GetCommandLineA == (char *)0x0)) {
		msvc::exit(-1);
	}
	FUN_004961a0();
	FUN_004960b0();
	FUN_0048e740();
	local_68 = (byte *)msvc::g_GetCommandLineA;
	if (*msvc::g_GetCommandLineA == '\"') {
		while( true ) {
			pbVar4 = local_68;
			local_68 = pbVar4 + 1;
			bVar1 = *local_68;
			if ((bVar1 == 0x22) || (bVar1 == 0)) break;
			iVar3 = FUN_00496050((uint)bVar1);
			if (iVar3 != 0) {
				local_68 = pbVar4 + 2;
			}
		}
		if (*local_68 == 0x22) {
			local_68 = pbVar4 + 2;
		}
	}
	else {
		for (; 0x20 < *local_68; local_68 = local_68 + 1) {
		}
	}
	for (; (*local_68 != 0 && (*local_68 < 0x21)); local_68 = local_68 + 1) {
	}
	local_60.dwFlags = 0;
	GetStartupInfoA((LPSTARTUPINFOA)&local_60);
	if ((local_60.dwFlags & 1) == 0) {
		nShowCmd = 10;
	}
	else {
		nShowCmd = local_60._48_4_ & 0xffff;
	}
	hPrevInstance = (HINSTANCE)0x0;
	hInstance = GetModuleHandleA((LPCSTR)0x0);
	iVar3 = lego::WinEntry((HINSTANCE)hInstance,hPrevInstance,(LPSTR)local_68,nShowCmd);
	msvc::exit(iVar3);
	*in_FS_OFFSET = local_14;
	return;
}




// <LegoRR.exe @00496450>
LPSTR msvc::GetEnvironmentStringsA(void)
{
	char cVar1;
	WCHAR WVar2;
	WCHAR *pWVar3;
	int iVar5;
	uint uVar6;
	undefined4 *puVar7;
	uint uVar8;
	undefined4 *puVar9;
	LPWCH lpWideCharStr;
	undefined4 *puVar10;
	undefined4 *puVar11;
	WCHAR *pWVar4;
	
	lpWideCharStr = (LPWCH)0x0;
	puVar9 = (undefined4 *)0x0;
	if (DAT_0054a2b0 == 0) {
		lpWideCharStr = GetEnvironmentStringsW();
		if (lpWideCharStr == (LPWCH)0x0) {
			puVar9 = (undefined4 *)GetEnvironmentStrings();
			if (puVar9 == (undefined4 *)0x0) {
				return (LPSTR)(undefined4 *)0x0;
			}
			DAT_0054a2b0 = 2;
		}
		else {
			DAT_0054a2b0 = 1;
		}
	}
	if (DAT_0054a2b0 == 1) {
		if ((lpWideCharStr != (LPWCH)0x0) ||
			 (lpWideCharStr = GetEnvironmentStringsW(), lpWideCharStr != (LPWCH)0x0)) {
			WVar2 = *lpWideCharStr;
			pWVar3 = lpWideCharStr;
			while (WVar2 != L'\0') {
				do {
					pWVar4 = pWVar3;
					pWVar3 = pWVar4 + 1;
				} while (*pWVar3 != L'\0');
				pWVar3 = pWVar4 + 2;
				WVar2 = *pWVar3;
			}
			iVar5 = ((int)((int)pWVar3 - (int)lpWideCharStr) >> 1) + 1;
			uVar6 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
			if ((uVar6 != 0) && (puVar9 = (undefined4 *)msvc::malloc(uVar6), puVar9 != (undefined4 *)0x0))
			{
				iVar5 = WideCharToMultiByte(0,0,lpWideCharStr,iVar5,(LPSTR)puVar9,uVar6,(LPCSTR)0x0,
																		(LPBOOL)0x0);
				if (iVar5 == 0) {
					msvc::free(puVar9);
					puVar9 = (undefined4 *)0x0;
				}
				FreeEnvironmentStringsW(lpWideCharStr);
				return (LPSTR)puVar9;
			}
			FreeEnvironmentStringsW(lpWideCharStr);
			return (LPSTR)(undefined4 *)0x0;
		}
	}
	else {
		if ((DAT_0054a2b0 == 2) &&
			 ((puVar9 != (undefined4 *)0x0 ||
				(puVar9 = (undefined4 *)GetEnvironmentStrings(), puVar9 != (undefined4 *)0x0)))) {
			cVar1 = *(char *)puVar9;
			puVar7 = puVar9;
			while (cVar1 != '\0') {
				do {
					puVar10 = puVar7;
					puVar7 = (undefined4 *)((int)puVar10 + 1);
				} while (*(char *)((int)puVar10 + 1) != '\0');
				puVar7 = (undefined4 *)((int)puVar10 + 2);
				cVar1 = *(char *)((int)puVar10 + 2);
			}
			uVar6 = (int)puVar7 + (1 - (int)puVar9);
			puVar7 = (undefined4 *)msvc::malloc(uVar6);
			if (puVar7 != (undefined4 *)0x0) {
				puVar10 = puVar9;
				puVar11 = puVar7;
				for (uVar8 = uVar6 >> 2; uVar8 != 0; uVar8 -= 1) {
					*puVar11 = *puVar10;
					puVar10 = puVar10 + 1;
					puVar11 = puVar11 + 1;
				}
				for (uVar6 &= 3; uVar6 != 0; uVar6 -= 1) {
					*(undefined *)puVar11 = *(undefined *)puVar10;
					puVar10 = (undefined4 *)((int)puVar10 + 1);
					puVar11 = (undefined4 *)((int)puVar11 + 1);
				}
				FreeEnvironmentStringsA((LPCH)puVar9);
				return (LPSTR)puVar7;
			}
			FreeEnvironmentStringsA((LPCH)puVar9);
			return (LPSTR)(undefined4 *)0x0;
		}
	}
	return (LPSTR)(undefined4 *)0x0;
}

// <LegoRR.exe @0048dd10>
char* __cdecl strstr(char* str, const char* strSearch)
{
	char *pcVar1;
	char *pcVar2;
	char charSearch; //cVar3;
	uint uVar4;
	char cVar5;
	uint uVar6;
	char *pcVar7;
	uint uVar8;
	uint *puVar9;
	char *pcVar10;
	
	char charSearch = *strSearch;
	if (*strSearch == '\0') {
		return str;
		// return (char *)(uint *)str;
	}
	if (strSearch[1] == '\0') {
		uVar4 = (uint)str & 3;
		while (uVar4 != 0) {
			if (*str == charSearch) {
				return (char *)(uint *)str;
			}
			if (*str == '\0') {
				return (char *)(uint *)0x0;
			}
			uVar4 = (uint)(uint *)((int)str + 1) & 3;
			str = (char *)(uint *)((int)str + 1);
		}
		while( true ) {
			while( true ) {
				uVar4 = *(uint *)str;
				uVar8 = uVar4 ^ CONCAT22(CONCAT11(charSearch,charSearch),CONCAT11(charSearch,charSearch));
				uVar6 = uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff;
				puVar9 = (uint *)((int)str + 4);
				if (((uVar8 ^ 0xffffffff ^ uVar8 + 0x7efefeff) & 0x81010100) != 0) break;
				str = (char *)puVar9;
				if ((uVar6 & 0x81010100) != 0) {
					if ((uVar6 & 0x1010100) != 0) {
						return (char *)(uint *)0x0;
					}
					if ((uVar4 + 0x7efefeff & 0x80000000) == 0) {
						return (char *)(uint *)0x0;
					}
				}
			}
			uVar4 = *(uint *)str;
			if ((char)uVar4 == charSearch) {
				return (char *)(uint *)str;
			}
			if ((char)uVar4 == '\0') {
				return (char *)(uint *)0x0;
			}
			cVar5 = (char)(uVar4 >> 8);
			if (cVar5 == charSearch) {
				return (char *)(uint *)((int)str + 1);
			}
			if (cVar5 == '\0') break;
			cVar5 = (char)(uVar4 >> 0x10);
			if (cVar5 == charSearch) {
				return (char *)(uint *)((int)str + 2);
			}
			if (cVar5 == '\0') {
				return (char *)(uint *)0x0;
			}
			cVar5 = (char)(uVar4 >> 0x18);
			if (cVar5 == charSearch) {
				return (char *)(uint *)((int)str + 3);
			}
			str = (char *)puVar9;
			if (cVar5 == '\0') {
				return (char *)(uint *)0x0;
			}
		}
		return (char *)(uint *)0x0;
	}
	do {
		cVar5 = *str;
		do {
			while (str = str + 1, cVar5 != charSearch) {
				if (cVar5 == '\0') {
					return (char *)(uint *)0x0;
				}
				cVar5 = *str;
			}
			cVar5 = *str;
			pcVar10 = str + 1;
			pcVar7 = strSearch;
		} while (cVar5 != strSearch[1]);
		do {
			if (pcVar7[2] == '\0') {
		LAB_0048dd83:
				return (char *)(uint *)(str + -1);
			}
			if (*pcVar10 != pcVar7[2]) break;
			pcVar1 = pcVar7 + 3;
			if (*pcVar1 == '\0') {
				//goto LAB_0048dd83;
				return (char *)(uint *)(str + -1);
			}
			pcVar2 = pcVar10 + 1;
			pcVar7 = pcVar7 + 2;
			pcVar10 = pcVar10 + 2;
		} while (*pcVar1 == *pcVar2);
	} while( true );
}

// <LegoRR.exe @0049df90>
char* __cdecl msvc::_strupr(char* str);



// char* __cdecl FUN_0048b5f0(char* param_1, char* param_2)
// <LegoRR.exe @0048b5f0>
const char* __cdecl Reg_SplitRootKey(const char* fullKey, char* out_rootKey)
{
	*out_rootKey = '\0';
	// find first separator
	while (*fullKey != '\0' && *fullKey != '\\') {
		*out_rootKey++ = *fullKey++;
	}

	if (*fullKey == '\\')
		fullKey++; // skip separator
	*out_rootKey = '\0';

	return fullKey; // return key path after base key
}

// "SOFTWARE\\LEGO Media\\Games\\Rock Raiders","StandardParameters", 0x400
// "SOFTWARE\\LEGO Media\\Games\\Rock Raiders","NoHALMessage", 0x400

// Path_InitDataDir(globals::g_ExeName, insistOnCD, "SOFTWARE\\LEGO Media\\Games\\Rock Raiders");
// regKey,"CDMissing", 0x400);
// regKey,"SetupError", 0x400);
// regKey,"DataMissing", 0x400);

// <https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeya>
// <https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexa>



// - mode must be 0 or 1... but otherwise, both values do the same thing
// <LegoRR.exe @0048b650>
BOOL __cdecl Reg_QueryString(HKEY hKey, const char* subKey, const char* valueName, unsigned int valueType, char* out_buffer, unsigned int bufferSize)
{
	char rootSubKey[100];
	const char* splitSubKey = Reg_SplitRootKey(subKey, rootSubKey);
	if (*rootSubKey != '\0') {
		// rootSubKey isn't empty, we have more keys to recurse through
		HKEY hSubKey;
		RegCreateKeyA(hKey, rootSubKey, &hSubKey);
		if (hSubKey == NULL)
			return false /*0*/;

		// recursively open subkeys to get to where we need
		BOOL recurseResult = Reg_QueryString(hSubKey, splitSubKey, valueName, valueType, out_buffer, bufferSize);
		RegCloseKey(hSubKey);
		return recurseResult;
	}
	DWORD outValueType = 0;
	if (valueType == REG_SZ /*1*/) {
		LSTATUS result = RegQueryValueExA(hKey, valueName, NULL, &outValueType, out_buffer, &bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	}
	else if (valueType == REG_NONE /*0*/) {
		LSTATUS result = RegQueryValueExA(hKey, valueName, NULL, &outValueType, out_buffer, &bufferSize);
		return (result == ERROR_SUCCESS /*0*/);
	}
	return false /*0*/;
	// if (valueType != REG_NONE /*0*/) {
	// 	if (valueType != REG_SZ /*1*/)
	// 		return false /*0*/;

	// }
}

// <LegoRR.exe @0048b620>
BOOL __cdecl Reg_QueryString_LocalMachine(const char *subKey, const char* valueName, unsigned int valueType, char* out_buffer, unsigned int bufferSize)
{
	return Reg_QueryString((HKEY)HKEY_LOCAL_MACHINE /*0x80000002*/, subKey, valueName, mode, out_buffer, bufferSize);
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassa>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa>
// <https://docs.microsoft.com/en-us/windows/win32/winmsg/window-class-styles>
// <https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles>
// <https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles>


// <LegoRR.exe @004786b0>
BOOL __cdecl Win_CreateMainWindow(HINSTANCE hInstance)
{
	WNDCLASSA wndClass;
	wndClass.style = CS_DBLCLKS /*0x8*/;
	wndClass.lpfnWndProc = Wnd_WndProc_Main__00478b40;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = NULL;
	wndClass.hCursor = NULL;
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = g_WindowClassName;

	ATOM atomResult = RegisterClassA(&wndClass);
	if (atomResult == 0) {
		MessageBoxA(NULL, "Unable to register window class", "Fatal Error", 0);
		return false /*0*/;
	}
	g_hWnd = CreateWindowExA(WS_EX_APPWINDOW /*0x40000*/, g_WindowClassName, ""/*EMPTYSTR*/, WS_POPUP | WS_SYSMENU /*0x80000000 | 0x80000*/, 0, 0, 100, 100, NULL, NULL, hInstance, NULL);
	if (g_hWnd == NULL) {
		MessageBoxA(NULL, "Unable to Create Main Window", "Fatal Error", 0);
		return false /*0*/;
	}
	SetFocus(g_hWnd);
	return true /*1*/;
}

// <LegoRR.exe @004781f0>
void __cdecl FUN_004781f0(int param_1)
{
	Win_HandleMessageQueue();
	FUN_0047f1b0();
	Input_UpdateMousePosition();
	FUN_00478260();
	FUN_0047cb90();
	if (param_1 != 0) {
		FUN_0047d0e0(0, 0);
	}
	g_CMDLINE_FLAGS &= ~0x1 /*0xfffffffe*/;
}

// <LegoRR.exe @0047c770>
unsigned int __cdecl FUN_0047c770(unsigned int param_1, undefined4 param_2, undefined4 param_3, undefined4* param_4)
{
	int iVar1;
	int* unaff_ESI;
	unsigned int uVar2;
	undefined4 unaff_retaddr;
	code*** pppcVar3;
	int* piVar4;
	code** local_4;

	uVar2 = 0;
	DAT_0076bcb8 = 0;
	if (param_1 != 0 && ((*(unsigned int *)(param_1 + 0x110) & 1) != 0)) {
		iVar1 = DirectDrawCreate(~-(unsigned int)((*(unsigned int *)(param_1 + 0x110) & 0x10) != 0) & param_1, &local_4, 0);
		if (iVar1 == 0) {
			piVar4 = (int *)&DAT_004a0328;
			iVar1 = (**(code **)*local_4)(local_4,&DAT_004a0328,&param_1);
			if (iVar1 == 0) {
				pppcVar3 = &local_4;
				DAT_0076bcac = unaff_retaddr;
				(**(code **)(*unaff_ESI + 0x20))(param_1, 0,0, param_3, FUN_0047c810);
				(*(*pppcVar3)[2])(pppcVar3);
			}
			uVar2 = (unsigned int)(iVar1 == 0);
			(**(code **)(*piVar4 + 8))(piVar4);
		}
	}
	*param_4 = DAT_0076bcb8;
	return uVar2;
}

// <LegoRR.exe @00478240>
int __cdecl Win_GetDeviceBitsPerPixel(void)
{
	HDC hdc = GetDC(g_hWnd);
	return GetDeviceCaps(hdc, BITSPIXEL /*0xc*/);
}

// registers a screen mode option
// <LegoRR.exe @0049db30>
void __cdecl Win_RegisterScreenMode(int screenWidth, int screenHeight, int bitDepth)

{
  (&DAT_00569060)[g_ScreenModes_COUNT * 0x44] = screenWidth;
  (&DAT_00569064)[g_ScreenModes_COUNT * 0x44] = screenHeight;
  (&DAT_00569068)[g_ScreenModes_COUNT * 0x44] = bitDepth;
  g_ScreenModes_COUNT++;
  return;
}

  Win_RegisterScreenMode(640, 480, 16);
  if (param_2 != 0) {
    Win_RegisterScreenMode(800, 600, 16);
    Win_RegisterScreenMode(1024, 768, 16);
  }

// <LegoRR.exe @0049db90>
undefined4 __cdecl FUN_0049db90(int param_1)
{
	int *piVar1;
	uint uVar2;

	if (g_ScreenModes_COUNT == 0) {
		return false /*0*/;
	}
	uVar2 = 0;
	if (g_ScreenModes_COUNT != 0) {
		piVar1 = &DAT_00569064;
		do {
			if (((piVar1[-1] == 0) || (piVar1[-1] == *(int *)(&DAT_0055bbcc + param_1 * 0x110))) &&
			((*piVar1 == 0 || (*piVar1 == *(int *)(&DAT_0055bbd0 + param_1 * 0x110))))) {
				if (piVar1[1] == 0) {
					return true /*1*/;
				}
				if (piVar1[1] == *(int *)(&DAT_0055bbd4 + param_1 * 0x110)) {
					return true /*1*/;
				}
			}
			uVar2++;
			piVar1 = piVar1 + 0x44;
		} while (uVar2 < g_ScreenModes_COUNT);
	}
	return false /*0*/;
}

// <https://docs.microsoft.com/en-us/windows/win32/controls/button-styles>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enddialog>

// WM_SETTEXT      (0x000c): <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-settext>
// BM_SETCHECK     (0x00f1): <https://docs.microsoft.com/en-us/windows/win32/controls/bm-setcheck>
// WM_INITDIALOG   (0x0110): <https://docs.microsoft.com/en-us/windows/win32/dlgbox/wm-initdialog>
// WM_COMMAND      (0x0111): <https://docs.microsoft.com/en-us/windows/win32/menurc/wm-command>
// LB_ADDSTRING    (0x0180): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-addstring>
// LB_DELETESTRING (0x0182): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-deletestring>
// LB_SETCURSEL    (0x0186): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-setcursel>
// LB_GETCURSEL    (0x0188): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-getcursel>
// LB_GETTEXT      (0x0189): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-gettext>
// 
// <LegoRR.exe @0049d5b0>
BOOL Win_ModeSelectionDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// short sVar1;
	// HWND pHVar2;
	// LRESULT LVar3;
	// WPARAM wParam;
	//   short sVar4;
	// unsigned int uVar5;
	// undefined* lParam;
	// int iVar6;
	// RECT dlgRect;
	// RECT desktopRect;
	char screenModeText[0x400];

	if (message == WM_INITDIALOG /*0x110*/) {
		RECT dlgRect;
		RECT desktopRect;
		HWND hDesktopWnd = GetDesktopWindow();
		GetWindowRect(hDesktopWnd, &desktopRect);
		GetWindowRect(hDlg, &dlgRect);
		MoveWindow(hDlg, desktopRect.right  / 2 - (dlgRect.right - dlgRect.left) / 2,
						 desktopRect.bottom / 2 - (dlgRect.bottom - dlgRect.top) / 2,
						 dlgRect.right - dlgRect.left,
						 dlgRect.bottom - dlgRect.top,
						 1);
		int idRadioButton;
		if (g_FullScreenMode == false /*0*/) {
			idRadioButton = LEGORR_ID_WINDOW_RADIOBUTTON /*1005*/;
		}
		else {
			idRadioButton = LEGORR_ID_FULLSCREEN_RADIOBUTTON /*1004*/;
		}
		HWND hCtrlRadioButton = GetDlgItem(hDlg, idRadioButton);
		SendMessageA(hCtrlRadioButton, BM_SETCHECK /*0xf1*/, BST_CHECKED /*1*/, 0);
		HWND hCtrlDriverListbox = hCtrlDriverListbox = GetDlgItem(hDlg, LEGORR_ID_DRIVER_LISTBOX /*1000*/);
		unsigned int uVar5 = 0;
		if (DAT_005590a0 != 0) {
			char* text = &DAT_005590bc;
			do {
				SendMessageA(hCtrlDriverListbox, LB_ADDSTRING /*0x180*/, 0, (LPARAM)text);
				uVar5++;
				text += 0x114;
			} while (uVar5 < DAT_005590a0);
		}
		SendMessageA(hCtrlDriverListbox, LB_SETCURSEL /*0x186*/, 0, 0);
		SetFocus(hCtrlDriverListbox);
		FUN_0049dc90(hDlg);
		FUN_0049da40(hDlg);
		FUN_0049d8f0(hDlg);
		return false /*0*/;
	}

	else if (message == WM_COMMAND /*0x111*/) {
		short msgSource = (short)((wParam >> 16) & 0xffff);
		//   short sVar4 = (short)wParam;
		short idCaller = (short)(wParam & 0xffff);
		if (msgSource == 1 /*message from Accelerator*/) {
			if (idCaller == LEGORR_ID_DEVICE_LISTBOX /*1002*/) {
				int selection = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				DAT_00569050 = &DAT_0055a63c + selIndex * 0x114;
				return true /*1*/;
			}
			else if (idCaller == LEGORR_ID_SCREENMODES_LISTBOX /*1003*/) {
				int selection = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				SendMessageA((HWND)lParam, LB_GETTEXT /*0x189*/, selection, (LPARAM)screenModeText);

				// probably get index of screen mode struct, by name
				unsigned int outIndex;
				int iVar6 = FUN_0049dc10(screenModeText, &outIndex);
				if (iVar6 != 0) {
					DAT_00569054 = &DAT_0055bbcc + outIndex * 0x110;
					return true /*1*/;
				}
			}
			else if (idCaller == LEGORR_ID_DRIVER_LISTBOX /*1000*/) {
				int selection = (int)SendMessageA((HWND)lParam, LB_GETCURSEL /*0x188*/, 0, 0);
				DAT_0056904c = &DAT_005590ac + selection * 0x114;
				FUN_0049dc90(hDlg);
				FUN_0049d8f0(hDlg);
				FUN_0049da40(hDlg);
			}
		}
		else if (msgSource == 0 /*message from Menu*/) {
			// handle screen mode changed
			if (idCaller == LEGORR_ID_WINDOW_RADIOBUTTON /*1005*/) {
				FUN_0049d8a0(hDlg, false /*0*/);
			}
			else if (idCaller == LEGORR_ID_FULLSCREEN_RADIOBUTTON /*1004*/) {
				FUN_0049d8a0(hDlg, true /*1*/);
			}
			// handle exit
			else if (idCaller == LEGORR_ID_OK_BUTTON /*IDOK 1*/ || idCaller == LEGORR_ID_CANCEL_BUTTON /*IDCANCEL 2*/) {
				EndDialog(hDlg, wParam);
			}
		}
		return true /*1*/;
	}

	return false /*0*/;
}


// <LegoRR.exe @0049d2f0>
BOOL __cdecl FUN_0049d2f0(BOOL showDialog, BOOL isDebug, BOOL isBest, BOOL isWindow, const char* errorMessage)
{
	bool bVar1;
	uint uVar2;
	int iVar3;
	uint *puVar4;
	BOOL BVar5;
	int iVar6;
	undefined *puVar7;
	//   INT_PTR local_4;

	//   local_4 = 1;
	int idResult = IDOK /*1*/;

	DAT_0056904c = (undefined *)NULL;
	DAT_00569050 = (undefined *)NULL;
	DAT_00569054 = (int *)NULL;
	DAT_0056905c = 1;
	g_FullScreenMode = 1;
	g_ScreenModes_COUNT = 0;
	Win_RegisterScreenMode(640, 480, 16);
	if (isDebug != 0) {
		Win_RegisterScreenMode(800, 600, 16);
		Win_RegisterScreenMode(1024, 768, 16);
	}

	FUN_0047c480(&DAT_005590ac, &DAT_005590a0);
	if (DAT_005590a0 != 0) {
		DAT_0056904c = &DAT_005590ac;
		if (isBest == 0) {
			if (showModeSelection != 0) {
				idResult = (int)DialogBoxParamA(g_hInstance, (LPCSTR)(LEGORR_MODESELECTION_DIALOG /*101*/), g_hWnd, Win_ModeSelectionDialogProc, 0);
			}
		}
		else {
			bVar1 = false;
			iVar6 = DAT_005590a0 - 1;
			idResult = IDOK /*1*/;
			g_FullScreenMode = (isWindow == 0);
			if (iVar6 >= 0) {
				puVar7 = &DAT_005590ac + iVar6 * 0x114;
LAB_0049d3d2:
				uVar2 = FUN_0047c5a0(puVar7, &DAT_0055a63c, &DAT_005590a4);
				if (uVar2 == 0) {
					MessageBoxA(NULL, "Please install DirectX version 6 or later", "Error", 0);
					return false /*0*/;
				}
				FUN_0047c770((uint)puVar7, g_FullScreenMode, &DAT_0055bbcc, &DAT_005590a8);
				uVar2 = 0;
				if (DAT_005590a8 != 0) {
					do {
						iVar3 = FUN_0049db90(uVar2);
						if (iVar3 != 0) {
							iVar3 = DAT_005590a4 - 1;
							if (iVar3 >= 0) {
								puVar4 = &DAT_0055a74c + iVar3 * 0x45 /*0x114*/;
								goto LAB_0049d447;
							}
							break;
						}
						uVar2++;
					} while (uVar2 < DAT_005590a8);
				}
				goto LAB_0049d48f;
			}
LAB_0049d4a8:
			if (!bVar1) {
				MessageBoxA(NULL, errorMessage, "Error", 0);
				return false /*0*/;
			}
		}
		if (idResult == IDOK /*1*/) {
			if (g_FullScreenMode != 0) {
				return Main_DirectDrawCreate(1, (unsigned int)DAT_0056904c, DAT_00569050, DAT_00569054, 0, 0, 320, 200);
			}
			if (DAT_00569054 == (int *)NULL) {
				return Main_DirectDrawCreate(0, 0, DAT_00569050, (int *)NULL, 0x28, 0x28, 640, 480);
			}
			return Main_DirectDrawCreate(0, 0, DAT_00569050, (int *)NULL, 100, 100, DAT_00569054[0], DAT_00569054[1]);
		}
	}
	return false /*0*/;

	while( true ) {
		iVar3--;
		puVar4 -= 0x45 /*0x114*/;
		if (iVar3 < 0) break;
LAB_0049d447:
		if ((*puVar4 & 0x2000) != 0) {
			DAT_00569054 = (int *)(&DAT_0055bbcc + uVar2 * 0x110);
			bVar1 = true;
			DAT_00569050 = &DAT_0055a63c + iVar3 * 0x114;
			DAT_0056904c = puVar7;
			break;
		}
	}
LAB_0049d48f:
	if (bVar1) goto LAB_0049d4a8;
	iVar6--;
	puVar7 -= 0x114;
	if (iVar6 < 0) goto LAB_0049d4a8;
	goto LAB_0049d3d2;
}


// LB_ADDSTRING    (0x0180): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-addstring>
// LB_DELETESTRING (0x0182): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-deletestring>
// LB_SETCURSEL    (0x0186): <https://docs.microsoft.com/en-us/windows/win32/controls/lb-setcursel>
// 
// <LegoRR.exe @0049d8f0>
void __cdecl FUN_0049d8f0(HWND hParentWnd)
{
	// bool bVar1;
	// HWND hDlgScreenModes;
	// int iVar2;
	// HWND hDlgOKButton;
	// undefined4 uVar3;
	// undefined *puVar4;
	// BOOL bEnable;
	// unsigned int local_104;
	char unsupportedMessage[256];

	bool bVar1 = true;
	HWND hDlgScreenModes = GetDlgItem(hParentWnd, LEGORR_ID_SCREENMODES_LISTBOX /*1003*/);

	// remove all items from the list box
	int iVar2;
	do {
		iVar2 = SendMessageA(hDlgScreenModes, LB_DELETESTRING /*0x182*/, 0, 0);
	} while (iVar2 != -1);

	// int iVar2 = SendMessageA(hDlgScreenModes, LB_DELETESTRING /*0x182*/, 0, 0);
	// while (iVar2 != -1) {
	// 	iVar2 = SendMessageA(hDlgScreenModes, LB_DELETESTRING /*0x182*/, 0, 0);
	// }

	FUN_0047c770(DAT_0056904c, g_FullScreenMode, &DAT_0055bbcc, &DAT_005590a8);
	unsigned int local_104 = 0;
	if (DAT_005590a8 != 0) {
		undefined* puVar4 = &DAT_0055bbcc;
		do {
			iVar2 = FUN_0049db90(local_104);
			if (iVar2 != 0 && (SendMessageA(hDlgScreenModes, LB_ADDSTRING /*0x180*/, 0, (LPARAM)(puVar4 + 0xc)), bVar1)) {
				bVar1 = false;
				DAT_00569054 = puVar4;
			}
			local_104++;
			puVar4 += 0x110;
		} while (local_104 < DAT_005590a8);
	}

	BOOL bEnable;
	HWND hDlgOKButton = GetDlgItem(hParentWnd, LEGORR_ID_OK_BUTTON /*1*/);
	if (bVar1) {
		if (g_FullScreenMode == false /*0*/) {
			int bitMode = Win_GetDeviceBitsPerPixel();
			sprintf(unsupportedMessage, "No supported %i bit modes found", bitMode);
		}
		else {
			sprintf(unsupportedMessage, "No supported screen modes found");
		}
		SendMessageA(hDlgScreenModes, LB_ADDSTRING /*0x180*/, 0, (LPARAM)unsupportedMessage);
		bEnable = false /*0*/;
	}
	else {
		bEnable = true /*1*/;
	}
	EnableWindow(hDlgOKButton, bEnable);
	SendMessageA(hDlgScreenModes, LB_SETCURSEL /*0x186*/, 0, 0); // select first item (WPARAM)
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdlgitem>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessagea>
//
// WM_SETTEXT (0x000c): <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-settext>
// 
// <LegoRR.exe @0049d8a0>
void __cdecl FUN_0049d8a0(HWND hParentWnd, BOOL screenMode)
{
	g_FullScreenMode = screenMode;
	FUN_0049d8f0(hParentWnd);
	HWND hDlgLabel = GetDlgItem(hParentWnd, LEGORR_ID_SCREENMODES_LABEL /*1006*/);
	// Screen modes changes it's title when switching to windowed or full screen mode
	if (screenMode != false /*0*/) {
		SendMessageA(hDlgLabel, WM_SETTEXT /*0xc*/, 0, (LPARAM)"Screen Mode");
	}
	else {
		SendMessageA(hDlgLabel, WM_SETTEXT /*0xc*/, 0, (LPARAM)"Window Size");
	}
}

// <LegoRR.exe @0047c8d0>
BOOL __cdecl Main_DirectDrawCreate(BOOL isFullScreen, unsigned int param_2, int param_3, int* param_4, int x, int y, int screenWidth, int screenHeight);
// passes args: (isFullScreen, x, y, width, height) straight into Wnd_setupShow_FUN_00478370 <LegoRR.exe @00478370>

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrect>
// 
// <LegoRR.exe @004785d0>
void __cdecl Win_AdjustWindowedRect(RECT* lpRect)
{
	if (((unsigned char)g_CMDLINE_FLAGS & CMD_FULLSCREEN) == 0) { // not fullscreen
		AdjustWindowRect(lpRect, g_WindowStyle, false /*0*/);
	}
}

// <LegoRR.exe @0048b540>
void __cdecl Win_SetIsFullScreen(BOOL isFullScreen)
{
	g_IsFullScreen = isFullScreen;
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlonga>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow>
// 
// <LegoRR.exe @00478370>
void __cdecl Wnd_setupShow_FUN_00478370(BOOL isFullScreen, int x, int y, int width, int height)
{
	HWND hWnd;
	RECT rect;

	g_RESOLUTION_width = width;
	g_RESOLUTION_height = height;
	if (isFullScreen != false /*0*/) {
		g_CMDLINE_FLAGS |= CMD_FULLSCREEN;
	}
	Win_SetIsFullScreen(isFullScreen);
	if (isFullScreen == false /*0*/) {
		rect.left = x;
		rect.top  = y;
		rect.right  = width  + x;
		rect.bottom = height + y;
		//              /* WS_POPUPWINDOW | WS_CAPTION (0x80880000 | 0xc00000)*/
		//                         /* WS_CAPTION  0xc00000*/
		// g_WindowStyle = WS_POPUP | WS_BORDER | WS_DLGFRAME | WS_SYSMENU /*0x80c80000 = 0x80000000 | 0x800000 | 0x400000 | 0x80000*/;
		g_WindowStyle = WS_POPUPWINDOW | WS_CAPTION /*0x80880000 | 0xc00000*/;
		Win_AdjustWindowedRect((LPRECT)&rect);
		SetWindowLongA(g_hWnd, GWL_STYLE /*-16*/, g_WindowStyle);
		SetWindowPos(g_hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 4);
		ShowCursor(0);
	}
	else {
		hWnd = GetDesktopWindow();
		GetWindowRect(hWnd, &rect);
		SetWindowPos(g_hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 4);
		SetCursor(NULL);
	}
	ShowWindow(g_hWnd, SW_SHOW /*5*/);
	SetActiveWindow(g_hWnd);
}

// <https://wiki.winehq.org/List_Of_Windows_Messages>
// Why is Microsoft SO BAD at making constants easily available and accessible!!??
//
// When focus is taken away by another window:
// WM_ACTIVATEAPP (0x001c): <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-activateapp>
// 
// when F10 or Alt+_ key combo is pressed:
// WM_SYSKEYDOWN  (0x0104): <https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-syskeydown>
// WM_SYSKEYUP    (0x0105): <https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-syskeyup>
// 
// 
// <LegoRR.exe @004782d0>
BOOL __cdecl Win_ShouldHandleMessage(MSG* msg)
{
	if (((unsigned char)g_CMDLINE_FLAGS & CMD_FULLSCREEN) != 0) {
		unsigned int wm = msg->message;
		if (msg->message == WM_ACTIVATEAPP /*0x1c*/ || msg->message == WM_SYSKEYDOWN /*0x104*/ || msg->message == WM_SYSKEYUP /*0x105*/)
			return false /*0*/;
	}
	return true /*1*/;

	// unsigned int iVar1;


	// if (((unsigned char)g_CMDLINE_FLAGS & CMD_FULLSCREEN) != 0 && (msg->message == WM_ACTIVATEAPP /*0x1c*/ || msg->message == WM_SYSKEYDOWN /*0x104*/ || msg->message == WM_SYSKEYUP /*0x105*/)) {
	// 	return false /*0*/;
	// }
	// return true /*1*/;
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-translatemessage>
// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-dispatchmessagea>

// <LegoRR.exe @00478300>
void __cdecl Win_HandleMessageQueue(void)
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, 1)) {
		if (Win_ShouldHandleMessage(&msg)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}

// <https://docs.microsoft.com/en-us/previous-versions/dd757161(v=vs.85)>
// <https://docs.microsoft.com/en-us/previous-versions/dd757158(v=vs.85)>


// <LegoRR.exe @00489520>
BOOL __cdecl Music_UpdateErrorString(void)
{
	return mciGetErrorStringA(g_mciLastError, g_mciErrorText, 200);
}

// <LegoRR.exe @00488e70>
void __cdecl Music_PlayTrack(int trackIndex, int musicState, MusicCallbackFuncPtr* callback)
{
	if (g_SoundEnabled != 0) {
		if (musicState == true /*1*/) {
			g_MusicState = true /*1*/;
		}
		g_MusicTrackIndex = trackIndex;
		g_MusicCallback = callback;
		Music_CDAudio_Open(trackIndex);
	}
	return;
}

// <LegoRR.exe @004895f0>
BOOL __cdecl Music_CDAudio_Open(int trackIndex)
{
	g_mciLastError = mciSendStringA("open cdaudio", g_mciErrorText, 200, NULL);
	if (g_mciLastError == 0) {
		g_mciLastError = mciSendStringA("set cdaudio time format tmsf", g_mciErrorText, 200, NULL);
		if (g_mciLastError == 0) {
			Music_CDAudio_Play(trackIndex);
			if (g_mciLastError == 0) {
				return true /*1*/;
			}
		}
	}
	Music_UpdateErrorString();
	return false /*0*/;
}

// <LegoRR.exe @00489540>
BOOL __cdecl Music_IsTrackPlaying(int trackIndex)
{
	// int currentTrack;
	char buffer[100];
	
	// get audio mode
	sprintf(buffer, "status cdaudio mode");
	g_mciLastError = mciSendStringA(buffer, g_mciErrorText, 200, NULL);
	if (_stricmp(g_mciErrorText, "stopped") != 0) { // audio is playing (/paused?)

		// get current audio track
		sprintf(buffer, "status cdaudio current track");
		g_mciLastError = mciSendStringA(buffer, g_mciErrorText, 200, NULL);
		int currentTrack = atoi(g_mciErrorText);
		
		if (currentTrack <= trackIndex + 1)
			return true /*1*/;
	}
	Music_UpdateErrorString();
	return false /*0*/;
}

// <LegoRR.exe @00488ec0>
void __cdecl Music_Update(BOOL isMusicOn)
{
	if (!g_SoundEnabled)
		return;

	unsigned int currentTime = timeGetTime();
	unsigned int lastTime = g_MusicUpdateTime; // keeping this in-case there's some awkward multithreading race condition...
	if (currentTime > lastTime + 4000) {
		unsigned int nextTime = currentTime; // current time is updated even when isMusicOn is false

		if (isMusicOn && !Music_IsTrackPlaying(g_MusicTrackIndex)) {
			if (g_MusicState != false /*0*/)
				Music_CDAudio_Play(g_MusicTrackIndex);

			if (g_MusicCallback != NULL)
				(*g_MusicCallback)();
		}
		g_MusicUpdateTime = nextTime;
	}

	// DWORD DVar1;
	// DWORD DVar2;
	// int iVar3;

	// if (((g_SoundEnabled != 0 &&
	// 	(DVar2 = timeGetTime(), DVar1 = g_MusicUpdateTime, g_MusicUpdateTime + 4000 < DVar2)) &&
	// 	(DVar1 = DVar2, isMusicOn != false /*0*/)) && (iVar3 = Music_IsTrackPlaying(g_MusicTrackIndex), iVar3 == 0))
	// {
	// 	if (g_MusicState != false /*0*/) {
	// 		Music_CDAudio_Play(g_MusicTrackIndex);
	// 	}
	// 	if (g_MusicCallback != NULL) {
	// 		(*g_MusicCallback)(); // call callback (which may just select the next track automatically)
	// 	}
	// }
	// g_MusicUpdateTime = DVar1;
	// return;
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-wsprintfa>
// 
// <LegoRR.exe @004894d0>
BOOL __cdecl Music_CDAudio_Play(int trackIndex)
{
	char buffer[100];

	wsprintfA(buffer, "play cdaudio from %i", trackIndex + 1);
	g_mciLastError = mciSendStringA(buffer, g_mciErrorText, 200, NULL);
	if (g_mciLastError != 0) {
		Music_UpdateErrorString();
		return false /*0*/;
	}
	return true /*1*/;
}

// <LegoRR.exe @00488eb0>
BOOL __cdecl Music_CDAudio_Close(void)
{
	if (lego::globals::g_SoundEnabled == false /*0*/) {
		return false /*0*/;
	}
	g_mciLastError = mciSendStringA("stop cdaudio", g_mciErrorText, 200, NULL);
	if (g_mciLastError == 0 /*success*/) {
		g_mciLastError = mciSendStringA("close cdaudio", g_mciErrorText, 200, NULL);
		if (g_mciLastError == 0 /*success*/) {
			return true /*1*/;
		}
	}
	Music_UpdateErrorString();
	return false /*0*/;
}

// <LegoRR.exe @004296d0>
void __cdecl Music_CDAudio_PlayNextCallback(void)
{
	Music_CDAudio_Close();
	Music_PlayNext(true /*1*/);
	return;
}

// <LegoRR.exe @00414dd0>
void __cdecl FUN_00414dd0(BOOL isMusicOff)
{
  	Music_PlayNext((uint)(isMusicOff == 0));
  	return;
}

// <LegoRR.exe @004296e0>
void __cdecl Music_PlayNext(BOOL isMusicOn)
{
	if (isMusicOn != 0) {
		short sVar1 = randomInt16();
		g_GAME_GameFlags1 |= 8; // CDTrack playing?
		Music_PlayTrack(((unsigned int)(int)sVar1 % g_CDTracks - 1) + g_CDStartTrack, 0, Music_CDAudio_PlayNextCallback);
		return;
	}
	else {
		g_GAME_GameFlags1 &= ~0x8 /*0xfffffff7*/; // CDTrack not playing?
		Music_CDAudio_Close();
		Music_Update(0);
		return;
	}
}

// <LegoRR.exe @0047aac0>
void __cdecl lego::main::Main_DirectSoundCleanup(void)
{
	if (globals::g_DirectSoundEnabled != false /*0*/) {
		FUN_0047b7c0(DAT_0053487c);
		(**(code **)(*DAT_005075bc + 0x48))(DAT_005075bc);
		(**(code **)(*DAT_005075bc + 8))(DAT_005075bc);
		(**(code **)(*DAT_005075b8 + 8))(DAT_005075b8);
		DAT_005075b8 = (int *)NULL;
		globals::g_DirectSoundEnabled = false /*0*/;
	}
	return;
}

// <LegoRR.exe @00424fd0>
void __cdecl Game_Exit(void)
{
	Music_PlayNext(false /*0*/);
	exit(0);
	return;
}

// <LegoRR.exe @00424c20>
void __cdecl thunk_Game_Exit(void)
{
	Game_Exit();
	return;
}


// <LegoRR.exe @00478290>
BOOL __cdecl Main_SetGameFuncPtrs(GameFunctions* gameFuncs)
{
	if (gameFuncs != NULL) {                                          
		g_GameFunctions.init = gameFuncs->init;
		g_GameFunctions.update = gameFuncs->update;
		g_GameFunctions.cleanup = gameFuncs->cleanup;
		g_GameFunctions_ISINIT = 1;
		return true /*1*/;
	}
	return false /*0*/;
}

// <https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowtexta>
// 
// <LegoRR.exe @00478690>
BOOL __cdecl Win_SetWindowTitle(const char* title)
{
	return SetWindowTextA(g_hWnd, title);
}

// <LegoRR.exe @0041f950>
BOOL __cdecl Main_InitGameFunctions(const char* exeName)
{
	// int iVar1;
	// CFGProperty **ppCVar2;
	// 
	// ppCVar2 = &g_LegoCfgRoot;
	// for (iVar1 = 0x3be; iVar1 != 0; iVar1--) {
	// 	*ppCVar2 = (CFGProperty *)0x0;
	// 	ppCVar2++;
	// }
	
	memset(&g_LegoCfgRoot, 0, 0xef8 /*?? 0x3be * 0x4*/);
	g_CFG_ROOTPATH = exeName;
	Win_SetWindowTitle(exeName);
	
	GameFunctions gameFuncs; // local_c
	gameFuncs.init = Main_loadLegoCFG;
	gameFuncs.update = Main_GameUpdate;
	gameFuncs.cleanup = Main_GameCleanup;
	if (g_PROGRAMMER_MODE != 10)
		gameFuncs.cleanup = thunk_Game_Exit;

	return Main_SetGameFuncPtrs(&gameFuncs);
}


// <LegoRR.exe @0047cfb0>
void __cdecl FUN_0047cfb0(void)
{
	if (DAT_0076bc88 != (int *)0x0) {
		(**(code **)(*DAT_0076bc88 + 8))(DAT_0076bc88);
	}
	if (DAT_0076bc94 != (int *)0x0) {
		(**(code **)(*DAT_0076bc94 + 8))(DAT_0076bc94);
	}
	if (DAT_0076bc98 != (int *)0x0) {
		(**(code **)(*DAT_0076bc98 + 8))(DAT_0076bc98);
	}
	if (DAT_0076bc84 != (int *)0x0) {
		if (g_ScreenIsFullScreen != 0) {
			(**(code **)(*DAT_0076bc84 + 0x4c))(DAT_0076bc84);
		}
		if (DAT_0076bc84 != (int *)0x0) {
			(**(code **)(*DAT_0076bc84 + 8))(DAT_0076bc84);
		}
	}
	return;
}


// <https://docs.microsoft.com/en-us/windows/win32/api/vfw/nf-vfw-avifileinit>
// 
// <LegoRR.exe @0047ef40>
void __cdecl Main_InitAVIFile(undefined4 aviFileData)
{
	g_AVIFileData = aviFileData;
		/* WARNING: Could not recover jumptable at 0x0049b9ac. Too many branches */
		/* WARNING: Treating indirect jump as call */
	AVIFileInit();
	return;
}

// <LegoRR.exe @00409ff0>
void __cdecl FUN_00409ff0(const char* textFile, undefined4* font, const char* aviFile);

// <LegoRR.exe @00410300>
void __cdecl Main_ShowCredits(void)
{
	FUN_00409ff0(g_CreditsTextFile, g_FONT_RSFont, g_CreditsBackAVI);
	return;
}

// <LegoRR.exe @0048b520>
void __cdecl FUN_0048b520(void)
{
	PTR_00576ce0 = (LegoFileStream *)NULL;
	PTR_00576ce4 = (LegoFileStream *)NULL;
	PTR_00576ce8 = (LegoFileStream *)NULL;
	DAT_00576cec = 0;
	lego::globals::wnd::g_IsFullScreen = false /*0*/;
	return;
}

// <LegoRR.exe @0047c430>
void __cdecl FUN_0047c430(HWND hWnd)
{
	HWND_0076bc80 = hWnd;
	PTR_0076bc84 = (void *)0x0;
	PTR_0076bc88 = (void *)0x0;
	PTR_0076bc8c = (void *)0x0;
	DAT_0076bc90 = 0;
	DAT_0076bc94 = 0;
	DAT_0076bc9c = 0;
	DAT_0076bca4 = 0;
	DAT_0076bcac = 0;
	DAT_0076bcb0 = 0;
	DAT_0076bcb4 = 0;
	DAT_0076bcb8 = 0;
	return;
}


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

// <LegoRR.exe @00477410>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	char cVar1;
	DWORD DVar2;
	LPSTR pCVar3;
	undefined4 *puVar4;
	uint *puVar5;
	int iVar6;
	BOOL BVar7;
	CMDFlags CVar8;
	DWORD DVar9;
	uint uVar10;
	uint uVar11;
	undefined4 *puVar12;
	undefined4 *puVar13;
	char *pcVar14;
	char *pcVar15;
	uint local_c88;
	undefined4 uStack3204;

	char mutexName[0x400];
	char fullCmdLine[0x400];
	char errorMessage[0x400];
	char standardParameters[0x400];
	
	BOOL nosound = false /*0*/;
	BOOL insistOnCD = false /*0*/;

	if (true) {
		sprintf(mutexName, "%s Mutex", "Lego Rock Raiders");
		CreateMutexA((LPSECURITY_ATTRIBUTES)NULL, true /*1*/, mutexName);
		if (GetLastError() == ERROR_ALREADY_EXISTS /*0xb7*/)
			return 0;
	}

	char* cmdLine = GetCommandLineA();
	char* exeName = cmdLine;
	for (char* cmdPtr = cmdLine; *cmdPtr != '\0'; cmdPtr++) {
		if (*cmdPtr == '\\')
			exeName = cmdPtr + 1; // name after '\\' path separator
	}
	// while (*cmdLine != '\0') {
	// 	if (*cmdLine == '\\')
	// 		exeName = cmdLine + 1; // name after '\\' path separator
	// 	cmdLine++;
	// }
	strcpy(g_ExeName, exeName);
	// zero-out double quote '\"' characters (hopefully it's impossible for it to start with a quote character)
	for (char* exePtr = g_ExeName; *exePtr != '\0'; exePtr++) {
		if (*exePtr == '\"')
			*exePtr = '\0';
	}
	// find the last '.' for file extension
	char* exeExtension = g_ExeName;
	for (char* exePtr = g_ExeName; *exePtr != '\0'; exePtr++) {
		if (*exePtr == '.')
			exeExtension = exePtr + 1;
	}
	if (exeExtension != g_ExeName) {
		_strupr(exeExtension); // to upper
		exeExtension = strstr(g_ExeName, ".EXE");
		if (exeExtension != NULL) {
			// separate executable name from extension,
			// this name without extension will be the basis for many constant lookups
			*exeExtension = '\0'; 
		}
	}
	g_WindowClassName = g_ExeName;                                                     
	g_IsFocused = false /*0*/;
	g_IsClosing = false /*0*/;
	g_GameFunctions_ISINIT = false /*0*/;
	g_hInstance = hInstance;
	g_FPSLOCK_VSYNC = 0.0;
	g_CMDLINE_FLAGS = 0;

	// Add StandardParameters to command line arguments, then parse command line arguments
	BOOL regResult = Reg_QueryString_LocalMachine("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "StandardParameters", 0, standardParameters, 0x400);
	if (regResult == false /*0*/) {
		sprintf(fullCmdLine, "%s", lpCmdLine);
	}
	else {
		sprintf(fullCmdLine, "%s %s", lpCmdLine, standardParameters);
	}
	Boot_ParseCmdFlags(fullCmdLine, &nosound, &insistOnCD);

	regResult = Reg_QueryString_LocalMachine("SOFTWARE\\LEGO Media\\Games\\Rock Raiders", "NoHALMessage", 0, errorMessage, 0x400);
	if (regResult == false /*0*/) {
		sprintf(errorMessage, "No DirectX 3D accelerator could be found.");
	}
	FUN_0048b520();
	File_UNK_InitTableBuffers_004896b0();
	Path_InitDataDir((char *)g_ExeName, insistOnCD, "SOFTWARE\\LEGO Media\\Games\\Rock Raiders");
	ReservedPool<CFGProperty>::Init();
	Main_DirectInputCreate();
	if (Win_CreateMainWindow(hInstance) == false /*0*/)
		goto WinMain_Cleanup;

	FUN_0047c430(g_hWnd);
	if (Main_Init_Sound(nosound) == false /*0*/)
		goto WinMain_DestroyWindow;
	
	if (FUN_0049d2f0(true /*1*/, g_CMDLINE_FLAGS & CMD_DEBUG, g_CMDLINE_FLAGS & CMD_BEST, g_CMDLINE_FLAGS & CMD_WINDOW, errorMessage) == false /*0*/)
		goto WinMain_DestroyWindow;

	Main_InitAVIFile(DAT_0076bc84);
	FUN_00486140((float *)NULL);
	Main_InitGameFunctions(g_ExeName);
	if (!g_GameFunctions_ISINIT)
		goto WinMain_DestroyWindow;
	
	#pragma region ////// INIT / LOOP / CLEANUP //////

	if (g_GameFunctions.Init != NULL) {
		////// GAME INIT //////
		if ((*g_GameFunctions.Init)() == false /*0*/) {
			g_GameFunctions.Init = NULL;
			g_GameFunctions.Update = NULL;
			g_GameFunctions.Cleanup = NULL;
			goto WinMain_DestroyWindow; // (optional, control flow already takes us there)
		}
	}

	if (g_GameFunctions.Update != NULL) {
		float fpsSync = 1.0; // local_c94
		unsigned int lastTime = timeGetTime();

		////// GAME LOOP //////
		while (g_IsClosing == 0) {
			_DAT_0076bb4c = 0;
			_DAT_0076bb50 = 0;
			_DAT_0076bb54 = 0;
			_DAT_0076bb58 = 0;
			Win_HandleMessageQueue();

			if ((g_CMDLINE_FLAGS & CMD_FULLSCREEN) != 0)
				g_IsFocused = true /*1*/;

			FUN_0047f1b0();
			Input_UpdateMousePosition();

			if ((*g_GameFunctions.Update)(fpsSync) == false /*0*/)
				g_IsClosing = true /*1*/;

			FUN_00478260();
			FUN_0047cb90();

			// Okay... so we can just set this now since it's not tested against anywhere(?)
			g_CMDLINE_FLAGS &= ~0x1 /*0xfffffffe*/;
			//CMDFlags nextCmdFlags = g_CMDLINE_FLAGS & ~0x1 /*0xfffffffe*/;
			if ((g_CMDLINE_FLAGS & 0x80) != 0) {
				fpsSync = 0.8333333;
				//g_CMDLINE_FLAGS = nextCmdFlags;
			}
			else if ((g_CMDLINE_FLAGS & 0x10) != 0) {
				fpsSync = 0.0;
//LAB_00477e2a:
				//g_CMDLINE_FLAGS = nextCmdFlags;
				lastTime = timeGetTime();
			}
			else if (g_FPSLOCK_VSYNC != 0.0) {
				fpsSync = g_FPSLOCK_VSYNC;
				//goto LAB_00477e2a;
				//g_CMDLINE_FLAGS = nextCmdFlags;
				lastTime = timeGetTime();
			}
			else {
				//g_CMDLINE_FLAGS = nextCmdFlags;
				unsigned int currentTime = timeGetTime();
				
				uStack3204 = 0; // ???

				// local_c88 = currentTime - lastTime;
				// fpsSync = (float)(unsigned long long)local_c88 * 0.025f;
				fpsSync = (float)(unsigned long long)(currentTime - lastTime) * 0.025f;
				lastTime = currentTime;
				// // what the hell is this??
				// if ((ushort)((ushort)(fpsSync < 3.0) << 8 | (ushort)(fpsSync == 3.0) << 0xe) == 0) {
				// 	fpsSync = 3.0;
				// }
				// REAALLLY!???
				if (fpsSync > 3.0)
					fpsSync = 3.0;
			}
		}
	}

	if (g_GameFunctions.Cleanup != NULL) {
		////// GAME CLEANUP //////
		(*g_GameFunctions.Cleanup)();
	}

	#pragma endregion


WinMain_DestroyWindow:
	FUN_0047cfb0();
	DestroyWindow(g_hWnd);


WinMain_Cleanup:
	FUN_0047f290();
	ReservedPool<CFGProperty>::Cleanup();
	logf_removed(NULL);
	FUN_0048b550();
	Path_ScanRealFiles__0048b5b0();

	return 0;
}
