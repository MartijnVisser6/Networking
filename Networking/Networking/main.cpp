#include "Socket.h"
#include <iostream>
#include <string>
int main()
{
	int yourport, otherport;

	std::cout << "Type in your port number" << std::endl;

	std::cin >> yourport;

	std::cout << std::endl << "Type in other port number" << std::endl;

	std::cin >> otherport;

	Socket s(yourport);

	while (true)
	{
		char input[256];

		std::cout << "Type message:" << std::endl;

		std::cin.getline(input,256);

		short ip[] = { 127, 0, 0, 1 };
		s.Send(&input[0], &ip[0], otherport);

		s.Receive();
	}

	while (true){}
	return 0;
}