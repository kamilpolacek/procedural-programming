#include <stdio.h>
#include <stdlib.h>



typedef struct feeSumType {
  char feeType;
  double feeTotalCost;
} FEESUMTYPE:

typedef struct Section {
  int from;
  int to;
  char feeType;
  double feeCost;
} SECTION;

int compare(const void *a, const void *b) {
  const SECTION * s1 = (const SECTION*)a;
  const SECTION * s2 = (const SECTION*)b;

  return s1->from - s2->from;

}
int findStartingPosition(SECTION *section, int size, int from) {
  for(int i=0; i<size; i++) {
    if( from == section->m_from  )
      return i;
    if( from )
  }
}

SECTION* loadAndCheck(int *size){
  char startBracket;
  char commaOrBracket;
  char bracket;
  int n=1;
  scanf(" %c", &startBracket);
  SECTION *section = (SECTION*)malloc(sizeof(SECTION)*n); // yea n doesnt have to be here i know
  while(1) {
    scanf(" %c",&bracket );
    scanf("%d - %d : %c = %lf", &section[n-1].from, &section[n-1].to, &section[n-1].feeType,&section[n-1].feeCost );
    scanf(" %c",&bracket );
    scanf(" %c",&commaOrBracket );

    if(commaOrBracket == '}')
      break;

    n++;
    section = (SECTION*)realloc(section,sizeof(SECTION)*n);
  }
  *size = n;
  return section;
}


int main() {
  SECTION *section = NULL;
  int size=0;
  int typesN=0;
  int from=0;
  int to=0;
  int start=0;
  printf("ZMENY:\n");
  section=loadAndCheck(&size);

  qsort(section, size-1, sizeof(SECTION), &compare);

  /*for(int i=0; i<size; i++) {
    printf("%d - %d %c = %f\n", section[i].from , section[i].to, section[i].feeType, section[i].feeCost);
  }
  */
  printf("HLEDANI:\n");
  while( scanf("%d%d",&from, &to ) != EOF ) {
    start=findStartingPosition(section,size,from);


    FEESUMTYPE * feeSum = (FEESUMTYPE*)malloc(sizeof(feeSum),)

  }




  free(section);
  free(feeSum)

  return 0;
}
