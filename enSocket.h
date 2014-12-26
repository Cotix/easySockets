#ifndef ENSOCKET_HEADER
#define ENSOCKET_HEADER
#include "enBuffer.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

int enUDPSocketOut;

void enInit(unsigned short port);
int enSend(char* ip, unsigned short port, struct enBuffer* buff);
int enSendSized(char* ip, unsigned short port, struct enBuffer* buff, unsigned int size);
struct enSocket* enUDPListen(unsigned short port);
void enClose();

#endif