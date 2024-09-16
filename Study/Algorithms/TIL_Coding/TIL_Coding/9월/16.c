#include <stdio.h>

int main() {//5073	삼각형과 세 변, 기하: 직사각형과 삼각형
    int a, b, c, max, other;

    for (; ;) {
        scanf("%d %d %d", &a, &b, &c);
        max = a;
        other = b + c;
        if (max < b) {
            max = b;
            other = a + c;
        }
        if (max < c) {
            max = c;
            other = a + b;
        }

        if (a == 0 && b == 0 && c == 0) break;
        else if (max >= other) printf("Invalid");
        else if (a == b && b == c && a == c) printf("Equilateral");
        else if (a == b || b == c || a == c) printf("Isosceles");
        else printf("Scalene");
        printf("\n");
    }

    return 0;
}