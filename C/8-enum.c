
#include <stdio.h>
#include <assert.h>
/*An enumeration is a user-defined data type consists of integral constants and each integral constant is given a name.*/

enum color{Red,Green,Blue};

void printColor(enum color t_color)
  {
    const char* choice = "invalide color";

    switch(t_color)
      {
      case Red:
        choice = "Red";
        break;
      case Green:
        choice = "Blue";
        break;
      case Blue:
        choice = "Green";
        break;
      }

    puts(choice);
  }


/*enum with duplicated value*/
enum duplicated
{
  first = 0,
  second,
  third = 0,
  fourth
};

/* ananomus enum */
enum { bufferSize = 255};
static  unsigned char arr[bufferSize]={0};


  /*enum with range checkrs*/
      enum week{
        Invalid_min_day = -1,
        Mon,Thu,Wen,Thr,Fri,Sat,Sun,
        Invalid_max_day
      };

     static const char* const days_of_weeks[] = {
      [Mon]="Mon", [Thu] = "Thu", [Wen]="Wen",
      [Thr] = "Thr",[Fri]="Fri",[Sat]="Sat",[Sun]="Sun"
     } ;

void printDayOfTheWeek(enum week day)
  {
    assert(day>Invalid_min_day && day <Invalid_max_day);
    puts(days_of_weeks[day]);
  }


/*
 * typedef enum {...} color -> we can't use enum color ... we allowed just color C;
 *
 * on other hand:
 * enum color {};
 * typedef enum color color;
 *
 * we can use both
 *
 */

int main()
  {
    arr[0]=1;

    {
      enum color input;
      puts("enter int between 0 and 2");
      scanf("%d",(int*)&input);
      printColor(input);
    }

    return 0;
  }
