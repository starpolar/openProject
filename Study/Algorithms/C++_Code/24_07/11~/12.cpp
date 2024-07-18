// 2753 윤년
// 나누기 조건문
#include <cstdio>

int main() {
    int year;
    scanf("%d", &year);

    if (year % 4 == 0 && year % 100 != 0) {
        printf("1");
    } else if (year % 400 == 0) {
        printf("1");
    } else {
        printf("0");
    }

    return 0;
}