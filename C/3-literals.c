#include <stdio.h>
#include <stdint.h> // fixed lenght intergers
#include <uchar.h>// char32_t , char16_t
                  //

void printf_unicode_info(const char32_t utf_32_str[],size_t arr_size)
  {


    for(size_t idx = 0; idx < arr_size; ++idx)
      {
        printf("%#x ",utf_32_str[idx]);
      }
    puts("");

  }

int main(int argc, char* argv[])
  {
    (void)argv;
    (void)argc;
    /*floating point literals*/
    {
      double d = -3.69e6;// no suffix
      float  f = -3.35e6F;
      //long double ld = -3e6L;

      puts("floating point literals");
      printf("%f  %lf\n",f,d);
      puts("/*----*/");
    }
    /*interger literas*/
    {
      //base prefix
      int decimal = 5;
      int octal   = 0345;
      int hexa    = 0x12ab;
      puts("interger literals");
      printf("%d , %o=%d, %x=%d\n",decimal,octal,octal,hexa,hexa);

      //type suffix
      unsigned u = 45u;
      long int l = 455l;
      //long long int ll = 478ll;
      puts("interger literal suffix type");
      printf("%u %ld \n",u,l);
    }
    /*string literals prefix since C11*/
    {
      char* c = "ad";
      wchar_t* widechar = L"kls";
      //char* utf_8_encoding_string = u8"utf8 string"// or u8 prefix
     // char16_t* utf16_encoding_string =u"utf16 string";
     const  char32_t utf32_encoding_string[] = {0x00df,0x6c34,0x0001f34c} ;// U prefix or "z\u00df\u6c34\U0001f34c"

      printf("%s %ls \n",c,widechar);

      printf_unicode_info(utf32_encoding_string,3);

    }

    /*compound literals*/
    return 0;
  }
