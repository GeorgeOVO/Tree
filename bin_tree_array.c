#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_queue.h"

#define TREE_TYPE char
#define EMPTY '#'
#define PH "%c "

// 顺序存储二叉树结构
typedef struct BinTree
{
	TREE_TYPE* arr;
	size_t cal;
}BinTree;

// 通过以完全二叉树的格式层序遍历的结果来构建二叉树
BinTree* create_tree(TREE_TYPE* arr,size_t len)
{
	BinTree* tree = malloc(sizeof(BinTree));
	tree->arr = malloc(sizeof(TREE_TYPE)*len);
	tree->cal = len;
	memcpy(tree->arr,arr,sizeof(TREE_TYPE)*len);
	return tree;
}

// 从tree的编号为number的节点开始 进行前序遍历
void _dlr_show(BinTree* tree,size_t number)
{
	if(0 == number || number > tree->cal || EMPTY == tree->arr[number-1]) return;
	// 编号与下标相差1
	// 遍历根
   	printf("%c ",tree->arr[number-1]);
	// 遍历左
	_dlr_show(tree,number*2);
	// 遍历右
	_dlr_show(tree,number*2+1);
}
// 前序
void dlr_show(BinTree* tree)
{
	_dlr_show(tree,1);
}

void _ldr_show(BinTree* tree,size_t number)
{
	if(0 == number || number > tree->cal || EMPTY == tree->arr[number-1]) return;
	 _ldr_show(tree,number*2);
	printf("%c ",tree->arr[number-1]);
	_ldr_show(tree,number*2+1);
}

// 中序
void ldr_show(BinTree* tree)
{
	_ldr_show(tree,1);
}

void _lrd_show(BinTree* tree,size_t number)
{
	if(0 == number || number > tree->cal || EMPTY == tree->arr[number-1]) return;
     _lrd_show(tree,number*2);
	 _lrd_show(tree,number*2+1);
	 printf("%c ",tree->arr[number-1]);
}

// 后序
void lrd_show(BinTree* tree)
{
	_lrd_show(tree,1);
}

// 层序遍历
void layer_show(BinTree* tree)
{
	ListQueue* queue = create_list_queue();
	// 把根节点的编号入队
	push_list_queue(queue,1);
	while(!empty_list_queue(queue))
	{
		// 获取队头
		int number = front_list_queue(queue);
		// 计算左子树编号，存在就入队
		int left = number*2;
		if(left-1 < tree->cal && EMPTY != tree->arr[left-1])
		   push_list_queue(queue,left);	
		// 计算右子树编号，存在就入队
		int right = number*2+1;
		if(right-1 < tree->cal && EMPTY != tree->arr[right-1])
		   push_list_queue(queue,right);
		// 显示队头  出队
		printf(PH,tree->arr[number-1]);
		pop_list_queue(queue);	
	}
	destroy_list_queue(queue);
	printf("\n");
}

// 计算编号number节点的高度
int _hight_tree(BinTree* tree,size_t number)
{
	if(number-1 >= tree->cal || EMPTY == tree->arr[number-1])
		return 0;
	int lh = _hight_tree(tree,number*2);
	int rh = _hight_tree(tree,number*2+1);
	return lh > rh ? lh+1:rh+1;
}

// 树的高度
int hight_tree(BinTree* tree)
{
	return _hight_tree(tree,1);
}

int _density_tree(BinTree* tree,int number)
{
	if(number-1 >= tree->cal || EMPTY == tree->arr[number-1])
		return 0;
	int ld = _density_tree(tree,number*2);
	int rd = _density_tree(tree,number*2+1);
	return ld+rd+1;
}

// 树的密度
int density_tree(BinTree* tree)
{
	return _density_tree(tree,1);
}

// 插入  只能插在pdata的左右子树的空位置
bool insert_tree(BinTree* tree,TREE_TYPE pdata,TREE_TYPE data)
{
	// 如果要插入的位置超过容量  要扩容且初始化为#
}

// 删除  只能删除叶子节点
bool delete_tree(BinTree* tree,TREE_TYPE data)
{
	
}

// 求左子树节点的下标
int left_tree(BinTree* tree,TREE_TYPE data)
{
		
}

// 根据下标求节点的data
TREE_TYPE node_data(BinTree* tree,int index)
{
	
}

int main(int argc,const char* argv[])
{
	char* str = "ABCDE#FG#HI";
	BinTree* tree = create_tree(str,strlen(str));	
/*	dlr_show(tree);
	puts("");
	ldr_show(tree);
	puts("");
	lrd_show(tree);
*/
	layer_show(tree);
	printf("hight:%d\n",hight_tree(tree));
	printf("density:%d\n",density_tree(tree));
	return 0;
}
