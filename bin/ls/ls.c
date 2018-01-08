#include "file.h"
#include "system.h"
#include "write.h"

#define O_RDONLY1	0x0000

struct linux_dirent {
               unsigned long  d_ino;     /* Inode number */
               unsigned long  d_off;     /* Offset to next linux_dirent */
               unsigned short d_reclen;  /* Length of this linux_dirent */
               char           d_name[];  /* Filename (null-terminated) */
           };


int main(int argc, char *argv[] ){

if(argc!=2)
{
	putOnFd("ls usage : ls <pathOfDirectory>\n",1);
}
else{
char *filePath="/home/mkhaira";


if( argc == 2 ){
			filePath= argv[1];
}

unsigned long ret=0;

char buf[1024];

struct linux_dirent *d;

int commandNumber=2;

/*__asm__("movq %1, %%rax;\n"
	   "movq %2, %%rdi;\n"
	   "movq %3, %%rsi;\n"
	   "syscall;\n"
	   "movq %%rax, %0;\n"
	   : "=g"(ret)
	   : "m"(commandNumber),"m"(filePath),"m"(ret)
	   : "rax","rdi","rsi");

*/

ret=_fdopen(filePath,0);

if(ret<2 || ret >100)
{
	putOnFd("Please provide a valid directory as input\n",1);
}
else{
commandNumber=78;
//printf("fd is %lu\n",ret);
unsigned long bufferSize=1024;
unsigned long nndode=0;
__asm__("movq %1, %%rax;\n"
	   "movq %2, %%rdi;\n"
	   "movq %3, %%rsi;\n"
	   "movq %4, %%rdx;\n"
	   "syscall;\n"
	   "movq %%rax, %3;\n"
	   : "=g"(nndode)
	   : "m"(commandNumber),"m"(ret),"g"(buf),"g"(bufferSize)
	   : "rax","rdi","rsi","rdx");

for (int bpos = 0; bpos < nndode;) {
            d = (struct linux_dirent *) (buf + bpos);
            putOnFd(d->d_name,1);
            putOnFd("\n",1);
            bpos += d->d_reclen;
        }
	return ret;
}
}
}


