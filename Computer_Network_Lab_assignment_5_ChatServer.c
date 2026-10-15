#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	WSADATA wsa;
	SOCKADDR_IN addr = {0};
	char buf[1024], reply[1024];
	SOCKET srv, cli;
	int n;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	srv = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(8080);

	bind(srv, (SOCKADDR *)&addr, sizeof(addr));
	listen(srv, 1);
	printf("Listening on port 8080...\n");

	cli = accept(srv, NULL, NULL);
	printf("Client connected\n");

	while ((n = recv(cli, buf, sizeof(buf) - 1, 0)) > 0) {
		buf[n] = '\0';
		printf("Client: %s", buf);

		printf("Reply: ");
		if (!fgets(reply, sizeof(reply), stdin))
			break;
		send(cli, reply, (int)strlen(reply), 0);
	}

	closesocket(cli);
	closesocket(srv);
	WSACleanup();
	return 0;
}
