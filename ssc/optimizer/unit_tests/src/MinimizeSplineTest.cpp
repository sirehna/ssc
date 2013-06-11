/*
 * MinimizeSplineTest.cpp
 *
 * \date 10 juin 2013, 11:47:46
 *  \author cec
 */

#include "MinimizeSplineTest.hpp"

#define EPS 1E-6
#include <functional>
#include "MinimizeSpline.hpp"
#include "test_macros.hpp"

MinimizeSplineTest::MinimizeSplineTest() : a(DataGenerator(29973))
{
}

MinimizeSplineTest::~MinimizeSplineTest()
{
}

void MinimizeSplineTest::SetUp()
{
}

void MinimizeSplineTest::TearDown()
{
}

TEST_F(MinimizeSplineTest, example)
{
    for (size_t k = 0 ; k < 50 ; ++k)
    {
//! [MinimizeSplineTest example]
    const double xmin = a.random<double>();
    const double xmax = a.random<double>().greater_than(xmin);
    const double x0 = a.random<double>().between(xmin,xmax);
    const auto f = [x0](double x) {return (x-x0)*(x-x0);};
    std::vector<double> y;
    const size_t n = a.random<size_t>().between(5,20);
    for (size_t i = 0 ; i < n ; ++i)
    {
        y.push_back(f(xmin + (xmax-xmin)/double(n-1)*double(i)));
    }
    MinimizeSpline ms(xmin, xmax, y);
//! [MinimizeSplineTest example]
//! [MinimizeSplineTest expected output]
    ASSERT_NEAR(x0, ms.get_min(),(xmax-xmin)/(2*n));
//! [MinimizeSplineTest expected output]
    }
}



