#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	WSADATA wsa;
	SOCKADDR_IN addr = {0};
	char buf[256], reply[256];
	SOCKET srv, cli;
	double a, b, res;
	char op;
	int n;

	WSAStartup(MAKEWORD(2, 2), &wsa);

	srv = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(9090);

	bind(srv, (SOCKADDR *)&addr, sizeof(addr));
	listen(srv, 1);
	printf("Calculator server listening on port 9090...\n");

	cli = accept(srv, NULL, NULL);
	printf("Client connected\n");

	while ((n = recv(cli, buf, sizeof(buf) - 1, 0)) > 0) {
		buf[n] = '\0';

		if (sscanf(buf, "%lf %c %lf", &a, &op, &b) != 3) {
			n = sprintf(reply, "Error: use format  number op number\n");
		} else if (op == '/' && b == 0) {
			n = sprintf(reply, "Error: division by zero\n");
		} else if (op == '+' || op == '-' || op == '*' || op == '/') {
			res = op == '+' ? a + b : op == '-' ? a - b :
			      op == '*' ? a * b : a / b;
			n = sprintf(reply, "= %g\n", res);
		} else {
			n = sprintf(reply, "Error: operator must be + - * /\n");
		}
		send(cli, reply, n, 0);
	}

	closesocket(cli);
	closesocket(srv);
	WSACleanup();
	return 0;
}
