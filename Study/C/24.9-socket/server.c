#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <arpa/inet.h> // 여기부터 소켓 헤더
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

#define BUFFSIZE 200

int g_clnt_socks[CLNT_MAX]; // 글로벌 함수니까 g_
int g_clnt_count = 0;

pthread_mutext_t g_mutex;

void send_all_clnt(char * msg, int my_sock){ // 채팅한 본인 이외에 보내는 스레드

	pthread_mutex_lock(&g_mutex);
		// g_clnt_socks을 한번 쓰니까 mutex.
	for(int i = 0; i < g_clnt_count; i++){

		if(g_clnt_socks[i] != my_sock) {
			write(g_clnt_socks[i], msg, strlen(msg)+1);
		}
	}
	pthread_mutex_unlock(&g_mutex);

}

void * clnt_connection(void * arg){

	int clnt_sock = (int)arg;
	int str_len=0;

	char msg[BUFFSIZE];
	int i;

	while(1){

		// 읽기
		str_len = read(clnt_sock,msg,sizeof(msg));
		if(str_len == -1){ // 세션이 끊어진 상황.
			printf("clnt[%d] close\n", clnt_sock);
			break;
		}

		// 채팅
		printf("%s\n",msg);

		send_all_clnt(msg, clnt_sock);

	}

	pthread_mutex_lock(&g_mutex);
	for(int i = 0; i < g_clnt_count; i++){ // 소켓을 하나 없앰.
		if(clnt_sock == g_clnt_socks[i]){
			for(; i < g_clnt_count-1; i++) {
				g_clnt_socks[i] = g_clnt_socks[i+1];
			}
			break;
		}
	}
	pthread_mutex_unlock(&g_mutex);

	close(clnt_sock);
	pthread_exit(0); // 자원 반환.
	return NULL;
}

int main(int argc, char ** argv){

	int serv_sock;
		
	// 소켓 껍대기 만들기.
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
// 번호 반환한거 받음. //( IPv4를 쓸거다, TCP 통신을 할거다, TCP 프로토콜을 의미)
		// PF_INET : AF_INET와 같지만 통상적 PF 씀. 메크로임.
		// SOCK_STREAM : 스트림, TCP 프로토콜의 전송 방식.
		// 0 : 정석이라면 IPPROTO_TCP가 들어가지만 첫, 두번째 매개변수를 기준으로
			// 0으로 자동지정해서 매칭한다. 
			// 즉, 자동 지정해주는 매크로인 IPPROTO_HOPOPTS 와 같다.
	

	// bind - IP, PORT, Protocol 선언. 을 위해선 구조체 하나 선언.
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
			// AF_INET : PF_INET와 똑같은 의미. P는 Protocol A는 Address
				// 근데 두개를 바꿔도 아무상관 없다. 단, 통상적으로 이렇게 쓴다.
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			// 주소를 넣어줌. : 소켓 바인드 할때 어떤 주소로 넣어줄꺼냐.
					// htonl 의 뜻 : host to network long = h to n l
						// host 방식의 오더 방식을 network 방식으로 바꾸고. l은 데이터 크기는 32비트다. 라는 뜻.
					// INADDR_ANY : 내 현재 컴퓨터의 아이피. 메크로는 왜? 계속 바뀌는 값이기에
	serv_addr.sin_port=htons(7989);
			// 위에랑 같이 host to network 로 바꿔라. s : 16비트 크기로.
			// atoi(argv[1]) : 로 쓴다면? 프로그램을 호출 할때마다 port 번호를 바꿀 수 있음.
				// 지금은 보기 쉽게 포트 번호로.

	// 바인드할 정보를 준비했고 이제 바인드 시작.
	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		// 껍대기 넣고, 지정한 옵션을 넣는다, 옵션에 대한 사이즈 넣어주고
			// (struct sockaddr *) 는 함수 내부적으로 처리 해줘서 필요없지만 warning 이 뜸으로 넣는걸로.
		// bind 함수는 오류가 날시 -1을 반환한다.
		printf("bind error\n");
	}


	// 이제 리슨한다.
	if(listen(serv_sock, 5) == -1){
		// 소켓을 넣고, 5 : listen 상태로 대기 할수 있는 고객 수.(접속할 수 있는 수가 아님.)
				// 5 : 즉, 만약 1명이 오래 작업하고 있으면 그 뒤 5명은 기다리고 있고 이 뒤에 6명 부터는 에러가 난다.
		printf("listen error");
	}
		
	
	// accept 과정.
	int clnt_sock;

	struct sockaddr_in clnt_addr;
	int clnt_addr_size; // socklen_t * 은 함수 내부의 인자형식 때문에, int와 같음.

	char buf[200];
	int recv_len = 0;

	pthread_t t_thread;
	pthread_mutex_init(&g_mutex, NULL);
	while(1){

		clnt_addr_size=sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
			// 리슨하는 과정은 계속 진행이 되고 있고 리슨이 끝날때마다 고객을 바로 수용 해준다.
			// 수용 해주면 소켓이 하나 튀어나온다.
				// 서버에서 소켓은 2종류가 생성되는데 서버소켓, 클라이언트 소켓이다. 
				// 클라이언트 소켓은 고객 한명당 소켓이 생성되는 것.
				// 사용은? 접속할땐 서버소켓으로 접속하고 실질적으로 데이터를 주고 받는건 클라이언트 소켓으로 주고 받는다.
			// &clnt_addr : serev_addr 와 똑같은 구조로 넘겨주는데 왜? 유저 정보를 받기 위해.
				// IP를 얻기 위함이 가장 중요한 목적.
					// 이것을 가지고 IP 차단, IP 추적 등으로 사용 가능


		/* 1명 유저 받기 
		

		// 쓰레드를 생성해야하는 이유는? 처리하면서 또 다른 손님을 받아야 되니까.
			// 없으면? 고객 1명만 받고 듣는거밖에 할 수 없음.

		// 데이터 받기
		while(1) { // read하는 과정은 항상 반복이 되니까.
			recv_len = read(clnt_sock, buf, 200);
			// recv_len : 얼마만큼 받아왔니? 를 리턴하고 데이터는 buf에 저장.
				// (.., 어떤 버퍼에 담을거냐, 버퍼의 최대사이즈)

			printf("recv : ");
			for(int i=0; i<recv_len; i++){
				printf("%02X ", (unsigned char)buf[i]);
			}
			printf("\n");
		}
		*/


		// 쓰레드로 유저 받기
		pthread_mutex_lock(&g_mutex);
			// g_clnt_count 고객이 들어오고 나가면 문제가 발생. -> mutex를 걸어야됨.
		g_clnt_socks[g_clnt_count++] = clnt_sock; // 클라이언트 소켓 하나 보관.
		pthread_mutex_unlock(&g_mutex);
			// 쓰레드 없으면? 필요없음.
		pthread_create(&t_thread, NULL, clnt_connection,(void *)clnt_sock);
	}

}
