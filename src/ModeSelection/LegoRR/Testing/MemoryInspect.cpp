// MemoryInspect.cpp : 
//

#include "MemoryInspect.h"


namespace inspect {
namespace globals {
	static BOOL g_Inspect_ISINIT = FALSE;
	static HANDLE g_LegoRRHandle;
} /* namespace globals */

HANDLE __cdecl GetProcessIfLegoRR(DWORD processID);
HANDLE __cdecl OpenLegoRR();
void __cdecl CloseLegoRR();
} /* namespace inspect */


#define LEGORR_EXE "LegoRR.exe"
#define LEGORR_NOEXE "LegoRR"


using namespace inspect;
using namespace lego;


// <https://docs.microsoft.com/en-us/windows/win32/psapi/enumerating-all-processes>
HANDLE inspect::GetProcessIfLegoRR(DWORD processID)
{
    char szProcessName[MAX_PATH] = "<unknown>";

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (hProcess != nullptr) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
            GetModuleBaseNameA(hProcess, hMod, szProcessName,
                sizeof(szProcessName) / sizeof(char));
        }

        if (_stricmp(szProcessName, LEGORR_EXE) == 0 || _stricmp(szProcessName, LEGORR_NOEXE) == 0) {
            return hProcess;
        }

        CloseHandle(hProcess);
    }

    return nullptr;
}

void __cdecl inspect::CloseLegoRR()
{
    if (globals::g_LegoRRHandle != nullptr) {
        CloseHandle(globals::g_LegoRRHandle);
        globals::g_LegoRRHandle = nullptr;
    }
}

HANDLE __cdecl inspect::OpenLegoRR()
{
    if (globals::g_LegoRRHandle != nullptr)
        return globals::g_LegoRRHandle;

    // Get the list of process identifiers.

    DWORD cbNeeded = 0;
    DWORD dummy = 0;
    if (!EnumProcesses(&dummy, 0, &cbNeeded))
        return nullptr;

    DWORD* lpProcesses = (DWORD*)std::malloc(cbNeeded);
    std::memset(lpProcesses, 0, cbNeeded);

    if (!EnumProcesses(lpProcesses, cbNeeded, &cbNeeded)) {
        std::free(lpProcesses);
        return nullptr;
    }

    DWORD cProcesses = cbNeeded / sizeof(DWORD);

    //DWORD cbNeeded, cProcesses;
    //DWORD aProcesses[4096], cbNeeded, cProcesses;
    //std::memset(aProcesses, 0, sizeof(aProcesses));

    //if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    //    return nullptr;

    // Calculate how many process identifiers were returned.

    //cProcesses = (cbNeeded + sizeof(DWORD) - 1) / sizeof(DWORD);
    //cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
    HANDLE hProcess = nullptr;
    for (unsigned int i = 0; i < cProcesses && hProcess == nullptr; i++){
        if (lpProcesses[i] != 0)
            hProcess = GetProcessIfLegoRR(lpProcesses[i]);
    }
    std::free(lpProcesses);

    if (hProcess != nullptr) {
        globals::g_LegoRRHandle = hProcess;
        return hProcess;
    }
    else {
        debugf("FAILED: OpenLegoRR()\n");
        return nullptr;
    }
}


void __cdecl inspect::InitMemoryInspect()
{
	globals::g_LegoRRHandle = nullptr;
	globals::g_Inspect_ISINIT = TRUE;
}

void __cdecl inspect::CleanupMemoryInspect()
{
    CloseLegoRR();
    globals::g_LegoRRHandle = nullptr;
    globals::g_Inspect_ISINIT = FALSE;
}

size_t __cdecl inspect::ReadMemory(RVAddress address, void* out_buffer, size_t size)
{
    HANDLE hProcess = OpenLegoRR(); // ensure it's open when we need it
    if (hProcess != nullptr && address) {
        DWORD numBytesRead;
        if (ReadProcessMemory(hProcess, (LPCVOID)address, out_buffer, size, &numBytesRead)) {
            return (size_t)numBytesRead;
        }
        else {
            debugf("FAILED: ReadProcessMemory %p\nGetLastError = %u\n", (LPVOID)address, GetLastError());
        }
    }
    return 0;
}

RVAddress __cdecl inspect::ResolvePointer(RVAddress address)
{
    HANDLE hProcess = OpenLegoRR(); // ensure it's open when we need it
    if (hProcess != nullptr) {
        DWORD numBytesRead;
        RVAddress pointer = 0;
        if (ReadProcessMemory(hProcess, (LPCVOID)address, &pointer, 4, &numBytesRead)) {
            if (numBytesRead == 4) {
                return (RVAddress)pointer;
            }
            else {
                debugf("FAILED: ResolvePointer %p bytes = %u\nGetLastError = %u\n", (LPVOID)address, numBytesRead, GetLastError());
            }
            return numBytesRead;
        }
        else {
            debugf("FAILED: ResolvePointer %p\nGetLastError = %u\n", (LPVOID)address, GetLastError());
        }
    }
    return (RVAddress)nullptr;
}

BOOL __cdecl inspect::IsMemoryOpen()
{
    return (globals::g_LegoRRHandle != nullptr);
}

