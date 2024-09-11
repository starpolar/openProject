#include <stdio.h>

int main() {//2292	벌집 / 일반 수학 1
    int n, hexagonMin = 1, hexagonMax = 1, roomCnt = 1, multiple = 6;
    scanf("%d", &n);

    for (; ;) {
        if (hexagonMin <= n && n <= hexagonMax) {
            printf("%d", roomCnt);
            break;
        }
        hexagonMax += multiple;
        hexagonMin = hexagonMax - (multiple - 1);
        multiple += 6;
        roomCnt++;
    }

    return 0;
}