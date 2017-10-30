#include <bits/stdc++.h>
using namespace std;


int arr[10000009], n;


int main()
{
  n = 0;
  while(scanf("%d", &arr[n++]) != EOF)
    ;
  n--;
  sort(arr, arr + n);

  /*
  for(int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  */
  return 0;
}
