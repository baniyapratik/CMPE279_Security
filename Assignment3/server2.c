#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
int main(int argc, char *argv[])
{

  printf("Here\n");
  int new_socket = atoi(argv[1]);
  printf("%s",argv[2] );
  int pfd = atoi(argv[2]);
  char buffer[1024] = {0};
  char c[1024] = {0};
  printf("Here");
  chdir('/tmp');
  if (chroot("/tmp") != 0) {
         perror("chroot /tmp");
         return 1;
  }

  int sz = read(pfd, c, 1024);
  c[sz] = '\0';
  printf("Those bytes are as follows: % s\n", c);

  //char *hello = "Hello from server";
  int valread;

  valread = read(new_socket , buffer, 1024);
  printf("buffer is %s\n",buffer );
  send(new_socket , c , strlen(c) , 0 );
  printf("message sent from server\n");
}
