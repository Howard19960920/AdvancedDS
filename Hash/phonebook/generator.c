/*
 *
 * #PHONEBOOK DATA GENERATOR#
 * The program will create n records, with a 5~15 bits long name and a 10 digits long number for each,
 *
 * About two text file generated,
 *
 *  (1) records.txt: With n records inside, each contains a name and a number,
 *  (2) queries.txt: With around n/2 names inside, used for queries test.
 *
 * */





#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>



/**************Global***************/

int n, i, j, len;
char namebuf[16], phonebuf[16];
struct timeval sp, ep;

/**********************************/


void pre()  {

  printf("number of records to create: ");
  scanf("%d", &n);
  assert(n >= 0);
  srand((unsigned int) time(NULL));

}

void starttiming()  {

  gettimeofday(&sp, NULL);

}

void endtiming()  {

  gettimeofday(&ep, NULL);

}

float showtiming()  {

  return (ep.tv_sec-sp.tv_sec +(float)(ep.tv_usec-sp.tv_usec)/1000000);

}

void gen()  {

  FILE *fprec = fopen("records.txt", "w"), *fpqry = fopen("queries.txt", "w");
  assert(fprec != NULL && fpqry != NULL);

  for(i = 0; i < n; i++)  {

    len = (rand() % 11) + 5;

    for(j = 0; j < len; j++)
      namebuf[j] = (rand() % 26) + 97;
    namebuf[j] = '\0';

    for(j = 0; j < 10; j++)
      phonebuf[j] = (rand() % 10) + 48;
    phonebuf[j] = '\0';

    fprintf(fprec, "%s\t%s\n", namebuf, phonebuf);

    if(rand() & 1) // randomly choose
      fprintf(fpqry, "%s\n", namebuf);
  }
  fclose(fprec);
  fclose(fpqry);

}

int main() {


  pre();
  starttiming();
  gen();
  endtiming();
  printf("WCT to generate %d records: %f sec\n", n, showtiming());
  return 0;

}
