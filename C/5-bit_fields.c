#include <stdio.h>
#include <stdint.h>
/*bit fields : A simple bit-field can be used to describe things that may have a specific number of bits involved

  */
struct encoderPosition
{
  unsigned int encoderCounts: 23;
  unsigned int encoderTurns : 4;
  unsigned int _reserved    : 5;
};


struct FPGAInfo
{
  union
  {
    struct
    {
      unsigned int bulb10n : 1;
      unsigned int bulb20n : 1;
      unsigned int bulb10ff : 1;
      unsigned int bulb20ff : 1;
      unsigned int jetOn: 1;
    }bits;
    unsigned int data;
  };
};
/* we can access indiviual bits */


typedef union
{
  struct _bits
  {
    #if defined(WIN32) || defined(LITTLE_ENDIAN)
    uint8_t commFailure :1;
    uint8_t hardwareFailure :1;
    uint8_t _reserved : 6;
    #else
    uint8_t _resereved :6;
    uint8_t harwardFailre: 1;
    uint8_t commFailure :1;
    #endif
  };
  uint8_t data;
} hardwareStatus;

int main()
  {

    {
      /*bits fields example*/
      struct FPGAInfo info;
      info.data = 0xff34F;
      if(info.bits.bulb10n)
        {
          puts("bulb 1 is on");
        }
    }

    /*using bit fields as small int*/
    {
      struct
      {
        unsigned int uint3: 3;
      }small;

       unsigned int value = 255-2;/*11111101 */
       small.uint3 = value;/*extract the right 3 bit 101*/
       printf("%d\n", small.uint3);

    }

    {
    /* Bit-field alignment */
      struct C
      {
        short s;            /* 2 bytes */
        char  c;            /* 1 byte */
        int   bit1 : 1;     /* 1 bit */
        int   nib  : 4;     /* 4 bits padded up to boundary of 8 bits. Thus 3 bits are padded */
        int   sept : 7;     /* 7 Bits septet, padded up to boundary of 32 bits. */
      };

      struct A /*1 bytes size*/
      {
        unsigned char c1 : 3;
        unsigned char c2 : 4;
        unsigned char c3 : 1;
      };

      struct B
      {
        unsigned char c1 : 1;
        unsigned char    : 2;    /* Skips 2 bits in the layout */
        unsigned char c2 : 2;
        unsigned char    : 0;    /* Causes padding up to next container boundary */
        unsigned char c3 : 4;
        unsigned char c4 : 1;
      };
    }

    {
      /* zero out a bit field structre with union usage */
       typedef union
       {
         struct
           {
             unsigned int a:2;
             unsigned int b:1;
             unsigned int c:3;
             unsigned int d:1;
             unsigned int e:1;
           };
         uint8_t data;
       } union_bit;

       union_bit un_bit;
       un_bit.data = 0x00;
       un_bit.a = 2;
       printf("%d\n",un_bit.a);
    }

    return 0;
  }
