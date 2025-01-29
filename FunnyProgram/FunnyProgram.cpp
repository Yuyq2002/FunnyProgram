// FunnyProgram.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "FunnyProgram.h"

void WinCtrlD();

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    bool isPressed = false;
    while (true)
    {
        short pressed = GetKeyState(0x43) & 0x80;

        if (pressed)
        {
            if (!isPressed)
            {
                WinCtrlD();
                isPressed = true;
            }
        }
        else
        {
            isPressed = false;
        }
    }

    return 0;
}

void WinCtrlD()
{
    INPUT inputs[6] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_LWIN;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_LCONTROL;

    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'D';

    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = 'D';
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[4].type = INPUT_KEYBOARD;
    inputs[4].ki.wVk = VK_LCONTROL;
    inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

    inputs[5].type = INPUT_KEYBOARD;
    inputs[5].ki.wVk = VK_LWIN;
    inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;


    UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
}