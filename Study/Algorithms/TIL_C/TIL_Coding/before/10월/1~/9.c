// 약수, 배수와 소수 2 / 10.9
// 18258	 큐 2
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 2000000

int queue[MAX_SIZE];
int head = 0, tail = 0;

int main() {
    int N;
    scanf("%d", &N);
    char command[6];
    int x;

    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        if (strcmp(command, "push") == 0) {
            scanf("%d", &x);
            queue[tail++] = x;
        }
        else if (strcmp(command, "pop") == 0) {
            if (head == tail) {
                printf("-1\n");
            }
            else {
                printf("%d\n", queue[head++]);
            }
        }
        else if (strcmp(command, "size") == 0) {
            printf("%d\n", tail - head);
        }
        else if (strcmp(command, "empty") == 0) {
            printf("%d\n", (head == tail) ? 1 : 0);
        }
        else if (strcmp(command, "front") == 0) {
            if (head == tail) {
                printf("-1\n");
            }
            else {
                printf("%d\n", queue[head]);
            }
        }
        else if (strcmp(command, "back") == 0) {
            if (head == tail) {
                printf("-1\n");
            }
            else {
                printf("%d\n", queue[tail - 1]);
            }
        }
    }
    return 0;
}
