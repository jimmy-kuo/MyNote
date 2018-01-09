#include<winsock2.h>
#include<stdio.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验2 - 丢包率计算
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
    char send_buf[BUF] = "test_data";                                                    //发送字符缓冲区
    char recv_buf[BUF] = "";                                                    //接受字符缓冲区

    char num[4];
    int number, count = 1;
    printf("通信双方协商报文个数>\n");
    scanf("%s", num);                                                           //发送本次测试发包个数

    sendto(sockClient, num, sizeof(num), 0, (sockaddr *) &addrServer, len);
    number = atoi(num);
    getchar();
    printf("本次测试数目以协商完成,按任意键开始发送...");
    getchar();
    while (number--)
    {
        printf("发送第%d个数据包\n", count);
        sendto(sockClient, send_buf, strlen(send_buf) + 1, 0, (sockaddr *) &addrServer, len);
        count++;

    }
    printf("发包完成，退出\n");

    //关闭socket
    closesocket(sockClient);
    WSACleanup();

    return 0;
}