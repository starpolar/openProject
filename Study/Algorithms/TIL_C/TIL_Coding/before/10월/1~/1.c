// 약수, 배수와 소수 2 / 10.1
// 13241	최소공배수
#include <stdio.h>

long long gcd(long long a, long long b);

int main() {

	// 유클리드 호제법 :
	// r = a % b, r == 0 b가 최대공약수(GCD)
	// r != 0 이면 a = b, b = r 바꿔서 다시 반복
	long long a, b;
	scanf("%lld %lld", &a, &b);
	 
	// 최소 공배수 : a * b / gcd
	printf("%lld", a * b / gcd(a, b));

	return 0;
}

long long gcd(long long a, long long b) {
	while (b) { // b가 마지막 r이되며 0이되고 a가 b가되는걸 이용해서 간소화
		long long r = a % b;
		a = b;
		b = r;
	}

	return a;
}