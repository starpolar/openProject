// 10953 A + B - 6 / 11.4
#include <stdio.h>

int sum(char a, char b) { // * 인자로 받았을때도 되는 이유는? 
	// a의 값을 주소로 치고 주소 연산으로 '0'을 뺀것을 int로 변환한 것. 
	// 즉, 운이 좋았을 뿐 정확한 연산은 아니다.
	int anum = a - '0';
	int bnum = b - '0';
	int c = anum + bnum;
	return c;
}

int main() {

	int n;
	scanf("%d ", &n);

	char buf[10] = "";
	while (n--) {
		gets(buf);
		printf("%d\n", sum(buf[0], buf[2]));
	}

	return 0;
}