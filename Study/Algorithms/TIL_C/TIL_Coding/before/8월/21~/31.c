#include <stdio.h>

void convert_to_base(int n, int base) {
    char result[36]; // 결과를 저장할 배열, 최대 36자리 (2진법에서 10진수 최대 1000000000은 약 30자리)
    int index = 0;

    // 변환 작업
    // 즉, 나눈거에서 또 나누게 되니
    // 첫번째 나눈게 b^0 의 지수값과 같게 되고
    // 두번째는 b^1로 같게 되는것. 나머지는 자리값이 된다.
    while (n > 0) {
        int remainder = n % base;
        if (remainder < 10) {
            result[index++] = remainder + '0'; // 숫자일 경우
        }
        else {
            result[index++] = remainder - 10 + 'A'; // 문자일 경우
        }
        n /= base;
    }

    // 역순으로 출력
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", result[i]);
    }
    printf("\n");
}

int main() {
    int N, B;
    scanf("%d %d", &N, &B);
    convert_to_base(N, B);
    return 0;
}
