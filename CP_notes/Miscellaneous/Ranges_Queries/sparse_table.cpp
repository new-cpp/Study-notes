#include <iostream>
#include <functional>

const int MAXN = 1e7;
const int K    = 25;
int n;
int arr[MAXN];
int rmq[K][MAXN];



int log2_floor(int n)
  {
    /* __builtin_clz(1) == 31 */
    return n? ( __builtin_clz(1) - __builtin_clz(n) ) : -1;
  }

void build_sparse_table()
   {
     std::copy(arr,arr+n,rmq[0]);

     for(int i = 0 ; i < K ;++i)
       {
         for(int j = 0 ; j < n ; ++i)
           {
              rmq[i][j] = std::min( rmq[i - 1][j], rmq[i-1][j + (1<<i-1)] );
           }
       }
   }

void query()
  {
    int L,R;
    std::cin>>L>>R;

    int len = R  - L +1;
    int i = (log2_floor(len));/*closest power of 2*/
    std::cout<< std::min( rmq[ i ][ L ]  , rmq[ i ][R-( 1<<i ) + 1]   );
  }
int main()
  {
    int q;
    std::cin>>n>>q;

    for(int i = 0 ; i < n ;++i)
      std::cin>>arr[i];

    build_sparse_table();

    while( q-- )
      {
        query();
      }

  }
