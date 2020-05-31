# SmallObject

SmallObject is a C++ library which optimizes memory allocation for small sized objects. The allocator is written such that it uses the least amount of memory overhead keeping performance in mind.

## Build and install

To build and install, just execute the following commands on your bash terminal. Installation will require sudo permission. By default the install path is set to /usr/local/. If this is not your default path for headers and libraries, please change the path or add these to your environment variable. After installation, the dynamic library libsmobjall.so will be set up.

```bash
make
make install
```

## Build examples

To build the examples, just execute the following.

```bash
make examples
```

## Usage

As a reference, you can look at any of the examples codes. For compilation, refer to the Makefile in exmaples/. In simple words, you need to do the following:
* Include the *small_obj_base.hh* header in your source code.
* Call *SmallObjAllocator::getSmallObjAllocator(numChunkBytes, SmallObjSizeLimit)* with your desirable parameter values.
* Any small object class needs to inherit from SmallObjBase<>.
* Compile your source code and link it by using -lsmobjall.

## Have fun