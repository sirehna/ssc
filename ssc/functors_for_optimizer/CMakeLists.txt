cmake_minimum_required (VERSION 2.6)
project (functors_for_optimizer)
set(SOURCES src/State.cpp
            src/StateGenerator.cpp
            src/Node.cpp
            src/Null.cpp
            src/Parameter.cpp
            src/Nullary.cpp
            src/Sum.cpp
            src/Binary.cpp
            src/N_ary.cpp
            src/Multiply.cpp
            src/Pow.cpp
            src/Divide.cpp
            src/Difference.cpp
            src/Serialize.cpp
            src/Ln.cpp
            src/Unary.cpp
            src/Sin.cpp
            src/Cos.cpp
            src/FunctorAlgebra.cpp
            src/Constant.cpp
            src/PiecewiseConstantFunctor.cpp
            src/PiecewiseLinearFunctor.cpp
            src/SplineFunctor.cpp
            src/PiecewiseParabolicFunctor.cpp
            src/GradHes.cpp
            src/StateGetter.cpp
            src/Grad.cpp
            src/Hes.cpp)

include_directories(inc)
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_SOURCE_DIR})
include_directories(${interpolation_INCLUDE_DIRS})

link_directories(${CMAKE_SOURCE_DIR}/external/bin)


#add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

#FIND_LIBRARY(${exception_handling_LIBRARIES} exception_handling ${CMAKE_CURRENT_BUILD_DIR}/../exception_handling)
#FILE(TO_CMAKE_PATH ${exception_handling_LIBRARIES} exception_handling_LIBRARIES)
#target_link_libraries(${PROJECT_NAME}_shared "${exception_handling_STATIC}")

add_subdirectory(unit_tests)

