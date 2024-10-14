// 약수, 배수와 소수 2 / 10.12
// 28279	 덱 2
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int command = 0, head=1000000, tail=1000000,x=0;
	int dex[2000001] = { 0 };
	while (n--) {
		//printf("==\n");
		scanf("%d", &command);
		//printf("=====\n");
		switch (command) {
			case 1:
				scanf("%d", &x);
				dex[--head] = x;
				break;
			case 2:
				scanf("%d", &x);
				dex[tail++] = x;
				break;
			case 3:
				if ((tail - head)==0) {
					printf("-1\n");
				}
				else {
					printf("%d\n", dex[head++]);
				}
				break;
			case 4:
				if ((tail - head) == 0) {
					printf("-1\n");
				}
				else {
					printf("%d\n", dex[tail-1]);
					tail--;
				}
				break;
			case 5:
				printf("%d\n", tail - head);
				break;
			case 6:
				if (!(tail - head)) {
					printf("1\n");
				}
				else {
					printf("0\n");
				}
				break;
			case 7:
				if ((tail - head) == 0) {
					printf("-1\n");
				}
				else {
					printf("%d\n", dex[head]);
				}
				break;
			case 8:
				if ((tail - head) == 0) {
					printf("-1\n");
				}
				else {
					printf("%d\n", dex[tail-1]);
				}
				break;
			default :
				break;
		}
	}

	return 0;
}