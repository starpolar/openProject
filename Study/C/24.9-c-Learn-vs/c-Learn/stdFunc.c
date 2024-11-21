#include <stdio.h>

char* strcpy(char* __restrict dst, const char* __restrict src);
size_t strlen(const char* s123);
int strcmp(const char* string1, const char* string2);

int main() {

	char dst[20] = "abcdef";
	char src[20] = "abcdfg";

	printf("%d", strcmp(dst, src));

	/*printf("before : %s\n", dst);
	strcpy(dst, src);
	printf("after : %s\n", dst);

	printf("%d", strlen(dst));*/

	return 0;
}

char* strcpy(char* __restrict dst, const char* __restrict src) {
	while (*src) {
		*dst++ = *src++;
	}

	while (*dst) { // src 이외에 값은 삭제.
		*dst++ = 0;
	}
}

size_t strlen(const char* s) {
	size_t cnt = 0;
	while (*s++) {
		cnt++;
	}
	return cnt;
}

int strcmp(const char* s1, const char* s2) {
	int len = 0;
	if (strlen(s1) > strlen(s2)) {
		len = strlen(s1);
	}
	else {
		len = strlen(s2);
	}

	while (len--) {
		if (*s1++ != *s2++) {
			return *--s1 - *--s2;
		}
	}

	return NULL;
}