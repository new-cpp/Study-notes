/*compound literals : is an unnamed object which is created in the scope where is
                    defined,
                    sotrage duration :
                      - static : if it's appear in file scope.
                      -automatic: if it's appear in block scopre.
*/

#include <stdio.h>
#include <stdlib.h>

struct point
  {
     unsigned x , y;
  };


void print_point(struct point p)
  {
    printf("point:[%u ,%u]\n",p.x,p.y);
  }


int main(int argc, char* argv[])
  {

    (void)argc;
    (void)argv;

    {
      int *p = (int[2]){2,4};

      for(int idx = 0 ; idx < 2; ++idx)
        printf("%d ",p[idx]);
      puts("");
    }

    /* initialize lenght less than array size */
    {
      int *p = (int[10]){2,4};

      for(int idx = 0 ; idx < 10; ++idx)
        printf("%d ",p[idx]);
      puts("");
    }
    /* array size it's not specifiyed */
    {
      int *p = (int[]){2,4};

      for(int idx = 0 ; idx < 2; ++idx)
        printf("%d ",p[idx]);
      puts("");
    }

    /*compound literal with designators*/
    print_point((struct point){.x=4,.y=6});


       return EXIT_SUCCESS;
  }
