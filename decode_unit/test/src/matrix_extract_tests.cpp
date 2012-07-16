#include <vector>

#include "matrix_extract_tests.hpp"

void matrix_test::SetUp()
{
    SetUpDoubleMatrix();
    SetUpFloatMatrix();
    SetUpIntMatrix();
    SetUpSizeTMatrix();
}

void matrix_test::SetUpDoubleMatrix()
{
    test_matrix_double(0,0) = 1.31;
    test_matrix_double(0,1) = 6541.31;
    test_matrix_double(0,2) = 1.354541;
    test_matrix_double(0,3) = 87421.31;
    test_matrix_double(0,4) = 87121982.31;
    test_matrix_double(1,0) = 131;
    test_matrix_double(1,1) = 654131;
    test_matrix_double(1,2) = -354541;
    test_matrix_double(1,3) = 8742131;
    test_matrix_double(1,4) = -712131;
    test_matrix_double(2,0) = -971371.120;
    test_matrix_double(2,1) = -46584131.794;
    test_matrix_double(2,2) = 39554541.6456;
    test_matrix_double(2,3) = -878.42131;
    test_matrix_double(2,4) = 712.2131;
    test_matrix_double(3,0) = 131;
    test_matrix_double(3,1) = 254131;
    test_matrix_double(3,2) = -354541;
    test_matrix_double(3,3) = 4742131;
    test_matrix_double(3,4) = 5712131;
    test_matrix_double(4,0) = -31;
    test_matrix_double(4,1) = -54131.18;
    test_matrix_double(4,2) = 354541.982;
    test_matrix_double(4,3) = -4742131.648;
    test_matrix_double(4,4) = 5712131;
    test_matrix_double(5,0) = -31;
    test_matrix_double(5,1) = -54131.18;
    test_matrix_double(5,2) = 354541.982;
    test_matrix_double(5,3) = -4742131.648;
    test_matrix_double(5,4) = 5712131;
}

void matrix_test::SetUpFloatMatrix()
{
    test_matrix_float(0,0) = 81.31;
    test_matrix_float(0,1) = 651541.31;
    test_matrix_float(0,2) = 1.1354541;
    test_matrix_float(0,3) = 872421.31;
    test_matrix_float(0,4) = 876121982.31;
    test_matrix_float(1,0) = 1371;
    test_matrix_float(1,1) = 6584131;
    test_matrix_float(1,2) = -3954541;
    test_matrix_float(1,3) = 87842131;
    test_matrix_float(1,4) = -7122131;
    test_matrix_float(2,0) = -971371.120;
    test_matrix_float(2,1) = -46584131.794;
    test_matrix_float(2,2) = 39554541.6456;
    test_matrix_float(2,3) = -878.42131;
    test_matrix_float(2,4) = 712.2131;
    test_matrix_float(3,0) = 1311;
    test_matrix_float(3,1) = 2594131;
    test_matrix_float(3,2) = -3524541;
    test_matrix_float(3,3) = 474752131;
    test_matrix_float(3,4) = 57122131;
    test_matrix_float(4,0) = -301;
    test_matrix_float(4,1) = -524131.18;
    test_matrix_float(4,2) = 3524541.982;
    test_matrix_float(4,3) = -472742131.648;
    test_matrix_float(4,4) = 57121931.64;
    test_matrix_float(5,0) = -31.645;
    test_matrix_float(5,1) = -5413971.18;
    test_matrix_float(5,2) = 35454781.982;
    test_matrix_float(5,3) = -47425131.648;
    test_matrix_float(5,4) = 5712131.9845;
}

void matrix_test::SetUpIntMatrix()
{
    test_matrix_int(0,0) = 81;
    test_matrix_int(0,1) = 651541;
    test_matrix_int(0,2) = 1;
    test_matrix_int(0,3) = 872421;
    test_matrix_int(0,4) = 876121982;
    test_matrix_int(1,0) = 1371;
    test_matrix_int(1,1) = 6584131;
    test_matrix_int(1,2) = -3954541;
    test_matrix_int(1,3) = 87842131;
    test_matrix_int(1,4) = -7122131;
    test_matrix_int(2,0) = -971371120;
    test_matrix_int(2,1) = -465841317;
    test_matrix_int(2,2) = 395545416;
    test_matrix_int(2,3) = -8782131;
    test_matrix_int(2,4) = 7122131;
    test_matrix_int(3,0) = 1311;
    test_matrix_int(3,1) = 2594131;
    test_matrix_int(3,2) = -3524541;
    test_matrix_int(3,3) = 474752131;
    test_matrix_int(3,4) = 57122131;
    test_matrix_int(4,0) = -301;
    test_matrix_int(4,1) = -524131;
    test_matrix_int(4,2) = 3524541;
    test_matrix_int(4,3) = -472742131;
    test_matrix_int(4,4) = 57121931;
    test_matrix_int(5,0) = -31;
    test_matrix_int(5,1) = -5413971;
    test_matrix_int(5,2) = 35454781;
    test_matrix_int(5,3) = -47425131;
    test_matrix_int(5,4) = 5712131;
}

void matrix_test::SetUpSizeTMatrix()
{
    test_matrix_size_t(0,0) = 81;
    test_matrix_size_t(0,1) = 651541;
    test_matrix_size_t(0,2) = 1;
    test_matrix_size_t(0,3) = 872421;
    test_matrix_size_t(0,4) = 876121982;
    test_matrix_size_t(1,0) = 1371;
    test_matrix_size_t(1,1) = 6584131;
    test_matrix_size_t(1,2) = 3954541;
    test_matrix_size_t(1,3) = 87842131;
    test_matrix_size_t(1,4) = 7122131;
    test_matrix_size_t(2,0) = 971371120;
    test_matrix_size_t(2,1) = 465841317;
    test_matrix_size_t(2,2) = 395545416;
    test_matrix_size_t(2,3) = 8782131;
    test_matrix_size_t(2,4) = 7122131;
    test_matrix_size_t(3,0) = 1311;
    test_matrix_size_t(3,1) = 2594131;
    test_matrix_size_t(3,2) = 3524541;
    test_matrix_size_t(3,3) = 474752131;
    test_matrix_size_t(3,4) = 57122131;
    test_matrix_size_t(4,0) = 301;
    test_matrix_size_t(4,1) = 524131;
    test_matrix_size_t(4,2) = 3524541;
    test_matrix_size_t(4,3) = 472742131;
    test_matrix_size_t(4,4) = 57121931;
    test_matrix_size_t(5,0) = 31;
    test_matrix_size_t(5,1) = 5413971;
    test_matrix_size_t(5,2) = 35454781;
    test_matrix_size_t(5,3) = 47425131;
    test_matrix_size_t(5,4) = 5712131;
}

void matrix_test::TearDown()
{
}


TEST_F(matrix_test, extract_column_test)
{
    const std::vector<double> col2 = test_matrix_double.col_stl_vector(2);
    const std::vector<float>  col3 = test_matrix_float.col_stl_vector(3);
    const std::vector<int>    col4 = test_matrix_int.col_stl_vector(4);
    const std::vector<size_t> col1 = test_matrix_size_t.col_stl_vector(1);

    const size_t c1[] = {651541, 6584131, 465841317, 2594131, 524131, 5413971};
    const double c2[] = {1.354541, -354541, 39554541.6456, -354541, 354541.982, 354541.982};
    const float c3[] = {872421.31, 87842131, -878.42131, 474752131, -472742131.648, -47425131.648};
    const int c4[] = {876121982, -7122131, 7122131, 57122131, 57121931, 5712131};
    
    const std::vector<size_t> col1_ref(c1, c1 + sizeof(c1) / sizeof(size_t));
    const std::vector<double> col2_ref(c2, c2 + sizeof(c2) / sizeof(double));
    const std::vector<float> col3_ref(c3, c3 + sizeof(c3) / sizeof(float));
    const std::vector<int> col4_ref(c4, c4 + sizeof(c4) / sizeof(int));

    ASSERT_EQ(col1_ref.size(), col1.size());
    ASSERT_EQ(col2_ref.size(), col2.size());
    ASSERT_EQ(col3_ref.size(), col3.size());
    ASSERT_EQ(col4_ref.size(), col4.size());

    EXPECT_TRUE(vectors_are_equal<size_t>(col1_ref, col1));
    EXPECT_TRUE(vectors_are_equal<double>(col2_ref, col2));
    EXPECT_TRUE(vectors_are_equal<float>(col3_ref, col3));
    EXPECT_TRUE(vectors_are_equal<int>(col4_ref, col4));
}

TEST_F(matrix_test, extract_line_test)
{
    const std::vector<double> row2 = test_matrix_double.row_stl_vector(2);
    const std::vector<float>  row3 = test_matrix_float.row_stl_vector(3);
    const std::vector<int>    row4 = test_matrix_int.row_stl_vector(4);
    const std::vector<size_t> row1 = test_matrix_size_t.row_stl_vector(1);

    const size_t r1[] = { 1371, 6584131, 3954541, 87842131, 7122131 };
    const double r2[] = { -971371.120, -46584131.794, 39554541.6456, -878.42131, 712.2131};
    const float r3[] = { 1311, 2594131, -3524541, 474752131, 57122131};
    const int r4[] = {-301, -524131, 3524541, -472742131, 57121931};

    const std::vector<size_t> row1_ref(r1, r1 + sizeof(r1) / sizeof(size_t));
    const std::vector<double> row2_ref(r2, r2 + sizeof(r2) / sizeof(double));
    const std::vector<float> row3_ref(r3, r3 + sizeof(r3) / sizeof(float));
    const std::vector<int> row4_ref(r4, r4 + sizeof(r4) / sizeof(int));

    ASSERT_EQ(row1_ref.size(), row1.size());
    ASSERT_EQ(row2_ref.size(), row2.size());
    ASSERT_EQ(row3_ref.size(), row3.size());
    ASSERT_EQ(row4_ref.size(), row4.size());

    EXPECT_TRUE(vectors_are_equal<size_t>(row1_ref, row1));
    EXPECT_TRUE(vectors_are_equal<double>(row2_ref, row2));
    EXPECT_TRUE(vectors_are_equal<float>(row3_ref, row3));
    EXPECT_TRUE(vectors_are_equal<int>(row4_ref, row4));
}

