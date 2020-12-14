cpp-codegen
===========
cpp-codegen is a library that generates compiles and runs C++ code at runtime.

  * It is in experimental stage 
  * Used for code specialization tasks
  * Essentially JIT compilation
  
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
Run simple example
-----------
```bash
export CXX=g++ //or your favourite C++ compiler
cd <your/installation/path>/bin
helloworld
```
Create your own programm
---------
### Step 1. Create the C++ file: 

This can be achieved by using plain strings or making a template:
1. String
  ```C++
// src/mymain.cpp
...
	StringCompile sc ;
	std::string str;
	str.append("extern \"C\" int func()\n");
	str.append("{\n");
	str.append("return 5+5;\n");
	str.append("}\n");
 
	sc.append(str);
	sc.save();
	sc.compile();
...
 ```
2. Template
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
	StringCompile sc ;
	sc.append("../templates/test.txt");
	sc.replace("$hook","5+5");
	sc.save();
	sc.compile();
...
 ```
 ### Step 2. Compile and run the function: 
 
  ```C++
 // src/mymain.cpp
...
	StringExec se;
	se.openlib();
	se.loadlib("func");
	se.func();
	se.closelib();
...
 ```
 
