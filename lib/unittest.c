#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include "unittest.h"
#include "log.h"

int test_run_cnt = 0;

int
num_tests_run(void)
{
    return test_run_cnt;
}

void
assert_eq(uint32_t actual, uint32_t expected, char *fmt, ...)
{
    va_list args;

    // for some reason, calling log_msg here wreaks havoc on the output.
    if (verbose) {
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
    log_msg("...");
    assert(actual == expected);
    log_msg(" SUCCESS.\n");
    test_run_cnt++;
}
