// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    int addrlen = sizeof(serv_addr);
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr)); // to make sure the struct is empty. Essentially sets sin_zero as 0
                                                // which is meant to be, and rest is defined below

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address - listens from all interfaces.
    serv_addr.sin_port = htons(PORT);


    char *hello = "~[client] : Establishing connection";
    char *requestlist = "listall";
    char input[1024];    
    
    
    while (1) {
        memset(input, 0, sizeof(input));
        memset(buffer, 0, sizeof(buffer));


        scanf("%s", input);
        // printf("%s\n", input);
        sendto(sock, input, strlen(input), 0, (struct sockaddr*)&serv_addr,
                                                        sizeof(serv_addr));

        valread = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&serv_addr, 
                                                        &addrlen);

        printf("Received from server - \n%s\n", buffer);
    }

    return 0;
}
