#include <stdio.h>  // standard output/input
#include <stdint.h> // fix width interges
#include <limits.h> // limits range of intergers

int  fn(long l , short s)
{
  (void)l;
  (void)s;
  return 0;
}

int a;
int* fn_ptr(void) { return &a;}

int (*fp)(void) l = &fn_ptr; // function ptr
                             //
                             //
int main(void)
   {
     puts("Hello World\n");

     uint32_t u32 = 32;
     uint8_t  u8  = 255;
     int64_t  i64 = -65;

     char* array_of_string_c[20]; // array of char*
     char (*ptr_to_char_array)[10]; // ptr to array of char

     int arr[5][8];
     int* ptr = &a;
     int** ptr_to_ptr_to_int=&ptr;

     signed char c = 127; // 1 byte
     signed short int si = 32767; // at least 2 bytes
     signed int i = 32767;// at least 2 bytes
     signed long int li = 2147483647; // at least 4 bytes
     signed long long int lli = (1<<63) - 1; // at least 8 bytes

     unsigned int ui = 65535;
     unsigned short us = 2767;
     unsigned char uc= 255;

     int d = 42; // decimal
     int o = 052;// octal
     int x = 0xaf;// hex
     int X = 0XAF;// hex case insensitive

     //suffixs
     {
       long int i = 0x32;
       unsigned int ui = 655635u; // unsgined int
       long int li = 655635l;// long int
     }
     // sizes
     {
       CHAR_BIT;
       CHAR_MIN;
       INT_MAX;
       UINT_MAX;
     }

     // floating point constans
     {
       float f = 0.314f;
       double d = 0.314;
       long double ld = 0.314l;

       double x = 1., y = .1;

       // scientific representation
       double sd = 1.2e3; // == 1200.0
     }

     //sring literals read-only
     {
       char* str = "hello, world";
       // str[0] = 'F'; UB

       char a1[]= "abc";
       char a2[4]= "abc";
       char a3[3]= "abc"; // '\0'

       const char* s1 = "foobar";

       char* s = "hello, " "world" "!"; // concat at compile time
       char* fmt = "%"PRId16;

       //diffrent character set
       wchar_t* s2 = L"abc"; // type wchar_t[]
       char* s3 = u8 "abc" ;
       char16_t* s4 = u"abc"; // 16 bit wide string liral
       char32_t* s5 = U"abc";
     }
    return 0;
   }
