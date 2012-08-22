#ifndef __SPARSE_VECTOR_TESTS__
#define __SPARSE_VECTOR_TESTS__

#include "gtest/gtest.h"
#include "SparseVector.hpp"
#include "DataGenerator.hpp"

class SparseVectorTests : public ::testing::Test
{
    protected:
        SparseVectorTests() : a(DataGenerator(95442))
                                {}
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif
