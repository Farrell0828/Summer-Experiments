#include <stdio.h>
#include <stdlib.h>

// ���������ṹ����
typedef struct TreeNode {
	int data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

typedef TreeNode* BinTree;

// ��value���뵽������t��,����ɹ�����1�����򷵻�0
int InsertNode(BinTree& t, int value) {
	// �����Ϊ�գ��½���㲢�����ֵ��Ϊvalue
	if (t == NULL) {
		t = (BinTree)malloc(sizeof(TreeNode));
		t->data = value;
		t->lchild = NULL;
		t->rchild = NULL;
		return 1;
	}
	// ���valueֵ�����dateֵ��ȣ�����Ҫ�ٲ������value
	else if (t->data == value) {
		printf("Failed to insert %d. Already have it in the tree.\n", value);
		return 0;
	}
	// ���valueֵ�ȵ�ǰ���t��dataֵС����value���뵽t����������
	else if (value < t->data) {
		return (InsertNode(t->lchild, value));
	}
	// ��֮����value���뵽t����������
	else {
		return (InsertNode(t->rchild, value));
	}
}

// �ڶ�����t�в��ҽ��dataֵ����value�Ľ�㣬�ɹ��򷵻�ָ�����ڽ���ָ�룬���򷵻�NULL
TreeNode* SearchNode(BinTree t, int value) {
	// ���tΪ�գ�����ʧ�ܣ�����NULL
	if (t == NULL) {
		return NULL;
	}
	// ���valueֵ�����dateֵ��ȣ����ҳɹ�������ָ��ǰ����ָ��
	else if (value == t->data) {
		return t;
	}
	// ���valueֵ�ȵ�ǰ���t��dataֵС�����������м�������vlaue
	else if (value < t->data) {
		return (SearchNode(t->lchild, value));
	}
	// ���valueֵ�ȵ�ǰ���t��dataֵ�����������м�������vlaue
	else {
		return (SearchNode(t->rchild, value));
	}
}

// �ڶ�����t�в��ҽ��node�ĸ���㣬�������򷵻�ָ�򸸽���ָ�룬���򷵻�NULL
TreeNode* FindParentNode(BinTree t, TreeNode* node) {
	// �����û�и���㣬����NULL��tΪ����������NULL
	if (node == t || t == NULL) {
		return NULL;
	}
	// ���t����node�ĸ���㣬����t
	else if (t->lchild == node || t->rchild == node) {
		return t;
	}
	// ������t�����������зֱ����node�ĸ���㣬����������һ�����ط�NULLֵ
	// �����ڷ�NULLֵ���ֵ��Ϊnode�ĸ����ָ�룬�����߶�ΪNULL��t�в�����node�ĸ���㣬����NULL
	else {
		TreeNode* left = FindParentNode(t->lchild, node);
		TreeNode* right = FindParentNode(t->rchild, node);
		return left ? left : right;
	}
}

// ɾ��������t�н��dataֵ����value�Ľ�㣬���������ṹʹt���������������������
// ��ɾ���ɹ��򷵻�1�����򷵻�0
int DeleteNode(BinTree &t, int value) {
	TreeNode* location = SearchNode(t, value);
	TreeNode* parent = FindParentNode(t, location);
	// ���t��û������value
	if (location == NULL) {
		printf("Failed to delete. There is no node with the date value %d.\n", value);
		return 0;
	}
	// �����ɾ�����ΪҶ�ӽ��
	if (location->lchild == NULL && location->rchild == NULL) {
		// ��parent==NULL˵����ʱlocation==t
		if (parent == NULL) {
			t = NULL;
		}
		// ��locationΪparent��������
		else if (parent->lchild == location) {
			parent->lchild = NULL;
		}
		// ����Ϊ������
		else {
			parent->rchild = NULL;
		}
	}
	// ����ɾ�����������Ϊ�ն���������Ϊ��
	else if (location->lchild == NULL && location->rchild != NULL) {
		// ��parent==NULL˵����ʱlocation==t
		if (parent == NULL) {
			t = location->rchild;
		}
		// ��locationΪparent��������
		else if (parent->lchild == location) {
			parent->lchild = location->rchild;
		}
		// ����Ϊ������
		else {
			parent->rchild = location->rchild;
		}
	}
	// ����ɾ�����������Ϊ�ն���������Ϊ��
	else if (location->rchild == NULL && location->lchild != NULL) {
		// ��parent==NULL˵����ʱlocation==t
		if (parent == NULL) {
			t = location->lchild;
		}
		// ��locationΪparent��������
		else if (parent->lchild == location) {
			parent->lchild = location->lchild;
		}
		// ����Ϊ������
		else {
			parent->rchild = location->lchild;
		}
	}
	// ���������������Ϊ��
	else {
		TreeNode* replace = location->lchild;
		TreeNode* replace_parent = location;
		// Ѱ��location�������������ҽ��replace�Լ�replace�ĸ����replace_parent
		while (replace->rchild != NULL) {
			replace_parent = replace;
			replace = replace->rchild;
		}
		// ��parent==NULL˵����ʱlocation==t
		if (parent == NULL) {
			t = replace;
		}
		// ��locationΪparent��������
		else if (parent->lchild == location) {
			parent->lchild = replace;
		}
		// ����Ϊ������
		else {
			parent->rchild = replace;
		}
		// ���������ָ��ָ����ɾ������������
		replace->rchild = location->rchild;
		// ���������ĸ���㲻����ɾ�����
		if (replace_parent != location) {
			// �������㸸���ԭ��ָ���������ָ��ָ���������������
			if (replace_parent->lchild == replace) {
				replace_parent->lchild = replace->lchild;
			}
			else {
				replace_parent->rchild = replace->lchild;
			}
			// �����������ָ��ָ����ɾ����������
			replace->lchild = location->lchild;
		}
	}
	// �ͷ���ɾ�����ռ�
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