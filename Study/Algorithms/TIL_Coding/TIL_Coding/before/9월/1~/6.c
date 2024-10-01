#include <stdio.h>

int main() {//2501	약수 구하기 / 약수, 배수와 소수
    int n, k, cnt = 0;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (cnt == k) { // k는 몇번째 약수니까, cnt 즉, 약수의 순서가 k번째라면 약수 i를 출력.
                printf("%d", i);
                return 0;
            }
        }
    }
    printf("%d", 0);


    return 0;
}
