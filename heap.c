#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SWAP(a,b) {typeof(a) t=(a);(a)=(b);(b)=t;}

typedef struct Heap
{
	int* arr;
	size_t cal;
	size_t cnt;
}Heap;

// 创建
Heap* create_heap(size_t cal)
{
	Heap* heap = malloc(sizeof(Heap));
	heap->arr = malloc(sizeof(int)*cal);
	heap->cal = cal;
	heap->cnt = 0;
	return heap;
}

// 空堆
bool empty_heap(Heap* heap)
{
	return 0 == heap->cnt;
}

// 满堆
bool full_heap(Heap* heap)
{
	return heap->cnt >= heap->cal;
}

// 查看堆顶
int top_heap(Heap* heap)
{
	return heap->arr[0];
}

// 添加
bool add_heap(Heap* heap,int data)
{
	if(full_heap(heap)) return false;
	heap->arr[heap->cnt++] = data;

	// 重新从添加位置调整成堆结构
	int number = heap->cnt; // 编号
	while(number/2 >= 1)
	{
		if(heap->arr[number/2-1] < data)
		{
			SWAP(heap->arr[number/2-1],heap->arr[number-1]);
			number /= 2;
			continue;
		}
		return true;
	}
	return true;
}

// 删除堆顶 重新调整
bool del_heap(Heap* heap)
{
	if(empty_heap(heap)) return false;
	// 堆顶与末尾交换
	SWAP(heap->arr[0],heap->arr[heap->cnt-1]);
	// 删除末尾
	heap->cnt--;
	// 从堆顶开始 从上到下重新调整成堆
	int n = 1;  // 编号
	while(n-1 < heap->cnt)
	{
		// 有右  完全二叉树 有右就有左
		if(n*2 < heap->cnt)
		{
			// 左比右大 且比根大
			if(heap->arr[n*2-1] >= heap->arr[n*2] && heap->arr[n*2-1] > heap->arr[n-1])
			{
				SWAP(heap->arr[n*2-1],heap->arr[n-1]);
				n *= 2;
			}
			// 右比左大 且比根大
			else if(heap->arr[n*2] > heap->arr[n*2-1] && heap->arr[n*2] > heap->arr[n-1])
			{
				SWAP(heap->arr[n*2],heap->arr[n-1]);
				n = n*2+1;
			}
			else
				break;
		}
		// 只有左
		else if(n*2-1 < heap->cnt)
		{
			if(heap->arr[n*2-1] > heap->arr[n-1])
			{
				SWAP(heap->arr[n*2-1],heap->arr[n-1]);
				n *= 2;	
			}
			else
				break;
		}
		else  // 无左无右
			break;
	}
	return true;
}

// 查看
void show_heap(Heap* heap)
{
	for(int i=0; i<heap->cnt; i++)
	{
		printf("%d ",heap->arr[i]);
	}
	printf("\n");
}

// 堆排序
void heap_sort(int* arr,int len)
{
	// 把数组调整成堆结构
	for(int i=2; i<=len; i++) // i是编号
	{
		int j = i;
		while(j > 1)
		{
			if(arr[j/2-1] < arr[j-1])
			{
				SWAP(arr[j/2-1],arr[j-1]);
				j /= 2;
				continue;
			}
			break;
		}
	}
	// 堆顶交换末尾 从堆顶到末尾-1调整回堆 直到全部调整
	while(len > 1)
	{
		SWAP(arr[0],arr[len-1]);
		len--;

		int i = 1;
		while(i-1 < len)
		{
			if(i*2 < len)
			{
				if(arr[i*2] >= arr[i*2-1] && arr[i*2] > arr[i-1])
				{
					SWAP(arr[i*2],arr[i-1]);
					i = i*2+1;
				}
				else if(arr[i*2-1] > arr[i*2] && arr[i*2-1] > arr[i-1])
				{
					SWAP(arr[i*2-1],arr[i-1]);
					i = i*2;
				}
				else
					break;
			}
			else if(i*2-1 < len)
			{
				if(arr[i*2-1] > arr[i-1])
				{
					SWAP(arr[i*2-1],arr[i-1]);
					i *= 2;
				}
				else
					break;
			}
			else
				break;
		}
	}
}

// 对从top下标到end下标进行调整成堆
void _heap_sort(int* arr,int top,int end)
{
	if(top >= end) return;

	int max = top+1;  // 根、左、右中的最大值编号
	int l = max*2;    // 左子树编号
	int r = max*2+1;  // 右子树编号

	if(l-1 <= end && arr[l-1] > arr[max-1])
	{
		max = l;
	}
	if(r-1 <= end && arr[r-1] > arr[max-1])
	{
		max = r;
	}
	if(max != top+1)
	{
		// 最大值不是根
		SWAP(arr[top],arr[max-1]);
		_heap_sort(arr,max-1,end);
	}
}

// 递归实现 堆排序
void heap_sort_recursion(int* arr,int len)
{
	// 把数组调整成堆结构
	for(int i=2; i<=len; i++) // i是编号
	{
		int j = i;
		while(j > 1)
		{
			if(arr[j/2-1] < arr[j-1])
			{
				SWAP(arr[j/2-1],arr[j-1]);
				j /= 2;
				continue;
			}
			break;
		}
	}

	for(int i=len-1; i>=1; i--)
	{
		SWAP(arr[0],arr[i]);
		_heap_sort(arr,0,i-1);
	}
}

int main(int argc,const char* argv[])
{	
	int arr[10] = {};
	for(int i=0; i<10; i++)
	{
		arr[i] = rand()%100;
	}
//	heap_sort(arr,10);
	heap_sort_recursion(arr,10);
	for(int i=0; i<10; i++)
	{
		printf("%d ",arr[i]);
	}
	/*
	Heap* heap = create_heap(10);
	for(int i=0; i<10; i++)
	{
		add_heap(heap,rand()%100);
	}
	show_heap(heap);
	while(!empty_heap(heap))
	{
		printf("%d ",top_heap(heap));
		del_heap(heap);
	}
	*/
	return 0;
}
