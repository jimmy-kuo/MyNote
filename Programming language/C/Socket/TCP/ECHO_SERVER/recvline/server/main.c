#include<winsock2.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * ��������ҵ��ѧ(����) ��������� II
 * ʵ��1 - ���������
 * a.recvline��ʽ
 *
 * server - ��������
 * @author  h-j-13(140420227)
 * @time    2018��1��7��
 * */

#define PORT 6013
#define BUF 20
#define MAX_CONNECT_TIME 5

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
    while (connect_cnt--)
    {
        sockClient = accept(sockServer, (SOCKADDR *) &addrClient, &len);
        printf("welcome %s \n", inet_ntoa(addrClient.sin_addr));

        while (1)
        {
            if(recv(sockClient, recv_buf, BUF, 0)==0)               // �ͻ��˶Ͽ�����ʱ�Ͽ�������
                break;
            printf("recv>%s\n",recv_buf);
            sprintf(send_buf, "echo:%s", recv_buf);                 // �����ַ���
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
