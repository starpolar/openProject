#include <stdio.h>

int main() {//1193	분수찾기 / 일반 수학 1
    int x = 1, y = 1, X, nextX = 2, nextY = 2, cnt = 1;
    scanf("%d", &X);

    if (X == 1) {
        printf("%d/%d", x, y);
        return 0;
    }
    for (; ;) {
        x = 1;
        y = nextX;
        cnt++;
        for (int j = 0; j < nextX - 1; j++) {
            if (cnt >= X) break;
            x++;
            y--;
            cnt++;
        }
        nextX++;
        if (cnt >= X) break;

        x = nextX;
        y = 1;
        cnt++;
        for (int j = 0; j < nextX - 1; j++) {
            if (cnt >= X) break;
            x--;
            y++;
            cnt++;
        }
        nextX++;
        if (cnt >= X) break;
    }

    printf("%d/%d", x, y);

    return 0;
} // 나는 순서대로 찾은 것이였고,
// 더 단순화 할 수 있는 방법으로 대각선의 번호를 매기고, 대각선의 시작 숫자를 파악 하여 해결 가능.