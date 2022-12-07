#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char *argv[])
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
		printf("Socket creation failed\n");
	else
		printf("Socket creation successful\n");

	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;

	// if(connect(sockfd, (struct sockaddr*)&ser, sizeof(ser)) != 0)
	// 	printf("Socket connect failed\n");
	// else
	// 	printf("Socket connect successful\n");

	//Functionality
	char buff[100];
	while(1)
	{
		printf("Enter msg to server: ");
		scanf("%s", buff);

		// send(sockfd, buff,sizeof(buff), 0);
		// recv(sockfd, buff, sizeof(buff), 0);
		int len = sizeof(ser);
		sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr*)&ser, len);
		recvfrom(sockfd, buff,sizeof(buff), MSG_WAITALL, (struct sockaddr*)&ser, &len);
		
		printf("Reply from server: %s\n",buff);
	}
	return 0;
}