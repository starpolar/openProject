// 2083 럭비 클럽 / 10.15
#include <stdio.h>

int main() {

	while (1) {
		char name[100] = { 0 };
		int age, weight;
		scanf("%s %d %d", &name, &age, &weight);

		if (age == 0) break;

		printf("%s ", name);
		if (age > 17) {
			printf("Senior\n");
		}
		else if (weight >= 80) {
			printf("Senior\n");
		}
		else {
			printf("Junior\n");
		}
	}
	
	return 0;
}