#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

// note
// 请在编译时添加额外参数 -lwsock32 (gcc)

/**
 * 哈尔滨工业大学(威海) 计算机网络 II
 * 实验1 - 时间同步服务器
 *
 * server - 服务器端
 * @author  h-j-13(140420227)
 * @time    2017年12月24日
 * */

#define PORT 6013

int get_local_time_str(char *time_str)
{/** 获取本地时间字符串*/
    // 清空原始内容
    memset(time_str, 0, sizeof(time_str));
    char local_time[20] = "";
    // 获取当前世界
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    // 格式化本地时间字符串
    char *time_format = "%Y-%m-%d %H:%M:%S";
    strftime(local_time, sizeof(local_time), time_format, timenow);
    strncat(time_str, local_time, sizeof(local_time));

    return 0;
}

int main(void)
{

    // 获取本地时间
    char local_time_str[20] = "1970-01-01 00:00:00";
    get_local_time_str(local_time_str);

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
    char *sendBuf;                                                  //发送至客户端的字符串
    sendBuf = local_time_str;

    //会阻塞进程，直到有客户端连接上来为止
    sockClient = accept(sockServer, (SOCKADDR *) &addrClient, &len);

    //接收并打印客户端数据
    send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
    printf("已发送本地时间,即将关闭链接\n");

    //关闭socket、清理
    shutdown(sockClient, SD_SEND);
    closesocket(sockClient);
    closesocket(sockServer);
    WSACleanup();

    return 0;
}