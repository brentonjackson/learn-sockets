/**
 * Program to make a TCP client
 * that connects to the port
 * specified by a command line argument
 * 
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // 1. declare variables needed
    struct sockaddr_in peer;
    int s;
    int rc; // holder for values after socket and connect calls
    char buf[1];

    // 2. setup server address (localhost)
    peer.sin_family = AF_INET;
    int port = atoi(argv[1]);                      // ascii to int conversion
    peer.sin_port = htons(port);                   // short int from host to network byte order
    inet_pton(AF_INET, "0.0.0.0", &peer.sin_addr); // listen on every network interface

    // 3. obtain socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed");
        return 1;
    }

    // 4. make connection to server
    rc = connect(s, (struct sockaddr *)&peer, sizeof(peer));
    if (rc)
    {
        perror("connect call failed");
        return 1;
    }

    // 5. send data from socket to the server
    rc = send(s, "1", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed");
        return 1;
    }
    printf("sending message to server...\n");

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