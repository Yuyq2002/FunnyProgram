#pragma once

#include "KeyState.h"
#include <unordered_map>
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <vector>

class InputSystem
{
public:
	static void Init();
	static void UpdateInput();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyPressed(int keyCode);
	static bool IsKeyReleased(int keyCode);
	static const std::vector<int>& GetAnyKeysPressed();
	static const std::vector<int>& GetAnyKeysReleased();

private:
	static std::unordered_map<int, KeyState> m_keys;
	static std::vector<int> KeysPressed;
	static std::vector<int> KeysReleased;

private:
	static void AddKey(const int& p_keyCode);
};