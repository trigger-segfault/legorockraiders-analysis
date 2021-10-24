//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Steves Include File For <LEGO [Rock Raiders]>
//
// Started:	10-07-98
// Coding:	Glenn Benson
// Graphics:
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹


#ifndef	__STEVE_H


#ifndef CDVERSION

typedef	enum
{
	EM_OFF,
	EM_VERTEX_OFFSET,
	EM_COLOUR_LIGHT,
	EM_MISC,
	EM_LOAD,
	EM_SAVE,
	EM_OBJ_EDITOR,
} EDIT_MODE;

typedef struct mapedit_st
{
	int	vx;
	int	vy;
	int	mode;
	char	fileName[64];

} MAPEDITGLOBS, *lpMAPEDITGLOBS;


extern	MAPEDITGLOBS		mapeditGlobs;


#endif

lpContainer	init_test_vehicle(lpContainer root, LPUCHAR fname);


void	init_demo_vehicle(int vehicle_index);
//void	update_demo_vehicle(lpLegoCam cam);
void	set_camera_on_position(lpContainer camera_container, VECTOR3D *pos, VECTOR3D *look_pos);
void	set_camera_on_container(lpContainer camera_container, lpContainer viewed_container, VECTOR3D *cpos);

void	Steve_InitialiseGameData(void);




// **************************************************************
// editor.h
// **************************************************************
#define		MAX_EDITOR_MENU_ITEMS		10

// **************************************************************
enum
{
	EDITOR_MENU_TOGGLE,
	EDITOR_MENU_VALUE,
	EDITOR_MENU_FUNCTION,
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
	int			edit_obj;
	
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



// **************************************************************
// **************************************************************
// **************************************************************
// **************************************************************









#define	__STEVE_H
#endif
