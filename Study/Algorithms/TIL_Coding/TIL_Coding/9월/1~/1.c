#include <stdio.h>
#include <math.h>

int main() {
    int n, jisu = 1;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        jisu *= 2;
    }
    int sideLength = jisu + 1;  // 한 변에 있는 점의 수
    int totalPoints = sideLength * sideLength;  // 전체 점의 수

    printf("%d\n", totalPoints);

    return 0;
}
