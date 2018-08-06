#//include "00.test.h"

#include <stdio.h>
#include <stdlib.h>

#define THT_NUMBER_OF_NODES 12	// 图的顶点个数

// 邻接表存储的图的顶点的结构定义
typedef struct VertexNode {
	int vertex;					// 此顶点的编号
	struct EdgeListNode* list;	// 指向此顶点的边表
	int in_degree;				// 此顶点的入度
}VNode;

// 边表的结点结构定义
typedef struct EdgeListNode {
	int vertex;					// 边的末端顶点的编号
	struct EdgeListNode* next;	// 指向下一个边表结点
}ELNode;

typedef VNode* Graph;

// 初始化图g
void InitGraph(Graph g, int n) {
	for (int i = 0; i < n; i++) {
		g[i].vertex = i;
		g[i].list = NULL;
		g[i].in_degree = 0;
	}
}

// 为图g增加一条从顶点v指向顶点w的边，若成功返回1，否则返回0
int AddEdge(Graph g, int v, int w) {
	ELNode* p = g[v].list;
	ELNode* per = NULL;
	while (p != NULL) {
		// 如果图中已经有了这条边
		if (p->vertex == w) {
			printf("Add edge failed. Alread have edge <%d, %d> in this graph.\n", v, w);
			return 0;
		}
		per = p;
		p = p->next;
	}
	ELNode* new_node = (ELNode*)malloc(sizeof(ELNode));
	// 如果申请空间失败
	if (new_node == NULL) {
		printf("Add edge failed. There is no more space.\n");
		return 0;
	}
	// 申请空间成功，设置新节点信息
	new_node->vertex = w;
	new_node->next = NULL;
	// 如果per不为空，说明上面的while循环有执行，g[v].list不为空
	// 此时per指向此边表的最后一个结点，将新结点接在后面
	if (per) {
		per->next = new_node;
	}
	// 如果per为空，说明上面的while循环没有执行，即g[v].list为空
	// 此时直接将g[v].list指向新结点，新结点为此边表的第一个结点
	else {
		g[v].list = new_node;
	}
	(g[w].in_degree)++;		// 将顶点w的入度加1
}

// 拓扑排序，成功返回1，否则返回0
int TopSort(Graph g) {
	// 设置一个栈用来保存入度为0的顶点的编号
	int stack[THT_NUMBER_OF_NODES] = { THT_NUMBER_OF_NODES };
	int top = 0;
	// 将所有入度为0的顶点编号入栈
	for (int i = 0; i < THT_NUMBER_OF_NODES; i++) {
		if (g[i].in_degree == 0) {
			stack[top++] = i;
		}
	}
	// 尝试每次去掉并输出一个入度为0的顶点，最多进行 THT_NUMBER_OF_NODES 次
	for (int i = 0; i < THT_NUMBER_OF_NODES; i++) {
		// 如果栈顶指针在0，说明图中不存在入度为0的顶点，即图中有环，无法进行拓扑排序
		if (top == 0) {
			printf("This Grapg has a cycle. Sort terminated.\n");
			return 0;
		}
		// 否则说明还存在入度为0的顶点，从栈中出一个
		int v = stack[--top];
		// 输出此入度为0的顶点
		// 此处直接输出课程编号类似“C1”、“C2”这种，下标从1开始，所以v+1
		printf("C%d ", v + 1);
		// 将此顶点的所有后继顶点的入度都减1
		ELNode* p = g[v].list;
		while (p) {
			int k = p->vertex;	// k为v的一个后继顶点
			(g[k].in_degree)--;
			// 如果此顶点的入度减为0了，就把此顶点入栈
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