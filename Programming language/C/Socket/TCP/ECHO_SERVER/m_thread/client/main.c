#include<winsock2.h>
#include<stdio.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验1 - 回射服务器
 * d.多线程形式
 *
 * clinet - 客户端
 * @author  h-j-13(140420227)
 * @time    2018年1月7日
 * */

#define PORT 6013
#define BUF 100


int main(void)
{
    WSADATA wsaData;
    SOCKET sockClient;                                                          //客户端Socket
    SOCKADDR_IN addrServer;                                                     //服务端地址
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //新建客户端socket
    sockClient = socket(AF_INET, SOCK_STREAM, 0);

    //定义要连接的服务端地址
    addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");                   //目标IP(127.0.0.1是回送地址)
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);                                          //连接端口6000

    //连接到服务端
    if (connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR)) != 0)
    {
        printf("链接回射服务器失败\n");
        closesocket(sockClient);
        WSACleanup();
        return 0;
    };

    char send_buf[BUF] = "";                                               //发送字符缓冲区
    char recv_buf[BUF] = "";                                               //接受字符缓冲区
    while (1)
    {
        printf("input>");
        scanf("%s", send_buf);
        if (strcmp(send_buf, "q") == 0)
        {
            printf("退出客户端\n");
            break;
        }

        send(sockClient, send_buf, strlen(send_buf) + 1, 0);
        printf("recv echo>");                                  // 回射的长度总是定值
        recv(sockClient, recv_buf, BUF, 0);                    // 送出字符串 + "echo:"的长度
        printf("%s\n", recv_buf);
    }

    //关闭socket
    shutdown(sockClient, SD_BOTH);
    closesocket(sockClient);
    WSACleanup();

    return 0;
}
