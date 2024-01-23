add_executable(Rational_test rational.h rational.cpp rational_test.cpp)
add_test(NAME RATIONAL_TEST COMMAND Rational_test)