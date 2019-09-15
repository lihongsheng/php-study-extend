#include <stdlib.h>

typedef struct list_node_tag
{
    void *data;
    /**
     * 队列的下一指针
     */ 
    struct list_node_tag *next;
    /* data */
} list_node;


typedef struct list
{
    /* data */
    /**
     * 队列的头指针
     */ 
    list_node *head;
    /**
     * 队列的数据量
     */ 
    int count;
} list_t;


list_t *create_list()
{
    list_t *returnVal;
    returnVal = malloc(sizeof(list_t));
    if (returnVal) {
        returnVal->count = 0;
        returnVal->head  = NULL;
    }
    return returnVal;
}

/**
 * 入队列
 */ 
int list_push(list_t *ls, void *data)
{
    list_node *node;
    /**
     * 申请内存
     */ 
    node = malloc(sizeof(list_node));
    if (!node) {
        printf("push获取内存错误\n");
        return 0;
    }

    node->data = data;
    node->next =  NULL;

    list_node *lastNode;
    if (ls->head == NULL) {
        ls->head = node;
    } else {
        lastNode = ls->head;
        while (lastNode->next)
        {
            lastNode = lastNode->next;
        }
        lastNode->next = node;
    }
   ls->count++;
   return 1;
}


/**
 * 出队列
 */ 
int list_pop(list_t *ls,void **data)
{
    if (ls->count <= 0) {
        return 0;
    }

    if (ls->head) {
        list_node *node;
        node = ls->head;
        ls->head = ls->head->next;
        ls->count--;
        
        *data = node->data;
        free(node);
        return 1;
    }

    return 0;

}

void list_free(list_t *ls)
{
    list_node *lastNode;
    list_node *tmp;
    lastNode = ls->head;
    ls->head = NULL;
    while (lastNode)
    {
        tmp      = lastNode;
        ls->count--;
        lastNode = lastNode->next;
        free(tmp);
        /* code */
    }
    free(ls);
    
}

int list_count(list_t *ls)
{
    return ls->count;
}

