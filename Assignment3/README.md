1.What happens if the file being requested is not inside the chroot? Does it matter?
Answer: It doesn’t matter as the file is read before chroot and the file descriptor is passed. We are able to read the file and send it via the socket.

2.Explain the mechanism you are using to pass file descriptors between parent and child processes.
Ans: Im using open(), It returns a file descriptor for the named file that is the lowest file descriptor not currently open for that process.

It is passed to the child process as a param using execvp.
Ref: https://linux.die.net/man/3/open

3.  What happens if the file size of the disk file exceeds the size of the client’s hardcoded buffer?  
    Does the client have sufficient checks to ensure no buffer overruns occur?
    Answer: Only the buffer size is read from the file, which in our case is 1024 characters. So, even if the file has 2000 characters only 1024 would be read and is sent to the client. The client is not doing additional checks and is simply doing a read into the buffer.

## Execution

```JSON
Server:
gcc -Wall server2.c -o server2.out
gcc -Wall server.c -o server.out
 ./server.out 8080 /home/ec2-user/test.txt

/home/ec2-user/test.txt: could be any text file

client:
gcc -Wall client.c -o client.out
```
