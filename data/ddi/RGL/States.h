
#ifndef _RGL_STATES_H
#define _RGL_STATES_H

#ifdef _RGL

struct State {

	REAL delta;

	BOOL (*funcInitialiseLoop)(struct State *thisState, REAL delta);
	VOID (*funcInitialise)(struct State *thisState);
	struct State *(*funcLoop)(struct State *thisState, REAL delta);
	VOID (*funcShutdown)(struct State *thisState);

	struct State *returnState;

	LPVOID userData;
};

#endif // _RGL

typedef struct State				*lpState;

extern VOID __cdecl State_SetUserData(lpState state, LPVOID data);
extern LPVOID __cdecl State_GetUserData(lpState state);
extern VOID __cdecl State_Initialise(VOID);
extern VOID __cdecl State_Shutdown(VOID);
extern lpState __cdecl State_Create(VOID);
extern VOID __cdecl State_Set_Initialise(lpState state, VOID (*funcInitialise)(struct State *thisState), BOOL (*funcInitialiseLoop)(struct State *thisState, REAL delta));
extern VOID __cdecl State_Deflate(lpState state, VOID (*funcInitialise)(struct State *thisState));
extern VOID __cdecl State_Set_Loop(lpState state, struct State *(*funcLoop)(struct State *thisState, REAL delta));
extern VOID __cdecl State_Set_Shutdown(lpState state, VOID (*funcShutdown)(struct State *thisState));
extern BOOL __cdecl State_Loop(REAL delta);
extern VOID __cdecl State_Abort(VOID);


#endif // _RGL_STATES_H
