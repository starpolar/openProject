#include <stdio.h>

int main() {//1085	���簢������ Ż��, ����: ���簢���� �ﰢ��
    int x, y, w, h;
    scanf("%d %d %d %d", &x, &y, &w, &h);

    int a = w - x, b = h - y;
    int min = a;
    if (min > b) min = b;
    if (min > x) min = x;
    if (min > y) min = y;

    printf("%d", min);

    return 0;
}