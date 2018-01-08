#include "syscall.h"

#ifndef SYSTEM_H
#define SYSTEM_H

#define PROT_READ	0x1     
#define PROT_WRITE	0x2     
#define PROT_EXEC	0x4
#define MAP_PRIVATE	0x02
#define MAP_ANONYMOUS 0x20
#define MAP_SHARED	0x01

char bigBuffer[1000000];
char *mallocPointer=bigBuffer;

//int myExit(int n)
//{
 //   unsigned long ret = __syscall0(60);
  //  return (int)ret;
//}
/*void _getcwd(char *buf){

unsigned long size=100;
int command=79;
unsigned long ret=0;

 __asm__("movq %1, %%rax;\n"
     "movq %2, %%rdi;\n"
     "movq %3, %%rsi;\n"
     "syscall;\n"
     "movq %%rax, %0;\n"
     : "=g"(ret)
     : "m"(command),"m"(buf),"m"(size)
     : "rax","rdi","rsi");

&ret;
}
*/
int myExit(int n)
{
    unsigned long ret = __syscall0(60);
    return (int)ret;
}


signed int _forkIt()
{
   return(signed int)__syscall0(57);
}
int _chdir(char * new_path)
{
 return (int)__syscall3(80,new_path);
}
int _pipe(int pipebuf[2])
{
  return (signed int)__syscall2(22, pipebuf);
}
int _dup(int oldfd)
{
  return (int)__syscall1(32,oldfd);
}
signed int _wait(int *status)
{
 return (signed int)__syscall5(61,status);
}
int _execve(char * cmd, char * const argv[],char * env[])
{
	unsigned long a=59;
	return (int)__syscall6(a,cmd,argv,env);
}/*void * _malloc(unsigned long length){
void *ret;
unsigned long start=0;
unsigned long  command=9;
unsigned long permissions=PROT_WRITE|PROT_READ;
unsigned long flags=MAP_ANONYMOUS|MAP_SHARED;
unsigned long fd=-1;
unsigned long off=0;

 __asm__("mov %1, %%eax;\n"
     "mov %2, %%ebx;\n"
     "mov %3, %%ecx;\n"
     "mov %4, %%edx;\n"
     "mov %5, %%r10;\n"
     "mov %6, %%r8;\n"
     "mov %7, %%r9;\n"
     "syscall;\n"
     : "=m"(ret)
     : "m"(command),"m"(start),"m"(length),"m"(permissions),"m"(flags),"m"(fd),"m"(off)
     :);

//&ret;
 return ret;
}*/
void * _malloc(int length){

void *toReturn=mallocPointer;
mallocPointer+=length+10;
return toReturn;

}
/*
int chdir(char * new_path)
{
	if(new_path !=0)
	{
	 return (int)__syscall3(80,new_path);
	}
}

signed int fork()
{
   return(signed int)__syscall0(57);
}*/
#endif
