#include<winsock2.h>
#include<stdio.h>
#include <time.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

// note
// ���ڱ���ʱ��Ӷ������ -lwsock32 (gcc)

/**
 * ��������ҵ��ѧ(����) ��������� II
 * ʵ��1 - ʱ��ͬ��������
 *
 * server - ��������
 * @author  h-j-13(140420227)
 * @time    2017��12��24��
 * */

#define PORT 6013
#define SEND_CHAR_LENGTH 100

int get_local_time_str(char *time_str) {/** ��ȡ����ʱ���ַ���*/
    // ���ԭʼ����
    memset(time_str, 0, sizeof(time_str));
    char local_time[32] = "";
    // ��ȡ��ǰ����
    time_t now;
    struct tm *timenow;
    time(&now);
    timenow = localtime(&now);
    // ��ʽ������ʱ���ַ���
    char *time_format = "%Y-%m-%d %H:%M:%S";
    strftime(local_time, sizeof(local_time), time_format, timenow);
    strncat(time_str, local_time, sizeof(local_time));

    return 0;
}

int main(void) {

    // ��ȡ����ʱ��
    char local_time_str[32] = "1970 00:00:00";
    get_local_time_str(local_time_str);
    // ��ʼ��socket
    WSADATA wsaData;
    SOCKET sockServer;
    SOCKADDR_IN addrServer;
    SOCKET sockClient;
    SOCKADDR_IN addrClient;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // ����socket����
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);            //INADDR_ANY��ʾ�κ�IP
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);                              //�󶨶˿�
    bind(sockServer, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));

    //Listen������
    listen(sockServer, 5);                                          //5Ϊ�ȴ�������Ŀ
    printf("����������: ���� %d �˿�...\n", PORT);
    int len = sizeof(SOCKADDR);
    char *sendBuf;                                 //�������ͻ��˵��ַ���
    sendBuf = local_time_str;

    //���������̣�ֱ���пͻ�����������Ϊֹ
    sockClient = accept(sockServer, (SOCKADDR *) &addrClient, &len);

    //���ղ���ӡ�ͻ�������
    send(sockClient, sendBuf, SEND_CHAR_LENGTH, 0);
    printf("�ѷ��ͱ���ʱ��,�����ر�����\n");

    //�ر�socket������
    closesocket(sockClient);
    WSACleanup();

    return 0;
}