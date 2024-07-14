// 	2525	오븐 시계
// 시간, 조건문
#include <cstdio>

int main() {
    int h, m, t;
    scanf("%d %d", &h, &m);
    scanf("%d", &t);

    m += t;
    if (m >= 60) {
        int m_x = m / 60;
        for (int i = 0; i < m_x; i++) {
            h++;
        }
        m = m % 60;
        if (h >= 24) {
            h -= 24;
        }
    }

    printf("%d %d", h, m);

    return 0;
}