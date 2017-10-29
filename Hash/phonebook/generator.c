#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>


int main(int argc, char **argv)
{
  int num, i, j, k, slen;
  char namebuf[16], phonebuf[16];
  struct timeval sp, ep;

  printf("number of records to generate: \n");
  scanf("%d", &num);

  FILE *fdr = fopen("records", "w");
  FILE *fdq = fopen("queries", "w");
  assert(fdr != NULL && fdq != NULL);

  srand(time(NULL));
  gettimeofday(&sp, NULL);

  for(i = 0, k = 0; i < num; i++)
  {
    slen = (rand() % 11) + 5; // 姓名長度 5 ~ 15 個字母
    for(j = 0; j < slen; j++)
    {
      namebuf[j] = rand() % 26 + 97; // 姓名由小寫英文字母組成
    }
    namebuf[j] = '\0';

    for(j = 0; j < 10; j++)
    {
      phonebuf[j] = rand() % 10 + 48;
    }
    phonebuf[j] = '\0';

    fprintf(fdr, "%s\t%s\n", namebuf, phonebuf);

    // 隨機決定是否在之後查詢這筆聯絡人資訊
    if(rand() & 1)
    {
      fprintf(fdq, "%s\n", namebuf);
      k++;
    }
  }
  fclose(fdr);
  fclose(fdq);
  gettimeofday(&ep, NULL);
  printf("wct to create %d records and %d queries: %f secs\n", num, k, \
      ep.tv_sec - sp.tv_sec + (float) (ep.tv_usec - sp.tv_usec) / 1000000);

  return 0;
}
