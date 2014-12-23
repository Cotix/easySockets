#ifndef ENBUFFER_HEADER
#define ENBUFFER_HEADER

struct enBuffer{
	void * data;
	unsigned int len;
	unsigned int ptr;
};

struct enBuffer* enBufferCreate(unsigned int length);
void enBufferWrite(struct enBuffer* buff, void * data, unsigned int length);
int enBufferRead(struct enBuffer* buff, void * data, unsigned int maxLength);
void enBufferRealloc(struct enBuffer* buff, unsigned int size);
int enBufferSeek(struct enBuffer* buff, unsigned int pos);
void enBufferFree(struct enBuffer* buff);
#endif