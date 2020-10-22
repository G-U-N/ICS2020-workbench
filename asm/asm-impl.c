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
  //You can't reference two memory locations in a single mov instruction.
  //不确定是否正确。
  asm("movq $0, %%rdx;"//i
  "cycle_memcpy: cmpq %%rdx, %%rcx;"
  "jbe end_memcpy;"
  "mov (%%rbx,%%rdx,4),%%rsi;"
  "mov %%rsi,(%%rax,%%rdx,4);"//指针都是32位。
  "incq %%rdx;"
  "jmp cycle_memcpy;"
  "end_memcpy:"
  :"=a"(dest)
  :"a"(dest),"b"(src),"c"(n));

  return dest;
   
}
//esp保存当前栈顶的地址。
//ebp保存当前函数栈帧的地址。
//eip保存下一条指令的地址。
int asm_setjmp( asm_jmp_buf env) {
  //return setjmp(env);
  //把各个信息存储下来，最后返回eax

  //调用时，需要存储的是ebx，esi,edi,ebp,esp,pc.
  asm("setjmp:"
  "movq 8(%%rsp), %%rax;"//把数组首地址地址取下来。
  "movq %%rbx, (%%rax);"
  "movq %%rsi, 8(%%rax);"
  "movq %%rdi, 16(%%rax);"
  "movq %%rbp, 24(%%rax);"
  "leaq 8(%%rsp), %%rcx;"//rsp本身的值+8
  "movq %%rcx , 32(%%rax);"
  "movq (%%rsp),%%rcx;"//rsp所指向的内存地址中的值，也就是下一条指令的地址。
  "movq %%rcx, 40(%%rax);"
  "xorq %%rax,%%rax;"
  "ret;");
}

void asm_longjmp( asm_jmp_buf env, int val) {
  longjmp(env, val);
}
