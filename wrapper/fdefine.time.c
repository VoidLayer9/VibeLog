//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end

#include <time.h>

long wrapper_get_unix_time(void) {
    return (long)time(NULL);
}

int wrapper_get_random(void) {
    return rand();
}

void wrapper_get_formatted_time(long timestamp, char *buf, int buf_size, const char *fmt) {
    time_t t = (time_t)timestamp;
    struct tm *gm = gmtime(&t);
    if (!gm) {
        buf[0] = '\0';
        return;
    }
    if (strcmp(fmt, "iso") == 0) {
        strftime(buf, buf_size, "%Y-%m-%dT%H:%M:%SZ", gm);
    } else if (strcmp(fmt, "date") == 0) {
        strftime(buf, buf_size, "%d-%m-%Y", gm);
    } else if (strcmp(fmt, "display") == 0) {
        strftime(buf, buf_size, "%d %b %Y", gm);
    } else {
        buf[0] = '\0';
    }
}
