#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define N 27			// 字母表中的字符总数，即叶子结点数
#define M (2*N - 1)		// 哈夫曼树总结点个数为叶子结点的2倍少1

typedef struct HuffmanTreeNode {
	char ch;
	int parent;
	int lchild;
	int rchild;
	double weight;
}HTNode;

void BuildHuffmanTree(HTNode tree_nodes[], char alphabet[], double weights[]) {
	// 初始化哈夫曼树结点集合
	for (int i = 0; i < M; i++) {
		tree_nodes[i].ch = '@';			// 初始化为不再字母表中的任一字符
		tree_nodes[i].parent = -1;		// -1代表不存在
		tree_nodes[i].lchild = -1;
		tree_nodes[i].rchild = -1;
		tree_nodes[i].weight = 0.0;
	}
	// 将字母表中的字母及其权值存储在前N个结点内
	for (int i = 0; i < N; i++) {
		tree_nodes[i].ch = alphabet[i];
		tree_nodes[i].weight = weights[i];
	}
	// 合并结点，构造哈夫曼树，供需进行N-1次合并，
	// 每次选出两个最小的结点合并成一个新节点，并将两个结点设为新节点的孩子结点，
	// 将新节点设置为两个结点的父结点，新节点的权值为两结点权值之和
	for (int i = 0; i < N - 1; i++) {
		int min_sub1 = M, min_sub2 = M;
		double min_value1 = DBL_MAX, min_value2 = DBL_MAX;
		// 遍历现有的不存在父结点的结点，找出权值最小的两个结点的下标和权值
		for (int j = 0; j < N + i; j++) {
			// 不存在父结点才考虑
			if (tree_nodes[j].parent == -1) {
				// 如果此结点权值比min_value1还小
				if (tree_nodes[j].weight < min_value1) {
					min_value2 = min_value1;
					min_sub2 = min_sub1;
					min_value1 = tree_nodes[j].weight;
					min_sub1 = j;
				}
				// 如果此结点权值介于min_value1和min_value2之间
				else if (tree_nodes[j].weight < min_value2) {
					min_value2 = tree_nodes[j].weight;
					min_sub2 = j;
				}
			}
		}
		// 将两个结点设为新节点的孩子结点，
		// 将新节点设置为两个结点的父结点，新节点的权值为两结点权值之和
		tree_nodes[N + i].weight = min_value1 + min_value2;
		tree_nodes[N + i].lchild = min_sub1;
		tree_nodes[N + i].rchild = min_sub2;
		tree_nodes[min_sub1].parent = N + i;
		tree_nodes[min_sub2].parent = N + i;
	}
}

void Encode(HTNode tree_nodes[], char ch) {
	char stack[M] = { '2' };
	int top = 0;
	int sub = -1;
	for (int i = 0; i < N; i++) {
		if (tree_nodes[i].ch == ch) {
			sub = i;
			break;
		}
	}
	///*
	if (sub == -1) {
		printf("\nThe character %c is not in the alphabate.\n");
		return;
	}
	//*/
	int child = sub;
	int parent = tree_nodes[child].parent;
	while (parent != -1) {
		// 如果是左孩子
		if (tree_nodes[parent].lchild == child) {
			stack[top++] = '0';
		}
		// 否则右孩子
		else {
			stack[top++] = '1';
		}
		child = parent;
		parent = tree_nodes[parent].parent;
	}
	while (top != 0) {
		printf("%c", stack[--top]);
	}

}

int main() {
	HTNode tree_nodes[M];

	char alphabet[N] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
		'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 
		'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '
	};

	double weights[N] = {
		64, 13, 22, 32, 103, 21, 15, 47, 57,
		1, 5, 32, 20, 57, 63, 15, 1, 48,
		51, 80, 23, 8, 18, 1, 16, 1, 168
	};

	BuildHuffmanTree(tree_nodes, alphabet, weights);

	for (int i = 0; i < N; i++) {
		printf("%c: ", alphabet[i]);
		Encode(tree_nodes, alphabet[i]);
		printf("\n");
	}

	char s[24] = "C PROGRAM IS MY FAVORITE";
	for (int i = 0; i < 24; i++) {
		Encode(tree_nodes, s[i]);
	}
	printf("\n");

	// scanf("%[^\n]", &s);
	/*
	char* p = &s[0];
	while ((*p) != '\0') {
		Encode(tree_nodes, p);
		p++;
	}
	*/

	system("pause");
	return 0;
}