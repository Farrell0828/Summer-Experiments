#include <stdio.h>
#include <stdlib.h>

// 二叉树结点结构定义
typedef struct TreeNode {
	int data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

typedef TreeNode* BinTree;

// 将value插入到二叉树t中,插入成功返回1，否则返回0
int InsertNode(BinTree& t, int value) {
	// 如果树为空，新建结点并将结点值设为value
	if (t == NULL) {
		t = (BinTree)malloc(sizeof(TreeNode));
		t->data = value;
		t->lchild = NULL;
		t->rchild = NULL;
		return 1;
	}
	// 如果value值与结点的date值相等，则不需要再插入这个value
	else if (t->data == value) {
		printf("Failed to insert %d. Already have it in the tree.\n", value);
		return 0;
	}
	// 如果value值比当前结点t的data值小，则将value插入到t的左子树中
	else if (value < t->data) {
		return (InsertNode(t->lchild, value));
	}
	// 反之，则将value插入到t的右子树中
	else {
		return (InsertNode(t->rchild, value));
	}
}

// 在二叉树t中查找结点data值等于value的结点，成功则返回指向所在结点的指针，否则返回NULL
TreeNode* SearchNode(BinTree t, int value) {
	// 如果t为空，查找失败，返回NULL
	if (t == NULL) {
		return NULL;
	}
	// 如果value值与结点的date值相等，查找成功，返回指向当前结点的指针
	else if (value == t->data) {
		return t;
	}
	// 如果value值比当前结点t的data值小，在左子树中继续查找vlaue
	else if (value < t->data) {
		return (SearchNode(t->lchild, value));
	}
	// 如果value值比当前结点t的data值大，在右子树中继续查找vlaue
	else {
		return (SearchNode(t->rchild, value));
	}
}

// 在二叉树t中查找结点node的父结点，若存在则返回指向父结点的指针，否则返回NULL
TreeNode* FindParentNode(BinTree t, TreeNode* node) {
	// 根结点没有父结点，返回NULL；t为空树，返回NULL
	if (node == t || t == NULL) {
		return NULL;
	}
	// 如果t就是node的父结点，返回t
	else if (t->lchild == node || t->rchild == node) {
		return t;
	}
	// 否则在t的左右子树中分别查找node的父结点，两边至多有一个返回非NULL值
	// 若存在非NULL值则此值即为node的父结点指针，若两边都为NULL则t中不存在node的父结点，返回NULL
	else {
		TreeNode* left = FindParentNode(t->lchild, node);
		TreeNode* right = FindParentNode(t->rchild, node);
		return left ? left : right;
	}
}

// 删除二叉树t中结点data值等于value的结点，并调整结点结构使t仍满足二叉排序树的性质
// 若删除成功则返回1，否则返回0
int DeleteNode(BinTree &t, int value) {
	TreeNode* location = SearchNode(t, value);
	TreeNode* parent = FindParentNode(t, location);
	// 如果t中没搜索到value
	if (location == NULL) {
		printf("Failed to delete. There is no node with the date value %d.\n", value);
		return 0;
	}
	// 如果需删除结点为叶子结点
	if (location->lchild == NULL && location->rchild == NULL) {
		// 若parent==NULL说明此时location==t
		if (parent == NULL) {
			t = NULL;
		}
		// 若location为parent的左子树
		else if (parent->lchild == location) {
			parent->lchild = NULL;
		}
		// 否则为右子树
		else {
			parent->rchild = NULL;
		}
	}
	// 若需删除结点左子树为空而右子树不为空
	else if (location->lchild == NULL && location->rchild != NULL) {
		// 若parent==NULL说明此时location==t
		if (parent == NULL) {
			t = location->rchild;
		}
		// 若location为parent的左子树
		else if (parent->lchild == location) {
			parent->lchild = location->rchild;
		}
		// 否则为右子树
		else {
			parent->rchild = location->rchild;
		}
	}
	// 若需删除结点右子树为空而左子树不为空
	else if (location->rchild == NULL && location->lchild != NULL) {
		// 若parent==NULL说明此时location==t
		if (parent == NULL) {
			t = location->lchild;
		}
		// 若location为parent的左子树
		else if (parent->lchild == location) {
			parent->lchild = location->lchild;
		}
		// 否则为右子树
		else {
			parent->rchild = location->lchild;
		}
	}
	// 如果左右子树都不为空
	else {
		TreeNode* replace = location->lchild;
		TreeNode* replace_parent = location;
		// 寻找location的左子树的最右结点replace以及replace的父结点replace_parent
		while (replace->rchild != NULL) {
			replace_parent = replace;
			replace = replace->rchild;
		}
		// 若parent==NULL说明此时location==t
		if (parent == NULL) {
			t = replace;
		}
		// 若location为parent的左子树
		else if (parent->lchild == location) {
			parent->lchild = replace;
		}
		// 否则为右子树
		else {
			parent->rchild = replace;
		}
		// 替代结点的有指针指向需删除结点的右子树
		replace->rchild = location->rchild;
		// 如果替代结点的父结点不是需删除结点
		if (replace_parent != location) {
			// 将替代结点父结点原本指向替代结点的指针指向替代结点的左子树
			if (replace_parent->lchild == replace) {
				replace_parent->lchild = replace->lchild;
			}
			else {
				replace_parent->rchild = replace->lchild;
			}
			// 将替代结点的左指针指向需删除结点的左孩子
			replace->lchild = location->lchild;
		}
	}
	// 释放需删除结点空间
	free(location);
	return 1;
}

void Inorder(BinTree t) {
	if (t) {
		Inorder(t->lchild);
		printf("%d ", t->data);
		Inorder(t->rchild);
	}
}

int main() {
	BinTree a = NULL;
	a = (TreeNode*)malloc(sizeof(TreeNode));
	a->data = 5;
	a->lchild = NULL;
	a->rchild = NULL;
	Inorder(a);

	printf("Please enter integer sequence. Separated by \"Enter\" or \"Space\", \n");
	printf("and End with any non-numeric character: \n");
	int temp;
	BinTree t = NULL;
	while (scanf("%d", &temp) == 1) {
		InsertNode(t, temp);
		Inorder(t);
		printf("\n");
	}

	if (SearchNode(t, 78)) {
		printf("Search 78 done. Finded.\n");
	}
	else {
		printf("Search 78 done. Did't find.\n");
	}

	if (DeleteNode(t, 90)) {
		printf("Delete 90 done.\n");
		Inorder(t);
	}
	else {
		printf("Faile to delete 90. Does not exist.\n");
	}

	system("pause");
	return 0;
}