# SmallObject

SmallObject is a C++ library which optimizes memory allocation for small sized objects. The allocator is written such that it uses the least amount of memory overhead keeping performance in mind.

## Build and install

To build and install, just execute the following commands on your bash terminal. Installation will require sudo permission. By default the install path is set to _/usr/local/_. If this is not your default path for headers and libraries, please change the path or add these to your environment variable. After installation, the dynamic library libsmobjall.so will be set up.

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

* Any small object class needs to inherit from __SmallObjBase<>__. The template parameter is defaulted to use SmallObjAllocator. You can also use your own allocator by inheriting from __SmallObjBase<YourAllocator>__.

```c++
class Test : public SmallObjBase<>
```
or
```c++
class Test : public SmallObjBase<YourAllocator>
```

* Compile your source code using -std=c++11 and link it by using -lsmobjall.

## Have fun