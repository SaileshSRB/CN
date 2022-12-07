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
	
	if(bind(sockfd, (struct sockaddr*)&ser, sizeof(ser)) != 0)
		printf("Socket bind failed\n");
	else
		printf("Socket bind success\n");
	
	if(listen(sockfd,1) !=0)
		printf("Socket listen failed\n");
	else
		printf("Socket listen success\n");
		
	int clisoc = accept(sockfd,NULL,NULL);
	
	//Functionality
	char buff[100];
	while(1)
	{
	recv(clisoc,buff,sizeof(buff),0);
	printf("Client : %s\n",buff);
	buff[0] = 'z';
	send(clisoc,buff,sizeof(buff),0);
	}
	return 0;
}
