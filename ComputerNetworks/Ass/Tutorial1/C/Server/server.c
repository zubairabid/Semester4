#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#define PORT 8080


void listFiles(char **flist) {
    // char *flist;
    DIR *directory;
    struct dirent  *fname;
    if ((directory = opendir(".")) != NULL) {
        while ((fname = readdir(directory)) != NULL) {
            printf("%s\n", fname->d_name);
            strcat(*flist, fname->d_name);
            strcat(*flist, "\n");
        }
    }
    else {
        perror("dirent");
    }
    // printf("%s", flist);
    // return flist;
}

int compstr(char *one, char *two, int len) {
    if (strlen(two) < len || strlen(one) < len)
        return 0;

    for (int i = 0; i < len; i++) {
        if (one[i] != two[i])
            return 0;
    }
    return 1;
}

int sendfile(FILE* filepointer, char *buffer) {
    for (int i = 0; i <  1024; i++) {
        buffer[i] = fgetc(filepointer);
        if (buffer[i] == EOF)
            return 1;
    }
    return 0;
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
    char *inv = "invalid";

    FILE* filepointer;


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


    char *filelist = malloc(sizeof(char)*1024);
    listFiles(&filelist);
    // printf("THIS IS NEW %s\n", filelist);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        
        printf("\n\nWaiting for client requests\n");
        
        valread = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&address, 
                                                        &addrlen);
        printf("~[server] : Received from client - %s\n", buffer);
        
        if (compstr(buffer, "listall", strlen(buffer))) {
            printf("listall command detected\n");
            sendto(server_fd, filelist, strlen(filelist), 0, (struct sockaddr*)&address,
                                                        sizeof(address));
            // break;
        }
        else if (compstr(buffer, "send", 4)) {
            printf("Detected send message\n");
            sendto(server_fd, lsfiles_msg, strlen(lsfiles_msg), 0, (struct sockaddr*)&address,
                                                            sizeof(address));
        }
        else { // Assume filename
            char *filname = "./server";
            // strcat("server");
            printf("trying to open file %s\n", filname);
            if ((filepointer = fopen(filname, "r")) == NULL) {
                perror("fopen");

                sendto(server_fd, inv, strlen(inv), 0, (struct sockaddr*)&address,
                                                            sizeof(address));
            }
            else {
                memset(buffer, 0, sizeof(buffer));
                // while (valread = fread())
                sendfile(filepointer, buffer);
                printf("GOT SOME %s\n", buffer);
                sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&address,
                                                            sizeof(address));
            }

            
        }

    }

    return 0;
}
