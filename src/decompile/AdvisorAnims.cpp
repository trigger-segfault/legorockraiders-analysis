//////////////////////////////////////////////////////////////////////////////
/// FUNCTIONS:  00401000 -> 00401b90
/// GLOBALVAR:  004b3db0 -> 004b41c0
///
/// CONTAINS:
///  30 cleaned function definitions (3 of which are outside the address range)
///  12 global variables (2 of which are outside the address range)
///  6  enum types (2 of which are flags)
///  2  structures (+1 global structure to signify a module)
///
//////////////////////////////////////////////////////////////////////////////

enum PanelType : int
{
	PANEL__INVALID       = -1,

	PANEL_RADAR          = 0,
	PANEL_RADARFILL      = 1,
	PANEL_RADAROVERLAY   = 2,
	PANEL_MESSAGES       = 3,
	PANEL_MESSAGESIDE    = 4,
	PANEL_CRYSTALSIDEBAR = 5,
	PANEL_TOPPANEL       = 6,
	PANEL_INFORMATION    = 7,
	PANEL_PRIORITYLIST   = 8,
	PANEL_CAMERACONTROL  = 9,
	PANEL_INFODOCK       = 10,
	PANEL_ENCYCLOPEDIA   = 11,

	PANEL__COUNT         = 12, // number of panels, often treated as "NULL" (no panel)
};

enum TextType : int
{
	TEXT__INVALID            = -1,

	TEXT_WALK                = 0,
	TEXT_DRILL               = 1,
	TEXT_NODRILL             = 2,
	TEXT_CANTDRILL           = 3,
	TEXT_REINFORCE           = 4,
	TEXT_CANTREINFORCE       = 6,
	TEXT_NOREINFORCE         = 5,
	TEXT_PICKUPCRYSTAL       = 7,
	TEXT_ENCYCLOPEDIA        = 8,
	TEXT_RADARHELP           = 9,
	TEXT_BUILDHELP           = 10,
	TEXT_SELECTIONHELP       = 11,
	TEXT_DRIVE               = 12,
	TEXT_CANTDRIVE           = 13,
	TEXT_MAKETELEPORTER      = 14,
	TEXT_CANNOTPLACEBUILDING = 15,
	TEXT_CRYSTALOREDISABLED  = 16,
	TEXT_CRYSTALFOUND        = 17,
	TEXT_CAVERNDISCOVERED    = 18,
	TEXT_OREFOUND            = 19,
	TEXT_AIRSUPPLYLOW        = 20,
	TEXT_AIRSUPPLYRUNNINGOUT = 21,
	TEXT_SPACETOCONTINUE     = 22,
	TEXT_GAMECOMPLETE        = 23,
	TEXT_MANTRAINED          = 24,
	TEXT_UNITUPGRADED        = 25,

	TEXT__COUNT              = 26, // number of texts, often treated as "NULL" (no text)
};

enum AdvisorAnimType : int
{
	ADVISORANIM__INVALID   = -1,

	ADVISORANIM_POINTTOMAP = 0,
	ADVISORANIM_POINT_N    = 1,
	ADVISORANIM_POINT_NE   = 2,
	ADVISORANIM_POINT_E    = 3,
	ADVISORANIM_POINT_SE   = 4,
	ADVISORANIM_POINT_S    = 5,
	ADVISORANIM_POINT_SW   = 6,
	ADVISORANIM_POINT_W    = 7,
	ADVISORANIM_POINT_NW   = 8,
	ADVISORANIM_POINT_UP   = 9,
	ADVISORANIM_TALK_TOP   = 10,

	ADVISORANIM__COUNT     = 11,
};

enum AdvisorType : int
{
	ADVISOR__INVALID                         = -1,

	ADVISOR_OBJECTIVE                        = 0,
	ADVISOR_OBJECTIVEACHIEVED                = 1,
	ADVISOR_OBJECTIVEFAILED                  = 2,
	ADVISOR_ICONPOINT_NORMAL                 = 3,
	ADVISOR_ICONPOINT_BACKBUTTON             = 4,
	ADVISOR_ICONPOINT_TOPBUTTONS             = 5,
	ADVISOR_PANELPOINT_RADARTOGGLE           = 6,
	ADVISOR_PANELPOINT_RADARTOGGLEOBJECTVIEW = 7,
	ADVISOR_PANELPOINT_RADARZOOMIN           = 8,
	ADVISOR_PANELPOINT_RADARZOOMOUT          = 9,
	ADVISOR_PANELPOINT_RADARMAPVIEW          = 10,
	ADVISOR_PANELPOINT_INFODOCKGOTO          = 11,
	ADVISOR_PANELPOINT_INFODOCKCLOSE         = 12,
	ADVISOR_PANELPOINT_TOPPANELINFO          = 13,
	ADVISOR_PANELPOINT_TOPPANELOPTIONS       = 14,
	ADVISOR_PANELPOINT_TOPPANELPRIORITIES    = 15,
	ADVISOR_PANELPOINT_TOPPANELCALLTOARMS    = 16,
	ADVISOR_PANELPOINT_TOPPANELGOBACK        = 17,
	ADVISOR_PANELPOINT_CONTROLZOOMIN         = 18,
	ADVISOR_PANELPOINT_CONTROLZOOMOUT        = 19,
	ADVISOR_TALKINGAME                       = 20,

	ADVISOR__COUNT                           = 21,
};

enum AdvisorStateFlags : unsigned int
{
	ADVISORSTATE_NONE  = 0,
	ADVISORSTATE_UNK_1 = 0x1,
	ADVISORSTATE_UNK_2 = 0x2,
};

enum AdvisorPositionFlags : unsigned int
{
	ADVISORPOS_NONE    = 0,
	ADVISORPOS_NOPANEL = 0x10000,
	ADVISORPOS_DEFAULT = 0x20000,
	ADVISORPOS_HASTEXT = 0x40000,
};


struct AdvisorAnimData
{
	/*0,4*/ ResourceData * resData;
	/*4,4*/ float loopStartTime; // ignored when not looping
	/*8,4*/ float loopEndTime;   // ignored when not looping
	/*c*/
};

struct AdvisorPositionData
{
	/*00,4*/ AdvisorAnimType animType;
	/*04,4*/ TextType textType;
	/*08,4*/ int sfxIndex;
	/*0c,4*/ PanelType panelType;
	/*10,8*/ Point2F point1;
	/*18,8*/ Point2F point2;
	/*20,4*/ AdvisorPositionFlags flags;
	/*24*/ 
};


// <LegoRR.exe @004b3db0>
extern char * lego::globals::g_AdvisorTypes_TABLE[ADVISOR__COUNT /*21*/];
// <LegoRR.exe @004b3e04>
extern AdvisorPositionData lego::globals::g_AdvisorPositions_TABLE[ADVISOR__COUNT /*21*/];
// <LegoRR.exe @004b40f8>
extern char * lego::globals::g_AdvisorAnimTypes_TABLE[ADVISORANIM__COUNT /*11*/];
// <LegoRR.exe @004b4124>
extern AdvisorAnimData lego::globals::g_AdvisorAnimsData_TABLE[ADVISORANIM__COUNT /*11*/];
// <LegoRR.exe @004b41a8>
extern AdvisorType lego::globals::g_Advisor_CurrentType;
// <LegoRR.exe @004b41ac>
extern ResourceData * lego::globals::g_Advisor_ResRoot;
// <LegoRR.exe @004b41b0>
extern void * lego::globals::g_Advisor_ptr1c;    // ptr1c might to be some sort of viewport resource
// <LegoRR.exe @004b41b4>
extern float lego::globals::g_AdvisorPosition_Z; // Always set to 0.96f  (was probably configurable at one point)
// <LegoRR.exe @004b41b8>
extern ResourceData * lego::globals::g_Advisor_ResLight; // 3DRM light resource
// <LegoRR.exe @004b41bc>
extern AdvisorStateFlags lego::globals::g_Advisor_CurrentFlags;

// The entire module can be fit inside a structure,
//  however it is not memzero'ed like other global structures
// <LegoRR.exe @004b3db0 -> 004b41c0>
struct AdvisorManager
{
	// <LegoRR.exe @004b3db0>
	/*000,54*/  extern char * AdvisorTypes_TABLE[ADVISOR__COUNT /*21*/];
	// <LegoRR.exe @004b3e04>
	/*054,2f4*/ extern AdvisorPositionData g_AdvisorPositions_TABLE[ADVISOR__COUNT /*21*/];
	// <LegoRR.exe @004b40f8>
	/*348,2c*/  extern char * AnimTypes_TABLE[ADVISORANIM__COUNT /*11*/];
	// <LegoRR.exe @004b4124>
	/*374,84*/  extern AdvisorAnimData AdvisorAnimsData_TABLE[ADVISORANIM__COUNT /*11*/];
	// <LegoRR.exe @004b41a8>
	/*3f8,4*/   extern AdvisorType currentType;
	// <LegoRR.exe @004b41ac>
	/*3fc,4*/   extern ResourceData * resRoot;
	// <LegoRR.exe @004b41b0>
	/*400,4*/   extern void * ptr1c;    // ptr1c might to be some sort of viewport resource
	// <LegoRR.exe @004b41b4>
	/*404,4*/   extern float position_Z; // Always set to 0.96f  (was probably configurable at one point)
	// <LegoRR.exe @004b41b8>
	/*408,4*/   extern ResourceData * resLight; // 3DRM light resource
	// <LegoRR.exe @004b41bc>
	/*40c,4*/   extern AdvisorStateFlags flags;
	/*410*/
};
// <LegoRR.exe @004b3db0>
extern AdvisorManager g_Advisor;


// <LegoRR.exe @00401000>
void __cdecl lego::front::Advisor_Init(const char *keyRoot, Struct_bc *structbc, void *ptr_1c)
{
	globals::g_AdvisorTypes_TABLE[0] = "Advisor_Objective";
	globals::g_AdvisorTypes_TABLE[1] = "Advisor_ObjectiveAcheived";
	globals::g_AdvisorTypes_TABLE[2] = "Advisor_ObjectiveFailed";
	globals::g_AdvisorTypes_TABLE[3] = "Advisor_IconPoint_Normal";
	globals::g_AdvisorTypes_TABLE[4] = "Advisor_IconPoint_BackButton";
	globals::g_AdvisorTypes_TABLE[5] = "Advisor_IconPoint_TopButtons";
	globals::g_AdvisorTypes_TABLE[6] = "Advisor_PanelPoint_RadarToggle";
	globals::g_AdvisorTypes_TABLE[7] = "Advisor_PanelPoint_RadarTaggedObjectView";
	globals::g_AdvisorTypes_TABLE[8] = "Advisor_PanelPoint_RadarZoomIn";
	globals::g_AdvisorTypes_TABLE[9] = "Advisor_PanelPoint_RadarZoomOut";
	globals::g_AdvisorTypes_TABLE[10] = "Advisor_PanelPoint_RadarMapView";
	globals::g_AdvisorTypes_TABLE[11] = "Advisor_PanelPoint_InfoDockGoto";
	globals::g_AdvisorTypes_TABLE[12] = "Advisor_PanelPoint_InfoDockClose";
	globals::g_AdvisorTypes_TABLE[13] = "Advisor_PanelPoint_TopPanelInfo";
	globals::g_AdvisorTypes_TABLE[14] = "Advisor_PanelPoint_TopPanelOptions";
	globals::g_AdvisorTypes_TABLE[15] = "Advisor_PanelPoint_TopPanelPriorities";
	globals::g_AdvisorTypes_TABLE[16] = "Advisor_PanelPoint_TopPanelCallToArms";
	globals::g_AdvisorTypes_TABLE[17] = "Advisor_PanelPoint_TopPanelGoBack";
	globals::g_AdvisorTypes_TABLE[18] = "Advisor_PanelPoint_ControlZoomIn";
	globals::g_AdvisorTypes_TABLE[19] = "Advisor_PanelPoint_ControlZoomOut";
	globals::g_AdvisorTypes_TABLE[20] = "Advisor_TalkInGame";

	globals::g_AdvisorAnimTypes_TABLE[0] = "Advisor_Anim_PointToMap";
	globals::g_AdvisorAnimTypes_TABLE[1] = "Advisor_Anim_Point_N";
	globals::g_AdvisorAnimTypes_TABLE[2] = "Advisor_Anim_Point_NE";
	globals::g_AdvisorAnimTypes_TABLE[3] = "Advisor_Anim_Point_E";
	globals::g_AdvisorAnimTypes_TABLE[4] = "Advisor_Anim_Point_SE";
	globals::g_AdvisorAnimTypes_TABLE[5] = "Advisor_Anim_Point_S";
	globals::g_AdvisorAnimTypes_TABLE[6] = "Advisor_Anim_Point_SW";
	globals::g_AdvisorAnimTypes_TABLE[7] = "Advisor_Anim_Point_W";
	globals::g_AdvisorAnimTypes_TABLE[8] = "Advisor_Anim_Point_NW";
	globals::g_AdvisorAnimTypes_TABLE[9] = "Advisor_Anim_Point_Up";
	globals::g_AdvisorAnimTypes_TABLE[10] = "Advisor_Anim_Talk_Top";

	globals::g_Advisor_ResRoot = structbc->resData_24;

	globals::g_Advisor_ptr1c = ptr_1c;
	globals::g_Advisor_ResLight = res::Res_CreateLight(structbc->resData_24, D3DRMLIGHT_DIRECTIONAL /*3*/, 1.0f, 1.0f, 1.0f);
	res::Res_SetFrameOrientation(globals::g_Advisor_ResLight, structbc->resData_24, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	res::Res_UnkSetup3DFrameTransform(globals::g_Advisor_ResLight, true /*use3rdFrame*/);

	globals::g_Advisor_CurrentFlags = ADVISORSTATE_NONE /*0x0*/;
	return;
}

// <LegoRR.exe @004011c0>
void __cdecl lego::front::Advisor_Cleanup(void)
{
	AdvisorAnimType animType = globals::g_AdvisorPositions_TABLE[globals::g_Advisor_CurrentType].animType;
	if (globals::g_AdvisorAnimsData_TABLE[animType].resData != NULL) {
		res::Res_UnkSetup3DFrameTransform(globals::g_AdvisorAnimsData_TABLE[animType].resData, true /*use3rdFrame*/);
	}

	globals::g_Advisor_CurrentFlags &= ~ADVISORSTATE_UNK_1 /*~0x1*/;
	res::Res_UnkSetup3DFrameTransform(globals::g_Advisor_ResLight, true /*use3rdFrame*/);
	return;
}

// <LegoRR.exe @00401210>
void __cdecl lego::front::Advisor_InitViewport(float param_unused)
{
	// it seems there used to be more functionality here, but it's been gutted
	unk::Ptr1c_ViewportGetBack(globals::g_Advisor_ptr1c);  // unused accessor (returns float)
	unk::Ptr1c_ViewportGetFront(globals::g_Advisor_ptr1c); // unused accessor (returns float)
	globals::g_AdvisorPosition_Z = 0.96f;
	return;
}

/// RESULT: sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)))
// <LegoRR.exe @00401240>
float10 __cdecl lego::math::Vector2_Distance(const Point2F *a, const Point2F *b)
{
	return std::sqrt(((a->x - b->x)*(a->x - b->x)) + ((a->y - b->y)*(a->y - b->y)));
}

/// USAGE: <advisorType>  <animFileName>,<loopStart(seconds)>,<loopEnd(seconds)>
/// NOTE: last two parameters can be set to any value if the anim is not made to loop e.g. 0,0
///
/// EXONE: Advisor_Anim_Point_Up  Mini-Figures\Captain\NEW_Captain_Point_CALL_T_ARMS,1.04,4.0
/// EXTWO: Advisor_Anim_Talk_Top  Mini-Figures\Captain\NEW_Captain_Point_QTalk,1.04,2.4
// <LegoRR.exe @00401270>
void __cdecl lego::front::Advisor_LoadAdvisorAnims(CFGProperty *root, const char *keyRoot)
{
	char *stringParts[3];
	char buffer[64];

	// 11 = length of globals::g_AdvisorAnimTypes_TABLE[]
	for (int i = 0; i < ADVISORANIM__COUNT /*11*/; i++) {
		AdvisorAnimData *animData = &globals::g_AdvisorAnimsData_TABLE[i];
		const char *animName = globals::g_AdvisorAnimTypes_TABLE[i];

		const char *keyPath = cfg::CFG_JoinPath(keyRoot,"Advisor",animName,0);
		const char *value = cfg::CFG_GetPropertyValue(root, keyPath);
		if (value == NULL) {
			if (!(globals::g_CMDLINE_FLAGS & CMD_REDUCEANIMATION)) {
				/// BUG: Reduce buffer name is never used, '!' prefix cannot
				///      be used with Advisor block properties as intended.
				std::sprintf(buffer, "!%s", animName); // unused??
				keyPath = cfg::CFG_JoinPath(keyRoot,"Advisor",animName,0);
				value = cfg::CFG_GetPropertyValue(root, keyPath);
			}
		}

		if (value != NULL) {
			util::stringSplit(value, stringParts, ",");
			animData->resData = res::Res_LoadResource(globals::g_Advisor_ResRoot, stringParts[0], "LWS", true);
			if (animData->resData != NULL) {
				res::Res_SetFrameOrientation(animData->resData, globals::g_Advisor_ResRoot, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
				res::Res_UnkSetup3DFrameTransform(animData->resData, true /*use3rdFrame*/);
			}
			animData->loopStartTime = (float)(std::atof(stringParts[1]) * 25.0);
			animData->loopEndTime   = (float)(std::atof(stringParts[2]) * 25.0);
		}
	}
	return;
}

// <LegoRR.exe @004013a0>
BOOL __cdecl lego::front::Advisor_GetAdvisorType(const char *advisorName, AdvisorType *out_advisorType)
{
	// 21 = length of globals::g_AdvisorTypes_TABLE[]
	for (int i = 0; i < ADVISOR__COUNT /*21*/; i++) {
		if (_stricmp(globals::g_AdvisorTypes_TABLE[i], advisorName) == 0) {
			*out_advisorType = i;
			return true;
		}
	}
	return false;
}

/// RESULT: out_vector = { (a.y * b.z) - (a.z * b.y),
///                        (a.z * b.x) - (a.x * b.z),
///                        (a.x * b.y) - (a.y * b.x) }
// <LegoRR.exe @004013e0>
Vector3F * __cdecl lego::math::Vector3_CrossProduct(Vector3F *out_vector, const Vector3F *a, const Vector3F *b)
{
	out_vector->x = a->y * b->z - a->z * b->y;
	out_vector->y = a->z * b->x - a->x * b->z;
	out_vector->z = a->x * b->y - a->y * b->x;
}

// <LegoRR.exe @00401430>
BOOL __cdecl lego::front::Advisor_GetAnimType(const char *animName, AdvisorAnimType *out_animType)
{
	// 11 = length of globals::g_AdvisorAnimTypes_TABLE[]
	for (int i = 0; i < ADVISORANIM__COUNT /*11*/; i++) {
		if (_stricmp(globals::g_AdvisorAnimTypes_TABLE[i], animName) == 0) {
			*out_animType = i;
			return true;
		}
	}
	return false;
}

/// RESULT: out_vector = a + b
// <LegoRR.exe @00401470>
Vector3F * __cdecl lego::math::Vector3_Add(Vector3F *out_vector, const Vector3F *a, const Vector3F *b)
{
	out_vector->x = a->x + b->x;
	out_vector->y = a->y + b->y;
	out_vector->z = a->z + b->z;
	return out_vector;
}

/// USAGE: <positionType>  <animName>,<textName|NULL>,<sfxName|SFX_NULL>,<x(float)>,<y(float)>,<panelName|NULL>
///
/// EXONE: Advisor_IconPoint_TopButtons    Advisor_Anim_Point_NE,NULL,SFX_NULL,-25,25,NULL
/// EXTWO: Advisor_PanelPoint_RadarToggle  Advisor_Anim_Point_N,NULL,SFX_NULL,220,65,Panel_Radar
// <LegoRR.exe @004014a0>
void __cdecl lego::front::Advisor_LoadAdvisorPositions(CFGProperty *root, const char *keyRoot, int screenWidth, int screenHeight)
{
	AdvisorAnimType animType;
	AdvisorType advisorType;
	int sfxIndex;
	char *stringParts[6];
	char advisorKeyPath[128];

	std::sprintf(advisorKeyPath, "AdvisorPositions%ix%i", screenWidth, screenHeight);
	const char *keyPath = cfg::CFG_JoinPath(keyRoot,advisorKeyPath,0);
	for (CFGProperty *prop = cfg::CFG_GetBlockFirstChild(root, keyPath); prop != NULL; prop = cfg::CFG_NextFlatProperty(prop)) {
		
		TextType textType   = TEXT__COUNT /*26*/;  // treated as "NULL"
		PanelType panelType = PANEL__COUNT /*12*/; // treated as "NULL"

		if (Advisor_GetAdvisorType(prop->key, &advisorType)) {
			util::stringSplit(prop->value, stringParts, ",");

			if (!Advisor_GetAnimType(stringParts[0], &animType)
				continue;
			if ((_stricmp("NULL", stringParts[1]) != 0 && !Text_GetTextType(stringParts[1], &textType))
				continue;
			if (!snd::Snd_GetSFX(stringParts[2], &sfxIndex))
				continue;

			float x = (float)std::atof(stringParts[3]);
			float y = (float)std::atof(stringParts[4]);

			if (_stricmp("NULL", stringParts[5]) == 0 || Panel_GetPanelType(stringParts[5], &panelType)) {
				Advisor_AddAdvisorPosition(advisorType, animType, textType, sfxIndex, panelType, x, y);
			}
		}
	}
	return;
}

/// RESULT: out_vector = a - b
// <LegoRR.exe @00401630>
Vector3F * __cdecl lego::math::Vector3_Subtract(Vector3F *out_vector, const Vector3F *a, const Vector3F *b)
{
	out_vector->x = a->x - b->x;
	out_vector->y = a->y - b->y;
	out_vector->z = a->z - b->z;
	return out_vector;
}

/// RESULT: out_vector = a * scalar
// <LegoRR.exe @00401660>
Vector3F * __cdecl lego::math::Vector3_Scale(Vector3F *out_vector, const Vector3F *a, float scalar)
{
	out_vector->x = a->x * scalar;
	out_vector->y = a->y * scalar;
	out_vector->z = a->z * scalar;
	return out_vector;
}

/// RESULT: ref_vector = ref_vector * (1.0 / modulus(ref_vector))
/// REFERENCE: modulus(ref_vector) -> sqrt(dot_product(ref_vector, ref_vector))
// <LegoRR.exe @00401690>
Vector3F * __cdecl lego::math::Vector3_Normalize(Vector3F *ref_vector)
{
	float10 value = 1.0 / std::sqrt((ref_vector->x * ref_vector->x) + (ref_vector->y * ref_vector->y) + (ref_vector->z * ref_vector->z));
	ref_vector->x *= value;
	ref_vector->y *= value;
	ref_vector->z *= value;
	return ref_vector;
}

// <LegoRR.exe @004016f0>
void __cdecl lego::front::Advisor_AddAdvisorPosition(AdvisorType advisorType, AdvisorAnimType animType, TextType textType, int sfxIndex, PanelType panelType, float x, float y)
{
	globals::g_AdvisorPositions_TABLE[advisorType].flags = ADVISORPOS_DEFAULT /*0x20000*/;
	globals::g_AdvisorPositions_TABLE[advisorType].animType = animType;
	globals::g_AdvisorPositions_TABLE[advisorType].textType = textType;
	globals::g_AdvisorPositions_TABLE[advisorType].sfxIndex = sfxIndex;
	globals::g_AdvisorPositions_TABLE[advisorType].point1.x = x;
	globals::g_AdvisorPositions_TABLE[advisorType].point1.y = y;
	globals::g_AdvisorPositions_TABLE[advisorType].point2.x = x;
	globals::g_AdvisorPositions_TABLE[advisorType].point2.y = y;
	globals::g_AdvisorPositions_TABLE[advisorType].panelType = panelType;

	if (panelType == PANEL__COUNT /*12*/) // NULL panel
		globals::g_AdvisorPositions_TABLE[advisorType].flags |= ADVISORPOS_NOPANEL /*0x10000*/;

	if (textType != TEXT__COUNT /*26*/) // non-NULL text
		globals::g_AdvisorPositions_TABLE[advisorType].flags |= ADVISORPOS_HASTEXT /*0x40000*/;

	return;
}

// <LegoRR.exe @00401780>
void __cdecl lego::front::Advisor_SetParameters(AdvisorType advisorType, PanelType panelType, float x1, float y1)
{
	globals::g_AdvisorPositions_TABLE[advisorType].point1.x = x1;
	globals::g_AdvisorPositions_TABLE[advisorType].point1.y = y1;
	globals::g_AdvisorPositions_TABLE[advisorType].panelType = panelType;

	if (panelType == PANEL__COUNT /*12*/) // NULL panel
		globals::g_AdvisorPositions_TABLE[advisorType].flags |= ADVISORPOS_NOPANEL /*0x10000*/;
	else
		globals::g_AdvisorPositions_TABLE[advisorType].flags &= ~ADVISORPOS_NOPANEL /*~0x10000*/;

	return;
}

// <LegoRR.exe @004017d0>
void __cdecl lego::front::Advisor_GetPoint2(AdvisorType advisorType, float *out_x2, float *out_y2)
{
	*out_x2 = globals::g_AdvisorPositions_TABLE[advisorType].point2.x;
	*out_y2 = globals::g_AdvisorPositions_TABLE[advisorType].point2.y;
	return;
}

// <LegoRR.exe @00401800>
BOOL __cdecl lego::front::Advisor_SetCurrentAdvisor(AdvisorType advisorType, BOOL setFlag2)
{
	if (globals::g_AdvisorPositions_TABLE[advisorType].flags & ADVISORPOS_DEFAULT) {
		if (globals::g_Game.unkbool_308 != 0 && !(globals::g_Advisor_CurrentFlags & ADVISORSTATE_UNK_1 /*0x1*/)) {
			globals::g_Advisor_CurrentType = advisorType;
			Advisor_SetCurrentSound(advisorType);
			globals::g_Advisor_CurrentFlags |= ADVISORSTATE_UNK_1 /*0x1*/;
			if (setAdvisorFlag3)
				globals::g_Advisor_CurrentFlags |= ADVISORSTATE_UNK_2 /*0x2*/;
			else
				globals::g_Advisor_CurrentFlags &= ~ADVISORSTATE_UNK_2 /*~0x2*/;
				
			return true;
		}
	}
	return false;
}

// <LegoRR.exe @00401870>
void __cdecl lego::front::Advisor_SetCurrentSound(AdvisorType advisorType)
{
	AdvisorAnimType animType = globals::g_AdvisorPositions_TABLE[advisorType].animType;
	ResourceData *resData = globals::g_AdvisorAnimsData_TABLE[animType].resData;
	if (resData != NULL) {
		res::Res_UnkSetup3DFrameTransform(resData, false /*!use3rdFrame*/);
		res::Res_DoCallbacks(resData, 0.0f /*elapsed time*/);
		snd::Snd_Play_FUN_00465260(globals::g_AdvisorPositions_TABLE[advisorType].sfxIndex, 0 /*mode*/);
		snd::Audio_AddToSoundQueue1(0x2a /*42*/ /*some reserved sound ID number?*/, 0 /*mode*/);
	}
	return;
}

// Called by Main_GameUpdate
// <LegoRR.exe @004018d0>
void __cdecl lego::front::Advisor_Update(float elapsed)
{
	AdvisorType advisorType = globals::g_Advisor_CurrentType;
	AdvisorAnimType animType = globals::g_AdvisorPositions_TABLE[advisorType].animType;
	ResourceData *resData = globals::g_AdvisorAnimsData_TABLE[animType].resData;

	if (resData != NULL) {
		if ((globals::g_Advisor_CurrentFlags & ADVISORSTATE_UNK_1 /*0x1*/) && globals::g_Game.unkbool_308 != 0) {
			if (globals::g_AdvisorPositions_TABLE[advisorType].flags & ADVISORPOS_HASTEXT /*0x40000*/) {
				Text_DisplayType(globals::g_AdvisorPositions_TABLE[advisorType].textType, true /*changeTiming?*/, false /*setFlag4*/);
			}
			res::Res_UnkSetup3DFrameTransform(resData, false /*!use3rdFrame*/);
			res::Res_UnkSetup3DFrameTransform(globals::g_Advisor_ResLight, false /*!use3rdFrame*/);
			FUN_00473780(globals::g_Advisor_ResLight, resData);
			Advisor_FUN_00401a70(advisorType);

			if (Advisor_FUN_004019b0(globals::g_AdvisorPositions_TABLE[advisorType].animType, elapsed))
				return;

			globals::g_Advisor_CurrentFlags &= ~ADVISORSTATE_UNK_1 /*~0x1*/;
		}
		res::Res_UnkSetup3DFrameTransform(resData, true /*use3rdFrame*/);
	}
	res::Res_UnkSetup3DFrameTransform(globals::g_Advisor_ResLight, true /*use3rdFrame*/);
	return;
}

// Called by Advisor_Update
// <LegoRR.exe @004019b0>
BOOL __cdecl lego::front::Advisor_FUN_004019b0(AdvisorAnimType animType, float elapsed)
{
	AdvisorAnimData *animData = &globals::g_AdvisorAnimsData_TABLE[animType];
	ResourceData *resData = animData->resData;

	float10 time = res::Res_DoAnimElapsedCallbacks(resData, elapsed);
	//if ((ushort)((ushort)(time < (float10)0.0) << 8 | (ushort)(time == (float10)0.0) << 0xe) == 0)
	//if (time > 0.0)

	if (globals::g_Advisor_CurrentFlags & ADVISORSTATE_UNK_2 /*0x2*/) {
		if (time > 0.0) {
			res::Res_DoCallbacks(resData, (float)(animData->loopStartTime + time));
		}
		else {
			time = res::Res_GetAnimFloat10(resData);
			if (time >= animData->loopEndTime) {
				res::Res_DoCallbacks(resData, (float)(animData->loopStartTime + (time - animData->loopEndTime)));
			}
		}
	}
	else if (time > 0.0) {
		return false;
	}

	return true;
}

// <LegoRR.exe @00401a60>
void __cdecl lego::front::Advisor_ClearFlag2(void)
{
	globals::g_Advisor_CurrentFlags &= ~ADVISORSTATE_UNK_2 /*~0x2*/;
	return;
}

// Called by Advisor_Update
// <LegoRR.exe @00401a70>
void __cdecl lego::front::Advisor_FUN_00401a70(AdvisorType advisorType)
{
	Point2F panelPosition;
	Vector3F vector;
	Vector4F transform4d;
	
	AdvisorAnimType animType = globals::g_AdvisorPositions_TABLE[advisorType].animType;
	ResourceData *resData = globals::g_AdvisorAnimsData_TABLE[animType].resData;

	if (!(globals::g_AdvisorPositions_TABLE[advisorType].flags & ADVISORPOS_NOPANEL /*0x10000*/)) {
		// output -> x, y (get panel position?)
		FUN_0045a9c0(globals::g_AdvisorPositions_TABLE[advisorType].panelType, &panelPosition.x, &panelPosition.y);
	}
	else {
		panelPosition.x = 0.0f;
		panelPosition.y = 0.0f;
	}
	transform4d.x = globals::g_AdvisorPositions_TABLE[advisorType].point1.x + panelPosition.x;
	transform4d.y = globals::g_AdvisorPositions_TABLE[advisorType].point1.y + panelPosition.y;
	transform4d.z = globals::g_AdvisorPosition_Z;
	transform4d.w = 1.0f;
	FUN_00477550(globals::g_Advisor_ptr1c, &vector, &transform4d);
	res::Res_SetFramePosition(resData, NULL, vector.x, vector.y, vector.z);
	return;
}

// <LegoRR.exe @00401b30>
ProgrammerMode __cdecl lego::main::Config_GetProgrammerMode(void)
{
	return globals::g_PROGRAMMER_MODE;
}

// <LegoRR.exe @00401b40>
const char * __cdecl lego::game::Game_GetStartLevel(void)
{
	if (globals::g_CMDLINE_FLAGS & CMD_STARTLEVEL)
		return globals::g_STARTLEVEL;
	return NULL;
}

// <LegoRR.exe @00401b60>
BOOL __cdecl lego::front::Advisor_GetFlag1(void)
{
	return globals::g_Advisor_CurrentFlags & ADVISORSTATE_UNK_1 /*0x1*/;
}

// <LegoRR.exe @00401b70>
int __cdecl lego::main::Config_GetResolutionWidth(void)
{
	return globals::g_RESOLUTION.width;
}

// <LegoRR.exe @00401b80>
int __cdecl lego::main::Config_GetResolutionHeight(void)
{
	return globals::g_RESOLUTION.height;
}



//////////////////////////////////////////////////////////////////////////////
//// LIST OF MODIFIED FUNCTION/GLOBAL NAMES OUTSIDE OF THIS ADDRESS RANGE ////

// <LegoRR.exe @005010e0>
extern char * lego::globals::g_PanelTypes_TABLE[PANEL__COUNT /*12*/];

// <LegoRR.exe @00504190>
extern char * lego::globals::g_TextTypes_TABLE[TEXT__COUNT /*26*/];


// <LegoRR.exe @0045a630>
BOOL __cdecl lego::front::Panel_GetPanelType(const char *panelName, PanelType *out_panelType)
{
	// 12 = length of globals::g_PanelTypes_TABLE[]
	for (int i = 0; i < PANEL__COUNT /*12*/; i++) {
		if (_stricmp(globals::g_PanelTypes_TABLE[i], panelName) == 0) {
			*out_panelType = i;
			return true;
		}
	}
	return false;
}

// <LegoRR.exe @0046ad90>
BOOL __cdecl lego::front::Text_GetTextType(const char *textName, TextType *out_textType)
{
	// 26 = length of globals::g_TextTypes_TABLE[]
	for (int i = 0; i < TEXT__COUNT /*26*/; i++) {
		if (_stricmp(globals::g_TextTypes_TABLE[i], textName) == 0) {
			*out_textType = i;
			return true;
		}
	}
	return false;
}

// <LegoRR.exe @00473780>
void __cdecl lego::res::Res_SetLightEnableFrame(ResourceData *resLight, ResourceData *resData)
{
	IDirect3DRMFrame *rmFrame;
	//IDirect3DRMFrame3->QueryInterface(this, IID_IDirect3DRMFrame, IDirect3DRMFrame** lplpOut)
	// (downcast: IDirect3DRMFrame3 -> IDirect3DRMFrame)
	resData->frame1->QueryInterface(idl::IID_IDirect3DRMFrame, (void **)&rmFrame);
	IDirect3DRMLight *rmLight = resLight->subdata_c->light;
	//IDirect3DRMLight->SetEnableFrame(this, IDirect3DRMFrame* lpEnableFrame)
	rmLight->SetEnableFrame(rmFrame);
	return;
}
