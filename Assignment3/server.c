// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
//#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    int port;
    char *file_name;
    int pfd;

    // read from the command line argument
    // first argument is the PORT
    // second argument is the file
    if (argc >=2){
         port = atoi(argv[1]);
         file_name = argv[2];
         #define PORT port
    }

    printf("Filename is %s \n", file_name);
    printf("Port is %d \n", PORT);
    // open the file ref: https://linux.die.net/man/3/open
    pfd = open(file_name, O_RDONLY);

    if (pfd < 0){
        perror("pfd error");
        exit(1);
    }
    printf("opened the pfd = % d\n", pfd);
    /* chroot*/
    /*
    chdir('/home/ec2-user');
    if (chroot("/home/ec2-user") != 0) {
         perror("chroot /home/ec2-user");
         return 1;
     }
   */
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int random = fork();
    printf("Random %d\n", random);
    if(random == 0){
            int length = snprintf( NULL, 0, "%d", new_socket );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", new_socket );


            int length_2 = snprintf( NULL, 0, "%d", pfd);
            char* str2 = malloc( length_2 + 1 );
            snprintf( str2, length_2 + 1, "%d", pfd );

            char *args[]={"./server2.out", str, str2, NULL};
            if(execvp(args[0], args) < 1) {
                perror("Error");
                exit(1);
            }
            free(str);
    }
    else {
        wait(random);
        if (close(pfd) < 0)
        {
            perror("pfd closing error");
            exit(1);
        }
        printf("closed the pfd.\n");
        printf("Done \n");
    }
    return 0;
}
