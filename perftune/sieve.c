#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

clock_t start,total;

#define N 10000000

static bool is_prime[N];
static int  primes[N];


//欧拉筛时间，o(n).
//埃氏筛的时间o(nloglogn)

//#define origin
#define ola

#ifdef origin

int *sieve(int n) {
  assert(n + 1 < N);
  start=clock();
  for (int i = 0; i <= n; i++)
    is_prime[i] = true;

  for (int i = 2; i <= n; i++) {
    for (int j = i + i; j <= n; j += i) {
      is_prime[j] = false;
    }
  }



  int *p = primes;
  for (int i = 2; i <= n; i++)
    if (is_prime[i]) {
      *p++ = i;
    }
  *p = 0;
  total=clock()-start;
  printf("%ld",total);
  return primes;
}

#endif


#ifdef ola
int *sieve(int n)
{
  start=clock();
  for (int i=2;i<=n;i++)
  {
    is_prime[i]=1;
  }
  int cnt=0;

  for (int i=2;i<=n;i++)
  {
    if (is_prime[i])
    {
      primes[cnt++]=i;
    }


    for (int j=0;j<cnt && i*primes[j]<=n;j++)
    {
      is_prime[i*primes[j]]=0;

      if (i%primes[j]==0)
      {
        break;
      }
    }
  }

  primes[cnt]=0;
  total=clock()-start;  
  printf("%ld",total);
  return primes;
  
}
#endif
