#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验1 - 回射服务器
 * c.recvvl 形式
 *
 * server - 服务器端
 * @author  h-j-13(140420227)
 * @time    2018年1月7日
 * */

#define PORT 6013
#define BUF 100
#define MAX_CONNECT_TIME 5

int recvn(SOCKET s, char *recvbuf, unsigned int fixedlen)
{/** socket接受定长字符串 */
    int iResult;                                            //存储单次recv操作的返回值
    int cnt;                                                //用于统计相对于固定长度，剩余多少字节尚未接收
    cnt = fixedlen;
    char *pp = recvbuf;
    while (cnt > 0)
    {
        iResult = recv(s, pp, 5, 0);
        if (iResult < 0)
        {//数据接收出现错误，返回失败
            printf("接收发生错误: %d\n", WSAGetLastError());
            return -1;
        }
        if (iResult == 0)
        {//对方关闭连接，返回已接收到的小于fixedlen的字节数
            printf("连接关闭\n");
            return fixedlen - cnt;
        }
        //printf("接收到的字节数: %d\n", iResult);
        pp += iResult;                                              //接收缓存指针向后移动
        cnt -= iResult;                                             //更新cnt值

    }

    return cnt;
}

int recvvl(SOCKET s, char *recvbuf, unsigned int recvbuflen)
{/** 接受变长字符串 */
    int iResult;
    char length[sizeof(unsigned int) + 1];
    unsigned int reclen;

    //接收到消息长度
    iResult = recv(s, length, 4, 0);
    printf("变长消息长度:%s\n", length);
    reclen = atoi(length);                                          //将字符串变为整数

    printf("循环接收长度%d\n", reclen);
    printf("缓冲区空间长度%d\n", recvbuflen);
    // 为了可读性,简化了部分错误检错
    return recv(s, recvbuf, reclen + 1, 0);
}


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
            if (recvvl(sockClient, recv_buf, BUF) == 0)               // 客户端断开连接时断开链链接
                break;
            printf("recv>%s\n", recv_buf);
            sprintf(send_buf, "echo:%s", recv_buf);                 // 回射字符串
            send(sockClient, send_buf, BUF, 0);
        }
        shutdown(sockClient, SD_BOTH);
        closesocket(sockClient);
    }

    shutdown(sockClient, SD_SEND);
    closesocket(sockServer);
    WSACleanup();

    return 0;
}
