#include "string.h"
#include "file.h"

#ifndef EXECUTER_H
#define EXECUTER_H

#define TEMPFILE "text.txt"
#define PATHFILE "path.txt"

extern char *path;
extern char **pathArray;
extern char *PS1;
extern char *pwd;
extern int pathArrayCount;

char *execCommand(char *command, char *buf,int size){
	int status = 1;
	int splittedCount=0;
	char **args = split(trim(command)," ",&splittedCount);
	if(splittedCount==0)
	{
		splittedCount=1;
	}
	if(args[0]){
		args[splittedCount] = 0; 
		signed int pid;
		int pipefd[2];
		_pipe(pipefd);
		char *buffer=(char *)_malloc(size*sizeof(char));
		logIt(pathArray[0]);
		for(int j=0;j<pathArrayCount;j++)
		{
			char *commandPath=concatenate(concatenate(pathArray[j],"/"),args[0]);
			logIt("checking command :\n");
			logIt(commandPath);
			logIt("\n");
			if(fileExist(commandPath)){
				
				args[0]=commandPath;
				break;
			}
		}
		logIt("full command is : ");
		logIt(args[0]);
		logIt("\n");
		pid = _forkIt();
		if(pid == 0){
			_fdclose(pipefd[0]);
			_fdclose(1);
			_dup(pipefd[1]);
			char *envp1[]={
        			0
			};
			_execve(args[0],args,envp1);
			//logIt("exec done\n");
			_fdclose(pipefd[1]);
			myExit(0);
		}
		else{
			while(_wait(&status) != pid);
			_fdclose(pipefd[1]);
			int i = _fdread(pipefd[0], buffer,size);
			*(buffer+i)='\n';
                	*(buffer+i+1)='\0';
		}
		buf = buffer;
		return buf;
	}
	return 0;
}
char *executeAndReturn(char *command,int size){
        char *returnCommand = 0;
        logIt("command received is : ");
	logIt(command);
	logIt("\n");
	if(command){
		char *buf=0;
		logIt("executing the command now to get output\n");
		buf = execCommand(command, buf,size);
		logIt("buffer is : ");
		logIt(buf);
		logIt("\n");
		returnCommand = trim(buf);
        }
        return returnCommand;
}

int executeSpecialCommand(char *command){
	if(startsWith(reduceWhiteSpace(command),"export PATH=")||startsWith(reduceWhiteSpace(command),"export PATH =")){
		char *newPath=substring(command,indexOfChar(command,'=')+1);
		newPath=replaceString(newPath,"$PATH",path);
		path=newPath;
		writeToFile(PATHFILE,newPath);
	//	setenv("PATH",path,1);
//		free(pathArray);
		pathArray=split(path,":",&pathArrayCount);
		putOnFd(concatenate("PATH updated to : ",path),1);
		putOnFd("\n",1);
		return 1;
	}
        if(startsWith(reduceWhiteSpace(command),"export PS1=")||startsWith(reduceWhiteSpace(command),"export PS1 =")
	 || startsWith(reduceWhiteSpace(command),"PS1=")||startsWith(reduceWhiteSpace(command),"PS1 =")){
                char *newPs1=substring(command,indexOfChar(command,'=')+1);
		int sizeOfPs1=getStringSize(newPs1);
		if(sizeOfPs1>=2 && (newPs1[0]==newPs1[sizeOfPs1-1]) && (newPs1[0]=='"'||newPs1[0]=='\'')){
		    char encloser[1]={newPs1[0]};
		    newPs1=replaceString(newPs1,encloser,"");
		    newPs1=replaceString(newPs1,encloser,"");
		}
		PS1=newPs1;
		putOnFd(concatenate("PS1 updated to : ",newPs1),1);
                putOnFd("\n",1);
		return 1;
	}
	if(startsWith(trim(command),"cd ")){
		char *argument=trim(replaceString(command,"cd ",""));
		int status = _chdir(argument);
		if(status < 0)
		{
			putOnFd("Error in Chdir",1);
		}
		pwd=executeAndReturn("pwd",100);
		return 1;
	}
	if(isEqual(trim(command),"exit")){
		myExit(0);
       }
	if(isEqual(trim(command),"echo $PATH")){
		putOnFd(path,1);
		putOnFd("\n",1);
		return 1;
	}
        if(isEqual(trim(command),"echo $PS1")){
                putOnFd(PS1,1);
                putOnFd("\n",1);
        	return 1;
	}

        return 0;
}

void executeCommand(char *command){
	command=trim(command);
	logIt("command is : ");
	logIt(command);
	logIt("\n");
	if(!executeSpecialCommand(command)){
	logIt("not a special command\n");
	int counter=0;
	int splitNumber;
	char **splitCommands=split(command," ",&splitNumber);
	char *basicCommand=splitCommands[0];
	logIt("basic command is : ");
	logIt(basicCommand);
	logIt("\n");
	while(1){
	    if(counter>=pathArrayCount){
	 	putOnFd("Unable to find command ",1);
		putOnFd(basicCommand,1);
		putOnFd(" in path : ",1);
		putOnFd(path,1);
		putOnFd("\n",1);
		break;
	    }
	    char *commandPath=concatenate(concatenate(pathArray[counter],"/"),basicCommand);
	    logIt("trying to find at commandPath :");
	    logIt(commandPath);
            logIt("\n");
	    char *fullCommand=concatenate(concatenate(pathArray[counter],"/"),command);
 	    logIt("full command with path is : ");
	    logIt(fullCommand);
            logIt("\n");
 	    if(fileExist(commandPath)){
		logIt("command exists\n");
		//	int status = system(fullCommand);
                //	if(status < 0){
                  //      	putOnFd("Error in System Command",1);
                //	}
		char *buf = 0;
		buf=execCommand(command,buf,500);
                if(buf == 0){
                        putOnFd("Error in System Command",1);
                }
                putOnFd(buf,1);
		break;
	    }
	    else{
	    	logIt("command doesnot exist at this location in path :\n");
	    }
	    counter++;
	 }
//	free(splitCommands);
    }
}

#endif 
