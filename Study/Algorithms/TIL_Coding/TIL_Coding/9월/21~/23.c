#include <stdio.h>
// 브루트 포스 / 9.23
int main() {//2798	블랙잭
	int n, m, sum = 0, res = 0, tmp;
	scanf("%d %d", &n, &m);
	int card[101] = { 0 };

	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		card[i] = tmp;
	}

	for (int i = 0; i < n; i++) {
		sum = 0;
		for (int j = i+1; j < n; j++) {
			for (int k = j+1; k < n; k++) {
				sum = card[i] + card[j] + card[k];
				if (sum == m || res == m) {
					printf("%d", m);
					return 0;
				}
				if (sum < m && sum > res) res = sum;
				else if (sum >= m && sum < res) res = sum;
			}
		}
	}

	printf("%d", res);

	return 0;
}