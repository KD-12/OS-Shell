#include "file.h"
#include "system.h"
#include "write.h"

#define O_RDONLY1	0x0000

int main(int argc, char *argv[] ){

if(argc!=2)
{
	putOnFd("ls usage : ls <pathOfDirectory>\n",1);
}
else{
char *filePath;

if( argc == 2 ){
	filePath= argv[1];
}

unsigned long ret=0;

ret=_fdopen(filePath,0);

if(ret<2 || ret >100)
{
	putOnFd("Please provide a valid directory as input\n",1);
}
else
{
char string[2000];
int read=_fdread(ret,string,2000);
if(read<0)
{
	putOnFd("unable to read the file\n",1);
}
putOnFd(string,1);
	
}

}
}


