#include <stdio.h>

int main() {
	char s[1000];
	scanf("%s", &s);
	int i;
	scanf("%d", &i);
	printf("%c", s[i - 1]);

	return 0;
}