#include "Server.h"
#include "InputSystem.h"
#include "KeyCode.h"
#include <string>

int main()
{
	//InputSystem::Init();

	Server server;
	server.Init(true);
	server.Listen();

	bool is_running = true;

	while (is_running)
	{
		if (InputSystem::IsKeyPressed(KeyCode_Add))
		{
			is_running = false;
		}

		server.Recv();

		std::string input;
		std::getline(std::cin, input);

		server.Send(input.c_str());
	}
}