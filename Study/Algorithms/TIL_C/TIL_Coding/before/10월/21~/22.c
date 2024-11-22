// 2506 점수계산 / 10.22
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int answer, cnt = 0, grade = 0;
	while (n--) {
		scanf("%d", &answer);
		if (answer) {
			cnt++;
			grade += cnt;
		}
		else {
			cnt = 0;
		}
	}
	printf("%d", grade);

	return 0;
}