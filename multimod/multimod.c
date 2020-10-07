#include <stdint.h>
#include <stdio.h>

const uint64_t half=9223372036854775808UL;
const uint64_t whole_1= 18446744073709551615UL;



uint64_t mod(uint64_t a, uint64_t m)
{
  if((!(m&(m-1)) )&& m)
  {
    int k;
    for( k=0;(k<64)&!((1<<k)&m);k++);

    return a&((1<<k)-1);
  }

  while (a>=m)
  {
    a-m;
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
      //这一步的ans+a可能已经出现了溢出
/*      if(ans<half&& a<half)
      {
             ans=(ans+a)%m;
      }
      else if(ans>=half && a>=half)
      {
        ans=((((ans-half)+(a-half))%m+(whole_1)%m)%m+1)%m;
        
      }
      else if (ans>=half&&a<half)
      {
        ans=((((ans-half)+a)%m+(half)%m))%m;
      }
      else
      {
        ans=((((ans)+(a-half))%m+(half)%m))%m;
      }
      
*/      
      


    }

     //这一步的a+a可能已经出现了溢出。 
/*
    if (a<half) 
    {
      a=(a+a)%m;
    }
    else
    {
      a=((((a-half)+(a-half))%m+(whole_1)%m)%m+1)%m;
    }
*/    
    a=mod(a+a,m);
    b>>=1;//b/=2;
  }

  return ans;


}
