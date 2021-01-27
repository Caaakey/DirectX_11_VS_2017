#pragma once

class InputManager
{
public:
	InputManager();
	static InputManager* Get()
	{
		static InputManager Instance;
		return &Instance;
	}

	bool KeyDown(int KeyCode);
	bool StayKeyDown(int KeyCode);
	bool KeyUp(int KeyCode);
	bool ToggleKeyDown(int KeyCode);

private:
	unsigned char keyDown[256];
	unsigned char prevKey[256];
};

#define _KeyCode InputManager::Get()