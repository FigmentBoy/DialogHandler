#pragma once
#include <cocos2d.h>

using namespace cocos2d;
namespace DialogHandler {
    void displayFromFile(int);

    void __fastcall hkSchUpdate(cocos2d::CCScheduler* self, void*, float delta);
    inline void(__thiscall* schUpdate)(cocos2d::CCScheduler* self, float delta);

    void mem_init();
}