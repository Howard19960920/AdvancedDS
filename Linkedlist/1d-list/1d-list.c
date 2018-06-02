// term frequency analysis using 1D linkedlist
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXLEN 1024
extern char *strdup(const char *__s);

typedef struct listNode
{
    int cnt;
    char *p2key;
    struct listNode *p2next;
}   listNode;

listNode *listFind(listNode *head, char *patt)
{
    if(head == NULL)
    {
        return NULL;
    }
    listNode *curr = head;
    while(curr != NULL)
    {
        if(strcmp(curr -> p2key, patt) == 0)
        {
            return curr;
        }
        curr = curr -> p2next;
    }
    return NULL;
}

void listAppend(listNode **head, listNode **tail, char *patt)
{
    listNode *temp = (listNode *) malloc(sizeof(listNode));
    assert(temp != NULL);
    temp -> p2key = strdup(patt);
    assert(temp -> p2key != NULL);
    temp -> cnt = 1;
    temp -> p2next = NULL;
    if((*head) == NULL)
    {
        (*head) = (*tail) = temp;
    }
    else
    {
        (*tail) -> p2next = temp;
        (*tail) = (*tail) -> p2next;
    }
}

int desc(const void *a, const void *b)
{
    return (*((listNode**)a)) -> cnt < (*((listNode**)b)) -> cnt;
}

int asce(const void *a, const void *b)
{
    return (*((listNode**)a)) -> cnt > (*((listNode**)b)) -> cnt;
}

void listShow(listNode *trav, int listlen, int (*cmp)(const void *a, const void *b))
{
    listNode **p2list = (listNode **) malloc(sizeof(listNode *) * listlen);
    assert(p2list != NULL);
    int idx = 0, i;
    while(trav != NULL)
    {
        p2list[idx++] = trav;
        trav = trav -> p2next;
    }
    if(cmp != NULL)
    {
        qsort(p2list, listlen, sizeof(p2list[0]), cmp);
    }
    for(i = 0; i < idx; i++)
    {
        printf("%d\t%s\n", p2list[i] -> cnt, p2list[i] -> p2key);
    }
    free(p2list);
}

void listFree(listNode *curr)
{
    listNode *prev;
    while(curr != NULL)
    {
        prev = curr;
        curr = curr -> p2next;
        free(prev -> p2key);
        free(prev);
    }
}

int main(int argc, char **argv)
{
    int listlen = 0;
    char buff[MAXLEN];
    listNode *head = NULL, *tail = NULL, *p2node = NULL;
    while(scanf("%s", buff) != EOF)
    {
        if((p2node = listFind(head, buff)) != NULL)
        {
            p2node -> cnt ++;
        }
        else
        {
            listAppend(&head, &tail, buff);
            listlen++;
        }
    }
    listShow(head, listlen, NULL);
    // listShow(head, listlen, asce);
    // listShow(head, listlen, desc);
    listFree(head);
    printf("%d\n", listlen);
    return 0;
}