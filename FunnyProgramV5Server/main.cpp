#include "Server.h"
#include "InputSystem.h"
#include "KeyCode.h"

int main()
{
	InputSystem::Init();

	Server server;
	server.Init(true);
	server.Listen();

	bool is_running = true;

	while (is_running)
	{
		InputSystem::UpdateInput();

		if (InputSystem::IsKeyPressed(KeyCode_Add))
		{
			is_running = false;
		}

		byte_stream stream;
		byte_stream_writer writer(stream);

		std::vector<int> pressed = InputSystem::GetAnyKeysPressed();
		for (const auto& k : pressed)
		{
			writer.serialize(k);
			writer.serialize(true);
		}

		std::vector<int> released = InputSystem::GetAnyKeysReleased();
		for (const auto& k : released)
		{
			writer.serialize(k);
			writer.serialize(false);
		}

		server.Send(stream);

		Sleep(16);

	}
}