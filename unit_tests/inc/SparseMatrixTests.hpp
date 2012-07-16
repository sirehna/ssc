#ifndef __SPARSE_MATRIX_TESTS__
#define __SPARSE_MATRIX_TESTS__

#include "gtest/gtest.h"
#include "SparseMatrix.hpp"
#include "DataGenerator.hpp"

class SparseMatrixTests : public ::testing::Test
{
    protected:
        SparseMatrixTests() : a(DataGenerator(95442))
                                {}
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif
