# CMake generated Testfile for 
# Source directory: /workspaces/OOP1/lab3
# Build directory: /workspaces/OOP1/lab3/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MyProjectTests "/workspaces/OOP1/lab3/build/tests")
set_tests_properties(MyProjectTests PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/OOP1/lab3/CMakeLists.txt;47;add_test;/workspaces/OOP1/lab3/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
