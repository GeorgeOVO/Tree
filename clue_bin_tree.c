#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 线索二叉树

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
	bool rclue;  // 为真时  右子树是线索
}TreeNode;

TreeNode* create_node(int data)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->rclue = false;
	return node;
}

void _insert(TreeNode** root,TreeNode* node)
{
	if(NULL == node) return;
	if(NULL == *root)
	{
		*root = node;
		return;
	}
	if(node->data < (*root)->data)
		_insert(&((*root)->left),node);
	else
		_insert(&((*root)->right),node);
}

void insert_tree(TreeNode** root,int data)
{
	_insert(root,create_node(data));	
}

void ldr_show(TreeNode* root)
{
	if(NULL == root) return;
	ldr_show(root->left);
	printf("%d ",root->data);
	ldr_show(root->right);
}

// 按照中序  root的上一个节点
TreeNode* prev = NULL;

// 按照中序 遍历并创建线索 root是prev的下一个节点
void create_clue_ldr(TreeNode* root)
{
	if(NULL == root) return;
	// 左子树创建线索
	create_clue_ldr(root->left);

	// 根
	if(NULL != prev && NULL == prev->right)
	{
		// 创建线索
		prev->right = root;
		prev->rclue = true;
	}
	prev = root;

	// 右子树创建线索
	create_clue_ldr(root->right);
}

// 根据线索遍历
void clue_show(TreeNode* node)
{
	while(node)
	{
		while(node->left) node = node->left;
		printf("%d ",node->data);
		while(node->rclue)
		{
			node = node->right;
			printf("%d ",node->data);
		}
		node = node->right;
	}
}

int main(int argc,const char* argv[])
{
	TreeNode* root = NULL;
	for(int i=0; i<10; i++)
	{
		insert_tree(&root,rand()%100);
	}
	ldr_show(root);
	printf("\n");
	create_clue_ldr(root);
	clue_show(root);
	return 0;
}
