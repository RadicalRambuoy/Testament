#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKADDR_IN addr = {0};
	char expr[256], reply[256];
	SOCKET sock;
	int n;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9090);
	addr.sin_addr.s_addr = inet_addr(argc > 1 ? argv[1] : "127.0.0.1");

	if (connect(sock, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("Connection failed\n");
		return 1;
	}

	printf("Enter e.g. 12 * 3 (type q to quit)\n> ");
	while (fgets(expr, sizeof(expr), stdin) && expr[0] != 'q') {
		send(sock, expr, (int)strlen(expr), 0);
		n = recv(sock, reply, sizeof(reply) - 1, 0);
		if (n <= 0)
			break;
		reply[n] = '\0';
		printf("%s> ", reply);
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
