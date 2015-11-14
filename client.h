#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

class Socket_client_tcp{
    private:
    	int sockfd;
    	struct sockaddr_in serv_addr;
    public:
	Socket_client_tcp(char* ip, char* portno){
      	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
        	error("ERROR opening socket");
	memset(&serv_addr,0,sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
	inet_aton(ip,&serv_addr.sin_addr);
	serv_addr.sin_port = htons(atoi(portno));
	}
	int conectar();
	friend void chamar(char buffer[256], Socket_client_tcp p_client);
	friend void atender(char buffer[256], Socket_client_tcp p_client);
	void close_client(){close(sockfd);}
	//~Socket_client_tcp(){close(sockfd);}
};

int Socket_client_tcp::conectar(){
	return connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));	//cli_conectar < 0 for ERROR
}

void chamar(char p_buffer[256], Socket_client_tcp p_client){
    int n;
    bzero(p_buffer,256);
    fgets(p_buffer,255,stdin);
    //Manda o buffer para o servidor
    n = write(p_client.sockfd,p_buffer,strlen(p_buffer));
    if (n < 0) 
 	 error("ERROR writing to socket");
    bzero(p_buffer,256);
    //Recebe a mensagem de resposta
    n = read(p_client.sockfd,p_buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",p_buffer);
}

void atender(char p_buffer[256], Socket_client_tcp p_client){
	int n;
	bzero(p_buffer,256);
	n = read(p_client.sockfd,p_buffer,255);
	if (n < 0)
		error("ERROR reading from socket");
	printf("Here is the message: %s\n",p_buffer);
	n = write(p_client.sockfd,"I got your message\n",19);
	if ( n < 0)
		error("Writing to socket");
}
