// 2480	주사위 세개
// 조건문
#include <cstdio>

int main() {
    int x1, x2, x3, pay, top;
    scanf("%d %d %d", &x1, &x2, &x3);


    if (x1 == x2 && x2 == x3) {
        pay = 10000 + x1 * 1000;
    } else if (x1 == x2 || x1 == x3)
    {
        pay = 1000 + x1 * 100;
    } else if (x2 == x3)
    {
        pay = 1000 + x2 * 100;
    } else {
        top = x1;
        if (top <= x2) {
            top = x2;
        }
        if (top <= x3) {
            top = x3;
        }
        pay = top * 100;
    }
    
    printf("%d", pay);

    return 0;
}