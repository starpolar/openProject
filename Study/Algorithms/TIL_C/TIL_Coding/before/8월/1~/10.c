#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		char s[1000];
		scanf("%s", &s);
		int idx = strlen(s);
		printf("%c%c\n",s[0], s[idx - 1]);
	}

	return 0;
}