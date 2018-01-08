#ifndef _SYSCALL_H
#define _SYSCALL_H
#define SYSCALL_TYPE(d) static __inline unsigned long __syscall##d

SYSCALL_TYPE(0)(unsigned long n)
{
 unsigned long ret;
   __asm__("movq %1, %%rax;\n"
          "syscall;\n"
          "movq %%rax, %0\n"
          : "=g"(ret)
          : "m"(n)
          : "rax");
    return ret;
}
SYSCALL_TYPE(1)(unsigned long n,int n1)
{
unsigned  long ret;
    __asm__ (
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
        "syscall;\n"
        : "=g" (ret)
        : "m"(n), "m"(n1)
        : "%rdi",  "%rax"
    );
    return ret;
}
SYSCALL_TYPE(2)(unsigned long n,int *n1)
{
unsigned long ret;
    __asm__ (
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
        "syscall;\n"
        : "=g" (ret)
        : "m"(n), "m"(n1)
        : "%rdi",  "%rax"
    );
     return ret;
}

   /*SYSCALL_TYPE(1)(int n,int n1)
{
int ret;
    __asm__ (
        "movq %2, %%rdi;"
        "movq %1, %%rax;"
        "int $0x80;"
        : "=a" (ret)
        : "g"(n1), "a"(n)
        : "%rdi",  "%rax"
    );
    return ret;
}
SYSCALL_TYPE(2)(int n, char* p,int f)
{

 int ret;
    __asm__ (
        "movq %2, %%rdi;"
        "movq %3, %%rsi;"
        "movq %1, %%rax;"
        "int $0x80;"
        : "=a" (ret)
        : "g"(p), "g"(f), "a"(n)
        : "%rdi", "%rsi", "%rax"
    );
    return ret;
}

SYSCALL_TYPE(3)(int n, char * p)
{

 int ret;
    __asm__ (
        "movq %2, %%rdi;"
        "movq %1, %%rax;"
        "int $0x80;"
        : "=a" (ret)
        : "g"(p),  "a"(n)
        : "%rdi",  "%rax"
    );
    return ret;
}
*/
SYSCALL_TYPE(3)(unsigned long n, char* p)
{

 unsigned long ret;
    __asm__ (
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
        "syscall;\n"
        "movq %%rax, %0;"
        : "=g" (ret)
        : "m"(n), "m"(p)
        : "%rax", "%rdi"
    );
    return ret;
}

SYSCALL_TYPE(4)(unsigned long n,unsigned long n1, char* p,unsigned long f)
{

 unsigned long ret;
    __asm__ (
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
        "movq %3, %%rsi;\n"
        "movq %4, %%rdx;\n"
        "syscall;\n"
	"movq %%rax, %0;"
        : "=g" (ret)
        : "m"(n),"m"(n1), "m"(p), "m"(f)
        : "%rax", "%rdi", "%rsi","%rdx"
    );
    return ret;
}
SYSCALL_TYPE(5)(unsigned long n,int* n1)
{
unsigned  long ret;
    __asm__ (
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
        "syscall;\n"
        : "=g" (ret)
        : "m"(n), "m"(n1)
        : "%rdi",  "%rax"
    );
    return ret;
}
SYSCALL_TYPE(6)(unsigned long n,char *n1, char * const n2[],char * n3[])
{
unsigned  long ret;
   __asm__(
        "movq %1, %%rdi;\n"
        "movq %2, %%rsi;\n"
       "movq %3, %%rdx;\n"
       "movq %4, %%rax;\n"
       "syscall;\n"
       : "=g" (ret)
       : "m"(n1),"m"(n2), "m"(n3), "m"(n)
       : "%rdi", "%rsi", "%rax","%rdx"
   );
   return ret;
}
SYSCALL_TYPE(7)(unsigned long n,char *n1,unsigned long flag)
{
unsigned  long ret;
   __asm__(
        "movq %1, %%rax;\n"
        "movq %2, %%rdi;\n"
       "movq %3, %%rsi;\n"
       "syscall;\n"
       : "=g" (ret)
       : "m"(n),"m"(n1), "m"(flag)
       : "%rdi", "%rsi", "%rax"
   );
   return ret;
}
#endif
