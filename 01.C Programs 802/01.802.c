#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20		// 散列表最大容量
#define P 11				// H(key) = key % P 中P的取值

// 线性散列表元素结构定义
typedef struct {
	int key;
}LinearElement;

// 链式散列表元素结构定义
typedef struct {
	int key;
	struct ChainElement* next;
}ChainElement;

// 初始化线性散列表
void InitLinearTable(LinearElement hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i].key = -1;
	}
}

// 初始化链式散列表
void InitChainTable(ChainElement* hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		hash_table[i] = NULL;
	}
}

// 散列函数，H(key) = key % P
int Hash(int key) {
	return key % P;
}

// 线性探测再散列法的插入函数, 插入成功返回1, 否则返回0
int LinearInsert(LinearElement hash_table[], LinearElement item) {
	int hash_value = Hash(item.key);
	// 最多进行TABLE_SIZE次探测
	for (int i = 0; i < TABLE_SIZE; i++) {
		int detecting = (hash_value + i) % TABLE_SIZE;
		// 找到空的位置
		if (hash_table[detecting].key == -1) {
			hash_table[detecting] = item;
			printf("Insert %d successfully.\n", item.key);
			return 1;
		}
		// 发现表中已经有了此关键字
		if (hash_table[detecting].key == item.key) {
			printf("Insert %d failed. Alread have this key in the table.\n", item.key);
			return 0;
		}
	}
	// 如果探测完整个表
	printf("Insert %d failed. There is no more space in the table.\n", item.key);
	return 0;
}

// 拉链法的插入函数, 插入成功返回1, 否则返回0
int ChainInsert(ChainElement* hash_table[], ChainElement item) {
	int hash_value = Hash(item.key);
	ChainElement* p = hash_table[hash_value];
	ChainElement* per = NULL;
	while (p != NULL) {
		// 关键字已经在表中
		if (p->key == item.key) {
			printf("Insert %d failed. Alread have this key in the table.\n", item.key);
			return 0;
		}
		per = p;
		p = p->next;
	}
	ChainElement* new_element = (ChainElement*)malloc(sizeof(ChainElement));
	// 如果申请空间失败
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

// 线性探测法的哈希表展示
void ShowLinearTable(LinearElement hash_table[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("%d: %d\n", i, hash_table[i].key);
	}
}

// 拉链法的哈希表展示
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

	// 线性散列表
	LinearElement linear_hash_table[TABLE_SIZE];
	InitLinearTable(linear_hash_table);
	printf("Begin to insert elements into linear hash table:\n");
	for (int i = 0; i < 12; i++) {
		LinearInsert(linear_hash_table, linear_elements[i]);
	}
	printf("Insert done. The result is as follows:\n");
	ShowLinearTable(linear_hash_table);

	// 链式散列表
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