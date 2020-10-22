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
  "cycle:cmpl $64, %%ecx;"
  "jge label;"
  "movq %%rbx, %%rdx;"
  "and $1,%%rdx;"
  "addl %%edx,%%eax;"
  "shrq $1,%%rbx;"
  "jmp cycle;"
  "label:"
  :"=a"(ans)
  :"b"(x));
  return ans;
}
//The shift is repeated the number of times indicated by the second operand, 
//which is either an immediate number or the contents of the CL register.
// To reduce the maximum execution time, the 80386 does not allow shift counts greater than 31.
// If a shift count greater than 31 is attempted, only the bottom five bits of the shift count are used. 
//(The 8086 uses all eight bits of the shift count.)

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
