/**
 * Program to make a simple TCP client
 * 
 * 
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(void)
{
    // 1. declare variables needed
    struct sockaddr_in peer;
    int s;
    int rc; // holder for values after socket and connect calls
    char buf[1];

    // 2. setup peer address (localhost)
    peer.sin_family = AF_INET;
    peer.sin_port = htons(7500);
    peer.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. obtain socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed");
        return 1;
    }

    // 4. make connection to peer
    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    if (rc)
    {
        perror("connect call failed");
        return 1;
    }

    // 5. send data from socket to the server
    printf("sending message to server...\n");
    rc = send(s, "1", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed");
        return 1;
    }

    // 6. recieve data from socket into buffer and write it to stdout
    rc = recv(s, buf, 1, 0);
    if (rc <= 0)
    {
        perror("receive call failed");
    }
    else
    {
        printf("message from server: \n");
        printf("%c\n", buf[0]);
    }
    return 0;
}