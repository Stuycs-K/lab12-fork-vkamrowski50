#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

int main(){
  pid_t p,p2;
  p = fork();
  if(p<0){
    err();
  }
  else if(p!=0){
    printf("hi parent\n");
    p2 = fork();
  }
  if(p==0 || p2==0){
    printf("hi child\n");
  }

  return 0;
}
