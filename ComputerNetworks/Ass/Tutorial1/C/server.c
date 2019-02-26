#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#define PORT 8080


void listFiles() {
    DIR *directory;
    struct dirent  *fname;
    if ((directory = opendir(".")) != NULL) {
        while ((fname = readdir(directory)) != NULL) {
            printf("%s\n", fname->d_name);
        }
    }
    else {
        perror("dirent");
    }
}


int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;  // sockaddr_in - references elements of the socket address. "in" for internet
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    char *hello = "~[server] : Connection established";
    char *lsfiles_msg = "~[server] : Received request to view files";
    char *lsfiles_ret = "~[server] : Files in directory";
    char *sendfile_msg = "~[server] : Received request to send file";
    char *sendfile_ret = "~[server] : Sending file";


    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0)  // creates socket, SOCK_STREAM is for TCP. SOCK_DGRAM for UDP
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // This is to lose the pesky "Address already in use" error message
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) // SOL_SOCKET is the socket layer itself
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;  // Address family. For IPv6, it's AF_INET6. 29 others exist like AF_UNIX etc.
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address - listens from all interfaces.
    address.sin_port = htons( PORT );    // Server port to open. Htons converts to Big Endian - Left to Right. RTL is Little Endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }


    while (1) {
        printf("Waiting for client requests\n");
        memset(buffer, 0, sizeof(buffer));
        valread = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&address, 
                                                        &addrlen);
        printf("%s\n", buffer);
        while (strcmp("listall",buffer) != 0) {
            listFiles();
            break;
        }                
    }




    // // Port bind is done. You want to wait for incoming connections and handle them in some way.
    // // The process is two step: first you listen(), then you accept()
    // if (listen(server_fd, 3) < 0) // 3 is the maximum size of queue - connections you haven't accepted
    // {
    //     perror("listen");
    //     exit(EXIT_FAILURE);
    // }

    // // returns a brand new socket file descriptor to use for this single accepted connection. Once done, use send and recv
    // if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
    //                    (socklen_t*)&addrlen))<0)
    // {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }
    // valread = read( new_socket , buffer, 1024);  // read infromation received into the buffer
    // printf("%s\n",buffer );
    // send(new_socket , hello , strlen(hello) , 0 );  // use sendto() and recvfrom() for DGRAM
    // printf("~[server] : Connection message sent\n");
    // memset(buffer, 0, sizeof(buffer));    

    // while (1) {
    //     valread = read( new_socket , buffer, 1024);  // read infromation received into the buffer
    //     // printf("%s\n",buffer );

    //     while (strcmp("listall",buffer) != 0) {
    //         printf("equal");
    //     }
    
    // }



    return 0;
}
