// 11382 꼬마 정민
#include <cstdio>

int main() {
    long long x1, x2, x3;
    scanf("%lld %lld %lld", &x1, &x2, &x3);
    printf("%lld", x1+x2+x3);

    return 0;
}

/* 
char : 1 바이트, -128 ~ 127
short : 2 바이트, -32,768 ~ 32,767
int / long : 4 바이트, -2,147,483,648 ~ 2,147,483,647
long long : 8 바이트, -9,223,372,036,854,775,808 ~ 9,223,372,036,854,775,807
 */