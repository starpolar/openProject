// 약수, 배수와 소수 2 / 10.7
// 	17103	골드바흐 파티션
#include <stdio.h>

#define MAX 1000000
// 저장, 선언, 탐색을 줄이는게 최적화방법..
int main() {

	int isPrime[MAX + 1] = { 0 };

	// 0과 1은 소수가 아님
	isPrime[0] = isPrime[1] = 1;

	// 에라토스테네스의 체로 소수 판별
	for (int i = 2; i * i <= MAX; i++) {
		if (!isPrime[i]) {
			for (int j = i * i; j <= MAX; j += i) {
				isPrime[j] = 1; // 소수가 아님을 표시
			}
		}
	}

	int t;
	scanf("%d", &t);

	while (t--) {
		int n, count = 0;
		scanf("%d", &n);

		// n/2까지만 탐색 (중복 계산 방지)
		for (int i = 2; i <= n / 2; i++) {
			if (!isPrime[i] && !isPrime[n - i]) {
				// 저장 한번 줄이고 탐색만 한번해서 더 빠름.
				count++;
			}
		}

		// 결과 출력
		printf("%d\n", count);
	}

	return 0;

	//에라토스테네스의 체로 소수들을 1,000,000 까지 구하고
	// 인풋 숫자 만큼을 소수 하나마다 더해서 하면 소수갯수의 O(n2)복잡도 일것임.
	// 소수가 250,000개라고 가정하면 62,500,000,000 번의 복잡도. 0.5초의 시간안에 될까?

	int eraNotPrime[MAX + 1] = { 1, 1, 0 }; // 1로 초기화를 할 수 없음.
	
	for (int i = 2; i * i <= MAX; i++) {
		if (!(eraNotPrime[i])) {
			for (int j = i * i; j <= MAX; j += i) {
				eraNotPrime[j] = 1;
			}
		}
	}

	// 소수 배열에 소수만 따로 저장
	int prime[MAX / 2] = { 0 }, primeCount = 0;
	for (int i = 2; i <= MAX; i++) {
		if (!eraNotPrime[i]) {
			prime[primeCount++] = i;
		}
	}

	int t;
	scanf("%d", &t);
	while (t--) {
		int n, cnt = 0;
		scanf("%d", &n);

		// 소수 i와 소수 j의 합이 n이 되는 경우를 카운팅
		for (int i = 0; prime[i] <= n / 2; i++) {
			int a = prime[i];
			int b = n - a;
			// b도 소수인지 확인
			if (!eraNotPrime[b]) {
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}

	return 0;



	int prime[MAX / 2] = { 0 }, index=0;
	for (int i = 2; i <= MAX + 1; i++) {
		if (!(eraNotPrime[i])) {
			prime[index] = i;
			index++;
		}
	}

	/*for (int i = 0; i < MAX/2; i++) {
		printf("%d=%d ", prime[i], i);
		if (i % 19 == 0) printf("\n");
	}
	return 0;*/

	int t;
	scanf("%d", &t);
	while (t) {

		int n, idx=0, cnt=0, max=-1;
		scanf("%d", &n);

		for (int i = 0; i <= MAX / 2; i++) {
			if (max == prime[i]) { //if문과 저장식이 항상 탐색하고 저장하기에 소모량이 많다.
				break;
			}
			for (int j = i; j <= MAX / 2; j++) {
				if (prime[j] > n) {
					break;
				}
				if (prime[i] + prime[j] == n) {//탐색이 모든 경우를 탐색함.
					cnt++;
					if (max < prime[j]) {
						max = prime[j];
					}
				}
			}
		}
		printf("%d\n", cnt);

		t--;
	}

	/*int t;
	scanf("%d", &t);
	while (t) {
		int n, cnt=0, max=0;
		scanf("%d", &n);
		
		for (int i = 3; i < n; i+=2) {
			if (max == i) {
				break;
			}
			if (eraNotPrime[i]) {
				continue;
			}
			for (int j = i+2; j < n; j+=2) {
				if (eraNotPrime[j]) {
					continue;
				}
				if ((i + j) == n) {
					cnt++;
					if (max < j) {
						max = j;
					}
				}
			}
		}
		printf("%d\n", cnt);

		t--;
	}*/

	return 0;
}