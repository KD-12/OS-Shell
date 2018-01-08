#include "write.h"
#ifndef LOG_H
#define LOG_H

#define LOG 0 

void logIt(char * toLog){
	if(LOG){
			putOnFd(toLog,1);
	}
}

#endif 
