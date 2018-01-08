#include<stdlib.h>
//#include<system.h>

int myExit(int n);
void _start(void) {
  int res = main(0,NULL,NULL);
  
  myExit(res); // call main() and exit() here
}
