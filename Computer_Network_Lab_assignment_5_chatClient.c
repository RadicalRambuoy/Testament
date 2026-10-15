#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKADDR_IN addr = {0};
	char msg[1024], reply[1100];
	SOCKET sock;
	int n;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr(argc > 1 ? argv[1] : "127.0.0.1");

	if (connect(sock, (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR) {
		printf("Connection failed\n");
		return 1;
	}

	printf("Connected. Type messages (Ctrl+Z then Enter to quit).\n> ");
	while (fgets(msg, sizeof(msg), stdin)) {
		send(sock, msg, (int)strlen(msg), 0);
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
