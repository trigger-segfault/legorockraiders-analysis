
#include "Standard.h"
#include "Errors.h"
#include "Lists.h"
#include "Main.h"
#include "States.h"

#include <windows.h>

struct StateGlobs {

	struct List *list;
	struct State *currState;
	BOOL stateChanged;

	HANDLE currStateInitialiseThread;
	ULONG currStateInitialiseThreadID;
	BOOL currStateThreadRunning;

} stateGlobs;

VOID State_Initialise(VOID) {

	stateGlobs.list = List_Create(sizeof(struct State));
}

VOID State_Shutdown(VOID) {

	Error_Fatal(NULL != stateGlobs.currState, "Unremoved State!!!");
}

VOID State_SetUserData(lpState state, LPVOID data) {

	state->userData = data;
}

LPVOID State_GetUserData(lpState state) {

	return state->userData;
}

lpState State_Create(VOID) {

	lpState state = List_ObtainItem(stateGlobs.list);

	if (NULL == stateGlobs.currState) stateGlobs.currState = state;

	state->delta = 1.0f;

	return state;
}

VOID State_Set_Initialise(lpState state, VOID (*funcInitialise)(lpState thisState), BOOL (*funcInitialiseLoop)(lpState thisState, REAL delta)) {

	Error_Fatal(NULL == funcInitialise, "NULL passed to State_Set_Initialise()");

	state->funcInitialise = funcInitialise;
	state->funcInitialiseLoop = funcInitialiseLoop;
}

VOID State_Set_Loop(lpState state, lpState (*funcLoop)(lpState thisState, REAL delta)) {

	Error_Fatal(NULL == funcLoop, "NULL passed to State_Set_Loop()");
	state->funcLoop = funcLoop;
}

VOID State_Set_Shutdown(lpState state, VOID (*funcShutdown)(lpState thisState)) {

	Error_Fatal(NULL == funcShutdown, "NULL passed to State_Set_Shutdown()");
	Error_Fatal(NULL == state->funcInitialise, "Cannot set a shutdown function without first setting the initialise function");

	state->funcShutdown = funcShutdown;
}

#ifdef _DEBUG
BOOL State_Debug_CheckRemove(lpState state, LPVOID removeState) {

	Error_Fatal(state->returnState == removeState, "Return state is being removed");

	return FALSE;
}
#endif // _DEBUG

static VOID State_Remove(lpState state) {

	if (state->funcShutdown && NULL == state->funcInitialise) {
		state->funcShutdown(state);
	}
	
#ifdef _DEBUG
	List_RunThrough(stateGlobs.list, State_Debug_CheckRemove, state);
#endif // _DEBUG

	List_ReturnItem(stateGlobs.list, state);
}

VOID State_Deflate(lpState state, VOID (*funcInitialise)(lpState thisState)) {

	// Call immediately before returning a different state in the loop to call
	// the state's shutdown function and reinstate the initialisation function.

	state->funcShutdown(state);
	state->funcInitialise = funcInitialise;
}

ULONG WINAPI State_Initialise_ThreadProc(lpState state) {

	state->funcInitialise(state);

	stateGlobs.currStateThreadRunning = FALSE;

	return 0;
}

VOID State_Abort(VOID) {

	if (stateGlobs.currStateThreadRunning) {
		TerminateThread(stateGlobs.currStateInitialiseThread, 0);
		stateGlobs.currStateInitialiseThread = NULL;
	}

}

BOOL State_Loop(REAL delta) {

	if (stateGlobs.currState) {

		lpState newState;

		if (stateGlobs.stateChanged) stateGlobs.stateChanged = FALSE;
		else stateGlobs.currState->delta = delta;

		if (stateGlobs.currState->funcInitialise) {

			if (stateGlobs.currState->funcInitialiseLoop) {

				if (NULL == stateGlobs.currStateInitialiseThread) {

					stateGlobs.currStateInitialiseThread = CreateThread(NULL, 0, State_Initialise_ThreadProc, stateGlobs.currState, 0, &stateGlobs.currStateInitialiseThreadID);
					stateGlobs.currStateThreadRunning = TRUE;

				}

				if (stateGlobs.currState->funcInitialiseLoop(stateGlobs.currState, delta)) {

					if (!stateGlobs.currStateThreadRunning) {

						stateGlobs.currStateInitialiseThread = NULL;
						stateGlobs.currStateInitialiseThreadID = 0;

						stateGlobs.currState->funcInitialise = NULL;
						stateGlobs.currState->funcInitialiseLoop = NULL;

					}

				}

				return TRUE;

			} else {

				stateGlobs.currState->funcInitialise(stateGlobs.currState);
				stateGlobs.currState->funcInitialise = NULL;

			}

		}

		if (newState = stateGlobs.currState->funcLoop(stateGlobs.currState, stateGlobs.currState->delta)) {
			
			if (newState != stateGlobs.currState) {

				newState->returnState = stateGlobs.currState;
				stateGlobs.currState = newState;
				
				stateGlobs.stateChanged = TRUE;
			}

		} else {

			newState = stateGlobs.currState->returnState;
			State_Remove(stateGlobs.currState);
			stateGlobs.currState = newState;

			stateGlobs.stateChanged = TRUE;
		}
	}

	return (NULL != stateGlobs.currState);
}
