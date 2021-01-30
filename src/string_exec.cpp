#include "string_exec.h"

StringExec::StringExec(const char* cmpflagfile, const char* sav_dir_arg , const char* sav_name_arg ){
	this->program<<"";
	std::string cmpflags;
	file2string(cmpflagfile, &cmpflags);
	sav_dir = sav_dir_arg;
	sav_name = sav_name_arg;
	this->cmp_cmd<<"${CXX} -fPIC -shared"<<cmpflags<<" -o "<< sav_dir<<"/"<<"lib"<<sav_name<<".so "<<sav_dir<<"/"<<sav_name<<".cpp";
}
StringExec::~StringExec(){
	this->closelib();
}
void StringExec::save(){
	std::string cmd = "mkdir -p " + sav_dir;
	system(cmd.c_str());
	std::string cppname = "";
	cppname = sav_dir+"/"+sav_name+".cpp";
	std::ofstream out(cppname.c_str());
    out << this->program.str();
    out.close();
}

void StringExec::print(){
	std::cout<<this->program.str()<<"\n";
}
void StringExec::clear(){
	this->program.str(std::string());
	this->program.clear();
}

void StringExec::append_str(std::string str){
	this->program<<str<<"\n";
}
void StringExec::append_file(const char* file){
	std::string tmpstring;
	file2string(file,&tmpstring);
	this->program<<tmpstring<<"\n";
}
void StringExec::file2string(const char* file, std::string* string){
	std::ifstream t(file);
	if (!t){
		std::cerr << "Failed to open file: "<< file <<"\n";
		exit(1);
	}
	std::stringstream buffer;
	buffer << t.rdbuf();
	(*string)=buffer.str();
}
void StringExec::replace(const std::string& from, const std::string& to){
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
void StringExec::compile(int verbose){
	if(verbose==1)	std::cout<<this->cmp_cmd.str()<<"\n";
	system(this->cmp_cmd.str().c_str());
}
void StringExec::openlib(const char* filename){
	this->fnhandle = dlopen(filename,RTLD_LAZY);
	if (!this->fnhandle) {
		std::cerr << dlerror() << '\n';
		exit(1);
	}
}
void StringExec::loadlib(const char* libname){
	*(void**)(&this->func) = dlsym(this->fnhandle, libname);
	if (!this->func){
		std::cerr << dlerror() << '\n';
		exit(1);
	}
	
}
void StringExec::closelib(){
	dlclose(this->fnhandle);
}
