#include <cstdio>
#include <cstdlib> // for exit()
#include <dlfcn.h> // for dlopen()

#include "ffi.h"

void dynamicCall(void (*fn)(void), int argc, void **argv, ffi_type **argTypes,
                 void *retValue, ffi_type *retType) {
  ffi_cif cif;
  ffi_status status =
      ffi_prep_cif(&cif, FFI_DEFAULT_ABI, argc, retType, argTypes);
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

  int (*_puts)(const char *) = NULL;
  // Hack to satisfy -Wpedantic:
  // https://pubs.opengroup.org/onlinepubs/009695399/functions/dlsym.html
  *(void **)(&_puts) = dlsym(self, "puts");
  if (_puts == NULL) {
    fprintf(stderr, "Failed to dlsym()\n");
    return 1;
  }

  const char *arg = "Hello from libffi!";
  void *args[1] = {(void *)&arg};
  ffi_type *argTypes[1] = {&ffi_type_pointer};

  // Caller must ensure this is big enough to hold the return value
  ffi_arg retValue;
  dynamicCall((void (*)(void))_puts, 1, args, argTypes, &retValue,
              &ffi_type_sint);

  // TODO check retValue
}
