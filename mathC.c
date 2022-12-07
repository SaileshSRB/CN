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
	int buff[4],buff1[2],c;
	int idx = 0;
	

	while(1)
	{
		printf("Enter the operand 1 \n");
		scanf("%d",&buff[0]);
		printf("Enter the operand 2 \n");
		scanf("%d",&buff[1]);
		printf("Enter the operator \n");
		scanf("%d",&buff[2]);
		send(sockfd,buff,sizeof(buff),0);
		recv(sockfd,buff1,sizeof(buff1),0);
		printf("Result from server : %d\n",buff1[0]);
	}

	
	return 0;
}
