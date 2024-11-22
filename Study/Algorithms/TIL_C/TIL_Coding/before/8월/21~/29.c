#include <stdio.h>
#include <string.h>

int main() { // 10798	세로읽기 / 2차원 배열
    char sa[16], sb[16], sc[16], sd[16], se[16];
    scanf("%s %s %s %s %s", &sa, &sb, &sc, &sd, &se);

    char* sarr[5] = {sa, sb, sc, sd, se}; // 배열은 자동으로 시작 주소를 가르키는 포인터로 변환됨.
    // 문자포인터를 가르키는 문자 포인터 배열.
    
    // TODO : 인덱스를 하나씩 읽어 출력하는데 예외처리.
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 5; j++) {
            if (strlen(sarr[j]) <= i) continue;
            //if (strlen(sa) <= i && j == 0) continue;
            //if (strlen(sb) <= i && j == 1) continue;
            //if (strlen(sc) <= i && j == 2) continue;
            //if (strlen(sd) <= i && j == 3) continue;
            //if (strlen(se) <= i && j == 4) continue;

            printf("%c", *(sarr[j] + i)); // ** 은 이중포인터. 포인터를 가르키는 포인터.         
            // sarr[j][i] 는 내부에서 sarr[j] + i 를 해서 역참조해 값까지 가져오는 것.
            // %s는 주소를 받아서 출력하는 것이다.
            // 역참조를 할 경우 char의 포인터에서 역참조를 하는 것이니 char 타입의 크기인 1bite만 가져온다.
        }
    }

    return 0;
}