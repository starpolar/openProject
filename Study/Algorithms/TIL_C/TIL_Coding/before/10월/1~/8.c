// 약수, 배수와 소수 2 / 10.8
// 13909	 창문 닫기
#include <stdio.h>
#include <math.h>

//int count_divisors(int);

int main() {

	// 약수의 개수가 홀수일때만 문이 열리고
	// 약수의 개수가 홀수인 경우는 완전제곱수 밖에 없다..
	// 완전 제곱수를 구하는 방법은 C표준함수인 sqrt()으로
	// sqrt()은 내부적으로 수치해석기법과 CPU 최적화가 되있는 함수라 직접구현하기 어렵다.

	long long n, cnt = 0;
	scanf("%lld", &n);

	for (int i = 1; i * i <= n; i++) {
		cnt++;
	}

	printf("%d", cnt);

	return 0;

	// 제곱근을 안구하고 n까지의 제곱근의 수가 몇개인지 구해도 완전제곱수의 수가 나오는데 왜?
	
	// 어떤수의 제곱근을 구하고 정수만 취하면 어떤수의 완전제곱근 갯수가 된다.
	// 왜? 완전제곱근의 수는 결국 1^2, 2^2, 3^2 .. k^2 의 등차수열이 되니까
	// 어떤수의 가장 큰 완전제곱근만 구하면 그게 갯수가 된다.
	// 그래서 어떤수의 제곱근을 구한다음에 정수만 취하면 그게 가장 높은 완전제곱근의 수이고 갯수가 된다.
	long long N;
	scanf("%lld", &N);
	long long result = (long long)sqrt(N);
	printf("%lld\n", result);
	return 0;



	/*for (;;) {
		int a;
		printf("입력 : __\b\b");
		scanf("%d", &a);
		printf("결과 : %d\n", count_divisors(a));
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
//		count *= 2; // 남은 N이 소수인 경우
//	}
//	return count;
//}