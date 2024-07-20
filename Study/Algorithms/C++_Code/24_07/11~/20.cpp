// 25304 영수증
// 반복문
#include <cstdio>

int main() {
    long long total, cnt = 0;
    int n;
    scanf("%d", &total);
    scanf("%d", &n);
    printf("total : %d\n", total);

    for (int _ = 0; _ < n; _++) {
        long long a = 0, b = 0;
        scanf("%d %d", &a, &b);
        cnt += a * b;
        printf("%d and %d\n", cnt, _);
    }
    if (total == cnt) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}