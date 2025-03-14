#include "Server.h"
#include "InputSystem.h"
#include "KeyCode.h"

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
	}
}