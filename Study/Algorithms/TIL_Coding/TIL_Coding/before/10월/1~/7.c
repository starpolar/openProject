// ���, ����� �Ҽ� 2 / 10.7
// 	17103	������ ��Ƽ��
#include <stdio.h>

#define MAX 1000000
// ����, ����, Ž���� ���̴°� ����ȭ���..
int main() {

	int isPrime[MAX + 1] = { 0 };

	// 0�� 1�� �Ҽ��� �ƴ�
	isPrime[0] = isPrime[1] = 1;

	// �����佺�׳׽��� ü�� �Ҽ� �Ǻ�
	for (int i = 2; i * i <= MAX; i++) {
		if (!isPrime[i]) {
			for (int j = i * i; j <= MAX; j += i) {
				isPrime[j] = 1; // �Ҽ��� �ƴ��� ǥ��
			}
		}
	}

	int t;
	scanf("%d", &t);

	while (t--) {
		int n, count = 0;
		scanf("%d", &n);

		// n/2������ Ž�� (�ߺ� ��� ����)
		for (int i = 2; i <= n / 2; i++) {
			if (!isPrime[i] && !isPrime[n - i]) {
				// ���� �ѹ� ���̰� Ž���� �ѹ��ؼ� �� ����.
				count++;
			}
		}

		// ��� ���
		printf("%d\n", count);
	}

	return 0;

	//�����佺�׳׽��� ü�� �Ҽ����� 1,000,000 ���� ���ϰ�
	// ��ǲ ���� ��ŭ�� �Ҽ� �ϳ����� ���ؼ� �ϸ� �Ҽ������� O(n2)���⵵ �ϰ���.
	// �Ҽ��� 250,000����� �����ϸ� 62,500,000,000 ���� ���⵵. 0.5���� �ð��ȿ� �ɱ�?

	int eraNotPrime[MAX + 1] = { 1, 1, 0 }; // 1�� �ʱ�ȭ�� �� �� ����.
	
	for (int i = 2; i * i <= MAX; i++) {
		if (!(eraNotPrime[i])) {
			for (int j = i * i; j <= MAX; j += i) {
				eraNotPrime[j] = 1;
			}
		}
	}

	// �Ҽ� �迭�� �Ҽ��� ���� ����
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

		// �Ҽ� i�� �Ҽ� j�� ���� n�� �Ǵ� ��츦 ī����
		for (int i = 0; prime[i] <= n / 2; i++) {
			int a = prime[i];
			int b = n - a;
			// b�� �Ҽ����� Ȯ��
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
			if (max == prime[i]) { //if���� ������� �׻� Ž���ϰ� �����ϱ⿡ �Ҹ��� ����.
				break;
			}
			for (int j = i; j <= MAX / 2; j++) {
				if (prime[j] > n) {
					break;
				}
				if (prime[i] + prime[j] == n) {//Ž���� ��� ��츦 Ž����.
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