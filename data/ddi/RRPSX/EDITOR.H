// **************************************************************
// editor.h
// **************************************************************
#define		MAX_EDITOR_MENU_ITEMS		10

// **************************************************************
enum
{
	EDITOR_MENU_TOGGLE,
	EDITOR_MENU_FUNCTION,
	EDITOR_MENU_VALUE,				// any types defined after here can recieve left/right dpad message
	EDITOR_MENU_TRIGGER,				
};

typedef struct
{
	char 			text[128];				// text to show
	int			type;
	BOOL		toggle;
	int			value;
	void			(*callback)(int i);
}EDITOR_MENU_ITEM_TYPE;

typedef struct
{
	BOOL		show_menu;
	int			num_items;
	int			highlighted_item;
	EDITOR_MENU_ITEM_TYPE		item[MAX_EDITOR_MENU_ITEMS];
}EDITOR_MENU_TYPE;

typedef struct
{
	BOOL		active;						// is the editor active?
	int			current_object_type;			// what object are we currently editing
	int			current_object_class;			// what object are we currently editing
	
	BOOL		toggle_text;
	
	int			tempVal;						// temp val used in menu stuff
	int			edit_obj;						// which item did we press START over?
	int			selected_item;					// set to the trigger that is being hold with CIRCLE
	
}EDITOR_GLOBS_TYPE;

// **************************************************************
void 		EDITOR_SetActiveState(BOOL new_state);
BOOL 	EDITOR_GetActiveState(void);
void 		EDITOR_Initialise(void);
void 		EDITOR_Poll(void);
void 		EDITOR_Closedown(void);
void 		EDITOR_ChangeObject(char val);
void 		EDITOR_ChangeClass(char val);
void 		EDITOR_DrawText(void);
void		EDITOR_ObjectEditor(void);
void 		EDITOR_SaveObjectList(void);
void 		EDITOR_PlaceObject(void);
void 		EDITOR_SaveTriggerList(void);
void 		EDITOR_DrawObjects(void);
void		EDITOR_DrawSingleObject(int x, int y, int z, int red, int green, int blue, char *text);
void 		EDITOR_SetStringFromClassAndType(int obj_class, int obj_type, char *text);
int 		EDITOR_FindClosestObjectTo(int x, int y);
void 		EDITOR_DrawMenu(EDITOR_MENU_TYPE *menu);
void 		EDITOR_InitMenu(void);
void 		EDITOR_AddItem(EDITOR_MENU_TYPE *menu, char *text, BOOL toggle, int value, void (*Callback)(int i), int type);
void 		EDITOR_ToggleText(int item);
void 		EDITOR_SaveMap(int item);
void		EDITOR_MenuPoll(EDITOR_MENU_TYPE *menu);
void 		EDITOR_RemoveItem(int item);
void 		EDITOR_RotateItem(int item);
void 		EDITOR_PickupObject(void);
void 		EDITOR_SetTriggerPosition(int t, int x, int y);
void 		EDITOR_SaveTriggerBinary(void);
void 		EDITOR_ShowHelp(void);
void 		EDITOR_LoadMap(int item);
void		EDITOR_ChangeTrigger(int item);
void 		EDITOR_SetStringFromTriggerType(int trigger, char *text);
void 		EDITOR_DrawWorldLine(LPVECTOR3D from, LPVECTOR3D to, int r, int g, int b);


// **************************************************************
// **************************************************************
// **************************************************************
// **************************************************************

