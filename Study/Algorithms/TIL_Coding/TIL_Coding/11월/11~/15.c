// 5565 ¿µ¼öÁõ / 11.15
#include <stdio.h>

int main() {

	int n = 9, total;
	scanf("%d", &total);
	int price;
	while (n--) {
		scanf("%d", &price);
		total -= price;
	}
	printf("%d", total);

	return 0;
}