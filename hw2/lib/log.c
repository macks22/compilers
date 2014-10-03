#include <stdio.h>
#include <stdarg.h>
#include "log.h"

int verbose = 0;

int
get_verbosity(void)
{
    return verbose;
}

void
set_verbosity(int level)
{
    verbose = level;
}

void
log_msg(char *fmt, ...)
{   /* Wrap printf in order to log based on a flag. */
    va_list args;
    if (verbose) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}
