//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Viewport.c - [Viewport Code]
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ


#define VIEWPORT_FLAG_INITIALISED	0x00000001

typedef struct Viewport
{
	REAL			xoffset, yoffset;			// Position on viewport normalised to between 0.0 and 1.0
	REAL			width, height;				// Width and height of the viewport normalised as above

	POLY_F4		test[2];

	DR_AREA		clip_prim[2];					// clipping change primitive (double buffered)
	DR_OFFSET	offset_prim[2];				// offset change primitive (double buffered)
	REAL			scale;							// camera scaling factor
	//REAL			clipBack, clipFront;
	//REAL			smoothFOV;
	lpContainer	camera_container;
	ULONG			identifier;					/* which order table to reference */

} Viewport, *lpViewport;

typedef struct Viewport_Globs
{
	Viewport *viewport_list[MAX_VIEWPORTS];

	ULONG 		flags;
	ULONG			models_drawn;
	ULONG			models_clipped;

	ULONG			sprites_drawn;
	ULONG			sprites_clipped;

	ULONG			next_identifier;
	lpViewport	current_viewport;

} Viewport_Globs, *lpViewport_Globs;

typedef struct Viewport_PickInfo {

	lpContainer		pickCont;
	ULONG				group, face;
	VECTOR3D			position;

} Viewport_PickInfo, *lpViewport_PickInfo;

typedef struct Viewport_Pick {

	lpViewport_PickInfo	pickArray;
	ULONG						pickCount;

} Viewport_Pick, *lpViewport_Pick;

#define	Viewport_SetBackClip(_v_,_c_)		(_v_)->clipBack=(_c_)
#define	Viewport_SetFrontClip(_v_,_c_)	(_v_)->clipFront=(_c_)

void				Viewport_Initialise(void);
lpViewport		Viewport_Create(REAL xPos, REAL yPos, REAL width, REAL height, lpContainer camera);
lpViewport		Viewport_CreatePixel(SLONG xPos, SLONG yPos, ULONG width, ULONG height, lpContainer camera);
VOID				Viewport_AddList(VOID);
BOOL				Viewport_PickFind(lpViewport_Pick pick, lpContainer findCont, LPULONG group, LPULONG face, LPVECTOR3D position);
lpContainer	Viewport_PickSearch(lpViewport_Pick pick, BOOL (*SearchCallback)(lpContainer match, ULONG group, ULONG face, LPVECTOR3D position, LPVOID data), LPVOID data);
VOID				Viewport_InverseTransform(lpViewport vp, LPVECTOR3D dest, LPVECTOR4D src);
VOID				Viewport_Transform(lpViewport vp, LPVECTOR4D dest, LPVECTOR3D src);
LPVECTOR2D 	Viewport_WorldToScreen(lpViewport vp, LPVECTOR2D screen, LPVECTOR3D world);

VOID				Viewport_Clear(lpViewport vp);
VOID				Viewport_Render(lpViewport vp, lpContainer root, REAL delta);
BOOL				Viewport_RenderFrame(lpViewport vp, lpContainer frame);
BOOL				Viewport_RenderObject(lpViewport vp, lpContainer cont);


/* added by SteveD */

BOOL	Viewport_SetActive(lpViewport vp);

void	Viewport_RenderStaticHMD(lpContainer cont, int x, int y, int z, int rx, int ry, int rz);

