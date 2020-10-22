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
  "movl $0, %%eax;"//ans
  "movl $0, %%ecx;"//i
  "cycle_popcnt:cmpl $64, %%ecx;"
  "jge label;"
  "movq %%rbx, %%rdx;"
  "shrq %%ecx, %%rdx;"
  "and $1, %%rdx;"
  "cmpq $1, %%rdx;"
  "je t1;"
  "jmp t2;"
  "t1:"
  "incl %%eax;"
  "t2:"
  "incl %%ecx;"
  "jmp cycle_popcnt;"
  "label:"
  :"=a"(ans)
  :"b"(x));
  return ans;
  /*更快的代码
    "movl $0, %%eax;"//ans
  "movl $0, %%ecx;"//i
  "cycle:cmpl $64, %%ecx;"
  "jge label;"
  "movq %%rbx, %%rdx;"
  "and $1,%%rdx;"
  "addl %%edx,%%eax;"
  "incl %%ecx;"
  "shrq $1,%%rbx;"
  "jmp cycle;"
  "label:"
  :"=a"(ans)
  :"b"(x));
  */
}

void *asm_memcpy(void *dest, const void *src, size_t n) {

  asm("movq $0, %%rdx;"//i
  "cycle_memcpy: cmpq %%rdx, %%rcx;"
  "jbe end_memcpy;"
  "mov (%%rbx,%%rdx,4), (%%rax,%%rdx,4);"
  "incq %%rdx;"
  "jmp cycle_memcpy;"
  "end_memcpy:"
  :"=a"(dest)
  :"a"(dest),"b"(src),"c"(n));

  return dest;
   
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
