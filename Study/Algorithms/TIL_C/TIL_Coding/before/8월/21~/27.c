#include <stdio.h>

int main() {
    int a, b;

    while (1) {
        // 두 수를 입력받습니다.
        scanf("%d %d", &a, &b);

        // 입력이 0 0이면 프로그램을 종료합니다.
        if (a == 0 && b == 0) {
            break;
        }

        // 첫 번째 수가 두 번째 수의 약수인 경우
        if (b % a == 0) {
            printf("factor\n");
        }
        // 첫 번째 수가 두 번째 수의 배수인 경우
        else if (a % b == 0) {
            printf("multiple\n");
        }
        // 둘 다 아닌 경우
        else {
            printf("neither\n");
        }
    }

    return 0;
}
