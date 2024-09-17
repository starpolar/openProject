#include <stdio.h>

int main() {//14215	세 막대, 기하: 직사각형과 삼각형
    int a, b, c, max, other;

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

    if (max < other) {
        printf("%d", a + b + c);
    }
    else {
        max = other - 1;
        printf("%d", max + other);
    }

    return 0;
}