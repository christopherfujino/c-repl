## Dependencies

While this project depends on [libffi](https://github.com/libffi/libffi),
the [configure.sloth](/configure.sloth) script will fetch and compile it. The build dependencies
are:

```
apt-get install \
    autoconf \
    automake \
    autotools-dev \
    libtool \
    texinfo
```

To run the configure script, you will need [slothscript](https://github.com/christopherfujino/slothscript).

## Building

```bash
./configure.sloth
```
