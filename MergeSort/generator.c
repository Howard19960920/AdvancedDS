#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


int main()
{
  int n, i;
  printf("number of records to gen: ");
  scanf("%d", &n);

  FILE *fd = fopen("td", "w");
  assert(fd != NULL);
  srand(time(NULL));
  for(i = 0; i < n; i++)
  {
    fprintf(fd, "%d ", rand());
  }
  fprintf(fd, "\n");
  fclose(fd);
  return 0;
}
