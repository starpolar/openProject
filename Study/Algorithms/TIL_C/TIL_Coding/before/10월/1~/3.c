// ���, ����� �Ҽ� 2 / 10.3
// 2485 ���μ�
#include <stdio.h>

int gcd(int a, int b);

int main() {

	// input ���� �迭�� ����.
	// �ּ�, �ִ� ������ 2�� ã��.
	// ������ �ּ� ������ �ΰ��� gcd�� ����.
	// ������ gcd�� �ִ밪���� ������ ����Ƚ�� ��.
	// ��, ���۰��� Ȧ���� ��쿣 +1

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
	}// ��� �Ÿ��� �����ؼ� �ִ������� ���ؾ� �������� ������.
	// �ݷ� 4 0	4 10 18


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

	// ������ gcd���� �� �Ÿ����� ���.

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
// �ٽ� ������ �� ���� �غ���
// ������ �Ÿ��� ��� ���ϰ�
// ��� �Ÿ����� gcd�� ���ϰ�
// �� �Ÿ����� gcd �� ������ -1 �� �� �� �Ÿ��� �ʿ��� ���� ������ ���� ����.

int gcd(int a, int b) {
	while (b) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}