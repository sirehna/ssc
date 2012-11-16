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

TEST_F(TwoDimensionalSplinesTest, should_work_for_asymetric_bounds)
{
//! [TwoDimensionalSplinesTest example]
    std::vector<std::vector<double> > M;
    M.push_back({883,969,1059,1153,1251,1353,1459,1569,1683,1801});
    M.push_back({886,972,1062,1156,1254,1356,1462,1572,1686,1804});
    M.push_back({891,977,1067,1161,1259,1361,1467,1577,1691,1809});
    M.push_back({898,984,1074,1168,1266,1368,1474,1584,1698,1816});
    M.push_back({907,993,1083,1177,1275,1377,1483,1593,1707,1825});
    M.push_back({918,1004,1094,1188,1286,1388,1494,1604,1718,1836});
    M.push_back({931,1017,1107,1201,1299,1401,1507,1617,1731,1849});
    M.push_back({946,1032,1122,1216,1314,1416,1522,1632,1746,1864});
    M.push_back({963,1049,1139,1233,1331,1433,1539,1649,1763,1881});
    M.push_back({982,1068,1158,1252,1350,1452,1558,1668,1782,1900});
    TwoDimensionalInterpolation<LinearInterpolation> spline(1,10,21,30,M);
    ASSERT_DOUBLE_EQ(883, spline.f(1,21));
    ASSERT_DOUBLE_EQ(886, spline.f(2,21));
    ASSERT_DOUBLE_EQ(891, spline.f(3,21));

    ASSERT_DOUBLE_EQ(982, spline.f(10,21));
    ASSERT_DOUBLE_EQ(1900, spline.f(10,30));
    ASSERT_DOUBLE_EQ(1801, spline.f(1,30));
    ASSERT_DOUBLE_EQ(1331.5, spline.f(5.5,25.5));
}
