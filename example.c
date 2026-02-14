#include <dlfcn.h>
#include <ffi.h>
#include <stdlib.h>

void dynamicCall(void (*fn)(void), int argc, void **argv, ffi_type **argTypes,
                 void *retValue) {
  ffi_cif cif;
  ffi_status status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, argc,
                                   &ffi_type_sint /* TODO */, argTypes);
  if (status != FFI_OK) {
    exit(1);
  }

  ffi_call(&cif, fn, retValue, argv);
}

int main(void) {
  ffi_type *argTypes[1];
  void *args[1];
  char *s;
  int (*_puts)(const char *);
  void *self = dlopen(NULL, RTLD_NOW);
  if (self == NULL) {
    return 1;
  }

  *(void **)(&_puts) = dlsym(self, "puts");

  argTypes[0] = &ffi_type_pointer;
  args[0] = &s;

  s = "Yolo dawg";
  ffi_arg retValue;
  dynamicCall((void (*)(void))_puts, 1, args, argTypes, &retValue);

  return 0;
}
