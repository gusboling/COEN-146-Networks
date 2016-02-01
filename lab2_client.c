#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char * argv[])
{
	//Validating command line usage
	if(argc < 3)
		exit(1);
	//Initializing the client socket
	printf("Beginning Initialization. \n");
		
	struct hostent * server_addr = gethostbyname(argv[1]);

	struct sockaddr_in server;
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	bcopy((char*)server_addr->h_addr, (char*)&server.sin_addr, server_addr->h_length);
	server.sin_port=htons(5001);
	
	printf("Socket Initialized. \n");	
	//Opening client socket
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

	printf("Socket Opened. \n");
	//Preparing file I/O, gathering data
	char* out_buffer[257];

	FILE *fp = fopen(argv[2], "r");
	fread(out_buffer, 1, 256, fp);
	
	printf("Read File. \n");	
	//Sending data gathered from file, recording number of bytes sent.
	int num_bytes = sendto(sockfd, out_buffer, 256, 0, (struct sockaddr*)&server,sizeof(server));
	//File closing and summary of bytes sent.
	fclose(fp);

	printf("Bytes Sent: %d \n", num_bytes);	
}
