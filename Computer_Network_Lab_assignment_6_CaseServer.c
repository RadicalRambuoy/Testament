#include <winsock2.h>
#include <stdio.h>
#include <ctype.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	WSADATA wsa;
	SOCKADDR_IN srv = {0}, cli;
	char buf[1024];
	SOCKET sock;
	int n, i, cli_len;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = INADDR_ANY;
	srv.sin_port = htons(9091);
	bind(sock, (SOCKADDR *)&srv, sizeof(srv));
	printf("UDP lowercase server listening on port 9091...\n");

	for (;;) {
		cli_len = sizeof(cli);
		n = recvfrom(sock, buf, sizeof(buf) - 1, 0, (SOCKADDR *)&cli, &cli_len);
		if (n <= 0)
			continue;
		buf[n] = '\0';
		printf("Received: %s\n", buf);

		for (i = 0; i < n; i++)
			buf[i] = (char)tolower((unsigned char)buf[i]);

		sendto(sock, buf, n, 0, (SOCKADDR *)&cli, cli_len);
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
