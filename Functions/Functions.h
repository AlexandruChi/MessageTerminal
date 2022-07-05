#ifndef Functions_h
#define Functions_h

void *allocate(size_t size);
char *allocateString(const char * string);
_Bool isPozitivNumber(const char *string);
FILE *openFile(const char *name, const char *mode);
void resetMemory(void *block_address, int count, long unsigned int esize);

#endif /* Functions_h */
