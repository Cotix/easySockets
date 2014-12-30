#include "enSocket.h"
#include "enBuffer.h"
#include <stdio.h>

int main(){
	struct enBuffer* myBuffer = enBufferCreate(32);
	enInit();
	int socket = enUDPListen(3636);
	while(1){
		unsigned int ip;
		unsigned short port;
		int len = enUDPRecv(socket, myBuffer, &ip, &port);
		char str[64];
		if(len >= 64){
			len = 63;
		}
		enBufferRead(myBuffer, str, len);
		printf("Got a message from %s: %s(len:%i; len of buffer: %u; from port: %u)\n", enIPChar(ip), str, len, myBuffer->len, port);
	}
}