#include <stdio.h>
#include <stdlib.h>

int H, arr[500009], i; // 題目說最多50萬個

void heapify(int *arr, int i)
{
  int l = i<<1, r = i<<1|1, maxi, temp;
  if(l <= H && arr[l] > arr[i])
    maxi = l;
  else
    maxi = i;
  if(r <= H && arr[r] > arr[maxi])
    maxi = r;
  if(maxi != i)
  {
    temp = arr[maxi];
    arr[maxi] = arr[i];
    arr[i] = temp;
    heapify(arr, maxi);
  }
}


int main()
{
  scanf("%d", &H);
  for(i = 1; i <= H; i++)
    scanf("%d", &arr[i]);

  for(i = H / 2; i >= 1; i--)
    heapify(arr, i);

  for(i = 1; i <= H; i++)
    printf("%d ", arr[i]);
  printf("\n");

  return 0;
}
