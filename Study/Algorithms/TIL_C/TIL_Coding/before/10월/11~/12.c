// 약수, 배수와 소수 2 / 10.12
// 11866	 요세푸스 문제 0
#include <stdio.h>

int main() {

	int n = 7, k = 3;
	scanf("%d %d", &n, &k);

	int arr[1000] = { 0 };
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	} // 값을 입력 안하고 0 과 1로 제거 됬는지만 구분하고
	// reIdx를 제거된 수로 합쳐서 while문을 하나 줄일 수도 있다.

	int res[1002] = { 0 };
	int reIdx=0,idx = -1,cnt=0;
	int tmp = n;
	while (tmp--) {
		cnt = 0;
		while (1) {
			idx++;
			if (idx >= n) {
				idx = 0;
			}
			if (arr[idx] != 0) {
				cnt++;
				if (cnt == k) {
					res[reIdx++] = arr[idx];
					arr[idx] = 0;
					break;
				}
			}
		}
	}

	printf("<");
	for (int i = 0; i < n; i++) {
		printf("%d", res[i]);
		if (res[i + 1]) {
			printf(", ");
		} // res 배열을 작게 선언해서 문제였음.
		// 아래처럼 마지막에서 하나전까지만 출력해도 됨.
		/*if (i != n - 1) {
			printf(", ");
		}*/
	}
	printf(">");

	return 0;
}