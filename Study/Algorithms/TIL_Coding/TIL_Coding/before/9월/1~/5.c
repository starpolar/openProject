//#include <stdio.h>
//
//int main() {//2869	�����̴� �ö󰡰� �ʹ� / �Ϲ� ���� 1
//    int a, b, v, cur = 0, day = 0;
//    scanf("%d %d %d", &a, &b, &v);
//
//    if (v % (a - b) != 0) {
//        day = (v / (a - b));
//        day++;
//    }
//    else {
//        day = (v / (a - b)) - b;
//    }
//
//    /*for (; ;) {
//        cur += a;
//        day++;
//        if (cur >= v) break;
//        cur -= b;
//    }*/
//
//    printf("%d", day);
//
//    return 0;
//}
//
#include <stdio.h>

int main() {
    int A, B, V;
    scanf("%d %d %d", &A, &B, &V);

    // (V - A)�� (A - B)�� ������, ������ �� ���ϱ�
    //int day = (V - B - 1) / (A - B) + 1;
    int day = (V - A) / (A - B) + 1;

    printf("%d\n", day);

    return 0;
} // �׳�, ���� ���������� ����� �� �ִ� ������ ��������.
