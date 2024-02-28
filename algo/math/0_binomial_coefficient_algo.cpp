#include <chorono>
#include <cstdint>

int32_t fact[1e6];

void pre_computed_factorial(int32_t n)
  {
    assert(n<static_cast<int32_t>(1e6));

    fact[0]=1;
    for(uint32_t i = 1 ; i <= n ; ++i)
      {
        fact[i]= i * fact[i-1];
      }
  }

int32_t naive_factorial(int32_t n)
  {
    uint32_t res = 1;
    for(uint32_t i = 2; i <=n ; ++i)
      res *= i;

    return res;
  }

int32_t combination_v1(int32_t n, int32_t k)
  {
    return (naive_factorial(n))/(naive_factorial(k)*naive_factorial(n-k));
  }

int32_t combination_v2(uint32_t n , uint32_t k)
  {
    double res = 1;
    for(double i = 1 ; i <static_cast<double>(n-k);++i)
      {
        res*=i; // overfloat :D!!
      }
    for(double i = 1 ; i < static_cast<double>(k);++i)
      {
        res/=i;
      }
    return res;
  }

int32_t combination_v3(uint32_t n , int32_t k)
  {
    double res = 1;
    for(int32_t i = 1 ; i <= k ; ++i)
      res = res*(n-k+i)/i;

    return static_cast<int32_t>(res + 0.01);
  }

// pascal Triangle
constexpr int32_t maxn = 1e5;
int32_t C[maxn + 1][maxn + 1];

int32_t combination_v4()
  {
    C[0][0] = 1;
    for(int32_t i = 1 ; i <= maxn; ++i)
      {
        C[i][0] = C[i][i] = 1;
        for(int32_t k = 1 ; k <= i ; ++k)
          C[n][k] = C[n-1][k-1] + C[n-1][k];
      }
  }
// case of p is prime number
#region FERMAT_LITTLE_THEORM
namespace modulate_inverse_and_fermat_little_theorm
{
  int32_t powmod(int32_t a , int32_t b , int32_t p )
    {
      int32_t res = 1;
      while(b)
        {
          if(b&1)
            {
              res*=a;
              res%=p
              --b;
            }

           a*=a;
           a%=p;
           b>>=1;
        }

      return res;
    }

  int32_t inv(int32_t a ,int32_t p)
    {
      return powmod(a,p-2,p);
    }

  int32_t nCk(int32_t n , int32_t k, int32_t p)
    {
      return ((fact[n] * inv(fact[k],p)%p)* inv(fact[n-k],p))%p;
    }
}



int main()
  {
    return 0;
  }
