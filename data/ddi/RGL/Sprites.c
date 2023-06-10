
#include "Standard.h"
#include "Viewports.h"
#include "Render.h"
#include "Errors.h"
#include "Frames.h"
#include "Files.h"
#include "Lists.h"
#include "Draw.h"

#include "Sprites.h"

// Test implementation...

struct SpriteGlobs {

	lpList list;
	lpViewport vp;
	lpFrame camera;
	REAL time;

} spriteGlobs = { 0 };

VOID Sprite_Initialise(VOID) {

	spriteGlobs.list = List_Create(sizeof(struct TestSprite));
}

BOOL Sprite_ShutdownCallback(lpTestSprite sprite, LPVOID data) {

	Error_Fatal(TRUE, "Unremoved sprite");

#pragma message ( "Remove this..." )
	Sprite_Remove(sprite);

	return FALSE;
}

VOID Sprite_Shutdown(VOID) {

#ifdef _DEBUG
	List_RunThrough(spriteGlobs.list, Sprite_ShutdownCallback, NULL);
#endif // _DEBUG
	List_Remove(spriteGlobs.list);
	spriteGlobs.list = NULL;
}

lpTestSprite Sprite_Load(LPUCHAR fname, lpFrame frame, BOOL useShared, BOOL anim) {

	lpTestSprite sprite = NULL;
	lpTexture texture;
//	UCHAR maskName[FILE_MAXPATH];

	if (texture = Texture_Load(fname, useShared)) {
	
		sprite = List_ObtainItem(spriteGlobs.list);
		sprite->texture = texture;
		sprite->frame = frame;
		if (anim) sprite->flags |= SPRITE_FLAG_ANIM;

//		sprintf(maskName, "%s", fname);
//		if (File_GetSuffix(maskName)) File_GetSuffix(maskName)[-1] = '\0';
//		strcat(maskName, "_mask");
//		if (File_GetSuffix(maskName)) {
//			strcat(maskName, ".");
//			strcat(maskName, File_GetSuffix(fname));
//		}

//		sprite->mask = Texture_Load(maskName, useShared);
	}

	return sprite;
}

VOID Sprite_Remove(lpTestSprite sprite) {

	if (sprite->texture) Texture_Remove(sprite->texture);
	List_ReturnItem(spriteGlobs.list, sprite);
}

ULONG Sprite_Render(lpTestSprite sprite) {

	struct DrawPrimitiveCoord coord;
	VECTOR2D uvList[4];
	ULONG frame = (ULONG) (spriteGlobs.time);

	Frame_GetWorldPosition(sprite->frame, &coord.coord.position);
	coord.coord.colour = COLOUR_FROMCHAR(255, 255, 255);
	coord.size = 10.0f;
	coord.angle = 0.0f;

	if (sprite->flags & SPRITE_FLAG_ANIM) {
	
		frame %= 10;

		uvList[0].x = 0.25f * (frame % 4);
		uvList[0].y = 0.25f * (frame / 4);
		uvList[1].x = 0.25f * ((frame % 4) + 1);
		uvList[1].y = 0.25f * (frame / 4);
		uvList[2].x = 0.25f * ((frame % 4) + 1);
		uvList[2].y = 0.25f * ((frame / 4) + 1);
		uvList[3].x = 0.25f * (frame % 4);
		uvList[3].y = 0.25f * ((frame / 4) + 1);

		Draw_WorldPrimitiveListUV(spriteGlobs.vp, spriteGlobs.camera, &coord, 1, sprite->texture, uvList, DRAW_FLAG_COLOURKEYED);

	} else {

		Draw_WorldPrimitiveList(spriteGlobs.vp, spriteGlobs.camera, &coord, 1, sprite->texture, DRAW_FLAG_COLOURKEYED);

	}

	return 1;
}

BOOL Sprite_SetupRenderCallback(lpTestSprite sprite, LPVOID data) {

	Render_AddSpriteEntry(sprite);

	return FALSE;
}

VOID Sprite_SetupRender(lpViewport vp, lpFrame camera, REAL delta) {

	spriteGlobs.vp = vp;
	spriteGlobs.camera = camera;
	spriteGlobs.time += delta;

	List_RunThrough(spriteGlobs.list, Sprite_SetupRenderCallback, NULL);
}
