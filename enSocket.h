#ifndef ENSOCKET_HEADER
#define ENSOCKET_HEADER
#include "enBuffer.h"
#include <sys/socket.h>

struct enSocket{
	int sock;

};

struct enSocket* enTCPConnect(char* ip, unsigned short port);
struct enSocket* enTCPListen(unsigned short port);
void enSend(struct enSocket* socket, struct enBuffer* buff);
void enSendSized(struct enSocket* socket, struct enBuffer* buff, unsigned int size);


#endif