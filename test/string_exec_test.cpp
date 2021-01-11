#include <gtest/gtest.h>
#include "string_exec.h"
#include "gtest/gtest-death-test.h"

TEST(StringExec, ClassTest) {
    StringCompile sc ;
	sc.append_file("../templates/test.txt");
	sc.replace("$string_hook","1+2");
	sc.save();
	sc.compile(0);

    StringExec se;
	se.openlib();
	se.loadlib("func");
	int (*test)();
	test = (int(*)())se.func;
	int test_res = test();
	se.closelib();
	EXPECT_EQ(3,test_res);
}
TEST(StringExec, FailFile2StringTest){
	StringCompile sc;
	std::string string;
    EXPECT_EXIT({
			sc.file2string("doesnotexist.txt",&string);
			},::testing::ExitedWithCode(1), "Failed to open file: doesnotexist.txt");
}

TEST(StringExec, NoLibTest){
    StringExec se;
	EXPECT_EXIT({
			se.openlib("doesnotexist.so");
			},::testing::ExitedWithCode(1), "doesnotexist.so: cannot open shared object file: No such file or directory");
}

TEST(StringExec, NoFuncTest){
    StringExec se;
	se.openlib();
	EXPECT_EXIT({
			se.loadlib("doesnotexist");
			},::testing::ExitedWithCode(1), "/tmp/cpp-codegen/libtmp.so: undefined symbol: doesnotexist");
}
