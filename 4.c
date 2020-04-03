#include <stdio.h>
#include <stdlib.h>
/*
* Program to count minimum number of billboards needed to be placed by the road of certain length
* with consideration of distance given which determines maximum possible distance between each billboard
* and also maximum distance allowed between start & firstBillboard and end & lastBillboard
*/

// loads length of the road and possible locations that are suited for placing billboards
void loadAndCheck(int * length, int * suitableLocation, int * sizeOfArray);
// sort suitable locations in ascending order
void sortsuitableLocations(int * suitableLocation,int size);
// count number of billboards with restrictions of distance
int numberOfBillboards(int * suitableLocation, int size, int distance, int length);
  // checks if calculation is possible.
  int checkMinDistance(int * suitableLocation, int size, int distance, int length);
  int firstBillboard(int * suitableLocation, int size, int distance, int * i);
  int lastBillboard(int * suitableLocation, int size, int distance, int length, int * i);

int main() {
  int length=0;
  int suitableLocation[1000000]={0};
  int sizeOfArray=0;
  int distance=0;
  int billboards=0;

  printf("Mozna umisteni:\n");
  loadAndCheck(&length,suitableLocation,&sizeOfArray);
  sortsuitableLocations(suitableLocation,sizeOfArray);


  printf("Vzdalenosti:\n");
  while( scanf("%d", &distance) != EOF ) {
    if( distance <= 0 ) {
      printf("Nespravny vstup.\n");
      return 0;
    }
    billboards=numberOfBillboards(suitableLocation,sizeOfArray,distance,length);
    if( billboards == -1 ) {
      printf("N/A\n");
    }
    else {
      printf("Billboardu: %d\n",billboards );
    }
  }


  return 0;
}

void loadAndCheck(int * length, int * suitableLocation, int * sizeOfArray) {
  char symbolCheck;
  char endSymbol;
  int i=0;


  if( scanf("%d : %c",length, &symbolCheck) != 2 || *length <= 0 ||symbolCheck != '{'  ) {
    printf("Nespravny vstup.\n");
    exit(0);
  }

  while(1) {
    if( scanf("%d %c", &suitableLocation[i], &endSymbol) != 2 || (endSymbol != ',' && endSymbol != '}') || suitableLocation[i] <= 0 || suitableLocation[i] >= *length ) {
      printf("Nespravny vstup.\n");
      exit(0);
    }
    i++;

    if( i > 999999 ) {
      printf("Nespravny vstup.\n");
      exit(0);
    }

    if( endSymbol == '}' )
    break;
  }
  *sizeOfArray=i;

}

void sortsuitableLocations(int * suitableLocation,int size) {
  int temp=0;

  for(int i=0; i<size; i++) {
    for(int j=0; j<(size-i-1); j++) {
      if(suitableLocation[j] > suitableLocation[j+1]) {
        temp = suitableLocation[j];
        suitableLocation[j] = suitableLocation[j+1];
        suitableLocation[j+1] = temp;
      }
    }
  }

}

int numberOfBillboards(int * suitableLocation, int size, int distance, int length) {
  int billboards=0;
  int i=0;

  if ( checkMinDistance(suitableLocation,size,distance,length) == -1 )
  return -1;
  if( distance >= length )
  return 0;
  if( distance >= suitableLocation[size-1] )
  return 1;


  billboards += firstBillboard(suitableLocation,size,distance,&i);

  for(int j=i; j<size; j++) {
    for(int k=i+1; k<size; k++) {
      if( (suitableLocation[j]+distance) > suitableLocation[size-1] )
      break;
      if( suitableLocation[j]+distance == suitableLocation[k] ) {
        billboards++;
        j=k-1;
        i=k;
        break;
      }
      if( suitableLocation[j]+distance < suitableLocation[k] ) {
        billboards++;
        j=k-2;
        i=k-1;
        break;
      }
    }
  }

  billboards += lastBillboard(suitableLocation,size,distance,length,&i);

  return billboards;
}

int checkMinDistance(int * suitableLocation, int size, int distance, int length) {

  if( distance < suitableLocation[0] )
    return -1;
  if( length-distance > suitableLocation[size-1] )
    return -1;

  for(int c=0; c<size-1; c++) {
    if( (suitableLocation[c] + distance) < suitableLocation[c+1] )
      return -1;
  }

  return 0;
}

int firstBillboard(int * suitableLocation, int size, int distance, int * i) {

  for(int j=0; j<size; j++) {
    if( distance == suitableLocation[j] ) {
      *i=j;
      return 1;
    }
    if( distance < suitableLocation[j] ) {
      j--;
      *i=j;
      return 1;
    }
  }

  return 0;
}

int lastBillboard(int * suitableLocation, int size, int distance, int length, int * i) {

  for(int l=size-1; l>=0; l--) {
    if( suitableLocation[l] < suitableLocation[*i] )
      break;
    if( length-distance == suitableLocation[l] && suitableLocation[l] != suitableLocation[*i] )
      return 1;
    if( length-distance > suitableLocation[l-1] && suitableLocation[l] != suitableLocation[*i] )
      return 1;
  }

  return 0;
}
