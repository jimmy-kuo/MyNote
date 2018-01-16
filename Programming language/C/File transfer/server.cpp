#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT 6013
#define IP "172.30.58.113"
int main(void)
{
	int Condition;
//传送源文件打开区
	FILE *fsource;
	fsource = fopen("C:\\Users\\Administrator\\Desktop\\The Little Prince.txt", "r");
	if (fsource == NULL)
	{
		puts("错误：文件打开失败,按任意键退出");
		getchar();
		exit(-1);
	}
	puts("===================文件打开成功===================\n\n");
//创建套接字
	WSADATA wsaData;
	SOCKET socket_Server;
	SOCKADDR_IN addrServer;
	SOCKET socket_Client;
	SOCKADDR_IN addrClient;
	Condition = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Condition != 0)
	{
		puts("错误：Windows Socket API 启动失败，按任意键退出");
		getchar();
		exit(-1);
	}
	socket_Server = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_Server == INVALID_SOCKET)
	{
		puts("错误：SOCKET 创建失败，按任意键退出");
		WSACleanup();
		getchar();
		exit(-1);
	}
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	Condition = bind(socket_Server, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	if (Condition == SOCKET_ERROR)
	{
		puts("错误：socket_Server绑定失败，按任意键退出");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("=================WSA,socket启动成功===============\n\n");
//侦听链接请求
	Condition = listen(socket_Server, 5);
	if (Condition == SOCKET_ERROR)
	{
		puts("错误：侦听连接请求失败，按任意键退出");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	puts("================正在侦听链接请求......============\n\n");
	int len = sizeof(SOCKADDR);
	char send_massage[100] = "来自服务器：已经连接到服务器";
	char recvBuf[100];
	socket_Client = accept(socket_Server, (SOCKADDR*)&addrClient, &len);
	if (socket_Client == INVALID_SOCKET)
	{
		puts("错误：链接到客户端失败，按任意键退出");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	send(socket_Client, send_massage, strlen(send_massage) + 1, 0);
	recv(socket_Client, recvBuf, 100, 0);
	printf("%s\n", recvBuf);
	char Send_File_buf[101];
//循环发送数据
	puts("\n================开始准备发送文件数据==============\n\n");
	while (feof(fsource) == 0)
	{
		//Sleep(5);
		fgets(Send_File_buf, 100, fsource);
		send(socket_Client, Send_File_buf, strlen(Send_File_buf) + 1, 0);
	}
		puts("==================发送文件数据完毕================\n\n");
//关闭文件部分
	Condition = fclose(fsource);
	if (Condition == EOF)
	{
		puts("错误：文件关闭失败，按任意键退出");
		closesocket(socket_Server);
		WSACleanup();
		getchar();
		exit(-1);
	}
	closesocket(socket_Client);
	WSACleanup();
	puts("==============程序结束，按任意键退出==============\n\n");
	getchar();
}
