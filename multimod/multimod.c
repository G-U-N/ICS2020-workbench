#include <stdint.h>

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {

  uint64_t ans;
  
  a%=m;

  while(b)
  {
    if(b&1)//如果b是奇数
    {
      ans=(ans+a)%m;

    }


    a=(2*a)%m;

    b>>=1;//b/=2;
  }

  return ans;


}
