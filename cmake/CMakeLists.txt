configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CppCodegenConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/CppCodegenConfig.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CppCodegenConfig.cmake
        DESTINATION cmake)
