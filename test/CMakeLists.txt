#add_executable(Sample_test main.cpp sampleTest.cpp)

#target_link_libraries(Sample_test GTest::GTest GTest::Main pthread )

#add_test(NAME Sample_test
#	COMMAND Sample_test)
add_executable(string_exec_test main.cpp string_exec_test.cpp)

target_link_libraries(string_exec_test GTest::GTest GTest::Main pthread string_exec dl)

add_test(NAME string_exec_test
	COMMAND string_exec_test)
