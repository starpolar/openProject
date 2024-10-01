#include <stdio.h>
// 브루트 포스 / 9.28
int main() {//2839	설탕 배달
    // 3으로 먼저 나누다가 해야 맞아떨어짐.
    int n;
    scanf("%d", &n);

    int count = 0; // 봉지 수

    while (n > 0) {
        if (n % 5 == 0) { // 5로 나누어떨어지면
            count += n / 5;
            n = 0;
            break;
        }
        n -= 3; // 3kg 봉지 하나 사용
        count++;
    }

    if (n < 0) { // 정확히 나눌 수 없는 경우
        printf("-1\n");
    }
    else {
        printf("%d\n", count);
    }

    return 0;
}