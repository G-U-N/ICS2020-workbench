#include <stdint.h>
#include <stdio.h>


//返回(a+b)%m
uint64_t addmod(uint64_t a, uint64_t b, uint64_t m)
{
  return 0;
  
}

uint64_t multimod(uint64_t a,uint64_t b,uint64_t m)
{
  uint64_t ans=0;

  while(b>0)
  {
    if (b&1)
    {
      ans=(ans+a)%m;//此处可能会有问题
    }
    a=(a+a)%m;//此处可能会有问题

    b>>=1;
  }
  return ans;
  
}