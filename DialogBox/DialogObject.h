#pragma once
#include <cocos2d.h>
#include <string>

using namespace cocos2d;


class AttemptAtReversingDialogObject : public cocos2d::CCObject {
protected:
	char pad_0x00[0x60]; // 0x00

	std::string m_content; // 0x32
	std::string m_title; // 0x56
	int type; // 0x80
	_ccColor3B color; // 9x84
	char pad_0x87[0x01]; // 0x87
	float m_unknown; // 0x88
	char pad_0x92[0x04]; // 0x92
	bool m_unknown_2; // 0x96

public:
	bool init(std::string title, std::string text, int type, float unknown, bool also_unknown, _ccColor3B textColor) {
		uintptr_t base = (uintptr_t)GetModuleHandle(0);

		return reinterpret_cast<bool(__thiscall*)(AttemptAtReversingDialogObject*, std::string, std::string, int, float, bool, _ccColor3B)>
			(base + 0x6D2E0)(this, title, text, type, unknown, also_unknown, textColor);
	}

	static AttemptAtReversingDialogObject* create(std::string title, std::string text, int type, float text_scale, bool is_unskippable, _ccColor3B textColor) {
		AttemptAtReversingDialogObject* obj = new AttemptAtReversingDialogObject;
		
		obj->init(title, text, type, text_scale, is_unskippable, textColor);
		obj->autorelease();

		return obj;
	}
};