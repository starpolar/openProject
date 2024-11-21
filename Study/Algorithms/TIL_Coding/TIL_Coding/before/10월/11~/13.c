// 약수, 배수와 소수 2 / 10.13
// 2346	 풍선 터뜨리기
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;            // 풍선 안의 숫자
    int index;          // 풍선의 원래 위치 (1부터 시작)
    struct Node* prev;  // 이전 노드
    struct Node* next;  // 다음 노드
} Node;

int main() {
    int N;
    scanf("%d", &N);

    // 노드 배열을 동적 할당하여 생성
    Node* nodes = (Node*)malloc(N * sizeof(Node));

    // 첫 번째 노드 설정
    for (int i = 0; i < N; i++) {
        nodes[i].index = i + 1;
        scanf("%d", &nodes[i].num);
        if (i > 0) {
            nodes[i].prev = &nodes[i - 1];
            nodes[i - 1].next = &nodes[i];
        }
    }

    // 원형 이중 연결 리스트로 만들기
    nodes[0].prev = &nodes[N - 1];
    nodes[N - 1].next = &nodes[0];

    Node* curr = &nodes[0]; // 현재 노드를 첫 번째 노드로 설정

    for (int count = 0; count < N; count++) {
        printf("%d ", curr->index);
        int move = curr->num;

        // 현재 노드를 리스트에서 제거
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        // 노드가 하나만 남은 경우
        if (count == N - 1) {
            break;
        }

        // 이동 방향 및 이동 횟수 결정
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

    free(nodes); // 동적 할당된 메모리 해제
    return 0;
}
