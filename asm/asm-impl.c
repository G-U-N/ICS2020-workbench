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
int asm_setjmp( asm_jmp_buf env) {
  //return setjmp(env);
  //把各个信息存储下来，最后返回rax
  //调用时，需要存储的是rbx，rsi,rdi,rbp,rsp,pc.
  asm("setjmp:"
  "push %%rbp;" //压栈
  "mov %%rsp, %%rbp;" //rsp和rbp都指向栈底。
  "mov %%rdi,%%rax;"//找到传送过来的参数，也就是env的头指针，存放在rdi中。
  "mov %%rbx,(%%rax);"
  "mov %%rsi,8(%%rax);"
  "mov %%rdi,16(%%rax);"//被调用者寄存器中的内容 rbx，rsi，rdi。
  "mov (%%rbp),%%rcx;"
  "mov %%rcx, 24(%%rax);"//调用之前的栈底地址rbp
  "lea 8(%%rbp),%%rcx;"
  "mov %%rcx,32(%%rax);"//调用setjmp之前的返回地址处,rsp
  "mov 8(%%rbp),%%rcx;"
  "mov %%rcx, 40(%%rax);"//上一个过程的rsp之前的eip，存储了读取指令的地址，所以会重复执行调用者。
  "xor %%rax,%%rax;"
  "pop %%rbp;"
  "ret;"
  :
  :
  :);
  return 0;
}

void asm_longjmp( asm_jmp_buf env, int val) {

  asm("longjmp:"
  "mov %%esi, %%eax;"
  "cmp %%eax,%%eax;"
  "jnz jm;"
  "inc %%eax;"
  "jm:"
  "mov (%%rdi),%%rbx;"
  "mov 8(%%rdi),%%rsi;"
  "mov 16(%%rdi),%%rdi;"
  "mov 24(%%rdi),%%rbp;"
  "mov 32(%%rdi),%%rsp;"
  "mov 40(%%rdi),%%rcx;"
  "jmp *%%rcx;"
  :"=S"(val)
  :"D"(env),"S"(val)
  :);
}
