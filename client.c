#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{

    //创建一个通信的套接字，需要指定服务器的IP和端口号y
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd != -1);

    struct sockaddr_in ser_addr;
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(6000);//转化端口号
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//回环地址


//连接服务器，需要知道服务器绑定的IP和端口
    int res = connect(sockfd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    assert(res != -1);

    //通信
    while (1)
    {

        printf("input: ");
        char buff[128] = { 0 };
        fgets(buff, 127, stdin);
        if (strncmp(buff, "end", 3) == 0)
        {
            break;
        }

        send(sockfd, buff, strlen(buff) - 1, 0);//\n不发

        memset(buff, 0, 128);
        recv(sockfd, buff, 127, 0);
        printf("%s\n", buff);
    }

    //断开连接
    close(sockfd);

    return 0;
}
