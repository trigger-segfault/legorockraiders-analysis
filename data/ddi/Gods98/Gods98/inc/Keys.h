
#ifndef _GODS98_KEYS_H_
#define _GODS98_KEYS_H_

#include "Standard.h"

/**********************************************************************************
******	keys header file													******
***********************************************************************************/

#define		KEY_ESCAPE			0x001
#define		KEY_ONE				0x002	// 1
#define		KEY_TWO				0x003	// 2
#define		KEY_THREE			0x004	// 3
#define		KEY_FOUR			0x005	// 4
#define		KEY_FIVE			0x006	// 5
#define		KEY_SIX				0x007	// 6
#define		KEY_SEVEN			0x008	// 7
#define		KEY_EIGHT			0x009	// 8
#define		KEY_NINE			0x00A	// 9
#define		KEY_ZERO			0x00B	// 0
#define		KEY_MINUS			0x00C	// -
#define		KEY_EQUALS			0x00D	// +
#define		KEY_BACKSPACE		0x00E
#define		KEY_TAB				0x00F
#define		KEY_Q				0x010	// Q
#define		KEY_W				0x011	// W
#define		KEY_E				0x012	// E
#define		KEY_R				0x013	// R
#define		KEY_T				0x014	// T
#define		KEY_Y				0x015	// Y
#define		KEY_U				0x016	// U
#define		KEY_I				0x017	// I
#define		KEY_O				0x018	// O
#define		KEY_P				0x019	// P
#define		KEY_LEFTBRACE		0x01A	// [
#define		KEY_RIGHTBRACE		0x01B	// ]
#define		KEY_RETURN			0x01C
#define		KEY_LEFTCTRL		0x01D
#define		KEY_A				0x01E	// A
#define		KEY_S				0x01F	// S
#define		KEY_D				0x020	// D
#define		KEY_F				0x021	// F
#define		KEY_G				0x022	// G
#define		KEY_H				0x023	// H
#define		KEY_J				0x024	// J
#define		KEY_K				0x025	// K
#define		KEY_L				0x026	// L
#define		KEY_SEMICOLON		0x027	// // 
#define		KEY_AT				0x028	// @
#define		KEY_RSINGLEQUOTE	0x029	// `
#define		KEY_LEFTSHIFT		0x02A
#define		KEY_HASH			0x02B	// #
#define		KEY_Z				0x02C	// Z
#define		KEY_X				0x02D	// X
#define		KEY_C				0x02E	// C
#define		KEY_V				0x02F	// V
#define		KEY_B				0x030	// B
#define		KEY_N				0x031	// N
#define		KEY_M				0x032	// M
#define		KEY_LEFTARROW		0x033	// <
#define		KEY_RIGHTARROW		0x034	// >
#define		KEY_QUESTIONMARK	0x035	// ?
#define		KEY_RIGHTSHIFT		0x036
#define		KEYPAD_ASTERISK		0x037	// *
#define		KEY_ALT				0x038
#define		KEY_SPACE			0x039	// 
#define		KEY_CAPLOCK			0x03A
#define		KEY_F1				0x03B
#define		KEY_F2				0x03C
#define		KEY_F3				0x03D
#define		KEY_F4				0x03E
#define		KEY_F5				0x03F
#define		KEY_F6				0x040
#define		KEY_F7				0x041
#define		KEY_F8				0x042
#define		KEY_F9				0x043
#define		KEY_F10				0x044
#define		KEYPAD_NUMLOCK		0x045
#define		KEY_SCROLLLOCK		0x046
#define		KEYPAD_7			0x047	// 7
#define		KEYPAD_8			0x048	// 8
#define		KEYPAD_9			0x049	// 9
#define		KEYPAD_MINUS		0x04A	// -
#define		KEYPAD_4			0x04B	// 4
#define		KEYPAD_5			0x04C	// 5
#define		KEYPAD_6			0x04D	// 6
#define		KEYPAD_PLUS			0x04E	// +
#define		KEYPAD_1			0x04F	// 1
#define		KEYPAD_2			0x050	// 2
#define		KEYPAD_3			0x051	// 3
#define		KEYPAD_0			0x052	// 0
#define		KEYPAD_DELETE		0x053
#define		KEY_BACKSLASH		0x056
#define		KEY_F11				0x057
#define		KEY_F12				0x058

#define		KEYPAD_ENTER		0x09C
#define		KEY_RIGHTCTRL		0x09D
#define		KEYPAD_FORWARDSLASH	0x0B5
#define		KEY_PRINTSCREEN		0x0B7
#define		KEY_ALTGR			0x0B8
#define		KEY_HOME			0x0C7
#define		KEY_CURSORUP		0x0C8
#define		KEY_PGUP			0x0C9
#define		KEY_CURSORLEFT		0x0CB
#define		KEY_CURSORRIGHT		0x0CD
#define		KEY_END				0x0CF
#define		KEY_CURSORDOWN		0x0D0
#define		KEY_PGDN			0x0D1
#define		KEY_INSERT			0x0D2
#define		KEY_DELETE			0x0D3

#define Key_RegisterName(k)		(keyGlobs.keyName[k]=#k)

typedef struct Key_Globs {

	LPUCHAR keyName[256];

} Key_Globs, *lpKey_Globs;

#ifndef _GENPROTFILE
#include "..\Src\Keys.prot"
#endif // !_GENPROTFILE

#endif // _GODS98_KEYS_H_
