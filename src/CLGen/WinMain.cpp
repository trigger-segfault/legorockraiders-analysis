// WinMain.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WinMain.h"
#include "Common.h"
#include "Registry.h"


namespace lego {

    // CLGen mode for combobox
    struct CLGenMode
    {
        /*0,4*/ const char* displayName;  // display name
        /*4,4*/ const char* options;      // command-line options
        /*8*/
    };

    // Global Variables:
    namespace globals {

        // Allocated buffer containing "CLGen.dat" file data (+1 byte for null-terminator)
        //  (never freed by the program :P)
        //  (although this data *is* used by most of the global variables below)
        // <CLGen.exe @0040aa30>
        static char* g_CLGenDat_Buffer = NULL;
        // file size of "CLGen.dat" excluding null-terminator
        // <CLGen.exe @0040aa34>
        static unsigned int g_CLGenDat_FileSize = 0;
        // Title property for the dialog
        // <CLGen.exe @0040aa38>
        static const char* g_CLGen_Title = NULL;
        // Label property for the dialog to show above the combobox
        // <CLGen.exe @0040aa3c>
        static const char* g_CLGen_Instruction = NULL;
        // Registry key to write selected mode options to
        // <CLGen.exe @0040aa40>
        static const char* g_CLGen_WriteKey = NULL;
        // Table of CLGenMode items to show in dialog combobox
        // <CLGen.exe @0040aa44>
        static CLGenMode* g_Modes_TABLE = NULL;
        // Total number of CLGenMode items
        // <CLGen.exe @0040aa48>
        static unsigned int g_Modes_COUNT = 0;
        // Current capacity of CLGenMode items table (>= COUNT)
        // <CLGen.exe @0040aa4c>
        static unsigned int g_Modes_CAPACITY = 0;
        // Currently selected CLGenMode, used when accept is pressed
        //  (-1 == unselected, which is interestingly not the default)
        // <CLGen.exe @0040aa50>
        static int g_Modes_CURSEL = 0;

    } /* namespace globals */

    // WinMain entrypoint
    // <CLGen.exe @00401000>
    //int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);

    // CLGen-specific parsing and execution behavior
    namespace CLGen {

        // Open "CLGen.dat" file and parse commands
        // <CLGen.exe @004010b0>
        static BOOL __cdecl Open(const char* filename);
        // Parse a single "CLGen.dat" line command
        // <CLGen.exe @00401220>
        static const char* __cdecl ParseCommand(int numParts, char** parts);
        // Apply changes to Registry key using the passed mode's options
        // <CLGen.exe @00401320>
        static void __cdecl ApplyRegistryChanges(const CLGenMode* mode);
        // Add a CLGen mode name and associated options to table
        // <CLGen.exe @00401380>
        static CLGenMode* __cdecl AddModeItem(const char* modeName, const char* options);

    } /* namespace CLGen */

    // Dialog-specific handling for CLGen
    namespace Selector {

        // <CLGen.exe @004014b0>
        static INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
        // <CLGen.exe @00401520>
        static BOOL __cdecl HandleMessage_InitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam);
        // <CLGen.exe @004015c0>
        static BOOL __cdecl HandleMessage_Command(HWND hDlg, WPARAM wParam, LPARAM lParam);
        // <CLGen.exe @00401600>
        static BOOL __cdecl HandleMessage_MenuCommand(HWND hDlg, WPARAM wParam);
        // <CLGen.exe @00401630>
        static BOOL __cdecl HandleMessage_AcceleratorCommand(HWND hDlg, WORD sourceId, HWND hCtrl);

    } /* namespace Selector */

} /* namespace lego */


#define CLGEN_DATA_FILENAME     "CLGen.dat"


#define CMD_TITLE               "TITLE"
#define USAGE_TITLE             "Usage " CMD_TITLE "|<Window title text>"

#define CMD_INSTRUCTION         "INSTRUCTION"
#define USAGE_INSTRUCTION       "Usage " CMD_INSTRUCTION "|<Instruction message text>"
#define CMD_ADDITEM             "ADDITEM"
#define USAGE_ADDITEM           "Usage " CMD_ADDITEM "|<Mode Name>|<Options>"
#define CMD_ACTION              "ACTION"
#define ACTION_WRITEKEY         "WRITEKEY"
#define USAGE_ACTION_WRITEKEY   "Usage " CMD_ACTION  "|" ACTION_WRITEKEY  "|<registry key>"
#define MSG_UNKNOWN_ACTION      "Unknown action"


using namespace lego;


#pragma region CLGen Behavior

// <CLGen.exe @004010b0>
BOOL __cdecl lego::CLGen::Open(const char* filename)
{
    char* stringParts[128];
    char errorMessage[1024];

    FILE* file = std::fopen(filename, "rb");
    if (file != NULL) {
        // Determine file size, and read all data into buffer
        std::fseek(file, 0, SEEK_END /*2*/);
        globals::g_CLGenDat_FileSize = std::ftell(file);
        std::fseek(file, 0, SEEK_SET /*0*/);
        // This is never free'd, yey~
        globals::g_CLGenDat_Buffer = (char*)std::malloc(globals::g_CLGenDat_FileSize + 1); // +1 for null-terminator
        std::fread(globals::g_CLGenDat_Buffer, 1, globals::g_CLGenDat_FileSize, file);
        std::fclose(file);

        // tokenize file by lines
        for (unsigned int i = 0; i < globals::g_CLGenDat_FileSize; i++) {
            if (globals::g_CLGenDat_Buffer[i] == '\r' || globals::g_CLGenDat_Buffer[i] == '\n') {
                globals::g_CLGenDat_Buffer[i] = '\0';
            }
        }
        globals::g_CLGenDat_Buffer[globals::g_CLGenDat_FileSize] = '\0'; // null-terminate end of buffer

        // read commands by line
        bool isEOL = true; // EOL signifies we can start reading the next command
        char* lineStart = NULL; // not actually assigned, but will always be assigned by first usage
        for (unsigned int i = 0; i < globals::g_CLGenDat_FileSize; i++) {
            if (isEOL) {
                if (globals::g_CLGenDat_Buffer[i] != '\0') {
                    // set start of next line
                    isEOL = false;
                    lineStart = globals::g_CLGenDat_Buffer + i;
                }
            }
            else if (globals::g_CLGenDat_Buffer[i] == '\0') {
                // end of current line found, now parse the command
                int numParts = util::stringSplit(lineStart, stringParts, "|");
                const char* message = CLGen::ParseCommand(numParts, stringParts);
                if (message != NULL) {
                    std::sprintf(errorMessage, "Error in \"%s\":\n%s", filename, message);
                    MessageBoxA(NULL, errorMessage, "Error", MB_OK /*0*/);
                }
                isEOL = true;
            }
        }

        return true;
    }
    return false;
}

// <CLGen.exe @00401220>
const char* __cdecl lego::CLGen::ParseCommand(int numParts, char** parts)
{
    if (_stricmp(parts[0], "TITLE") == 0) {
        if (numParts == 2) {
            globals::g_CLGen_Title = parts[1];
            return NULL;
        }
        return "Usage TITLE|<Window title text>";
    }
    else if (_stricmp(parts[0], "INSTRUCTION") == 0) {
        if (numParts == 2) {
            globals::g_CLGen_Instruction = parts[1];
            return NULL;
        }
        return "Usage INSTRUCTION|<Instruction message text>";
    }
    else if (_stricmp(parts[0], "ADDITEM") == 0) {
        if (numParts == 3) {
            CLGen::AddModeItem(parts[1], parts[2]);
            return NULL;
        }
        return "Usage ADDITEM|<Mode Name>|<Options>";
    }
    else if (_stricmp(parts[0], "ACTION") == 0) {
        if (_stricmp(parts[1], "WRITEKEY") == 0) {
            if (numParts == 3) {
                globals::g_CLGen_WriteKey = parts[2];
                return NULL;
            }
            return "Usage ACTION|WRITEKEY|<registry key>";
        }
        return "Unknown action";
    }
    else {
        return parts[0];
    }
}

// <CLGen.exe @00401320>
CLGenMode* __cdecl lego::CLGen::AddModeItem(const char* modeName, const char* options)
{
    if (globals::g_Modes_COUNT == globals::g_Modes_CAPACITY) {
        // Allocate more space for table
        globals::g_Modes_CAPACITY += 10;
        // `realloc` behaves as `malloc` for the first call, since g_Modes_TABLE is NULL
        globals::g_Modes_TABLE = (CLGenMode*)std::realloc(globals::g_Modes_TABLE, globals::g_Modes_CAPACITY * sizeof(CLGenMode) /*0x8*/);
    }

    CLGenMode* mode = &globals::g_Modes_TABLE[globals::g_Modes_COUNT++];
    mode->displayName = modeName;
    mode->options = options;
    return mode;
}

// <CLGen.exe @00401380>
void __cdecl lego::CLGen::ApplyRegistryChanges(const CLGenMode* mode)
{
    char buffer[1024];

    if (globals::g_CLGen_WriteKey != NULL) {
        // Split "HKEY_LOCAL_MACHINE", subkey, and value name
        char* valueName = NULL;
        char* regSubKey = NULL; // dummy init to stop compiler from complaining
        std::sprintf(buffer, "%s", globals::g_CLGen_WriteKey);
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (buffer[i] == '\\') {
                if (valueName == NULL) {
                    buffer[i] = '\0';
                    regSubKey = &buffer[i] + 1;
                }
                valueName = &buffer[i] + 1;
            }
            //buffer[0] = buffer[i + 1]; // why...??? oh... Ghidra just being really dump :P
        }

        // No null checks, don't fuck this up
        valueName[-1] = '\0'; // split subkey from value name

        if (_stricmp(buffer, "HKEY_LOCAL_MACHINE") == 0) {
            registry::SetValue_OnLocalMachine(regSubKey, valueName, registry::REGISTRY_STRING, mode->options, std::strlen(mode->options));
        }
        else {
            MessageBoxA(NULL, "Can only write to HKEY_LOCAL_MACHINE", "Error", MB_OK /*0*/);
        }
    }
}

#pragma endregion


#pragma region Selector Dialog

// WINDOWS MESSAGES:
//
//  WM_CLOSE        - close the application without applying changes
//  WM_INITDIALOG   - set the label text and populate the combobox
//  WM_COMMAND      - update currently selected mode and handle OK/Cancel buttons
//
// <CLGen.exe @004014b0>
INT_PTR CALLBACK lego::Selector::DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CLOSE /*0x10*/:
        EndDialog(hDlg, IDCANCEL /*2*/);
        return (INT_PTR)TRUE;
    case WM_INITDIALOG /*0x110*/:
        return (INT_PTR)HandleMessage_InitDialog(hDlg, wParam, lParam);
    case WM_COMMAND /*0x111*/:
        return (INT_PTR)HandleMessage_Command(hDlg, wParam, lParam);

    default:
        return (INT_PTR)FALSE;
    }
}

// <CLGen.exe @00401520>
BOOL __cdecl lego::Selector::HandleMessage_InitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
    HWND hCtrlCombobox = GetDlgItem(hDlg, IDC_SELECT_DROPDOWN /*1001*/);
    HWND hCtrlLabel = GetDlgItem(hDlg, IDC_SELECT_LABEL /*1006*/);

    SendMessageA(hDlg, WM_SETTEXT /*0xc*/, 0, (LPARAM)globals::g_CLGen_Title);
    SendMessageA(hCtrlLabel, WM_SETTEXT /*0xc*/, 0, (LPARAM)globals::g_CLGen_Instruction);

    // remove all items from the combobox
    while (SendMessageA(hCtrlCombobox, CB_DELETESTRING /*0x144*/, 0, 0) != -1);

    // populate the combobox with CLGen modes
    for (unsigned int i = 0; i < globals::g_Modes_COUNT; i++) {
        SendMessageA(hCtrlCombobox, CB_ADDSTRING /*0x143*/, 0, (LPARAM)globals::g_Modes_TABLE[i].displayName);
    }

    SendMessageA(hCtrlCombobox, CB_SETCURSEL /*0x14e*/, 0, 0);
    return FALSE;
}

// <CLGen.exe @004015c0>
BOOL __cdecl lego::Selector::HandleMessage_Command(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
    WORD msgSource = HIWORD(wParam);
    WORD idCaller = LOWORD(wParam);

    switch (msgSource) {
    case 0 /*message from Menu*/:
        return HandleMessage_MenuCommand(hDlg, wParam);
    case 1 /*message from Accelerator*/:
        return HandleMessage_AcceleratorCommand(hDlg, idCaller, (HWND)lParam);
    default:
        return FALSE;
    }
}

// <CLGen.exe @00401600>
BOOL __cdecl lego::Selector::HandleMessage_MenuCommand(HWND hDlg, WPARAM wParam)
{
    WORD idCaller = LOWORD(wParam);
    if (idCaller == IDOK /*1*/ || idCaller == IDCANCEL /*2*/) {
        EndDialog(hDlg, (INT_PTR)idCaller);
        return TRUE;
    }
    return FALSE;
}

// <CLGen.exe @00401630>
BOOL __cdecl lego::Selector::HandleMessage_AcceleratorCommand(HWND hDlg, WORD idCaller, HWND hCtrl)
{
    if (idCaller == IDC_SELECT_DROPDOWN /*1001*/) {
        globals::g_Modes_CURSEL = SendMessageA(hCtrl, CB_GETCURSEL, 0, 0);
        return TRUE;
    }
    return FALSE;
}

#pragma endregion


#pragma region WinMain Entrypoint

// <CLGen.exe @00401000>
int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow)
{
    char errorMessage[1024];

    if (CLGen::Open(CLGEN_DATA_FILENAME)) {
        globals::g_Modes_CURSEL = globals::g_Modes_COUNT;
        INT_PTR result = DialogBoxParamA(hInstance, (LPCSTR)IDD_CLGEN_DIALOG, NULL, Selector::DialogProc, 0);
        if (result == IDOK && globals::g_Modes_CURSEL != globals::g_Modes_COUNT && globals::g_Modes_CURSEL != -1) {
            CLGen::ApplyRegistryChanges(&globals::g_Modes_TABLE[globals::g_Modes_CURSEL]);
            return 0;
        }
    }
    else {
        std::sprintf(errorMessage, "Cannot find data file \"%s\"", CLGEN_DATA_FILENAME);
        MessageBoxA(NULL, errorMessage, "Error", MB_OK /*0*/);
    }

    return 0;
}

#pragma endregion

