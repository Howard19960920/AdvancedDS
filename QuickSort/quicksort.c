/*
 *  Pseudo Code
 *
 * void quickSort(A, start, end)
 * {
 *    if(start < end)
 *    {
 *      pivot <- A[end];
 *      for(pidx = i = start; pidx < end and i < end; i++)
 *      {
 *        if(A[i] <= pivot)
 *        {
 *          SWAP(A[i], A[pidx]);
 *          pidx++;
 *        }
 *      }
 *      SWAP(A[pidx], A[end]);
 *      quickSort(A, start, pidx - 1);
 *      quickSort(A, pidx + 1, end);
 *    }
 * }
 * */




#include <stdio.h>
#include <stdlib.h>


#define SWAP(x, y) {int temp = x; x = y; y = temp;}
int arr[10000009]; // 測試資料


void quickSort(int *arr, int lbnd, int rbnd)
{
  if(lbnd >= rbnd)
    return;

  int pivot, pidx, i;
  /* Partitioning */
  pivot = arr[rbnd]; // choose right most element as pivot
  for(pidx = lbnd, i = lbnd; pidx < rbnd && i < rbnd; i++)
  {
    if(arr[i] <= pivot)
    {
      SWAP(arr[pidx], arr[i]);
      pidx++;
    }
  }
  SWAP(arr[pidx], arr[rbnd]);
  /* Recursion*/
  quickSort(arr, lbnd, pidx - 1);
  quickSort(arr, pidx + 1, rbnd);
}


int main(int argc, char **argv)
{
  int idx = 0, temp, i;

  // 讀測資
  while(scanf("%d", &temp) != EOF)
    arr[idx++] = temp;

  quickSort(arr, 0, idx - 1);

  /* print sorted arr */
  for(i = 0; i < idx; i++)
    printf("%d, ", arr[i]);
  printf("\n");

  return 0;
}
