#include <string.h>

#include "client_cmd.h"

void strip(char *str)
{
    int l = strlen(str) - 1;
    if (str[l] == '\n') str[l] = '\0';
}

