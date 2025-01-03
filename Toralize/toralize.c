#include "toralize.h"

Req* request(const char* dstip, const int dstport)
{
	Req* req = malloc(REQSIZE);
	if (req == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	req->vn = 4;
	req->cd = 1;
	req->dstport = htons(dstport);
	req->dstip = inet_addr(dstip);
	strncpy(req->userid, USERNAME, 8);

	return req;
}

int main(int argc, char** argv)
{
	char* host;
	int port, s;
	struct sockaddr_in sock;
	WSADATA wsaData;
	Req* req;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		perror("WSAStartup failed");
		WSACleanup();
		return -1;
	}

	if (argc < 3)
	{
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		WSACleanup();
		return -1;
	}

	host = argv[1];
	port = atoi(argv[2]);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		perror("socket");
		WSACleanup();
		return -1;
	}

	sock.sin_family = AF_INET;
	sock.sin_port = htons(PROXYPORT);

	if (inet_pton(AF_INET, PROXY, &sock.sin_addr) <= 0)
	{
		perror("inet_pton");
		closesocket(s);
		WSACleanup();
		return -1;
	}

	if (connect(s, (struct sockaddr*)&sock, sizeof(sock)))
	{
		perror("connect");
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connected to proxy\n");

	req = request(host, port);

	if (send(s, (const char*)req, REQSIZE, 0) == SOCKET_ERROR)
	{
		perror("send failed");
		closesocket(s);
		WSACleanup();
		free(req);
		return -1;
	}

	closesocket(s);
	WSACleanup();

	return 0;
}