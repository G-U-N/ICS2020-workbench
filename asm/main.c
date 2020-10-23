#include "asm.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {

  printf("%ld\n",asm_add(1234,5678));

  printf("%d\n",asm_popcnt(0x0123456789abcdefULL));
  
  const char src[50]="hello world!";
  char dest[50];
  asm_memcpy(dest,src,strlen(src)+1);
  printf("dest=%s\n",dest);

  asm_jmp_buf buf;

  printf("%d\n",asm_setjmp(buf));
  
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
