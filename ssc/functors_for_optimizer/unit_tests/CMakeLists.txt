# ------8<---[LINES TO MODIFY WHEN CHANGING MODULE]----->8-----
set(MODULE_UNDER_TEST functors_for_optimizer)
project (${MODULE_UNDER_TEST}_tests)
FILE(GLOB SRC src/NullTest.cpp
              src/StateGeneratorTest.cpp
              src/StateTest.cpp
              src/ParameterTest.cpp
              src/SumTest.cpp
              src/MultiplyTest.cpp
              src/PowTest.cpp
              src/DivideTest.cpp
              src/DifferenceTest.cpp
              src/SerializeTest.cpp
              src/LnTest.cpp
              src/SinTest.cpp
              src/CosTest.cpp
              src/FunctorAlgebraTest.cpp
              src/ConstantTest.cpp
              src/SimplifyTest.cpp
              src/SplineFunctorTest.cpp
              src/PiecewiseConstantFunctorTest.cpp
              src/PiecewiseLinearFunctorTest.cpp
              src/PiecewiseParabolicFunctorTest.cpp
              src/GradHesTest.cpp
              src/StateGetterTest.cpp
              src/SerializeReversePolishTest.cpp
              src/AbsTest.cpp
              src/SignTest.cpp
              src/SqrtTest.cpp
              src/StateAndParameterCounterTest.cpp)
# ------8<---------------------------------------------->8-----

# Include directories
include_directories(inc)
include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(SYSTEM ${YAMLCPP_INCLUDE_DIR})

add_library (${PROJECT_NAME} OBJECT ${SRC})


include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${random_data_generator_INCLUDE_DIRS})
