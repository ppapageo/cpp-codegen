cpp-codegen [![CI](https://github.com/ppgpn/cpp-codegen/workflows/CI/badge.svg)](https://github.com/ppgpn/cpp-codegen/actions)
===========
Cpp-codegen is a library that generates, compiles and runs C++ code at runtime. 

  * Performs code specialization at runtime (jit compilation)
  * Control over individual compilation parameters
  * Can produce more optimized code
  
The library is in experimental/development stage. 

How it works
-----
In a nutshell, at run time, the compile shell command and then the dynamic linking loader are called through the C interfaces, system() and dlsym() respectively.

Instructions
---------

Below there are instructions to build and use the library, as well as an example demonstrating potential performance benefits.

Requirements
-----------
gtest, cmake, libopenblas-dev

Build
-----------
```bash
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=<your/installation/path> .. 
make
make install
```
Run simple example
-----------
```bash
export CXX=g++ //or your favorite C++ compiler
cd <your/installation/path>/bin
helloworld
```
Run Convolution example
-------------------
To demonstrate the potential benefits to performance, two optimized functions for the convolution operation are generated
* 1. Substitute the loop boundary variables with their runtime values

* 2. Completely eliminate the 2 innermost loops traversing the kernel

Performance comparison against Normal Convolution and Im2col-Gemm Convolution

```bash
export CXX=g++ //or your favorite C++ compiler
cd <your/installation/path>/bin
./time_conv <input channel> <input rows> <input cols> <output channel> \
		<filter rows> <filter cols> <stride> <pad> <threads>
```

Specifically with Alexnet's conv2 layer:
```bash
./time_conv 96 27 27 256 5 5 1 1 1
./time_conv 96 27 27 256 5 5 1 1 2
```

|| 1 thread  | 2 threads  |
|---|---|---|
| Normal|	0.378811s  | 0.223168s  |
| Im2col|	0.018317s  | 0.020192s |
| Cgen-loop|	0.180567s  | 0.091323s  |
| Cgen-unroll|	0.088904s  | 0.045188s  |

In this case code specialization enables performance comparable to the widely used im2col-gemm implementations without their memory overheads


Create your own program
---------
### Step 1. Create the C++ file: 

This can be achieved by using plain strings or making a template:

Case 1. String
  ```C++
// src/mymain.cpp
...
	StringExec se ;
	std::string str;
	str.append("extern \"C\" int func()\n");
	str.append("{\n");
	str.append("return 5+5;\n");
	str.append("}\n");
 
	se.append(str);
	se.save();
	se.compile();
...
 ```
Case 2. Template
* Create a template
 ```C++
 // templates/mytemplate.txt
extern "C" int func()
{
	return $hook;
}
 ```
* On the main file append code from template  and replace hooks if any
 ```C++
 // src/mymain.cpp
...
	StringExec se ;
	se.append("../templates/test.txt");
	se.replace("$hook","5+5");
	se.save();
	se.compile();
...
 ```
 ### Step 2. Compile and run the function: 
 
  ```C++
 // src/mymain.cpp
...
	se.openlib();
	se.loadlib("func");
	se.func();
	se.closelib();
...
 ```
 
 TODO
----

  * [ ] Fix possible name conflict of same named generated libraries used by different programs:
    * [ ] Use unique directory name suffix per programm or function call

  * [ ] More fine grained compilation parameters:
    * [ ] Define compilation parameters at object init as strings
