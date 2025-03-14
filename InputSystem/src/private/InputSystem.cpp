#include "public/InputSystem.h"
#include "public/KeyCode.h"

std::unordered_map<int, KeyState> InputSystem::m_keys;
std::vector<int> InputSystem::KeysPressed;
std::vector<int> InputSystem::KeysReleased;

void InputSystem::Init()
{
	AddKey(KeyCode_Left    );
	AddKey(KeyCode_Up	   );
	AddKey(KeyCode_Right   );
	AddKey(KeyCode_Down	   );
	AddKey(KeyCode_Numpad0 );
	AddKey(KeyCode_Numpad1 );
	AddKey(KeyCode_Numpad2 );
	AddKey(KeyCode_Numpad3 );
	AddKey(KeyCode_Numpad4 );
	AddKey(KeyCode_Numpad5 );
	AddKey(KeyCode_Numpad6 );
	AddKey(KeyCode_Numpad7 );
	AddKey(KeyCode_Numpad8 );
	AddKey(KeyCode_Numpad9 );
	AddKey(KeyCode_Subtract);
	AddKey(KeyCode_A	   );
	AddKey(KeyCode_B	   );
	AddKey(KeyCode_C	   );
	AddKey(KeyCode_D	   );
	AddKey(KeyCode_E	   );
	AddKey(KeyCode_F	   );
	AddKey(KeyCode_G	   );
	AddKey(KeyCode_H	   );
	AddKey(KeyCode_I	   );
	AddKey(KeyCode_J	   );
	AddKey(KeyCode_K	   );
	AddKey(KeyCode_L	   );
	AddKey(KeyCode_M	   );
	AddKey(KeyCode_N	   );
	AddKey(KeyCode_O	   );
	AddKey(KeyCode_P	   );
	AddKey(KeyCode_Q	   );
	AddKey(KeyCode_R	   );
	AddKey(KeyCode_S	   );
	AddKey(KeyCode_T	   );
	AddKey(KeyCode_U	   );
	AddKey(KeyCode_V	   );
	AddKey(KeyCode_W	   );
	AddKey(KeyCode_X	   );
	AddKey(KeyCode_Y	   );
	AddKey(KeyCode_Z	   );
}

void InputSystem::UpdateInput()
{
	KeysPressed.clear();
	KeysReleased.clear();

	for (auto& k : m_keys)
	{
		// for keys pressed or released last frame, set pressed or released state to false
		k.second.is_pressed = false;
		k.second.is_released = false;

		// Update key input state for this frame
		short pressed = GetKeyState(k.first) & 0x80;
		k.second.is_released = (k.second.is_down && !pressed) ? true : false;
		if (k.second.is_released) 
			KeysReleased.push_back(k.first);
		k.second.is_pressed = (pressed && !k.second.is_down) ? true : false;
		if (k.second.is_pressed) 
			KeysPressed.push_back(k.first);
		k.second.is_down = pressed ? true : false;
	}
}

bool InputSystem::IsKeyDown(int keyCode)
{
	if (m_keys[keyCode].is_down) return true;
	return false;
}

bool InputSystem::IsKeyPressed(int keyCode)
{
	if (m_keys[keyCode].is_pressed) return true;
	return false;
}

bool InputSystem::IsKeyReleased(int keyCode)
{
	if (m_keys[keyCode].is_released) return true;
	return false;
}

const std::vector<int>& InputSystem::GetAnyKeysPressed()
{
	return KeysPressed;
}

const std::vector<int>& InputSystem::GetAnyKeysReleased()
{
	return KeysReleased;
}

void InputSystem::AddKey(const int& p_keyCode)
{
	m_keys.insert(std::pair<int, KeyState>(p_keyCode, KeyState()));
}
