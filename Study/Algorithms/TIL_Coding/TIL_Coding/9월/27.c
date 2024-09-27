#include <stdio.h>
// 브루트 포스 / 9.27
int main() {//1436	영화감독 숌
    int n;
    scanf("%d", &n);

    int count = 0;
    int num = 666;

    while (1) {
        char str[20];
        sprintf(str, "%d", num);  // 숫자를 문자열로 변환

        if (strstr(str, "666") != NULL) {  // '666'이 포함된 경우
            count++;
        }

        if (count == n) {  // N번째 '666'을 찾으면 출력
            printf("%d\n", num);
            break;
        }

        num++;  // 다음 숫자로 증가
    }

	return 0;
}