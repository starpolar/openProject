#include <stdio.h>
#include <string.h>

int main() { // 10798	�����б� / 2���� �迭
    char sa[16], sb[16], sc[16], sd[16], se[16];
    scanf("%s %s %s %s %s", &sa, &sb, &sc, &sd, &se);

    char* sarr[5] = {sa, sb, sc, sd, se}; // �迭�� �ڵ����� ���� �ּҸ� ����Ű�� �����ͷ� ��ȯ��.
    // ���������͸� ����Ű�� ���� ������ �迭.
    
    // TODO : �ε����� �ϳ��� �о� ����ϴµ� ����ó��.
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 5; j++) {
            if (strlen(sarr[j]) <= i) continue;
            //if (strlen(sa) <= i && j == 0) continue;
            //if (strlen(sb) <= i && j == 1) continue;
            //if (strlen(sc) <= i && j == 2) continue;
            //if (strlen(sd) <= i && j == 3) continue;
            //if (strlen(se) <= i && j == 4) continue;

            printf("%c", *(sarr[j] + i)); // ** �� ����������. �����͸� ����Ű�� ������.         
            // sarr[j][i] �� ���ο��� sarr[j] + i �� �ؼ� �������� ������ �������� ��.
            // %s�� �ּҸ� �޾Ƽ� ����ϴ� ���̴�.
            // �������� �� ��� char�� �����Ϳ��� �������� �ϴ� ���̴� char Ÿ���� ũ���� 1bite�� �����´�.
        }
    }

    return 0;
}