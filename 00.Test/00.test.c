#include<stdio.h>
#define n 27  //叶子数目
#define m (2*n-1)    //结点总数
#define maxval 10000.0
#define maxsize 100   //哈夫曼编码的最大位数
typedef struct
{
	char ch;
	float weight;
	int lchild, rchild, parent;
}hufmtree;

typedef struct
{
	char bits[n];   //位串
	int start;      //编码在位串中的起始位置
	char ch;        //字符
}codetype;

void huffman(hufmtree tree[]);//建立哈夫曼树
void huffmancode(codetype code[], hufmtree tree[]);//根据哈夫曼树求出哈夫曼编码
void decode(hufmtree tree[]);//依次读入电文，根据哈夫曼树译码

void main()
{
	printf("                            ——哈夫曼编码——\n");
	printf("总共有%d个字符\n", n);
	hufmtree tree[m];
	codetype code[n];
	int i, j;//循环变量
	huffman(tree);//建立哈夫曼树
	huffmancode(code, tree);//根据哈夫曼树求出哈夫曼编码
	printf("【输出每个字符的哈夫曼编码】\n");
	for (i = 0; i<n; i++)
	{
		printf("%c: ", code[i].ch);
		for (j = code[i].start; j<n; j++)
			printf("%c ", code[i].bits[j]);
		printf("\n");
	}
	printf("【读入电文，并进行译码】\n");
	decode(tree);//依次读入电文，根据哈夫曼树译码
}

void huffman(hufmtree tree[])//建立哈夫曼树
{
	int i, j, p1, p2;//p1,p2分别记住每次合并时权值最小和次小的两个根结点的下标
	float small1, small2, f;
	char c;
	for (i = 0; i<m; i++)    //初始化
	{
		tree[i].parent = 0;
		tree[i].lchild = -1;
		tree[i].rchild = -1;
		tree[i].weight = 0.0;
	}
	printf("【依次读入前%d个结点的字符及权值(中间用空格隔开)】\n", n);
	for (i = 0; i<n; i++)  //读入前n个结点的字符及权值
	{
		printf("输入第%d个字符为和权值", i + 1);
		scanf("%c %f", &c, &f);
		getchar();
		tree[i].ch = c;
		tree[i].weight = f;
	}
	for (i = n; i<m; i++)      //进行n-1次合并，产生n-1个新结点
	{
		p1 = 0; p2 = 0;
		small1 = maxval; small2 = maxval;   //maxval是float类型的最大值
		for (j = 0; j<i; j++)    //选出两个权值最小的根结点
			if (tree[j].parent == 0)
				if (tree[j].weight<small1)
				{
					small2 = small1;  //改变最小权、次小权及对应的位置
					small1 = tree[j].weight;
					p2 = p1;
					p1 = j;
				}
				else
					if (tree[j].weight<small2)
					{
						small2 = tree[j].weight;  //改变次小权及位置
						p2 = j;
					}
		tree[p1].parent = i;
		tree[p2].parent = i;
		tree[i].lchild = p1;  //最小权根结点是新结点的左孩子
		tree[i].rchild = p2;  //次小权根结点是新结点的右孩子
		tree[i].weight = tree[p1].weight + tree[p2].weight;
	}
}//huffman

void huffmancode(codetype code[], hufmtree tree[])//根据哈夫曼树求出哈夫曼编码
												  //codetype code[]为求出的哈夫曼编码
												  //hufmtree tree[]为已知的哈夫曼树
{
	int i, c, p;
	codetype cd;   //缓冲变量
	for (i = 0; i<n; i++)
	{
		cd.start = n;
		cd.ch = tree[i].ch;
		c = i;       //从叶结点出发向上回溯
		p = tree[i].parent;   //tree[p]是tree[i]的双亲
		while (p != 0)
		{
			cd.start--;
			if (tree[p].lchild == c)
				cd.bits[cd.start] = '0';   //tree[i]是左子树，生成代码'0'
			else
				cd.bits[cd.start] = '1';   //tree[i]是右子树，生成代码'1'
			c = p;
			p = tree[p].parent;
		}
		code[i] = cd;    //第i+1个字符的编码存入code[i]
	}
}//huffmancode

void decode(hufmtree tree[])//依次读入电文，根据哈夫曼树译码
{
	int i, j = 0;
	char b[maxsize];
	char endflag = '2';    //电文结束标志取2
	i = m - 1;             //从根结点开始往下搜索
	printf("输入发送的编码(以'2'为结束标志)：");
	gets(b);
	printf("译码后的字符为");
	while (b[j] != '2')
	{
		if (b[j] == '0')
			i = tree[i].lchild;   //走向左孩子
		else
			i = tree[i].rchild;   //走向右孩子
		if (tree[i].lchild == -1)     //tree[i]是叶结点
		{
			printf("%c", tree[i].ch);
			i = m - 1;      //回到根结点
		}
		j++;
	}
	printf("\n");
	if (tree[i].lchild != -1 && b[j] != '2')   //电文读完，但尚未到叶子结点
		printf("\nERROR\n");  //输入电文有错
}//decode