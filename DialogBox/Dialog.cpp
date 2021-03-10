#include "Dialog.h"

void DialogObject::mem_init() {
	uintptr_t base = (uintptr_t)GetModuleHandle(0);
	DialogObject::init = reinterpret_cast<decltype(DialogObject::init)>(base + 0x6D2E0);
}

void DialogLayer::mem_init() {
	uintptr_t base = (uintptr_t)GetModuleHandle(0);
	DialogLayer::create = reinterpret_cast<decltype(DialogLayer::create)>(base + 0x6D470);
	DialogLayer::animateIn = reinterpret_cast<decltype(DialogLayer::animateIn)>(base + 0x6E130);
}

std::string GetPlayerName() {
	size_t base = reinterpret_cast<size_t>(GetModuleHandle(0));
	uintptr_t AccountManager = *reinterpret_cast<std::uintptr_t*>(base + 0x3222D8);

	auto name = *reinterpret_cast<std::string*>(AccountManager + 0x108);

	return name;
}


CCDialogObject* DialogObject::create(std::string title, std::string text, int type, float text_scale, bool is_unskippable, _ccColor3B color) {
	CCDialogObject* obj = new CCDialogObject();

	int index;
	int pos = 0;
	std::string username;

	while ((index = text.find("{user}", pos)) != std::string::npos) {
		if (username.empty()) {
			username = GetPlayerName();
		}
		text.replace(index, 6, username);

		pos = index + 1;
	}


	while ((index = title.find("{user}", pos)) != std::string::npos) {
		if (username.empty()) {
			username = GetPlayerName();
		}
		title.replace(index, 6, username);

		pos = index + 1;
	}
	
	init(obj, title, text, type, text_scale, is_unskippable, color);
	obj->autorelease();

	return obj;
}