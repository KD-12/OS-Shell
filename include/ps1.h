#include "string.h"
#include "executer.h"


#ifndef PS1_H
#define PS1_H

char *hostName;
char *hostNameFull;
char *userName;
extern char* pwd;
char *PS1="\\u@\\h:\\w :sbush>";
//char *shellName;
char *version="1.0";
char *versionAndPatch="1.0.0";
//char *homeDirectory;

char  *concatenate(char *,char *);
int indexOfString(char *,char *);
char *replaceString(char *,char *,char *);
void logIt(char *);

void initializePS1(){
    userName=executeAndReturn("whoami",50);
    hostNameFull=executeAndReturn("hostname",50);
  //  homeDirectory=executeAndReturn("echo  ~",50);
    int splittedHostNameCount;
    char **splittedHostName=split(hostNameFull,".",&splittedHostNameCount);
    hostName=splittedHostName[0];
    //shellName=executeAndReturn("echo $0",50);
}

char *replacePlaceHolders(char *ps1,char *placeholder, char *value){
        while(1){
        if(indexOfString(ps1,placeholder)==-1)
        {
                return ps1;
        }
        char *newPs1=replaceString(ps1,placeholder,value);
//        free(ps1);
        ps1=newPs1;
        }
}

char *getPrompt(){
	char *tempPs1=concatenate(PS1,"");
	logIt("getting the variable values\n");
//	char* dateBasic=executeAndReturn("date +\"%a %b %d\"",50);
	char* time24H=executeAndReturn("date +\"%H:%M:%S\"",50);
	char* time12H=executeAndReturn("date +\"%I:%M:%S\"",50);
//	char* timeAMPM=executeAndReturn("date +\"%I:%M:%S %p\"",50);
	char *directoryPrompt;

//	if(indexOfString(pwd,homeDirectory)==0){
//		directoryPrompt=replaceString(pwd,homeDirectory,"~");
//	}
//	else{
		directoryPrompt=concatenate(pwd,"");
//	}
	int splittedCount=0;
	char **splittedFolder=split(pwd,"/",&splittedCount);
	
	char *presentFolder = 0;
	for(int i=0;i<splittedCount;i++)
	{
		presentFolder=splittedFolder[i];
	}

    logIt("putting the variables\n");
  //  tempPs1=replacePlaceHolders(tempPs1,"\\d",dateBasic);
	tempPs1=replacePlaceHolders(tempPs1,"\\h",hostName);
	tempPs1=replacePlaceHolders(tempPs1,"\\H",hostNameFull);
//	tempPs1=replacePlaceHolders(tempPs1,"\\s",shellName);
	tempPs1=replacePlaceHolders(tempPs1,"\\t",time24H);
	tempPs1=replacePlaceHolders(tempPs1,"\\T",time12H);
//	tempPs1=replacePlaceHolders(tempPs1,"\\@",timeAMPM);
	tempPs1=replacePlaceHolders(tempPs1,"\\u",userName);
	tempPs1=replacePlaceHolders(tempPs1,"\\v",version);
	tempPs1=replacePlaceHolders(tempPs1,"\\V",versionAndPatch);
	tempPs1=replacePlaceHolders(tempPs1,"\\w",directoryPrompt);
	tempPs1=replacePlaceHolders(tempPs1,"\\W",presentFolder);

	//logIt("freeing up memory\n");
	//free(dateBasic);
	//free(time24H);
	//free(time12H);
	//free(timeAMPM);
	//free(splittedFolder);
	//free(presentFolder);
	//free(directoryPrompt);
	//logIt("freed up memory\n");

	return tempPs1;
}

#endif 

