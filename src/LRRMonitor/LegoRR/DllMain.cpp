// DllMain.cpp : Defines the entry point and injection function for the DLL application.
// 

#include "DllMain.h"
#include "DllInject.h"
#include "Main/GameHook.h"


/*namespace globals {
    static HWND* gp_hWnd = (HWND*)0x00506800;
}*/

FILE* logFile = nullptr;
//#define logmsg(msg, ...) if (logFile) { std::fprintf(logFile, msg, __VA_ARGS__); std::fflush(logFile); }
static BOOL isDone = false;
static void* addr_SetMainWindowTitle = (void*)0x00478690;
HINSTANCE g_hDllInstance = nullptr;

static const char* lp_title_dummy = nullptr;

makeGlob(00506800, HWND*, g_hWnd);

#if 0
// <LegoRR.exe @00478690>
void __cdecl SetMainWindowTitle(const char* title)
{
    lp_title_dummy = title;
    /*if (logFile) {
        std::fprintf(logFile, "SetMainWindowTitle [called]\n");
        std::fflush(logFile);
    }*/
    //std::fprintf(logFile, "globals::gp_hWnd -> %08x\n", (unsigned int)*globals::gp_hWnd);
    //std::fflush(logFile);
    //GetWindow()
    char buffer[1024];
    std::sprintf(buffer, "%s (Debug Mode)", title);
    BOOL result = SetWindowTextA(*g_hWnd, buffer); // "LRRCE-TITLEREPLACE");// , title);
    //BOOL result = SetWindowTextA(*((HWND*)0x00506800), buffer); // "LRRCE-TITLEREPLACE");// , title);
    //BOOL result = SetWindowTextA(*globals::gp_hWnd, "LRRCE-TITLEREPLACE");// , title);
    /*if (logFile) {
        std::fclose(logFile);
        logFile = nullptr;
    }*/
    //return result;
}
#endif

#if 0
static unsigned int QueryAddress(void* address)
{
    MEMORY_BASIC_INFORMATION memInfo;
    std::memset(&memInfo, 0, sizeof(memInfo));
    SIZE_T queryRet = VirtualQuery(address, &memInfo, sizeof(memInfo));
    std::fprintf(logFile, "VirtualQuery = 0x%x (%i)\n", (unsigned int)queryRet, (int)queryRet);
    std::fflush(logFile);
    std::fprintf(logFile, "MEMORY_BASIC_INFORMATION {\n");
    std::fprintf(logFile, "\tBaseAddress       = @ %08x\n", (unsigned int)memInfo.BaseAddress);
    std::fprintf(logFile, "\tAllocationBase    = @ %08x\n", (unsigned int)memInfo.AllocationBase);
    std::fprintf(logFile, "\tAllocationProtect = 0x%x (%i)\n", (unsigned int)memInfo.AllocationProtect, (int)memInfo.AllocationProtect);
    // x64 only
    //std::fprintf(logFile, "\tPartitionId       = 0x%x (%i)\n", (unsigned int)memInfo.PartitionId, (int)memInfo.PartitionId);
    std::fprintf(logFile, "\tRegionSize        = 0x%x (%i)\n", (unsigned int)memInfo.RegionSize, (int)memInfo.RegionSize);
    std::fprintf(logFile, "\tState             = 0x%x (%i)\n", (unsigned int)memInfo.State, (int)memInfo.State);
    std::fprintf(logFile, "\tProtect           = 0x%x (%i)\n", (unsigned int)memInfo.Protect, (int)memInfo.Protect);
    std::fprintf(logFile, "\tType              = 0x%x (%i)\n", (unsigned int)memInfo.Type, (int)memInfo.Type);
    std::fprintf(logFile, "}\n");
    std::fflush(logFile);
}

static unsigned int ReplaceQuery(void* address, unsigned int param_2)
{
    MEMORY_BASIC_INFORMATION memInfo;
    std::memset(&memInfo, 0, sizeof(memInfo));
    SIZE_T queryRet = VirtualQuery(address, &memInfo, sizeof(memInfo));
    std::fprintf(logFile, "VirtualQuery = 0x%x\n", (unsigned int)queryRet);
    std::fflush(logFile);
    std::fprintf(logFile, "MEMORY_BASIC_INFORMATION {\n");
    std::fprintf(logFile, "\tBaseAddress      = @ %08x\n", (unsigned int)memInfo.BaseAddress);
    std::fprintf(logFile, "\tAllocationBase    = @ %08x\n", (unsigned int)memInfo.AllocationBase);
    std::fprintf(logFile, "\tAllocationProtect = 0x%x (%i)\n", (unsigned int)memInfo.AllocationProtect, (int)memInfo.AllocationProtect);
    // x64 only
    //std::fprintf(logFile, "\tPartitionId       = 0x%x (%i)\n", (unsigned int)memInfo.PartitionId, (int)memInfo.PartitionId);
    std::fprintf(logFile, "\tRegionSize        = 0x%x (%i)\n", (unsigned int)memInfo.RegionSize, (int)memInfo.RegionSize);
    std::fprintf(logFile, "\tState             = 0x%x (%i)\n", (unsigned int)memInfo.State, (int)memInfo.State);
    std::fprintf(logFile, "\tProtect           = 0x%x (%i)\n", (unsigned int)memInfo.Protect, (int)memInfo.Protect);
    std::fprintf(logFile, "\tType              = 0x%x (%i)\n", (unsigned int)memInfo.Type, (int)memInfo.Type);
    std::fprintf(logFile, "}\n");
    std::fflush(logFile);

    unsigned int uVar2 = 0;
    if (*(unsigned int*)memInfo.AllocationBase == 0x5a4d) {
        int* piVar1 = (int*)((char*)memInfo.AllocationBase + *(int*)((char*)memInfo.AllocationBase + 0x3c));
        if (*piVar1 == 0x4550) {
            uVar2 = 0;
            if ((param_2 < (unsigned int)((char*)memInfo.AllocationBase + piVar1[0x36])) ||
                (uVar2 = (int)memInfo.AllocationBase + piVar1[0x37] + piVar1[0x36], uVar2 <= param_2)) {
                uVar2 &= 0xffffff00;
            }
            else {
                uVar2 = uVar2 & 0xffffff00 | 1;
            }
        }
        else {
            uVar2 = (unsigned int)piVar1 & 0xffffff00;
        }
    }
    else {
        uVar2 = (unsigned int)memInfo.AllocationBase & 0xffffff00;
    }
    return uVar2;
}


static void* __cdecl GetRVAddress(void* address, unsigned int* param_2)
{
    unsigned char* param_1 = (unsigned char*)address;
    unsigned char** ppcVar1;
    //char cVar2;

    if (param_1 == nullptr) {
        param_1 = nullptr;
    }
    else {
        if (param_2 != nullptr)
            *param_2 = 0;

        if (param_1[0] == 0xff && param_1[1] == 0x25) {
            logmsg("[01]: param_1[0] == 0xff && param_1[1] == 0x25\n");
            ppcVar1 = *(unsigned char***)(param_1 + 2);
            if ((unsigned char)ReplaceQuery(param_1, (unsigned int)ppcVar1)) {
                logmsg("[02]: ReplaceQuery\n");
                param_1 = *ppcVar1;
            }
        }
        if (param_1[0] == 0xeb) {
            logmsg("[03]: param_1[0] == 0xeb\n");
            param_1 += (char)param_1[1] + 2;
            if (param_1[0] == 0xff && param_1[1] == 0x25) {
                logmsg("[04]: param_1[0] == 0xff && param_1[1] == 0x25\n");
                ppcVar1 = *(unsigned char***)(param_1 + 2);
                if ((unsigned char)ReplaceQuery(param_1, (unsigned int)ppcVar1)) {
                    logmsg("[05]: ReplaceQuery\n");
                    param_1 = *ppcVar1;
                }
            }
            else if (param_1[0] == 0xe9) {
                logmsg("[06]: param_1[0] == 0xe9\n");
                param_1 += *(int*)(param_1 + 1) + 5;
            }
        }
    }
    logmsg("GetRVAddress @ %08x -> %08x\n", (unsigned int)address, (unsigned int)param_1);
    return (void*)param_1;
}

static void ReplaceFunction(void* address, void* function)
{
    if (logFile) {
        std::fprintf(logFile, "SetMainWindowTitle [replace]\n");
        std::fflush(logFile);
    }
    address = GetRVAddress(address, nullptr);
    function = GetRVAddress(function, nullptr);

    MEMORY_BASIC_INFORMATION memInfo;
    std::memset(&memInfo, 0, sizeof(memInfo));
    SIZE_T queryRet = VirtualQuery(address, &memInfo, sizeof(memInfo));
    std::fprintf(logFile, "VirtualQuery = 0x%x\n", (unsigned int)queryRet);
    std::fflush(logFile);
    std::fprintf(logFile, "MEMORY_BASIC_INFORMATION {\n");
    std::fprintf(logFile, "\tBaseAddress      = @ %08x\n", (unsigned int)memInfo.BaseAddress);
    std::fprintf(logFile, "\tAllocationBase    = @ %08x\n", (unsigned int)memInfo.AllocationBase);
    std::fprintf(logFile, "\tAllocationProtect = 0x%x (%i)\n", (unsigned int)memInfo.AllocationProtect, (int)memInfo.AllocationProtect);
    // x64 only
    //std::fprintf(logFile, "\tPartitionId       = 0x%x (%i)\n", (unsigned int)memInfo.PartitionId, (int)memInfo.PartitionId);
    std::fprintf(logFile, "\tRegionSize        = 0x%x (%i)\n", (unsigned int)memInfo.RegionSize, (int)memInfo.RegionSize);
    std::fprintf(logFile, "\tState             = 0x%x (%i)\n", (unsigned int)memInfo.State, (int)memInfo.State);
    std::fprintf(logFile, "\tProtect           = 0x%x (%i)\n", (unsigned int)memInfo.Protect, (int)memInfo.Protect);
    std::fprintf(logFile, "\tType              = 0x%x (%i)\n", (unsigned int)memInfo.Type, (int)memInfo.Type);
    std::fprintf(logFile, "}\n");
    std::fflush(logFile);

    /*if (*(unsigned int*)memInfo.AllocationBase == 0x5a4d) {
        int* piVar1 = (int*)((char*)memInfo.AllocationBase + *(int*)((char*)memInfo.AllocationBase + 0x3c));
        if (*piVar1 == 0x4550) {
            uVar2 = 0;
            if ((param_2 < (unsigned int)((char*)memInfo.AllocationBase + piVar1[0x36])) ||
                (uVar2 = (int)memInfo.AllocationBase + piVar1[0x37] + piVar1[0x36], uVar2 <= param_2)) {
                uVar2 &= 0xffffff00;
            }
            else {
                uVar2 = uVar2 & 0xffffff00 | 1;
            }
        }
        else {
            uVar2 = (unsigned int)piVar1 & 0xffffff00;
        }
    }
    else {
        uVar2 = (unsigned int)memInfo.AllocationBase & 0xffffff00;
    }*/
    //DWORD prevProtect = 0;
    //PAGE_EXECUTE_READWRITE /*0x40*/
    /*if (!VirtualProtect(address, (SIZE_T)0x9, PAGE_EXECUTE_READWRITE, &prevProtect)) {
        if (logFile) {
            std::fprintf(logFile, "VirtualProtect [failed] error = %i\n", (int)GetLastError());
            std::fflush(logFile);
        }
    }
    unsigned char* bytes = (unsigned char*)address;
    *((unsigned char*)address) = 0xe9;
    std::fprintf(logFile, "0xe9 ");
    std::fflush(logFile);
    *((unsigned int*)((unsigned char*)address + 1)) = (unsigned int)function;
    std::fprintf(logFile, "fnReplace ");
    std::fflush(logFile);
    *((unsigned int*)((unsigned char*)address + 5)) = 0xcccccccc;
    std::fprintf(logFile, "0xcccccccc \n");
    std::fflush(logFile);*/

    /* PAGE_EXECUTE_READWRITE (0x40) */
}
#endif

extern "C" {
    __declspec(dllexport) void __cdecl Dummy(void)
    {
    }
};

#if 0

// dllmain.cpp : Defines the entry point for the DLL application.
//#include "stdafx.h"

#define JMP_SIZE 6  
class RedirectFunction
{
    LPVOID pOrigFunction;                                // address of original
    LPVOID pNewFunction;
    BYTE oldBytes[JMP_SIZE];// = { 0 };                                         // backup
    BYTE JMP[JMP_SIZE];// = { 0 };                                              // 6 byte JMP instruction
    DWORD oldProtect;
    DWORD myProtect; // = PAGE_EXECUTE_READWRITE;
    BOOL isHooked;

public:
    RedirectFunction(LPVOID origFunction, LPVOID newFunction)
    {
        logmsg("RedirectFunction @ %08x -> %08x\n", (unsigned int)origFunction, (unsigned int)newFunction);
        this->pOrigFunction = origFunction;
        this->pNewFunction = newFunction;
        std::memset(this->oldBytes, 0, JMP_SIZE);
        std::memset(this->JMP, 0, JMP_SIZE);
        this->oldProtect = PAGE_EXECUTE_READWRITE;
        this->myProtect = PAGE_EXECUTE_READWRITE;
        this->isHooked = false;
    }

    bool IsBound()
    {
        return this->isHooked;
    }

    bool Begin()
    {
        if (this->isHooked)
            return true;
        logmsg("dll beginredirect\n");

        //OutputDebugStringA("dll beginredirect\n");
        BYTE tempJMP[JMP_SIZE] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0xC3 };         // 0xE9 = JMP 0x90 = NOP 0xC3 = RET
        std::memcpy(this->JMP, tempJMP, JMP_SIZE);                                        // store jmp instruction to JMP
        DWORD JMPDist = ((DWORD)this->pNewFunction - (DWORD)this->pOrigFunction - 5);  // calculate jump distance
        // assign read write protection
        if (!VirtualProtect(this->pOrigFunction, JMP_SIZE, PAGE_EXECUTE_READWRITE, &this->oldProtect)) {
            logmsg("VirtualProtect1 failed %i\n", (int)GetLastError());
            return false;
        }
        std::memcpy(this->oldBytes, this->pOrigFunction, JMP_SIZE);                            // make backup
        std::memcpy(&this->JMP[1], &JMPDist, 4);                              // fill the nop's with the jump distance (JMP,distance(4bytes),RET)
        std::memcpy(this->pOrigFunction, this->JMP, JMP_SIZE);                                 // set jump instruction at the beginning of the original function
        
        DWORD newProtect = 0;
        if (!VirtualProtect(this->pOrigFunction, JMP_SIZE, this->oldProtect, &newProtect)) {
            logmsg("VirtualProtect2 failed %i\n", (int)GetLastError());
            return false;
        }
        //{
            //char str[200];
            //std::sprintf(str, "VirtualProtect2 failed %d\n", GetLastError());
            //OutputDebugStringA(str);
        //}
        // reset protection
        this->isHooked = true;
        return true;
    }

    bool End()
    {
        if (!this->isHooked)
            return true;
        logmsg("dll endredirect\n");
        std::memcpy(this->pOrigFunction, this->oldBytes, JMP_SIZE); // restore backup
        this->isHooked = false;
        return true;
    }
};
#endif



/*#define JMP_SIZE 6  
typedef HANDLE(WINAPI* pFindFirstFileA)(LPCSTR, LPWIN32_FIND_DATAA);  // Messagebox protoype
HANDLE WINAPI MyFindFirstFileA(LPCSTR, LPWIN32_FIND_DATAA);            // Our detour
void BeginRedirect(LPVOID);
pFindFirstFileA pOrigMBAddress = NULL;                                // address of original
BYTE oldBytes[JMP_SIZE] = { 0 };                                         // backup
BYTE JMP[JMP_SIZE] = { 0 };                                              // 6 byte JMP instruction
DWORD oldProtect, myProtect = PAGE_EXECUTE_READWRITE;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugStringA("dll attach\n");
        pOrigMBAddress = (pFindFirstFileA)
            GetProcAddress(GetModuleHandleA("Kernel32.dll"),               // get address of original 
                "FindFirstFileA");
        if (pOrigMBAddress != NULL)
        {
            OutputDebugStringA("dll attach orig address is not null");
            BeginRedirect(MyFindFirstFileA);
        }
        else
            OutputDebugStringA("dll attach orig address is null");
        // start detouring
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        std::memcpy(pOrigMBAddress, oldBytes, JMP_SIZE);                       // restore backup
        break;
    }
    return TRUE;
}

// <https://stackoverflow.com/questions/21194431/api-hooking-fails-using-jmp-instruction>
void BeginRedirect(LPVOID oldFunction, LPVOID newFunction)
{
    OutputDebugStringA("dll beginredirect\n");
    BYTE tempJMP[JMP_SIZE] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0xC3 };         // 0xE9 = JMP 0x90 = NOP oxC3 = RET
    std::memcpy(JMP, tempJMP, JMP_SIZE);                                        // store jmp instruction to JMP
    DWORD JMPSize = ((DWORD)newFunction - (DWORD)oldFunction - 5);  // calculate jump distance
    bool ret = VirtualProtect((LPVOID)oldFunction, JMP_SIZE,                       // assign read write protection
        PAGE_EXECUTE_READWRITE, &oldProtect);
    if (!ret)
        OutputDebugStringA("VirtualProtect1 failed\n");
    std::memcpy(oldBytes, oldFunction, JMP_SIZE);                            // make backup
    std::memcpy(&JMP[1], &JMPSize, 4);                              // fill the nop's with the jump distance (JMP,distance(4bytes),RET)
    std::memcpy(oldFunction, JMP, JMP_SIZE);                                 // set jump instruction at the beginning of the original function
    DWORD newProtect = 0;
    ret = VirtualProtect((LPVOID)oldFunction, JMP_SIZE, oldProtect, &newProtect);
    if (!ret)
    {
        logmsg("VirtualProtect2 failed %d\n", (int)GetLastError());
        //char str[200];
        //std::sprintf(str, "VirtualProtect2 failed %d\n", GetLastError());
        //OutputDebugStringA(str);
    }
    // reset protection
}*/

/*HANDLE WINAPI MyFindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
    OutputDebugStringA("success hook");
    VirtualProtect((LPVOID)pOrigMBAddress, SIZE, myProtect, NULL);     // assign read write protection
    memcpy(pOrigMBAddress, oldBytes, SIZE);                            // restore backup
    HANDLE retValue = FindFirstFileA(lpFileName, lpFindFileData);       // get return value of original function
    memcpy(pOrigMBAddress, JMP, SIZE);                                 // set the jump instruction again
    VirtualProtect((LPVOID)pOrigMBAddress, SIZE, oldProtect, NULL);    // reset protection
    return retValue;                                                   // return original return value
}*/


/*static void* addr_SetMainWindowTitle = (void*)0x00478690;

static const char* lp_title_dummy = nullptr;*/

//#define addr_SetMainWindowTitle (void*)0x00478690
//void __cdecl SetMainWindowTitle(const char* title)

#define DEFINE_AUTOINJECT(rvAddress, function) InjectFunction func_ ##function = InjectFunction((void*)( 0x ##rvAddress ), (function), #function , true)

//InjectFunction bind_SetMainWindowTitle = InjectFunction((void*)0x00478690, SetMainWindowTitle, "SetMainWindowTitle");

/*void** LiveObject__g_NEXT = (void*)0x004df810;
void** LiveObject__g_NEXT = (void*)0x004df810;

void* __cdecl LiveObject__Next(void)
{
    int iVar1;
    LiveObject* pLVar2;
    LiveObject* liveObj;

    if (globals::ReservedPool<LiveObject>__g_NEXT == (LiveObject*)0x0) {
        ReservedPool<LiveObject>__Alloc();
    }
    liveObj = globals::ReservedPool<LiveObject>__g_NEXT;
    pLVar2 = globals::ReservedPool<LiveObject>__g_NEXT;
    globals::ReservedPool<LiveObject>__g_NEXT = globals::ReservedPool<LiveObject>__g_NEXT->pool_m_next
        ;
    for (iVar1 = 0x103; iVar1 != 0; iVar1 += -1) {
        pLVar2->objType = OBJECT_NONE;
        pLVar2 = (LiveObject*)&pLVar2->objIndex;
    }
    liveObj->pool_m_next = liveObj;
    (liveObj->point_2f4).y = -1.0;
    (liveObj->point_2f4).x = -1.0;
    return (undefined4*)liveObj;
}*/


using namespace lego::game;
DEFINE_AUTOINJECT(00478690,  SetMainWindowTitle);

DEFINE_AUTOINJECT(00478290,  SetGameFunctions);

DEFINE_AUTOINJECT(004786b0,  CreateMainWindow);

DEFINE_AUTOINJECT(00438670,  LiveObject_SetIsCrystalPowered);
DEFINE_AUTOINJECT(00469ed0,  LiveObject_SetLevel);
DEFINE_AUTOINJECT(00474060,  Res_SetOwnerObject);



BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD   fdwReason,
                      LPVOID  lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_hDllInstance = hModule;
        if (!isDone) {
            logFile = std::fopen("lrrce-replace.log", "w");
            if (logFile) {
                std::fprintf(logFile, "DLL_PROCESS_ATTACH\n");
                std::fflush(logFile);
            }
            //std::fclose(logFile);
            InjectFunction::LoadAutoInject();
            //func_SetMainWindowTitle.Load();
            //ReplaceFunction(addr_SetMainWindowTitle, SetMainWindowTitle);
            //logFile = nullptr;
            isDone = true;
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        InjectFunction::UnloadAll();
        //func_SetMainWindowTitle.Unload();
        break;
    }
    return TRUE;
}

