#pragma once

#include "Common.h"


void QueryAddress(void* address);

#pragma region Injection


/*LiveObject* __cdecl lego::pool::ReservedPool<LiveObject>__Next(void)
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
    return liveObj;
}

void __cdecl lego::pool::ReservedPool<ImageFont>__Release(ImageFont* font)
{
    ReservedPool<ImageBMP>__Release(font->bitmap);
    font->pool_m_next = globals::ReservedPool<ImageFont>__g_NEXT;
    globals::ReservedPool<ImageFont>__g_NEXT = font;
    return;
}*/


// <https://stackoverflow.com/questions/21194431/api-hooking-fails-using-jmp-instruction>
//#define Inject_JMP_SIZE 6
class InjectFunction
{
    static std::vector<InjectFunction*> g_autoInject;
    static std::vector<InjectFunction*> g_injected;

    void* pOrigFunction;
    void* pNewFunction;
    /*std::array<unsigned char, 6> origBytes;
    std::array<unsigned char, 6> JMP;*/
    unsigned char JMP[6];// = { 0 };
    unsigned char origBytes[6];// = { 0 };
    unsigned long origProtect; // = PAGE_EXECUTE_READWRITE;
    unsigned long newProtect;
    bool isLoaded;
    bool isAutoInject;
    bool isBaseLoaded;
    std::string name;

public:
    InjectFunction(void* origFunction, void* newFunction, const std::string& name = "", bool autoInject = true);

    const std::string& Name() const;

    bool IsAutoInject() const;

    bool IsLoaded() const;
    bool IsBaseLoaded() const;

    bool Load();

    bool Unload();


    bool LoadBase();
    bool UnloadBase();

    static bool LoadAutoInject();
    static bool UnloadAll();
};

#pragma endregion

