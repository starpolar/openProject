// 집합과 맵 / 9.29
//14425	문자열 집합

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10001
#define STRING_LENGTH 501

// 해시 테이블로 문자열 집합 구현
typedef struct Node {
    char str[STRING_LENGTH];
    struct Node* next;
} Node;

Node* hashTable[MAX];

// 해시 함수: 문자열의 해시 값을 계산합니다.
unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash % MAX;
}

// 문자열을 해시 테이블에 추가합니다.
void insert(const char* str) {
    unsigned int idx = hash(str);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->str, str);
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// 해시 테이블에서 문자열을 찾습니다.
int find(const char* str) {
    unsigned int idx = hash(str);
    Node* current = hashTable[idx];
    while (current) {
        if (strcmp(current->str, str) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// 해시 테이블의 모든 메모리를 해제합니다.
void freeHashTable() {
    for (int i = 0; i < MAX; i++) {
        Node* current = hashTable[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    int N, M;
    char str[STRING_LENGTH];

    // 문자열 집합의 크기 입력
    scanf("%d %d", &N, &M);

    // 문자열 집합 입력
    for (int i = 0; i < N; i++) {
        scanf("%s", str);
        insert(str);
    }

    int count = 0;

    // 확인할 문자열들 입력 및 검색
    for (int i = 0; i < M; i++) {
        scanf("%s", str);
        if (find(str)) {
            count++;
        }
    }

    // 결과 출력
    printf("%d\n", count);

    // 메모리 해제
    freeHashTable();

    return 0;
}
