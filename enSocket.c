#include "enSocket.h"
struct enSocket* enTCPConnect(char* ip, unsigned short port){
	struct enSocket socket = malloc(sizeof(enSocket));
	struct sockaddr_in myAddr;
	socket->sock = socket(AF_INET, SOCKET_STREAM, 0);
	myAddr.sin_family = AF_INET;
	myAddr.sin_port = htons(port);
	myAddr.sin_addr.s_addr = inet_addr(ip);
	if(connect(socket->sock, (struct sockaddr*)&myAddr, sizeof(struct sockaddr))){
		return socket;
	}else{
		close(socket->sock);
		free(socket);
		return 0;
	}
}
struct enSocket* enTCPListen(unsigned short port);
void enSend(struct enSocket* socket, struct enBuffer* buff);
void enSendSized(struct enSocket* socket, struct enBuffer* buff, unsigned int size);
