#include <stdint.h>
#include <stdio.h>


uint64_t multimod(uint64_t a,uint64_t b,uint64_t m)
{
  uint64_t ans=0;

  while(b>0)
  {
    if (b&1)
    {
      ans=(ans+a)%m;
    }
    a=(a+a)%m;

    b>>=1;
  }
  
}