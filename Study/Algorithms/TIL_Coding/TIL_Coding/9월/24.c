#include <stdio.h>
// 브루트 포스 / 9.24

int main() {
	// 순서대로 분해자로 대입해서 n(생성자) 값이 될때까지 순차 연산.
	// n전까지만 대입할 때 의미가 있다.
	// 반복해서 생성자값이 나올때까지 찾고 출력 후 종료, 끝까지 없으면 0 반환후 종료.
	int n;
	scanf("%d", &n);

	int rest, sum;
	for (int i = 1; i < n; i++) {
		sum = i; // 마지막에 i를 더해야되니 미리 선언해도됨.
		rest = i;
		while (rest > 0) {
			sum += rest % 10; // 나머지 값을 바로 합칠 수 있음.
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
//int main() {//2231	분해합
//	// 1자리씩 빼는건 %10 으로 할 수 있고 while로 가능함.
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