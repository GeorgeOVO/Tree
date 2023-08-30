#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 有序二叉树
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

void _insert(TreeNode** root,TreeNode* node)
{
	if(NULL == node) return;
	if(NULL == *root)
	{
		*root = node;
		return;
	}

	if((*root)->data > node->data)
		_insert(&((*root)->left),node);
	else	
		_insert(&((*root)->right),node);
}

// 插入
void insert_tree(TreeNode** root,int data)
{
/*	if(NULL == *root)
	{
		TreeNode* node = create_node(data);
		*root = node;
		return;
	}

	if((*root)->data > data)
		insert_tree(&((*root)->left),data);
	else	
		insert_tree(&((*root)->right),data);
*/
	_insert(root,create_node(data));
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

void lrd_show(TreeNode* root)
{
	if(NULL == root) return;
	lrd_show(root->left);
	lrd_show(root->right);
	printf("%d ",root->data);
}

// 查找
bool search_tree(TreeNode* root,int data)
{
	if(NULL == root) return false;
	if(root->data == data) return true;

	if(root->data > data)
		return search_tree(root->left,data);
	return search_tree(root->right,data);
}

// 高度
int hight_tree(TreeNode* root)
{
	if(NULL == root) return 0;
	int lh = hight_tree(root->left);
	int rh = hight_tree(root->right);
	return lh>rh ? lh+1:rh+1;
}

// 密度
// 销毁

bool _access(TreeNode* root,size_t index,int* ptr,int* count)
{
	if(NULL == root) return false;
	if(_access(root->left,index,ptr,count)) return true;
	if((*count)++ == index)
	{
		*ptr = root->data;
		return true;
	}
	return _access(root->right,index,ptr,count);
}

// 按中序访问第index个节点数据
bool access_ldr_tree(TreeNode* root,size_t index,int* ptr)
{
	int count = 0;
	return _access(root,index,ptr,&count);
}

// 按值删除
bool del_value_tree(TreeNode** root,int data)
{
	if(NULL == *root) return false;
	if((*root)->data == data)
	{
		TreeNode* temp = *root;
		*root = temp->left;
		_insert(root,temp->right);
		free(temp);
		return true;
	}
	if(data < (*root)->data)
		return del_value_tree(&((*root)->left),data);
	return del_value_tree(&((*root)->right),data);
}

// 判断是否平衡
// 左右子树高度差不超过1 并且所有子树都满足 则平衡
bool is_AVL(TreeNode* root)
{
	if(NULL == root) return true;
	int lh = hight_tree(root->left);
	int rh = hight_tree(root->right);
	return abs(lh-rh) <= 1 && is_AVL(root->left) && is_AVL(root->right);
}

int main(int argc,const char* argv[])
{
	TreeNode* root = NULL;
	for(int i=0; i<5; i++)
	{
		int num = rand()%100;
		printf("%d ",num);
		insert_tree(&root,num);
	}	
	printf("\n");
	dlr_show(root);
	printf("\n");
	ldr_show(root);
	printf("\n");
	lrd_show(root);
	printf("\n");
	printf("AVL:%d\n",is_AVL(root));
//	printf("%d\n",search_tree(root,21));
//	int num = -100;
//	access_ldr_tree(root,3,&num);
//	printf("%d\n",num);
//	del_value_tree(&root,83);
//	ldr_show(root);
	return 0;
}
