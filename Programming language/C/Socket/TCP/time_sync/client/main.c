#include<winsock2.h>
#include<stdio.h>
#include<string.h>

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
#define RECV_CHAR 10

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
    if (connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR)) != 0) {
        printf("链接时间同步服务器失败\n");
        closesocket(sockClient);
        WSACleanup();
        return 0;
    };

    //使用 recv() 函数循环接受数据
    int recv_result = RECV_CHAR;
    char message[RECV_CHAR + 1] = "";
    char result[RECV_CHAR * 100] = "";                                          // 一个足够大的结果字符串数组
    while (recv_result > 0) {
        // 循环接受数据
        recv_result = recv(sockClient, message, RECV_CHAR, 0);
        if (recv_result == 0) {
            printf("服务器关闭了链接\n");
            shutdown(sockClient, SD_RECEIVE);
        } else if (recv_result == SOCKET_ERROR) {
            printf("接收数据过程发生了错误:%d", WSAGetLastError());
            closesocket(sockClient);
            WSACleanup();
        } else if (recv_result > 0) {
            printf("接收到了%d个字节:", recv_result);
            printf("%s\n", message);
            strcat(result, message);
        }

    }

    printf("接收到服务器时间为:%s", result);

    //关闭socket
    closesocket(sockClient);
    WSACleanup();

    return 0;
}