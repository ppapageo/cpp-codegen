#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <dlfcn.h>
#include <streambuf>
#include <sstream>
class StringCompile
{
	std::stringstream program;
	std::stringstream cmp_cmd;
	public:
	StringCompile();
	void append(std::string str);
	void append(const char* file);
	void file2string(const char* file, std::string* string);
	void replace(const std::string& from, const std::string& to);
	void save();
	void print();
	void compile(int verbose=1);
	void clear();
};
class StringExec
{
	void* fnhandle;

	public:
	void (*func)(...);
	void openlib();
	void loadlib(const char* libname);
	void closelib();
};
