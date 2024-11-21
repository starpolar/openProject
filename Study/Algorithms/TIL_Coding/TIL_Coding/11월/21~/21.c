// 5063 TGN / 11.21
#include <stdio.h>

int main() {

	int n, r, e, c;
	scanf("%d", &n);

	while (n--) {
		scanf("%d %d %d", &r, &e, &c);
		int profit = e - r - c;
		if (profit < 0) {
			printf("do not advertise\n");
		}
		else if (profit == 0) {
			printf("does not matter\n");
		}
		else {
			printf("advertise\n");
		}
	}

	return 0;
}