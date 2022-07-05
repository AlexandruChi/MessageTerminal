#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../define.h"
#include "ServerInit.h"
#include "../Functions/Functions.h"

struct readArgumentsReturn *readArguments(int argc, const char *argv[], int *port) {
    struct readArgumentsReturn *Return = (struct readArgumentsReturn*)allocate(sizeof(struct readArgumentsReturn));
    Return->fileName = allocateString(__DEFAULT_LOG_FILE);
    *port = __DEFAULT_PORT;
    
    if (argc == 1) {
        printf("No arguments provided\n\nUsing default configurations\n\n%s\n\n", __HELP_ATRIBUTES);
        return Return;
    }
    int flag_p = false, flag_o = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' and strlen(argv[i]) == 2) {
            if (argv[i][1] == 'p' and !flag_p) {
                if (argv[i + 1][1] != '-' and isPozitivNumber(argv[i + 1])) {
                    
                }
            }
            if (argv[i][1] == 'o' and !flag_o) {
                
            }
        }
    }
    
    return Return;
}