// ���, ����� �Ҽ� 2 / 10.8
// 13909	 â�� �ݱ�
#include <stdio.h>
#include <math.h>

//int count_divisors(int);

int main() {

	// ����� ������ Ȧ���϶��� ���� ������
	// ����� ������ Ȧ���� ���� ���������� �ۿ� ����..
	// ���� �������� ���ϴ� ����� Cǥ���Լ��� sqrt()����
	// sqrt()�� ���������� ��ġ�ؼ������ CPU ����ȭ�� ���ִ� �Լ��� ���������ϱ� ��ƴ�.

	long long n, cnt = 0;
	scanf("%lld", &n);

	for (int i = 1; i * i <= n; i++) {
		cnt++;
	}

	printf("%d", cnt);

	return 0;

	// �������� �ȱ��ϰ� n������ �������� ���� ����� ���ص� ������������ ���� �����µ� ��?
	
	// ����� �������� ���ϰ� ������ ���ϸ� ����� ���������� ������ �ȴ�.
	// ��? ������������ ���� �ᱹ 1^2, 2^2, 3^2 .. k^2 �� ���������� �Ǵϱ�
	// ����� ���� ū ���������ٸ� ���ϸ� �װ� ������ �ȴ�.
	// �׷��� ����� �������� ���Ѵ����� ������ ���ϸ� �װ� ���� ���� ������������ ���̰� ������ �ȴ�.
	long long N;
	scanf("%lld", &N);
	long long result = (long long)sqrt(N);
	printf("%lld\n", result);
	return 0;



	/*for (;;) {
		int a;
		printf("�Է� : __\b\b");
		scanf("%d", &a);
		printf("��� : %d\n", count_divisors(a));
		if (a == 0) break;
	}

	return 0;*/

	/*long long n, cnt=0;
	scanf("%lld", &n);
	
	for (int i = 1; i <= n; i++) {
		if (count_divisors(i) % 2 == 1) {
			cnt ++ ;
		}
	}

	printf("%d", cnt);

	return 0;*/

	/*char* nArr = (char*)malloc(sizeof(char)*2100000002);
	long long cnt = 1;
	for (long long i = 2; i <= n; i++) {
		for (long long j = i; j <= n; j += i) {
			if (nArr[j] == 0) {
				nArr[j] = 'c';
			}
			else {
				nArr[j] = 0;
			}
		}
		if (nArr[i] == 0) {
			cnt++;
		}
	}

	printf("%lld", cnt);

	free(nArr);

	return 0;*/
}

//int count_divisors(int N) {
//	int count = 1;
//	int divisor = 2;
//	int exponent;
//
//	while (divisor * divisor <= N) {
//		exponent = 0;
//		while (N % divisor == 0) {
//			N /= divisor;
//			exponent++;
//		}
//		if (exponent > 0) {
//			count *= (exponent + 1);
//		}
//		divisor++;
//	}
//	if (N > 1) {
//		count *= 2; // ���� N�� �Ҽ��� ���
//	}
//	return count;
//}