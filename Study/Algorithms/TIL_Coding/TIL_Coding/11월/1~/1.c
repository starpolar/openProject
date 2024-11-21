// 11719 그대로 출력하기 2 / 11.01
#include <stdio.h>

int main() {

	char buf[150] = "";
	while (gets(buf) != NULL) {
		printf("%s\n", buf);
	}

	return 0;
}