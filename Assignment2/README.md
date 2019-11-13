## Assignment 2
Starting with assignment 1 as a starting point, add in code to re-exec the server’s child process after forking. You will need to determine how to pass the socket file descriptor between the forked child and the new exec’ed child, so that the new exec’ed child can process the incoming child request.

## Steps for execution
```JSON
gcc -Wall server.c -o server.out
gcc -Wall server2.c -o server2.out
gcc -Wall client.c -o client.out
```

## run
```JSON
 ./server.out
 ./client.out
 ```
