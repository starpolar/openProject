// 2884 알람 시계
// 조건문

#include <cstdio>

int main() {
    int h, m;
    scanf("%d %d", &h, &m);

    if (m - 45 < 0) {
        if (h - 1 < 0) {
            h = 24 - 1;    
        } else {
            h -= 1;
        }        
        int x = 45 - m;
        m = 60 - x;
    } else {
        m -= 45;
    }
    printf("%d %d", h, m);

    return 0;
}