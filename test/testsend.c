#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]){
	int portno = 8080;
	int destport = 8086;
	if(argc >= 2){
		portno = atoi(argv[1]);
	}
	if(argc == 3){
		destport = atoi(argv[2]);
	}
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	const int one =1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portno);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(sock, (struct sockaddr*)&addr, sizeof(addr));

	struct sockaddr_in daddr;
	daddr.sin_family = AF_INET;
	daddr.sin_port = htons(destport);
	inet_pton(AF_INET, "127.0.0.1", &(daddr.sin_addr));
	sendto(sock, "hello world\n", 12, 0, (struct sockaddr*)&daddr, sizeof(daddr));
	close(sock);
	return 0;
}
