#include "enSocket.h"
#include <stdio.h>
void enInit(){
	if((enUDPSocketOut = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		printf("Couldn't make global udp socket");
	}
}
int enSend(char* ip, unsigned short port, struct enBuffer* buff){
	if(buff->ptr == 0){
		return 0;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	sendto(enUDPSocketOut, buff->data, buff->ptr, 0, (struct sockaddr*)&addr, sizeof(addr));
	return buff->ptr;
}
int enSendSized(char* ip, unsigned short port, struct enBuffer* buff, unsigned int size){
	if(buff->ptr == 0 || size == 0){
		return 0;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	if(size > buff->ptr){
		size = buff->ptr;
	}
	void* start = buff->data + buff->ptr - size;
	sendto(enUDPSocketOut, start, size, 0, (struct sockaddr*)&addr, sizeof(addr));
	return size;
}
int enUDPListen(unsigned short port){
	int sock;
	if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
		return -1;
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		close(sock);
		return -1;
	}
	return sock;
}
int enUDPRecv(int sock, struct enBuffer* buff, unsigned int *ip, unsigned short *port){
	struct sockaddr_in addr;
	int maxBuffer = (buff->len - buff->ptr);
	int recvd = 0;
	int size;
	while((recvd = recvfrom(sock, buff->data+buff->ptr, maxBuffer, MSG_PEEK, (struct sockaddr *) &addr, &size)) >= maxBuffer){
		maxBuffer <<= 1;
		enBufferSizeUp(buff, maxBuffer);
		maxBuffer = (buff->len - buff->ptr);
	}
	*ip = ntohs(addr.sin_addr.s_addr);
	*port = ntohs(addr.sin_port);
	return recvfrom(sock, buff->data+buff->ptr, maxBuffer, 0, (struct sockaddr *) &addr, &size);
}
char *enIPChar(unsigned int ip){
	struct in_addr addr;
	addr.s_addr = htons(ip);
	return inet_ntoa(addr);
}
void enClose(){
	close(enUDPSocketOut);
}