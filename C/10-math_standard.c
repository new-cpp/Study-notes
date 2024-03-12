#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
  {


    {
      /*float point remainder*/
      double a = 5.6;
      double b = 2.2;

      /*fmod, fmodf,fmodl*/
      printf("%lf\n",fmod(a,b));
    }

    {
      /*power*/
      float a = 8;
      float b = 9;

      /*pow , powf,powl*/
      printf("%lf\n",pow(a,b));
    }
    return EXIT_SUCCESS;
  }
