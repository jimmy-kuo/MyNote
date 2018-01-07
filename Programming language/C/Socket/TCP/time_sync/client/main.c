#include<winsock2.h>
#include<stdio.h>
#include<string.h>

#pragma comment(lib, "ws2_32.lib")

/**
 * ��������ҵ��ѧ(����) ��������� II
 * ʵ��1 - ʱ��ͬ��������
 *
 * clinet - �ͻ���
 * @author  h-j-13(140420227)
 * @time    2017��12��24��
 * */

#define PORT 6013
#define RECV_CHAR 10

int main(void) {
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
    if (connect(sockClient, (SOCKADDR *) &addrServer, sizeof(SOCKADDR)) != 0) {
        printf("����ʱ��ͬ��������ʧ��\n");
        closesocket(sockClient);
        WSACleanup();
        return 0;
    };

    //ʹ�� recv() ����ѭ����������
    int recv_result = RECV_CHAR;
    char message[RECV_CHAR + 1] = "";
    char result[RECV_CHAR * 100] = "";                                          // һ���㹻��Ľ���ַ�������
    while (recv_result > 0) {
        // ѭ����������
        recv_result = recv(sockClient, message, RECV_CHAR, 0);
        if (recv_result == 0) {
            printf("�������ر�������\n");
            shutdown(sockClient, SD_RECEIVE);
        } else if (recv_result == SOCKET_ERROR) {
            printf("�������ݹ��̷����˴���:%d", WSAGetLastError());
            closesocket(sockClient);
            WSACleanup();
        } else if (recv_result > 0) {
            printf("���յ���%d���ֽ�:", recv_result);
            printf("%s\n", message);
            strcat(result, message);
        }

    }

    printf("���յ�������ʱ��Ϊ:%s", result);

    //�ر�socket
    closesocket(sockClient);
    WSACleanup();

    return 0;
}