#include <stdio.h>

int main() { //2563	색종이
    int n; // 색종이의 수
    int paper[100][100] = { 0 }; // 100x100 도화지, 초기값은 모두 0
    int x, y; // 색종이의 좌표
    int count = 0; // 색종이가 붙여진 영역의 넓이

    // 색종이 수 입력
    scanf("%d", &n);

    // 각 색종이의 왼쪽 아래 좌표를 받아와 도화지에 표시
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);

        // 색종이의 크기는 10x10
        for (int j = x; j < x + 10; j++) {
            for (int k = y; k < y + 10; k++) {
                // 해당 영역을 1로 표시
                paper[j][k] = 1;
            }
        }
    }

    // 도화지에서 1로 표시된 영역의 수를 계산
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (paper[i][j] == 1) {
                count++;
            }
        }
    }

    // 결과 출력
    printf("%d\n", count);

    return 0;
}
