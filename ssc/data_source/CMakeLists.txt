cmake_minimum_required (VERSION 2.8.8)
project (data_source)

set(SRC DataSource.cpp
        DataSourceModule.cpp
        SignalContainer.cpp
        SignalContainerTypeLists.cpp
        TypeCoercion.cpp
        PhysicalQuantity.cpp
        DataSourceDrawer.cpp
        )

include_directories(${SSC_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME}_object OBJECT ${SRC})

add_subdirectory(unit_tests)
