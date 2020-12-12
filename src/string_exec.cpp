#include "string_exec.h"
StringCompile::StringCompile(){
	this->program<<"";
	std::string cmpflags;
	file2string("../cmpflags.txt", &cmpflags);
	this->cmp_cmd<<"${CXX} -fPIC -shared"<<cmpflags<<" -o tmpfiles/libtmp.so tmpfiles/tmp.cpp";
}
void StringCompile::save(){
	system("mkdir -p tmpfiles");
	std::string cppname = "";
	cppname = "tmpfiles/tmp.cpp";
	std::ofstream out(cppname.c_str());
    out << this->program.str();
    out.close();
}

void StringCompile::print(){
	std::cout<<this->program.str()<<"\n";
}
void StringCompile::clear(){
	this->program.str(std::string());
	this->program.clear();
}

void StringCompile::append(std::string str){
	this->program<<str<<"\n";
}
void StringCompile::append(const char* file){
	std::string tmpstring;
	file2string(file,&tmpstring);
	this->program<<tmpstring<<"\n";
}
void StringCompile::file2string(const char* file, std::string* string){
	std::ifstream t(file);
	if (!t){
		std::cout << "Failed to open file: "<< file <<"\n";
		exit(1);
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	(*string)=buffer.str();
}
void StringCompile::replace(const std::string& from, const std::string& to){
	std::string str = program.str();
	if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
	this->program.str(str);
}
void StringCompile::compile(int verbose){
	if(verbose==1)	std::cout<<this->cmp_cmd.str()<<"\n";
	system(this->cmp_cmd.str().c_str());
}
void StringExec::openlib(){
	std::string filename = "./tmpfiles/libtmp.so";
	this->fnhandle = dlopen(filename.c_str(),RTLD_LAZY);
	if (!this->fnhandle) {
		std::cerr << "Cannot load library: " << dlerror() << '\n';
		exit(1);
	}
}
void StringExec::loadlib(const char* libname){
	*(void**)(&this->func) = dlsym(this->fnhandle, libname);
	if (!this->func){
		std::cerr << "Cannot load library: " << dlerror() << '\n';
		exit(1);
	}
	
}
void StringExec::closelib(){
	dlclose(this->fnhandle);
}
