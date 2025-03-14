#include <iostream>
#include <string>

#include <public/InputSystem.h>
#include <public/KeyCode.h>

int main()
{
	//FreeConsole();
	srand(time(0));

	int letterKeys[]
	{
		KeyCode_A,
		KeyCode_B,
		KeyCode_C,
		KeyCode_D,
		KeyCode_E,
		KeyCode_F,
		KeyCode_G,
		KeyCode_H,
		KeyCode_I,
		KeyCode_J,
		KeyCode_K,
		KeyCode_L,
		KeyCode_M,
		KeyCode_N,
		KeyCode_O,
		KeyCode_P,
		KeyCode_Q,
		KeyCode_R,
		KeyCode_S,
		KeyCode_T,
		KeyCode_U,
		KeyCode_V,
		KeyCode_W,
		KeyCode_X,
		KeyCode_Y,
		KeyCode_Z
	};

	INPUT input[2];
	ZeroMemory(input, sizeof(input));

	input[0].type = INPUT_KEYBOARD;
	input[0].ki.wVk = 'B';
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 'B';
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

	while (true)
	{
		std::string a;
		std::cin >> a;

		if (SendInput(ARRAYSIZE(input), input, sizeof(INPUT)))
		{
			std::cout << "Uppps some error in SendInput: " << GetLastError() << std::endl;
		}
	}
}