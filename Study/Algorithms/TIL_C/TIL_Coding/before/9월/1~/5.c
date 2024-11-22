//#include <stdio.h>
//
//int main() {//2869	달팽이는 올라가고 싶다 / 일반 수학 1
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

    // (V - A)를 (A - B)로 나누고, 마지막 날 더하기
    //int day = (V - B - 1) / (A - B) + 1;
    int day = (V - A) / (A - B) + 1;

    printf("%d\n", day);

    return 0;
} // 그냥, 논리를 수학적으로 계산할 수 있다 정도로 정의하자.
