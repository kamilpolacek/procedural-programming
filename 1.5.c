#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <float.h>

double determinePerimeter2( double a, double b, double c ) {
  if( a >= (a + b) || b >= (b + c) || c >= (a + b) || fabs(a-(a+b)) < 0.00001 || fabs(b-(a+b)) < 0.00001 || fabs(c-(a+b)) < 0.00001 ) {
    printf("Neplatny trojuhelnik.\n");
    exit(0);
  }
  else
  return a+b+c;
}
double determineVolume2( double a, double b, double c ) {
  double s;

  s=(a+b+a)/2;
  return s * (s-a) * (s-b) * (s-c);
}

double determineVolume(double a1, double a2, double b1, double b2, double c1, double c2) {  
  double ab,bc,ac,s;
  ab=bc=ac=s=0;


  ab = sqrt( pow(a1-b1,2) + pow(a2-b2,2) );
  bc = sqrt( pow(b1-c1,2) + pow(b2-c2,2) );
  ac = sqrt( pow(a1-c1,2) + pow(a2-c2,2) );


  s=(ab+bc+ac)/2;

  return s * (s-ab) * (s-bc) * (s-ac);
}

double determinePerimeter(double a1, double a2, double b1, double b2, double c1, double c2) {
  double ab,bc,ac,s;
  ab=bc=ac=s=0;

  ab = sqrt( pow(a1-b1,2) + pow(a2-b2,2) );
  bc = sqrt( pow(b1-c1,2) + pow(b2-c2,2) );
  ac = sqrt( pow(a1-c1,2) + pow(a2-c2,2) );

  s=(ab+bc+ac)/2;
  if ( fabs(s) < 0.00000000001 && s !=0 ) {
    s *= 1000000000000000;
    s *= 1000000000000000;
    s *= 1000000000000000;
    s *= 1000000000000000;
    s *= 1000000000000000;
    s *= 1000000000000000;

  }

  if( (s * (s-ab) * (s-bc) * (s-ac)) <= 0.00001 ) {
    printf("Neplatny trojuhelnik.\n");
    exit(0);
  }

    return ab + bc + ac;
}




void loadAndCheck(double *a1, double *a2, double *b1, double *b2, double *c1, double *c2 ) {
 char brm;

  if ( scanf(" [ %lf ; %lf %c", a1, a2, &brm) != 3 || brm != ']') {
    printf("Nespravny vstup.\n");
    exit(0);
  }
  if ( scanf(" , [ %lf ; %lf %c", b1, b2, &brm) != 3 || brm != ']') {
    printf("Nespravny vstup.\n");
    exit(0);
  }

  if ( scanf(" , [ %lf ; %lf ] %c", c1, c2, &brm) != 3 || brm != '}') {
    printf("Nespravny vstup.\n");
    exit(0);
  }


}

void loadAndCheck2( double *b, double *c) {
//  {51.09,49.49,4.94}

char charcik;

  if ( scanf(" , %lf , %lf %c", b, c, &charcik) != 3 ) {
    printf("Nespravny vstup.\n");
    exit(0);
  }

  if ( charcik != '}' ) {
    printf("Nespravny vstup.\n");
    exit(0);
  }

}







int main ()
{
    double a1,a2,b1,b2,c1,c2;
    a1=a2=b1=b2=c1=c2=0;
    double f1,f2;
    f1=f2=0;


    double perimeterA,perimeterB,volumeA,volumeB;
    perimeterA=perimeterB=volumeA=volumeB=0;

    char firstChar;
    double number=0,number2=0;

    printf("Trojuhelnik #1:\n");



      if (scanf(" %c", &firstChar ) != 1 ) {
        printf("Nespravny vstup.\n");
        exit(0);
      }
    if( firstChar != '{' ) {
      printf("Nespravny vstup.\n");
      exit(0);
    }

    if( scanf( "%lf", &number) != 1 ) {


    loadAndCheck(&a1,&a2,&b1,&b2,&c1,&c2);
    perimeterA=determinePerimeter(a1,a2,b1,b2,c1,c2);
    volumeA=determineVolume(a1,a2,b1,b2,c1,c2);

    }
    else {


      loadAndCheck2(&a2,&b1);
      perimeterA=determinePerimeter2(number,a2,b1);
      volumeA=determineVolume2(number,a2,b1);
    }

    printf("Trojuhelnik #2:\n");
// maybe another character maaaaaaaaaaaaan
    if ( scanf(" %c", &firstChar ) != 1 ) {
      printf("Nespravny vstup.\n");
      exit(0);
    }
    if( firstChar != '{' ) {
      printf("Nespravny vstup.\n");
      exit(0);
    }

    if( scanf( "%lf", &number2) != 1 ) {

    loadAndCheck(&a1,&a2,&b1,&b2,&c1,&c2);
    perimeterB=determinePerimeter(a1,a2,b1,b2,c1,c2);
    volumeB=determineVolume(a1,a2,b1,b2,c1,c2);


    }
    else {

      loadAndCheck2(&f1,&f2 );
      perimeterB=determinePerimeter2(number2,f1,f2);
      volumeB=determineVolume2(number2,f1,f2);
    }


    if( fabs(perimeterA - perimeterB) < DBL_EPSILON*(fabs(perimeterA)+fabs(perimeterB)*1000) && fabs(volumeA - volumeB) < DBL_EPSILON*(fabs(perimeterA)+fabs(perimeterB)*1000) ) {
      printf("Trojuhelniky jsou shodne.\n");
      return 0;
    }

    if( fabs(perimeterA - perimeterB ) < DBL_EPSILON*(fabs(perimeterA)+fabs(perimeterB)*1000) ) {
      printf("Trojuhelniky nejsou shodne, ale maji stejny obvod.\n");
      return 0;
    }

    if( perimeterA < perimeterB ) {
      printf("Trojuhelnik #2 ma vetsi obvod.\n");
      return 0;
    }
    else
    printf("Trojuhelnik #1 ma vetsi obvod.\n");


    return 0;
  }
