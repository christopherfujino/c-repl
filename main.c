#include <dlfcn.h> // for dlopen()
#include <stdio.h>
#include <stdlib.h> // for exit()

#include "ffi.h"

void dynamicCall(void (*fn)(void), int argc, void **argv, ffi_type **argTypes,
                 void *retValue) {
  ffi_cif cif;
  ffi_status status =
      ffi_prep_cif(&cif, FFI_DEFAULT_ABI, argc, &ffi_type_sint /* TODO */, argTypes);
  if (status != FFI_OK) {
    fprintf(stderr, "Failed to call ffi_prep_cif\n");
    exit(1);
  }

  ffi_call(&cif, fn, retValue, argv);
}

int main(void) {
  void *self = dlopen(NULL, RTLD_NOW);
  if (self == NULL) {
    fprintf(stderr, "Failed to dlopen()\n");
    return 1;
  }

  int (*_puts)(const char *);
  void *rawPuts = dlsym(self, "puts");
  // Hack to satisfy -Wpedantic:
  // https://pubs.opengroup.org/onlinepubs/009695399/functions/dlsym.html
  *(void **)(&_puts) = rawPuts;
  _puts("Hello, world!");

  // void ffi_call (ffi_cif *cif, void *fn, void *rvalue, void **avalues)
  //
  // rvalue is a pointer to a chunk of memory that will hold the result of the
  // function call. This must be large enough to hold the result, no smaller
  // than the system register size (generally 32 or 64 bits), and must be
  // suitably aligned; it is the caller’s responsibility to ensure this. If
  // cif declares that the function returns void (using ffi_type_void), then
  // rvalue is ignored.

  const char *arg = "Hello from libffi!";
  void* args[1] = {(void *)&arg};
  //void *args[1];
  //args[0] = &arg;
  ffi_type *argTypes[1] = {&ffi_type_pointer};
  ffi_arg retValue;
  dynamicCall((void (*)(void))_puts, 1, args, argTypes, &retValue);

  // TODO check retValue
}
