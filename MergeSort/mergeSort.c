#include <stdio.h>
#include <stdlib.h>


int arr[10000009], temp[10000009];


void merge(int *arr, int l, int m, int r)
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


void mergeSort(int *arr, int l, int r)
{
  if(l == r)
    return;

  int m = (l + r) / 2;
  mergeSort(arr, l, m);
  mergeSort(arr, m + 1, r);
  merge(arr, l, m, r);
}


int main()
{
  int idx = 0, i;
  while(scanf("%d", &arr[idx++]) != EOF)
    ; idx--;
  mergeSort(&arr[0], 0, idx - 1);
/*
  for(i = 0; i < idx; i++)
    printf("%d ", arr[i]);
  printf("\n");
  */
  return 0;
}
