#include "StdAfx.h"
#include "server.h"
void HttpServer::start()
{
	stopsymbol="";
	cout<<"start service successful"<<endl;
	WSAStartup(MAKEWORD(2,0),&wsadata);  
	SOCKET ssocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//����һ��TCP��Socket������û�а�  
	struct sockaddr_in server;  
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  //inet_addr("192.168.1.107");  
	server.sin_family = AF_INET;  
	server.sin_port = htons(PORT);//����һ���˿ڵ�ַ��ָ����ַ�Ͷ˿ں�  
	   
	if(bind(ssocket,(sockaddr*)&server,sizeof(sockaddr_in)) == SOCKET_ERROR)
	{  
		std::cout<<"error bind"<<std::endl;  
	}//��TCP Socket��ָ���Ķ˿ڵ�ַ  
	if(listen(ssocket, 4) == SOCKET_ERROR)
	{  
		std::cout<<"listen error"<<std::endl;  
	}  
	fd_set read_fdset;//���ļ�������  
	std::vector<int> sockets;//���˿ڵļ��ϣ�ÿ������һ�����󣬾ͻ��½�һ���˿ڣ����Ҵ�ŵ��ü�����  
	HANDLE       hThread;
	DWORD        dwThreadId; 
	SOCKET       sClient; 
	while(true){  
		if (stopsymbol=="stop")
		{
			closesocket(ssocket);
			break;
		}
		FD_ZERO(&read_fdset);  
		FD_SET(ssocket,&read_fdset); 
		int n = select(0,&read_fdset,NULL,NULL,0);  
		if(FD_ISSET(ssocket,&read_fdset))
		{//��������˿ڽ��յ��˶�������Ҳ���ǿͻ��˷�������������  
			SOCKET sClient = accept(ssocket,NULL,0);//����һ���µĶ˿� 

			if(n!=SOCKET_ERROR)
			{  
				hThread=CreateThread(NULL,NULL,HttpServer::AnswerThread,(LPVOID)sClient, 0, &dwThreadId); 
			//if(hThread==NULL)    
			//	printf("CreatThread AnswerThread() failed./n"); 
			//else 
			//	printf("CreateThread OK./n");    
			}  
		}  
	}  

}

void HttpServer::stop()
{
	stopsymbol="stop";
	cout<<"stop service successful"<<endl;
}
