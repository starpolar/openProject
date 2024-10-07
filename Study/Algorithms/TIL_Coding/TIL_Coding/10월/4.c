// 약수, 배수와 소수 2 / 10.4
// 4134	다음 소수

// n 만큼 인풋을 받아 배열에 넣으며 배열을 정렬하고
// 배열하나를 구한후 정답 소수를 구했으면 인덱스 값을 ++ 하며 출력.

#include <stdio.h>
#include <math.h>

// 소수 판별 함수: 제곱근까지만 나눠서 확인
// : 짝수는 모두 소수가 아니고 홀수인 제곱근으로 나누어 떨어지는 지만 확인해보고 아니면 소수임.
int is_prime(long long n) {
    if (n < 2) return 0; // 2보다 작은 수는 소수가 아님
    if (n == 2) return 1; // 2는 소수
    if (n % 2 == 0) return 0; // 짝수는 소수가 아님

    long long sqrt_n = (long long)sqrt(n);
    for (long long i = 3; i <= sqrt_n; i += 2) {
        if (n % i == 0) return 0; // 나누어 떨어지면 소수가 아님
    }
    return 1; // 소수임
}

// 다음 소수 찾기
long long next_prime(long long n) {
    if (n <= 1) return 2; // 1 이하의 경우 2가 첫 소수
    long long candidate = n;

    if (candidate % 2 == 0) candidate++; // 짝수면 1을 더해서 홀수로 만듦
    else candidate += 2; // 홀수면 다음 홀수로 이동

    while (!is_prime(candidate)) {
        candidate += 2; // 소수가 아니면 다음 홀수로 이동
    }

    return candidate;
}

int main() {
    int t;
    scanf("%d", &t); // 테스트 케이스 개수 입력

    while (t--) {
        long long n;
        scanf("%lld", &n); // 주어진 수 입력
        printf("%lld\n", next_prime(n));
    }

    return 0;
}
