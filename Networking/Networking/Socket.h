class Socket
{
public:

	Socket(int port);

	~Socket();

	bool Send(char* data, short* ip, int port);

	char* Receive();

private:

	bool InitializeSockets();

	void ShutdownSockets();

	bool CreateSocket();

	bool BindSocket(int port);

	bool SetToNonBlocking();	

	int handle;
};