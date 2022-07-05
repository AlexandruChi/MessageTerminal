#ifndef ServerInit_h
#define ServerInit_h

struct readArgumentsReturn {
    char *fileName;
};

struct readArgumentsReturn *readArguments(int argc, const char *argv[], int *port);

#endif /* ServerInit_h */
