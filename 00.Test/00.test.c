#include <stdio.h>
#include <stdlib.h>

// 哈夫曼结点结构定义
typedef struct {
	char ch;
	int parent;
	int lchild;
	int rchild;
	int weight;
}HuffmanTreeNode;

