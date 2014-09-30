extern int verbose;  // set or unset; if set, log_msg will go to stdout.

extern int get_verbosity(void);

extern void set_verbosity(int level);

void log_msg(char *fmt, ...);
