#include <dlfcn.h> // for dlopen()
#include <stdio.h>

#include <ffi.h>

int main(void) {
  void *self = dlopen(NULL, RTLD_NOW);
  if (self == NULL) {
    fprintf(stderr, "Failed to dlopen()\n");
    return 1;
  }

  int (*_puts)(const char *);
  // Hack to satisfy -Wpedantic: https://pubs.opengroup.org/onlinepubs/009695399/functions/dlsym.html
  *(void **)(&_puts) = dlsym(self, "puts");

  _puts("Hello, world!");
}
