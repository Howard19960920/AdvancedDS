#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// 讀入測資
void init(int **arr, int *cnt)
{
  int size = 1 << 10;
  (*cnt) = 0;
  (*arr) = (int *) malloc(sizeof(int) * size);
  assert((*arr) != NULL);

  while(scanf("%d", &((*arr)[*cnt])) != EOF)
  {
    (*cnt) ++;
    if((*cnt) == size)
    {
      size <<= 1;
      (*arr) = (int *) realloc((*arr), sizeof(int) * size);
      assert((*arr) != NULL);
    }
  }
}

int cmp(const void *a, const void *b)
{
  return (*((int *) a)) - (*((int *) b));
}



int main()
{
  int *arr, cnt, i;
  init(&arr, &cnt);
  qsort(arr, cnt, sizeof(int), cmp);

  for(i = 0; i < cnt; i++)
    printf("%d ", arr[i]);
  printf("\n");

  return 0;
}
