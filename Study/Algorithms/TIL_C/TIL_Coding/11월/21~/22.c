// 10833 »ç°ú / 11.3
#include <stdio.h>

int main() {

	int n, stud, appl;
	scanf("%d", &n);

	int sum = 0;
	while (n--) {
		scanf("%d %d", &stud, &appl);
		int applCnt = appl / stud;
		int restAppl = appl - (applCnt * stud);
		sum += restAppl;
	}

	printf("%d", sum);

	return 0;
}