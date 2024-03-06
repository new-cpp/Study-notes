
/*original stl : iteratos , algorithms , containers*/

/**
 * *
 * containers : represent a sequence of element
 *              have an internal structre and ordering
 *
 *
 * sequence containers:
 * vector , deque , list, array, forward_list
 *
 * associative containers:
 * map, set, multimap, mutliset

 * unordered associative containers( using hashtable )
 * unordered_map,unordered_set,unordedred_multimap,unordered_multiset
 *
 *
 * container adaptors( wrappers around classic container to provide some
 * runtime prorities ) :
 * queue,stack,priority_queue
 *
 *
 */

/**
 * *
 * iterators : link between of containers and algorithms
              ever own the elements to which they refer
              5 type of iterators: output,input,forward ,bidirectional , random-access
 */

/**
 * * algoritms process ranges of element of a collection
 */
/**
 * *
 iterator range : pair of iterators [first, last)

 reverse iterator : template<class Iter> reverse_iterator
 insert iterator : template<class Containter> back_insert_iterator;
                   template<class Container> front_insert_iterator;
                   template<class Container> insert_iterator;

 */

/**
 * *
 common container alais:
 template< ... >
 class container
 {
 using value_type = ..
 using reference
 using const_reference

 using iterator
 using const_iterator
 using size_type
 using differnce_type
 }
 usage : container::alais
 */

/**
 * *
 * common container set of functions
 * template<>
 * class container
 * {
 * iterator begin()
 * iterator end();
 *
 * const_iterator begin() const;
 * const_iterator end() const;
 *
 * const_iterator cbegin() const;
 * const_iterator cend() const;
 }

 }

 */
#include <chrono>

/* have push_back method */
#include <vector>
#include <list>
#include <array>
#include <deque>

/* have insert method */
#include <set>
#include <stack>
#include <queue> // peroity_queue

#incluude <map>

/*from javidx9 container tuto */
template<typename T>
void container_internal_memory_allocation(const T& container)
  {
    std::chrono::duration<double> insertTime{0};
    char c;
    do{
    const int* pAdressOfItemZero = &(*container.begin());

    std::cout<<"Contains "<< container.size()<<"elements tock "<<
    std::chrono::duration_cast<std::chrono::microseconds>(insertTime).count()<<"us\n";

    for(const auto& i : container)
      {
        const int* pAddressOfItem = &i;
        int pItemoffset = pAddressfItem - pAdressOfItemZero;
        int pItemOffsetOriginal = pAddressOfItem - pAddressOfOriginalItemZero;

        std::cout<<"Offset from orginal "<< pItemOffsetOriginal<<
          "offset from zero: "<< pItemOffset<<" \n";
      }

    auto tp1 = std::chrono::high_resolution_clock::now();
    contanier.push_back(rand()%6 + 1);
    auto tp2 = std::chrono::high_resolution_clock::now();
    insertTime = (tp2 - tp1);
  }while(  c = getc(stdin) && c != 'q');

int main()
  {
    return 0;
  }
