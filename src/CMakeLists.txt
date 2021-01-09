add_library(string_exec string_exec.cpp)

add_library(conv conv/ConvUtils.cpp conv/BaseConv.cpp conv/VanillaConv.cpp conv/CgenConv.cpp conv/Im2colConv.cpp)

add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld string_exec dl)

install(TARGETS helloworld
		RUNTIME DESTINATION bin)
