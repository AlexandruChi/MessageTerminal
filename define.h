#ifndef define_h
#define define_h

#define and &&
#define or ||

#define true 1
#define false 0

#define __HELP_ATRIBUTES "For asigning atributs run program using:\n\n    /MessageTerminalServer -p [port number] -o [output for conversation log]"

#define __DEFAULT_PORT 4092
#define __DEFAULT_LOG_FILE "conversationLog.txt"

#define __ALLLOCATE_ERROR "\n\nNot enough memory\n"
#define __OPEN_FILE_ERROR "\n\nCan't open file %s\n"
#define __SOCKET_CREATE_ERROR "\n\nCan't ceate socket\n"
#define __SOCKET_CONFIG_ERROR "\n\nCan't config socket\n"
#define __SOCKET_CANT_OPEN_ERROR "\n\nCan't open socket\n"
#define __SOCKET_CANT_ACCEPT_CONNECTIONS_ERROR "\n\nCan't accept connections\n"
#define __CREATE_ATTR_ERROR "\n\nError creating attr\n"
#define __CREATE_THREAD_ERROR "\n\nError creating thread %d\n"
#define __GET_CLIENT_ERROR "\n\nError conecting to client\n"

#endif /* define_h */
