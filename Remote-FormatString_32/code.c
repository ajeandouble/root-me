#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_PORT 56033
#define LENGTH 1024

/*
gcc -m32 -o ch32 ch32.c -z execstack
*/

extern char **environ;
int ssock;



int recv_loop(void)
{

  int csock;
  struct sockaddr_in caddr;
  socklen_t clen = sizeof(caddr);
  char input[LENGTH];
  char output[LENGTH];

  printf("RECV_LOOP");
  while(1)
  {
    if( (csock = accept(ssock, (struct sockaddr *) &caddr, &clen)) < 0) {
      perror("accept()");
      exit(1);
    } else { printf("QQQ"); }
    memset(input, '\0', LENGTH);
    memset(output, '\0', LENGTH);

    recv(csock, input, LENGTH-1, 0);
    snprintf (output, sizeof (output), input);
    output[sizeof (output) - 1] = '\0';
    send(csock, output, LENGTH-1, 0);
    close(csock);
  }

  return 0;
}

int main(void)
{
  int i, pid, yes = 1;
  struct sockaddr_in saddr;

  for(i=0; environ[i] != NULL; i++) {
    memset(environ[i], '\0', strlen(environ[i]));
"ch32.c" 106L, 2050C                                                                                1,1           Top
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_PORT 56033
#define LENGTH 1024

/*
gcc -m32 -o ch32 ch32.c -z execstack
*/

extern char **environ;
int ssock;



int recv_loop(void)
{

  int csock;
  struct sockaddr_in caddr;
  socklen_t clen = sizeof(caddr);
  char input[LENGTH];
  char output[LENGTH];

  printf("RECV_LOOP");
  while(1)
  {
    if( (csock = accept(ssock, (struct sockaddr *) &caddr, &clen)) < 0) {
      perror("accept()");
      exit(1);
    } else { printf("QQQ"); }
    memset(input, '\0', LENGTH);
    memset(output, '\0', LENGTH);

    recv(csock, input, LENGTH-1, 0);
    snprintf (output, sizeof (output), input);
    output[sizeof (output) - 1] = '\0';
    send(csock, output, LENGTH-1, 0);
    close(csock);
  }

  return 0;
}

int main(void)
{
  int i, pid, yes = 1;
  struct sockaddr_in saddr;

  for(i=0; environ[i] != NULL; i++) {
    memset(environ[i], '\0', strlen(environ[i]));
  }

  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons(LISTEN_PORT);

  while(1)
  {
    pid = fork();
    if( pid == 0 ) {

      printf("run (pid=%d)\n", getpid());
      printf("run (pid=%d)\n", getpid());
            if( (ssock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
      printf("run (pid=%d)\n", getpid());
        perror("socket()");
        exit(1);
      }

      printf("))");
      if(setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) <0) {
         perror("setsockopt()");
         exit(1);
      }

      printf("))");
      if( bind(ssock, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) {
        perror("bind()");
        exit(1);
      }

      printf("))");
      if( listen(ssock, 5) < 0) {
        perror("listen()");
        exit(1);
      }

      printf("))");
      recv_loop();
    } else {
       printf("else");
       wait(NULL);
       close(ssock);
    }
  }

  return 0;
}