#include "common.h"
#include "equipamentos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXEQUIPAMENTOS 4
#define MAXSENSORES 4
#define BUFSZ 1024


void usage(int argc, char **argv) {
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 1024

int main(int argc, char **argv) {
	if (argc < 3) {
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		usage(argc, argv);
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	while(1) {
	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);
	printf("mensagem> ");
	//guarda o input do teclado dentro do buf
	fgets(buf, BUFSZ-1, stdin);
	//envia para o servidor
	size_t count = send(s, buf, strlen(buf)+1, 0);
	if (count != strlen(buf)+1) {
		logexit("send");
	}
	memset(buf, 0, BUFSZ);
	unsigned total = 0;
	size_t countr = recv(s, buf , BUFSZ - total, 0);
	printf("Valor count: %ld\n", countr);
	puts(buf);
	}
	close(s);
	//puts(buf);

	exit(EXIT_SUCCESS);
}