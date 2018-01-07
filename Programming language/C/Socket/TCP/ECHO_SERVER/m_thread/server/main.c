#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * ��������ҵ��ѧ(����) ��������� II
 * ʵ��1 - ���������
 * c.recvvl ��ʽ
 *
 * server - ��������
 * @author  h-j-13(140420227)
 * @time    2018��1��7��
 * */

#define PORT 6013
#define BUF 100
#define MAX_CONNECT_TIME 5

DWORD WINAPI sockClientThread(LPVOID lpParam)
{
    char sendBuf[BUF];
    char recvBuf[BUF];

    SOCKET sockClient = (SOCKET) (LPVOID) lpParam;                          // ǿ������ת��

    while (1)
    {
        if (recv(sockClient, recvBuf, BUF, 0) == 0)                         // �ͻ��˶Ͽ�����ʱ�Ͽ�������
            break;
        printf("recv>%s\n", recvBuf);
        sprintf(sendBuf, "echo:%s", recvBuf);                               // �����ַ���
        send(sockClient, sendBuf, BUF, 0);
    }
    shutdown(sockClient, SD_BOTH);
    closesocket(sockClient);

    return 0;
}

int main(void)
{
    // ��ʼ��socket
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sockServer, sockClient;
    SOCKADDR_IN addrServer, addrClient;

    // ����socket����
    sockServer = socket(AF_INET, SOCK_STREAM, 0);
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);            //INADDR_ANY��ʾ�κ�IP
    addrServer.sin_family = AF_INET;                                //IPv4Э����
    addrServer.sin_port = htons(PORT);                              //�󶨶˿�
    bind(sockServer, (SOCKADDR *) &addrServer, sizeof(SOCKADDR));

    //Listen������
    listen(sockServer, 5);                                          //5Ϊ�ȴ�������Ŀ
    printf("����������: ���� %d �˿�...\n", PORT);

    int len = sizeof(SOCKADDR);
    char send_buf[BUF] = "";                                        //�����ַ�������
    char recv_buf[BUF] = "";                                        //�����ַ�������
    int connect_cnt = MAX_CONNECT_TIME;

    // ѭ�����ܿͻ�������
    HANDLE hThread;                                                 //���̴߳�������
    while (connect_cnt--)
    {
        sockClient = accept(sockServer, (SOCKADDR *) &addrClient, &len);
        printf("welcome %s \n", inet_ntoa(addrClient.sin_addr));
        hThread = CreateThread(NULL, 0, sockClientThread, (LPVOID) sockClient, 0, NULL);
        if (hThread == NULL)
            printf("�����߳�ʧ�ܣ�\n");
        else
            printf("���������̳߳ɹ���\n");
    }

    shutdown(sockServer, SD_BOTH);
    closesocket(sockServer);
    WSACleanup();

    return 0;
}
