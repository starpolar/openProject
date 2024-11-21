#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>


#define BUFFSIZE 100
#define NAMESIZE 20

int StoHEX(char fi, char sc);
void error_handling(char *msg);
void * send_message(void * arg);
void * recv_message(void * arg);

char message[BUFFSIZE];

void * rcv(void * arg){ // 서버가 보내는걸 받는 스레드.

    printf("rcv thread created\n");
    int sock = (int)arg;
    char buf[500];
    int len;
    while(1){
        len = read(sock, buf, sizeof(buf));

        if(len == -1){
            printf("sock close\n");
            break;
        }

        printf("%s", buf);
    }

    pthread_exit(0);
    return NULL;
}

int main(int argc, char **argv) {

    int sock;
    struct sockaddr_in serv_addr;
    pthread_t rcv_thread;
    void* thread_result;

    char id[100];
    if(argc < 2) { // 여기 하나에 걸리게만 만드는게 좋은 예외처리.
        printf("you have to enter ID\n");
        return 0;
    }
    strcpy(id, argv[1]);
    printf("id : %s\n", id);

    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1){
        printf("socket error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    uint16_t tmpPort = 7989;
    serv_addr.sin_port=htons(tmpPort);

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        printf("connect error");
    }

    pthread_create(&rcv_thread, NULL, rcv, (void *)sock);

    char msg[1000];
    char chat[100];
    while(1){
        printf("채팅 입력 : ");
        gets(chat);
	        // gets가 위험한 이유는? 무한으로 입력 받을 수 있어서. 
		        // 시스템 명령어나 리눅스를 조작하는 코드를 보내서 해킹하고 시스템을 조작할 수 있어서.
        sprintf(msg, "[%s] : %s\n", id, chat);
        printf("send : %s\n", msg);

        write(sock, msg, strlen(msg)+1);
        sleep(1);
    }

    /* 쓰레드
    pthread_crete(&snd_thread, NULL, send_mesesage, (void*)sock);
    pthread_crete(&rcv_thread, NULL, recv_mesesage, (void*)sock);

    pthread_join(snd_thread, &thread_result);
    pthread_join(rcv_thread, &thread_result);
    */


    close(sock);
    return 0;
}