#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TREE_TYPE char
#define PH "%c "
#define EMPTY '#'

// 设计二叉树节点
typedef struct TreeNode
{
	TREE_TYPE data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

// 创建节点
TreeNode* create_tree_node(TREE_TYPE data)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// 按前序构建一棵树 返回该树的根节点
TreeNode* create_dlr_tree(void)
{
	TREE_TYPE data = 0;
	scanf("%c",&data);
	if(EMPTY == data) return NULL;

	TreeNode* node = create_tree_node(data);
	node->left = create_dlr_tree();
	node->right = create_dlr_tree();
	return node;	
}

TreeNode* _create(const char** str)
{
	if(EMPTY == **str || '\0' == **str) return NULL;
	TreeNode* node = create_tree_node(**str);
	*str += 1;
	node->left = _create(str);
	*str += 1;
	node->right = _create(str);
	return node;
}

// 由调用者提供的前序遍历的结果  构建二叉树
TreeNode* create_dlr_tree_str(const char* str)
{
	_create(&str);
}

// 前序遍历
void dlr_show(TreeNode* root)
{
	if(NULL == root) return;
	printf(PH,root->data);
	dlr_show(root->left);
	dlr_show(root->right);
}

// 中序遍历
void ldr_show(TreeNode* root)
{
	if(NULL == root) return;
	ldr_show(root->left);
	printf(PH,root->data);
	ldr_show(root->right);
}

// 后序遍历
void lrd_show(TreeNode* root)
{
	if(NULL == root) return;
	lrd_show(root->left);
	lrd_show(root->right);
	printf(PH,root->data);
}

// 求高度
int hight_tree(TreeNode* root)
{
	if(NULL == root) return 0;
	int lh = hight_tree(root->left);
	int rh = hight_tree(root->right);
	return lh > rh ? lh+1:rh+1;
}

// 求密度
int density_tree(TreeNode* root)
{
	if(NULL == root) return 0;
	int ld = density_tree(root->left);
	int rd = density_tree(root->right);
	return ld+rd+1;
}

// 插入
bool insert_tree(TreeNode* root,TREE_TYPE pdata,TREE_TYPE data)
{
	if(NULL == root) return false;
	if(pdata == root->data)
	{
		if(NULL == root->left)
		{
			root->left = create_tree_node(data);
			return true;
		}
		if(NULL == root->right)
		{
			root->right = create_tree_node(data);
			return true;
		}
		return false;
	}
	return insert_tree(root->left,pdata,data) || insert_tree(root->right,pdata,data);
}

// 删除 只删叶子节点
bool delete_tree(TreeNode** root,TREE_TYPE data)
{
	if(NULL == *root) return false;
	if(data == (*root)->data)
	{
		if((*root)->left || (*root)->right) return false;
		free(*root);
		*root = NULL;
		return true;
	}
	return delete_tree(&(*root)->left,data) || delete_tree(&(*root)->right,data);
}

// 销毁
void destroy_tree(TreeNode* root)
{
	if(NULL == root) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int main(int argc,const char* argv[])
{
//	TreeNode* root = create_dlr_tree();
	TreeNode* root = create_dlr_tree_str("ABDG###EH##I##C#F##");
	dlr_show(root);
	printf("\n");
	ldr_show(root);
	printf("\n");
	lrd_show(root);
	printf("\n");
	printf("hight:%d\n",hight_tree(root));
	printf("density:%d\n",density_tree(root));
	insert_tree(root,'D','J');
	delete_tree(&root,'F');
	dlr_show(root);
	printf("\n");
	return 0;
}
