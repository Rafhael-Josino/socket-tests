#include <iostream>
#include "client.h"

using namespace std;

int main(int argc,char* argv[]){
	if(argc < 3)
		error("ERROR missing inputs\n");
	Socket_client_tcp client(argv[1],argv[2]);
	char buffer[256];
	int data = 0;

	if(client.conectar() < 0)
		error("Fail to connect\n");
	cout << "Which data do you want [1,2]?\n";
	chamar(buffer,client);
	client.close_client();
	return 0;
}
