// FunnyProgramV3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <public/InputSystem.h>
#include <public/KeyCode.h>

int main()
{
	FreeConsole();
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
	input[0].ki.wVk = 'A';
	input[1].type = INPUT_KEYBOARD;
	input[1].ki.wVk = 'A';
	input[1].ki.dwFlags = KEYEVENTF_KEYUP;

    while (true)
    {
        InputSystem::UpdateInput();

		for (int i = 0; i < 26; i++)
		{
			if (InputSystem::IsKeyPressed(letterKeys[i]))
			{
				if (rand() % 100 <= 10)
				{
					int a = letterKeys[i];

					input[0].ki.wVk = a;
					input[1].ki.wVk = a;

					SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
				}
			}
		}

		Sleep(33);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
