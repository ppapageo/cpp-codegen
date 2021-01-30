#include <gtest/gtest.h>
#include "string_exec.h"
#include "gtest/gtest-death-test.h"

TEST(StringExec, ClassTest) {
    StringExec se;
	se.append_file("../templates/test.txt");
	se.replace("$string_hook","1+2");
	se.save();
	se.compile(0);

	se.openlib();
	se.loadlib("func");
	int (*test)();
	test = (int(*)())se.func;
	int test_res = test();
	se.closelib();
	EXPECT_EQ(3,test_res);
}
TEST(StringExec, FailFile2StringTest){
	StringExec se;
	std::string string;
    EXPECT_EXIT({
			se.file2string("doesnotexist.txt",&string);
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
