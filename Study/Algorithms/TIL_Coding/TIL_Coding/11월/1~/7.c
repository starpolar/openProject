// 2754 학점계산 / 11.7
#include <stdio.h>
#include <string.h>

float get_grade(const char* grade) {

    if (strcmp(grade, "A+") == 0) return 4.3;
    if (strcmp(grade, "A0") == 0) return 4.0;
    if (strcmp(grade, "A-") == 0) return 3.7;
    if (strcmp(grade, "B+") == 0) return 3.3;
    if (strcmp(grade, "B0") == 0) return 3.0;
    if (strcmp(grade, "B-") == 0) return 2.7;
    if (strcmp(grade, "C+") == 0) return 2.3;
    if (strcmp(grade, "C0") == 0) return 2.0;
    if (strcmp(grade, "C-") == 0) return 1.7;
    if (strcmp(grade, "D+") == 0) return 1.3;
    if (strcmp(grade, "D0") == 0) return 1.0;
    if (strcmp(grade, "D-") == 0) return 0.7;
    if (strcmp(grade, "F") == 0) return 0.0;

}

int main() { // 문자열은 배열이기 때문에 직접 비교가 불가.

    char grade[10];
    scanf("%s", &grade);

    printf("%.1f\n", get_grade(grade));
    
    return 0;
}