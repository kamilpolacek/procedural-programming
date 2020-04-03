#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
**
*/
long long int countAllDigits(long long int low, long long int high, int numeralSystem) {
  long long int allDigits=0;
  long long int divisor=0;
  long long int digitsInNumber=1;
  divisor=numeralSystem;

// counts highest divisor and number of digits in highest number
  while(1) {
    if( high < divisor ) {
      break;
    }
    if( (high / divisor) < numeralSystem ) {
      digitsInNumber++;
      break;
    }
    else{
    divisor *= numeralSystem;
    digitsInNumber++;
    }
  }
// count number of digits for every number of interval from highest to the lowest
  for(long long int i=high; i>=low; i--) {
    if( i < numeralSystem ) {
      allDigits++;
      continue;
    }
    if( i / divisor == 0 ) {
      divisor=divisor/numeralSystem;
      digitsInNumber--;
    }
    allDigits+=digitsInNumber;
  }


  return allDigits;
}

long long int countAllZeros(long long int low, long long int high, int numeralSystem) {
  long long int allZeros=0;
  long long int number=0;

    for(long long int i=high; i>=low; i--) {
      if( i == 0 ){
        allZeros++;
        break;
      }
      if( i < numeralSystem ) {
        continue;
      }
      number = i; //basically copy of i so I can change it and dont affect loop

        while(1) {
          if( number/numeralSystem == 0 ) {
            break;
          }
          if( number%numeralSystem == 0 ) {
            allZeros++;
            number=number/numeralSystem;
          }
          if( number%numeralSystem != 0 ) {
            number=number/numeralSystem;
          }
        }

    }

  return allZeros;
}
long long int countLongestSequenceOfZeros(long long int low, long long int high, int numeralSystem) {
  long long int longestSequence=0;
  long long int longestSequenceYet=0;
  long long int zerosInNumber=0;
  long long int number=0;

  for(long long int i=high; i>=low; i--) {
    zerosInNumber=0;
    if( i == 0 ){
      zerosInNumber++;
      if( longestSequenceYet < zerosInNumber ) {
        longestSequenceYet = zerosInNumber;
        longestSequence = zerosInNumber;
      }
      break;
    }
    if( i < numeralSystem ) {
      continue;
    }
    number = i; //basically copy of i so I can change it and dont affect loop
    
      while(1) {
        if( number/numeralSystem == 0 ) {
          break;
        }
        if( number%numeralSystem == 0 ) {
          zerosInNumber++;
          number=number/numeralSystem;

          if( longestSequenceYet < zerosInNumber ) {
            longestSequenceYet = zerosInNumber;
            longestSequence = zerosInNumber;
          }
        }
        if( number%numeralSystem != 0 ) {
          number=number/numeralSystem;
          zerosInNumber=0;
        }
      }
  }

  return longestSequence;
}



void loadAndCheckDecimal(long long int * low, long long int * high, char * operation) {

  if( scanf("%lli ; %lli > %c", low, high, operation) != 3 || (*operation != 'z' && *operation != 's' && *operation != 'l' )  || *low > *high || *low < 0) {
    printf("Nespravny vstup.\n");
    exit(0);
  }
}
//r2:<11;21> l
//<11;21> l
void loadAndCheckOthers(long long int * low, long long int * high, int * numeralSystem, char * operation) {

  if( scanf("%d : < %lli ; %lli > %c", numeralSystem, low, high, operation) != 4 || *numeralSystem < 2 || *numeralSystem > 36 || *low > *high || *low < 0) {
    printf("Nespravny vstup.\n");
    exit(0);
  }

  if( *operation != 'z' && *operation != 'l' && *operation != 's' ) {
    printf("Nespravny vstup\n");
    exit(0);
  }
}

void test() {


  assert(countAllDigits(0,100,10) == 193);
  assert(countAllDigits(11,21,2) == 50);
  assert(countAllDigits(10,20,4) == 27);
  assert(countAllDigits(70,112,3) == 204);
  assert(countAllDigits(6,100,10) == 187);
  assert(countAllDigits(44,144,36) == 202);
  assert(countAllDigits(10,10,10) == 2);
  assert(countAllDigits(61,61,19) == 2);
  assert(countAllDigits(0,0,10) == 1);


  assert(countAllZeros(0,100,10) == 12);
  assert(countAllZeros(11,21,2) == 22);
  assert(countAllZeros(10,20,4) == 7);
  assert(countAllZeros(70,112,3) == 70);
  assert(countAllZeros(6,100,10) == 11);
  assert(countAllZeros(10,10,10) == 1);
  assert(countAllZeros(61,61,19) == 0);
  assert(countAllZeros(0,0,10) == 1);
  assert(countAllZeros(44,144,36) == 3);


  assert(countLongestSequenceOfZeros(0,100,10) == 2);
  assert(countLongestSequenceOfZeros(11,21,2) == 4);
  assert(countLongestSequenceOfZeros(10,20,4) == 2);
  assert(countLongestSequenceOfZeros(70,112,3) == 4);
  assert(countLongestSequenceOfZeros(6,100,10) == 2);
  assert(countLongestSequenceOfZeros(44,144,36) == 1);
  assert(countLongestSequenceOfZeros(10,10,10) == 1);
  assert(countLongestSequenceOfZeros(61,61,19) == 0);



}

int main() {
  char defaultDecide;
  int numeralSystem=10;
  long long int low=0, high=0;
  char operation;

  test();

  printf("Zadejte intervaly:\n");
  while ( scanf(" %c", &defaultDecide) != EOF ) {

    if( defaultDecide == '<' ) {
      loadAndCheckDecimal(&low, &high, &operation);
      numeralSystem=10;
    }
    else if ( defaultDecide == 'r' ) {
      loadAndCheckOthers(&low, &high, &numeralSystem, &operation);
    }
    else {
      printf("Nespravny vstup.\n");
      exit(0);
    }


    if( operation == 'l' ) {
      printf("Cifer: %lli\n", countAllDigits(low,high,numeralSystem));
    }
    else if( operation == 'z' ) {
      printf("Nul: %lli\n", countAllZeros(low,high,numeralSystem));
    }

    else if( operation == 's' ) {
      printf("Sekvence: %lli\n", countLongestSequenceOfZeros(low,high,numeralSystem));
    }

  }



  return 0;
}
