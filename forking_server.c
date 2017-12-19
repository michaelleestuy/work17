#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client, int);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("HOLA");
    exit(0);
  }
}

int main() {
  int from_client;
  int to_client;
  while(1){
    from_client = server_setup();
    printf("server forking\n");
    if(!fork()){
      to_client = server_connect(from_client);
      subserver(from_client, to_client);
      
    }else{
      remove("HOLA");
      close(from_client);
    }
  }
  
  
}

void subserver(int from_client, int to_client) {
  char red[100];

  while(read(from_client, red, 100)){
    process(red);
    write(to_client, red, 100);
  }

  
}

void process(char * s) {
  s[0] = '!';
  
}
