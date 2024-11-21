#include <stdio.h>

int reverse(int num) {
    int reversed = 0;

    // 숫자를 뒤집는 로직
    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }

    return reversed;
}

int main() { // 2908	상수 정답지.
    int a, b;

    // 두 개의 정수 입력
    scanf("%d %d", &a, &b);

    // 각각의 정수를 뒤집기
    int rev_a = reverse(a);
    int rev_b = reverse(b);

    // 더 큰 값을 출력
    if (rev_a > rev_b) {
        printf("%d\n", rev_a);
    }
    else {
        printf("%d\n", rev_b);
    }

    return 0;
}
