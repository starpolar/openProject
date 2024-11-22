#include <stdio.h>
#include <string.h>

int main() { // 10988	팰린드롬인지 확인하기 / 심화 1
	char s[101];
	scanf("%s", &s);
	
	int pel = 1, len = strlen(s) - 1;
	for (int i = 0; i < strlen(s) / 2; i++) {
		if (s[i] != s[len--]) pel = 0;
	}

	printf("%d", pel);

	return 0;
}