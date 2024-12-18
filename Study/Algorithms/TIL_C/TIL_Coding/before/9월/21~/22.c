//#include <stdio.h>
//// 시간 복잡도 / 9.22
//int main() {//24367 알고리즘 수업 - 알고리즘의 수행 시간 6
//	// 1. n-2 2. i+1, n-1 3. j+1
//	// ex)7 일때 1. n-2=5회 2. 6까지 i-1회 3. n까지 i-1회
//	// 1. 5회 2. 5 4 3 2 1 3. 5(3 4 5 6 7)=5회 4=4회
//	// 2번째 루프의 실행 횟수를 모두 더한것과 같다 = 15+10+6+3+1
//	// = n-2의 자연수를 역순으로 -1씩 줄여가며 더한것과 같다.
//
//	// ex)6 일때 1. 4회 2. 4 3 2 1 = 10+6+3+1
//	// 규칙이 숫자가 줄 때 자연수의 합을 더하는 단위도 비례해서 줄음. = 루프로 처리하자.
//
//	long long n, sum = 0;
//	scanf("%lld", &n);
//
//	if (n <= 2) {
//		printf("0\n3");
//		return 0;
//	}
//	else {
//		for (int i = 3; i <= n; i++) { 
//			// k(k+1)/2 : 등차수열의 합 공식.
//			// i-2(i-1)/2
//			sum += (i - 2) * (i - 1) / 2;
//          // 틀린 이유 : 오버플로우 : int i가 연산시에 담을 수 없어 오버플로우가
//          // 되니 long long i 로 바꾸면 오케이.
//		}
//	}	
//
//	printf("%lld\n3", sum);
//
//	return 0;
//}

#include <stdio.h>

int main() {
    long long n;
    scanf("%lld", &n);

    long long count = n * (n - 1) * (n - 2) / 6;
    printf("%lld\n3", count);
    // # 코드1이 실행되는 총 횟수는 n개의 원소 중에서 3개의 원소를 선택하는
    // 조합의 수와 동일하다. 따라서 조합수학의 C(n,3) 공식을 사용해
    // 모든 경우의 수를 알수있고 동일한 총 실행 횟수를 알 수 있다.

    // C(n.3) 공식이 성립되려면 : 중복이나 순서에 의한 차이가 없고 i < j < k를
    // 만족해야 함.

    return 0;
}
