#include "Socket.h"

#include <WinSock2.h>

#include <iostream>

#pragma comment( lib, "wsock32.lib")

Socket::Socket(int port)
{
	InitializeSockets();
	CreateSocket();

	BindSocket(port);
	SetToNonBlocking();
}

Socket::~Socket()
{

}

bool Socket::InitializeSockets()
{
	WSADATA WsaData;

	return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
}

void Socket::ShutdownSockets()
{
	WSACleanup();
}

bool Socket::CreateSocket()
{
	handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (handle <= 0)
	{
		printf("failed to create socket\n");
		return false;
	}
}

bool Socket::BindSocket(int port)
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)port);


	if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		printf("failed to bind socket\n");
		return false;
	}
	return true;
}

bool Socket::SetToNonBlocking()
{
	DWORD nonblocking = 1;
	if (ioctlsocket(handle, FIONBIO, &nonblocking) != 0)
	{
		printf("failed to set non-blocking\n");
		return false;
	}

	return true;
}

bool Socket::Send(char* data, short* ip, int port)
{
	unsigned int addr = (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];

	sockaddr_in recAddress;
	recAddress.sin_family = AF_INET;
	recAddress.sin_addr.s_addr = htonl(addr);
	recAddress.sin_port = htons(port);

	int sent_bytes = sendto(handle, (const char*) data, sizeof(char) * 256, 0, (sockaddr*)&recAddress, sizeof(sockaddr_in));
	if (sent_bytes != sizeof(*data))
	{
		printf("failed to send packet\n");
		return false;
	}
}

char* Socket::Receive()
{
	unsigned char packet_data[256];

	unsigned int max_packet_size = sizeof(packet_data);

	typedef int socklen_t;

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = recvfrom(handle, (char*)packet_data, max_packet_size, 0, (sockaddr*)&from, &fromLength);

	if (bytes <= 0)
		return "empty rec";
	else
	{
		printf("Received Message: ");
		for (int i = 0; i < bytes; ++i)
			std::cout << packet_data[i];
	}

	unsigned int from_address = ntohl(from.sin_addr.s_addr);

	unsigned int from_port = ntohs(from.sin_port);
}

