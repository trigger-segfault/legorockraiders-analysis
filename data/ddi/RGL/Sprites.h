
#ifndef _RGL_SPRITES_H
#define _RGL_SPRITES_H

#define SPRITE_FLAG_ANIM		0x0001

struct TestSprite {

	struct Texture *texture;//, *mask;
	struct Frame *frame;
	UWORD renderFlags;
	UWORD flags;
};

typedef struct TestSprite		*lpTestSprite;


extern void __cdecl Sprite_Initialise(void);
extern lpTestSprite __cdecl Sprite_Load(LPUCHAR fname, struct Frame *frame, BOOL useShared, BOOL anim);
extern VOID __cdecl Sprite_SetupRender(struct Viewport *vp, struct Frame *camera, REAL delta);
extern ULONG __cdecl Sprite_Render(struct TestSprite *sprite);
extern VOID __cdecl Sprite_Remove(struct TestSprite *sprite);
extern VOID __cdecl Sprite_Shutdown(VOID);

#endif // !_RGL_SPRITES_H
