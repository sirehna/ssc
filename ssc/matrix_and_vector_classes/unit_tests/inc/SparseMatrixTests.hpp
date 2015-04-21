#ifndef __SPARSE_MATRIX_TESTS__
#define __SPARSE_MATRIX_TESTS__

#include "gtest/gtest.h"
#include "ssc/matrix_and_vector_classes/SparseMatrix.hpp"
#include "ssc/random_data_generator/DataGenerator.hpp"

class SparseMatrixTests : public ::testing::Test
{
    protected:
        SparseMatrixTests() : a(ssc::random_data_generator::DataGenerator(95442))
                                {}
        virtual void SetUp();
        virtual void TearDown();
        ssc::random_data_generator::DataGenerator a;
};

#endif
