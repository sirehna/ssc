/*
 * ParabolicInterpolationTest.cpp
 *
 * \date 19 févr. 2013, 09:56:08
 *  \author cec
 */

#include "ParabolicInterpolationTest.hpp"
#include "ParabolicInterpolation.hpp"

ParabolicInterpolationTest::ParabolicInterpolationTest() : a(DataGenerator(77))
{
}

ParabolicInterpolationTest::~ParabolicInterpolationTest()
{
}

void ParabolicInterpolationTest::SetUp()
{
}

void ParabolicInterpolationTest::TearDown()
{
}

template <> ParabolicCoefficients TypedScalarDataGenerator<ParabolicCoefficients>::get() const
{
    ParabolicCoefficients ret(random<double>(),random<double>(),random<double>());
    return ret;
}

template<> ParabolicCoefficients get_max_bound<ParabolicCoefficients>()
{
    return ParabolicCoefficients(0,0,0);
}

template<> ParabolicCoefficients get_min_bound<ParabolicCoefficients>()
{
    return ParabolicCoefficients(0,0,0);
}


TEST_F(ParabolicInterpolationTest, example)
{
//! [ParabolicInterpolationTest example]
    std::vector<ParabolicCoefficients> v;
    v.push_back(ParabolicCoefficients(1,2,3));
    v.push_back(ParabolicCoefficients(4,5,6));
    v.push_back(ParabolicCoefficients(7,8,9));
    v.push_back(ParabolicCoefficients(10,11,12));
    ParabolicInterpolation pi(0,5,v);
//! [ParabolicInterpolationTest example]
//! [ParabolicInterpolationTest expected output]
    double x = 0.5;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(1*x*x+2*x+3, pi.f());
    x = 1.7;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(4*x*x+5*x+6, pi.f());
    x = 2.8;
    pi.set_computed_value(x);
    ASSERT_DOUBLE_EQ(7*x*x+8*x+9, pi.f());
//! [ParabolicInterpolationTest expected output]
}

TEST_F(ParabolicInterpolationTest, derivative)
{
    std::vector<ParabolicCoefficients> coeffs;
    coeffs.push_back(ParabolicCoefficients(12./5.,0,1./5.));
    coeffs.push_back(ParabolicCoefficients(-6.,84./5.,-41./5.));
    coeffs.push_back(ParabolicCoefficients(18./5.,-108./5.,151./5.));
    ParabolicInterpolation pp(0, 3, coeffs);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double X = a.random<double>().between(0,1);
        pp.set_computed_value(X);
        ASSERT_DOUBLE_EQ(2.*(12./5.)*X,pp.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double X = a.random<double>().between(1,2);
        pp.set_computed_value(X);
        ASSERT_DOUBLE_EQ((84./5.)-2.*6.*X,pp.df());
    }
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double X = a.random<double>().between(2,3);
        pp.set_computed_value(X);
        ASSERT_DOUBLE_EQ(-(108./5.)+2.*(18./5.)*X,pp.df());
    }
}

TEST_F(ParabolicInterpolationTest, should_throw_if_coeffs_has_too_few_elements)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = a.random<double>().greater_than(xmin);
        const size_t n = a.random<size_t>().no().greater_than(1);
        ASSERT_THROW(ParabolicInterpolation(xmin, xmax, a.random_vector_of<ParabolicCoefficients>().of_size(n)), ParabolicInterpolationException);
    }
}

TEST_F(ParabolicInterpolationTest, should_throw_if_xmin_greater_than_xmax)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmax = a.random<double>();
        const double xmin = a.random<double>().greater_than(xmax);
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        ASSERT_THROW(ParabolicInterpolation(xmin, xmax, a.random_vector_of<ParabolicCoefficients>().of_size(n)), ParabolicInterpolationException);
    }
}

TEST_F(ParabolicInterpolationTest, should_not_throw_if_xmin_equals_xmax)
{
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        const double xmin = a.random<double>();
        const double xmax = xmin;
        const size_t n = a.random<size_t>().greater_than(1).but().no().greater_than(1000);
        ASSERT_NO_THROW(ParabolicInterpolation(xmin, xmax, a.random_vector_of<ParabolicCoefficients>().of_size(n)));
    }
}
