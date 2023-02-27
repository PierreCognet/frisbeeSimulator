#ifndef PRJ_KEYACTIONMAPPER_H
#define PRJ_KEYACTIONMAPPER_H

#include <map>

enum KeyAction { pitchUp, pitchDown, yawLeft, yawRight, rollLeft, rollRight, moveUp, moveDown, moveLeft, moveRight, moveForward, moveBackward, resetPosition, startStopTime };

class KeyActionMapper {
	public:
		KeyActionMapper();
		bool mapKeyToAction(int key, KeyAction& action);
		bool getMappedAction(QKeyEvent* event, KeyAction& action);
		int findBindedKey(KeyAction const& a);
		bool remapKeyToAction(int key, KeyAction& action);

	private:
		std::map<int, KeyAction> keyActionMap; // For each key, maps to the corresponding action. Would be cleaner to use Qt::Key, as key type.
};


#endif
