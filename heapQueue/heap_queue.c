#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include "zend_alloc.h"

#define MAX_IDLE_RATE 50
/**
 * 保存数据的结构体
 * 
 */ 
typedef struct brucket
{
    void *data;/* 存储 PHPzval的指针 */
    int  score;/* 记录分数 用来构建二叉堆的有序性*/
    int  status;/* 1 正常状态，0为初始化状态 */
    //struct brucket *next;
} brucket_t;

/**
 * 二叉堆的信息 
 */
typedef struct heapTable
{
    brucket_t **arHeap; /* 指向存储brucket的头指针 */
    int tablezSize; /* 数据大小 */
    int validSize;  /* 实际使用的有效数 */
    int brucketNum; /* 存储的单元数 */
    int idleRate; /* 空闲比率 */
} heapTable_t;

void heap_space_optimization(heapTable_t *heap);

/**
 *初始化 
 * 
 */
heapTable_t * heap_init(int minNum)
{
    heapTable_t *heap = emalloc(sizeof(heapTable_t));
    if(!heap) {
        //printf("heap init error\n");
        return NULL;
    }
    heap->brucketNum = 0;
    heap->tablezSize = minNum;
    heap->idleRate   = MAX_IDLE_RATE;
    heap->validSize  = 0;
    /* 默认初始化的存储大小*/
    heap->arHeap = emalloc(minNum * sizeof(brucket_t));
    if(!heap->arHeap) {
        return NULL;
       // printf("heap->arHeap init error\n");
    }
    return heap;
}

/**
 * 插入数据
 * 
 */ 
int heap_insert(heapTable_t *heap,void *data,int score)
{
    brucket_t *br = emalloc(sizeof(brucket_t));
    br->data   = data;
    br->score  = score;
    br->status = 1;
    if (!br) {
        //printf("inset brucket error\n");
        return -1;
    }

    /**
     * 扩充内存
     */ 
    if (heap->validSize == heap->tablezSize) {
       // printf("%d\n",heap->tablezSize);
        heap->tablezSize  = heap->tablezSize * 2;
        //printf("%d\n",heap->tablezSize);
        heap->arHeap = erealloc(heap->arHeap,heap->tablezSize * sizeof(brucket_t));
        if (!heap->arHeap) {
            return -1;/* 扩充内存出错 */
        }
    }

    heap->arHeap[heap->validSize] = br;
    heap->brucketNum++;
    int i = heap->validSize;
    //printf("插入成功\n");
    while (i >= 0)
    {
        int j = (i - 1) / 2;
        if(j>=0 && heap->arHeap[i]->score < heap->arHeap[j]->score) {
            brucket_t *tmp   = heap->arHeap[j];
            heap->arHeap[j] = heap->arHeap[i];
            heap->arHeap[i] = tmp;
            i = j;
        } else {
            break;
        }
    }

    php_printf("head==%d\n", heap->arHeap[0]->score);

    heap->validSize++;
    return 1;
    
}

/**
 * 取一个值
 */ 
int heap_pop(heapTable_t *heap, void **data)
{
    if(heap->validSize == 0) {
        return 0;
    }

    int maxTableSize   = heap->validSize - 1;
    brucket_t *head    = heap->arHeap[0];
    brucket_t *lastBru = heap->arHeap[maxTableSize];
    int index = 0;
    while (2 * index <= maxTableSize)
    {
        int left  = 2 * index + 1;
        int right = 2 * index + 2;
        int t = left;
        if (right <= maxTableSize && heap->arHeap[right]->status == 1 && heap->arHeap[right]->score < heap->arHeap[left]->score)
        {
            t = right;
        }

        if (lastBru->score > heap->arHeap[index]->score) {
            heap->arHeap[index] = heap->arHeap[t];
            index = t;
        } else {
            break;
        }

    }

   

    heap->brucketNum--;
    heap->arHeap[index] = lastBru;
    heap->validSize = maxTableSize;

    heap->arHeap[maxTableSize] = NULL;
    *data = head->data;
    php_printf("head==%d\n", head->score);
    efree(head);
    
    /**
     * 优化内存，后期加定时器优化
     */ 
    heap_space_optimization(heap);
    // test *dd = *data;
    //printf(":::***::%d::***::\n", ((test *)*data)->a);
    //printf(":---::::%d:::---:\n",((test *)heap->arHeap[maxTableSize-1]->data)->v);
    
    
    return 1;

}


int heap_count(heapTable_t *heap) 
{
    return heap->validSize;
}

int heap_size(heapTable_t *heap) 
{
    return heap->tablezSize;
}

/**
 * 释放所有数据内存
 */ 
void heap_free(heapTable_t *heap, int allFree) 
{
    for (int i = 0; i < heap->tablezSize; i++)
    {
        heap->brucketNum--;
        heap->validSize--;
        efree(heap->arHeap[i]);
    }
    if (allFree) {
        efree(heap->arHeap);
        efree(heap);
    }
    
}


/**
 * 回收内存
 */ 
void heap_space_optimization(heapTable_t *heap)
{
    //计算比例
    int ratio = (heap->validSize / (heap->tablezSize * 1.0)) * 100;
    //无效内存占有率是否大于预设值
    if ((100-ratio) >= heap->idleRate) {
        int minusNum     = ((heap->idleRate / 100.00) * heap->tablezSize) / 2;
        int index        = heap->tablezSize - minusNum;
        heap->tablezSize = index;
        for (int i = index; i < heap->tablezSize; i++)
        {
            free(heap->arHeap[i]);
        }

        heap->arHeap = erealloc(heap->arHeap, heap->tablezSize * sizeof(brucket_t));        
    }

}