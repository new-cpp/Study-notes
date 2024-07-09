#include <stdio.h>
#include <string.h>
struct Person
{
  char title[8];
  char name [32];
  int age;
};

int main()
  {
   struct Person p;
    strncpy(p.title, "name___", 7);
    strncpy(p.name, "whatever", 31);
    p.age = 33;

    printf("[%s] [%s] [%d]",
           p.title,
           p.name,
           p.age);

    return 0;
  }
