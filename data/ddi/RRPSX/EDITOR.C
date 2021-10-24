// ***********************************************************
// editor.c
// ***********************************************************
#include	"globals.h"

#define	MAX_TRIGGERS_PER_LEVEL				20

#define	EDITOR_DRAW_SEMI_TRANS_GREY_BOX(x,y,w,h)		Overlay_DrawFilledRectangle(x,y,w,h,32,32,32,(GsALON),10)

EDITOR_GLOBS_TYPE				editorGlobs;
TRIGGER_ENTITY				trigger_entities[MAX_TRIGGERS_PER_LEVEL];
int								placed_object_count;

EDITOR_MENU_TYPE				*current_menu;
EDITOR_MENU_TYPE				craft_menu, pickup_menu, creature_menu, main_menu;

// ***********************************************************
void EDITOR_Initialise(void)
{
int l;

	for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
	{
		trigger_entities[l].triggerType = TT_END_OF_LIST;
	}

	placed_object_count				=	0;
	editorGlobs.current_object_type 	= 	TR_CREATURE_ROCKMONSTER;
	editorGlobs.current_object_class 	= 	OC_CREATURE;
	editorGlobs.active 		 		= 	FALSE;

	editorGlobs.selected_item			=	-1;	
	current_menu = NULL;
	EDITOR_InitMenu();
}

// ***********************************************************
void EDITOR_SetActiveState(BOOL new_state)
{
	editorGlobs.active = new_state;
}

// ***********************************************************
BOOL EDITOR_GetActiveState(void)
{
	return editorGlobs.active;
}

// ***********************************************************
void EDITOR_Poll(void)
{
//lpCONTROL		control=craftGlobs.playerList[0].controlSet;
	
}

// ***********************************************************
void EDITOR_DrawText(void)
{
unsigned char buf[64];
unsigned char string[255];
int	editor_info_y = 192;
int   width;

	sprintf(buf, "OBJECT   EDITOR     %d/%d", placed_object_count, MAX_TRIGGERS_PER_LEVEL);
	Font_PrintF(legoGlobs.stdFont, 8 , editor_info_y+1, buf);
	
	EDITOR_DRAW_SEMI_TRANS_GREY_BOX( 0, editor_info_y,  gfxGlobs.scrW, gfxGlobs.scrH-editor_info_y);
	EDITOR_SetStringFromClassAndType(editorGlobs.current_object_class, editorGlobs.current_object_type, buf);

	sprintf(string, "PLACING %s", buf);
	Font_PrintF(legoGlobs.stdFont, 8, editor_info_y+16 , string);
		
	switch (editorGlobs.current_object_class)
	{
		case		OC_CRAFT		:	strcpy(buf, "CRAFTS");		break;
		case		OC_PICKUP		:	strcpy(buf, "PICK UPS");		break;
		case		OC_CREATURE	:	strcpy(buf, "CREATURES");	break;
	}
	
	Font_PrintF(legoGlobs.stdFont, 8, editor_info_y+28 , buf);
}
	
// ***********************************************************
void EDITOR_Closedown(void)
{

}

// ***********************************************************
void EDITOR_ChangeObject(char val)
{
int max_val = 0;

	editorGlobs.current_object_type+=val;
	switch (editorGlobs.current_object_class)
	{
		case	OC_CRAFT				:	max_val = TR_CRAFT_MAX_TYPES;		break;
		case	OC_PICKUP				:	max_val = TR_PICKUP_MAX_TYPES;		break;
		case	OC_CREATURE			:	max_val = TR_MAX_CREATURE_TYPES;		break;
		case	OC_MINIFIGURE			:	max_val = 0;						break;
		case	OC_SYSTEM				:	max_val = 0;						break;
	}
	
	if (editorGlobs.current_object_type < 0) 			editorGlobs.current_object_type = max_val-1;
	if (editorGlobs.current_object_type >= max_val) 	editorGlobs.current_object_type = 0;
}

// ***********************************************************
void EDITOR_ChangeClass(char val)
{
	editorGlobs.current_object_class+=val;
	if (editorGlobs.current_object_class < 0) 				editorGlobs.current_object_class = OC_CREATURE;
	if (editorGlobs.current_object_class > OC_CREATURE) 	editorGlobs.current_object_class = 0;
	
	editorGlobs.current_object_type = 0;
}

// ***********************************************************
void	EDITOR_ObjectEditor(void)
{
lpCONTROL		control=objectGlobs.playerList[0].controlSet;
int 				editor_block_delta = 16;
int				sel, l;

	// draw the markers fgor each object
	EDITOR_DrawObjects();

	// check to see if I'm toggling the menu
	if (PAD_EVENT(control, CONTROL_START))
	{
		CLEAR_EVENT_RELEASE(control, CONTROL_START);
		
		sel = EDITOR_FindClosestObjectTo( mapeditGlobs.vx, mapeditGlobs.vy);
		editorGlobs.edit_obj = sel;					// remember what we're editing
		editorGlobs.tempVal	= 0;
		
		if (sel == -1)
		{
			// if we aren't highlighting an object......show the standard menu
			current_menu = &main_menu;
		}
		else
		{
			// show contect sensitive menu
			switch (trigger_entities[sel].objectClass)
			{
				case		OC_CRAFT		:	current_menu = &craft_menu;			break;
											
				case		OC_PICKUP		:	current_menu = &pickup_menu;		break;
											
				case		OC_CREATURE	:	current_menu = &creature_menu;		break;
			}
			
			for (l = 0 ; l < current_menu->num_items ; l++)
			{
				// call all the functions here - they should check for -1 and set any viewable parameters
				editorGlobs.tempVal	= l;
				if (current_menu->item[l].callback != FALSE)		current_menu->item[l].callback(-1);
			}
		}
		
		current_menu->show_menu = !current_menu->show_menu;
	}

	editorGlobs.tempVal	= 0;
	if (current_menu->show_menu == TRUE)
	{
		EDITOR_MenuPoll(current_menu);
		return;	
	}

	// see if we want to display the help....
	if (PAD_EVENT(control,CONTROL_SYS_TRIANGLE))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_TRIANGLE);
		EDITOR_ShowHelp();
	}

	// check for returning to normal mode........
	if (PAD_EVENT(control,CONTROL_SELECT))
	{
		CLEAR_EVENT_RELEASE(control,CONTROL_SELECT);
		mapeditGlobs.mode = EM_OFF;
		Control_initialiseControlSet(objectGlobs.playerList[0].controlSet);
		return;
	}

	// scroll faster if we're holding R2 down........
	editor_block_delta = 16;					// normal speed.....
	if (PAD_EVENT(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER))
	{
		editor_block_delta = 64;				// fast speed......
		CLEAR_EVENT_IMMEDIATE(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER);
	}
	
	// scroll left..........
	if (PAD_EVENT(control,CONTROL_TURN_LEFT))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);
		mapeditGlobs.vx-=editor_block_delta;
		if (mapeditGlobs.vx<0)	mapeditGlobs.vx=0;
		EDITOR_SetTriggerPosition(editorGlobs.selected_item, mapeditGlobs.vx, mapeditGlobs.vy);
	}

	// scroll right.............
	if (PAD_EVENT(control,CONTROL_TURN_RIGHT))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);
		mapeditGlobs.vx+=editor_block_delta;
		EDITOR_SetTriggerPosition(editorGlobs.selected_item, mapeditGlobs.vx, mapeditGlobs.vy);
		/* cap for size here... */
	}

	// scroll up..........
	if (PAD_EVENT(control,CONTROL_FORWARD))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_FORWARD);
		mapeditGlobs.vy-=editor_block_delta;
		if (mapeditGlobs.vy<0)		mapeditGlobs.vy=0;
		EDITOR_SetTriggerPosition(editorGlobs.selected_item, mapeditGlobs.vx, mapeditGlobs.vy);
	}

	// scroll down............
	if (PAD_EVENT(control,CONTROL_REVERSE))
	{
	 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_REVERSE);
		mapeditGlobs.vy+=editor_block_delta;
		EDITOR_SetTriggerPosition(editorGlobs.selected_item, mapeditGlobs.vx, mapeditGlobs.vy);
		/* cap for size here... */
	}

	if (PAD_EVENT(control,CONTROL_SYS_RIGHT_TOP_SHOULDER))
	{
		EDITOR_ChangeObject(1);
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_RIGHT_TOP_SHOULDER);
	}

	if (PAD_EVENT(control,CONTROL_SYS_LEFT_TOP_SHOULDER))
	{
		EDITOR_ChangeObject(-1);
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_LEFT_TOP_SHOULDER);
	}

	if (PAD_EVENT(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER))
	{
		EDITOR_ChangeClass(1);
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_RIGHT_BOTTOM_SHOULDER);
	}

	if (PAD_EVENT(control,CONTROL_SYS_LEFT_BOTTOM_SHOULDER))
	{
		EDITOR_ChangeClass(-1);
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_LEFT_BOTTOM_SHOULDER);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CROSS))
	{
		EDITOR_PlaceObject();
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CROSS);
	}

	if (PAD_EVENT(control,CONTROL_SYS_CIRCLE))
	{
		EDITOR_PickupObject();
		CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CIRCLE);
	}
	
	EDITOR_DrawText();
}

// ***********************************************************
void EDITOR_PlaceObject(void)
{
int height = 0;

	if (Surface_GetHeight(legoGlobs.currLevel, mapeditGlobs.vx, mapeditGlobs.vy, &height) == FALSE)	return;
	
	trigger_entities[placed_object_count].objectType		= editorGlobs.current_object_type;
	trigger_entities[placed_object_count].objectClass		= editorGlobs.current_object_class;
	trigger_entities[placed_object_count].triggerType 		= TT_NO_CONDITION;
	trigger_entities[placed_object_count].elapsedTime		= 0;
	
	trigger_entities[placed_object_count].x 				= mapeditGlobs.vx;
	trigger_entities[placed_object_count].y 				= mapeditGlobs.vy;
	trigger_entities[placed_object_count].z 				= height;
	trigger_entities[placed_object_count].rotation 		= 0;

	trigger_entities[placed_object_count].parameter1 		= 0;
	trigger_entities[placed_object_count].parameter2 		= 0;
	trigger_entities[placed_object_count].parameter3 		= 0;
	trigger_entities[placed_object_count].parameter4		= 0;

	trigger_entities[placed_object_count].flags			= 0;

	placed_object_count++;
}

// ***********************************************************
void EDITOR_SaveObjectList(void)
{
char		pathname[128];
char 		buf[255];
int		handle, count, l;

	PCinit();

	sprintf(pathname, "%s\\%s\\%sOBJECTS.TXT", _DEBUGPATH, "CD_ROOT\\DATA",legoGlobs.levelPath);

//	sprintf(pathname, "C:\\TEST.TXT");
	handle=PCcreat(pathname,0);
				
	if (handle!=-1)
	{
		sprintf(buf, "Lego*{\n");					
		count = PCwrite( handle,    (void*) buf, strlen(buf));
		
		for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
		{
			if (trigger_entities[l].triggerType != TT_END_OF_LIST)
			{
				sprintf(buf, "\tObject %d {\n", l);					// write the Object 1 {		bit
				count = PCwrite( handle,    (void*) buf, strlen(buf));

				sprintf(buf, "\t\t Class %d\n", trigger_entities[l].objectClass);	count = PCwrite( handle,    (void*) buf, strlen(buf));	
				sprintf(buf, "\t\t Type %d\n", trigger_entities[l].objectType);	count = PCwrite( handle,    (void*) buf, strlen(buf));	
		
				sprintf(buf, "\t\t Xpos %d\n", trigger_entities[l].x);	count = PCwrite( handle,    (void*) buf, strlen(buf));	
				sprintf(buf, "\t\t Ypos %d\n", trigger_entities[l].y);	count = PCwrite( handle,    (void*) buf, strlen(buf));	
				sprintf(buf, "\t\t Zpos %d\n", trigger_entities[l].z);	count = PCwrite( handle,    (void*) buf, strlen(buf));	
					
				sprintf(buf, "\t}\n");					
				count = PCwrite( handle,    (void*) buf, strlen(buf));			// write the Type SNAKE
			}
		}
		
		sprintf(buf, "}\n");					
		count = PCwrite( handle,    (void*) buf, strlen(buf));
		PCclose(handle);
	}

}

// ***********************************************************
void EDITOR_SaveTriggerList(void)
{
char		pathname[128];
char 		buf[255];
int		handle, count, l, len;

	PCinit();
	//sprintf(pathname, "C:\\TRIGGERS.TXT");
	sprintf(pathname, "%s\\%s\\%sTRIGGERS.TXT", _DEBUGPATH, "CD_ROOT\\DATA",legoGlobs.levelPath);
	
	handle=PCcreat(pathname,0);
				
	if (handle!=-1)
	{
		for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
		{
			if (trigger_entities[l].triggerType != TT_END_OF_LIST)
			{
				sprintf(buf, "\tObject %d {\n", l);					// write the Object 1 {		bit
				count = PCwrite( handle,    (void*) buf, strlen(buf));

				sprintf(buf, "\t\ttriggerType %d \n", trigger_entities[l].triggerType);	count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\telapsedTime %d \n", trigger_entities[l].elapsedTime);	count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tx %d \n", trigger_entities[l].x);					count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\ty %d \n", trigger_entities[l].y);					count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tz %d \n", trigger_entities[l].z);						count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\trotation %d \n", trigger_entities[l].rotation);			count = PCwrite( handle,    (void*) buf, strlen(buf));

				sprintf(buf, "\t\tparameter1 %d \n", trigger_entities[l].parameter1);		count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tparameter2 %d \n", trigger_entities[l].parameter2);		count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tparameter3 %d \n", trigger_entities[l].parameter3);		count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tparameter4 %d \n", trigger_entities[l].parameter4);		count = PCwrite( handle,    (void*) buf, strlen(buf));

				sprintf(buf, "\t\tflags %d \n", trigger_entities[l].flags);				count = PCwrite( handle,    (void*) buf, strlen(buf));
				
				sprintf(buf, "\t\tobjectClass %d \n", trigger_entities[l].objectClass);		count = PCwrite( handle,    (void*) buf, strlen(buf));
				sprintf(buf, "\t\tobjectType %d \n", trigger_entities[l].objectType);		count = PCwrite( handle,    (void*) buf, strlen(buf));

				sprintf(buf, "\t}\n");					
				count = PCwrite( handle,    (void*) buf, strlen(buf));			
			}
		}
		PCclose(handle);
	}
}

// ***********************************************************
void EDITOR_SaveTriggerBinary(void)
{
char		pathname[128];
char 		buf[255];
int		handle, count, l, len, save_amount;

	save_amount = -1;
	for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
	{
		if ((trigger_entities[l].triggerType == TT_END_OF_LIST) && (save_amount == -1))
		{
			save_amount = l;
		}
	}
			
	if (save_amount <= 0)	return;
	
	PCinit();
//	sprintf(pathname, "C:\\OBJECTS.TRG");
	sprintf(pathname, "%s\\%s\\%sOBJECTS.TRG", _DEBUGPATH, "CD_ROOT\\DATA",legoGlobs.levelPath);
	handle=PCcreat(pathname, 0);

	if (handle!=-1)
	{
		count = PCwrite( handle,(void*)trigger_entities, sizeof(TRIGGER_ENTITY)*(placed_object_count+1));
		PCclose(handle);
	}
}

// ***********************************************************
void EDITOR_DrawObjects(void)
{
int l, r, g, b, sel;
char text[64];
char buf[255];

	sel = EDITOR_FindClosestObjectTo( mapeditGlobs.vx, mapeditGlobs.vy);

	for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
	{
		if (trigger_entities[l].triggerType != TT_END_OF_LIST)
		{
			EDITOR_SetStringFromClassAndType(trigger_entities[l].objectClass, trigger_entities[l].objectType, text);

			sprintf(buf, "%s", text);
			switch (trigger_entities[l].objectClass)
			{
				case		OC_CRAFT		:	r = 0;	g = 0; 	b = 255;		
											if (sel == l ) sprintf(buf, "|6%s", text);
											break;
											
				case		OC_PICKUP		:	r = 0;	g = 255;	b = 0	;		
											if (sel == l ) sprintf(buf, "|2%s", text);
											break;
											
				case		OC_CREATURE	:	r = 255;	g = 0;	b = 0;		
											if (sel == l ) sprintf(buf, "|1%s", text);
											break;
			}
			EDITOR_DrawSingleObject(trigger_entities[l].x, trigger_entities[l].y, trigger_entities[l].z, r, g, b, buf);
			
			if (sel == l)
			{
				// now if we've highlighted draw a line to show the angle	
				VECTOR3D	f,t;

				f.x = trigger_entities[l].x;	
				f.y = trigger_entities[l].y;	
				f.z = trigger_entities[l].z;
				
				t.x = f.x+Asm_MulFIX(rsin(trigger_entities[l].rotation), 100);
				t.y = f.y+Asm_MulFIX(rcos(trigger_entities[l].rotation), 100);
				t.z = f.z;
				EDITOR_DrawWorldLine(&f, &t, 255, 255, 255);
			}
		}
	}
}

// ***********************************************************
void	EDITOR_DrawSingleObject(int x, int y, int z, int red, int green, int blue, char *text)
{
GsLINE	line;
GsCOORDINATE2	coord;
MATRIX	mat;
short		coords[3];
long		depth,flag,sort;
SVECTOR	vector;
int width;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	vector.vx=-x;
	vector.vy=z;
	vector.vz=y;
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);

	line.attribute=0;
	line.r=red;
	line.g=green;
	line.b=blue;

	line.x0=coords[0]-15;
	line.y0=coords[1];
	line.x1=coords[0]+15;
	line.y1=coords[1];
	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);

	line.x0=coords[0];
	line.y0=coords[1]-15;
	line.x1=coords[0];
	line.y1=coords[1]+15;
	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],10);

	if (editorGlobs.toggle_text == TRUE)
	{
		width = FONT_GetStringWidth(legoGlobs.stdFont, text) / 2;
		Font_PrintF(legoGlobs.stdFont, coords[0]+(gfxGlobs.scrW/2)-width, coords[1]+(gfxGlobs.scrH/2), text);
	}
}

// ***********************************************************
void EDITOR_SetStringFromClassAndType(int obj_class, int obj_type, char *text)
{
	switch (obj_class)
 	{
		case		OC_CRAFT	:
								switch(obj_type)
								{
								case		TR_CRAFT_LARGE_DIGGER		:strcpy(text, "LARGE DIGGER");		break;
								case		TR_CRAFT_LARGE_HELICOPTER	:strcpy(text, "LARGE HELICOPTER");	break;
								case		TR_CRAFT_BIG_LASER			:strcpy(text, "BIG LASER");			break;
								case		TR_CRAFT_BULLDOZER			:strcpy(text, "BULLDOZER");		break;
								case		TR_CRAFT_SMALL_TRUCK		:strcpy(text, "SMALL TRUCK");		break;
								case		TR_CRAFT_SMALL_LASER			:strcpy(text, "SMALL LASER");		break;
								case		TR_CRAFT_SMALL_DIGGER		:strcpy(text, "SMALL DIGGER");		break;
								case		TR_CRAFT_SMALL_HELICOPTER	:strcpy(text, "SMALL HELICOPTER");	break;
								case		TR_CRAFT_HOVERBOARD			:strcpy(text, "HOVERBOARD");		break;
								}
								break;
								
		case		OC_PICKUP	:
								switch(obj_type)
								{
								case		TR_PICKUP_FREEZER_AMMO		:strcpy(text, "FREEZER AMMO");		break;
								case		TR_PICKUP_PUSHER_AMMO		:strcpy(text, "PUSHER AMMO");		break;
								case		TR_PICKUP_DYNAMITE			:strcpy(text, "DYNAMITE");			break;
								case		TR_PICKUP_SUPER_DYNAMITE	:strcpy(text, "SUPER DYNAMITE");	break;
								case		TR_PICKUP_POWER_CRYSTAL		:strcpy(text, "POWER CRYSTAL");	break;
								case		TR_PICKUP_BONUS_CRYSTAL		:strcpy(text, "BONUS CRYSTAL");		break;
								case		TR_PICKUP_FUEL				:strcpy(text, "FUEL");				break;
								case		TR_PICKUP_CRATE				:strcpy(text, "CRATE");				break;
								}
								break;

		case		OC_CREATURE	:
								switch(obj_type)
								{
								case		TR_CREATURE_ROCKMONSTER	:strcpy(text, "ROCK MONSTER");		break;
								case		TR_CREATURE_ROCKWHALE		:strcpy(text, "ROCK WHALE");		break;
								case		TR_CREATURE_SNAKE			:strcpy(text, "ROCK SNAKE");		break;
								case		TR_CREATURE_SPIDER			:strcpy(text, "ROCK SPIDER");		break;
								case		TR_CREATURE_SCORPION			:strcpy(text, "ROCK SCORPION");		break;
								}
								break;
		}
}

// ***********************************************************
int EDITOR_FindClosestObjectTo(int x, int y)
{
int l, width, height;
char text[128];

	for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
	{
		if (trigger_entities[l].triggerType != TT_END_OF_LIST)
		{
			EDITOR_SetStringFromClassAndType(trigger_entities[l].objectClass, trigger_entities[l].objectType, text);
			
			if (  (x > trigger_entities[l].x-30) && (x < trigger_entities[l].x+30) &&
			       (y > trigger_entities[l].y-30) && (y < trigger_entities[l].y+30)   )
			{
			       return l;
			}
		}	
	}

return -1;
}

// ***********************************************************
void EDITOR_DrawMenu(EDITOR_MENU_TYPE *menu)
{
int width, ypos, l;
int small_x, large_x;
char buf[128], print[128];

	if (menu->show_menu == FALSE)	return;
	
	small_x = 9999;
	large_x  = -9999;
	ypos = 80;
	
	for (l = 0 ; l < menu->num_items ; l++)
	{
		sprintf(buf, "%s", menu->item[l].text);
		
		switch (menu->item[l].type)
		{
		case		EDITOR_MENU_TOGGLE:			
												if (menu->item[l].toggle == TRUE)	
													sprintf(buf, "%s - ON", buf);
												else
													sprintf(buf, "%s - OFF", buf);
												break;
												
		case		EDITOR_MENU_VALUE:			sprintf(buf, "%s  - %d", buf, menu->item[l].value);
												break;
		
		case		EDITOR_MENU_TRIGGER:			EDITOR_SetStringFromTriggerType(trigger_entities[editorGlobs.edit_obj].triggerType, buf);
												break;
				
		}

		if (menu->highlighted_item == l)			sprintf(print, "|f%s", buf);
		else									strcpy(print, buf);

		width = FONT_GetStringWidth(legoGlobs.stdFont, print) / 2;
		Font_PrintF(legoGlobs.stdFont, (gfxGlobs.scrW/2)-width, ypos, print);
		
		if (((gfxGlobs.scrW/2)-width)  < small_x)		small_x = (gfxGlobs.scrW/2)-width;
		if (width  > large_x)						large_x = width;
		ypos+=8;
	}
	
	EDITOR_DRAW_SEMI_TRANS_GREY_BOX( small_x, 80, large_x*2, (ypos+2)-80);
}

// ***********************************************************
void EDITOR_AddItem(EDITOR_MENU_TYPE	*menu, char *text, BOOL toggle, int value, void (*Callback)(int i), int type)
{
int i;

	i = menu->num_items;
	menu->item[i].type 		= type;
	menu->item[i].toggle	= toggle;
	menu->item[i].value 	= value;
	menu->item[i].callback	= Callback;
	strcpy(menu->item[i].text, text);
	menu->num_items++;
}

// ***********************************************************
void EDITOR_InitMenu(void)
{
	main_menu.highlighted_item = 0;
	editorGlobs.toggle_text			= TRUE;

	// initialise the main menu
	main_menu.show_menu		= FALSE;
	EDITOR_AddItem(&main_menu, "TOGGLE TEXT",  TRUE, -1, EDITOR_ToggleText, EDITOR_MENU_TOGGLE);
	EDITOR_AddItem(&main_menu, "LOAD MAP", FALSE, -1, EDITOR_LoadMap, EDITOR_MENU_FUNCTION);
	EDITOR_AddItem(&main_menu, "SAVE MAP", FALSE, -1, EDITOR_SaveMap, EDITOR_MENU_FUNCTION);
	
	// initialise the craft menu
	craft_menu.show_menu		= FALSE;
	EDITOR_AddItem(&craft_menu, "REMOVE CRAFT", 	FALSE, -1,  EDITOR_RemoveItem, EDITOR_MENU_FUNCTION);
	EDITOR_AddItem(&craft_menu, "ROTATE CRAFT", FALSE, 0, EDITOR_RotateItem, EDITOR_MENU_VALUE);
	EDITOR_AddItem(&craft_menu, "EVEN MORE CRAFT STUFF", FALSE, -1, EDITOR_SaveMap, EDITOR_MENU_FUNCTION);
	
	pickup_menu.show_menu		= FALSE;
	EDITOR_AddItem(&pickup_menu, "REMOVE PICKUP", FALSE, -1,  EDITOR_RemoveItem, EDITOR_MENU_FUNCTION);
	EDITOR_AddItem(&pickup_menu, "ROTATE PICKUP", FALSE,  0, EDITOR_RotateItem, EDITOR_MENU_VALUE);
	EDITOR_AddItem(&pickup_menu, "EVEN MORE PICKUP STUFF", FALSE, -1, EDITOR_SaveMap, EDITOR_MENU_FUNCTION);

	creature_menu.show_menu		= FALSE;
	EDITOR_AddItem(&creature_menu, "ROTATE CREATURE", FALSE,  0, EDITOR_RotateItem, EDITOR_MENU_VALUE);
	EDITOR_AddItem(&creature_menu, "TRIGGER", FALSE,  0, EDITOR_ChangeTrigger, EDITOR_MENU_TRIGGER);
	EDITOR_AddItem(&creature_menu, "REMOVE CREATURE", FALSE, -1,  EDITOR_RemoveItem, EDITOR_MENU_FUNCTION);
}

// ***********************************************************
void EDITOR_ToggleText(int item)
{
	if (item == -1)		return;
	editorGlobs.toggle_text = !editorGlobs.toggle_text;
	main_menu.item[item].toggle = editorGlobs.toggle_text;
}

// ***********************************************************
void 	EDITOR_SaveMap(int item)
{
	if (item == -1)		return;
	EDITOR_SaveObjectList();
	EDITOR_SaveTriggerList();
	EDITOR_SaveTriggerBinary();
}

// ***********************************************************
void	EDITOR_MenuPoll(EDITOR_MENU_TYPE *menu)
{
lpCONTROL		control=objectGlobs.playerList[0].controlSet;

	EDITOR_DrawMenu(menu);

	if (PAD_EVENT(control,CONTROL_FORWARD))
	{
	 	CLEAR_EVENT_RELEASE(control,CONTROL_FORWARD);
		menu->highlighted_item -=1;
		if (menu->highlighted_item<0)		menu->highlighted_item = menu->num_items-1;
	}

	if (PAD_EVENT(control,CONTROL_REVERSE))
	{
	 	CLEAR_EVENT_RELEASE(control,CONTROL_REVERSE);
		menu->highlighted_item +=1;
		if (menu->highlighted_item  >	menu->num_items-1) menu->highlighted_item = 0;
	}
	
	if (PAD_EVENT(control,CONTROL_SYS_CROSS))
	{
	 	CLEAR_EVENT_RELEASE(control,CONTROL_SYS_CROSS);
		if (menu->item[menu->highlighted_item].callback != FALSE)
		{
			menu->item[menu->highlighted_item].callback(menu->highlighted_item);
		}
	}

	editorGlobs.tempVal = 0;
	
	if (  PAD_EVENT(control,CONTROL_TURN_RIGHT) && 	(menu->item[menu->highlighted_item].type >= EDITOR_MENU_VALUE))
	{
		switch (menu->item[menu->highlighted_item].type)
		{
			case		EDITOR_MENU_VALUE	: 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_RIGHT);		break;
			case		EDITOR_MENU_TRIGGER	: 	CLEAR_EVENT_RELEASE(control,CONTROL_TURN_RIGHT);			break;
		}
		editorGlobs.tempVal = 1;
		if (menu->item[menu->highlighted_item].callback != FALSE)		menu->item[menu->highlighted_item].callback(menu->highlighted_item);
	}

	if (  PAD_EVENT(control,CONTROL_TURN_LEFT) && (menu->item[menu->highlighted_item].type >= EDITOR_MENU_VALUE))
	{
		switch (menu->item[menu->highlighted_item].type)
		{
			case		EDITOR_MENU_VALUE	: 	CLEAR_EVENT_IMMEDIATE(control,CONTROL_TURN_LEFT);		break;
			case		EDITOR_MENU_TRIGGER	: 	CLEAR_EVENT_RELEASE(control,CONTROL_TURN_LEFT);			break;
		}
		editorGlobs.tempVal = -1;
		if (menu->item[menu->highlighted_item].callback != FALSE)		menu->item[menu->highlighted_item].callback(menu->highlighted_item);
	}
}

// ***********************************************************
void EDITOR_RemoveItem(int item)
{
int l;
	if (item == -1)		return;
	
	if (editorGlobs.edit_obj == placed_object_count-1)
	{
		trigger_entities[editorGlobs.edit_obj].triggerType = TT_END_OF_LIST;
		placed_object_count--;
		return;
	}
	else
	{
		for (l = editorGlobs.edit_obj ; l < placed_object_count-1 ; l++)
		{
			trigger_entities[l] = trigger_entities[l+1];
		}	
		trigger_entities[placed_object_count-1].triggerType = TT_END_OF_LIST;
		placed_object_count--;
		return;
	}
}

// ***********************************************************
void EDITOR_RotateItem(int item)
{
	// item is the menu item..ie.  menu->item[*item*]
	// we come in here with -1 when start is pressed.  Test when item is -1 then set the default value - the menu id is in editorGlobs.tempVal
	// don't forget to return out of it.
	if (item == -1)		
	{
		current_menu->item[editorGlobs.tempVal].value = trigger_entities[editorGlobs.edit_obj].rotation / (4096 / 360);
		return;
	}
	
	trigger_entities[editorGlobs.edit_obj].rotation+=editorGlobs.tempVal*12;
	if (trigger_entities[editorGlobs.edit_obj].rotation < 0) trigger_entities[editorGlobs.edit_obj].rotation = 4096;
	if (trigger_entities[editorGlobs.edit_obj].rotation > 4096) trigger_entities[editorGlobs.edit_obj].rotation = 0;
	
	current_menu->item[item].value =   trigger_entities[editorGlobs.edit_obj].rotation / (4096 / 360);
}

// ***********************************************************
void EDITOR_PickupObject(void)
{
int sel;

	if (editorGlobs.selected_item > -1)
	{
		editorGlobs.selected_item		=	-1;
		return;
	}
	
	sel = EDITOR_FindClosestObjectTo( mapeditGlobs.vx, mapeditGlobs.vy);
	if (sel == -1)		return;
	
	editorGlobs.selected_item		=	sel;
}

// ***********************************************************
void EDITOR_SetTriggerPosition(int t, int x, int y)
{
int height = 0;

	Surface_GetHeight(legoGlobs.currLevel, mapeditGlobs.vx, mapeditGlobs.vy, &height);
	if (t == -1)	return;
	
	trigger_entities[t].x	=	x;
	trigger_entities[t].y	=	y;
	trigger_entities[t].z	=	height;
}

// ***********************************************************
void EDITOR_ShowHelp(void)
{
int l;

	for (l = 0 ; l < 3 ; l++)
	{
		EDITOR_DRAW_SEMI_TRANS_GREY_BOX( 0, 0, gfxGlobs.scrW, gfxGlobs.scrH);
	}
	
	Font_PrintF(legoGlobs.stdFont, 16, 42, "|2L1 and |2R1 |7cycle through the objects you're placing");
	Font_PrintF(legoGlobs.stdFont, 16, 52, "|2L2 |7changes the object class");
	Font_PrintF(legoGlobs.stdFont, 16, 62, "|2R2 |7hold this down for faster scrolling");
	Font_PrintF(legoGlobs.stdFont, 16, 72, "|2TRIANGLE |7hold down for this help screen");
	Font_PrintF(legoGlobs.stdFont, 16, 82, "|2CIRCLE |7press to pick up object and again to put it back");
	Font_PrintF(legoGlobs.stdFont, 16, 92, "|2CROSS |7press to create a new object");
	Font_PrintF(legoGlobs.stdFont, 16, 102, "|2START |7press to get a context sensitive menu");
}

// ***********************************************************
void EDITOR_LoadMap(int item)
{
char		pathname[128];
char 		buf[255];
int		handle, count, l, len, length;

	if (item == -1)		return;
	PCinit();
	//sprintf(pathname, "C:\\OBJECTS.TRG");

	sprintf(pathname, "%s\\%s\\%sOBJECTS.TRG", _DEBUGPATH, "CD_ROOT\\DATA",legoGlobs.levelPath);

	handle=PCopen(pathname, 0, 0);

	if (handle!=-1)
	{
		length = PClseek(handle, 0,2);
		PClseek(handle, 0,0);
		count = PCread(handle, (void*)trigger_entities, length);
		PCclose(handle);
	}
	
	placed_object_count = -1;
	for (l = 0 ; l < MAX_TRIGGERS_PER_LEVEL ; l++)
	{
		if ((trigger_entities[l].triggerType == TT_END_OF_LIST) && (placed_object_count == -1))
		{
			placed_object_count = l;
		}
	}
}

// ***********************************************************
void	EDITOR_ChangeTrigger(int item)
{
	if (item == -1)		return;
	trigger_entities[editorGlobs.edit_obj].triggerType+=editorGlobs.tempVal;

	if (trigger_entities[editorGlobs.edit_obj].triggerType >= TT_MAX_TRIGGER_TYPES)	
								trigger_entities[editorGlobs.edit_obj].triggerType = TT_NO_CONDITION;
								
	if (trigger_entities[editorGlobs.edit_obj].triggerType < TT_NO_CONDITION)	
								trigger_entities[editorGlobs.edit_obj].triggerType = TT_MAX_TRIGGER_TYPES-1;
}

// ***********************************************************
void EDITOR_SetStringFromTriggerType(int trigger, char *text)
{
	strcpy(text, "**INVALID TRIGGER**");
	switch (trigger)
 	{
		case		TT_NO_CONDITION						:	strcpy(text, "NO CONDITION");					break;
		case		TT_AT_TIME							:	strcpy(text, "AT TIME");						break;
		case		TT_BLOCK_DUG							:	strcpy(text, "BLOCK DUG");						break;
		case		TT_CREATURE_OF_ID_DESTROYED			:	strcpy(text, "CREATURE ID DESTROYED");		break;
		case		TT_CREATURE_OF_TYPE_DESTROYED		:	strcpy(text, "CREATURE TYPE DESTROYED");		break;
		case		TT_OBJECT_OF_ID_COLLECTED			:	strcpy(text, "OBJECT ID COLLECTED");			break;
		case		TT_OBJECT_OF_TYPE_COLLECTED			:	strcpy(text, "OBJECT TYPE COLLECTED");		break;
		case		TT_MINIFIGURE_ARRIVED					:	strcpy(text, "MINIFIGURE ARRIVED");				break;
		case		TT_CRAFT_ARRIVED						:	strcpy(text, "CRAFT ARRIVED");					break;
		case		TT_CREATURE_ARRIVED					:	strcpy(text, "CREATURE ARRIVED");				break;
	}
}

// ***********************************************************
void EDITOR_DrawWorldLine(LPVECTOR3D from, LPVECTOR3D to, int r, int g, int b)
{
GsLINE	line;
ULONG		attribute=0;							/* default to draw/solid */
SVECTOR	vector;
short		coords[3];
long			depth=14,flag,sort;
GsCOORDINATE2	coord;
MATRIX	mat;

	GsInitCoordinate2(WORLD, &coord);
	GsGetLs(&coord, &mat);
	GsSetLsMatrix(&mat);

	line.attribute = (GsALON | GsAONE);
	
	vector.vx=-from->x;				vector.vy=from->z;				vector.vz=from->y;
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);
	line.x0=(coords[0]);				line.y0=(coords[1]);		
	
	vector.vx=-to->x;					vector.vy=to->z;				vector.vz=to->y;
	gte_RotTransPers(&vector,(long*)&coords[0],&depth,&flag,&sort);
	line.x1=(coords[0]);				line.y1=(coords[1]);	
		
	line.r = r;						line.g = g;						line.b = b;

	GsSortLine(&line,&gfxGlobs.Wot[gfxGlobs.bufID],sort);
}

// ***********************************************************
// ***********************************************************
// ***********************************************************
// ***********************************************************
// ***********************************************************
