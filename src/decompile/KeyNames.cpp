// KeyNames.cpp : Defines a table of names mapped to DirectInput key codes.
//
/// STATUS: [COMPLETE]

#include "KeyNames.h"


using namespace lego;
using namespace lego::input;


#pragma region Globals

// <LegoRR.exe @005775e0>
const char* lego::globals::g_KEYS_TABLE[256];

#pragma endregion


#pragma region Functions

// <LegoRR.exe @00485ce0>
void __cdecl lego::input::InitKeyNames(void)
{
	std::memset(globals::g_KEYS_TABLE, 0, sizeof(globals::g_KEYS_TABLE) /*0x400*/);

	// (skip 0)
	globals::g_KEYS_TABLE[1] = "KEY_ESCAPE";
	globals::g_KEYS_TABLE[2] = "KEY_ONE";
	globals::g_KEYS_TABLE[3] = "KEY_TWO";
	globals::g_KEYS_TABLE[4] = "KEY_THREE";
	globals::g_KEYS_TABLE[5] = "KEY_FOUR";
	globals::g_KEYS_TABLE[6] = "KEY_FIVE";
	globals::g_KEYS_TABLE[7] = "KEY_SIX";
	globals::g_KEYS_TABLE[8] = "KEY_SEVEN";
	globals::g_KEYS_TABLE[9] = "KEY_EIGHT";
	globals::g_KEYS_TABLE[10] = "KEY_NINE";
	globals::g_KEYS_TABLE[11] = "KEY_ZERO";
	globals::g_KEYS_TABLE[12] = "KEY_MINUS";
	globals::g_KEYS_TABLE[13] = "KEY_EQUALS";
	globals::g_KEYS_TABLE[14] = "KEY_BACKSPACE";
	globals::g_KEYS_TABLE[15] = "KEY_TAB";
	globals::g_KEYS_TABLE[16] = "KEY_Q";
	globals::g_KEYS_TABLE[17] = "KEY_W";
	globals::g_KEYS_TABLE[18] = "KEY_E";
	globals::g_KEYS_TABLE[19] = "KEY_R";
	globals::g_KEYS_TABLE[20] = "KEY_T";
	globals::g_KEYS_TABLE[21] = "KEY_Y";
	globals::g_KEYS_TABLE[22] = "KEY_U";
	globals::g_KEYS_TABLE[23] = "KEY_I";
	globals::g_KEYS_TABLE[24] = "KEY_O";
	globals::g_KEYS_TABLE[25] = "KEY_P";
	globals::g_KEYS_TABLE[26] = "KEY_LEFTBRACE";
	globals::g_KEYS_TABLE[27] = "KEY_RIGHTBRACE";
	globals::g_KEYS_TABLE[28] = "KEY_RETURN";
	globals::g_KEYS_TABLE[29] = "KEY_LEFTCTRL";
	globals::g_KEYS_TABLE[30] = "KEY_A";
	globals::g_KEYS_TABLE[31] = "KEY_S";
	globals::g_KEYS_TABLE[32] = "KEY_D";
	globals::g_KEYS_TABLE[33] = "KEY_F";
	globals::g_KEYS_TABLE[34] = "KEY_G";
	globals::g_KEYS_TABLE[35] = "KEY_H";
	globals::g_KEYS_TABLE[36] = "KEY_J";
	globals::g_KEYS_TABLE[37] = "KEY_K";
	globals::g_KEYS_TABLE[38] = "KEY_L";
	globals::g_KEYS_TABLE[39] = "KEY_SEMICOLON";
	globals::g_KEYS_TABLE[40] = "KEY_AT";
	globals::g_KEYS_TABLE[41] = "KEY_RSINGLEQUOTE";
	globals::g_KEYS_TABLE[42] = "KEY_LEFTSHIFT";
	globals::g_KEYS_TABLE[43] = "KEY_HASH";
	globals::g_KEYS_TABLE[44] = "KEY_Z";
	globals::g_KEYS_TABLE[45] = "KEY_X";
	globals::g_KEYS_TABLE[46] = "KEY_C";
	globals::g_KEYS_TABLE[47] = "KEY_V";
	globals::g_KEYS_TABLE[48] = "KEY_B";
	globals::g_KEYS_TABLE[49] = "KEY_N";
	globals::g_KEYS_TABLE[50] = "KEY_M";
	globals::g_KEYS_TABLE[51] = "KEY_LEFTARROW";
	globals::g_KEYS_TABLE[52] = "KEY_RIGHTARROW";
	globals::g_KEYS_TABLE[53] = "KEY_QUESTIONMARK";
	globals::g_KEYS_TABLE[54] = "KEY_RIGHTSHIFT";
	globals::g_KEYS_TABLE[55] = "KEYPAD_ASTERISK";
	globals::g_KEYS_TABLE[56] = "KEY_ALT";
	globals::g_KEYS_TABLE[57] = "KEY_SPACE";
	globals::g_KEYS_TABLE[58] = "KEY_CAPLOCK";
	globals::g_KEYS_TABLE[59] = "KEY_F1";
	globals::g_KEYS_TABLE[60] = "KEY_F2";
	globals::g_KEYS_TABLE[61] = "KEY_F3";
	globals::g_KEYS_TABLE[62] = "KEY_F4";
	globals::g_KEYS_TABLE[63] = "KEY_F5";
	globals::g_KEYS_TABLE[64] = "KEY_F6";
	globals::g_KEYS_TABLE[65] = "KEY_F7";
	globals::g_KEYS_TABLE[66] = "KEY_F8";
	globals::g_KEYS_TABLE[67] = "KEY_F9";
	globals::g_KEYS_TABLE[68] = "KEY_F10";
	globals::g_KEYS_TABLE[69] = "KEYPAD_NUMLOCK";
	globals::g_KEYS_TABLE[70] = "KEY_SCROLLLOCK";
	globals::g_KEYS_TABLE[71] = "KEYPAD_7";
	globals::g_KEYS_TABLE[72] = "KEYPAD_8";
	globals::g_KEYS_TABLE[73] = "KEYPAD_9";
	globals::g_KEYS_TABLE[74] = "KEYPAD_MINUS";
	globals::g_KEYS_TABLE[75] = "KEYPAD_4";
	globals::g_KEYS_TABLE[76] = "KEYPAD_5";
	globals::g_KEYS_TABLE[77] = "KEYPAD_6";
	globals::g_KEYS_TABLE[78] = "KEYPAD_PLUS";
	globals::g_KEYS_TABLE[79] = "KEYPAD_1";
	globals::g_KEYS_TABLE[80] = "KEYPAD_2";
	globals::g_KEYS_TABLE[81] = "KEYPAD_3";
	globals::g_KEYS_TABLE[82] = "KEYPAD_0";
	globals::g_KEYS_TABLE[83] = "KEYPAD_DELETE";
	// (gap)
	globals::g_KEYS_TABLE[86] = "KEY_BACKSLASH";
	globals::g_KEYS_TABLE[87] = "KEY_F11";
	globals::g_KEYS_TABLE[88] = "KEY_F12";
	// (gap)
	globals::g_KEYS_TABLE[156] = "KEYPAD_ENTER";
	globals::g_KEYS_TABLE[157] = "KEY_RIGHTCTRL";
	// (gap)
	globals::g_KEYS_TABLE[181] = "KEYPAD_FORWARDSLASH";
	// (gap)
	globals::g_KEYS_TABLE[183] = "KEY_PRINTSCREEN";
	globals::g_KEYS_TABLE[184] = "KEY_ALTGR";
	// (gap)
	globals::g_KEYS_TABLE[199] = "KEY_HOME";
	globals::g_KEYS_TABLE[200] = "KEY_CURSORUP";
	globals::g_KEYS_TABLE[201] = "KEY_PGUP";
	// (gap)
	globals::g_KEYS_TABLE[203] = "KEY_CURSORLEFT";
	// (gap)
	globals::g_KEYS_TABLE[205] = "KEY_CURSORRIGHT";
	// (gap)
	globals::g_KEYS_TABLE[207] = "KEY_END";
	globals::g_KEYS_TABLE[208] = "KEY_CURSORDOWN";
	globals::g_KEYS_TABLE[209] = "KEY_PGDN";
	globals::g_KEYS_TABLE[210] = "KEY_INSERT";
	globals::g_KEYS_TABLE[211] = "KEY_DELETE";
	// (skip remaining)
}

// Does not assign `out_keyCode` on failure!
// <LegoRR.exe @004860f0>
BOOL __cdecl lego::input::Key_Parse(const char* keyName, Keys* out_keyCode)
{
	for (int i = 0; i < _countof(globals::g_KEYS_TABLE); i++) {

		if (::_stricmp(globals::g_KEYS_TABLE[i], keyName) == 0) {
			*out_keyCode = (Keys)i;
			return true;
		}
	}
	return false;
}

#pragma endregion
