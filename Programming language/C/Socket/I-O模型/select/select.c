#include<iostream>
#include<windows.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include"stdafx.h"

#undef UNICODE 
#define WIN32_LEAN_AND_MEAN  

using namespace std;

int main(){
	WSADATA wsadata;
	WORD wv;
	wv=MAKEWORD(1,1);
	int err;
	err=WSAStartup(wv,&wsadata);
	if(err!=0){
		return -1;
	}
	char recvbuf[512];
	int recvbuflen = 1024;
	//tcp
	SOCKET socksrv=socket(AF_INET,SOCK_STREAM,0);
	SOCKADDR_IN addrsrv;
	addrsrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrsrv.sin_family=AF_INET;
	addrsrv.sin_port=htons(1234);
	
	int res1=bind(socksrv,(SOCKADDR*)& addrsrv,sizeof(SOCKADDR));
	if(res1!=0)
		return -1;
	listen(socksrv,5);
	SOCKADDR_IN addrclient;
	SOCKET AcceptSocket= INVALID_SOCKET;
	//udp
	SOCKET sockudps=socket(AF_INET,SOCK_DGRAM,0);
	SOCKADDR_IN addrudps;
	addrudps.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrudps.sin_family=AF_INET;
	addrudps.sin_port=htons(1234);
	bind(sockudps,(SOCKADDR*)&addrudps,sizeof(SOCKADDR));
	//进行select模型创建
	fd_set fdRead1,fdRead;
	FD_ZERO(&fdRead1);
	FD_SET(socksrv,&fdRead1);
	FD_SET(sockudps,&fdRead1); 
	//进行处理
	while(1){
		fdRead=fdRead1;
		int count=select(0,&fdRead,NULL,NULL,NULL);
		//start thread
		if (count>0){
			for(int i=0;i<(int)fdRead1.fd_count;i++){
				//进行检测 
				if(FD_ISSET(fdRead1.fd_array[i],&fdRead))
				{
					if(fdRead1.fd_array[i]==socksrv){
						if(fdRead1.fd_count<FD_SETSIZE){
							
						int len=sizeof(SOCKADDR);
						AcceptSocket = accept(socksrv, (SOCKADDR*)&addrclient, &len);//有请求连接的TCP客户端
							if (AcceptSocket == INVALID_SOCKET)
							{
								printf("accept failed !\n");
								closesocket(fdRead1.fd_array[i]);
								WSACleanup();
								return -1;
							}
							//增加新的连接套接字进行复用等待
							FD_SET(AcceptSocket, &fdRead1);
							printf("接收到新的连接：%s\n", inet_ntoa(addrclient.sin_addr));
						}
						else
						{
							printf("连接个数超限!\n");
							continue;
						}
					}
					else if(fdRead1.fd_array[i]==sockudps){
						int len=sizeof(SOCKADDR);
						int resu=recvfrom(sockudps, recvbuf,recvbuflen,0, (SOCKADDR*)&addrudps, &len);
						if (resu > 0)
						{

							//处理数据请求
							char sendBuf[100];
							sprintf(sendBuf, "echo:%s", recvbuf);
							//strcat_s(recvbuf, "--echo");
							sendto(sockudps, recvbuf, sizeof(recvbuf), 0, (SOCKADDR*)&addrudps, sizeof(SOCKADDR));//发送回射内容
							//....
						}
						else
						{
							//情况2：接收失败
							printf("UPD  recv failed with error: %d\n", WSAGetLastError());
							closesocket(fdRead1.fd_array[i]);
							FD_CLR(fdRead1.fd_array[i], &fdRead1);
						}
					}
					//待读的是accept套接字 
					else{
						//有数据到达
						
						char recvbuf1[512];
						int iResult = recv(fdRead1.fd_array[i], recvbuf1, recvbuflen, 0);//有来自TCP客户端的数据到达
						if (iResult > 0)
						{
							//情况1：成功接收到数据
							printf("\nTCP Bytes received: %d\n", iResult);
							//strcat_s(recvbuf, "--echo");
							send(fdRead1.fd_array[i], recvbuf1, strlen(recvbuf) + 1, 0);//发送回射内容
								            
						}
						else if (iResult == 0)
						{
							//情况2：连接关闭
							printf("TCP Current Connection closing...\n");
							closesocket(fdRead1.fd_array[i]);
							FD_CLR(fdRead1.fd_array[i], &fdRead1);
						}
						else
						{
							//情况3：接收失败
							printf("recv failed with error: %d\n", WSAGetLastError());
							closesocket(fdRead1.fd_array[i]);
							FD_CLR(fdRead1.fd_array[i], &fdRead1);
						}
						
					}
					}
				}
				
			}
			else{
			
			printf("select failed with error: %d\n", WSAGetLastError());
			break;

			}
		}
			// cleanup 
		closesocket(socksrv);
		WSACleanup();
		return 0;
		
	} 
