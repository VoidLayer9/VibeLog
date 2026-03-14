//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end


int wrapper_snprintf(void *ctx, char *str, unsigned long size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int result = vsnprintf(str, (size_t)size, format, args);
  va_end(args);
  return result;
}
int wrapper_sprintf(void *ctx, char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int result = vsprintf(str, format, args);
  va_end(args);
  return result;
}
unsigned long wrapper_strlen(void *ctx, const char *s) { return (unsigned long)strlen(s); }

void *wrapper_malloc(void *ctx, unsigned long size) { return malloc((size_t)size); }

void *wrapper_calloc(void *ctx, unsigned long num, unsigned long size) {
  return calloc((size_t)num, (size_t)size);
}

void *wrapper_realloc(void *ctx, void *ptr, unsigned long size) {
  return realloc(ptr, (size_t)size);
}

char *wrapper_strdup(void *ctx, const char *s) { return strdup(s); }

void *wrapper_memcpy(void *ctx, void *dst, const void *src, unsigned long n) {
  return memcpy(dst, src, (size_t)n);
}

void *wrapper_memset(void *ctx, void *s, int c, unsigned long n) {
  return memset(s, c, (size_t)n);
}

int wrapper_strncmp(void *ctx, const char *s1, const char *s2, unsigned long n) {
  return strncmp(s1, s2, (size_t)n);
}

int wrapper_memcmp(void *ctx, const void *s1, const void *s2, unsigned long n) {
  return memcmp(s1, s2, (size_t)n);
}

char *wrapper_strcpy(void *ctx, char *dst, const char *src) { return strcpy(dst, src); }

char *wrapper_strcat(void *ctx, char *dst, const char *src) { return strcat(dst, src); }

int wrapper_run_command(void *ctx, const char *cmd) { return system(cmd); }
