#include "enBuffer.h"
#include <stdlib.h>
#include <string.h>
struct enBuffer* enBufferCreate(unsigned int length){
	struct enBuffer* res = malloc(sizeof(struct enBuffer));
	res->ptr = 0;
	res->len = length;
	res->data = malloc(length);
	return res;
}
void enBufferWrite(struct enBuffer* buff, void * data, unsigned int length){
	if((buff->len - buff->ptr) < length){
		buff->data = realloc(buff->data, buff->ptr + length);
	}
	buff->ptr += length;
	memcpy(buff->data + buff->ptr, data, length);
}
int enBufferRead(struct enBuffer* buff, void * data, unsigned int maxLength){
	if((buff->len - buff->ptr) < maxLength){
		maxLength = buff->len - buff->ptr;
	}
	memcpy(data,buff->data + buff->ptr, maxLength);
	buff->ptr += maxLength;
	return maxLength;
}
void enBufferRealloc(struct enBuffer* buff, unsigned int size){
	buff->data = realloc(buff->data, size);
	buff->len = size;
	if(buff->ptr > size){
		buff->ptr = size;
	}
}
int enBufferSeek(struct enBuffer* buff, unsigned int pos){
	return buff->ptr = (buff->len > pos) ? pos : 0;
}
void enBufferFree(struct enBuffer* buff){
	free(buff->data);
	free(buff);
}
void enBufferSizeUp(struct enBuffer* buff, unsigned int size){
	buff->data = realloc(buff->data, buff->len + size);
	buff->len += size;
}