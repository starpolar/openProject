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

	int gap[100000] = { 0 };
	for (int i = 0; i < n - 1; i++) {
		gap[i] = arr[i + 1] - arr[i];
	}

	int gcdRe = gap[0];
	for (int i = 1; i < n - 1; i++) { 
		gcdRe = gcd(gcdRe, gap[i]);
	}// 모든 거리를 포함해서 최대공약수를 구해야 정답으로 인정됨.
	// 반례 4 0	4 10 18


	/*int min = 1000000000, max=0;
	for (int i = 0; i < n-1; i++) {
		int tmp = arr[i + 1] - arr[i];
		if (tmp < min) {
			min = tmp;
		}
		if (tmp > max) {
			max = tmp;
		}
	}*/

	// 범위의 gcd값을 각 거리마다 계산.

	//int gapGcd = gcd(max, min);
	int res=0;
	for (int i = 0; i < n-1; i++) {
		int tmp = arr[i + 1] - arr[i];
		res += tmp / gcdRe - 1;
	}


	/*int res = arr[n-1] / gcd(max, min) - n;
	if (arr[n-1] % 2 == 1 && res % 2 == 0) {
		res++;
	}*/

	printf("%d", res);

	return 0;
}
// 다시 로직을 재 정의 해보면
// 사이의 거리를 모두 구하고
// 모든 거리들의 gcd를 구하고
// 각 거리마다 gcd 로 나누고 -1 을 해 각 거리의 필요한 나무 갯수를 도출 가능.

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}