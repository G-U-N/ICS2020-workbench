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
  "mov 4(%%rsp), %%rax;"//参数buf的内容,也就是env的头地址。
  "mov %%rbx, (%%rax);"
  "mov %%rsi, 8(%%rax);"
  "mov %%rdi, 16(%%rax);"
  "mov %%rbp, 24(%%rax);"
  "lea 4c(%%rsp), %%rcx;"//rsp本身的值+4。
  "mov %%rcx , 32(%%rax);"
  "mov (%%rsp),%%rcx;"//rsp所指向的内存地址中的值，也就是下一条指令的地址。
  "mov %%rcx, 40(%%rax);"
  "xor %%rax,%%rax;"
  "ret;"
  :
  :
  :);
}

void asm_longjmp( asm_jmp_buf env, int val) {

  asm("longjmp:;"
  "mov 8(%%rsp), %%rdx;"
  "mov 16(%%rsp), %%rax;"
  "cmp %%rax,%%rax;"
  "jnz 1;"
  "inc %%rax;"
  "1:;"
  "mov (%%rdx), %%rbx;"
  "mov 8(%%rdx),%%rsi;"
  "mov 16(%%rdx),%%rdi;"
  "mov 24(%%rdx),%%rbp;"
  "mov 32(%%rdx),%%rcx;"
  "mov %%rcx,%%rsp;"
  "mov 40(%%rdx),%%rcx;"
  "jmp *%%rcx;"
  :
  :
  :);
}
