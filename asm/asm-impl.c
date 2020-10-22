#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  asm(  "addq %%rbx, %%rax;"
  :"=a" (a)
  : "a" (a),"b"(b));

  return a;
}

//汇编语言掌握的不好！

int asm_popcnt(uint64_t x) {
/*  int s = 0;
  for (int i = 0; i < 64; i++) {
    if ((x >> i) & 1) s++;
  }
  return s;
 */
  int ans;
  asm(
  "movl $0 %%eax;"//ans
  "movl $0 %%ecx;"//i
  "cycle:coml %%ecx $64;"
  "jge label;"
  "movq %%rbx %%rdx;"
  "shrq %%ecx %%rdx;"
  "andq $1 %%rdx;"
  "comq %%rdx $1;"
  "je t1;"
  "jmp t2;"
  "t1:"
  "incl %%eax;"
  "t2:"
  "jmp cycle;"
  "label:"
  :"=a"(ans)
  :"b"(x));

  return ans;
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
