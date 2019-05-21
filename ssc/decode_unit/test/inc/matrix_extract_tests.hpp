#ifndef __SIR_MATRIX_EXTRACT_TEST__
#define __SIR_MATRIX_EXTRACT_TEST__


#include "gtest/gtest.h"
#include "matrix.h"
#include <vector>

using namespace math;

class matrix_test : public ::testing::Test
{
    protected:
        matrix_test() : test_matrix_double(matrix<double>(6,5)), test_matrix_float(matrix<float>(6,5)), test_matrix_int(matrix<int>(6,5)), test_matrix_size_t(matrix<size_t>(6,5)) {}
        virtual void SetUp();
        virtual void TearDown();
        void SetUpDoubleMatrix();
        void SetUpFloatMatrix();
        void SetUpIntMatrix();
        void SetUpSizeTMatrix();

        matrix<double> test_matrix_double;
        matrix<float> test_matrix_float;
        matrix<int> test_matrix_int;
        matrix<size_t> test_matrix_size_t;


        template <class T>
        bool vectors_are_equal(const std::vector<T>& vec1, const std::vector<T>& vec2)
        {
            const size_t n = vec1.size();
            if (n != vec2.size()) return false;
            bool are_equal = true;
            size_t i = 0;
            while ((i < n) && are_equal)
            {
                are_equal = are_equal || (vec1.at(i) == vec2.at(i));
                ++i;
            }
            return are_equal;
        }
};

#endif
