#include <stdint.h>
#include <stdio.h>

uint64_t mod(uint64_t a,uint64_t m)
{

  uint64_t x=m;
  while(x<=a>>1)
  {
    x<<=1;
  }
  while(a>=m)
  {
    if(a>=x)
    {
      a-=x;
    }
    x>>=1;
  }
  return a;
  

}

//返回(a+b)%m
uint64_t addmod(uint64_t a, uint64_t b, uint64_t m)
{
  uint64_t max_1=18446744073709551615UL;
  //如果溢出
  if(a+b<a||a+b<b)
  {
   return addmod(mod(a+b,m),mod(max_1,m)+1,m);
  }
  //没有溢出
  else
  {
    return mod(a+b,m);
    
  }
  
  
}

uint64_t multimod(uint64_t a,uint64_t b,uint64_t m)
{

  uint64_t ans=0;
  a=mod(a,m);

  while(b)
  {
    if (b&1)
    {
      ans=addmod(ans,a,m);//此处可能会有问题
    }
    a=addmod(a,a,m);//此处可能会有问题

    b>>=1;
  }
  return ans;
  
}