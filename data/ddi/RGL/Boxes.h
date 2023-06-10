
#ifndef _RGL_BOXES_H_
#define _RGL_BOXES_H_

enum BoxSide {

	BoxSide_Left,
	BoxSide_Right,
	BoxSide_Bottom,
	BoxSide_Top,
	BoxSide_Front,
	BoxSide_Back,

	BoxSide_Count
};

#ifndef _AUTOPROTOTYPES
// Auto Prototypes
extern unsigned __int64 __stdcall Int64ShllMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern __int64 __stdcall Int64ShraMod32(__int64 Value,unsigned long ShiftCount);
extern unsigned __int64 __stdcall Int64ShrlMod32(unsigned __int64 Value,unsigned long ShiftCount);
extern void *__cdecl GetFiberData(void );
extern void *__cdecl GetCurrentFiber(void );
extern int __cdecl Box_LineIntersection(struct BOX3D *box,struct VECTOR3D *start,struct VECTOR3D *end);
extern int __cdecl Box_LineIntersectionEx(struct BOX3D *box,struct VECTOR3D *start,struct VECTOR3D *end,struct VECTOR3D *hit, LPREAL delta, enum BoxSide *side);
extern int __cdecl Box_ThroughSideX(float planeX,struct VECTOR3D *a,struct VECTOR3D *b,float *yHit,float *zHit);
extern int __cdecl Box_ThroughSideY(float planeY,struct VECTOR3D *a,struct VECTOR3D *b,float *xHit,float *zHit);
extern int __cdecl Box_ThroughSideZ(float planeZ,struct VECTOR3D *a,struct VECTOR3D *b,float *xHit,float *yHit);
extern int __cdecl Box_PointInside(struct BOX3D *box,struct VECTOR3D *point);
extern int __cdecl Box_IntersectionImpossible(struct BOX3D *aBox,struct BOX3D *bBox);
extern void __cdecl Box_SetupVisibiltyCheck(struct Viewport *vp,struct Frame *refFrame,struct Frame *camera);
extern int __cdecl Box_CornerVisibile(struct BOX3D *box);
extern VOID __cdecl Box_Scale(LPBOX3D box, LPVECTOR3D scale);
extern VOID __cdecl Box_GetCenter(LPBOX3D box, LPVECTOR3D center);
extern VOID __cdecl Box_Get(LPBOX3D box, LPVECTOR3D pointList, ULONG pointCount);
extern VOID __cdecl Box_BuildVectorList(LPBOX3D box, VECTOR3D vectorList[8]);
extern void __cdecl Box_Draw(LPBOX3D box, struct Viewport *vp, struct Frame *frame, struct Frame *camera, COLOUR colour);
extern VOID __cdecl Box_FromString(LPBOX3D box, LPUCHAR minString, LPUCHAR maxString);
// Auto Prototypes
#endif // !_AUTOPROTOTYPES

#endif // !_RGL_BOXES_H_
