#include "new_shell.h"

void sen_print(const char *message) {
    write(STDOUT_FILENO, message, strlen(message));
}
