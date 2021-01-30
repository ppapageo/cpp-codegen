#include "string_exec.h"
int main( int argc, char** argv ){
	StringExec se;
	se.append_file("../templates/helloworld.txt");
	se.replace("$string_hook","Hello World");
	se.save();
	se.compile();

	se.openlib();
	se.loadlib("func");
	se.func();
	se.closelib();


}	
