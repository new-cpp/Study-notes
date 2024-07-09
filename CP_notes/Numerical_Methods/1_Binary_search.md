#+title: 1 Binary Search


STL functions :
  binary_search.
  lower_bound.
  upper_bound.
  equal_range.




* Binary searching on arbitrary monotonic functions

*** Finding The Maximum x Such That f(x) = true
int last_true(int lo , int hi , std::function<bool(int)>f)
{
  --lo;

  while(lo < hi)
  {
    int mid = lo + (hi - lo + 1) ; // rounded up

    if(f(mid))
       lo = mid;
    else
       hi = mid - 1;
  }

  return lo;
 }

*** Finding The Minimum x Such That f(x) = true
int first_true(int lo, int hi, std::function<bool(int)> f)
{
  ++hi;
  while( lo < hi )
  {
    int mid = lo + (hi - lo)/2;

    if(f(mid))
    {
      hi = mid;
    }
    else
    {
        lo = mid +1;
    }
  }
  return lo;
}

* some approachs:

classi approach
#+NAME: classic apperoch
#+begin_src  cpp

int pos_bin_search(const std::vector<int>& arr, int value )
  {
    int l = 0 , r = arr.size()-1;

    while( l <=r )
      {
        int mid = std::midpoint(l,r);
        if(arr[mid] == value) return mid;
        else if ( arr[mid] < value ) r = mid - 1;
        else l = mid + 1;
      }
    return -1;
  }
#+end_src

lower bound version: find first
#+NAME: typical CP BS template
#+BEGIN_SRC cpp

#define MAX_VALUE 1e9
bool chk(int x)
  {
    // process on the element
  }

int find_first(const std::vector<int>& v, int value)
  {
    int l = 0, r = v.size() - 1;
    while( l <= r )
      {
        //int mid = l + (r - l)/2;
        //int mid = l + (r - l)>>1;
        int mid = std::midpoint(l,r);
        if(chk(mid))
          {
            l = mid + 1;
          }
        else
          {
            r = mid - 1;
          }
      }
    return l - 1;

  }
 #+END_SRC

 jumping search
 idea:
   jump with the biggest possible step close to target.
 #+name:
 #+#+begin_type options

 #+end_type_src cpp

bool condition(int element_position)
  {
    return v[element_postion] <= threshold;
  }

int bin_search(const std::vector<int>& v, int value)
{
  int p = 0;
  for (int step = n; step >= 1 ; step>>1)
    {
      if(p+step < n && condition(p + step))
        {
          p+= step;
        }
    }
  if(condition(p)) return p;
  return -1;
}
 #+end_src


** binery search on double
this implementation is somewhat error prone
#+begin_src cpp

double EPS = 1e-9;
double l = 0, r = 1e18;

while( r - l > EPS )
  {
    double mid = (l + r)/2.0;

    if(check(mid))
      l = mid;
    else
      r = mid;
  }
std::cout<<l;
#+end_src

use this one:
 #+begin_src cpp

 double l = 0, r = 1e18;
for(int it = 0 ;it <= 70;++it)
  {
    double mid = (l +r)/2.0;

    if(check(mid))
      l = mid;
    else
      r = mid;
  }
std::cout<<mid;
 #+end_src





 trick!!! :
 sometime the check function may be some sort of product of long long numbers .. which result in integer overflow .. solution
 determine the r value before bineary seach of which the first power of 2 is true:
 while(!check(r)) r*=2;

 base on expreince use this verision

 while(!good(r))r *=2;
 while( r > l+1)
 {
   int mid = l +(r - l)/2;
   if(good(mid))
    l = mid;
   else
    r = mid;
 }

 std::cout<<l;
