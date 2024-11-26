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

int generaterandomnums(){
  int randomnum = open("/dev/random",O_RDONLY);
  if(randomnum==-1){
    err();
  }
  int toreturn;
  if(read(randomnum,&toreturn, sizeof(int))==-1){
  close(randomnum);
  err();
  }
  close(randomnum);
  return abs(toreturn)%5+1;
}

int main(){
  printf("%d about to create 2 child processes\n",getpid());
  pid_t p,p2;
  p = fork();
  if(p<0){
    perror("fork fail");
  exit(1);
  }
  if(p==0){
    int fortime = generaterandomnums();
    printf("%d %dsec\n",getpid(),fortime);
    sleep(fortime);
    printf("%d finished after %d seconds\n",getpid(),fortime);
    exit(fortime);
  }else{
   p2 = fork();
   if(p2<0){
    perror("fork fail");
  exit(1);
  }
  if(p2==0){
    int fortime = generaterandomnums();
    printf("%d %dsec\n",getpid(),fortime);
    sleep(fortime);
    printf("%d finished after %d seconds\n",getpid(),fortime);
    exit(fortime);
  }else{
    int status;
    pid_t childdone = wait(&status);
    if(childdone>0 && WIFEXITED(status)){
      int time = WEXITSTATUS(status);
      printf("Main Process %d is done. Child %d slept for %d sec\n",getpid(),childdone,time);
    }
  }

  return 0;
}}
