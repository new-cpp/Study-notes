

    /*c strings*/
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <math.h>

    #define MAX_CAPACITY 1024
    /*tokenisation*/
    /* using strtok :
    -modifies the src by replacing seprators with '\0'
    -the source can't be const ( string literals )
    -not thread safe nor re-entrant it use static buffer while parsing
    */
    typedef struct tokenised_string
    {
    int toknum;
    char* arr[MAX_CAPACITY];

} tokenised_string;

tokenised_string tokenisation(char* src, const char* delimeters)
  {
    tokenised_string tmp;
    tmp.toknum = 0;
    tmp.arr[tmp.toknum] = strtok(src, delimeters);

    perror("strtok:");
    while(tmp.arr[tmp.toknum] != NULL)
      {
        printf("%d: [%s]\n",tmp.toknum,tmp.arr[tmp.toknum] );
        ++(tmp.toknum);
        (tmp.arr[tmp.toknum]) = strtok(NULL, delimeters);
      }
    puts("after strtok src become:");
    puts(src);
    return tmp;/* copy evil */
  }


int main(int argc , char* argv[])
  {

    //tokenisation ex
    char str[]="hello,,world";
    const char* sep = ",!";
    tokenised_string result = tokenisation(str, sep);
    (void)result;
    (void)argc;
    (void)argv;


 {
/*string literals*/
/*
 * has a static storage duration
 * "string" -> better be const char *
*/

 char *foo = "hello";
 fprintf(stderr,"%s\n",foo);
 //foo[0] = 'y'; /* UB*/

 char arr[] = "hello"; // array initialize
      arr[0] = 't'; // good
      *arr = 'l';
  }

 {
   /* strlen : nbr of bytes of null terminated string */
   char str[50] = "hello world!";
   printf("capacity [%d], length [%d]", sizeof(str),strlen(str));
 }

 {
   /* copy a string */
   char a[]="abs";
   char b[8];

   strcpy(b,a);
   printf("%s\n",b);

   snprintf(b,sizeof(b),"%s",a);/*safer but slower no overflow */

   char dst[32];
   char src[]="source";

   strncat(dst,src,sizeof(dst)-1); /* better perf */

   strncpy(dst,a ,sizeof(dst));/* padd with '\n' cause bad pref for big buffers*/
   dst[sizeof(b)/sizeof(*b) - 1] ='\0'; /* must manually added */
 }

 {
   /*concatnation*/
   char dst[32]="hello";
   char src[]="world";

   size_t len = strlen(dst);
   strncat(dst,src,sizeof(dst)-len-1);/*scan dst till end then add src , and add '\0' at the end*/
   strncat(dst+len,src,sizeof(dst) - len - 1); /*better pref*/
 }

 {
   char str[]="hlkjsd";
   /*iterating string*/
   size_t i = 0;
   while( str[i]!='\0' )
     {
       printf("%c\n",str[i]);
       ++i;
     }
 }

 {
   /*array of string*/
   char* read_only_string[]={ "foo","bar","baz"};
   char modifiable_string_array[][4]= { "foo","bar","baz"};

   (void) read_only_string;
   (void)modifiable_string_array;
 }


 {
   /*convert string to numbers:
     atoi, atol, atoll, atof  unsafe
   use strtol, strtoll,strtod
     */
   const char* number="879";
   long int long_integer = strtol(number,NULL,10);
   ++long_integer;
 }

 {

   /*string formatted data read write*/
   /*
    * sprintf, sscanf
    */

   char buffer[32];
   double pi=acos(-1);
   sprintf(buffer,"pi value %lf",pi);
   printf("%s\n", buffer);

   char date[]= " date : 02-08-0983";
   char str[50];
   int year,month,day;

   sscanf(date," %s : %02d-%02d-%04d",str,&day,&month,&year);
   printf("%s %d %d %d\n",str,day,month,year);
 }

 {
   /*compare strings : strcmp, strncmp*/
   /*int strcmp( const char *lhs, const char *rhs );
	*/

   char* first ="first";
   char* second ="second";

   int res =  strcmp(first,second);
   if(res == 0)puts("equal");
   else if (res == 1) puts("second lexicographically bigger");
   else puts("first lexicographically bigger");

 }

 {
   /*strchr(str,char) return ptr to first occur of char*/
   /*strrchr(str,char return ptr to last occur of char)*/
   const char* full_path ="/home/usr/data/file.txt";
   char* file_or_dir_name = NULL;
   if((file_or_dir_name==strrchr(full_path,'/')))
     {
       ++file_or_dir_name;
     }
 }


 {
   /*size_t strspn( const char *dest, const char *src );*/
   /*Returns the length of the maximum initial segment consist only of the char in src string*/

   /*size_t strcspn( const char *dest, const char *src );*/
   /*Returns the length of the maximum initial segment  not found in the src string*/

   const char * str_to_analyse= "abc123hi";
   const char * to_exclude = "123";
   const char* to_include = "abchi";
   size_t len_unvalid_prefix = strcspn(str_to_analyse,to_exclude);
   if(len_unvalid_prefix != strlen(str_to_analyse))
     {
       printf("%s valid suffix\n",str_to_analyse + len_unvalid_prefix);
     }

   size_t len_valid_prefix = strspn(str_to_analyse, to_include);
       printf("%d valid prefix pos\n", len_valid_prefix);

 }

 {
   /* char *strstr( const char *str, const char *substr ); search for substring */

   const char* str ="haystack_needle_haystack";
   const char* substr ="needle";

   char* found_str = strstr(str,substr);

   printf("position of the needle: [%d]\n", str - found_str);
 }

 {
   /*memory set value: void *memset( void *dest, int ch, size_t count );*/
    char str[] = "ghghghghghghghghghghgh";
    puts(str);
    memset(str,'a',5);
    puts(str);

 }



    return EXIT_SUCCESS;
  }
