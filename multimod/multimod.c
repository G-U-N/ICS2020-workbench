#include <stdint.h>

const uint64_t half=9223372036854775808UL;
const uint64_t whole_1= 18446744073709551615UL;

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
 
  uint64_t ans=0;
  
  a%=m;

  while(b)
  {
    if(b&1)//如果b是奇数
    {
      //这一步的ans+a可能已经出现了溢出
      if(ans<half|| a<half)
      {
             ans=(ans+a)%m;
      }
      else
      {
        ans=((((ans-half)+(a-half))%m+(whole_1)%m)%m+1)%m;
        
      }
      


    }

     //这一步的a+a可能已经出现了溢出。 

    if (a<half) 
    {
      a=(a+a)%m;
    }
    else
    {
      a=((((a-half)+(a-half))%m+(whole_1)%m)%m+1)%m;
    }
    
    b>>=1;//b/=2;
  }

  return ans;


}
