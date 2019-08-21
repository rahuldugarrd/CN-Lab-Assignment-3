#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
const int MAX_SIZE = 1000000;

int main(int argc, char const *argv[]) {
    int fd;
    char data[MAX_SIZE]; 
    struct sockaddr_in ServAddr; 
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        fprintf(stderr, "Socket cannot be created"); 
        exit(1); 
    }
    memset(&ServAddr, 0, sizeof(ServAddr));  
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_port = htons(atoi(argv[2]));
    ServAddr.sin_addr.s_addr = inet_addr(argv[1]);
    char fileName[100];
    printf("Type the name of file to be transferred : \t");
    scanf("%s", fileName);
    FILE* f = fopen(fileName, "r");
    fgets(data, MAX_SIZE, f);
    sendto(fd, data, strlen(data), MSG_CONFIRM, (const struct sockaddr *) &ServAddr, sizeof(ServAddr));
    close(fd);
    fclose(f);
    return 0; 
}