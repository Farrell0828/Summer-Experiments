#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define N 27			// ��ĸ���е��ַ���������Ҷ�ӽ����
#define M (2*N - 1)		// ���������ܽ�����ΪҶ�ӽ���2����1

typedef struct HuffmanTreeNode {
	char ch;
	int parent;
	int lchild;
	int rchild;
	double weight;
}HTNode;

void BuildHuffmanTree(HTNode tree_nodes[], char alphabet[], double weights[]) {
	// ��ʼ������������㼯��
	for (int i = 0; i < M; i++) {
		tree_nodes[i].ch = '@';			// ��ʼ��Ϊ������ĸ���е���һ�ַ�
		tree_nodes[i].parent = -1;		// -1��������
		tree_nodes[i].lchild = -1;
		tree_nodes[i].rchild = -1;
		tree_nodes[i].weight = 0.0;
	}
	// ����ĸ���е���ĸ����Ȩֵ�洢��ǰN�������
	for (int i = 0; i < N; i++) {
		tree_nodes[i].ch = alphabet[i];
		tree_nodes[i].weight = weights[i];
	}
	// �ϲ���㣬��������������������N-1�κϲ���
	// ÿ��ѡ��������С�Ľ��ϲ���һ���½ڵ㣬�������������Ϊ�½ڵ�ĺ��ӽ�㣬
	// ���½ڵ�����Ϊ�������ĸ���㣬�½ڵ��ȨֵΪ�����Ȩֵ֮��
	for (int i = 0; i < N - 1; i++) {
		int min_sub1 = M, min_sub2 = M;
		double min_value1 = DBL_MAX, min_value2 = DBL_MAX;
		// �������еĲ����ڸ����Ľ�㣬�ҳ�Ȩֵ��С�����������±��Ȩֵ
		for (int j = 0; j < N + i; j++) {
			// �����ڸ����ſ���
			if (tree_nodes[j].parent == -1) {
				// ����˽��Ȩֵ��min_value1��С
				if (tree_nodes[j].weight < min_value1) {
					min_value2 = min_value1;
					min_sub2 = min_sub1;
					min_value1 = tree_nodes[j].weight;
					min_sub1 = j;
				}
				// ����˽��Ȩֵ����min_value1��min_value2֮��
				else if (tree_nodes[j].weight < min_value2) {
					min_value2 = tree_nodes[j].weight;
					min_sub2 = j;
				}
			}
		}
		// �����������Ϊ�½ڵ�ĺ��ӽ�㣬
		// ���½ڵ�����Ϊ�������ĸ���㣬�½ڵ��ȨֵΪ�����Ȩֵ֮��
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
		// ���������
		if (tree_nodes[parent].lchild == child) {
			stack[top++] = '0';
		}
		// �����Һ���
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