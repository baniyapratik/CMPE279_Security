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
  printf("socket %d", new_socket);
  char buffer[1024] = {0};
  char *hello = "Hello from server";
  int valread;

  valread = read(new_socket , buffer, 1024);
  printf("%s\n",buffer );
  send(new_socket , hello , strlen(hello) , 0 ); 
  printf("Hello message sent\n"); 
}
