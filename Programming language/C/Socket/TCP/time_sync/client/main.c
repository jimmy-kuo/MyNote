#include<winsock2.h>
#include<stdio.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验1 - 时间同步服务器
 *
 * clinet - 客户端
 * @author  h-j-13(140420227)
 * @time    2017年12月24日
 * */

#define PORT 6013
#define SEND_CHAR_LENGTH 100

int main(void) {
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
    connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));

    //接受数据
    char message[SEND_CHAR_LENGTH] = "";
    recv(sockClient, message, SEND_CHAR_LENGTH, 0);
    printf("接收到服务器时间为 : %s",message);

    //关闭socket
    closesocket(sockClient);
    WSACleanup();

    return 0;
}