// ���, ����� �Ҽ� 2 / 10.1
// 13241	�ּҰ����
#include <stdio.h>

long long gcd(long long a, long long b);

int main() {

	// ��Ŭ���� ȣ���� :
	// r = a % b, r == 0 b�� �ִ�����(GCD)
	// r != 0 �̸� a = b, b = r �ٲ㼭 �ٽ� �ݺ�
	long long a, b;
	scanf("%lld %lld", &a, &b);
	 
	// �ּ� ����� : a * b / gcd
	printf("%lld", a * b / gcd(a, b));

	return 0;
}

long long gcd(long long a, long long b) {
	while (b) { // b�� ������ r�̵Ǹ� 0�̵ǰ� a�� b���Ǵ°� �̿��ؼ� ����ȭ
		long long r = a % b;
		a = b;
		b = r;
	}

	return a;
}