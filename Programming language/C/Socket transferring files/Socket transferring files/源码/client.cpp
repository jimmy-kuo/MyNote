#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 6013
#define IP "172.30.58.113"
int main(void)
{
	Sleep(1000);
	int Condition;
//传送目标文件创建区
	FILE *ftarget;
	ftarget = fopen("C:\\Users\\Administrator\\Desktop\\The Little Prince_COPY.txt", "w");
	if (ftarget == NULL)
	{
		puts("错误：文件创建失败,按任意键退出");
		getchar();
		exit(-1);
	}
	puts("=============文件创建成功==================\n\n");
//创建套接字
	WSADATA wsaData;
	SOCKADDR_IN addrServer;
	SOCKET socket_Client;
	Condition = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Condition != 0)
	{
		puts("错误：Windows Socket API 启动失败，按任意键退出");
		getchar();
		exit(-1);
	}
	socket_Client = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_Client == INVALID_SOCKET)
	{
		puts("错误：SOCKET 创建失败，按任意键退出");
		WSACleanup();
		getchar();
		exit(-1);
	}
	addrServer.sin_addr.S_un.S_addr = inet_addr(IP);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
//链接到服务器
	Condition = connect(socket_Client, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (Condition == SOCKET_ERROR)
	{
		puts("错误：连接到服务器失败，按任意键退出");
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("=============成功连接到服务器==============\n\n");
	char send_massage[100] = "来自客户端：客户端已经连接";
	char recvBuf[100];
	send(socket_Client, send_massage, strlen(send_massage) + 1, 0);
	Condition = recv(socket_Client, recvBuf, 100, 0);
	if (Condition == SOCKET_ERROR)
	{
		puts("错误：接收数据失败，按任意键退出");
		WSACleanup();
		getchar();
		exit(-1);
	}
	printf("%s\n", recvBuf);
	char Recv_File_buf[101];
	puts("\n=============准备接受文件数据==============\n\n");
//循环接收，并写入数据
	while (Condition != 0)
	{
		Condition = recv(socket_Client, Recv_File_buf, 1000, 0);
		fputs(Recv_File_buf, ftarget);
		//printf("%s", Recv_File_buf);
	
	}
	puts("\n=================接受文件数据完毕===============\n\n");
//关闭文件区域
	Condition = fclose(ftarget);
	if (Condition == EOF)
	{
		puts("错误：文件关闭失败，按任意键退出");
		closesocket(socket_Client);
		WSACleanup();
		getchar();
		exit(-1);
	}
	closesocket(socket_Client);
	WSACleanup();
	puts("=============程序结束，按任意键退出=============\n\n");
	getchar();
}