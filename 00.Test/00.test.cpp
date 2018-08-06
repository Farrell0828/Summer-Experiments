#//include "00.test.h"

#include <stdio.h>
#include <stdlib.h>

#define THT_NUMBER_OF_NODES 12	// ͼ�Ķ������

// �ڽӱ�洢��ͼ�Ķ���Ľṹ����
typedef struct VertexNode {
	int vertex;					// �˶���ı��
	struct EdgeListNode* list;	// ָ��˶���ı߱�
	int in_degree;				// �˶�������
}VNode;

// �߱�Ľ��ṹ����
typedef struct EdgeListNode {
	int vertex;					// �ߵ�ĩ�˶���ı��
	struct EdgeListNode* next;	// ָ����һ���߱���
}ELNode;

typedef VNode* Graph;

// ��ʼ��ͼg
void InitGraph(Graph g, int n) {
	for (int i = 0; i < n; i++) {
		g[i].vertex = i;
		g[i].list = NULL;
		g[i].in_degree = 0;
	}
}

// Ϊͼg����һ���Ӷ���vָ�򶥵�w�ıߣ����ɹ�����1�����򷵻�0
int AddEdge(Graph g, int v, int w) {
	ELNode* p = g[v].list;
	ELNode* per = NULL;
	while (p != NULL) {
		// ���ͼ���Ѿ�����������
		if (p->vertex == w) {
			printf("Add edge failed. Alread have edge <%d, %d> in this graph.\n", v, w);
			return 0;
		}
		per = p;
		p = p->next;
	}
	ELNode* new_node = (ELNode*)malloc(sizeof(ELNode));
	// �������ռ�ʧ��
	if (new_node == NULL) {
		printf("Add edge failed. There is no more space.\n");
		return 0;
	}
	// ����ռ�ɹ��������½ڵ���Ϣ
	new_node->vertex = w;
	new_node->next = NULL;
	// ���per��Ϊ�գ�˵�������whileѭ����ִ�У�g[v].list��Ϊ��
	// ��ʱperָ��˱߱�����һ����㣬���½����ں���
	if (per) {
		per->next = new_node;
	}
	// ���perΪ�գ�˵�������whileѭ��û��ִ�У���g[v].listΪ��
	// ��ʱֱ�ӽ�g[v].listָ���½�㣬�½��Ϊ�˱߱�ĵ�һ�����
	else {
		g[v].list = new_node;
	}
	(g[w].in_degree)++;		// ������w����ȼ�1
}

// �������򣬳ɹ�����1�����򷵻�0
int TopSort(Graph g) {
	// ����һ��ջ�����������Ϊ0�Ķ���ı��
	int stack[THT_NUMBER_OF_NODES] = { THT_NUMBER_OF_NODES };
	int top = 0;
	// ���������Ϊ0�Ķ�������ջ
	for (int i = 0; i < THT_NUMBER_OF_NODES; i++) {
		if (g[i].in_degree == 0) {
			stack[top++] = i;
		}
	}
	// ����ÿ��ȥ�������һ�����Ϊ0�Ķ��㣬������ THT_NUMBER_OF_NODES ��
	for (int i = 0; i < THT_NUMBER_OF_NODES; i++) {
		// ���ջ��ָ����0��˵��ͼ�в��������Ϊ0�Ķ��㣬��ͼ���л����޷�������������
		if (top == 0) {
			printf("This Grapg has a cycle. Sort terminated.\n");
			return 0;
		}
		// ����˵�����������Ϊ0�Ķ��㣬��ջ�г�һ��
		int v = stack[--top];
		// ��������Ϊ0�Ķ���
		// �˴�ֱ������γ̱�����ơ�C1������C2�����֣��±��1��ʼ������v+1
		printf("C%d ", v + 1);
		// ���˶�������к�̶������ȶ���1
		ELNode* p = g[v].list;
		while (p) {
			int k = p->vertex;	// kΪv��һ����̶���
			(g[k].in_degree)--;
			// ����˶������ȼ�Ϊ0�ˣ��ͰѴ˶�����ջ
			if (g[k].in_degree == 0) {
				stack[top++] = k;
			}
			p = p->next;
		}
	}
	printf("\nTop sort done.");
	return 1;
}

int main()
{
	VNode g[THT_NUMBER_OF_NODES];
	InitGraph(g, THT_NUMBER_OF_NODES);

	AddEdge(g, 0, 1);
	AddEdge(g, 0, 2); 
	AddEdge(g, 1, 2);
	AddEdge(g, 0, 3);
	AddEdge(g, 2, 4);
	AddEdge(g, 3, 4);
	AddEdge(g, 10, 5);
	AddEdge(g, 2, 6);
	AddEdge(g, 4, 6);
	AddEdge(g, 2, 7);
	AddEdge(g, 5, 7);
	AddEdge(g, 8, 9);
	AddEdge(g, 8, 10);
	AddEdge(g, 0, 11);
	AddEdge(g, 8, 11);
	AddEdge(g, 9, 11);

	TopSort(g);

	system("pause");
	return 0;
}