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
            src/FunctionMatrix.cpp
            src/SerializeReversePolish.cpp)

include_directories(inc)
include_directories(${exception_handling_INCLUDE_DIRS})
include_directories(${test_macros_SOURCE_DIR})
include_directories(${interpolation_INCLUDE_DIRS})

#link_directories(${CMAKE_SOURCE_DIR}/external/bin)


#add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
#add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)

