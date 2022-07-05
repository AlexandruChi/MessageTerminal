#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../define.h"

void *allocate(const size_t size) {
    void *p = malloc(size);
    if (!p) {
        fprintf(stderr, __ALLLOCATE_ERROR);
        exit(EXIT_FAILURE);
    }
    return p;
}

char *allocateString(const char *string) {
    char *s = (char*)allocate(sizeof(char) * (strlen(string) + 1));
    strcpy(s, string);
    return s;
}

_Bool isPozitivNumber(const char *string) {
    for (int i = 0; i < strlen(string); i++) {
        if (!isdigit(string[i])) {
            return false;
        }
    }
    return true;
}

FILE *openFile(const char *name, const char *mode) {
    FILE *file = fopen(name, mode);
    if (!file) {
        fprintf(stderr, __OPEN_FILE_ERROR, name);
        exit(EXIT_FAILURE);
    }
    return file;
}

void resetMemory(void *block_address, int count, long unsigned int esize) {
    memset(block_address, 0x00, esize * count);
}
