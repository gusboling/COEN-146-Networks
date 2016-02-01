#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc,char * argv[])
{
	//validating command line usage
	if(argc < 3)
		exit(1);

	//preparing recipient file
	
	FILE *fp = fopen(argv[2], "w");
	if(fp==NULL){
		printf("Error in Write File Opening. \n");
		exit(1);
	}
		
	char in_buffer[256];
	//initializing socket
	printf("Begining Initialization. \n");

	struct sockaddr_in server;
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5001);
	printf("Socket Initialized. \n");	
	//opening socket
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
	
	printf("Socket Opened. \n");
	//binding socket
	bind(sockfd,(struct sockaddr *)&server, sizeof(server));
	socklen_t len;

	printf("Socket Bound, Waiting for Datagram. \n");
	//waiting for sent data to be recieved
	int num_bytes = recvfrom(sockfd, in_buffer, 256, 0, (struct sockaddr *)&server, &len);
	
	printf("Bytes Recieved: %d \n", num_bytes);
	//writing data to file and closing file
	fwrite(in_buffer, 1, 256, fp);

	fclose(fp);	

	return 0;
}
