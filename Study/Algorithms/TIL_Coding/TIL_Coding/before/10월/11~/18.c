// 2953 나는 요리사다 / 10.18
#include <stdio.h>

int main() {

	int sum, point, idx, maxSum=0, maxIdx;
	for (int i = 0; i < 5; i++) {
		sum = 0;
		for (int j = 0; j < 4; j++) {
			scanf("%d", &point);
			sum += point;
		}
		if (sum > maxSum) {
			maxSum = sum;
			maxIdx = i+1;
		}
	}

	printf("%d %d", maxIdx, maxSum);

	return 0;
}