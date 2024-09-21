#include <stdio.h>

int main() {//3009	네 번째 점, 기하: 직사각형과 삼각형
    int x, y, x1 = 0, x2 = 0, y1 = 0, y2 = 0, resx, resy;

    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &x, &y);
        if (x1 == x) x1 = -1;
        else if (x2 == x) x2 = -1;
        else if (x1 == 0) x1 = x;
        else if (x2 == 0) x2 = x;
        
        if (y1 == y) y1 = -1;
        else if (y2 == y) y2 = -1;
        else if (y1 == 0) y1 = y;
        else if (y2 == 0) y2 = y;
    }
    
    resx = x1;
    resy = y1;
    if (x1 == -1) resx = x2;
    if (y1 == -1) resy = y2;

    printf("%d %d", resx, resy);

    return 0;
}