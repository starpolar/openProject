#include <stdio.h>
#include <string.h>

int main() { // 11718	그대로 출력하기 / 문자열
	char s[101] = { 0 };
	
	for (int i = 0; i < 100; i++) {
		if (fgets(s, sizeof(s), stdin) == 0) break; // EOF(입력 끝)의 호출 : (콘솔에서)ctrl + z. 입력 함수의 EOF를 받은 반환값은 0. 하지만 EOF 자체는 -1로 정의.
		// scanf는 백준에서 fail. 콘솔에서 enter 한번 더 요구. : 형식 입력 처리를 하기에 두번을 요구함. / gets는 백준 success. 콘솔 단번에 입력.
		// gets는 한 라인을 모두 받기에, 버퍼오버플로우 공격이 될 수 있으므로 fgets를 사용. 는 입력 길이 제한을 둠.
		// fgets은 \n 개행문자를 문자열에 더함. gets는 개행문자를 뺌.
		printf("%s", s); // puts : 변수 출력 x. 문자열만 출력 가능. \n 를 추가해서 출력.
	}
	
	return 0;
}