#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

class Socket_server_tcp{
     private:
     	int sockfd, newsockfd;
     	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
     public:
	Socket_server_tcp(char* portno){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	        error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(portno));
	}
	int the_binding_of_socket();
	int serv_conectar(int n_connections);
	friend void atender(char buffer[256], Socket_server_tcp serv);
	friend void chamar(char buffer[256], Socket_server_tcp serv);
	void close_server(){close(newsockfd);close(sockfd);}
};

int Socket_server_tcp::the_binding_of_socket(){
     return bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));};
     //the_binding_of_socket < 0 for ERROR

int Socket_server_tcp::serv_conectar(int n_connections){
	listen(sockfd,n_connections); 
	clilen = sizeof(cli_addr);
     	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);
     	if (newsockfd < 0) 
        	  error("ERROR on accept");
}

void atender(char p_buffer[256], Socket_server_tcp serv){
     int n;
     bzero(p_buffer,256);
     //Recebe a mensagem do cliente
     n = read(serv.newsockfd,p_buffer,255);
     if (n < 0)
	 error("ERROR reading from socket");
     printf("Here is the message: %s\n",p_buffer);
     //Manda a mensagem de resposta
     n = write(serv.newsockfd,"I got your message\n",19);
     if (n < 0)
	 error("ERROR writing to socket");
}


void chamar(char p_buffer[256], Socket_server_tcp serv){
    int n;
    bzero(p_buffer,256);
    fgets(p_buffer,255,stdin);
    n = write(serv.newsockfd,p_buffer,strlen(p_buffer));
    if (n < 0) 
 	 error("ERROR writing to socket");
    bzero(p_buffer,256);
    n = read(serv.newsockfd,p_buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",p_buffer);
}
