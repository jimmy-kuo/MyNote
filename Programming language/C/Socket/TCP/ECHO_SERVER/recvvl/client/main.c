#include<winsock2.h>
#include<stdio.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * ��������ҵ��ѧ(����) ��������� II
 * ʵ��1 - ���������
 * c.recvvl ��ʽ
 *
 * clinet - �ͻ���
 * @author  h-j-13(140420227)
 * @time    2018��1��7��
 * */

#define PORT 6013
#define BUF 100

int main(void)
{
    WSADATA wsaData;
    SOCKET sockClient;                                                          //�ͻ���Socket
    SOCKADDR_IN addrServer;                                                     //����˵�ַ
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�½��ͻ���socket
    sockClient = socket(AF_INET, SOCK_STREAM, 0);

    //����Ҫ���ӵķ���˵�ַ
    addrServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");                   //Ŀ��IP(127.0.0.1�ǻ��͵�ַ)
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);                                          //���Ӷ˿�6000

    //���ӵ������
    if (connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR)) != 0)
    {
        printf("���ӻ��������ʧ��\n");
        closesocket(sockClient);
        WSACleanup();
        return 0;
    };

    char send_buf[BUF] = "";                                               //�����ַ�������
    char recv_buf[BUF] = "";                                               //�����ַ�������
    while (1)
    {
        printf("input>");
        scanf("%s", send_buf);
        if (strcmp(send_buf, "q") == 0)
        {
            printf("�˳��ͻ���\n");
            break;
        }

        send(sockClient, send_buf, strlen(send_buf) + 1, 0);
        printf("recv echo>");                                  // ����ĳ������Ƕ�ֵ
        recv(sockClient, recv_buf, BUF, 0);                    // �ͳ��ַ��� + "echo:"�ĳ���
        printf("%s\n", recv_buf);
    }

    //�ر�socket
    shutdown(sockClient, SD_BOTH);
    closesocket(sockClient);
    WSACleanup();

    return 0;
}
