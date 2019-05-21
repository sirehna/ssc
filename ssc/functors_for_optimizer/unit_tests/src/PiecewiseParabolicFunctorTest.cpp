/*
 * PiecewiseParabolicFunctorTest.cpp
 *
 * \date 19 févr. 2013, 14:43:26
 * \author cec
 */

#include "PiecewiseParabolicFunctorTest.hpp"
#include "ssc/interpolation/ParabolicCoefficients.hpp"
#include "ssc/functors_for_optimizer/PiecewiseParabolicFunctor.hpp"
#include "ssc/macros/extra_test_assertions.hpp"

#define X_ (*x)
#define X (x->get_lambda()())

using namespace ssc::functors_for_optimizer;

PiecewiseParabolicFunctorTest::PiecewiseParabolicFunctorTest() : a(ssc::random_data_generator::DataGenerator(967)), generate(StateGenerator())
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

    std::vector<ssc::interpolation::ParabolicCoefficients> coeffs;
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(12./5.,0,1./5.));
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(-6.,84./5.,-41./5.));
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(18./5.,-108./5.,151./5.));
    PiecewiseParabolicFunctor pp(x, 0, 3, coeffs);
    const auto f = pp.get_lambda();
//! [PiecewiseParabolicFunctorTest example]

//! [PiecewiseParabolicFunctorTest expected output]
    const double eps = 1e-8;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(1./5.+(12./5.)*X*X,f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR(-41./5.+(84./5.)*(X-1)-6*(X-1)*(X-1),f(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(151./5.-(108./5.)*(X-2)+(18./5.)*(X-2)*(X-2),f(),eps);
    }
//! [PiecewiseParabolicFunctorTest expected output]
}

TEST_F(PiecewiseParabolicFunctorTest, derivative_should_be_piecewise_linear)
{
    auto x = generate.state("x");
    std::vector<ssc::interpolation::ParabolicCoefficients> coeffs;
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(12./5.,0,0.2));
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(-6.,24./5,13./5));
    coeffs.push_back(ssc::interpolation::ParabolicCoefficients(18./5,-36./5,7./5.));
    PiecewiseParabolicFunctor pp(x, 0, 3, coeffs);
    const auto f = pp.get_lambda();
    const auto df_dx = pp.diff(x)->get_lambda();
    const double eps = 1e-8;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(0,1);
        ASSERT_SMALL_RELATIVE_ERROR(2.*(12./5.)*X,df_dx(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(1,2);
        ASSERT_SMALL_RELATIVE_ERROR(24./5-2.*6*(X-1),df_dx(),eps);
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        X_ = a.random<double>().between(2,3);
        ASSERT_SMALL_RELATIVE_ERROR(-(36./5.)+2.*(18./5.)*(X-2),df_dx(),eps);
    }
}
