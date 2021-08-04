

enum LRRCEDialogControls : unsigned short
{
	IDC_DRIVERS_LISTBOX     = 1000 /*0x3e8*/,
	IDC_DEVICES_LISTBOX     = 1002 /*0x3ea*/,
	IDC_SCREENS_LISTBOX     = 1003 /*0x3eb*/,

	IDC_FULLSCREEN_RADIOBTN = 1004 /*0x3ec*/,
	IDC_WINDOW_RADIOBTN     = 1005 /*0x3ed*/,

	IDC_SCREENS_LABEL       = 1006 /*0x3ee*/,

	IDC_UNLOCKLVLS_CHECKBOX      = 1008 /*0x3f0*/,


	IDC_DEBUGKEYS_CHECKBOX       = 1011 /*0x3f3*/,
	IDC_UNLIMITEDRES_CHECKBOX    = 1012 /*0x3f4*/,
	IDC_NOBUILDINGDEPS_CHECKBOX  = 1013 /*0x3f5*/,
	IDC_CRYDRAIN_FIX_CHECKBOX    = 1014 /*0x3f6*/,
	IDC_NOINTROSPLASH_CHECKBOX   = 1015 /*0x3f7*/,
	IDC_DIVIDEBYNEO_FIX_CHECKBOX = 1016 /*0x3f8*/,

	IDC_DEBUGKEYS_CHECKBOX = 1011,
	IDC_UNLIMITEDRESOURCES_CHECKBOX = 1012,
	IDC_NOBUILDINGDEPENDENCIES_CHECKBOX = 1013,
	IDC_CRYDRAINFIX_CHECKBOX = 1014,
	IDC_NOINTROSPLASHES_CHECKBOX = 1015,
	IDC_DIVIDEBYNEOFIX_CHECKBOX = 1016,
	
	//IDC_DEVICE_LABEL = -1,
	//IDC_DRIVER_LABEL = -1,
	//IDC_SCREENMODE_LABEL = -1,
	//IDC_OPTIONS_LABEL = -1,
	//IDC_TESTFIXES_LABEL = -1,
};

// <lrrce.dll @101a32dc>
struct LRRCEDialog
{
	/*04c,1*/ bool CryDrain_Fix;
	/*04d,1*/ bool DivideByNeo_Fix;
	/*04e,1*/ bool UnlimitedResources;

	/*08c,4*/ BOOL IntroSplashes;

	/*b1,*/
	//....
};


INT_PTR lrrce::DialogProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)

{
  HWND pHVar1;
  LRESULT LVar2;
  INT_PTR IVar3;
  UINT UVar4;
  WPARAM WVar5;
  LPARAM LVar6;
  
  if (message == WM_INITDIALOG) {
    if ((**(uint **)(DAT_101a31ec + 0x38) & 0x20000) != 0) {
      LVar6 = 0;
      WVar5 = BST_CHECKED;
      UVar4 = BM_SETCHECK;
      pHVar1 = GetDlgItem(hDlg,IDC_UNLOCKLVLS_CHECKBOX);
      SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    }
    if (0 < **(int **)(DAT_101a31ec + 0x34)) {
      LVar6 = 0;
      WVar5 = BST_CHECKED;
      UVar4 = BM_SETCHECK;
      pHVar1 = GetDlgItem(hDlg,IDC_DEBUGKEYS_CHECKBOX);
      SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    }
    if (*(char *)(DAT_101a32dc + 0x4c) != '\0') {
      LVar6 = 0;
      WVar5 = BST_CHECKED;
      UVar4 = BM_SETCHECK;
      pHVar1 = GetDlgItem(hDlg,IDC_CRYDRAIN_FIX_CHECKBOX);
      SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    }
    if (*(char *)(DAT_101a32dc + 0x4d) != '\0') {
      LVar6 = 0;
      WVar5 = BST_CHECKED;
      UVar4 = BM_SETCHECK;
      pHVar1 = GetDlgItem(hDlg,IDC_DIVIDEBYNEO_FIX_CHECKBOX);
      SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    }
    if (*(int *)(DAT_101a32dc + 0x8c) == 0) {
      LVar6 = 0;
      WVar5 = BST_CHECKED;
      UVar4 = BM_SETCHECK;
      pHVar1 = GetDlgItem(hDlg,IDC_NOINTROSPLASH_CHECKBOX);
      SendMessageA(pHVar1,UVar4,WVar5,LVar6);
    }
  }
  else {
    if ((message == WM_COMMAND) && (true)) {
      switch(wParam & 0xffff) {
      case 0x3f0:
        if (wParam >> 0x10 == 0) {
          **(uint **)(DAT_101a31ec + 0x38) = **(uint **)(DAT_101a31ec + 0x38) & 0xfffdffff;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_UNLOCKLVLS_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            **(uint **)(DAT_101a31ec + 0x38) = **(uint **)(DAT_101a31ec + 0x38) | 0x20000;
          }
          return TRUE;
        }
        break;
      case 0x3f3:
        if (wParam >> 0x10 == 0) {
          **(undefined4 **)(DAT_101a31ec + 0x34) = 0;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_DEBUGKEYS_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            **(undefined4 **)(DAT_101a31ec + 0x34) = 1;
          }
          return TRUE;
        }
        break;
      case 0x3f4:
        if (wParam >> 0x10 == 0) {
          *(undefined *)(DAT_101a32dc + 0x4e) = 0;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_UNLIMITEDRES_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            *(undefined *)(DAT_101a32dc + 0x4e) = 1;
          }
          return TRUE;
        }
        break;
      case 0x3f5:
        if (wParam >> 0x10 == 0) {
          **(undefined4 **)(DAT_101a31ec + 0x20c) = 0;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_NOBUILDINGDEPS_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            **(undefined4 **)(DAT_101a31ec + 0x20c) = 1;
          }
          return TRUE;
        }
        break;
      case 0x3f6:
        if (wParam >> 0x10 == 0) {
          *(undefined *)(DAT_101a32dc + 0x4c) = 0;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_CRYDRAIN_FIX_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            *(undefined *)(DAT_101a32dc + 0x4c) = 1;
          }
          return TRUE;
        }
        break;
      case 0x3f7:
        if (wParam >> 0x10 == 0) {
          *(undefined4 *)(DAT_101a32dc + 0x8c) = 1;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_NOINTROSPLASH_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            *(undefined4 *)(DAT_101a32dc + 0x8c) = 0;
          }
          return TRUE;
        }
        break;
      case 0x3f8:
        if (wParam >> 0x10 == 0) {
          *(undefined *)(DAT_101a32dc + 0x4d) = 0;
          LVar2 = SendDlgItemMessageW(hDlg,IDC_DIVIDEBYNEO_FIX_CHECKBOX,BM_GETCHECK,0,0);
          if (LVar2 != 0) {
            *(undefined *)(DAT_101a32dc + 0x4d) = 1;
          }
          return TRUE;
        }
      }
    }
  }
  IVar3 = (*DAT_1017b0b0)(hDlg,message,wParam,lParam);
  return IVar3;
}



BOOL lrrce::DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpReserved)

{
  int iVar1;
  HANDLE pvVar2;
  
  iVar1 = FUN_10137ed0();
  if (iVar1 == 0) {
    if (fdwReason == 1) {
      FUN_101349d0(globals::g_Lrrce_DialogSettings,hinstDLL);
      FUN_10122040();
      FUN_10137ce0();
      FUN_10136f90();
      pvVar2 = GetCurrentThread();
      FUN_10137470(pvVar2);
      if (1009 < globals::g_Lrrce_DialogSettings->versionNum) {
        _PatchFunction_A_10136a10(&inject::FUN_CreateMainWindow,CreateMainWindow);
        _PatchFunction_A_10136a10(&inject::FUN_ShowGameWindow,ShowGameWindow);
        _PatchFunction_A_10136a10((void **)&inject::FUN_ParseCmdlineFlags,ParseCmdlineFlags);
        _PatchFunction_A_10136a10((void **)&DAT_1017b2e8,FUN_100fcf00);
        _PatchFunction_A_10136a10((void **)&DAT_1017b08c,FUN_100ff810);
        _PatchFunction_A_10136a10((void **)&DAT_1017b09c,LRRCE_UsesUnlimitedResources_FUN_100ff4e0);
        _PatchFunction_A_10136a10((void **)&inject::FUN_CfgRead,Read);
        _PatchFunction_A_10136a10((void **)&inject::FUN_CfgReadString,ReadString);
        _PatchFunction_A_10136a10((void **)&inject::FUN_CfgReadBool,ReadBool);
        _PatchFunction_A_10136a10((void **)&DAT_1017b314,FUN_10134890);
        _PatchFunction_A_10136a10((void **)&inject::FUN_CfgReadRadians,ReadFloatMinMaxTilt);
        _PatchFunction_A_10136a10((void **)&inject::FUN_CfgReadRGB,ReadRGB);
        _PatchFunction_A_10136a10(&inject::FUN_SetMainWindowTitle,SetMainWindowTitle);
        _PatchFunction_A_10136a10((void **)&DAT_1017b320,FUN_101346a0);
        _PatchFunction_A_10136a10((void **)&DAT_1017b080,LRRCE_UsesIntroSplashes_FUN_10100310);
        _PatchFunction_A_10136a10((void **)&DAT_1017b084,LRRCE_UsesInt88_FUN_10100350);
        _PatchFunction_A_10136a10((void **)&DAT_1017b090,FUN_100fdfa0);
        _PatchFunction_A_10136a10((void **)&inject::FUN_DialogProc,DialogProc);
        _PatchFunction_A_10136a10((void **)&DAT_1017b0a4,fix::Fix_CryDrain_FUN_100ff7a0);
        _PatchFunction_A_10136a10((void **)&DAT_1017b0a8,FUN_10100db0);
        _PatchFunction_C_100e51f0(0x422664,LRRCE_UsesByte84_FUN_101002a0);
        _PatchFunction_B_100efe00(0x28,0x49d4ce,0x49d4d9,FUN_100eeca0,0);
        _PatchData_D_10128bc0(0x49d4e0,"jn",2);
      }
      if (1019 < globals::g_Lrrce_DialogSettings->versionNum) {
        _PatchFunction_A_10136a10((void **)&DAT_1017b274,FUN_10100c70);
        _PatchFunction_A_10136a10((void **)&DAT_1017b0a0,FUN_100ff760);
        _PatchFunction_A_10136a10((void **)&DAT_1017b0bc,FUN_100fdeb0);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x21c),LRRCE_UsesField74_FUN_101336e0);
        _PatchFunction_A_10136a10
                  ((void **)(DAT_101a31ec + 0x220),LRRCE_UsesField74_Lava_FUN_10133730);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x228),FUN_10133590);
        _PatchFunction_C_100e51f0(0x40eca9,LRRCE_UsesBool59_FUN_101002d0);
        _PatchData_E_100e5220(DAT_1017b0d4,FUN_10100290);
        _PatchFunction_B_100efe00(0,0x40beb2,0x40beb7,FUN_100eec00,0);
        _PatchFunction_B_100efe00(1,0x40bf56,0x40bf5d,FUN_100eec10,0);
        _PatchFunction_B_100efe00(2,0x40c178,0x40c17f,FUN_100eec20,0);
        _PatchFunction_B_100efe00(3,0x40c311,0x40c31f,FUN_100eec30,0);
        _PatchFunction_B_100efe00(4,0x40c4bd,0x40c4c4,FUN_100eec50,0);
        _PatchFunction_B_100efe00(5,0x40c4fc,0x40c503,FUN_100eec60,0);
        _PatchFunction_B_100efe00(6,0x40c608,0x40c618,FUN_100eec70,0);
        _PatchFunction_B_100efe00(7,0x40c02c,0x40c033,FUN_100eec90,0);
        _PatchData_D_10128bc0(0x4123db,";\r$iP",6);
        _PatchData_D_10128bc0(0x4123f9,";\r(iP",6);
      }
      if (1029 < globals::g_Lrrce_DialogSettings->versionNum) {
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x230),FUN_10133af0);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x234),FUN_101345f0);
        _PatchFunction_A_10136a10((void **)&DAT_1017b324,LRRCE_UsesFloat9c_Floata0_FUN_10135330);
        _PatchFunction_A_10136a10((void **)&DAT_1017b328,LRRCE_UsesFloata4_Floata8_B_FUN_101352e0);
        _PatchFunction_A_10136a10((void **)&DAT_1017b32c,LRRCE_UsesFloata4_Floata8_FUN_10134dc0);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x254),draw_ui_menuBackground);
        _PatchFunction_A_10136a10((void **)&DAT_1017b330,FUN_10134ac0);
        _PatchFunction_A_10136a10((void **)&DAT_1017b2fc,FUN_10092bc0);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x244),InitFileSystem);
        _PatchFunction_A_10136a10((void **)(DAT_101a31ec + 0x24c),FUN_10133470);
        _PatchFunction_C_100e51f0(0x423b0c,FUN_101333d0);
        _PatchFunction_C_100e51f0(0x45c4da,FUN_101333d0);
        _PatchFunction_C_100e51f0(0x49d330,LRRCE_UsesBool4f_ScreenSize_FUN_10134580);
        _PatchFunction_C_100e51f0(0x45c51c,FUN_10133410);
        _PatchFunction_C_100e51f0(0x45c5a3,FUN_10133410);
        _PatchFunction_C_100e51f0(0x45c5d4,FUN_10133410);
        _PatchFunction_C_100e51f0(0x4386ed,FUN_10134a60);
      }
      FUN_10136ff0();
    }
    else {
      if (fdwReason == 0) {
        FUN_10107090();
        FUN_10136f90();
        pvVar2 = GetCurrentThread();
        FUN_10137470(pvVar2);
        FUN_10136ff0();
      }
    }
  }
  return 1;
}

