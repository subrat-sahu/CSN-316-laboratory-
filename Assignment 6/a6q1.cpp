#include <sys/socket.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
    int sockfd, sendbuff, recvbuff;
    socklen_t optlen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        printf("Error");

    int res = 0, buff = 0;

    // Get buffer size
    optlen = sizeof(sendbuff);
    res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);
    buff = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);

    if(res == -1 || buff == -1)
        printf("Error getsockopt one");
    else {
        printf("send buffer size = %d\n", sendbuff);
        printf("recieve buffer size = %d\n", recvbuff);
    }

    // Set buffer size
    sendbuff = 98304;
    recvbuff = 44444;

    printf("sets the send buffer to %d\n", sendbuff);

    cout << "Enter new size of send buffer: ";
    cin >> sendbuff;
    cout << "Enter new size of recieve buffer: ";
    cin >> recvbuff;

    cout << endl;

    printf("sets the recieve buffer to %d\n", recvbuff);

    res = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, sizeof(sendbuff));
    buff = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, sizeof(sendbuff));

    if(res == -1 || buff == -1)
        printf("Error setsockopt");


    // Get buffer size
    optlen = sizeof(sendbuff);
    res = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuff, &optlen);
    buff = getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuff, &optlen);


    if(res == -1 || buff == -1)
        printf("Error getsockopt one");
    else {
        printf("send buffer size = %d\n", sendbuff);
        printf("recieve buffer size = %d\n", recvbuff);
    }

    return 0;
}
