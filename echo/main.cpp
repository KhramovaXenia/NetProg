#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
void error(const char * why, const int exit_code){
	cout << endl << why << endl;
	exit(exit_code);
}

int main(int argc, char **argv)
{
	// Подготовка структуры с адресом программы
	sockaddr_in * selfAddr = new (sockaddr_in);
	selfAddr -> sin_family = AF_INET;
	selfAddr -> sin_port = 0;
	selfAddr -> sin_addr.s_addr = 0;
	
	// Подготовка структуры с адресом сервера daytime
	sockaddr_in * remoteAddr = new (sockaddr_in);
	remoteAddr -> sin_family = AF_INET;
	remoteAddr -> sin_port = htons(13);
	remoteAddr -> sin_addr.s_addr = inet_addr("82.179.90.12");
	
	// Сокет
	int mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1)
		error("error socket", 11);
	
	// Бинд
	int rc = bind(mySocket, (const sockaddr*)selfAddr, sizeof(sockaddr_in));
	if(rc == -1){
		close(mySocket);
		error("error bind", 12);
	}	
	// Connect
	rc = connect(mySocket, (const sockaddr*)remoteAddr, sizeof(sockaddr_in));
	if(rc == -1){
		close(mySocket);
		error("error connect", 13);
	}
	
	// Buff
	char * buf = new char[256];
	strcpy(buf, "Хей, дай время!");
	int length = strlen(buf);
	
	// Send
	rc = send(mySocket, buf, length, 0);
	if(rc == -1){
		close(mySocket);
		error("error send", 14);
	}
	cout << "We send: " << buf << endl;
	
	// Get
	rc = recv(mySocket, (char *)buf, 256, 0);
	if(rc == -1){
		close(mySocket);
		error("error get", 15);
	}
	cout << "We get: " << buf << endl;
	return 0;
}
