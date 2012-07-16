#include "SparseMatrixTests.hpp"
#include "Exception.hpp"
#include "test_macros.hpp"
#include <algorithm> // For sort

void SparseMatrixTests::SetUp()
{
}

void SparseMatrixTests::TearDown()
{
}

TEST_F(SparseMatrixTests, there_should_exist_a_sparse_matrix_class)
{
    SparseMatrix A;
    SparseMatrix B(1365);
}

TEST_F(SparseMatrixTests, should_be_able_to_set_and_retrieve_an_element)
{
    const size_t nb_of_trials = 100;
    for (size_t i = 0 ; i < nb_of_trials ; ++i)
    {
        SparseMatrix A(3);
        const size_t idx1 = a.random<size_t>()();
        const size_t idx2 = a.random<size_t>()();
        const size_t idx3 = a.random<size_t>().greater_than(idx1)();
        const size_t idx4 = a.random<size_t>()();
        const size_t idx5 = a.random<size_t>().greater_than(idx3)();
        const size_t idx6 = a.random<size_t>()();
        const double val1 = a.random<double>()();
        const double val2 = a.random<double>()();
        const double val3 = a.random<double>()();
        A.add_element_in_row_order(idx1,idx2, val1);
        A.add_element_in_row_order(idx3,idx4, val2);
        A.add_element_in_row_order(idx5,idx6, val3);
        EXPECT_EQ(val1, A.get(idx1,idx2));
        EXPECT_EQ(val2, A.get(idx3,idx4));
        EXPECT_EQ(val3, A.get(idx5,idx6));
    }
}

TEST_F(SparseMatrixTests, should_throw_an_exception_when_adding_an_element_twice_in_the_same_place)
{
    SparseMatrix A(3);
    const size_t idx1 = a.random_size_t();
    const size_t idx2 = a.random_size_t();
    A.add_element_in_row_order(idx1,idx2, a.random_double());
    EXPECT_THROW(A.add_element_in_row_order(idx1,idx2, a.random_double()),Exception);
}

TEST_F(SparseMatrixTests, should_throw_an_exception_when_inserting_an_element_not_in_row_order)
{
    SparseMatrix A(2);
    const size_t idx = a.random_size_t();
    A.add_element_in_row_order(idx+1,idx+2,a.random_double());
    EXPECT_THROW(A.add_element_in_row_order(idx,idx,a.random_double()), Exception);
}

TEST_F(SparseMatrixTests, elements_which_are_not_present_in_the_matrix_are_set_to_zero_by_default)
{
    SparseMatrix A(1);
    EXPECT_EQ(0, A.get(a.random_size_t(),a.random_size_t()));
}

TEST_F(SparseMatrixTests, should_throw_an_exception_when_adding_too_many_elements_to_an_array)
{
    SparseMatrix A(1);
    const size_t idx = a.random_size_t();
    A.add_element_in_row_order(idx,idx, a.random_double());
    EXPECT_THROW(A.add_element_in_row_order(idx+1,idx+1, a.random_double()),Exception);
}

TEST_F(SparseMatrixTests, should_be_able_to_retrieve_all_elements_all_line_indexes_and_all_column_indexes)
{
    const size_t nb_of_values = a.random_size_t(1,20);
    std::vector<size_t> idx = a.vector_of_random_size_ts(nb_of_values, 1, 400*nb_of_values);
    std::sort(idx.begin(), idx.end());
    SparseMatrix A(nb_of_values);
    for (size_t i = 0 ; i < nb_of_values ; ++i)
    {
        A.add_element_in_row_order(idx.at(i), idx.at(i), a.random_double());
    }
    SparseMatrix B(3);
    B.add_element_in_row_order(15, 9, 654);
    B.add_element_in_row_order(68, 620, 87654);
    B.add_element_in_row_order(647, 2, 69543);
    const size_t *c1 = B.get_columns();
    const size_t *l1 = B.get_rows();
    const double *v1 = B.get_values();
    EXPECT_EQ(15,  l1[0]);
    EXPECT_EQ(68,  l1[1]);
    EXPECT_EQ(647,  l1[2]);
    EXPECT_EQ(9, c1[0]);
    EXPECT_EQ(620, c1[1]);
    EXPECT_EQ(2, c1[2]);
    EXPECT_EQ(654, v1[0]);
    EXPECT_EQ(87654, v1[1]);
    EXPECT_EQ(69543, v1[2]);
}

TEST_F(SparseMatrixTests, should_have_an_operator_to_multiply_a_sparse_matrix_by_a_scalar_value)
{
    SparseMatrix A(3);
    A.add_element_in_row_order(15, 9, 654);
    A.add_element_in_row_order(68, 620, 87654);
    A.add_element_in_row_order(647, 2, 69543);
    SparseMatrix B(3*A);
    const double *v1 = B.get_values();
    EXPECT_EQ(3*654, v1[0]);
    EXPECT_EQ(3*87654, v1[1]);
    EXPECT_EQ(3*69543, v1[2]);
}


TEST_F(SparseMatrixTests, should_have_a_function_to_multiply_a_sparse_matrix_by_a_scalar_value_in_place)
{
    SparseMatrix A(3);
    A.add_element_in_row_order(15, 9, 654);
    A.add_element_in_row_order(68, 620, 87654);
    A.add_element_in_row_order(647, 2, 69543);
    A.multiply_in_place_by(4);
    const double *v = A.get_values();
    EXPECT_EQ(4*654, v[0]);
    EXPECT_EQ(4*87654, v[1]);
    EXPECT_EQ(4*69543, v[2]);
}


TEST_F(SparseMatrixTests, should_be_able_to_add_two_sparse_matrices)
{
    SparseMatrix A(4);
    A.add_element_in_row_order(0, 0, .654);
    A.add_element_in_row_order(0, 50, 876.54);
    A.add_element_in_row_order(27, 2, 695.43);
    A.add_element_in_row_order(270, 800, 69.543);
    SparseMatrix B(3);
    B.add_element_in_row_order(0, 50, .54);
    B.add_element_in_row_order(27, 2, 0.87);
    B.add_element_in_row_order(400, 4000, 8722.654);
    SparseMatrix C(A+B);
    const size_t *c = C.get_columns();
    const size_t *l = C.get_rows();
    const double *v = C.get_values();
    ASSERT_EQ(0, l[0]);
    ASSERT_EQ(0, l[1]);
    ASSERT_EQ(27, l[2]);
    ASSERT_EQ(270, l[3]);
    ASSERT_EQ(400, l[4]);
    ASSERT_EQ(0, c[0]);
    ASSERT_EQ(50, c[1]);
    ASSERT_EQ(2, c[2]);
    ASSERT_EQ(800, c[3]);
    ASSERT_EQ(4000, c[4]);
    EXPECT_EQ(0.654, v[0]);
    EXPECT_DOUBLE_EQ(877.08, v[1]);
    EXPECT_EQ(696.3, v[2]);
    EXPECT_EQ(69.543, v[3]);
    EXPECT_EQ(8722.654, v[4]);
}


TEST_F(SparseMatrixTests, should_have_a_method_to_initialize_a_matrix_with_the_sum_of_two_matrices)
{
    SparseMatrix A(4);
    A.add_element_in_row_order(0, 0, .654);
    A.add_element_in_row_order(0, 50, 876.54);
    A.add_element_in_row_order(27, 2, 695.43);
    A.add_element_in_row_order(270, 800, 69.543);
    SparseMatrix B(3);
    B.add_element_in_row_order(0, 50, .54);
    B.add_element_in_row_order(27, 2, 0.87);
    B.add_element_in_row_order(400, 4000, 8722.654);
    SparseMatrix C(A,B);
    const size_t *c = C.get_columns();
    const size_t *l = C.get_rows();
    const double *v = C.get_values();
    ASSERT_EQ(0, l[0]);
    ASSERT_EQ(0, l[1]);
    ASSERT_EQ(27, l[2]);
    ASSERT_EQ(270, l[3]);
    ASSERT_EQ(400, l[4]);
    ASSERT_EQ(0, c[0]);
    ASSERT_EQ(50, c[1]);
    ASSERT_EQ(2, c[2]);
    ASSERT_EQ(800, c[3]);
    ASSERT_EQ(4000, c[4]);
    EXPECT_EQ(0.654, v[0]);
    EXPECT_DOUBLE_EQ(877.08, v[1]);
    EXPECT_EQ(696.3, v[2]);
    EXPECT_EQ(69.543, v[3]);
    EXPECT_EQ(8722.654, v[4]);

}

TEST_F(SparseMatrixTests, no_memory_leaks_when_summing_an_empty_matrix)
{
    SparseMatrix A(4);
    A.add_element_in_row_order(0, 0, .654);
    A.add_element_in_row_order(0, 50, 876.54);
    A.add_element_in_row_order(27, 2, 695.43);
    A.add_element_in_row_order(270, 800, 69.543);
    SparseMatrix B(0);

    SparseMatrix C(A,B);
    SparseMatrix D = A + B;
    const size_t *c1 = C.get_columns();
    const size_t *l1 = C.get_rows();
    const double *v1 = C.get_values();
    const size_t *c2 = C.get_columns();
    const size_t *l2 = C.get_rows();
    const double *v2 = C.get_values();
    ASSERT_EQ(0, l1[0]);
    ASSERT_EQ(0, l1[1]);
    ASSERT_EQ(27, l1[2]);
    ASSERT_EQ(270, l1[3]);
    ASSERT_EQ(0, c1[0]);
    ASSERT_EQ(50, c1[1]);
    ASSERT_EQ(2, c1[2]);
    ASSERT_EQ(800, c1[3]);
    EXPECT_EQ(0.654, v1[0]);
    EXPECT_DOUBLE_EQ(876.54, v1[1]);
    EXPECT_EQ(695.43, v1[2]);
    EXPECT_EQ(69.543, v1[3]);
    ASSERT_EQ(0, l2[0]);
    ASSERT_EQ(0, l2[1]);
    ASSERT_EQ(27, l2[2]);
    ASSERT_EQ(270, l2[3]);
    ASSERT_EQ(0, c2[0]);
    ASSERT_EQ(50, c2[1]);
    ASSERT_EQ(2, c2[2]);
    ASSERT_EQ(800, c2[3]);
    EXPECT_EQ(0.654, v2[0]);
    EXPECT_DOUBLE_EQ(876.54, v2[1]);
    EXPECT_EQ(695.43, v2[2]);
    EXPECT_EQ(69.543, v2[3]);
}

TEST_F(SparseMatrixTests, should_have_a_method_to_generate_an_identity_matrix_of_a_given_dimension)
{
    const size_t n = a.random_size_t();
    const SparseMatrix E(eye(n));
    const size_t *c = E.get_columns();
    const size_t *l = E.get_rows();
    const double *v = E.get_values();
    for (size_t k = 0 ; k < n ; ++k)
    {
        EXPECT_EQ(k,c[k]);
        EXPECT_EQ(k,l[k]);
        EXPECT_EQ(1,v[k]);
    }
}

TEST_F(SparseMatrixTests, should_have_a_function_to_efficiently_sum_sparse_matrices_in_a_vector_of_the_same)
{
    std::vector<SparseMatrix> v;
    const size_t n = a.random_size_t(10,20);
    for (size_t k = 0 ; k < n ; ++k)
    {
        v.push_back(eye(k+1));
    }
    const SparseMatrix S(sum(v));
    const size_t *c = S.get_columns();
    const size_t *l = S.get_rows();
    const double *val = S.get_values();
    ASSERT_EQ(n, S.size());
    for (size_t k = 0 ; k < n ; ++k)
    {
        EXPECT_EQ(k,c[k]);
        EXPECT_EQ(k,l[k]);
        EXPECT_EQ(n-k,val[k]);
    }

}

TEST_F(SparseMatrixTests, should_have_an_operator_to_divide_a_sparse_matrix_by_a_scalar_value)
{
    SparseMatrix A(3);

    A.add_element_in_row_order(0,0,3);
    A.add_element_in_row_order(1,1,6);
    A.add_element_in_row_order(2,2,9);

    A.divide_in_place(3);
    EXPECT_EQ(1, A.get(0,0));
    EXPECT_EQ(2, A.get(1,1));
    EXPECT_EQ(3, A.get(2,2));

    A = A*3;
    EXPECT_EQ(3, A.get(0,0));
    EXPECT_EQ(6, A.get(1,1));
    EXPECT_EQ(9, A.get(2,2));

    A = A/3;
    EXPECT_EQ(1, A.get(0,0));
    EXPECT_EQ(2, A.get(1,1));
    EXPECT_EQ(3, A.get(2,2));

}

TEST_F(SparseMatrixTests, should_offer_an_implementation_of_the_minus_operator)
{
    SparseMatrix A(3);
    A.add_element_in_row_order(0,0,3);
    A.add_element_in_row_order(1,1,6);
    A.add_element_in_row_order(2,2,9);

    SparseMatrix B(4);
    B.add_element_in_row_order(0,0,4);
    B.add_element_in_row_order(1,1,7);
    B.add_element_in_row_order(2,2,10);
    B.add_element_in_row_order(3,3,20);

    const SparseMatrix M(A-B);
    const size_t *row_idx = M.get_rows();
    const size_t *col_idx = M.get_columns();
    const double *val = M.get_values();

    ASSERT_EQ(4, M.size());
    EXPECT_EQ(0, row_idx[0]);
    EXPECT_EQ(1, row_idx[1]);
    EXPECT_EQ(2, row_idx[2]);
    EXPECT_EQ(3, row_idx[3]);
    EXPECT_EQ(0, col_idx[0]);
    EXPECT_EQ(1, col_idx[1]);
    EXPECT_EQ(2, col_idx[2]);
    EXPECT_EQ(3, col_idx[3]);
    EXPECT_EQ(-1, val[0]);
    EXPECT_EQ(-1, val[1]);
    EXPECT_EQ(-1, val[2]);
    EXPECT_EQ(-20, val[3]);
}

TEST_F(SparseMatrixTests, function_empty_should_work_as_expected)
{
    SparseMatrix A(3);
    ASSERT_TRUE(A.empty());
    A.add_element_in_row_order(0,0,3);
    ASSERT_FALSE(A.empty());
}

TEST_F(SparseMatrixTests, should_offer_an_implementation_of_the_comparison_operators)
{
    SparseMatrix A(3);
    A.add_element_in_row_order(0,0,3);
    A.add_element_in_row_order(1,1,6);
    A.add_element_in_row_order(2,2,9);

    SparseMatrix B = 2*A;
    SparseMatrix C = A+A;

    ASSERT_EQ(2*A,B);
    ASSERT_EQ(B,C);
    ASSERT_NE(A, B);
}

TEST_F(SparseMatrixTests, should_offer_an_implementation_of_the_increment_operator)
{
    SparseMatrix A(3);
    A.add_element_in_row_order(0,0,3);
    A.add_element_in_row_order(1,1,6);
    A.add_element_in_row_order(2,2,9);

    SparseMatrix B(4);
    B.add_element_in_row_order(0,1,3);
    B.add_element_in_row_order(1,1,6);
    B.add_element_in_row_order(2,0,9);
    B.add_element_in_row_order(2,2,9);

    SparseMatrix C(5);
    C.add_element_in_row_order(0,0,3);
    C.add_element_in_row_order(0,1,3);
    C.add_element_in_row_order(1,1,12);
    C.add_element_in_row_order(2,0,9);
    C.add_element_in_row_order(2,2,18);

    A += B;

    ASSERT_EQ(C,A);
}

TEST_F(SparseMatrixTests, should_be_able_to_copy_row_indexes_to_array)
{
    SparseMatrix C(5);
    C.add_element_in_row_order(0,0,3);
    C.add_element_in_row_order(0,1,3);
    C.add_element_in_row_order(1,1,12);
    C.add_element_in_row_order(2,0,9);
    C.add_element_in_row_order(2,2,18);
    size_t *rows = new size_t[5];
    for (size_t i = 0 ; i < 5 ; ++i) rows[i] = 0;
    EXPECT_THROW(C.copy_row_indexes_to(5, NULL), SparseMatrixException);
    EXPECT_THROW(C.copy_row_indexes_to(a.random<size_t>().but_not(5)(), rows), SparseMatrixException);
    EXPECT_NO_THROW(C.copy_row_indexes_to(5, rows));
    EXPECT_EQ(0, rows[0]);
    EXPECT_EQ(0, rows[1]);
    EXPECT_EQ(1, rows[2]);
    EXPECT_EQ(2, rows[3]);
    EXPECT_EQ(2, rows[4]);
    delete [] rows;
}

TEST_F(SparseMatrixTests, should_be_able_to_copy_column_indexes_to_array)
{
    SparseMatrix C(5);
    C.add_element_in_row_order(0,0,3);
    C.add_element_in_row_order(0,1,3);
    C.add_element_in_row_order(1,1,12);
    C.add_element_in_row_order(2,0,9);
    C.add_element_in_row_order(2,2,18);
    size_t *columns = new size_t[5];
    for (size_t i = 0 ; i < 5 ; ++i) columns[i] = 0;
    EXPECT_THROW(C.copy_column_indexes_to(5, NULL), SparseMatrixException);
    EXPECT_THROW(C.copy_column_indexes_to(a.random<size_t>().but_not(5)(), columns), SparseMatrixException);
    EXPECT_NO_THROW(C.copy_column_indexes_to(5, columns));
    EXPECT_EQ(0, columns[0]);
    EXPECT_EQ(1, columns[1]);
    EXPECT_EQ(1, columns[2]);
    EXPECT_EQ(0, columns[3]);
    EXPECT_EQ(2, columns[4]);
    delete [] columns;
}

TEST_F(SparseMatrixTests, should_be_able_to_copy_values_to_array)
{
    SparseMatrix C(5);
    C.add_element_in_row_order(0,0,3);
    C.add_element_in_row_order(0,1,3);
    C.add_element_in_row_order(1,1,12);
    C.add_element_in_row_order(2,0,9);
    C.add_element_in_row_order(2,2,18);
    double *values = new double[5];
    for (size_t i = 0 ; i < 5 ; ++i) values[i] = 0;
    EXPECT_THROW(C.copy_values_to(5, NULL), SparseMatrixException);
    EXPECT_THROW(C.copy_values_to(a.random<size_t>().but_not(5)(), values), SparseMatrixException);
    EXPECT_NO_THROW(C.copy_values_to(5, values));
    EXPECT_EQ(3, values[0]);
    EXPECT_EQ(3, values[1]);
    EXPECT_EQ(12, values[2]);
    EXPECT_EQ(9, values[3]);
    EXPECT_EQ(18, values[4]);
    delete [] values;
}



TEST_F(SparseMatrixTests, should_be_able_to_return_the_absolute_value_of_a_matrix)
{
    SparseMatrix A(5);
    A.add_element_in_row_order(0,0,3);
    A.add_element_in_row_order(0,1,3);
    A.add_element_in_row_order(1,1,12);
    A.add_element_in_row_order(2,0,9);
    A.add_element_in_row_order(2,2,18);
    SparseMatrix B(5);
    B.add_element_in_row_order(0,0,-3);
    B.add_element_in_row_order(0,1,3);
    B.add_element_in_row_order(1,1,-12);
    B.add_element_in_row_order(2,0,9);
    B.add_element_in_row_order(2,2,-18);
    EXPECT_EQ(A, abs(B));
}

TEST_F(SparseMatrixTests, should_be_able_to_return_the_maximum_value_of_a_matrix)
{
    SparseMatrix A(5);
    SparseMatrix B(5);
    A.add_element_in_row_order(0,0,-3);
    A.add_element_in_row_order(0,1,3);
    A.add_element_in_row_order(1,1,-12);
    A.add_element_in_row_order(2,0,9);
    A.add_element_in_row_order(2,2,-18);
    EXPECT_EQ(18, abs(A).max());
    EXPECT_EQ(0, abs(B).max());
}

TEST_F(SparseMatrixTests, bug_in_cout)
{
    SparseMatrix M(4);
    M.add_element_in_row_order(0,0,1);
    M.add_element_in_row_order(1,3,2);
    M.add_element_in_row_order(2,1,3);
    M.add_element_in_row_order(3,2,4);
    COUT(M);
}

TEST_F(SparseMatrixTests, should_be_able_to_build_a_matrix_from_arrays)
{
    #define N 6
    const size_t rows[N] = {6,5,2,1,4,5};
    const size_t columns[N] = {1,8,9,7,6,2};
    const double values[N] = {1,2,3,4,5,6};
    const SparseMatrix actual(N, rows, columns, values);
    SparseMatrix expected(N);
    expected.add_element_in_row_order(1,7,4);
    expected.add_element_in_row_order(2,9,3);
    expected.add_element_in_row_order(4,6,5);
    expected.add_element_in_row_order(5,2,6);
    expected.add_element_in_row_order(5,8,2);
    expected.add_element_in_row_order(6,1,1);
    ASSERT_EQ(expected, actual);
}

