#define _GNU_SOURCE
#include <string.h>
#include <file.h>
#include <log.h>
#include <parse.h>
#include <ps1.h>
#include <executer.h>
#include <write.h>
#define PATHFILE "path.txt"

void parseAndExecute(char *input);

unsigned int MAXLINE_LENGTH=1000;
char *pwd;
char *path;
char ** pathArray;
int pathArrayCount=1;
//extern char **environ;

void getPath(){
	path=fileContent(PATHFILE,500);
	if(!path){
		path="/shared/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games";
                pathArray=split(path,":",&pathArrayCount);
		pathArrayCount=1;
		logIt("i am here trying to getPath\n");
		char *env=executeAndReturn("printenv",3000);
		logIt("printf env is : ");
		logIt(env);
		logIt("\n");
		int splitedCount=0;
		char **envSplitted=split(env,"\n",&splitedCount);;
		for(int i=0;i<splitedCount;i++)
		{
			if(startsWith(envSplitted[i],"PATH"))
			{
				path=trim(substring(envSplitted[i],5));
			}
		}
		logIt("path is :");
		logIt(path);
		logIt("\n");
		writeToFile(PATHFILE,path);
	}
	pathArray=split(path,":",&pathArrayCount);
}
int main(int argc, char *argv[], char *envp[]) {
        char *input;
        getPath();
        logIt("Starting up \n");
	pwd=executeAndReturn("pwd",50);
  	initializePS1();
	//homeDirectory=executeAndReturn("echo eval ~");
        input=(char*) _malloc(MAXLINE_LENGTH*sizeof(char));
        while(1){
           	logIt("getting the prompt\n");
	       	char *prompt=getPrompt();
	       	logIt("prompt received\n");
	       	putOnFd(prompt,1);
//	       	free(prompt);
		int status=_fdread(0,input,MAXLINE_LENGTH);
		*(input+status)='\n';
		*(input+status+1)='\0';       
	//	int status = getline(&input,&MAXLINE_LENGTH,stdin);
		if(status < 0){
			return 0;
		}
		logIt("received input :");
	       	logIt(input);
	       	logIt("\n");
	       	parseAndExecute(input);
	       	logIt("ready to take another input\n");
        }
        return 0;
}


