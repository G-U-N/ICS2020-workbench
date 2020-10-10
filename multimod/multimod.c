#include <stdint.h>
#include <stdio.h>



//const uint64_t half=9223372036854775808UL;
//const uint64_t whole_1= 18446744073709551615UL;
//如果能够处理好a+b取模m，我就能通过所有样例。


uint64_t mod(uint64_t a, uint64_t m)
{
  //当m是2的整数次幂时。
  if((!(m&(m-1)) )&& m)
  {
    int k;
    for( k=0;(k<64)&& !((1<<k)&m);k++);

    return a&((1<<k)-1);
  }
  while(a>=m)
  {
    a-=m;
  }
  return a;
  
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
 
  uint64_t ans=0;
  
  a=mod(a,m);

  while(b)
  {
    if(b&1)//如果b是奇数
    {
      ans=mod((ans+a),m);

    }

    a=mod(a+a,m);
    b>>=1;//b/=2;
  }

  return ans;


}


//变相的快速幂。
/*
uint64_t mod(uint64_t v, uint64_t m)
{
    //当m是2的整数次幂时。用于秒过简单样例
    while(v>=m)
    {
      v-=m;
    }
    return v;
    
}
uint64_t multimod(uint64_t a, uint64_t b, uint64_t m)
{
  uint64_t ans=0;
  for(int i=0;i<64;i++)
  {
    int temp=(a>>i)&1UL;
    if(temp)
    {
      ans+=mod((b<<i),m);
    }
    ans=mod(ans,m);
  }
  return ans;



}
*/