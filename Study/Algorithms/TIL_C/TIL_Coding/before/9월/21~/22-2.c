//#include <stdio.h>
//// 시간 복잡도 / 9.22
//int main() {//24313	알고리즘 수업 - 점근적 표기 1
//	long long a1, a0, c, n0;
//	scanf("%lld %lld %lld %lld", &a1, &a0, &c, &n0);
//
//	if (a1 * n0 + a0 <= c * n0) printf("1");
//	else printf("0");
//
//	return 0;
//}

#include <stdio.h>

int main() {
    long long a1, a0;
    long long c;
    long long n0;

    scanf("%lld %lld", &a1, &a0);
    scanf("%lld", &c);
    scanf("%lld", &n0);
    // a1 * n0 + a0 <= c * n0 이 식을 그대로 쓰면 안되는 이유는,
    // 단순히 n = n0 으로 가정하면 안 되는 이유다.
    // (ai-c) > 0 되면 n이 증가할 때 충족하지 못하는 경우의 수가 발생하므로 예외처리.

    // (0 ≤ |ai| ≤ 100) 에서 |ai| 의 뜻은? : 절대값.
    // 이는 ai가 음수이든 양수이든 절대값이 100 이하임을 나타냅니다.
    long long delta = a1 - c;

    if (delta <= 0) {
        long long left_side = delta * n0 + a0;
        if (left_side <= 0) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }
    else {
        printf("0\n");
    }

    return 0;
}
