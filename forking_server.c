#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("HOLA");
    exit(0);
  }
}

int main() {
  signal(SIGINT,sighandler);
  
  int from_client;
  int to_client;
  while(1){
    from_client = server_setup();
    printf("server forking\n");
    if(!fork()){
      //to_client = server_connect(from_client);
      subserver(from_client);
      
    }else{
      remove("HOLA");
      close(from_client);
    }
  }
  
  
}

void subserver(int from_client) {
  int to_client=server_connect(from_client);
  //int to_client;
  char buffer[BUFFER_SIZE];
  //int i=0;
  /*while (i<100) {
    red[i]=0;
    i++;
    }*/

  while(read(from_client,buffer,BUFFER_SIZE)){
    printf("subserver %d: received [%s]\n",getpid(),buffer);
    process(buffer);
    write(to_client, buffer, sizeof(buffer));
  }

  
}

void process(char * s) {
  int i=0;
  while (s[i]) {

    if ( (s[i]>='a' && s[i]<='m') || (s[i]>='A' && s[i]<='M'))
      s[i]+=13;
    else if ( (s[i]>='n' && s[i]<='z') || (s[i]>='N'&&s[i]<='Z'))
      s[i]-=13;
    i++;

  }
}
