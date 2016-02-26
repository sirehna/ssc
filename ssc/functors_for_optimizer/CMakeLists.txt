cmake_minimum_required (VERSION 2.6)
project (functors_for_optimizer)
set(SOURCES State.cpp
            StateGenerator.cpp
            Node.cpp
            Null.cpp
            Parameter.cpp
            Nullary.cpp
            Sum.cpp
            Binary.cpp
            N_ary.cpp
            Multiply.cpp
            Pow.cpp
            Divide.cpp
            Difference.cpp
            Serialize.cpp
            Ln.cpp
            Unary.cpp
            Sin.cpp
            Cos.cpp
            FunctorAlgebra.cpp
            Constant.cpp
            PiecewiseConstantFunctor.cpp
            PiecewiseLinearFunctor.cpp
            SplineFunctor.cpp
            PiecewiseParabolicFunctor.cpp
            GradHes.cpp
            StateGetter.cpp
            Abs.cpp
            Sign.cpp
            FunctionMatrix.cpp
            SerializeReversePolish.cpp
            StateAndParameterCounter.cpp
            )

include_directories(inc)
include_directories(${SSC_INCLUDE_DIRS})

# Using C++ 2011
# The -std=c++0x option causes g++ to go into 'strict ANSI' mode so it doesn't declare non-standard functions
# (and _stricmp() is non-standard - it's just a version of strcmp() that's case-insensitive).
# Use -std=gnu++0x instead.
IF (NOT(MSVC))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
ENDIF()

#link_directories(${CMAKE_SOURCE_DIR}/external/bin)


#add_library(${PROJECT_NAME}_shared SHARED ${SOURCES})
#add_library(${PROJECT_NAME}_static STATIC ${SOURCES})
add_library(${PROJECT_NAME}_object OBJECT ${SOURCES})

set(${PROJECT_NAME}_INCLUDE_DIRS     ${${PROJECT_NAME}_SOURCE_DIR}/inc                                                                               CACHE PATH     "Path to ${PROJECT_NAME}'s include directory")
set(${PROJECT_NAME}_LIBRARIES        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}         CACHE FILEPATH "${PROJECT_NAME}'s shared library")
set(${PROJECT_NAME}_STATIC_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_NAME}_static${CMAKE_STATIC_LIBRARY_SUFFIX}  CACHE FILEPATH "${PROJECT_NAME}'s static library")
set(${PROJECT_NAME}_FOUND            TRUE                                                                                                            CACHE BOOL     "Is ${PROJECT_NAME} available to other modules?")

add_subdirectory(unit_tests)

