#include "string.h"

#ifndef WRITE_H
#define WRITE_H


int putOnFd(char * str, int fd ){
//puts("In put console");
long write = 1;
long stdout= fd;

unsigned long len=getStringSize(str)+1;
unsigned long ret=0;
__asm__("movq %1, %%rax;\n"
  "movq %2, %%rdi;\n"
  "movq %3, %%rsi;\n"
  "movq %4, %%rdx;\n"
  "syscall;\n"
  "movq %%rax, %0\n"
  : "=g"(ret)
  : "m"(write),"m"(stdout),"m"(str),"m"(len)
  : "rax","rdi","rsi","rdx");
return (int)ret;
}

#endif
