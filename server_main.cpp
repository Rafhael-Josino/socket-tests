#include <iostream>
#include "server.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "ERROR, port's number not provided\n";
		exit(0);
	}
	Socket_server_tcp server(argv[1]);
	char buffer[256];
	char data1 = 'a';
	char data2 = 'b';

	if(server.the_binding_of_socket() < 0)
		error("Fail to bind\n");
	server.serv_conectar(5);
	cout << "Client message:\n";
	atender(buffer,server);
	if(buffer[0] == '1')
		cout << "sending data one.\n";
	else 
		cout << "sending data two.\n";
	server.close_server();
	return 0;
}
