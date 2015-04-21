#include "SparseVectorTests.hpp"
#include "ssc/exception_handling/Exception.hpp"
#include "ssc/macros/test_macros.hpp"

using namespace ssc::matrix_and_vector_classes;

void SparseVectorTests::SetUp()
{
}

void SparseVectorTests::TearDown()
{
}

TEST_F(SparseVectorTests, there_should_exist_a_sparse_vector_class)
{
    SparseVector A;
    SparseVector B(1365);
}

TEST_F(SparseVectorTests, should_be_able_to_set_and_retrieve_an_element)
{
    SparseVector A(3);
    const size_t idx1 = a.random<size_t>();
    const size_t idx2 = a.random<size_t>().between(idx1, ssc::random_data_generator::get_max_bound<size_t>());
    const size_t idx3 = a.random<size_t>().between(idx2, ssc::random_data_generator::get_max_bound<size_t>());
    const size_t idx4 = a.random<size_t>().between(idx3, ssc::random_data_generator::get_max_bound<size_t>());
    const double val1 = a.random<double>();
    const double val2 = a.random<double>();
    const double val3 = a.random<double>();
    A.add_element_in_order(idx1, val1);
    A.add_element_in_order(idx2, val2);
    A.add_element_in_order(idx3, val3);
    EXPECT_EQ(val1, A.get(idx1));
    EXPECT_EQ(val2, A.get(idx2));
    EXPECT_EQ(val3, A.get(idx3));
    EXPECT_THROW(A.add_element_in_order(idx1, val1), ssc::exception_handling::Exception);
    EXPECT_THROW(A.get(idx4), ssc::exception_handling::Exception);
    EXPECT_THROW(A.add_element_in_order(idx2,a.random<double>()), ssc::exception_handling::Exception);
}

TEST_F(SparseVectorTests, should_be_able_to_retrieve_all_elements_and_all_indexes)
{
    SparseVector A(3);
    A.add_element_in_order(15, 654);
    A.add_element_in_order(68, 87654);
    A.add_element_in_order(647, 69543);
    const size_t *idx = A.get_indexes();
    const double *v = A.get_values();
    EXPECT_EQ(15,  idx[0]);
    EXPECT_EQ(68,  idx[1]);
    EXPECT_EQ(647,  idx[2]);
    EXPECT_EQ(654, v[0]);
    EXPECT_EQ(87654, v[1]);
    EXPECT_EQ(69543, v[2]);
}

TEST_F(SparseVectorTests, should_have_an_operator_to_multiply_a_sparse_vector_by_a_scalar_value)
{
    SparseVector A(3);
    A.add_element_in_order(15, 654);
    A.add_element_in_order(68, 87654);
    A.add_element_in_order(647, 69543);
    SparseVector B(3*A);
    const double *v1 = B.get_values();
    EXPECT_EQ(3*654, v1[0]);
    EXPECT_EQ(3*87654, v1[1]);
    EXPECT_EQ(3*69543, v1[2]);
}


TEST_F(SparseVectorTests, should_have_a_function_to_multiply_a_sparse_vector_by_a_scalar_value_in_place)
{
    SparseVector A(3);
    A.add_element_in_order(15, 654);
    A.add_element_in_order(68, 87654);
    A.add_element_in_order(647, 69543);
    A.multiply_in_place_by(4);
    const double *v = A.get_values();
    EXPECT_EQ(4*654, v[0]);
    EXPECT_EQ(4*87654, v[1]);
    EXPECT_EQ(4*69543, v[2]);
}


TEST_F(SparseVectorTests, should_be_able_to_add_two_sparse_vectors)
{
    SparseVector A(4);
    A.add_element_in_order(0, .654);
    A.add_element_in_order(27, 695.43);
    A.add_element_in_order(50, 876.54);
    A.add_element_in_order(800, 69.543);
    SparseVector B(3);
    B.add_element_in_order(0, .54);
    B.add_element_in_order(27, 0.87);
    B.add_element_in_order(400, 8722.654);
    SparseVector C(A+B);
    const size_t *idx = C.get_indexes();
    const double *v = C.get_values();
    ASSERT_EQ(0, idx[0]);
    ASSERT_EQ(27, idx[1]);
    ASSERT_EQ(50, idx[2]);
    ASSERT_EQ(400, idx[3]);
    ASSERT_EQ(800, idx[4]);
    EXPECT_EQ(1.194, v[0]);
    EXPECT_DOUBLE_EQ(696.3, v[1]);
    EXPECT_EQ(876.54, v[2]);
    EXPECT_EQ(8722.654, v[3]);
    EXPECT_EQ(69.543, v[4]);
}


TEST_F(SparseVectorTests, should_have_a_method_to_initialize_a_vector_with_the_sum_of_two_vectors)
{
    SparseVector A(4);
    A.add_element_in_order(0, .654);
    A.add_element_in_order(27, 695.43);
    A.add_element_in_order(50, 876.54);
    A.add_element_in_order(800, 69.543);
    SparseVector B(3);
    B.add_element_in_order(0, .54);
    B.add_element_in_order(27, 0.87);
    B.add_element_in_order(400, 8722.654);
    SparseVector C(A,B);
    const size_t *idx = C.get_indexes();
    const double *v = C.get_values();
    ASSERT_EQ(0, idx[0]);
    ASSERT_EQ(27, idx[1]);
    ASSERT_EQ(50, idx[2]);
    ASSERT_EQ(400, idx[3]);
    ASSERT_EQ(800, idx[4]);
    EXPECT_EQ(1.194, v[0]);
    EXPECT_DOUBLE_EQ(696.3, v[1]);
    EXPECT_EQ(876.54, v[2]);
    EXPECT_EQ(8722.654, v[3]);
    EXPECT_EQ(69.543, v[4]);
}

TEST_F(SparseVectorTests, should_have_a_function_to_efficiently_sum_sparse_vectors_in_a_vector_of_the_same)
{
    SparseVector A(3);
    SparseVector B(4);
    SparseVector C(5);

    A.add_element_in_order(0,1);
    A.add_element_in_order(1,2);
    A.add_element_in_order(2,3);

    B.add_element_in_order(1,4);
    B.add_element_in_order(2,5);
    B.add_element_in_order(3,6);
    B.add_element_in_order(4,7);

    C.add_element_in_order(2,8);
    C.add_element_in_order(3,9);
    C.add_element_in_order(4,10);
    C.add_element_in_order(5,11);
    C.add_element_in_order(6,12);

    std::vector<SparseVector> v;
    v.push_back(A);
    v.push_back(B);
    v.push_back(C);

    SparseVector S(sum(v));
    ASSERT_EQ(7, S.size());
    const size_t *idx = S.get_indexes();
    const double *val = S.get_values();
    EXPECT_EQ(0, idx[0]);
    EXPECT_EQ(1, idx[1]);
    EXPECT_EQ(2, idx[2]);
    EXPECT_EQ(3, idx[3]);
    EXPECT_EQ(4, idx[4]);
    EXPECT_EQ(5, idx[5]);
    EXPECT_EQ(6, idx[6]);
    EXPECT_EQ(1, val[0]);
    EXPECT_EQ(6, val[1]);
    EXPECT_EQ(16, val[2]);
    EXPECT_EQ(15, val[3]);
    EXPECT_EQ(17, val[4]);
    EXPECT_EQ(11, val[5]);
    EXPECT_EQ(12, val[6]);
}

TEST_F(SparseVectorTests, should_have_an_operator_to_divide_a_sparse_vector_by_a_scalar_value)
{
    SparseVector A(3);

    A.add_element_in_order(0,3);
    A.add_element_in_order(1,6);
    A.add_element_in_order(2,9);

    A.divide_in_place(3);
    EXPECT_EQ(1, A.get(0));
    EXPECT_EQ(2, A.get(1));
    EXPECT_EQ(3, A.get(2));

    A = A*3;
    EXPECT_EQ(3, A.get(0));
    EXPECT_EQ(6, A.get(1));
    EXPECT_EQ(9, A.get(2));

    A = A/3;
    EXPECT_EQ(1, A.get(0));
    EXPECT_EQ(2, A.get(1));
    EXPECT_EQ(3, A.get(2));
}

TEST_F(SparseVectorTests, should_offer_an_implementation_of_the_minus_operator)
{
    SparseVector A(3);
    A.add_element_in_order(0,3);
    A.add_element_in_order(1,6);
    A.add_element_in_order(2,9);

    SparseVector B(4);
    B.add_element_in_order(0,4);
    B.add_element_in_order(1,7);
    B.add_element_in_order(2,10);
    B.add_element_in_order(3,20);

    const SparseVector M(A-B);
    const size_t *idx = M.get_indexes();
    const double *val = M.get_values();

    ASSERT_EQ(4, M.size());
    EXPECT_EQ(0, idx[0]);
    EXPECT_EQ(1, idx[1]);
    EXPECT_EQ(2, idx[2]);
    EXPECT_EQ(3, idx[3]);
    EXPECT_EQ(-1, val[0]);
    EXPECT_EQ(-1, val[1]);
    EXPECT_EQ(-1, val[2]);
    EXPECT_EQ(-20, val[3]);
}

TEST_F(SparseVectorTests, should_offer_an_implementation_of_the_comparison_operator)
{
    SparseVector A(3);
    A.add_element_in_order(0,3);
    A.add_element_in_order(1,6);
    A.add_element_in_order(2,9);

    SparseVector B(A);
    SparseVector C = 2*A;

    ASSERT_EQ(A,B);
    ASSERT_NE(A,C);
    ASSERT_NE(B,C);
}

TEST_F(SparseVectorTests, should_offer_an_implementation_of_the_increment_operator)
{
    SparseVector A(3);
    A.add_element_in_order(0,3);
    A.add_element_in_order(1,6);
    A.add_element_in_order(2,9);
    SparseVector B = 2*A;

    A += A;


    ASSERT_EQ(B, A);
    ASSERT_EQ(6, A.get(0));
    ASSERT_EQ(12, A.get(1));
    ASSERT_EQ(18, A.get(2));
}

TEST_F(SparseVectorTests, should_be_able_to_copy_indexes_to_array)
{
    SparseVector C(5);
    C.add_element_in_order(0,3);
    C.add_element_in_order(1,3);
    C.add_element_in_order(401,12);
    C.add_element_in_order(508,9);
    C.add_element_in_order(509,18);
    size_t *indexes = new size_t[5];
    for (size_t i = 0 ; i < 5 ; ++i) indexes[i] = 0;
    EXPECT_THROW(C.copy_indexes_to(5, NULL), SparseVectorException);
    EXPECT_THROW(C.copy_indexes_to(a.random<size_t>().but_not(5), indexes), SparseVectorException);
    EXPECT_NO_THROW(C.copy_indexes_to(5, indexes));
    EXPECT_EQ(0,  indexes[0]);
    EXPECT_EQ(1,  indexes[1]);
    EXPECT_EQ(401, indexes[2]);
    EXPECT_EQ(508, indexes[3]);
    EXPECT_EQ(509, indexes[4]);
    delete [] indexes;
}


TEST_F(SparseVectorTests, should_be_able_to_copy_values_to_array)
{
    SparseVector C(5);
    C.add_element_in_order(0,3);
    C.add_element_in_order(1,3);
    C.add_element_in_order(401,12);
    C.add_element_in_order(508,9);
    C.add_element_in_order(509,18);
    double *values = new double[5];
    for (size_t i = 0 ; i < 5 ; ++i) values[i] = 0;
    EXPECT_THROW(C.copy_values_to(5, NULL), SparseVectorException);
    EXPECT_THROW(C.copy_values_to(a.random<size_t>().but_not(5), values), SparseVectorException);
    EXPECT_NO_THROW(C.copy_values_to(5, values));
    EXPECT_EQ(3, values[0]);
    EXPECT_EQ(3, values[1]);
    EXPECT_EQ(12, values[2]);
    EXPECT_EQ(9, values[3]);
    EXPECT_EQ(18, values[4]);
    delete [] values;
}


