#include <dlfcn.h>
#include <ffi.h>

int main(void) {
  ffi_cif cif;
  ffi_type *args[1];
  void *values[1];
  char *s;
  ffi_arg rc;
  int (*_puts)(const char *);

  {
    void *self = dlopen(NULL, RTLD_NOW);
    if (self == NULL) {
      return 1;
    }

    *(void **)(&_puts) = dlsym(self, "puts");
  }

  args[0] = &ffi_type_pointer;
  values[0] = &s;

  if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint, args) == FFI_OK) {
    s = "Hello World!";
    ffi_call(&cif, (void (*)(void))_puts, &rc, values);

    s = "This is cool!";
    ffi_call(&cif, (void (*)(void))_puts, &rc, values);
  }

  return 0;
}
