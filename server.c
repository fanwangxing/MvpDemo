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
    //创建用于监听的套接字，这个套接字是一个文件描述符，用于检测有没有客户端发起一个新的连接
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd != -1);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6000);//转化端口号

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
// 将得到的监听的文件描述符和本地的IP端口进行绑定
    int res = bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    assert(res != -1);

    //设置监听（成功之后开始监听，监听的是客户端的连接）
    res = listen(listenfd, 5);
    assert(res != -1);

    //通信
    while (1)
    {
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        int c = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_len);
        if (c == -1)
        {
            printf("Get One Client Link Error\n");
            continue;
        }

        while (1)
        {
            char buff[128] = { 0 };
            int n = recv(c, buff, 127, 0);//读取数据放在buff中，一次读取127个
            if (n <= 0)
            {
                printf("Client will unlink\n");
                break;
            }
            printf("%d : %s\n", c, buff);
            send(c, "OK", 2, 0);
        }
        close(c);
    }

    //断开连接，关闭套接字（四次挥手）
    close(listenfd);


    return 0;
}
