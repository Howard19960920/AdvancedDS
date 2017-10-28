#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>


typedef struct dt_pthread
{

  int *arr, *temp, l, r;

} dt_pthread;


void print(int *arr, int l, int r)
{

  int i;
  for(i = l; i <= r; i++)
    printf("%d ", arr[i]);
  printf("\n");

}


void merge(int *arr, int *temp, int l, int m, int r)
{

  int i, j, k;
  for(i = l, j = m + 1, k = l; i <= m && j <= r;)
  {
    if(arr[i] < arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }
  while(i <= m)
    temp[k++] = arr[i++];
  while(j <= r)
    temp[k++] = arr[j++];
  for(i = l; i <= r; i++)
    arr[i] = temp[i];

}



void mergeSort(int *arr, int *temp, int l, int r)
{

  if(l == r)
    return;

  int m = (l + r) / 2;
  mergeSort(arr, temp, l, m);
  mergeSort(arr, temp, m + 1, r);
  merge(arr, temp, l, m, r);

}


void pthread(void *pstruct)
{
  dt_pthread *p = ((dt_pthread*) pstruct);
  mergeSort(p->arr, p->temp, p->l, p->r);
}



void init(int **arr, int **temp, int *cnt)
{

  int size = 1 << 10;
  *cnt = 0;
  (*arr) = (int *) malloc(sizeof(int) * size);
  assert((*arr) != NULL);

  while(scanf("%d", &(*arr)[*cnt]) != EOF)
  {
    (*cnt) ++;
    if((*cnt) == size)
    {
      size <<= 1;
      (*arr) = (int *) realloc((*arr), sizeof(int) * size);
      assert((*arr) != NULL);
    }

  }

  (*temp) = (int *) malloc(sizeof(int) * size);
  assert((*temp) != NULL);

}


int main()
{

  int *arr, *temp, cnt, idx_i;
  init(&arr, &temp, &cnt);
  int l = 0, m = (cnt - 1) / 2, r = cnt - 1;
  pthread_t pid[2];
  dt_pthread pstruct[2] = {{arr, temp, l, m}, {arr, temp, m + 1, r}};

  for(idx_i = 0; idx_i < 2; idx_i++)
    pthread_create(&pid[idx_i], NULL, (void *) pthread , &pstruct[idx_i]);
  for(idx_i = 0; idx_i < 2; idx_i++)
    pthread_join(pid[idx_i], NULL);

  merge(arr, temp, l, m, r);
  //print(arr, l, r);
  return 0;

}
