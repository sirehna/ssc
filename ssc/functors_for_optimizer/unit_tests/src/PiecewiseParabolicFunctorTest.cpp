/*
 * PiecewiseParabolicFunctorTest.cpp
 *
 * \date 19 févr. 2013, 14:43:26
 *  \author cec
 */

#include "PiecewiseParabolicFunctorTest.hpp"
#include "ParabolicCoefficients.hpp"
#include "PiecewiseParabolicFunctor.hpp"
#include "extra_test_assertions.hpp"

PiecewiseParabolicFunctorTest::PiecewiseParabolicFunctorTest() : a(DataGenerator(967)), generate(StateGenerator())
{
}

PiecewiseParabolicFunctorTest::~PiecewiseParabolicFunctorTest()
{
}

void PiecewiseParabolicFunctorTest::SetUp()
{
}

void PiecewiseParabolicFunctorTest::TearDown()
{
}

TEST_F(PiecewiseParabolicFunctorTest, example)
{
//! [PiecewiseParabolicFunctorTest example]
    auto x = generate.state("x");
    #define X (**x)
    std::vector<ParabolicCoefficients> coeffs;
    coeffs.push_back(ParabolicCoefficients(12./5.,0,1./5.));
    coeffs.push_back(ParabolicCoefficients(-6.,84./5.,-41./5.));
    coeffs.push_back(ParabolicCoefficients(18./5.,-108./5.,151./5.));
    PiecewiseParabolicFunctor pp(x, 0, 3, coeffs);
    const auto f = pp.get_lambda();
//! [PiecewiseParabolicFunctorTest example]

//! [PiecewiseParabolicFunctorTest expected output]
    const double eps = 1e-8;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(1./5.+(12./5.)*X*X,f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR(-41./5.+(84./5.)*X-6*X*X,f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(151./5.-(108./5.)*X+(18./5.)*X*X,f(),eps);
    }
//! [PiecewiseParabolicFunctorTest expected output]
}

TEST_F(PiecewiseParabolicFunctorTest, derivative_should_be_piecewise_linear)
{
    auto x = generate.state("x");
    #define X (**x)
    std::vector<ParabolicCoefficients> coeffs;
    coeffs.push_back(ParabolicCoefficients(12./5.,0,1./5.));
    coeffs.push_back(ParabolicCoefficients(-6.,84./5.,-41./5.));
    coeffs.push_back(ParabolicCoefficients(18./5.,-108./5.,151./5.));
    PiecewiseParabolicFunctor pp(x, 0, 3, coeffs);
    const auto f = pp.diff(x)->get_lambda();
    const double eps = 1e-8;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(2.*(12./5.)*X,f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR((84./5.)-2.*6.*X,f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        **x = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(-(108./5.)+2.*(18./5.)*X,f(),eps);
    }
}

