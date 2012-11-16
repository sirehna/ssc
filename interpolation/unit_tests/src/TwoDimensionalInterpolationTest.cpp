/*
 * TwoDimensionalSplinesTest.cpp
 *
 * \date 13 nov. 2012, 16:49:02
 *  \author cec
 */

#include "TwoDimensionalInterpolationTest.hpp"
#include "TwoDimensionalInterpolation.hpp"
#include <vector>
#include "LinearInterpolation.hpp"
#include "test_macros.hpp"

TwoDimensionalSplinesTest::TwoDimensionalSplinesTest() : a(DataGenerator(12))
{
}

TwoDimensionalSplinesTest::~TwoDimensionalSplinesTest()
{
}

void TwoDimensionalSplinesTest::SetUp()
{
}

void TwoDimensionalSplinesTest::TearDown()
{
}

TEST_F(TwoDimensionalSplinesTest, example)
{
//! [TwoDimensionalSplinesTest example]
    std::vector<std::vector<double> > M;
    M.push_back({2,5,10,17,26,37,50,65,82,101});
    M.push_back({5,8,13,20,29,40,53,68,85,104});
    M.push_back({10,13,18,25,34,45,58,73,90,109});
    M.push_back({17,20,25,32,41,52,65,80,97,116});
    M.push_back({26,29,34,41,50,61,74,89,106,125});
    M.push_back({37,40,45,52,61,72,85,100,117,136});
    M.push_back({50,53,58,65,74,85,98,113,130,149});
    M.push_back({65,68,73,80,89,100,113,128,145,164});
    M.push_back({82,85,90,97,106,117,130,145,162,181});
    M.push_back({101,104,109,116,125,136,149,164,181,200});
//! [TwoDimensionalSplinesTest example]
//! [TwoDimensionalSplinesTest expected output]

    TwoDimensionalInterpolation<LinearInterpolation> spline(1,10,1,10,M);
    ASSERT_DOUBLE_EQ(5, spline.f(1.5,1.5));
    ASSERT_DOUBLE_EQ(9, spline.f(2.5,1.5));
//! [TwoDimensionalSplinesTest expected output]
}

TEST_F(TwoDimensionalSplinesTest, should_throw_if_all_elements_in_M_arent_the_same_size)
{
    std::vector<std::vector<double> > M;

    const size_t n = a.random<size_t>().no().greater_than(20);
    for (size_t i = 0 ; i < n ; ++i)
    {
        M.push_back(a.random_vector_of<double>());
    }
    ASSERT_THROW(TwoDimensionalInterpolation<LinearInterpolation>(a.random<double>(),a.random<double>(),a.random<double>(),a.random<double>(),M), TwoDimensionalInterpolationException);
}

TEST_F(TwoDimensionalSplinesTest, should_throw_if_M_has_less_than_two_elements)
{
    std::vector<std::vector<double> > M;
    ASSERT_THROW(TwoDimensionalInterpolation<LinearInterpolation>(a.random<double>(),a.random<double>(),a.random<double>(),a.random<double>(),M), TwoDimensionalInterpolationException);
    M.push_back(a.random_vector_of<double>());
    ASSERT_THROW(TwoDimensionalInterpolation<LinearInterpolation>(a.random<double>(),a.random<double>(),a.random<double>(),a.random<double>(),M), TwoDimensionalInterpolationException);
}

TEST_F(TwoDimensionalSplinesTest, should_throw_if_any_element_in_M_has_one_element)
{
    std::vector<std::vector<double> > M;

    const size_t n = a.random<size_t>().no().greater_than(20);
    for (size_t i = 0 ; i < n ; ++i)
    {
        M.push_back(std::vector<double>(1,a.random<double>()));
    }
    ASSERT_THROW(TwoDimensionalInterpolation<LinearInterpolation>(a.random<double>(),a.random<double>(),a.random<double>(),a.random<double>(),M), TwoDimensionalInterpolationException);
}

TEST_F(TwoDimensionalSplinesTest, should_throw_if_any_element_in_M_is_empty)
{
    std::vector<std::vector<double> > M;

    const size_t n = a.random<size_t>().no().greater_than(20);
    for (size_t i = 0 ; i < n ; ++i)
    {
        M.push_back(std::vector<double>());
    }
    ASSERT_THROW(TwoDimensionalInterpolation<LinearInterpolation>(a.random<double>(),a.random<double>(),a.random<double>(),a.random<double>(),M), TwoDimensionalInterpolationException);
}


TEST_F(TwoDimensionalSplinesTest, should_work_like_matlabs_griddedInterpolant)
{
//! [TwoDimensionalSplinesTest example]
    std::vector<std::vector<double> > M;
    M.push_back({3,4,5,6,7,8,9,10,11,12});
    M.push_back({5,6,7,8,9,10,11,12,13,14});
    M.push_back({7,8,9,10,11,12,13,14,15,16});
    M.push_back({9,10,11,12,13,14,15,16,17,18});
    M.push_back({11,12,13,14,15,16,17,18,19,20});
    M.push_back({13,14,15,16,17,18,19,20,21,22});
    M.push_back({15,16,17,18,19,20,21,22,23,24});
    M.push_back({17,18,19,20,21,22,23,24,25,26});
    M.push_back({19,20,21,22,23,24,25,26,27,28});
    M.push_back({21,22,23,24,25,26,27,28,29,30});
//! [TwoDimensionalSplinesTest example]
//! [TwoDimensionalSplinesTest expected output]
    TwoDimensionalInterpolation<LinearInterpolation> spline(1,10,1,10,M);
    ASSERT_DOUBLE_EQ(3, spline.f(1,1));
    ASSERT_DOUBLE_EQ(30, spline.f(10,10));
    ASSERT_DOUBLE_EQ(4.5, spline.f(1.5,1.5));
    ASSERT_DOUBLE_EQ(6.5, spline.f(2.5,1.5));
    ASSERT_DOUBLE_EQ(5.5, spline.f(1.5,2.5));
    ASSERT_DOUBLE_EQ(8.146, spline.f(1.234,5.678));
//! [TwoDimensionalSplinesTest expected output]
}

