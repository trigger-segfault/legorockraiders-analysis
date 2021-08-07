//#pragma once
//#include "Model.h"

#ifdef DEFINE_EXTERNALS
//#define defExtern(symbol, cast, address) symbol cast address
//#define defExtern(symbol, cast, address) symbol cast address
//#define defGlob(symbol, cast, address) symbol cast address
//#define defFunc(symbol, cast, address) symbol cast address

#define defVar(ADDR, TYPE, NAME, ...) volatile TYPE (& NAME) __VA_ARGS__ = *(std::remove_reference_t<decltype(NAME)>*)ADDR
#define defFun(ADDR, RETURN, CONV, NAME, ...) RETURN (CONV* NAME)( __VA_ARGS__ ) = *(decltype(NAME))ADDR
//#define defCdecl(ADDR, RETURN, NAME, ...) RETURN (__cdecl* NAME) __VA_ARGS__ = *(decltype(NAME))ADDR;
#else
#pragma once
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defGlob(symbol, cast, address) extern symbol
//#define defFunc(symbol, cast, address) extern symbol

#define defVar(ADDR, TYPE, NAME, ...) /* ADDR */ extern volatile TYPE (& NAME) __VA_ARGS__ 
#define defFun(ADDR, RETURN, CONV, NAME, ...) /* ADDR */ extern RETURN (CONV* NAME)( __VA_ARGS__ )
//#define defCdecl(ADDR, RETURN, NAME, ...) extern RETURN (__cdecl* NAME) __VA_ARGS__ ;
#endif


//#define defGlob(symbol, cast, address) symbol cast address
//#define defFunc(symbol, cast, address) symbol cast address

#include "Model.h"
#include <type_traits>

using namespace lego;
//using namespace lego::game;




//#pragma warning disable format
//namespace lego {
namespace external {
#pragma region Externals

defFun(0x00478780, LRESULT, __cdecl, WindowProc_FullScreen, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
defFun(0x00478980, LRESULT, __cdecl, WindowProc_Windowed,	HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


defVar(0x004b0cc8, unsigned int,	g_RAND);

defVar(0x004dfe44, unsigned int,	g_LiveObjectLevels_Current_TABLE, [20][15][16]);  // [20][15][16]
defVar(0x004e4944, unsigned int,	g_LiveObjectLevels_Previous_TABLE, [20][15][16]); // [20][15][16]
defVar(0x004e9444, unsigned int,	g_NERPs_TrainFlags);
defVar(0x004e9448, LiveObject*,		MINIFIGOBJ_004e9448);
defVar(0x004e944c, lego::Point2I,	g_SlimySlugHoles_TABLE, [20]);
defVar(0x004e94ec, lego::Point2I,	g_RechargeSeams_TABLE, [10]);
defVar(0x004e953c, unsigned int,	g_SlimySlugHoles_COUNT);
defVar(0x004e9540, unsigned int,	g_RechargeSeams_COUNT);
defVar(0x004e9544, unsigned int,	DAT_004e9544);
defVar(0x004e9548, unsigned int,	DAT_004e9548);
defVar(0x004e954c, unsigned int,	DAT_004e954c);
defVar(0x004e9550, unsigned int,	DAT_004e9550);
defVar(0x004e9554, unsigned int,	DAT_004e9554);
defVar(0x004e9558, unsigned int,	DAT_004e9558);
defVar(0x004e955c, unsigned int,	DAT_004e955c);
defVar(0x004e9560, unsigned int,	DAT_004e9560);
defVar(0x004e9564, unsigned int,	DAT_004e9564);
defVar(0x004e9568, unsigned int,	DAT_004e9568);
defVar(0x004e956c, unsigned int,	DAT_004e956c);


defVar(0x004ebbc4, unsigned int,	DAT_004ebbc4);
defVar(0x004ebbc8, unsigned int,	DAT_004ebbc8);
defVar(0x004ebbcc, LiveObject*,		PTR_ARRAY_004ebbcc, [100]);
defVar(0x004ebd5c, unsigned int,	UINT_004ebd5c);
defVar(0x004ebd60, char*,			g_AbilityTypes_TABLE, [6]);
defVar(0x004ebd78, ImageBMP*,		g_ToolTipIcons_Abilities_TABLE, [6]);
defVar(0x004ebd90, ImageBMP*,		g_ToolTipIcons_Tools_TABLE, [11]);
defVar(0x004ebdbc, ImageBMP*,		g_ToolTipIcon_Blank);
defVar(0x004ebdc0, ImageBMP*,		g_ToolTipIcon_Ore);
defVar(0x004ebdc4, unsigned int,	g_BuildingsTeleported);

defVar(0x004ebdd8, lego::ResourceData*,	RESDATA_004ebdd8);
defVar(0x004ebddc, lego::ResourceData*,	RESDATA_004ebddc);
defVar(0x004ebde0, lego::ColourRGBF,	Vector3F_004ebde0);
defVar(0x004ebdec, lego::ColourRGBF,	Vector3F_004ebdec);
defVar(0x004ebdf8, lego::ColourRGBF,	g_BlinkRGBMax);
defVar(0x004ebe04, unsigned int,	DAT_004ebe04);
defVar(0x004ebe08, float,			g_RandomRangeForTimeBetweenBlinks_min);
defVar(0x004ebe0c, float,			g_RandomRangeForTimeBetweenBlinks_max);
defVar(0x004ebe10, unsigned int,	DAT_004ebe10);
defVar(0x004ebe14, float,			g_MaxChangeAllowed);
defVar(0x004ebe18, float,			FLOAT_004ebe18);
defVar(0x004ebe1c, float,			FLOAT_004ebe1c);
defVar(0x004ebe20, float,			FLOAT_004ebe20);
defVar(0x004ebe24, lego::ColourRGBF,	g_FadeRGBMin);
defVar(0x004ebe30, lego::ColourRGBF,	g_FadeRGBMax);
defVar(0x004ebe3c, float,			FLOAT_004ebe3c);
defVar(0x004ebe40, float,			g_RandomRangeForTimeBetweenFades_min);
defVar(0x004ebe44, float,			g_RandomRangeForTimeBetweenFades_max);
defVar(0x004ebe48, float,			FLOAT_004ebe48);
defVar(0x004ebe4c, float,			FLOAT_004ebe4c);
defVar(0x004ebe50, float,			FLOAT_004ebe50);
defVar(0x004ebe54, float,			g_RandomRangeForFadeTimeFade_min);
defVar(0x004ebe58, float,			g_RandomRangeForFadeTimeFade_max);
defVar(0x004ebe5c, float,			FLOAT_004ebe5c);
defVar(0x004ebe60, float,			g_RandomRangeForHoldTimeOfFade_min);
defVar(0x004ebe64, float,			g_RandomRangeForHoldTimeOfFade_max);
defVar(0x004ebe68, float,			FLOAT_004ebe68);
defVar(0x004ebe6c, float,			FLOAT_004ebe6c);
defVar(0x004ebe70, float,			FLOAT_004ebe70);
defVar(0x004ebe74, lego::Vector3F,	Vector3F_004ebe74);
defVar(0x004ebe80, lego::Vector3F,	g_MoveLimit_Vector);
defVar(0x004ebe8c, float,			FLOAT_004ebe8c);
defVar(0x004ebe90, float,			g_RandomRangeForTimeBetweenMoves_min);
defVar(0x004ebe94, float,			g_RandomRangeForTimeBetweenMoves_max);
defVar(0x004ebe98, float,			FLOAT_004ebe98);
defVar(0x004ebe9c, float,			g_RandomRangeForSpeedOfMove_min);
defVar(0x004ebea0, float,			g_RandomRangeForSpeedOfMove_max);
defVar(0x004ebea4, float,			FLOAT_004ebea4);
defVar(0x004ebea8, float,			FLOAT_004ebea8);
defVar(0x004ebeac, float,			FLOAT_004ebeac);
defVar(0x004ebeb0, float,			FLOAT_004ebeb0);
defVar(0x004ebeb4, float,			g_RandomRangeForDistOfMove_min);
defVar(0x004ebeb8, float,			g_RandomRangeForDistOfMove_max);

defVar(0x004ebec8, unsigned int,	FLAGS_004ebec8);

defVar(0x004ebf20, MessageAction,	MessageAction_ARRAY_ARRAY_004ebf20, [2][2048]);

defVar(0x004fff28, BOOL,			BOOL_004fff28);
defVar(0x004fff2c, LiveObject*,		g_SelectedUnits_TABLE, [100]);
defVar(0x005000bc, Keys,			g_SelectedUnit_Hotkeys_Keys_TABLE, [10]);
defVar(0x005000c8, MessageAction,	g_SelectedUnit_Hotkeys_Actions_TABLE, [10]);
defVar(0x00500190, const char*,		g_Messages_TABLE, [65]);
defVar(0x00500294, unsigned int,	DAT_00500294);
defVar(0x00500298, unsigned int,	g_SelectedUnits_COUNT);
defVar(0x0050029c, unsigned int,	g_SelectedUnit_Hotkeys_COUNT);

defVar(0x00500958, int,					g_NERPs_REGISTERS_TABLE, [8]);
defVar(0x00500978, BOOL,				g_NERPs_IsLoaded);

defVar(0x00500980, unsigned int,		g_NERPs_TutorialFlags);

defVar(0x00500990, int,					g_NERPs_HiddenObjectsFound);
defVar(0x00500994, int,					g_NERPs_MessageWait);

defVar(0x005009a0, float,				g_NERPs_TIMERS_TABLE, [4]);

defVar(0x00500bc0, ObjectiveFlags,		g_ObjectiveFlags);

defVar(0x00500e30, BOOL,				g_LevelIsComplete);

defVar(0x00500e48, BOOL,				g_IsEndTeleportEnabled);

defVar(0x00500e68, ObjInfoFlags,		g_ObjInfoFlags__00500e68);
defVar(0x00500e6c, unsigned int,		DAT_00500e6c);
defVar(0x00500e70, unsigned int,		DAT_00500e70);
defVar(0x00500e74, lego::Size2F,		g_HealthBarWidthHeight);
defVar(0x00500e7c, unsigned int,		g_HealthBarBorderSize);
defVar(0x00500e80, float,				g_HealthBarBorderRGB_red);
defVar(0x00500e84, float,				g_HealthBarBorderRGB_red_bright);
defVar(0x00500e88, float,				g_HealthBarBorderRGB_red_dark);
defVar(0x00500e8c, float,				g_HealthBarBorderRGB_green);
defVar(0x00500e90, float,				g_HealthBarBorderRGB_green_bright);
defVar(0x00500e94, float,				g_HealthBarBorderRGB_green_dark);
defVar(0x00500e98, float,				g_HealthBarBorderRGB_blue);
defVar(0x00500e9c, float,				g_HealthBarBorderRGB_blue_bright);
defVar(0x00500ea0, float,				g_HealthBarBorderRGB_blue_dark);
defVar(0x00500ea4, lego::ColourRGBF,	g_HealthBarRGB);
defVar(0x00500eb0, lego::ColourRGBF,	g_HealthBarBackgroundRGB);
defVar(0x00500ebc, lego::Point2F,	g_HungerImagesPosition);

defVar(0x00500ed8, lego::Point2F,	g_BubbleImagesPosition);



defVar(0x005010e0, const char*,		g_PanelTypes_TABLE, [24]);

defVar(0x0050134c, unsigned int,	DAT_0050134c);
defVar(0x00501350, char*,			g_PanelButtons_Radar_TABLE, [24]);
defVar(0x005013b0, char*,			g_PanelButtons_unused1_TABLE, [24]);
defVar(0x00501410, char*,			g_PanelButtons_unused2_TABLE, [24]);
defVar(0x00501470, char*,			g_PanelButtons_unused3_TABLE, [24]);
defVar(0x005014d0, char*,			g_PanelButtons_unused4_TABLE, [24]);
defVar(0x00501530, char*,			g_PanelButtons_CrystalSideBar_TABLE, [24]);
defVar(0x00501590, char*,			g_PanelButtons_TopPanel_TABLE, [24]);
defVar(0x005015f0, char*,			g_PanelButtons_Information_TABLE, [24]);
defVar(0x00501650, char*,			g_PanelButtons_PriorityList_TABLE, [24]);
defVar(0x005016b0, char*,			g_PanelButtons_CameraControl_TABLE, [24]);
defVar(0x00501710, char*,			g_PanelButtons_InfoDock_TABLE, [24]);
defVar(0x00504190, char*,			g_PanelButtons_Encyclopedia_TABLE, [24]);
defVar(0x005017d0, unsigned int,	UINT_005017d0);
defVar(0x005017d4, unsigned int,	UINT_005017d4);
defVar(0x005017d8, unsigned int,	DAT_005017d8);
defVar(0x005017dc, unsigned int,	DAT_005017dc);
defVar(0x005017e0, ImageBMP*,		g_RightPanel_SmallCrystal_bmp);
defVar(0x005017e4, ImageBMP*,		g_RightPanel_NoSmallCrystal_bmp);
defVar(0x005017e8, ImageBMP*,		g_RightPanel_UsedCrystal_bmp);
defVar(0x005017ec, unsigned int,	g_RewardsQuotaCrystals);
defVar(0x005017f0, ImageBMP*,		g_AirMeter_AirJuice_bmp);
defVar(0x005017f4, ImageBMP*,		g_AirMeter_NoAir_bmp);
defVar(0x005017f8, lego::Point2F,	g_AirMeter_AirJuice_positionORsize);
defVar(0x00501800, unsigned int,	UINT_00501800);
defVar(0x00501804, lego::Point2F,	g_AirMeter_NoAir_positionORsize);
defVar(0x0050180c, unsigned int,	DAT_0050180c);
defVar(0x00501810, unsigned int,	DAT_00501810);
defVar(0x00501814, lego::Point2F,	g_RightPanel_CryOreSideBar_positionORsize);
defVar(0x0050181c, unsigned int,	UINT_0050181c);
defVar(0x00501820, float,			FLOAT_00501820);
defVar(0x00501824, lego::Point2I,	g_PanelRotationControl_CenterPosition);
defVar(0x0050182c, int,				g_PanelRotationControl_Radius);
defVar(0x00501830, lego::Point2F,	g_PanelRotationControl_UpImage_position);
defVar(0x00501838, lego::Point2F,	g_PanelRotationControl_DownImage_position);
defVar(0x00501840, lego::Point2F,	g_PanelRotationControl_LeftImage_position);
defVar(0x00501848, lego::Point2F,	g_PanelRotationControl_RightImage_position);

defVar(0x00501e1c, const char*,		g_Pointers_TABLE, [56]);

defVar(0x0050211c, const char*,		g_PriorityNames_a_TABLE, [27]);
defVar(0x00502188, lego::Point2F,	g_PrioritiesImagePositions_TABLE, [27]);
defVar(0x00502260, const char*,		g_PriorityNames_b_TABLE, [27]);
defVar(0x005022cc, unsigned int,	g_Priorities_unk_TABLE, [27]);
defVar(0x00502338, BOOL,			g_Priorities_bool1_TABLE, [27]);
defVar(0x005023a4, unsigned int,	g_LevelPriorities_COUNT);

defVar(0x00502468, SampleProperty,	g_SampleProperties_TABLE, [495]);
defVar(0x005033e0, SampleProperty,	g_SampleGroups_TABLE, [200]);
defVar(0x00503a20, unsigned int*,	g_SampleHashNames_TABLE);
defVar(0x00503a24, unsigned int,	g_SampleHashNames_COUNT);
defVar(0x00503a28, unsigned int,	g_SampleGroups_COUNT);
defVar(0x00503a2c, AudioFlags,		g_AudioFlags);
defVar(0x00503a30, Sound3DInstance,	g_Sound3DInstances_TABLE, [10]);
defVar(0x00503b20, unsigned int,	g_Sound3DInstances_COUNT);
defVar(0x00503b24, float,			g_GlobalSampleDuration);
defVar(0x00503b28, int,				INT_00503b28);
defVar(0x00503b2c, int,				g_GlobalSampleIndex);
defVar(0x00503b30, int,				g_SoundQueueIndexes_Unk1_TABLE, [10]);
defVar(0x00503b58, BOOL,			g_SoundQueueModes_Unk1_TABLE, [10]);
defVar(0x00503b80, int,				g_SoundQueueIndexes_Unk2_TABLE, [10]);
defVar(0x00503ba8, BOOL,			g_SoundQueueModes_Unk2_TABLE, [10]);
defVar(0x00503bd0, unsigned int,	g_SoundQueue_Unk1_COUNT);
defVar(0x00503bd4, unsigned int,	g_SoundQueue_Unk2_COUNT);
defVar(0x00503bd8, ObjectStats**,	g_ObjectStats_TABLE, [20]);      // [20][*][*]
defVar(0x00503c28, unsigned int,	g_ObjectLevels_TABLE, [20][15]); // [20][15]

defVar(0x00504188, BOOL,			BOOL_00504188);

defVar(0x00504190, const char*,		g_TextTypes_TABLE, [26]);


defVar(0x00504608, unsigned int,	g_Texts_mutable_COUNT);
defVar(0x0050460c, unsigned int,	g_Texts_COUNT);

defVar(0x00504870, unsigned int,	g_WeaponTypes_COUNT);
defVar(0x00504874, char**,			g_WeaponNames_TABLE);


defVar(0x005063fc, CFGProperty*,	g_LegoCfgRoot_WeaponTypes);
defVar(0x00506400, char,			tmp_CHAR_ARRAY_00506400, [1024]);
defVar(0x00506804, HINSTANCE,		g_hInstance);
defVar(0x00506800, HWND,			g_hWnd);
defVar(0x00506808, BOOL,			g_IsFocused);
defVar(0x0050680c, BOOL,			g_IsClosing);
defVar(0x00506810, const char*,		g_WindowClassName);
defVar(0x00506814, char,			g_ExeName, [256]);
defVar(0x00506914, IDirect3DRM3*,		g_IDirect3DRM3);
defVar(0x00506918, IDirect3DRMDevice3*,	g_IDirect3DRMDevice3);
defVar(0x0050691c, IDirect3DDevice3*,	g_IDirect3DDevice3);
defVar(0x00506920, D3DRMSceneFogMethod,	g_SceneFogMethod);
defVar(0x00506924, lego::Size2I,		g_RESOLUTION);
defVar(0x0050692c, lego::GameFunctions,	g_GameFunctions);
defVar(0x00506938, BOOL,					g_GameFunctions_ISINIT);
defVar(0x0050693c, float,					g_FPSLOCK_VSYNC);
defVar(0x00506f80, DWORD,					g_WindowStyle);
defVar(0x00506f84, lego::CmdlineFlags,		g_CMDLINE_FLAGS);
defVar(0x00506f88, lego::ProgrammerMode,	g_PROGRAMMER_MODE);
defVar(0x00506f8c, char,					g_STARTLEVEL, [256]);
defVar(0x00506f8c, lego::FeatureFlags,		g_DEBUG_FLAGS);



defVar(0x005570d4, LevelData*,			g_Game_level);


defVar(0x004b41c8, AITaskData*,		g_AITasks_TABLE, [12]);
defVar(0x004b41f8, AITaskData*,		g_AITasks_NEXT);
defVar(0x004b41fc, unsigned int,	g_AITasks_COUNT);
defVar(0x004b9060, unsigned int,	g_AITasks_INITFLAGS);

defVar(0x004df790, LiveObject*,		g_LiveObjects_POOL, [32]);
defVar(0x004df810, LiveObject*,		g_LiveObjects_NEXT);
defVar(0x004dfe10, unsigned int,	g_LiveObjects_COUNT);
defVar(0x004dfe14, unsigned int,	g_LiveObjects_INITFLAGS);

defVar(0x0076bd80, ResourceData*,	g_Resources_TABLE, [20]);
defVar(0x0076bdd0, ResourceData*,	g_Resources_NEXT);
defVar(0x0076dd90, unsigned int,	g_Resources_COUNT);
defVar(0x0076dd94, unsigned int,	g_Resources_INITFLAGS);


defVar(0x00507098, char,			tmp_CFG_JOINPATH, [1024]);
defVar(0x00507498, CFGProperty*,	ReservedPool_CFGProperty___g_TABLE, [32]);
defVar(0x00507518, CFGProperty*,	ReservedPool_CFGProperty___g_NEXT);
defVar(0x0050751c, unsigned int,	ReservedPool_CFGProperty___g_COUNT);
defVar(0x00507520, BOOL,			ReservedPool_CFGProperty___g_ISINIT);


defVar(0x005570c0, GameManager,			g_Game);
defVar(0x00557fb8, unsigned int,		UINT_00557fb8);
defVar(0x00557fbc, unsigned int,		UINT_00557fbc);

defVar(0x00557428, lego::ColourRGBF,	g_PowerCrystalRGB);
defVar(0x00557434, lego::ColourRGBF,	g_UnpoweredCrystalRGB);

defVar(0x0055807c, char*,			g_Main_Version);

defVar(0x0055850c, lego::Size2I,	g_Menu_SaveImage_BigSize);

defVar(0x00558514, char,			g_Menu_LoadGame_text, [64]);
defVar(0x00558554, char,			g_Menu_SaveGame_text, [64]);
defVar(0x00558594, void*,			g_UnkStruct728_Menu_SaveText);
defVar(0x00558598, void*,			g_UnkStruct728_Menu_LevelText);
defVar(0x0055859c, char,			g_MenuOverwrite_Title, [128]);
defVar(0x0055861c, char,			g_MenuOverwrite_Text, [256]);
defVar(0x0055871c, char,			g_MenuOverwrite_Ok, [128]);
defVar(0x0055879c, char,			g_MenuOverwrite_Cancel, [128]);
defVar(0x0055881c, unsigned int,	DAT_0055881c);
defVar(0x00558824, unsigned int,	DAT_00558824);
defVar(0x00558828, int,				g_Menu_MaxLevelScreens);

defVar(0x00558834, unsigned int,	DAT_00558834);
defVar(0x00558838, unsigned int,	DAT_00558838);
defVar(0x0055883c, BOOL,			BOOL_0055883c);
defVar(0x00558840, float,			FLOAT_00558840);


defVar(0x00558850, float,			g_Flocks_Turn);
defVar(0x00558854, float,			g_Flocks_Speed);
defVar(0x00558858, float,			g_Flocks_Tightness);
defVar(0x0055885c, float,			g_Flocks_GoalUpdate);
defVar(0x00558860, BOOL,			g_ObjectUIsAlwaysVisible);
defVar(0x00558864, const char*,		g_Bubbles_bmp_TABLE, [39]);
defVar(0x00558900, const char*,		g_Bubbles_TABLE, [39]);

defVar(0x005590a0, int,				g_DriverModes_COUNT);
defVar(0x005590a4, int,				g_DeviceModes_COUNT);
defVar(0x005590a8, int,				g_ScreenModes_COUNT);
defVar(0x005590ac, DriverMode,		g_DriverModes_TABLE, [200]);
defVar(0x0055a63c, DeviceMode,		g_DeviceModes_TABLE, [200]);
defVar(0x0055bbcc, ScreenMode,		g_ScreenModes_TABLE, [200]);
defVar(0x0056904c, DriverMode*,		g_CurrentDriverMode);
defVar(0x00569050, DeviceMode*,		g_CurrentDeviceMode);
defVar(0x00569054, ScreenMode*,		g_CurrentScreenMode);
defVar(0x00569058, BOOL,			g_IsFullScreen);
defVar(0x0056905c, BOOL,			g_IsFullScreen_Backup);
defVar(0x00569060, ScreenMode,		g_RegisteredScreenModes_TABLE, [200]);
defVar(0x005764e0, int,				g_RegisteredScreenModes_COUNT);

defVar(0x00576500, WADFile,			g_WADFiles_TABLE, [10]);

defVar(0x005766a0, SharedWADEntry,   g_WADStreams_TABLE, [100]);
defVar(0x00576ce0, FileStream*,		g_ScanFileStream_1);
defVar(0x00576ce4, FileStream*,		g_ScanFileStream_2);
defVar(0x00576ce8, FileStream*,		g_ScanFileStream_3);
defVar(0x00576cec, FileStream*,		g_ScanFileStream_OutputList);
defVar(0x00576cf0, char,			g_ScanFilename_InputList, [1024]);
defVar(0x005770f0, char,			g_ScanFilename_OutputList, [1024]);

defVar(0x005774f4, BOOL,			g_ScanIsFullScreen);

defVar(0x00577500, char,			g_mciErrorText, [200]);

defVar(0x005775e0, const char*,		g_KEYS_TABLE, [256]);
defVar(0x005779e0, char,			g_ScanRealFiles_FilePaths_TABLE, [2000][1024]);
defVar(0x0076b9e0, unsigned int,	g_ScanRealFiles_FilePaths_COUNT);

defVar(0x0076ba00, bool,	g_KeyboardState_Current_TABLE, [256]);
defVar(0x0076bb00, IDirectInputA*,	g_IDirectInputA);
defVar(0x0076bb04, BOOL,	g_IsDirectInputAcquired);

defVar(0x0076bb24, lego::Point2I,	g_MousePosition);

defVar(0x0076bb34, lego::Point2I,	g_MouseDeltaPosition);
defVar(0x0076bb3c, BOOL,	g_LeftButtonState);
defVar(0x0076bb40, BOOL,	g_RightButtonState);
defVar(0x0076bb44, BOOL,	BOOL_0076bb44);
defVar(0x0076bb48, BOOL,	BOOL_0076bb48);
defVar(0x0076bb4c, BOOL,	BOOL_0076bb4c);
defVar(0x0076bb50, BOOL,	BOOL_0076bb50);
defVar(0x0076bb54, BOOL,	BOOL_0076bb54);
defVar(0x0076bb58, BOOL,	g_RightButtonDoubleClicked);

defVar(0x0076bb80, bool,	g_KeyboardState_Previous_TABLE, [256]);


defFun(0x004790b0, void, __cdecl,			ReservedPool_CFGProperty___Init, void);
defFun(0x004790e0, void, __cdecl,			ReservedPool_CFGProperty___Cleanup, void);
defFun(0x00479120, CFGProperty*, __cdecl,	CFG_Open, const char* filename);
defFun(0x00479210, const char*, __cdecl,	CFG_JoinPath, const char* keyPath1, ...);
defFun(0x004792b0, CFGProperty*, __cdecl,	CFG_GetChildren, CFGProperty* prop, const char* keyPath);
defFun(0x004792e0, CFGProperty*, __cdecl,	CFG_NextFlat, CFGProperty* prop);
defFun(0x00479310, char*, __cdecl,			CFG_CopyString, CFGProperty* prop, const char* keyPath);
defFun(0x00479370, const char*, __cdecl,	CFG_ReadString, CFGProperty* prop, const char* keyPath);
defFun(0x00479390, BOOL3, __cdecl,			CFG_ReadBool, CFGProperty* prop, const char* keyPath);
defFun(0x004793d0, float , __cdecl,			CFG_ReadRadians, CFGProperty* prop, const char* keyPath);
defFun(0x00479430, float, __cdecl,			CFG_ReadRGBF, CFGProperty* prop, const char* keyPath, float* out_r, float* out_g, float* out_b);
defFun(0x00479500, void, __cdecl,			CFG_Close, CFGProperty* root);
defFun(0x00479530, CFGProperty*, __cdecl,	ReservedPool_CFGProperty___Next, CFGProperty* previous);
defFun(0x00479580, void, __cdecl,			ReservedPool_CFGProperty___Release, CFGProperty* prop);
defFun(0x004795a0, CFGProperty*, __cdecl,	CFG_GetProperty, CFGProperty* prop, const char* keyPath);
defFun(0x00479750, void, __cdecl,			ReservedPool_CFGProperty___Alloc, void);



defFun(0x00474ce0, int, __cdecl,	Res_GetMeshGroupCount, ResourceData* resData);
defFun(0x004752e0, void, __cdecl,	Res_SetMeshColorMultiplier, ResourceData* resData, int index, float r, float g, float b, float multiplier);
defFun(0x004752b0, void, __cdecl,	Res_SetMeshColorUnk, ResourceData* resData, int index, float r, float g, float b);



//typedef unsigned int ObjArrayIndexes[15];
//typedef unsigned int ObjArrayLevels[15][16];


#pragma endregion
} /* namespace external */
//#pragma warning restore format
//}

/*namespace lego {
namespace globals {
///////////////////



	extern volatile char* (&g_AbilityTypes_TABLE)[6] = *(volatile char*(*)[6])0x004ebd60;

	extern volatile unsigned int (&g_BuildingsTeleported);

///////////////////
}
}*/

/*#ifndef DEFINE_EXTERNALS
#else
#ifndefdef EXTERNAL_H
#endif*/