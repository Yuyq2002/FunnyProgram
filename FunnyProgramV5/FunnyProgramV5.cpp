// FunnyProgramV5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Server.h"
//class Shared ...
//class Server...
#include "Client.h"
//class Client ...
#include <iostream>
#include <string>

int main() {
	/*std::cout << "Client or Server" << std::endl;
	std::string input;
	std::cin >> input;
	Shared* process;

	if (input == "S")
	{
		Server* server = new Server();
		if(server->Init(true))
			server->Listen();
		process = server;
	}
	else if (input == "C")
	{
		Client* client = new Client();
		if(client->Init())
			client->Connect();
		process = client;
	}

	std::cin >> input;*/

	Client client;
	client.Init();

	std::string t;
	std::cin >> t;
	client.Connect();

	std::string input;

	while (true)
	{
		client.Recv();

		std::getline(std::cin, input);
		std::cin >> input;
		if (input == "Close")
			break;
		else
			client.SendToDest(input.c_str());
	}

	return 0;
}
