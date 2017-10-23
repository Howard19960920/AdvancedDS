#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>


//extern char *strdup(const char *_s);



typedef struct dt_linkedlist  {

  char *name, *phone;
  struct dt_linkedlist *next;

} dt_linkedlist;


typedef struct dt_hashtable {

  int counter;
  struct dt_linkedlist *head, *tail;

} dt_hashtable;


typedef struct timeval timeval;


/***************Global****************/
int hbase, hsize, slen, i;
char namebuf[16], phonebuf[16];
long long hval;
timeval sp, ep;
dt_hashtable **ht;
dt_linkedlist *new;
/*************************************/


void starttiming()  {

  gettimeofday(&sp, NULL);

}

void endtiming() {

  gettimeofday(&ep, NULL);

}

float showtiming() {

  return ((ep.tv_sec-sp.tv_sec)+(float)(ep.tv_usec-sp.tv_usec)/1000000);

}



void getfactor() {

  printf("decide hash base: ");
  scanf("%d", &hbase);
  assert(hbase >= 0);

  printf("decide size of bucket: ");
  scanf("%d", &hsize);
  assert(hsize > 0);

}


void buildhash()  {


  FILE *fp = fopen("records.txt", "r");
  assert(fp != NULL);
  ht = (dt_hashtable **) malloc(sizeof(dt_hashtable *) * hsize);
  starttiming();
  while(fscanf(fp, "%s%s", namebuf, phonebuf) != EOF) {

    slen = strlen(namebuf);
    hval = 0;

    for(i = 0; i < slen; i++)
      hval = (hval * hbase + namebuf[i]) % hsize;
    assert(hval >= 0 && hval < hsize);

    new = (dt_linkedlist *) malloc(sizeof(dt_linkedlist));
    new -> name = strdup(namebuf);
    new -> phone = strdup(phonebuf);
    new -> next = NULL;

    if(ht[hval] == NULL) {

      ht[hval] = (dt_hashtable *) malloc(sizeof(dt_hashtable));
      ht[hval] -> counter = 1;
      ht[hval] -> head = ht[hval] -> tail = new;

    }

    else  {

      ht[hval] -> counter ++;
      ht[hval] -> tail -> next = new;
      ht[hval] -> tail = ht[hval] -> tail -> next;

    }
  }
  endtiming();
  fclose(fp);
  printf("WCT to build hash: %f sec\n", showtiming());

}




void freealloc()  {

  dt_linkedlist *p, *q;
  starttiming();
  for(i = 0; i < hsize; i++)  {

    if(ht[i] != NULL) {

      for(p = ht[i] -> head; p != NULL;)  {
        q = p;
        p = p -> next;
        free(q);
      }
      free(ht[i]);
    }

  }
  free(ht);
  endtiming();
  printf("WCT to free hash: %f sec\n", showtiming());

}


void hashquery()  {


  int nomi = 0, deno = 0, wstcolli = -1;
  dt_linkedlist *seek;
  FILE *fp = fopen("queries.txt", "r");
  assert(fp != NULL);
  starttiming();
  while(fscanf(fp, "%s", namebuf) != EOF) {

    deno ++;
    slen = strlen(namebuf);
    hval = 0;
    for(i = 0; i < slen; i++)
      hval = (hval * hbase + namebuf[i]) % hsize;
    assert(hval >= 0 && hval < hsize);

    if(ht[hval] != NULL)  {

      seek = ht[hval] -> head;
      while(seek != NULL) {

        if(strcmp(namebuf, seek -> name) == 0)
          ;
        else
          ;
        nomi ++;
        seek = seek -> next;

      }
      wstcolli = ht[hval] -> counter > wstcolli ? ht[hval] -> counter : wstcolli;

    }

    else
      exit(1);

  }
  endtiming();
  fclose(fp);
  printf("WCT to do %d query: %f sec,\tmax-colli: %d,\tcolli-rate: (%d/%d)\n", deno, showtiming(), wstcolli, nomi, deno);

}





int main()  {

  getfactor();
  buildhash();
  hashquery();
  freealloc();
  return 0;

}
