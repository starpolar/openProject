#include <stdio.h>
// ���Ʈ ���� / 9.25
int main() {//19532	������ ���鰭���Դϴ�
	
	// �Ǵ� �ҰŹ��� ����ϸ� �� �� �ּҰ������ ����ؼ� Ǯ�� ����.
	int a, b, c; // ù ��° �������� ���
	int d, e, f; // �� ��° �������� ���
	int x, y;    // �ظ� ������ ����
	int denominator; // �и�

	// ��� �Է�
	//printf("ù ��° �������� ��� a, b, c�� �Է��ϼ��� (��: 2 5 8): ");
	scanf("%d %d %d", &a, &b, &c);

	//printf("�� ��° �������� ��� d, e, f�� �Է��ϼ��� (��: 3 -4 -11): ");
	scanf("%d %d %d", &d, &e, &f);

	// �ҰŹ� ����
	// x�� �Ұ��ϱ� ���� ù ��° �����Ŀ� d�� ���ϰ�, �� ��° �����Ŀ� a�� ����
	int a1 = a * d;
	int b1 = b * d;
	int c1 = c * d;

	int a2 = d * a;
	int b2 = e * a;
	int c2 = f * a;

	// �� �������� ���� y�� ����
	int numerator_y = c1 - c2;
	int denominator_y = b1 - b2;

	if (denominator_y == 0) {
		//printf("�ظ� ���� �� �����ϴ�. (�и� 0�Դϴ�)\n");
		return 0;
	}

	y = numerator_y / denominator_y;

	// y ���� �̿��Ͽ� x ���� ����
	if (a != 0) {
		x = (c - b * y) / a;
	}
	else if (d != 0) {
		x = (f - e * y) / d;
	}
	else {
		//printf("�ظ� ���� �� �����ϴ�. (a�� d�� ��� 0�Դϴ�)\n");
		return 0;
	}

	// ��� ���
	//printf("x = %d, y = %d\n", x, y);
	printf("%d %d\n", x, y);

	return 0;


	// ���� �������� ũ���� ������ ���ؼ� Ǯ�� ����!
	//int a, b, c, d, e, f;
	//scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
	//printf("%d %d", (c * e - b * f) / (a * e - b * d), (c * d - a * f) / (b * d - a * e));
	
	
	// ���Ʈ ���� ���.
	//int a, b, c, d, e, f;
	//scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	//int x, y;
	//for (x = -999; x <= 999; x++) {
	//	for (y = -999; y <= 999; y++) {
	//		if (a * x + b * y == c && d * x + e * y == f) {
	//			printf("%d %d\n", x, y);
	//			return 0; // �ظ� ã���� ���α׷� ����
	//		}
	//	}
	//}
	
	
	// Fail..
	//float a, b, c, d, e, f;
	//scanf("%f %f %f %f %f %f", &a, &b, &c, &d, &e, &f);

	//// ax + by = c
	//// x = (c / (a+b+y))-1 �� ���� // �������� ���ʸ� �����°� �ƴ϶� ��� ���� �������� �±���.
	//
	//// x = (c - b * y) / a
	//// y = (c - a * x) / b

	//// x = (c - b * ( (c - a * x) / b) ) / a
	//int xre, yre, x2re, y2re;
	//for (int x = -999; x <= 999; x++) {
	//	if (b == 0 || e == 0 || a == 0 || d == 0) break;
	//	yre = (int)(c - a * x) / b;
	//	if (x == (c - b * yre) / a && a != 0) {
	//		xre = x;
	//		for (int x2 = -999; x2 <= 999; x2++) {
	//			/*if (x == 2) {
	//				printf("debug");
	//			}*/
	//			y2re = (int)(f - d * x) / e;
	//			if (x2 == (f - e * y2re) / d) {
	//				x2re = x2;

	//				if (xre == x2re && yre == y2re) {
	//					printf("%d %d", x2re, y2re);
	//					return 0;
	//				}
	//			}
	//		}
	//	}
	//}
		
	return 0;
}