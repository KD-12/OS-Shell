#include <string.h>
#include <syscall.h>
#include <system.h>
#include <write.h>
#include <log.h>
#ifndef FILE_H
#define FILE_H


int _fdopen(char * path_name,unsigned long flags)
{
//	unsigned long ret=0;
  unsigned long command=2;
  __asm__("movq %1, %%rax;\n"
     "movq %2, %%rdi;\n"
     "movq %3, %%rsi;\n"
     "syscall;\n"
     "movq %%rax, %0;\n"
     : "=g"(flags)
     : "m"(command),"m"(path_name),"m"(flags)
     : "rax","rdi","rsi");
    return(int) flags;
}
int _fdclose(int fd)
{
    unsigned long ret = __syscall1(3,fd);
    return (int)ret;
}
int _fdread(int file_discriptor,char * string,int len_string)
{
  signed int  ret =(signed int) __syscall4(0,file_discriptor,string,len_string);	 
  return (int)ret;
}

  int fileExist(char *path){
	logIt("checking for file : ");
	logIt(path);
	logIt("\n");
	path=trim(path);
	int file = _fdopen(path, 0);
	logIt("going to check\n");
	if(file>0 && file <100){
		_fdclose(file);
		return 1;
	}
	if(file >100)
	{
		logIt("file greater than 100\n");
	}
	logIt("could not find the file\n");
	return 0;
  }

 char *fileContent(char *path,int sz) {
    int file = _fdopen(path, 0);
    char *returnCommand;
    if (file>0 && file <100) {
      returnCommand = (char *) _malloc(sz*sizeof(char));
	int i= _fdread(file,returnCommand,sz);
	 if(i < 0){
      	  putOnFd("Error in File Read",1);
	  _fdclose(file);
	  return 0;
      }
      *(returnCommand + i - 1) = '\0';
      _fdclose(file);
      return returnCommand;
    }
    return 0;
  }
 
 void writeToFile(char *path, char *content){
	int fd=_fdopen(path,1);
	
	if(fd >0 && fd<100){
		putOnFd(content,1);
		_fdclose(fd);
	}
	else{
	   logIt("unable to write file :");
	   logIt(path);
	   logIt("\n");
	}
}
#endif 
