#include <stdio.h>

int main() {//15894	수학은 체육과목 입니다, 기하: 직사각형과 삼각형
    long long N;
    scanf("%lld", &N);  // 입력값을 받습니다.
    printf("%lld", N * 4);  // 둘레는 4 * N 이므로 출력합니다.
    return 0;
}