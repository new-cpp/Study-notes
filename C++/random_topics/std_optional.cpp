#include <optional>
#include <iostream>
#include <string>
#include <fstream>
/**
 * *
 * (since C++17)
 * Defined in header <optional>
   template< class T >
        class optional;

  The class template std::optional manages an optional contained value, i.e. a value that may or may not be present.

 */


/*optional as return value of function*/
std::optional<double> is_modern()
  {
    #if __cplusplus == 202002L

      return 20;
    #endif
      return {};
  }

std::optional<std::string> output_source_code(const std::string& path)
  {
    std::ifstream file_stream(path);

    if(file_stream.is_open())
      {
        std::string res{};
        std::string tmp{};
        while(std::getline(file_stream,tmp))
          {
            if(!res.empty())
              res+='\n';
            res+=tmp;
          }
        return res;
      }
    return std::nullopt;
  }


int main(void)
  {

    using namespace std::string_literals;


    auto version = is_modern();

    if(version.has_value())
    {
      std::cout<<"cpp version is 20:"<<version.value()<<'\n';
    }
   else
    {
      std::puts("no value\n"s.data());
    }


   if(output_source_code(__FILE__).has_value())
    {
      puts(output_source_code(__FILE__).value().data());
    }
   else
    {
      std::puts("empty or don't exist"s.data());
    }

   //or better
   puts(((output_source_code(__FILE__)).value_or("empty or don't exit"s)).data());

    return 0;
  }
