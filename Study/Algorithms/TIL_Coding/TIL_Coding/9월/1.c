#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int sideLength = pow(2, n) + 1;  // 한 변에 있는 점의 수
    int totalPoints = sideLength * sideLength;  // 전체 점의 수

    printf("%d\n", totalPoints);

    return 0;
}
