#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

TreeNode* create_node(int data)
{
	TreeNode* node = malloc(sizeof(TreeNode));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// 高度
int hight_tree(TreeNode* root)
{
	if(NULL == root) return 0;
	int lh = hight_tree(root->left);
	int rh = hight_tree(root->right);
	return lh > rh ? lh+1:rh+1;
}

int balance(TreeNode* root)
{
	if(NULL == root) return 0;
	return hight_tree(root->left) - hight_tree(root->right);
}

// 右旋
TreeNode* right_rotate(TreeNode* x)
{
	TreeNode* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

// 左旋
TreeNode* left_rotate(TreeNode* x)
{
	TreeNode* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

// 自动平衡
TreeNode* auto_balance(TreeNode* x)
{
	if(NULL == x) return NULL;
	int lh = hight_tree(x->left);
	int rh = hight_tree(x->right);
	if(lh - rh > 1) // x的左比右高
	{
		// 情况1  y的左比右高
		if(balance(x->left) >= 1)
		{
			// 右旋
			x = right_rotate(x);
		}
		// 情况3  y的右比左高
		else
		{
			// 左旋
			x->left = left_rotate(x->left);
			// 右旋
			x = right_rotate(x);
		}
	}
	else if(rh - lh > 1) // x的右比左高
	{
		// 情况2  y的右比左高
		if(balance(x->right) <= -1)
		{
			// 左旋
			x = left_rotate(x);
		}
		// 情况4  y的左比右高
		else
		{
			// 右旋
			x->right = right_rotate(x->right);
			// 左旋
			x = left_rotate(x);
		}
	}
	return x;
}

// 添加 通过返回值 返回root的新地址 需要调用者重新接收 因此无需传递二级指针
TreeNode* add_tree(TreeNode* root,int data)
{
	if(NULL == root) 
		return create_node(data);
	if(data < root->data)
		root->left = add_tree(root->left,data);
	else
		root->right = add_tree(root->right,data);

	// 自动调整平衡
	root = auto_balance(root);
	return root;
}

/*
	删除节点
	1、待删除的节点是叶子节点，直接删除
	2、待删除的节点左或右子树为空，则使用非空节点替换原节点
	3、待删除的节点左右子树都非空，根据左右子树高度来选择左边最大值或右边最小值替换
	重新调整平衡
*/

TreeNode* max_tree(TreeNode* root)
{
	TreeNode* max = root;
	if(NULL == root) return NULL;
	while(NULL != max->right)
		max = root->right;
	return max;	
}

TreeNode* min_tree(TreeNode* root)
{
	TreeNode* min = root;
	if(NULL == root) return NULL;
	while(NULL != min->left)
		min = min->left;
	return min;	
	
}

TreeNode* del_tree(TreeNode* root,int data)
{
	if(NULL == root) return NULL;

	if(data == root->data)
	{
		// 左右子树为空
		if(NULL == root->left && NULL == root->right)
		{
			free(root);
			return NULL;
		}
		// 左子树为空
		if(NULL == root->left)
		{
			TreeNode* temp = root->right;
			free(root);
			return temp;	
		}
		// 右子树为空
		if(NULL == root->right)
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 左右子树非空
		int lh = hight_tree(root->left);
		int rh = hight_tree(root->right);
		if(lh >= rh)
		{
			// 替换左子树的最大值
			TreeNode* max = max_tree(root->left);
			root->data = max->data;
			root->left = del_tree(root->left,max->data);
		}
		else
		{
			// 替换右子树的最小值
			TreeNode* min = min_tree(root->right);
			root->data = min->data;
			root->right = del_tree(root->right,min->data);
		}
	}
	if(data < root->data)
		root->left = del_tree(root->left,data);
	else
		root->right = del_tree(root->right,data);
	root = auto_balance(root);
	return root;
}

void dlr_show(TreeNode* root)
{
	if(NULL == root) return;
	printf("%d ",root->data);
	dlr_show(root->left);
	dlr_show(root->right);
}

void ldr_show(TreeNode* root)
{
	if(NULL == root) return;
	ldr_show(root->left);
	printf("%d ",root->data);
	ldr_show(root->right);
}

int main(int argc,const char* argv[])
{
	TreeNode* root = NULL;
	for(int i=0; i<10; i++)
	{
		root = add_tree(root,i+1);
	}
	dlr_show(root);
	printf("\n");
	ldr_show(root);
	printf("\n");
	return 0;
}
