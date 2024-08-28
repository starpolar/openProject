#include <stdio.h>
#include <string.h>

int main() {
    float gradeChart[4] = { 4.0, 3.0, 2.0, 1.0 };  // A, B, C, D에 대한 점수
    float creGraSum = 0.0, creSum = 0.0;

    for (int i = 0; i < 20; i++) {
        float credit;
        char s[51], grade[5];
        scanf("%s %f %s", s, &credit, grade);

        if (grade[0] == 'P') {  // Pass 학점은 GPA에 포함되지 않음
            continue;
        }

        int tmp = grade[0] - 'A';  // A:0, B:1, C:2, D:3
        float gradeValue = 0.0;

        if (grade[0] == 'F') {
            gradeValue = 0.0;  // F 학점은 0점
        }
        else {
            gradeValue = gradeChart[tmp];
            if (grade[1] == '+') {
                gradeValue += 0.5;  // +가 붙은 경우 0.5 추가
            }
        }

        creGraSum += gradeValue * credit;
        creSum += credit;
    }

    float result = creGraSum / creSum;
    printf("%.6f\n", result);  // 소수점 6자리까지 출력

    return 0;
}


//#include <stdio.h>
//#include <string.h>
//
//int main() { //25206	너의 평점은 / 심화 1
//	// P만 패스하고, F는 학점을 플러스 해야됨.
//	//int gradeCnt[9] = { 0 };
//	float gradeChart[2][4] = { {4.0, 3.0, 2.0, 1.0}, {4.5, 3.5, 2.5, 1.5} };
//	float creGraSum = 0.0, creSum = 0.0, result = 0.0;
//	for (int i = 0; i < 20; i++) { // 공식 : ((credit * grade) += 20pcs) / (credit += 20pcs)
//		float credit;
//		char s[51], grade[5];
//		scanf("%s %f %s", &s, &credit, &grade);
//
//		int tmp = grade[0] - 'A', idx = 0;
//		if (grade[0] == 'P' || grade[0] == 'F') {
//			creSum += credit;
//			continue;
//		}
//		else {
//			//gradeCnt[tmp]++;
//			if (grade[1] == '+') idx = 1;
//			creGraSum += gradeChart[idx][tmp] * credit;
//			creSum += credit;			
//		}
//		
//	}
//	result = creGraSum / creSum;
//	printf("%.6f", result);
//
//	return 0;
//}