#include <stdio.h>
#include <pthread.h> // 쓰려면 gcc thread.c -lpthread. 즉, 컴파일 시 라이브러리 참조해야됨.
                        // libpthread.so 라는 파일이 있는걸 -lpthread로 참조함.
                        // 왜 이렇게 해야할까? 그냥 리눅스의 규칙이다.
                    // pthread가 없는 경우도 있다. 그땐? 파일은 크로스 컴파일해서 사용하는 경우도 있다.

int a=0;
pthread_mutex_t mutex;
void * thread1(void * arg) { // void는 무반환, void 포인터는 무엇이든 반환함.
    // 이름은 임의로, 반환은 정해진 형식인 void * 로.

    printf("arg : %d\n", (int)arg);

    while(1){

        pthread_mutex_lock(&mutex);
        printf("thread%d a[%d]\n",(int)arg, ++a);
        pthread_mutex_unlock(&mutex);
        // mutex로 크리티컬 영역 문제를 해결했다.
            // java의 싱크로나이즈? 와 똑같은 개념이다.
        sleep(2);

    }

    return NULL;
} 


int main() {

    // main 프로세스 안에 쓰레드를 하나 생성.
    pthread_t s_thread[2]; // 윈도우에선 핸들이라 불러서 즉,  쓰레드 핸들.
    // 이 쓰레드를 좌지우지 할 수 있는 것.
    int id1 = 77;
    int id2 = 88;

    pthread_mutext_init(&mutex, NULL); // mutex 객체 초기화.
            // (정보넣을곳, 옵션(NULL은 fast))
            // mutex도 memory lick이 일어나므로 반환을 해줘야한다.


    pthread_create(&s_thread[0], NULL, thread1, (void *)id1);
        // (쓰레드 생성 시 정보를 넣을 곳, 옵션을 넣는곳, 쓰레드를 생성할 함수, 함수에 넘겨줄 인자)
    pthread_create(&s_thread[1], NULL, thread1, (void *)id2);
    
    pthread_join(s_thread[0],NULL);
        // join이 없으면 return으로 가서 main 프로세스가 바로 끝남.
        // 그래서 join을 하면 main이 join이 끝날때까지 기다려줌.
    pthread_join(s_thread[1],NULL);

    while(1){ // join과 같은 작용을 함.

        printf(" main loop\n"); // 쓰레드 하나를 더 쓰는 효과를 낼 수 있음.
        sleep(1);

    }



    return 0;
}