add_library(string_exec SHARED string_exec.cpp)
install(TARGETS string_exec
	LIBRARY DESTINATION lib)

add_library(conv conv/ConvUtils.cpp conv/BaseConv.cpp conv/VanillaConv.cpp conv/CgenConv.cpp conv/CgenUnrollConv.cpp conv/Im2colConv.cpp)

add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld string_exec dl)

add_executable(time_conv conv/time_conv.cpp)

target_link_libraries(time_conv conv string_exec dl openblas)
