#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
	WSADATA wsa;
	SOCKADDR_IN srv = {0};
	char msg[1024], reply[1024];
	SOCKET sock;
	int n, len;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(9091);
	srv.sin_addr.s_addr = inet_addr(argc > 1 ? argv[1] : "127.0.0.1");

	printf("Enter a string (type quit to exit)\n> ");
	while (fgets(msg, sizeof(msg), stdin)) {
		msg[strcspn(msg, "\r\n")] = '\0';
		if (strcmp(msg, "quit") == 0)
			break;

		len = (int)strlen(msg);
		sendto(sock, msg, len, 0, (SOCKADDR *)&srv, sizeof(srv));

		n = recvfrom(sock, reply, sizeof(reply) - 1, 0, NULL, NULL);
		if (n <= 0)
			break;
		reply[n] = '\0';
		printf("Server: %s\n> ", reply);
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
