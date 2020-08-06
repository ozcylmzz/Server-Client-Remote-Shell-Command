#include <stdio.h>
#include <string.h>
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>


#define USER_NAME "user"
#define USER_PASSWORD "pass"
#define SA struct sockaddr


int login(char username[100], char password[100]){
    
    FILE *fp;
    char string[1000], uName[100], uPass[100];
    int lenght, i, j, found;
    fp = fopen("userinfo","r");
    if(fp == NULL){
      printf("Error!");   
      exit(1);             
   }
   found = 0;
   while(!feof(fp)){
       if(fgets(string,10,fp) != NULL)
            //puts(string);
        sscanf(string,"%s %s",uName,uPass);
        if(strcmp(username,uName) == 0 && strcmp(password,uPass) == 0)
            found = 1;
        
              
   }
   return found;
}

const char* shell_execute(char* cmd){
    
    static char buff[1000];
    static char output[1000];
    FILE *fp;
    bzero(output, 1000);
    strcpy(output,"OUTPUT: "); 
    if ((fp = popen(cmd, "r")) == NULL) {
        printf("Error opening pipe!\n");
        return -1;
    }

    while (fgets(buff, 1000, fp) != NULL) {
        strcat(output,buff);
    }

    if(pclose(fp))  {
        printf("Command not found or exited with error status\n");
        return -1;
    }
    return output;

}


int main(int argc,char* argv[]){
    
    int counter, portno, login_succes;
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
    char buff[1000], *result, output[1000];
    char client_userName[1000], client_userPass[1000];
    for(counter = 0; counter< argc; counter++){
        printf("argv[%d]: %s\n", counter, argv[counter]);
	}
    // argv[0]: ./UKSU_server argv[1]: -p argv[2]: 4040 argv[3]: -u argv[4]: user argv[5]: -p argv[6]: pass
    if(strcmp(argv[1],"-p") != 0 || strcmp(argv[3],"-u") != 0 || strcmp(argv[5],"-p") != 0){
        printf("Wrong Arguments.\n");
        return -1;
    }else{
        if(strcmp(argv[4], USER_NAME) != 0 || strcmp(argv[6], USER_PASSWORD) != 0){
            printf("Unsuccesful login.\n");
            return -1;
        }else{
            printf("Succesful login.\n");
        }
    }
    portno = atoi(argv[2]);
    
	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { 
		printf("Socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(portno); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 
    while(1){
        // Accept the data packet from client and verification 
        connfd = accept(sockfd, (SA*)&cli, &len); 
        if (connfd < 0) { 
            printf("server acccept failed...\n"); 
            exit(0); 
        } 
        else{
            printf("server acccept the client...\n");
            
        }
        read(connfd, client_userName, sizeof(client_userName));
        read(connfd, client_userPass, sizeof(client_userPass));
        printf("Client user name :%s, Client user Pass:%s \n",client_userName,client_userPass);
        login_succes = login(client_userName,client_userPass);
        if(login_succes == 1){
            printf("Client:%s Succesfuly login.\n",client_userName);
            write(connfd, "succes", sizeof(6));
        }else{
            printf("Client Unsuccesfuly login\n");
            write(connfd, "fail", sizeof(4));
            close(sockfd);
            exit(1);
        }
        bzero(buff, 1000);
        while(strncmp("exit", buff, 4) != 0){
            read(connfd, buff, sizeof(buff));
            if (strncmp("exit", buff, 4) == 0) { 
                printf("Client %s Exit...\n",client_userName);
                write(connfd, buff, sizeof(buff)); 
                break; 
            }else{
                printf("From client: %s\n", buff);
                result = shell_execute(buff);
                bzero(output, 1000);
                strcpy(output,result);
                write(connfd, output, sizeof(output));
                bzero(result, 1000);
            }
        }
         
    }
    // After chatting close the socket
    close(sockfd);
    return 0;
} 