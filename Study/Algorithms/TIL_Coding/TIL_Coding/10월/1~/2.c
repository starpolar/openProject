// 약수, 배수와 소수 2 / 10.2
// 1735	분수 합
#include <stdio.h>

int gcd(int a, int b);
int lcm(int a, int b);

int main() {

	int xa, xb, ya, yb;
	scanf("%d %d %d %d", &xa, &xb, &ya, &yb);

	int reb = lcm(xb, yb);
	xa *= reb / xb;
	ya *= reb / yb;
	int rea = xa + ya;

	/*int cnt=0;
	while (cnt != 12) {
		cnt = 0;
		for (int i = 13; i >= 2; i--) { // 13보다 큰 소수는 무수히 많다..
			if (rea % i == 0 && reb % i == 0) {
				rea /= i;
				reb /= i;

			}
			else cnt++;
		}
	}*/

	int regcd = gcd(rea, reb);
	rea /= regcd;
	reb /= regcd;

	printf("%d %d", rea, reb);

	return 0;
}

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}

	return a;
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
}