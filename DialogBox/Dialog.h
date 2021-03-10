#pragma once
#include <cocos2d.h>
#include <string>

class CCDialogObject : public cocos2d::CCObject {
protected:
	char pad[0x60];
};

using namespace cocos2d;
namespace DialogObject {
	inline bool(__thiscall* init)(CCDialogObject* self, std::string title, std::string text, int type, float unknown, bool also_unknown, _ccColor3B textColor);
	
	CCDialogObject* create(std::string title, std::string text, int type, float text_scale, bool is_unskippable, _ccColor3B color);

	void mem_init();
}

namespace DialogLayer {
	inline CCLayerColor* (__fastcall* create)(CCObject*, CCArray*, int);
	inline CCAction* (__thiscall* animateIn)(CCLayerColor*, int);
	void mem_init();
}
