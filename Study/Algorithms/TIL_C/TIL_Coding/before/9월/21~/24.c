#include <stdio.h>
// ���Ʈ ���� / 9.24

int main() {
	// ������� �����ڷ� �����ؼ� n(������) ���� �ɶ����� ���� ����.
	// n�������� ������ �� �ǹ̰� �ִ�.
	// �ݺ��ؼ� �����ڰ��� ���ö����� ã�� ��� �� ����, ������ ������ 0 ��ȯ�� ����.
	int n;
	scanf("%d", &n);

	int rest, sum;
	for (int i = 1; i < n; i++) {
		sum = i; // �������� i�� ���ؾߵǴ� �̸� �����ص���.
		rest = i;
		while (rest > 0) {
			sum += rest % 10; // ������ ���� �ٷ� ��ĥ �� ����.
			rest /= 10;
		}

		if (sum == n) {
			printf("%d", i);
			return 0;
		}
	}
	printf("0");

	return 0;
}

//int decom(int m);
//
//int main() {//2231	������
//	// 1�ڸ��� ���°� %10 ���� �� �� �ְ� while�� ������.
//	int n = 0;
//	scanf("%d", &n);
//	
//	int cnt = 0;
//	for (; ;) {
//		cnt++;
//		/*if (cnt == 198) {
//			printf("debug\n");
//		}*/
//		if (cnt < 10) {
//			int res = cnt * 2;
//			if (res == n) {
//				printf("%d", cnt);
//				return 0;
//			}
//			else if (cnt >= n) {
//				printf("0");
//				return 0;
//			}
//		}
//		else {
//			int detmp = decom(cnt);
//			int res = detmp + cnt;
//			if (res == n) {
//				printf("%d", cnt);
//				return 0;
//			}
//			else if (cnt >= n) {
//				printf("0");
//				return 0;
//			}
//		}
//	}
//}
//
//int decom(int m) {
//	/*if (m == 198) {
//		printf("debug\n");
//	}*/
//	double tmp = m * 0.1 + 0.05, tmpRe;
//	int rest = m * 0.1, restSum = 0;
//
//	for (; ;) {
//		tmpRe = tmp - rest;
//		tmpRe *= 10;
//		restSum += tmpRe;
//
//		if (rest == 0) break;
//
//		tmp *= 0.1;
//		rest *= 0.1;
//	}
//
//	return restSum;
//}