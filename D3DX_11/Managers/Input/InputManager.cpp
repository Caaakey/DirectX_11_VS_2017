#include "InputManager.h"
#include "stdafx.h"

InputManager::InputManager()
{
	ZeroMemory(keyDown, sizeof keyDown);
	ZeroMemory(prevKey, sizeof prevKey);
}

bool InputManager::KeyDown(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		if (!keyDown[KeyCode]) {
			keyDown[KeyCode] = 0x01;
			return true;
		}
	}
	else keyDown[KeyCode] = 0;

	return false;
}

bool InputManager::StayKeyDown(int KeyCode)
{
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		prevKey[KeyCode] = 0x01;
		return true;
	}

	return false;
}

bool InputManager::KeyUp(int KeyCode)
{
	if (!StayKeyDown(KeyCode)) {
		if (prevKey[KeyCode] == 0x01) {
			prevKey[KeyCode] = 0;
			return true;
		}
	}

	return false;
}

bool InputManager::ToggleKeyDown(int KeyCode)
{
	if (GetKeyState(KeyCode) & 0x0001) return true;
	return false;
}
