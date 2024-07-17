// 2739 구구단
// 반복문
#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= 9; i++) {
        int answer = n * i;
        printf("%d * %d = %d\n", n, i, answer);
    }

    return 0;
}