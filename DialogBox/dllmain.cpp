#include <cocos2d.h>
#include "DialogHandler.h"
#include "Dialog.h"
#include "Minhook.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
    MH_Initialize();
    DialogLayer::mem_init();
    DialogObject::mem_init();
    DialogHandler::mem_init();
    MH_EnableHook(MH_ALL_HOOKS);

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

