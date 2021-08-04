#include "DllInject.h"
#include "DllMain.h"



/* Adds and binds the memeber function to an event listener with the same name as the member function. Requires: ClassName::FunctionName. */
//#define bindEvent(eventName, ...) #eventName, bind(&eventName, this, std::placeholders::_1, std::placeholders::_2, __VA_ARGS__)
/* Gets the name of the event so it can be removed from the event. */
//#define unbindEvent(eventName) #eventName

void QueryAddress(void* address)
{
    if (logFile) {
        std::fprintf(logFile, "QueryAddress\n");
        std::fflush(logFile);
    }
    MEMORY_BASIC_INFORMATION memInfo;
    std::memset(&memInfo, 0, sizeof(memInfo));
    SIZE_T queryRet = VirtualQuery(address, &memInfo, sizeof(memInfo));
    if (logFile) {
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
}

#pragma region Injection

// <https://stackoverflow.com/questions/21194431/api-hooking-fails-using-jmp-instruction>

std::vector<InjectFunction*> InjectFunction::g_autoInject;
std::vector<InjectFunction*> InjectFunction::g_injected;

InjectFunction::InjectFunction(void* origFunction, void* newFunction, const std::string& name, bool autoInject)
{
    //logmsg("RedirectFunction @ %08x -> %08x\n", (unsigned int)origFunction, (unsigned int)newFunction);
    this->name = name;
    this->pOrigFunction = origFunction;
    this->pNewFunction = newFunction;
    std::memset(this->origBytes, 0, sizeof(this->origBytes));
    std::memset(this->JMP, 0, sizeof(this->JMP));
    this->origProtect = PAGE_EXECUTE_READWRITE;
    this->newProtect = PAGE_EXECUTE_READWRITE;
    this->isLoaded = false;
    this->isAutoInject = autoInject;
    if (autoInject) {
        InjectFunction::g_autoInject.push_back(this);
    }
}

const std::string& InjectFunction::Name() const
{
    return this->name;
}

bool InjectFunction::IsAutoInject() const
{
    return this->isAutoInject;
}

bool InjectFunction::IsLoaded() const
{
    return this->isLoaded;
}
bool InjectFunction::IsBaseLoaded() const
{
    return this->isLoaded && this->isBaseLoaded;
}

bool InjectFunction::Load()
{
    if (!this->isLoaded) {
        //QueryAddress(this->pOrigFunction);
        //logmsg("dll beginredirect\n");

        //OutputDebugStringA("dll beginredirect\n");
        BYTE tempJMP[sizeof(InjectFunction::JMP)] = { 0xE9, 0x90, 0x90, 0x90, 0x90, 0xC3 };         // 0xE9 = JMP 0x90 = NOP 0xC3 = RET
        std::memcpy(this->JMP, tempJMP, sizeof(this->JMP));                                        // store jmp instruction to JMP
        DWORD JMPDist = ((DWORD)this->pNewFunction - (DWORD)this->pOrigFunction - 5);  // calculate jump distance
        // assign read write protection
        if (!VirtualProtect(this->pOrigFunction, sizeof(this->JMP), PAGE_EXECUTE_READWRITE, &this->origProtect)) {
            //logmsg("VirtualProtect1 failed %i\n", (int)GetLastError());
            return false;
        }
        std::memcpy(this->origBytes, this->pOrigFunction, sizeof(this->JMP));                            // make backup
        std::memcpy(&this->JMP[1], &JMPDist, 4);                              // fill the nop's with the jump distance (JMP,distance(4bytes),RET)
        std::memcpy(this->pOrigFunction, this->JMP, sizeof(this->JMP));                                 // set jump instruction at the beginning of the original function

        DWORD unused = 0;
        if (!VirtualProtect(this->pOrigFunction, sizeof(this->JMP), this->origProtect, &unused)) {
            //logmsg("VirtualProtect2 failed %i\n", (int)GetLastError());
            return false;
        }

        InjectFunction::g_injected.push_back(this);
        this->isLoaded = true;
    }
    return this->isLoaded;
}

bool InjectFunction::Unload()
{
    if (this->isLoaded) {
        if (!this->UnloadBase())
            return false;

        //logmsg("dll endredirect\n");
        std::memcpy(this->pOrigFunction, this->origBytes, sizeof(this->JMP)); // restore backup

        InjectFunction::g_injected.push_back(this);
        this->isLoaded = false;
    }
    return !this->isLoaded;
}


bool InjectFunction::LoadBase()
{
    if (this->isLoaded && !this->isBaseLoaded) {
        DWORD unused = 0;
        if (!VirtualProtect(this->pOrigFunction, sizeof(this->JMP), this->newProtect, &unused))
            return false;

        std::memcpy(this->pOrigFunction, this->origBytes, sizeof(this->JMP));

        this->isBaseLoaded = true;
    }
    return this->isBaseLoaded;
}
bool InjectFunction::UnloadBase()
{
    if (this->isLoaded && this->isBaseLoaded) {
        std::memcpy(this->pOrigFunction, this->JMP, sizeof(this->JMP));

        DWORD unused = 0;
        if (!VirtualProtect(this->pOrigFunction, sizeof(this->JMP), this->origProtect, &unused))
            return false;

        this->isBaseLoaded = false;
    }
    return !this->isBaseLoaded;
}

bool InjectFunction::LoadAutoInject()
{
    std::vector<InjectFunction*> autoInject(InjectFunction::g_autoInject);
    for (InjectFunction* func : autoInject) {
        if (!func->Load()) {
            // log error
        }
        else {
            func->isAutoInject = false;
        }
    }
    return true;
}
bool InjectFunction::UnloadAll()
{
    std::vector<InjectFunction*> current(InjectFunction::g_injected);
    for (InjectFunction* func : current) {
        if (!func->Load()) {
            // log error
        }
    }
    return true;
}

#pragma endregion

