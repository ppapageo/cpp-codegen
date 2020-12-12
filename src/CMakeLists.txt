add_library(string_exec string_exec.cpp)

add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld string_exec dl)

install(TARGETS helloworld
		RUNTIME DESTINATION bin)
