#include "DialogHandler.h"
#include "Dialog.h"
#include "DialogObject.h"
#include "MinHook.h"
#include <rapidjson/document.h>

#include <string>
#include <fstream>
#include <streambuf>

using namespace rapidjson;
CCLayerColor* parseJSON(std::string json) {
	Document document;
    document.Parse(json.c_str());

    int colorEnum = document["color"].GetInt();
    Value& a = document["lines"];

    CCArray* arr = CCArray::create();

    for(SizeType i = 0; i < a.Size(); i++) {
        GenericObject obj = a[i].GetObjectW();

        int portrait = obj["portrait"].GetInt();
        std::string title = obj["title"].GetString();
        std::string message = obj["message"].GetString();

        arr->addObject(DialogObject::create(title, message, portrait, 1.0, false, { 255, 255, 255 }));
    }

    CCLayerColor* output = DialogLayer::create(nullptr, arr, colorEnum);
    _asm add esp, 0x4;

    return output;
}

DWORD WINAPI update(LPVOID lpParam) {
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 0x01) {
			DialogHandler::displayFromFile(0);
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 0x01) {
			DialogHandler::displayFromFile(1);
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 0x01) {
			DialogHandler::displayFromFile(2);
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 0x01) {
			DialogHandler::displayFromFile(3);
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 0x01) {
			DialogHandler::displayFromFile(4);
		}

		if (GetAsyncKeyState(VK_NUMPAD5) & 0x01) {
			DialogHandler::displayFromFile(5);
		}

		if (GetAsyncKeyState(VK_NUMPAD6) & 0x01) {
			DialogHandler::displayFromFile(6);
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 0x01) {
			DialogHandler::displayFromFile(7);
		}

		if (GetAsyncKeyState(VK_NUMPAD8) & 0x01) {
			DialogHandler::displayFromFile(8);
		}

		if (GetAsyncKeyState(VK_NUMPAD9) & 0x01) {
			DialogHandler::displayFromFile(9);
		}
	}
	return 0;
}

static std::string json = "";
void __fastcall DialogHandler::hkSchUpdate(cocos2d::CCScheduler* self, void*, float delta) {
	if (!json.empty()) {
		CCLayerColor* layer = parseJSON(json);
		layer->setZOrder(100);
		CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
		DialogLayer::animateIn(layer, 4);

		json.clear();

	}

	schUpdate(self, delta);
}

namespace DialogHandler {
	void displayFromFile(int id) {

		std::string path = "dialogs\\" + std::to_string(id) + ".json";

		std::ifstream file(path);
		std::string str((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		if (str.empty()) {
			return;
		}

		json = str;

		
	}

	void mem_init() {
		MH_CreateHook(
			(PVOID)(GetProcAddress(GetModuleHandleA("libcocos2d.dll"), "?update@CCScheduler@cocos2d@@UAEXM@Z")),
			DialogHandler::hkSchUpdate,
			(LPVOID*)&DialogHandler::schUpdate);

		CreateThread(nullptr, 0, update, nullptr, 0, nullptr);
	}
}

/* 
Color Enum:
1 = Orange/Brown 
2 = Blue
3 = Green
4 = Purple
5 = Grey
*/