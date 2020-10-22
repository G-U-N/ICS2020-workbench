#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {

  printf("%ld\n",asm_add(1234,5678));

  printf("%d\n",asm_popcnt(0x0123456789abcdefULL));

  void *dest;

  printf("%p\n",asm_memcpy(dest,"1234567",5));

  asm_jmp_buf buf;
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
