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
    struct sockaddr_in ServAddr, CliAddr;
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        fprintf(stderr, "Error creating Sockfd\n");
        exit(1);
    }
    memset(&ServAddr, 0, sizeof(ServAddr));
    memset(&CliAddr, 0, sizeof(CliAddr));
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServAddr.sin_port = htons(atoi(argv[1]));
    if (bind(fd, (const struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0) {
        fprintf(stderr, "Error while binding socket to port\n");
        exit(1);
    }
    int _;
    int n = recvfrom(fd, (char *)data, MAX_SIZE, MSG_WAITALL, ( struct sockaddr *) &CliAddr, &_);
    data[n] = '\0';
    FILE *f = fopen("client_file", "w");
    fputs(data, f);
    fclose(f);
    return 0;
}