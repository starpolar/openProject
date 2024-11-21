// 10886 0 = not cute / 1 = cute / 11.13
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int inp, cute=0, ncute=0; 
	while (n--) {
		scanf("%d", &inp);
		if (inp) cute++;
		else ncute++;
	}
	if (cute > ncute) printf("Junhee is cute!");
	else printf("Junhee is not cute!");

	return 0;
}