#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *prev; // ���� ���� ���� �� �ִ�.
	int idx;
	char data[20];
	struct Node *next; // �� �����ͷ� ���� Node�� ���� �� �ִ�.
} Node;

Node *head = NULL;
Node *tail = NULL;

void create(int idx, char *data) {
	Node *node = malloc(sizeof(Node));

	if (head == NULL && tail == NULL) { // �ʱ� ����
		head = node;
		tail = node;
		node->prev = NULL;
		node->next = NULL;

		node->idx = idx;
		sprintf(node->data, "%s %d", data, idx);
	}
	else { // ���� ����
		tail->next = node;
		node->prev = tail;
		node->next = NULL;
		tail = node;

		node->idx = idx;
		sprintf(node->data, "%s %d", data, idx);
	}

}

void printAll() {
	if (head == NULL) { // node�� ������
		printf("no Node. can not print\n");
		return;
	}

	Node *tmp = head;
	while (tmp != NULL) {
		printf("idx : %d\n", tmp->idx);
		printf("data : %s\n", tmp->data);

		tmp = tmp->next;
	}
}

Node *stackPop() {
	if (tail == NULL) { // node�� ������
		return NULL;
	}

	if (tail->prev != NULL) {
		tail->prev->next = NULL;
		Node *tmp = tail;
		tail = tail->prev;
		return tmp;
	}
	else { // node�� 1�� �ۿ� ������ �ʱ�ȭ
		Node *tmp = tail;
		head = NULL;
		tail = NULL;
		return tmp;
	}
}

Node *quePop() {
	if (head == NULL) { // node�� ������
		return NULL;
	}

	if (head->next != NULL) {
		head->next->prev = NULL;
		Node *tmp = head;
		head = head->next;
		return tmp;
	}
	else { // node�� 1�� �ۿ� ������ �ʱ�ȭ
		Node *tmp = head;
		head = NULL;
		tail = NULL;
		return tmp;
	}
}

Node *search(int idx) {
	Node *tmp = head, *res = NULL;
	while (tmp != NULL) {
		if (tmp->idx == idx) { // ����� �Է°����� �˻�
			res = tmp;
		}
		tmp = tmp->next;
	}
	if (res) {
		return NULL; // ã�� ������ ��� NULL ��ȯ.
	}
	return res;
}

void insert(int idx, char *data) {
	if (tail->idx < idx || head->idx > idx) { // ���� �ε����϶� ����ó��.
		printf("is not index. fail insert\n");
		return;
	}

	Node* tmp = head;
	//int halfIdx = (tail->idx - head->idx) / 2; // �ε��� ������ ���� �̺� Ž�� �̻��.
	while (tmp != NULL) {
		if (tmp->idx == idx) {
			Node* node = malloc(sizeof(Node));
			node->idx = idx;
			sprintf(node->data, "%s %d", data, idx);

			node->prev = tmp->prev;
			tmp->prev->next = node;
			node->next = tmp;
			tmp->prev = node;

			while (tmp != NULL) { // ���� ���� �ε��� ����.
				tmp->idx++;
				tmp = tmp->next;
			}

			break;
		}
		tmp = tmp->next;
	}
}

void delete(int idx) {
	if (tail->idx < idx || head->idx > idx) { // ���� �ε����϶� ����ó��.
		printf("is not index. fail delete\n");
		return;
	}

	Node* tmp = head; // �ε��� ���Ҹ� ���� �̺� Ž�� �̻��.
	while (tmp != NULL) {
		if (tmp->idx == idx) {
			tmp->prev->next = tmp->next;
			if (tmp->next != NULL) { // ���� ��尡 �������� ����.
				tmp->next->prev = tmp->prev;
			}

			Node* delNode = tmp;
			tmp = tmp->next;
			free(delNode);
			printf("complete delete\n");

			while (tmp != NULL) { // ���� ���� �ε��� ����.
				tmp->idx--;
				tmp = tmp->next;
			}

			break;
		}
		tmp = tmp->next;
	}
}

int main() {

	char data[20] = "test";
	for (int i = 0; i < 5; i++) {
		create(i, data);
	}
	printAll();

	delete(4);
	printf("==========\n");
	printAll();
	printf("==========\n");

	/*char insertData[20] = "insert";
	insert(5, insertData);
	printf("==========\n");
	printAll();
	printf("==========\n");*/

	/*Node *val;

	val = search(4);
	if (val != NULL) {
		printf("==========\n");
		printf("search Node idx : %d\n", val->idx);
		printf("search Node data : %s\n", val->data);
		printf("==========\n");
	}
	else {
		printf("not search val\n");
	}*/

	/*
	// Pop Test
	
	for (int i = 0; i < 1; i++) {
		val = stackPop();
		if (val != NULL) {
			printf("==========\n");
			printf("stackPop idx : %d\n", val->idx);
			printf("stackPop data : %s\n", val->data);
			printf("==========\n");
			free(val);
		}
		else {
			printf("not val\n");
		}

		printAll();
	}
	
	for (int i = 0; i < 1; i++) {
		val = quePop();
		if (val != NULL) {
			printf("==========\n");
			printf("quePop idx : %d\n", val->idx);
			printf("quePop data : %s\n", val->data);
			printf("==========\n");
			free(val);
		}
		else {
			printf("not val\n");
		}

		printAll();
	}*/

	return 0;
}