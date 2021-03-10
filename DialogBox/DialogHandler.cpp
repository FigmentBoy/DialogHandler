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
		for (int i = 0; i < 10; i++)
			if (GetAsyncKeyState(VK_NUMPAD0 + i) & 0x01)
				DialogHandler::displayFromFile(i);
		Sleep(50);
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
