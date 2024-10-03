// 약수, 배수와 소수 2 / 10.3
// 2485 가로수
#include <stdio.h>

int gcd(int a, int b);

int main() {

	// input 값을 배열에 넣음.
	// 최소, 최대 범위값 2개 찾음.
	// 선별한 최소 범위값 두개의 gcd를 구함.
	// 범위값 gcd로 최대값에서 나누고 선언횟수 뺌.
	// 단, 시작값이 홀수일 경우엔 +1

	int n, arr[100000] = { 0 };
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int tmp;
		scanf("%d", &tmp);
		arr[i] = tmp;

	}

	/*int gap[100000] = { 0 };
	for (int i = 0; i < n - 1; i++) {
		gap[i] = arr[i + 1] - arr[i];
	}

	int gcdRe = gap[0];
	for (int i = 1; i < n - 1; i++) {
		gcdRe = gcd(gcdRe, gap[i]);
	}*/// 반례를 못찾았지만.. 모든 거리를 포함해서 최대공약수를 구해야 정답으로 인정됨.

	int min = 1000000000, max=0;
	for (int i = 0; i < n-1; i++) {
		int tmp = arr[i + 1] - arr[i];
		if (tmp < min) {
			min = tmp;
		}
		if (tmp > max) {
			max = tmp;
		}
	}

	// 범위의 gcd값을 각 거리마다 계산.

	int gapGcd = gcd(max, min);
	int res = 0;
	for (int i = 0; i < n - 1; i++) {
		int tmp = arr[i + 1] - arr[i];
		res += tmp / gapGcd - 1;
	}


	int res = arr[n-1] / gcd(max, min) - n;
	if (arr[n-1] % 2 == 1 && res % 2 == 0) {
		res++;
	}

	printf("%d", res);

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