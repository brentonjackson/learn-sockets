/**
 * Program to make a TCP server
 * using a random OS-assigned port
 * 
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main()
{
    // 1. declare variables needed
    struct sockaddr_in my_addr;
    socklen_t len = sizeof(my_addr);
    int s;
    int rc;
    int s1;
    char buf[1];

    // 2. obtain socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed");
        return 1;
    }

    // 3. set server socket to listen for connections
    rc = listen(s, 5);
    if (rc)
    {
        perror("listen call failed");
        return 1;
    }
    printf("socket listening for connections...\n");

    // 4. assign random port and ip address to my_addr struct
    getsockname(s, (struct sockaddr *)&my_addr, &len);
    printf("port: %d\n", ntohs(my_addr.sin_port));
    // printf("ip address: %s\n", inet_ntoa(my_addr.sin_addr));

    // 5. accept incoming message and create new socket
    s1 = accept(s, NULL, NULL);
    if (s1 < 0)
    {
        perror("socket accept failure");
        return 1;
    }

    // 6. receive message from connected socket and print to stdout
    rc = recv(s1, buf, 1, 0);
    if (rc <= 0)
    {
        perror("no message recieved");
        return 1;
    }
    printf("message from client: \n");
    printf("%c\n", buf[0]);

    // 7. send message to client
    rc = send(s1, "2", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed");
    }
    printf("sending message back to client...\n");
    return 0;
}