#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验1 - 回射服务器
 * a.recvline形式
 *
 * server - 服务器端
 * @author  h-j-13(140420227)
 * @time    2018年1月7日
 * */

#define PORT 6013
#define BUF 20
#define MAX_CONNECT_TIME 5

int main(void)
{
    // 初始化socket
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sockServer, sockClient;
    SOCKADDR_IN addrServer, addrClient;

    // 创建socket对象
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);            //INADDR_ANY表示任何IP
    addrServer.sin_family = AF_INET;                                //IPv4协议族
    addrServer.sin_port = htons(PORT);                              //绑定端口
    bind(sockServer, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));

    //Listen监听端
    listen(sockServer, 5);                                          //5为等待连接数目
    printf("服务器启动: 监听 %d 端口...\n", PORT);

    int len = sizeof(SOCKADDR);
    char send_buf[BUF] = "";                                        //发送字符缓冲区
    char recv_buf[BUF] = "";                                        //接受字符缓冲区
    int connect_cnt = MAX_CONNECT_TIME;

    // 循环接受客户端请求
    while (connect_cnt--)
    {
        sockClient = accept(sockServer, (SOCKADDR *) &addrClient, &len);
        printf("welcome %s \n", inet_ntoa(addrClient.sin_addr));

        while (1)
        {
            if(recv(sockClient, recv_buf, BUF, 0)==0)               // 客户端断开连接时断开链链接
                break;
            printf("recv>%s\n",recv_buf);
            sprintf(send_buf, "echo:%s", recv_buf);                 // 回射字符串
            send(sockClient, send_buf, BUF, 0);
        }
        shutdown(sockClient,SD_BOTH);
        closesocket(sockClient);
    }

    shutdown(sockClient, SD_SEND);
    closesocket(sockServer);
    WSACleanup();

    return 0;
}
