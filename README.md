cpp-codegen
===========
cpp-codegen generates compiles and runs C++ code at runtime.

  * It is in experimental stage 
  * Used for code specialization tasks
  * Functionaly JIT compilation
  
Requirements
-----------
gtest, cmake

Build
-----------
```bash
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=<your/installation/path> .. 
make
make install
```
Run example
-----------
```bash
cd <your/installation/path>/bin
helloworld
```
