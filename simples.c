/**
 * Program to make a simple TCP server
 * 
 * 
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
// #include <arpa/inet.h>
#include <stdio.h>

int main()
{
    // 1. declare variables needed
    struct sockaddr_in local;
    int s;
    int rc;
    int s1;
    char buf[1];

    // 2. setup local address parameters
    local.sin_family = AF_INET;
    local.sin_port = htons(7500);
    local.sin_addr.s_addr = htonl(INADDR_ANY);

    // 3. obtain socket
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket call failed");
        return 1;
    }

    printf("obtained socket...\n");

    // 4. bind socket to local interface address
    rc = bind(s, (const struct sockaddr *)&local, sizeof(local));
    if (rc < 0)
    {
        perror("bind call failed");
        return 1;
    }

    // 5. set server socket to listen for connections
    rc = listen(s, 5);
    if (rc)
    {
        perror("listen call failed");
        return 1;
    }
    printf("socket listening for connections...\n");

    // 6. accept incoming message and create new socket
    s1 = accept(s, NULL, NULL);
    if (s1 < 0)
    {
        perror("socket accept failure");
        return 1;
    }
    printf("connection established to client...\n");

    // 7. receive message from connected socket and print to stdout
    rc = recv(s1, buf, 1, 0);
    if (rc <= 0)
    {
        perror("no message recieved");
        return 1;
    }
    printf("message from client: \n");
    printf("%c\n", buf[0]);

    // 8. send message to client
    rc = send(s1, "2", 1, 0);
    if (rc <= 0)
    {
        perror("send call failed");
    }
    printf("sending message back to client...\n");
    return 0;
}