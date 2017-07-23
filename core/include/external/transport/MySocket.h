#pragma once

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
using namespace std;

#ifdef WIN32
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define socklen_t int
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
//#include <netinet/in.h>
#define SOCKET_ERROR   -1
#define INVALID_SOCKET -1
#define closesocket close
#define SOCKET int
#endif

#ifndef MESSAGE_BUFF_SIZE
#define MESSAGE_BUFF_SIZE 2048
#endif

#define LISTEN_QUEUE_DEFAULT 20

class CMySocket
{
public:
	CMySocket();
	~CMySocket();

	bool ListenFrom(int port);
	bool ConnectTo(const char * ip, int port);
	bool ConnectToO(const char * ip, int port, long timeout_sec, long timeout_usec);

	bool Create();
	bool Bind(int port);
	bool Connect(const char * ip, int port);
	bool ConnectO(const char * ip, int port, long timeout_sec, long timeout_usec);
	bool Listen();
	SOCKET Accept();
	int Send(const char * buff, int len);
	int SendO(const char * buff, int len, long timeout_sec, long timeout_usec);
	int Recv(char * buff, int len);
	int RecvO(char * buff, int len, long timeout_sec, long timeout_usec);
	void Close();

	void Clone(CMySocket & srcSock);

	void SetSocket(SOCKET sock);
	SOCKET GetSocket();
	bool SetMaxListenQueue(int listen_queue);
	int GetMaxListenQueue();

public:
	void Init();
	bool HasError();
	char * GetMessage();

	bool IsSockInvalid();
	bool IsSockInvalid(SOCKET sock);
	void SetSockInvalid();

protected:
	SOCKET m_localSock;
	int m_nMaxListenQueue;
	bool m_bHasError;
	char m_strMsg[MESSAGE_BUFF_SIZE];
};
