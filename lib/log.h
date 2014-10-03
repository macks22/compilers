extern int verbose;  // set or unset; if set, log_msg will go to stdout.

int get_verbosity(void);

void set_verbosity(int level);

void log_msg(char *fmt, ...);
