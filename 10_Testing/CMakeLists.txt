cmake_minimum_required(VERSION 3.16)
project(buf)
include(CTest)
add_compile_options(-std=c99 -Wall -Wextra -Werror -O3 -g3 --coverage)

add_library(buf buf.c buf.h)

add_executable(tests tests.c)

target_link_libraries(tests buf gcov)

add_custom_target(
        clean_generates
	COMMAND rm -rf tests libbuf.a Testing DartConfiguration.tcl CTestTestfile.cmake CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
)

add_custom_target(
	testing
	COMMAND ctest
	COMMAND ctest -T Coverage
)

add_test(NAME "buf_init_tests" COMMAND tests 1)
add_test(NAME "buf_clear_tests" COMMAND tests 2)
add_test(NAME "buf_push_tests" COMMAND tests 3)
add_test(NAME "buf_capacity_test" COMMAND tests 4)
add_test(NAME "buf_pop_test" COMMAND tests 5)
