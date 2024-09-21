#include <stdio.h>

int main() {//10101	삼각형 외우기, 기하: 직사각형과 삼각형
    int a, b, c, sum;
    scanf("%d %d %d", &a, &b, &c);

    sum = a + b + c;
    if (sum != 180) printf("Error");
    else if (a == 60 && b == 60 && c == 60) printf("Equilateral");
    else if (a == b || b == c || a == c) printf("Isosceles");
    else printf("Scalene");

    return 0;
}