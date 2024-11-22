// 약수, 배수와 소수 2 / 9.30
// 1934	최소공배수
#include <stdio.h>

// 최대공약수(GCD)를 구하는 함수
// 유클리드 호제법 사용.
// 유클리드 호제법(Euclidean Algorithm)은 
// 두 수의 **최대공약수(Greatest Common Divisor, GCD)**를 빠르게 구하는 알고리즘입니다. 
// 이 방법은 2,300년 전 그리스의 수학자 유클리드가 제시한 알고리즘으로,
// 두 수의 나머지를 이용하여 계산을 반복함으로써 최대공약수를 찾습니다
int gcd(int a, int b) {
	while (b != 0) {
		int temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

// 최소공배수(LCM)를 구하는 함수
int lcm(int a, int b) {
	return a * b / gcd(a, b);
}

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		// 최소공배수 출력
		printf("%d\n", lcm(a, b));
	}

	return 0;
}



#include <stdio.h>

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int a, b, res, multipSum = 1;
		scanf("%d %d", &a, &b);

		if (a == 1 || b == 1) {
			printf("%d\n", a * b);
			continue;
		}
		else if (a == b) {
			printf("%d\n", a);
			continue;
		}
		else {
			while (a > 0 && b > 0) {
				if (a % 2 == 0 && b % 2 == 0) {
					a /= 2;
					b /= 2;
					multipSum *= 2;
				}
				else if (a % 3 == 0 && b % 3 == 0) {
					a /= 3;
					b /= 3;
					multipSum *= 3;
				}
				else if (a % 5 == 0 && b % 5 == 0) {
					a /= 5;
					b /= 5;
					multipSum *= 5;
				}
				else if (a % 7 == 0 && b % 7 == 0) {
					a /= 7;
					b /= 7;
					multipSum *= 7;
				}
				else break;
			}
			printf("%d\n", a * b * multipSum);
		}
	}

	return 0;
}