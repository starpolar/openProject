// ���, ����� �Ҽ� 2 / 10.13
// 2346	 ǳ�� �Ͷ߸���
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;            // ǳ�� ���� ����
    int index;          // ǳ���� ���� ��ġ (1���� ����)
    struct Node* prev;  // ���� ���
    struct Node* next;  // ���� ���
} Node;

int main() {
    int N;
    scanf("%d", &N);

    // ��� �迭�� ���� �Ҵ��Ͽ� ����
    Node* nodes = (Node*)malloc(N * sizeof(Node));

    // ù ��° ��� ����
    for (int i = 0; i < N; i++) {
        nodes[i].index = i + 1;
        scanf("%d", &nodes[i].num);
        if (i > 0) {
            nodes[i].prev = &nodes[i - 1];
            nodes[i - 1].next = &nodes[i];
        }
    }

    // ���� ���� ���� ����Ʈ�� �����
    nodes[0].prev = &nodes[N - 1];
    nodes[N - 1].next = &nodes[0];

    Node* curr = &nodes[0]; // ���� ��带 ù ��° ���� ����

    for (int count = 0; count < N; count++) {
        printf("%d ", curr->index);
        int move = curr->num;

        // ���� ��带 ����Ʈ���� ����
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        // ��尡 �ϳ��� ���� ���
        if (count == N - 1) {
            break;
        }

        // �̵� ���� �� �̵� Ƚ�� ����
        if (move > 0) {
            for (int i = 0; i < move; i++) {
                curr = curr->next;
            }
        }
        else {
            for (int i = 0; i < -move; i++) {
                curr = curr->prev;
            }
        }
    }

    free(nodes); // ���� �Ҵ�� �޸� ����
    return 0;
}
