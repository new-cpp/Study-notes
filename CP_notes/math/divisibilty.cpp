#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

const int MAXN = 1e6;
int max_div[MAXN + 1];
int phi    [MAXN + 1];

constexpr const int PRIME = -1;
/*
 * Sieve of Eratosthenes O(nlog(n))
*/


void sieve()
{

	for(int i = 2 ; i <= MAXN; ++i)
	{
		if(max_div[i] == 0)
		{
			/*is a prime number*/
			max_div[i] = PRIME;

			for(int j = 2 * i ; j <= MAXN; j+=i)
				{
					max_div[i] = i;	
				}

		}
	}
}

/*
 * prime factorization : 
 * 	every number have a unique prime factorization
 * 	n = (p_1 ^ a_1) *...*(p_i ^ a_i)
 * 
 * 	and number of divisor are : product of (1 + a_i)  for all i 
 * 
 * preprocessing: Sieve of Eratosthenes O(nlog(n))
 * complexity   : O(log(n))
 * */


void prime_factorization(int n)
{
	sieve();
	
	int div_count = 1;
	while(n != 1)
	{
		int prime = max_div[n];
		int curr_div_count = 0;
		while( n % prime == 0)
		{
			++curr_div_count;
			n/=prime;
		}

		div_count *= curr_div_count + 1;
	}

	std::cout<<"number of divisors of : " <<n<< " is " << div_count<<'\n';
}




/*
 *
 * factors of a number starting from 2
 *
 * 	time complexity = O(sqrt(n))
 */
std::vector<int> factors ( int n )
{

	std::vector<int> factor;
	for(int i = 2 ; i* i <= n ;++i)
	{
		while(n%i == 0)
		{
			factor.push_back(i);
			n/=i;
		}
	}
	
	if(n>1)
		factor.push_back(n);
	return factor;
}




/*
 *
 * GCD & LCM
 *
 */

int GCD (int a ,int b)
{
	if(b == 0) return a;
	return GCD(b,a%b);
}


int interative_GCD(int a, int b)
{
	while(b)
	{
		a = std::exchange( b , a%b);
	}
	return a;
}


template<typename Arg,typename... Args>
Arg GCD(Arg a , Arg b ,Args... more)
{
	return GCD(GCD(a, b), more...); 
}


int LCM( int a ,int b)
{
	return a*(b / GCD(a,b));
}




/*phi functions : count how many number from [1,n] are coprime with m.gcd(n,x) = 1
 *
 * phi(n*m) = ph(n)*ph(m)
 * phi(p)   = p-1  if p is a prime number
 * phi(n)  = p^q - p^q-1   if n = p^q (n is a power of a prime number)
 *
 * so phi(n) for all numbers is phi of it's prime factorization ... so
 * if n = product of pi^qi 
 *
 * ph(n) = product of (ph(pi^qi) = product (pi ^qi - pi ^(qi-1))
 *
 *
 * algo : is the same as prime factorization ... o(sqrt(n))
 **/


int phi_function(int n)
{
 int ans = n;
 for(int p = 2 ; p * p <=n ; ++p)
 {
      if(n%p == 0)
      {

	while(n%p==0)
	{
		n/=p;
	}
	ans-= ans/p; // the trick we get the same formulate as above
      }
 }
 if(n>1) ans-= ans/n;
 return ans;
}

/*
 *precomputation all phi function of all numbers from 1 to n.. same as sieve
 *
 */

void precompute()
{
	for(int i= 1; i<= MAXN ; ++i) phi[i]= i;
	for(int i = 2 ; i <= MAXN; ++i)
	{
		if(phi[i] == i) // i is prime
			{
				for(int j = i ; j <= MAXN; ++j)
				{
					phi[j]-= phi[j]/i;
				}
			}
	}
}

int main()
{
	/* factors*/
	auto f = factors(35);
	for(auto& ele : f)
		std::cout<<ele<<' ';
	std::cout<<'\n';

	prime_factorization(50);
	

	/*gcd*/
	for(int a = 1 ; a < 20; ++a)
		for(int b = 40 ; b < 60 ; ++b)
			assert(GCD(a,b) == interative_GCD(a,b));


	std::cout<<GCD(44,55,33,55,66,88)<<'\n';
	return 0;
}
