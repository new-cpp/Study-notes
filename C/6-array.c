


/* array[] will decay to int* instead of int[], that why we must pass len as parameter */
size_t get_last(int array[],size_t len)
  {
    /*
     * size_t size = sizeof(array)/sizeof(array[0]); bad
     * cus array now is an int* ... don't have the lenght of array info
     */
    return array[len - 1];
  }
int main()
  {

    int array[] ={1,2,3,4,5,6,7,8,9};

    size_t size__bytes = sizeof(array);
    size_t lenght = (sizeof(array)/sizeof(array[0]));

    size_t len = get_length(array,lenght);

    int arr[10] = {0}; // 0 out the array

    // VAL : variable length array :
    size_t m = calc_len(); /* calcul size at runtime */
    int vla[m]; /* better not , may cause stack overflow in case of m is large  */
    return 0;
  }
