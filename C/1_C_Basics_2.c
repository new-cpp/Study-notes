#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdalign.h>
#include <stddef.h>
/*
 * Operators int C: bineary , unary, relation (beoolean) , bitwise(should be avoided for signed int)
*/

/*
 * masking : refers to the process of extracting the desired bit from a variable through
 * bitwise operation. ( the constant that used to perfom masking called mask )
*/

/*
 * comma operator : evaluted left to right
*/

/*
 * short circuit behavoir of logical operators:
 * skips evaluating part of conditions when able
 *
*/

/*
 * bool : 1-typedef enum
 *        2- stdbool.h header
 *        3- intrinsic built int type _Bool
*/
_Bool x = 1;

#if __STDC_VERSION__ < 199900L
typedef enum { false, true} bool;
#endif


void bit_pattern(int u)
  {
    int i , x , word;
    unsigned mask = 1;
    word = CHAR_BIT * sizeof(int);
    mask = mask << (word - 1);
    for(i = 1; i <= word; ++i)
      {
        x = (u & mask)?1:0;
        printf("%d",x);
        mask >>=1;
      }
    puts("\n");
  }

void printf_address_of(void* ptr)
  {
    printf("address of ptr:%p", ptr);
  }


int main(int argc, char* argv[])
{
  /*double diffrent formatter */
  double PI = acos(-1);
  printf("%f\n",PI);
  printf("%lf\n",PI);
  printf("%g\n", PI);
  printf("%e\n",PI);

  /*bitwise*/
  bit_pattern(5);

  /*address of operator &*/
  int x = 3;
  int *p = &x;
  printf_address_of((void*)&x);
  printf_address_of((void*)p);

/*sizeof operator*/
  size_t xx = 3;
  printf("nbr of bytes %zu, ,nbr of bits of int %zu\n",sizeof(int),CHAR_BIT*sizeof(xx));

  /* function call operator (implicit with function designator) */
  void (*func)(int) = &bit_pattern;
 (*func)(x);
  func(x);

  /* pointer subtraction */
  int y=5;
  int* px=&x;
  int* py=&y;

  ptrdiff_t diff = px - py;
  printf("\t %ti \r\n",diff);


  /* alignof operator */
  printf("alignement of int %zu\n", alignof(int));
  printf("alignement of max_align_t %zu\n",alignof(max_align_t));
  printf("alignement of struct %zu \n", alignof(struct{char c ; int i;}));
  return 0;
}
