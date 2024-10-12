// 약수, 배수와 소수 2 / 10.10
// 	2164	 카드2
#include <stdio.h>

int pop();
void push(int);

#define MAX 1000000
int queue[MAX] = { 0 };
int head = 0, tail = 0;


int main() {
    
    int n;
    scanf("%d", &n);
    
    int num = 1;
    while (n--) {
        queue[tail++] = num++;
    }

    while (1) {
        if ((tail - head) == 1) {
            printf("%d", queue[head]);
            break;
        }
        pop();
        push(pop());
    }

    return 0;
} // 스택은 tail을 하나씩 늘리고 줄이면 되고
// 큐는 head와 tail로 컨트롤 하면 된다.

int pop() {
    return queue[head++];
}

void push(int val) {
    queue[tail++] = val;
}