#include <stdio.h>
#include <stdlib.h> //malloc
#include <stddef.h> //offsetof

/*Structures provide a way to group a set of related variables of diverse types into a single unit of memory. */
struct point
{
  int x,y;
};

typedef struct point point;


/*always pass struct by pointer ... for performance*/
void print_point(point* p)
  {
    printf("%d %d\n", p->x,p->y);
  }


/* object based programming */

struct coordinate
{

  void(*set)(struct coordinate* this,int x,int y);
  void (*print)(struct coordinate* this);
  void (*info)(void);

  int x ,y;
};
//forward declration
struct coordinate* construct_coordinate(void);

void set_coordinate(struct coordinate* this,int x,int y)
  {
    this->x = x;
    this->y = y;
  }

void print_coordinate(struct coordinate* this)
  {
    printf("%d %d\n",this->x,this->y);
  }

void info_coordinate(void)
  {
    size_t struct_size = sizeof(struct coordinate);
    size_t x_offset   = offsetof(struct coordinate, x);
    size_t y_offset   = offsetof(struct coordinate, y);

    printf("%d %d %d\n",(int)struct_size,(int)x_offset,(int)y_offset);


    /*offsetof implentation : the address mmeber of casted 0 into struct */
    int  homemade_x_offset =    (int)(&(((struct coordinate*) (0))->x));
    int  homemade_y_offset =    (int)(&(((struct coordinate*) (0))->y));
    printf("%d %d\n" ,homemade_x_offset,homemade_y_offset);

  }

struct coordinate* construct_coordinate(void)
  {

    struct coordinate* c = (struct coordinate * )malloc(sizeof(struct coordinate));

    if(c)
      {
        c->x = 0;
        c->y = 0;
        c->set = &(set_coordinate);
        c->print = &(print_coordinate);
      }

    return c;
  }





int main()
  {

    point p = {1,2};
    print_point(&p);
    point p2 = {.x = 1, .y = 4};
    print_point(&p2);

    info_coordinate();
    return 0;
  }
