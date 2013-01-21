cmake_minimum_required (VERSION 2.6)
project (AllocatorProto)
ADD_DEFINITIONS("-std=gnu++0x")

include_directories(external/inc)

include_directories(SYSTEM ../CoinIpopt/include/coin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi -Woverloaded-virtual -Weffc++ -pedantic -pedantic-errors -Wextra  -Wall -Wunused-function  -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  -Wvariadic-macros -fno-common -Wformat=2 -Winit-self -Wpointer-arith -Wlarger-than-65500 -Wmissing-declarations -Wmissing-format-attribute -Wno-deprecated -Wredundant-decls -Wsign-compare -Wstrict-aliasing=2 -Wundef -Wwrite-strings -Wfatal-errors -Werror")

enable_testing()
set(GTEST_ROOT ~/work/c++0x/gtest-1.6.0/build)
find_package(GTest REQUIRED)
find_package (Threads)
link_directories(${CMAKE_SOURCE_DIR}/external/bin)
add_executable(run_all_tests test.cpp Pow.cpp StateNode.cpp)
target_link_libraries(run_all_tests ${GTEST_BOTH_LIBRARIES})
target_link_libraries (run_all_tests ${CMAKE_THREAD_LIBS_INIT}
 state exception_handling)
add_executable(test Fx.cpp
                    LinearInterpolator.cpp
                    main.cpp
                    Thruster.cpp)
target_link_libraries(test state exception_handling)
