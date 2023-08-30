#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list_queue.h"


// 顺序存储  双亲表示法
typedef struct TreeNode
{
	char data;  // 数据
	int parent; // 双亲节点下标
}TreeNode;

// 设计顺序树结构
typedef struct Tree
{
	TreeNode* arr;  // 存储节点的内存首地址
	size_t cal;    //  容量
	size_t cnt;    //  数量
}Tree;

//  创建树
Tree* create_tree(size_t cal)
{
	Tree* tree = malloc(sizeof(Tree));
	tree->arr = malloc(sizeof(TreeNode)*cal);
	tree->cal = cal;
	tree->cnt = 0;
	return tree;
}

// 添加 
bool add_tree(Tree* tree,char data,char parent)
{
	// 树不存在满的情况，可以扩容
	if(tree->cnt >= tree->cal)
	{
		tree->cal *= 2;
		tree->arr = realloc(tree->arr,sizeof(TreeNode)*tree->cal);
	}
	
	// 根节点没有双亲，约定根节点的双亲data为'\0'
	if('\0' == parent)
	{
		tree->arr[0].data = data;
		tree->arr[0].parent = -1;
		tree->cnt = 1;
		return true;
	}

	for(int i=0; i<tree->cnt; i++)
	{
		if(tree->arr[i].data == parent)
		{
			tree->arr[tree->cnt].data = data;
			tree->arr[tree->cnt++].parent = i;
			return true;
		}
	}
	return false;
}

void show_tree(Tree* tree)
{
	for(int i=0; i<tree->cnt; i++)
	{
		printf("index:%d data:%c parent:%d\n",i,tree->arr[i].data,tree->arr[i].parent);
	}
}

// 计算节点的度
int node_count(Tree* tree,char data)
{
	int index = -1,count = 0;
	for(int i=0; i<tree->cnt; i++)
	{
		if(tree->arr[i].data == data)
		{
			index = i;
			break;
		}
	}
	if(-1 == index) return -1;
	for(int i=index+1; i<tree->cnt; i++)
	{
		if(tree->arr[i].parent == index) count++; 
	}
	return count;
}

// 层序遍历一颗普通树，普通树没有前、中、后序遍历
void layer_show_tree(Tree* tree)
{
	// 创建一个队列
	ListQueue* queue = create_list_queue();
	// 先让根节点入队	
	push_list_queue(queue,tree->arr[0].data);

	// 一直循环直到队列为空
	while(!empty_list_queue(queue))
	{	
		// 把队头所有子节点入队
		char data = front_list_queue(queue);
		// 找出队头节点的下标
		int index = -1;
		for(int i=0; i<tree->cnt; i++)
		{
			if(data == tree->arr[i].data)
			{
				index = i;
				break;
			}
		}
		// 找队头节点的所有子节点入队
		for(int i=index+1; i<tree->cnt; i++)
		{
			if(tree->arr[i].parent == index) push_list_queue(queue,tree->arr[i].data);
		}
		// 把队头打印并出队
		printf("%c ",data);
		pop_list_queue(queue);
	}
		// 销毁队列结束
	destroy_list_queue(queue);
}

int main(int argc,const char* argv[])
{
	Tree* tree = create_tree(5);
	add_tree(tree,'A','\0');
	add_tree(tree,'B','A');
	add_tree(tree,'C','A');
	add_tree(tree,'D','A');
	add_tree(tree,'E','B');
	add_tree(tree,'F','B');
	add_tree(tree,'G','C');
	add_tree(tree,'H','D');
	add_tree(tree,'I','D');
	add_tree(tree,'J','E');
	add_tree(tree,'K','G');
	show_tree(tree);
	printf("count:%d\n",node_count(tree,'A'));

	layer_show_tree(tree);
	return 0;
}
