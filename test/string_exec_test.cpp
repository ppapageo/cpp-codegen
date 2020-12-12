#include <gtest/gtest.h>
#include "string_exec.h"
#include "gtest/gtest-death-test.h"

TEST(StringExec, ClassTest) {
    StringCompile sc ;
	sc.append("../templates/test.txt");
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
