#include <stdint.h>
#include <stdio.h>


//返回(a+b)%m
uint64_t addmod(uint64_t a, uint64_t b, uint64_t m)
{
  uint64_t max_1=18446744073709551615;
  //如果溢出
  if(a+b<a||a+b<b)
  {
   return (a+b)%m+(max_1)%m+1;
  }
  //没有溢出
  else
  {
    return (a+b)%m;
    
  }
  
  
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