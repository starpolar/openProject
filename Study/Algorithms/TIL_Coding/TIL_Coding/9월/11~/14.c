#include <stdio.h>

int main() {//9063	대지, 기하: 직사각형과 삼각형
    int n, x, y;
    int xmax = -10000, xmin = 10000, ymax = -10000, ymin = 10000;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);

        if (x < xmin) xmin = x;
        if (x > xmax) xmax = x;
        if (y < ymin) ymin = y;
        if (y > ymax) ymax = y;
    }

    int xres = xmax - xmin, yres = ymax - ymin;
    printf("%d", xres * yres);

    return 0;
}