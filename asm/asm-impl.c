#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  int ans;
/*  asm(  "addq %%rbx, %%rax;"
  :"=a" (ans)
  : "a" (a),"b"(b));
*/
  asm("addq %1,%0;"
  :"=a"(ans)
  :"a"(a),"b"(b));
  return ans;
}

//汇编语言掌握的不好！

int asm_popcnt(uint64_t x) {
  int s = 0;
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
