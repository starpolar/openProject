#include <stdio.h>
#include <string.h>

int main() {
    float gradeChart[4] = { 4.0, 3.0, 2.0, 1.0 };  // A, B, C, D�� ���� ����
    float creGraSum = 0.0, creSum = 0.0;

    for (int i = 0; i < 20; i++) {
        float credit;
        char s[51], grade[5];
        scanf("%s %f %s", s, &credit, grade);

        if (grade[0] == 'P') {  // Pass ������ GPA�� ���Ե��� ����
            continue;
        }

        int tmp = grade[0] - 'A';  // A:0, B:1, C:2, D:3
        float gradeValue = 0.0;

        if (grade[0] == 'F') {
            gradeValue = 0.0;  // F ������ 0��
        }
        else {
            gradeValue = gradeChart[tmp];
            if (grade[1] == '+') {
                gradeValue += 0.5;  // +�� ���� ��� 0.5 �߰�
            }
        }

        creGraSum += gradeValue * credit;
        creSum += credit;
    }

    float result = creGraSum / creSum;
    printf("%.6f\n", result);  // �Ҽ��� 6�ڸ����� ���

    return 0;
}


//#include <stdio.h>
//#include <string.h>
//
//int main() { //25206	���� ������ / ��ȭ 1
//	// P�� �н��ϰ�, F�� ������ �÷��� �ؾߵ�.
//	//int gradeCnt[9] = { 0 };
//	float gradeChart[2][4] = { {4.0, 3.0, 2.0, 1.0}, {4.5, 3.5, 2.5, 1.5} };
//	float creGraSum = 0.0, creSum = 0.0, result = 0.0;
//	for (int i = 0; i < 20; i++) { // ���� : ((credit * grade) += 20pcs) / (credit += 20pcs)
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