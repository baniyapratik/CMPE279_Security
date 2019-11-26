
Note: For the assignment i have attempted to apply seccomp in the client.c module to harden security capability. 


Questions:
1. Which capabilities API (seccomp-bpf, AppArmor, or SELinux) did you choose? Why did you make that choice?  
```JSON
Ans: I decided to choose seccomp-bpf. The reason i decided to choose seccomp-bpf vs selinux or AppArmor is because of developers flexibility to apply capabilities programability vs
depency on profiles and policies on the server/system itself.
```

2. What was the process you used to ascertain the list of system calls required by each program?
```JSON
sudo strace ./client.out 
```
3. What system calls are needed by each?
```JSON
execve("./client.out", ["./client.out"], 0x7ffcf342ce40 /* 14 vars */) = 0
brk(NULL)                               = 0x564aa2367000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=26522, ...}) = 0
mmap(NULL, 26522, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f9c38e1e000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libseccomp.so.2", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\200%\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=288976, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9c38e1c000
mmap(NULL, 2384112, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9c389b7000
mprotect(0x7f9c389e6000, 2097152, PROT_NONE) = 0
mmap(0x7f9c38be6000, 98304, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2f000) = 0x7f9c38be6000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\260\34\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030544, ...}) = 0
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f9c385c6000
mprotect(0x7f9c387ad000, 2097152, PROT_NONE) = 0
mmap(0x7f9c389ad000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f9c389ad000
mmap(0x7f9c389b3000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f9c389b3000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f9c38e19000
arch_prctl(ARCH_SET_FS, 0x7f9c38e19740) = 0
mprotect(0x7f9c389ad000, 16384, PROT_READ) = 0
mprotect(0x7f9c38be6000, 94208, PROT_READ) = 0
mprotect(0x564aa0564000, 4096, PROT_READ) = 0
mprotect(0x7f9c38e25000, 4096, PROT_READ) = 0
munmap(0x7f9c38e1e000, 26522)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
brk(NULL)                               = 0x564aa2367000
brk(0x564aa2388000)                     = 0x564aa2388000
write(1, "1. Init filter\n", 151. Init filter
)        = 15
prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)  = 0
seccomp(SECCOMP_SET_MODE_STRICT, 1, NULL) = -1 EINVAL (Invalid argument)
seccomp(SECCOMP_SET_MODE_FILTER, 0, {len=21, filter=0x564aa236b290}) = 0
write(1, "2. Trying to exec client\n", 252. Trying to exec client
) = 25
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
connect(3, {sa_family=AF_INET, sin_port=htons(8080), sin_addr=inet_addr("127.0.0.1")}, 16) = 0
write(1, "Preparing to send message\n", 26Preparing to send message
) = 26
sendto(3, "Hello from client", 17, 0, NULL, 0) = 17
write(1, "Hello message sent\n", 19Hello message sent
)    = 19
read(3, "Hello from server", 1024)      = 17
write(1, "Hello from server\n", 18Hello from server
)     = 18
exit_group(0)                           = ?
+++ exited with 0 +++
```
4. What happens when your application calls the prohibited system call? What is the application 
behaviour that results from the call?  

```JSON
Ans: As the program is built with "-lseccomp" flag and initialized with seccomp when the application calls 
the prohibited system call it kills the process. Below is the behavior observed from the call.

1. Init filter
2. Trying to exec client
Preparing to send message
Bad system call (core dumped)
```
