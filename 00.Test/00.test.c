#include <stdio.h>
#include <stdlib.h>

// ���������ṹ����
typedef struct {
	char ch;
	int parent;
	int lchild;
	int rchild;
	int weight;
}HuffmanTreeNode;

