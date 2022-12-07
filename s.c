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

	struct sockaddr_in ser,cli;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(atoi(argv[1]));
	ser.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr*)&ser, sizeof(ser)) != 0)
		printf("Socket bind failed\n");
	else
		printf("Socket bind successful\n");

	//Functionality
	char buff[100];
	while(1)
	{	
		int len = sizeof(cli);
		recvfrom(sockfd, buff,sizeof(buff), MSG_WAITALL, (struct sockaddr*)&cli, &len);
		int pnum = ntohs(cli.sin_port);

		printf("Msg from client %d: %s\n",pnum,buff);
		printf("Enter reply: ");
		scanf("%s",buff);
		sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (struct sockaddr*)&cli, len);
	}

	// if(listen(sockfd,3) != 0)
	// 	printf("Socket listen failed\n");
	// else
	// 	printf("Socket listen successful\n");

	// //Functionality
	// char buff[100];
	// while(1)
	// {	
	// 	int len = sizeof(cli);
	// 	int clisoc = accept(sockfd, (struct sockaddr*) &cli ,&len);
	// 	int pnum = ntohs(cli.sin_port);

	// 	int pid = fork();
	// 	if(pid == 0)
	// 	{
	// 		close(sockfd);
	// 		while(1)
	// 		{
	// 			recv(clisoc, buff,sizeof(buff), 0);
	// 			// int fd = open(buff, O_RDONLY);
	// 			// read(fd, &buff, 50);
	// 			printf("Msg from client %d: %s\n",pnum,buff);
	// 			printf("Enter reply: ");
	// 			scanf("%s",buff);
	// 			send(clisoc, buff, sizeof(buff), 0);
	// 		}
	// 	}
	// 	close(clisoc);
	// }
	return 0;
}