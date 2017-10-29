#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


extern char *strdup(const char *_s);


typedef struct dt_linkedlist
{

  char *name, *phone;
  struct dt_linkedlist *next;

} dt_linkedlist;


typedef struct dt_hashtable
{

  int counter;
  struct dt_linkedlist *head, *tail;

} dt_hashtable;


typedef long long lld;


void showHashtable(dt_hashtable **ptht, const int hsize)
{
  int i, j;
  dt_linkedlist *p;
  for(i = 0; i < hsize; i++)
  {
    if(ptht[i] == NULL)
    {
      printf("[%d] => NULL\n", i);
    }

    else
    {
      j = 0;
      printf("[%d] => ", i);
      for(p = ptht[i]->head; p != NULL;)
      {
        printf("(%d):%s, ", j++, p -> name);
        p = p -> next;
      }
      printf("\n");
    }
  }
}



void disAllocate(dt_hashtable **ptht, const int hsize)
{
  int i;
  dt_linkedlist *p, *q;
  for(i = 0; i < hsize; i++)
  {
    if(ptht[i] != NULL)
    {
      for(p = ptht[i] -> head; p != NULL;)
      {
        q = p;
        p = p -> next;
        free(q -> name);
        free(q -> phone);
        free(q);
      }
      free(ptht[i]);
    }
  }
  free(ptht);
}



int collisionScan(dt_hashtable **ptht, const int hsize)
{
  int i, ret = 0;
  for(i = 0; i < hsize; i++)
  {
    if(ptht[i] != NULL)
    {
      ret = ret > ptht[i] -> counter ? ret : ptht[i] -> counter;
    }
  }
  return ret;
}


float queryHashing(const char *qryfile, dt_hashtable **ptht, const int hbase, const int hsize)
{
  FILE *fd = fopen(qryfile, "r");
  assert(fd != NULL);

  int slen, i, j, chktime = 0, qrytime = 0, found = 0;
  lld hval;
  char namebuf[1024];
  dt_linkedlist *pseek;

  while(fscanf(fd, "%s", namebuf) != EOF)
  {
    qrytime++;
    slen = (int) strlen(namebuf);
    hval = 0;
    for(i = 0; i < slen; i++)
    {
      hval = (hval * hbase + namebuf[i]) % hsize;
    }
    if(ptht[hval] != NULL)
    {
      pseek = ptht[hval] -> head;
      while(pseek != NULL)
      {
        chktime++;
        if(strcmp(pseek -> name, namebuf) == 0)
        {
          found++;
          break; // 找到聯絡人電話
        }
        else
        {
          pseek = pseek -> next; // 繼續往下找
        }
      }
    }
    else
    {
      ; // bucket 不存在
    }
  }
  fclose(fd);
  assert(found == qrytime);
  return (float) chktime / qrytime;
}


dt_hashtable **keyHashing(const char *recfile, const int hbase, const int hsize, int *num)
{
  FILE *fd = fopen(recfile, "r");
  assert(fd != NULL);
  dt_linkedlist *newleaf;
  dt_hashtable **ptht = (dt_hashtable **) malloc(sizeof(dt_hashtable *) * hsize);
  assert(ptht != NULL);

  *num = 0;
  int slen, i;
  lld hval;
  char namebuf[1024], phonebuf[1024];
  while(fscanf(fd, "%s%s", namebuf, phonebuf) != EOF)
  {
    (*num)++;
    slen = (int) strlen(namebuf);
    hval = 0;
    for(i = 0; i < slen; i++)
    {
      hval = (hval * hbase + namebuf[i]) % hsize;
    }
    newleaf = (dt_linkedlist *) malloc(sizeof(dt_linkedlist));
    assert(newleaf != NULL);

    newleaf -> name = strdup(namebuf);
    newleaf -> phone = strdup(phonebuf);
    newleaf -> next = NULL;

    if(ptht[hval] == NULL) // 如果 bucket 為空
    {
      ptht[hval] = (dt_hashtable *) malloc(sizeof(dt_hashtable));
      assert(ptht[hval] != NULL);
      ptht[hval] -> counter = 1;
      ptht[hval] -> head = ptht[hval] -> tail = newleaf;
    }

    else // 如果 bucket 不為空
    {
      ptht[hval] -> counter++;
      ptht[hval] -> tail -> next = newleaf;
      ptht[hval] -> tail = ptht[hval] -> tail -> next;
    }
  }
  fclose(fd);
  return ptht;
}


int main(int argc, char **argv)
{
  int num; // 聯絡人總數
  const char *recfile = argv[1], *qryfile = argv[2];
  const int hbase = atoi(argv[3]), hsize = atoi(argv[4]);
  dt_hashtable **ptht = keyHashing(recfile, hbase, hsize, &num); // 建立 hash table
//  showHashtable(ptht, hsize);
  float loadfactor = (float) num / hsize;
  float avgqry = queryHashing(qryfile, ptht, hbase, hsize); // 單一筆資訊查詢次數
  int wstcolli = collisionScan(ptht, hsize); // 偵測最大碰撞率
  disAllocate(ptht, hsize); // 釋放記憶體
  printf("(1) Hash Load Factor : %f\t(%d / %d)\n", loadfactor, num, hsize);
  printf("(2) Hash Max Collision: %d\n", wstcolli);
  printf("(3) Average Query times: %f\n", avgqry);
  return 0;
}
