// ���հ� �� / 9.29
//14425	���ڿ� ����

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10001
#define STRING_LENGTH 501

// �ؽ� ���̺�� ���ڿ� ���� ����
typedef struct Node {
    char str[STRING_LENGTH];
    struct Node* next;
} Node;

Node* hashTable[MAX];

// �ؽ� �Լ�: ���ڿ��� �ؽ� ���� ����մϴ�.
unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + (*str++);
    }
    return hash % MAX;
}

// ���ڿ��� �ؽ� ���̺� �߰��մϴ�.
void insert(const char* str) {
    unsigned int idx = hash(str);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->str, str);
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// �ؽ� ���̺��� ���ڿ��� ã���ϴ�.
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

// �ؽ� ���̺��� ��� �޸𸮸� �����մϴ�.
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

    // ���ڿ� ������ ũ�� �Է�
    scanf("%d %d", &N, &M);

    // ���ڿ� ���� �Է�
    for (int i = 0; i < N; i++) {
        scanf("%s", str);
        insert(str);
    }

    int count = 0;

    // Ȯ���� ���ڿ��� �Է� �� �˻�
    for (int i = 0; i < M; i++) {
        scanf("%s", str);
        if (find(str)) {
            count++;
        }
    }

    // ��� ���
    printf("%d\n", count);

    // �޸� ����
    freeHashTable();

    return 0;
}
