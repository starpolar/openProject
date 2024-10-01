#include <stdio.h>
#include <string.h>

int main() { // 2566	최댓값 / 2차원 배열
    int x, y, val, max = 0;
    int arr[9][9] = { 0 };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &val);
            arr[i][j] = val;
            if (val >= max) {
                max = val;
                x = i + 1;
                y = j + 1;
            }
        }
    }

    printf("%d\n", max);
    printf("%d %d", x, y);

    return 0;
}