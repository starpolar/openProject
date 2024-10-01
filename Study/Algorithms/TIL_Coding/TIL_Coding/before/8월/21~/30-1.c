#include <stdio.h>
#include <string.h>

int main() { //2745	진법 변환 / 2차원 배열
    char n[100];
    int b;
    scanf("%s %d", &n, &b);
    int x = strlen(n);
    unsigned long res = 0, jisu = 1;

    for (int i = 0; i < strlen(n); i++) {
        if (n[i] >= 'A') {
            for (int _ = 0; _ < x; _++) {
                jisu *= b - 1;
            }
            int a = (n[i] - 'A' + 10);
            res += a * jisu;
            x--;
        }
        else {
            res += (n[i] - '0') * (x-- * b);
        }
    }

    printf("%d", res);

    return 0;
}