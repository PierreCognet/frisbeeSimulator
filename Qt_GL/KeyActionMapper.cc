#include "KeyActionMapper.h"



bool mapKeyToAction(int key, KeyAction& action) {
	keyActionMap[key] = action;
}

bool KeyActionMapper::getMappedAction(QKeyEvent* event, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(event->key()); // Find the action corresponding to this key press. 

	if (it != keyActionMap.end()) { 
		action = it->second;
		return true;
	} else {
		return false;
	}

}

int KeyActionMapper::findBindedKey(KeyAction const& a) {
	for (auto& it : keyActionMap) {
		if (it.second==a) {
			return it.first;
		}
	}
	throw string("VisualSimulation::findBindedKey(...)  action doesn't have any key binding");
}


bool remapKeyToAction(int key, KeyAction& action) {

	map<int, KeyAction>::iterator it = keyActionMap.find(key);

	if (it == keyActionMap.end()) {
		// The key is not already attributed to other action. Good, so attribute it to this action.
		bool valueNotYetFound (true);
		for (map<int, KeyAction>::iterator it=keyActionMap.begin(); it!=keyActionMap.end() && valueNotYetFound; ++it) {
			if (it->second==action) {
				keyActionMap.erase(it);
				valueNotYetFound = false;
			}
		}
		keyActionMap[key] = action;

		return true;
	} else {
		return false;
	}
}
