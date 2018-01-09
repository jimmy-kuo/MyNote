#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验2 - 回射服务器
 * 数据报套接字 UDP
 *
 * server - 服务器端
 * @author  h-j-13(140420227)
 * @time    2018年1月9日
 * */

#define PORT 6013
#define BUF 20

int main(void)
{
    // 初始化socket
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sockServer;
    SOCKADDR_IN addrServer, addrClient;

    // 创建socket对象
    sockServer = socket(AF_INET, SOCK_DGRAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);            //INADDR_ANY表示任何IP
    addrServer.sin_family = AF_INET;                                //IPv4协议族
    addrServer.sin_port = htons(PORT);                              //绑定端口

    // bind (数据报套接字(UDP)不需要侦听端口 即listen()函数)
    bind(sockServer, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));

    //Listen监听端
    listen(sockServer, 5);                                          //5为等待连接数目
    printf("服务器启动: 监听 %d 端口...\n", PORT);

    int len = sizeof(SOCKADDR);
    char send_buf[BUF] = "";                                        //发送字符缓冲区
    char recv_buf[BUF] = "";                                        //接受字符缓冲区

    // 循环接受UDP客户端请求,并回射
    while (1)
    {
        // 使用recvfrom函数接受字符串
        //多了 int len, int flags) 来源IP＋来源端口号 和 来源长度
        recvfrom(sockServer, recv_buf, BUF, 0, (SOCKADDR *) &addrClient, &len);

        // 若接收到了q,则退出
        if (strcmp("q", recv_buf) == 0)
            break;

        printf("recv:%s\n",recv_buf);
        sprintf(send_buf, "echo:%s", recv_buf);
        //通过sockServer 向 addrClient 地址回射字符串
        sendto(sockServer, send_buf, strlen(send_buf) + 1, 0, (SOCKADDR *) &addrClient, len);


    }

    // 同样UDP不使用shutdown()来关闭连接
    closesocket(sockServer);
    WSACleanup();

    return 0;
}