#include<winsock2.h>
#include<stdio.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验2 - 回射服务器
 * 数据报套接字 UDP
 *
 * clinet - 客户端
 * @author  h-j-13(140420227)
 * @time    2018年1月9日
 * */

#define PORT 6013
#define BUF 20

int main(void)
{
    WSADATA wsaData;
    SOCKET sockClient;                                                          //客户端Socket
    SOCKADDR_IN addrServer;                                                     //服务端地址
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //新建客户端socket
    sockClient = socket(AF_INET, SOCK_DGRAM, 0);

    //定义要连接的服务端地址
    addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");                   //目标IP(127.0.0.1是回送地址)
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);                                          //连接端口6000
    int len = sizeof(SOCKADDR);

    // 不使用connect()连接到服务端,即非连接方式
    char send_buf[BUF] = "";                                               //发送字符缓冲区
    char recv_buf[BUF] = "";                                               //接受字符缓冲区
    while (1)
    {
        printf("input>");
        scanf("%s", send_buf);
        sendto(sockClient, send_buf, BUF, 0, (SOCKADDR *) &addrServer, len);

        if (strcmp(send_buf, "q") == 0)
        {
            printf("退出客户端\n");
            break;
        }

        printf("recv echo>");
        recvfrom(sockClient, recv_buf, BUF, 0, (SOCKADDR *) &addrServer, &len);                    // 送出字符串 + "echo:"的长度
        printf("%s\n", recv_buf);
    }

    //关闭socket
    closesocket(sockClient);
    WSACleanup();

    return 0;
}