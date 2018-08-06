#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20		// ɢ�б��������
#define P 11				// H(key) = key % P ��P��ȡֵ

// ����ɢ�б�Ԫ�ؽṹ����
typedef struct {
	int key;
}LinearElement;

// ��ʽɢ�б�Ԫ�ؽṹ����
typedef struct {
	int key;
	struct ChainElement* next;
}ChainElement;

// ��ʼ������ɢ�б�
void InitLinearTable(LinearElement hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i].key = -1;
	}
}

// ��ʼ����ʽɢ�б�
void InitChainTable(ChainElement* hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

// ɢ�к�����H(key) = key % P
int Hash(int key) {
	return key % P;
}

// ����̽����ɢ�з��Ĳ��뺯��, ����ɹ�����1, ���򷵻�0
int LinearInsert(LinearElement hash_table[], LinearElement item) {
	int hash_value = Hash(item.key);
	// ������TABLE_SIZE��̽��
	for (int i = 0; i < TABLE_SIZE; i++) {
		int detecting = (hash_value + i) % TABLE_SIZE;
		// �ҵ��յ�λ��
		if (hash_table[detecting].key == -1) {
			hash_table[detecting] = item;
			printf("Insert %d successfully.\n", item.key);
			return 1;
		}
		// ���ֱ����Ѿ����˴˹ؼ���
		if (hash_table[detecting].key == item.key) {
			printf("Insert %d failed. Alread have this key in the table.\n", item.key);
			return 0;
		}
	}
	// ���̽����������
	printf("Insert %d failed. There is no more space in the table.\n", item.key);
	return 0;
}

// �������Ĳ��뺯��, ����ɹ�����1, ���򷵻�0
int ChainInsert(ChainElement* hash_table[], ChainElement item) {
	int hash_value = Hash(item.key);
	ChainElement* p = hash_table[hash_value];
	ChainElement* per = NULL;
	while (p != NULL) {
		// �ؼ����Ѿ��ڱ���
		if (p->key == item.key) {
			printf("Insert %d failed. Alread have this key in the table.\n", item.key);
			return 0;
		}
		per = p;
		p = p->next;
	}
	ChainElement* new_element = (ChainElement*)malloc(sizeof(ChainElement));
	// �������ռ�ʧ��
	if (new_element == NULL) {
		printf("Insert %d failed. The memory is full.\n", item.key);
		return 0;
	}
	new_element->key = item.key;
	new_element->next = NULL;
	if (per) {
		per->next = new_element;
	}
	else {
		hash_table[hash_value] = new_element;
	}
	printf("Insert %d successfully.\n", item.key);
	return 1;
}

// ����̽�ⷨ�Ĺ�ϣ��չʾ
void ShowLinearTable(LinearElement hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("%d: %d\n", i, hash_table[i].key);
	}
}

// �������Ĺ�ϣ��չʾ
void ShowChainTable(ChainElement* hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("%d: ", i);
		ChainElement* p = hash_table[i];
		while (p) {
			printf("%d->", p->key);
			p = p->next;
		}
		printf("NULL\n");
	}
}

int main() {
	int keys[12] = { 19, 14, 23, 1, 68, 20, 84, 27, 56, 11, 10, 79 };

	LinearElement linear_elements[12];
	for (int i = 0; i < 12; i++) {
		linear_elements[i].key = keys[i];
	}

	ChainElement chain_elements[12];
	for (int i = 0; i < 12; i++) {
		chain_elements[i].key = keys[i];
		chain_elements[i].next = NULL;
	}

	// ����ɢ�б�
	LinearElement linear_hash_table[TABLE_SIZE];
	InitLinearTable(linear_hash_table);
	printf("Begin to insert elements into linear hash table:\n");
	for (int i = 0; i < 12; i++) {
		LinearInsert(linear_hash_table, linear_elements[i]);
	}
	printf("Insert done. The result is as follows:\n");
	ShowLinearTable(linear_hash_table);

	// ��ʽɢ�б�
	ChainElement* chain_hash_table[TABLE_SIZE];
	InitChainTable(chain_hash_table);
	printf("Begin to insert elements into chain hash table:\n");
	for (int i = 0; i < 12; i++) {
		ChainInsert(chain_hash_table, chain_elements[i]);
	}
	printf("Insert done. The result is as follows:\n");
	ShowChainTable(chain_hash_table);

	system("pause");
	return 0;
}