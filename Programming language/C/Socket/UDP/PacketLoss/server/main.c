#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验2 - 丢包率计算
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
    printf("服务器启动: 监听 %d 端口...\n", PORT);

    int len = sizeof(SOCKADDR);
    char send_buf[BUF] = "";                                        //发送字符缓冲区
    char recv_buf[BUF] = "";                                        //接受字符缓冲区

    // 协商双方通信次数
    int number = 0, n = 0;
    int packet_recv = 0;
    int r = recvfrom(sockServer, recv_buf, BUF, 0, (SOCKADDR *) &addrClient, &len);
    if (r > 0)
    {
        n = number = atoi(recv_buf);
        printf("双方协商发送%d个数据包\n", number);
    } else if (r == SOCKET_ERROR)
    {
        closesocket(sockServer);
        WSACleanup();
    }
    while (n--)
    {
        r = recvfrom(sockServer, recv_buf, BUF, 0, (SOCKADDR *) &addrClient, &len);
        if (r > 0)
            packet_recv++;
        else
            printf("!丢失了第%d个包\n", n);
        Sleep(50);                                  // 阻塞50ms,模拟服务器繁忙效果
    }

    printf("Packet Total:%d (recv %d / lost %d) - %f", number, packet_recv, (number - packet_recv),
           (float) (number - packet_recv) / number);

    // 同样UDP不使用shutdown()来关闭连接
    closesocket(sockServer);
    WSACleanup();

    return 0;
}