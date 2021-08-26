//ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß
// Asmcode.s - [Misc. Assembly Code]
//ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ

//#define Asm_MulFIX(a,b)	((long)(((long)a*(long)b)>>12))
//#define Asm_DivFIX(a,b)	((long)(((long)a<<12)/(long)b))

void		ScreenOn(void);
void		ScreenOff(void);
void		SetScreen(Uint16 mode);

FIXED	Asm_MulFIX(FIXED, FIXED);
FIXED	Asm_DivFIX(FIXED, FIXED);
void		Asm_ResetPsx(void);
Uint32	Asm_GetMemAvailable(Uint32, Uint32);
LPVOID	Asm_GetMemStart(Uint32);
void		Asm_Rts(void);
Uint32	Asm_SortPrim(LPULONG, GsOT*, Uint32);
Uint32	Asm_Random(void);
Uint32	Asm_SetSeed(Uint32);
Uint32	Asm_GetSeed(void);













									  	
