#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>
#define PORT 8080

// Function to get list of files from directory
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
}


// Function to compare two strings within length len
int compstr(char *one, char *two, int len) {
    if (strlen(two) < len || strlen(one) < len)
        return 0;

    for (int i = 0; i < len; i++) {
        if (one[i] != two[i])
            return 0;
    }
    return 1;
}





int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;  // sockaddr_in - references elements of the socket address. "in" for internet
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    char *lsfiles_msg = "~[server] : Received request to view files";
    char *sendfile_msg = "~[server] : Received request to send file";
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


    // Now we listen and send datagrams as needed, because UDP
    while (1) {
        // Clearing the buffer before use
        memset(buffer, 0, sizeof(buffer));
        
        printf("\n\nWaiting for client requests\n");
        
        // Reception from client
        valread = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr *)&address, &addrlen);
        printf("~[server] : Received from client - %s\n", buffer);
        


        // Checking received string among options
        if (compstr(buffer, "listall", strlen(buffer))) {
            printf("listall command detected\n");
            sendto(server_fd, filelist, strlen(filelist), 0, (struct sockaddr*)&address, sizeof(address));
        }
        else if (compstr(buffer, "send", 4)) {
            printf("Detected send message\n");
            sendto(server_fd, lsfiles_msg, strlen(lsfiles_msg), 0, (struct sockaddr*)&address, sizeof(address));
        }
        else { // Assume filename

            // Getting the filename turned out to be very hacky
            char *filname = (char*)malloc(1024 * sizeof(char));
            filname[0] = '.';
            filname[1] = '/';
            for (int i = 0; i < strlen(buffer); i++) {
                filname[i+2] = buffer[i];
            }
            // strcat("server");
        
    
            printf("trying to open file %s\n", filname);
            if ((filepointer = fopen(filname, "r")) == NULL) {
                perror("fopen");
                sendto(server_fd, inv, strlen(inv), 0, (struct sockaddr*)&address, sizeof(address));
            }
            else {
                memset(buffer, 0, sizeof(buffer));
                
                // Reading from file
                char c;
                int i = 0;
                while (1) {
                    c = fgetc(filepointer);
                    buffer[i++] = c;
                    if (c == EOF)
                        break;
                }

                printf("Sending client data %s\n", buffer);
                sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr*)&address,
                                                            sizeof(address));

                fclose(filepointer);
            }

            
        }

    }

    return 0;
}
