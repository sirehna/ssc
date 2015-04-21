#ifndef __SPARSE_VECTOR_TESTS__
#define __SPARSE_VECTOR_TESTS__

#include "gtest/gtest.h"
#include "ssc/matrix_and_vector_classes/inc/SparseVector.hpp"
#include "ssc/random_data_generator/DataGenerator.hpp"

class SparseVectorTests : public ::testing::Test
{
    protected:
        SparseVectorTests() : a(ssc::random_data_generator::DataGenerator(95442))
                                {}
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif
