// FunnyProgramV2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <vector>
#include <mmsystem.h>

#include "public/InputSystem.h"

void PlayRandomSound(int i);

std::vector<int> GetRandomKeys(int amount);

int main()
{
    FreeConsole();
    srand(time(0));

    InputSystem::Init();

    std::vector<int> randomKeys = GetRandomKeys(5);
    std::vector<std::string> sound =
    {
        "f1.wav", "f2.wav", "f3.wav"
    };

    while (true)
    {
        InputSystem::UpdateInput();

        for (auto& key : randomKeys)
        {
            if (InputSystem::IsKeyPressed(key))
            {
                PlayRandomSound(rand() % 3);
                std::cout << "Trigger" << std::endl;
            }
        }

        Sleep(33);
    }

    return 0;
}

std::vector<int> GetRandomKeys(int amount)
{
    std::vector<int> returns;

    std::vector<int> keys
    {
        0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
        0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C,
        0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52,
        0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
        0x59, 0x5A,
    };

    for (int i = 0; i < amount; i++)
    {
        int random = rand() % keys.size();

        returns.push_back(keys[random]);

        keys.erase(keys.begin() + random);
    }

    return returns;
}

void PlayRandomSound(int i)
{
    switch (i)
    {
    case 0:
        PlaySound(TEXT("f1.wav"), NULL, SND_FILENAME);
        break;
    case 1:
        PlaySound(TEXT("f2.wav"), NULL, SND_FILENAME);
        break;
    case 2:
        PlaySound(TEXT("f3.wav"), NULL, SND_FILENAME);
        break;
    }
}