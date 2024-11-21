#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

int g_clnt_socks[CLNT_MAX];
int g_clnt_count = 0;

int main(int argc, char ** argv){
	printf("socket start1");
	int serv_sock;
	int clnt_sock;
	printf("socket start2");
	struct sockaddr_in clnt_addr;
	printf("socket start3");
	int clnt_addr_size;

	printf("socket start4");
	struct sockaddr_in serv_addr;
	printf("socket start5");
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
	printf("socket ok");

	serv_addr.sin_family = AF_INET;
	printf("family ok");
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("adr ok");
	serv_addr.sin_port=htons(7989);
	printf("port ok");

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		printf("bind error\n");
	} else {
		printf("bind ok");
	}


	if(listen(serv_sock, 5) == -1){
		printf("listen error");
	} else {
		printf("listen ok");
	}
		
	
	char buf[200];
	int recv_len = 0;
	while(1){

		clnt_addr_size=sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
		printf("stay");

		while(1) {
			recv_len = read(clnt_sock, buf, 200);

			printf("recv : ");
			for(int i = 0; i < recv_len; i++){
				printf("%02X ", (unsigned char)buf[i]);
			}
			printf("\n");
		}
	}

}
