#include <stdio.h>
#include <math.h>

int main() {
    int n, jisu = 1;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        jisu *= 2;
    }
    int sideLength = jisu + 1;  // �� ���� �ִ� ���� ��
    int totalPoints = sideLength * sideLength;  // ��ü ���� ��

    printf("%d\n", totalPoints);

    return 0;
}
