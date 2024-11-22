#include <stdio.h>
// 브루트 포스 / 9.25
int main() {//19532	수학은 비대면강의입니다
	
	// 또는 소거법을 사용하며 할 때 최소공배수를 사용해서 풀이 가능.
	int a, b, c; // 첫 번째 방정식의 계수
	int d, e, f; // 두 번째 방정식의 계수
	int x, y;    // 해를 저장할 변수
	int denominator; // 분모

	// 계수 입력
	//printf("첫 번째 방정식의 계수 a, b, c를 입력하세요 (예: 2 5 8): ");
	scanf("%d %d %d", &a, &b, &c);

	//printf("두 번째 방정식의 계수 d, e, f를 입력하세요 (예: 3 -4 -11): ");
	scanf("%d %d %d", &d, &e, &f);

	// 소거법 적용
	// x를 소거하기 위해 첫 번째 방정식에 d를 곱하고, 두 번째 방정식에 a를 곱함
	int a1 = a * d;
	int b1 = b * d;
	int c1 = c * d;

	int a2 = d * a;
	int b2 = e * a;
	int c2 = f * a;

	// 두 방정식을 빼서 y를 구함
	int numerator_y = c1 - c2;
	int denominator_y = b1 - b2;

	if (denominator_y == 0) {
		//printf("해를 구할 수 없습니다. (분모가 0입니다)\n");
		return 0;
	}

	y = numerator_y / denominator_y;

	// y 값을 이용하여 x 값을 구함
	if (a != 0) {
		x = (c - b * y) / a;
	}
	else if (d != 0) {
		x = (f - e * y) / d;
	}
	else {
		//printf("해를 구할 수 없습니다. (a와 d가 모두 0입니다)\n");
		return 0;
	}

	// 결과 출력
	//printf("x = %d, y = %d\n", x, y);
	printf("%d %d\n", x, y);

	return 0;


	// 연립 방정식은 크래머 공식을 통해서 풀이 가능!
	//int a, b, c, d, e, f;
	//scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
	//printf("%d %d", (c * e - b * f) / (a * e - b * d), (c * d - a * f) / (b * d - a * e));
	
	
	// 브루트 포스 방법.
	//int a, b, c, d, e, f;
	//scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	//int x, y;
	//for (x = -999; x <= 999; x++) {
	//	for (y = -999; y <= 999; y++) {
	//		if (a * x + b * y == c && d * x + e * y == f) {
	//			printf("%d %d\n", x, y);
	//			return 0; // 해를 찾으면 프로그램 종료
	//		}
	//	}
	//}
	
	
	// Fail..
	//float a, b, c, d, e, f;
	//scanf("%f %f %f %f %f %f", &a, &b, &c, &d, &e, &f);

	//// ax + by = c
	//// x = (c / (a+b+y))-1 는 오답 // 나누면은 한쪽만 나누는게 아니라 모든 항을 나눠야지 맞구나.
	//
	//// x = (c - b * y) / a
	//// y = (c - a * x) / b

	//// x = (c - b * ( (c - a * x) / b) ) / a
	//int xre, yre, x2re, y2re;
	//for (int x = -999; x <= 999; x++) {
	//	if (b == 0 || e == 0 || a == 0 || d == 0) break;
	//	yre = (int)(c - a * x) / b;
	//	if (x == (c - b * yre) / a && a != 0) {
	//		xre = x;
	//		for (int x2 = -999; x2 <= 999; x2++) {
	//			/*if (x == 2) {
	//				printf("debug");
	//			}*/
	//			y2re = (int)(f - d * x) / e;
	//			if (x2 == (f - e * y2re) / d) {
	//				x2re = x2;

	//				if (xre == x2re && yre == y2re) {
	//					printf("%d %d", x2re, y2re);
	//					return 0;
	//				}
	//			}
	//		}
	//	}
	//}
		
	return 0;
}