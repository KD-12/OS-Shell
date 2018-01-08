#include "executer.h"
#include "string.h"
#include "file.h"
#include "log.h"
#include "system.h"

#ifndef PARSE_H
#define PARSE_H

#define MAXCOMMANDS 100

void logIt(char *);
int executeScript(char *);

void executeCommands(char **commands,int commandNumber){
	for(int i=0;i<commandNumber;i++)
        {
                char *commandToBeExecuted=commands[i];
                if(i!=(commandNumber-1)){
                        commandToBeExecuted=concatenate(commandToBeExecuted," > commandOutput.txt");
                        char *suffix;
                        if(i%2){
                            suffix="_odd";
                        }
                        else{
                            suffix="_even";
                        }
                        commandToBeExecuted=concatenate(commandToBeExecuted,suffix);
                }
                if(i!=0)
                {
                         commandToBeExecuted=concatenate(commandToBeExecuted," < commandOutput.txt");
                        char *suffix;
                        if(i%2){
                            suffix="_even";
                        }
                        else{
                            suffix="_odd";
                        }
                        commandToBeExecuted=concatenate(commandToBeExecuted,suffix);
                }
                logIt("command to Be executed : ");
                logIt(commandToBeExecuted);
                logIt("\n");
								if(executeScript(commandToBeExecuted)){
									logIt("Script executed?\n");
									return;
								}
								else{
									logIt("Script not executed?\n");
									logIt(commandToBeExecuted);
									executeCommand(commandToBeExecuted);
								}

                logIt("command Executed\n");
        }
        if(commandNumber>1){
                logIt("deleting the output files\n");
                executeCommand("rm -rf commandOutput.txt*");
                logIt("deleted the output files\n");

        }

}

void parseAndExecute(char *input){

        //TODO: make a generic srack implementation in future;
        //TODO: make full lexical analyzer
        //TODO: handle trailing space after & in the end

        if(!getStringSize(trim(input))){
                return;
        }
				// logIt("At ParseExec\n");
				// logIt(input);
	extern unsigned int MAXLINE_LENGTH;
        char *specialCharStack,*initialPointer;//*commandStartPointer;
        initialPointer=specialCharStack=(char*)_malloc(MAXLINE_LENGTH*sizeof(char)/2);
        char *commands[MAXCOMMANDS];
        char c;
        int thisCommandSize,commandNumber,commandInBackground;
        thisCommandSize=commandNumber=commandInBackground=0;
        for(int i=0;(c=*(input+i))!='\0';i++,thisCommandSize++){
                if(c=='\\' && (*(input+i)=='"' ||*(input+i)=='\'' ))
                {
                  i++;
                  continue;
                }
                if((c=='"'||c=='\'')){
                        if((initialPointer!=specialCharStack) && c==*(specialCharStack-1)){
                                specialCharStack--;
                        }
                        else{
                                *specialCharStack=c;
                                specialCharStack++;
                        }
                }
                if(c=='|' || c=='&' || *(input+i+1)=='\n'){
			 						if(c=='&' && *(input+i+1)=='\n'){
                           commandInBackground=1;
                        }
                        else if(c=='&' && *(input+i+1)!='\n'){
                                continue;
                        }
                        else if(c!='&' && *(input+i+1)=='\n'){
                                i++;
                                thisCommandSize++;
				specialCharStack=initialPointer;
                        }
		 if(initialPointer==specialCharStack){
                                //pipes are outside special characters so a new command separated by pipe
                                char *command=(char*)_malloc(100*sizeof(char*));
                                commands[commandNumber]=command;
                                if(commandNumber!=0){
                                        thisCommandSize--;
                                }
                                int j=0;
                                for(;thisCommandSize>0;thisCommandSize--,j++){
					command[j]=*(input+i-thisCommandSize);
                                }
                                command[j]='\0';
                                commandNumber++;
                        }
                }
        }

    logIt("bifurcated commands are :\n");
	for(int i=0;i<commandNumber;i++){
        logIt(commands[i]);
        logIt("\n");
    }
    if(commandInBackground){
        if(_forkIt()==0){
            executeCommands(commands,commandNumber);
            logIt("running the child process\n");
            myExit(0);
        }
    }
    else{
        executeCommands(commands,commandNumber);
    }
    logIt("all the commands are executed \n");
}

int executeScript(char *commands){
	// logIt("In executeScript\n");
	char *command = commands;
	if(startsWith(trim(command),"sbush ")){
		char *argument=trim(replaceString(command,"sbush ",""));
		signed int pid;
		int status;
		if(fileExist(argument)){
			char *scriptContent = fileContent(argument,1000);
			// logIt("Script contents\n");
			// logIt(scriptContent);
			// logIt("\n");
			int splitCount;
			char **scriptCommands = split(scriptContent,"\n",&splitCount);
			logIt(scriptCommands[0]);
			logIt("\n");
			if(!isEqual(scriptCommands[0],"#!bin/sbush")){
				logIt("Not equal\n");
				return 0;
			}
			else{
				for(int i = 1; scriptCommands[i]; i++)
				{
					logIt(scriptCommands[i]);
					logIt("\n");
					char *commandToBeExecuted = concatenate(scriptCommands[i],"\n");
					pid = _forkIt();
					if(pid == 0){
						logIt("running the child process\n");
						parseAndExecute(commandToBeExecuted);
//						free(commandToBeExecuted);
						myExit(0);
					}
					else{
						logIt("Back to parent\n");
					        while(_wait(&status) != pid);	
					}
				}
			}
//			free(scriptCommands);
//			free(scriptContent);
		}
//		free(argument);
		return 1;
	}
	return 0;
}

#endif 
