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
  "jge end_memcpy;"
  "mov (%%rbx,%%rdx,4),%%rsi;"
  "mov %%rsi,(%%rax,%%rdx,4);"//指针都是32位。
  "incq %%rdx;"
  "jmp cycle_memcpy;"
  "end_memcpy:"
  :"=a"(dest)
  :"a"(dest),"b"(src),"c"(n));

  return dest;
   
}
int asm_setjmp( asm_jmp_buf env) {
  //return setjmp(env);
  //把各个信息存储下来，最后返回rax
  //调用时，需要存储的是rbx，rsi,rdi,rbp,rsp,pc.
  /*
  asm(
  ".globl setjmp;"
  "setjmp:;"
  "push %%rbp;" //压栈
  "mov %%rsp, %%rbp;" //指向下一条指令。rsp和rbp都是
  "mov %%rdi,%%rax;"//找到传送过来的参数，也就是env的头指针，存放在rdi中。
  "mov %%rbx,(%%rax);"
  "mov %%rsi,8(%%rax);"
  "mov %%rdi,16(%%rax);"//被调用者寄存器中的内容 rbx，rsi，rdi。
  "mov (%%rbp),%%rcx;"
  "mov %%rcx, 24(%%rax);"//存储以前的rbp
  "lea 16(%%rbp),%%rcx;"
  "mov %%rcx,32(%%rax);"//存储原来的buf地址，rsp的值，
  "mov 8(%%rbp),%%rcx;"
  "mov %%rcx, 40(%%rax);"//原来的eip指向的地址。
  "xor %%rax,%%rax;"
  "pop %%rbp;"
  "ret;"
  :
  :
  :);
  */
  //代补充，不使用pop的写法。
  asm("setjmp:;"
  "mov %%rdi, %%rax;"
  "mov %%rbx,(%%rax);"
  "mov %%rsi,8(%%rax);"
  "mov %%rdi,16(%%rax);"
  "mov %%rbp, 24(%%rax);"
  "lea 8(%%rsp), %%rcx;"
  "mov %%rcx,32(%%rax);"
  "mov (%%rsp),%%rcx;"
  "mov %%rcx,40(%%rax);"
  "xor %%rax,%%rax;"
  "ret;"
  :
  :
  :);
  return 0;
}

void asm_longjmp( asm_jmp_buf env, int val) {

  asm(
  ".globl longjmp;"
  "longjmp:;"
  "mov %%rdi, %%rdx;"
  "mov %%esi, %%eax;"
  "mov (%%rdx),%%rbx;"
  "mov 8(%%rdx),%%rsi;"
  "mov 16(%%rdx),%%rdi;"
  "mov 24(%%rdx),%%rbp;"
  "mov 32(%%rdx),%%rsp;"
  "jmp *40(%%rdx);"
  :
  :
  :);
}
