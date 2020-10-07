#include <stdint.h>

#define half 9223372036854775808
#define whole 18446744073709551616

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
 
  uint64_t ans=0;
  
  a%=m;

  while(b)
  {
    if(b&1)//如果b是奇数
    {
      //这一步的ans+a可能已经出现了溢出
      ans=(ans+a)%m;

    }

     //这一步的a+a可能已经出现了溢出。 

    if (a<half) 
    {
      a=(a+a)%m;
    }
    else
    {
      a=((a-half)+(a-half))%m+(whole-1)%m+1;
    }
    
    b>>=1;//b/=2;
  }

  return ans;


}
