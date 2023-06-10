
#ifndef _RGL_RENDER_H
#define _RGL_RENDER_H

#include <d3dtypes.h>

#define RENDER_FLAG_RENDERFIRST		0x0001
#define RENDER_FLAG_ALPHAMASK		0x00f0
#define RENDER_FLAG_ADDITIVE		0x0010
#define RENDER_FLAG_SUBTRACTIVE		0x0020
#define RENDER_FLAG_TRANSPARENT		0x0040

enum RenderEntryType {

	RenderEntryType_Mesh,
	RenderEntryType_Sprite,

	RenderEntryType_Count
};

struct RenderEntry {

	enum RenderEntryType type;
	union {
		struct MeshGroup *meshGroup;
		struct TestSprite *sprite;
	};
	union {
		struct Mesh *mesh;
	};
	struct Frame *frame;
};

typedef struct RenderEntry			*lpRenderEntry;

extern VOID __cdecl Render_Initialise(VOID);
extern VOID __cdecl Render_BeginScene(VOID);
extern VOID __cdecl Render_EndScene(VOID);
extern VOID __cdecl Render_ResetTextures(VOID);
extern BOOL __cdecl Render_SetupAlphaStates(unsigned short renderFlags);
extern VOID __cdecl Render_SetTextureStageState(ULONG index, D3DTEXTURESTAGESTATETYPE state, ULONG value);
extern VOID __cdecl Render_SetState(D3DRENDERSTATETYPE type, ULONG value);
extern VOID __cdecl Render_SetTexture(ULONG index, LPDIRECTDRAWSURFACE7 texture);
extern lpRenderEntry __cdecl Render_GetEntry(VOID);
extern VOID __cdecl Render_AddMeshEntry(struct Mesh *mesh, struct MeshGroup *group, struct Frame *frame);
extern VOID __cdecl Render_AddSpriteEntry(struct TestSprite *sprite);
extern struct Texture *__cdecl Render_GetEntryTexture(struct RenderEntry *entry, ULONG index);
extern ULONG __cdecl Render_GetEntryFlags(lpRenderEntry entry);
extern ULONG __cdecl Render_ProcessList(ULONG ambientColour);
extern VOID __cdecl Render_DarkenScreen(ULONG colour);

#endif // !_RGL_RENDER_H
