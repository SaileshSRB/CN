#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in ser;
	
	if(sockfd == -1)
		printf("Socket creation failed\n");
	else
		printf("Socket creation success\n");
		
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;
	
	if(connect(sockfd, (struct sockaddr*)&ser, sizeof(ser)) != 0)
		printf("Socket connection failed\n");
	else
		printf("Socket connection success\n");
	
	//Functionality
	char buff[100],buff1[100],c;
	int idx = 0;
	
	int f = 1;
	while(f)
	{
		scanf("%s",buff);
		send(sockfd,buff,sizeof(buff),0);
		recv(sockfd,buff1,sizeof(buff1),0);
		printf("Echo from server : %s\n",buff1);
	}

	
	return 0;
}
