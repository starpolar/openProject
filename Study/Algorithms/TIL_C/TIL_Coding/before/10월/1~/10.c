// ���, ����� �Ҽ� 2 / 10.10
// 	2164	 ī��2
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
} // ������ tail�� �ϳ��� �ø��� ���̸� �ǰ�
// ť�� head�� tail�� ��Ʈ�� �ϸ� �ȴ�.

int pop() {
    return queue[head++];
}

void push(int val) {
    queue[tail++] = val;
}