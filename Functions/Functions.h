#ifndef Functions_h
#define Functions_h

void *allocate(size_t size);
char *allocateString(const char * string);
_Bool isPozitivNumber(const char *string);
FILE *openFile(const char *name, const char *mode);

#endif /* Functions_h */
