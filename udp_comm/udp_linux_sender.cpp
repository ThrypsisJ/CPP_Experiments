#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        printf("Failed to create a socket!\n");
        return -1;
    }

    struct sockaddr_in self_addr;
    memset(&self_addr, 0, sizeof(self_addr));
    self_addr.sin_family = AF_INET;
    self_addr.sin_port = htons(4000);
    self_addr.sin_addr.s_addr = inet_addr("172.30.1.114");

    int result_bind = bind(sock, (struct sockaddr*)&self_addr, sizeof(self_addr));
    if (result_bind == -1) {
        printf("bind failed!\n");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4000);
    server_addr.sin_addr.s_addr = inet_addr("172.30.1.60");

    while(true) {
        char buff[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
        sendto(sock, buff, sizeof(buff), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
        usleep(500);
    }

    return 0;
}
