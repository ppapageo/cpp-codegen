#include "string_exec.h"
int main( int argc, char** argv ){
	StringCompile sc ;
	sc.append("../templates/helloworld.txt");
	sc.replace("$string_hook","Hello World");
	sc.save();
	sc.compile();

	StringExec se;
	se.openlib();
	se.loadlib("func");
	se.func();
	se.closelib();


}	
