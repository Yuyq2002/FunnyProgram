#pragma once

#include "KeyState.h"
#include <unordered_map>
#include <Windows.h>
#include <WinUser.h>
#include <iostream>

class InputSystem
{
public:
	static void Init();
	static void UpdateInput();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyPressed(int keyCode);
	static bool IsKeyReleased(int keyCode);

private:
	static std::unordered_map<int, KeyState> m_keys;

private:
	static void AddKey(const int& p_keyCode);
};