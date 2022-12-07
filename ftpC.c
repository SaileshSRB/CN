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
	char file[100],buff[100];
	char dest[100];

	while(1)
	{
		printf("Enter the source file name \n");
		scanf("%s",file);
		send(sockfd,file,sizeof(file),0);
		recv(sockfd,buff,sizeof(buff),0);
		printf("Result from server : %s\n",buff);
		printf("Enter the destination file name \n");
		scanf("%s",dest);
		
		int r2 = open(dest,O_CREAT|O_RDWR|O_APPEND);
		
		int len = 0;
		while(buff[len] != '\0')
		{
			len++;
		}
		
		write(r2,buff,(len-1)*sizeof(char));
		
	}

	
	return 0;
}
