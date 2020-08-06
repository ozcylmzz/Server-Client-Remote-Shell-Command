#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 

#define HOST "www.yildiz.edu.tr" 
#define SA struct sockaddr 


int main(int argc,char* argv[]){
    
    int counter, portno;
	int sockfd, connfd, len, n; 
	struct sockaddr_in servaddr, cli; 
    char buff[1000], result[1000], userName[1000], userPass[1000];
    
    for(counter = 0; counter< argc; counter++){
        printf("argv[%d]: %s\n", counter, argv[counter]);
	}
    // argv[0]: ./UKSU_client argv[1]: -h argv[2]: wwww.yildiz.edu.tr argv[3]: -p argv[4]: 4040 argv[5]: -u argv[6]: user argv[7]: -p argv[8]: pass
    if(strcmp(argv[1],"-h") != 0 || strcmp(argv[2],HOST) != 0 || strcmp(argv[3],"-p") != 0 || strcmp(argv[5],"-u") != 0 || strcmp(argv[7],"-p") != 0){
        printf("Wrong Arguments\n");
        return -1;
    }
    // socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("Socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

    portno = atoi(argv[4]);

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(portno); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("Connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("Connected to the server..\n");
    strcpy(userName,argv[6]);
    write(sockfd,userName, sizeof(userName));
    strcpy(userPass,argv[8]);
    write(sockfd,userPass, sizeof(userPass));
    read(sockfd, result, sizeof(result));
	if (strncmp("fail", result, 4) == 0){
		printf("Unsuccesful login.\n");
		close(sockfd);
		exit(1);
	}
	printf("For quit: write exit to console.\n");
	while(1){
        bzero(buff, 1000);
		printf("What is the command?\n");
		n = 0;
    	while ((buff[n++] = getchar()) != '\n');
		write(sockfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n");
            write(sockfd, buff, sizeof(buff)); 
			break; 
		}else{
            read(sockfd, result, sizeof(result));
			printf("result: %s\n",result);
			bzero(result, 1000);
        }
    } 
    printf("Client exit.\n");
    close(sockfd);
    
    return 0;
}