# SmallObject

SmallObject is a C++ library which optimizes memory allocation for small sized objects. The allocator is written such that it uses the least amount of memory overhead keeping performance in mind.

## Build and install

To build and install, just execute the following commands on your bash terminal. Installation will require sudo permission. By default, the install path is set to _/usr/_. After installation, the dynamic library __libsmobjall.so__ will be set up.

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

As a reference, you can look at any of the examples codes. For compilation, refer to the Makefile in examples/. In simple words, you need to do the following:
* Include the __small_obj_base.hh__ header in your source code and Call __SmallObjAllocator::createSmallObjAllocator(numChunkBytes, SmallObjSizeLimit)__ right at the beginning.

```c++
#include <small_obj_base.hh>

constexpr std::size_t numChunkBytes = 64;
constexpr std::size_t SmallObjSizeLimit = 16;
...

int main ()
{
    SmallObjAllocator::createSmallObjAllocator(numChunkBytes, SmallObjSizeLimit);
    ...;

    return 0;
}
```

* Any small object class needs to inherit from __SmallObjBase<>__. The template parameter is defaulted to use __SmallObjAllocator__.

```c++
class Test : public SmallObjBase<>
```

* Compile your source code using -std=c++11 and link it by using _-lsmobjall_.

## Have fun