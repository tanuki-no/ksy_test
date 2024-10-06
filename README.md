# Objectives
This is a simple KaiTai Struct Compiler test where I use Teltonica protocol as a sample to generate a small test app taking either binary encoded string or JSON structure to perform 2-way Teltonica protocol translation.
# Requirements
1. [Kaitai Struct Compiler](https://github.com/kaitai-io/kaitai_struct_compiler).
2. [CMake](https://cmake.org/).
3. [JSON CPP](dev-libs/jsoncpp).
4. [Kaitai Struct: runtime library for C++/STL](https://github.com/kaitai-io/kaitai_struct_cpp_stl_runtime).
5. Any working C compiler. The sample works with both GCC and CLang stuff.
# Compiling
I hope you know what to do with cmake. If not, do something like this:
```
cd ksy_test
mkdir build
cd build
cmake ..
make
```
