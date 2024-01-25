add_executable(cstring_test cstring_test.cpp cstring.h cstring.cpp)
add_test(NAME CSTRING_TEST COMMAND cstring_test)