/*
 * almost_equalTest.hpp
 *
 * \date 26 nov. 2013, 08:41:26
 *  \author cec
 */

#ifndef ALMOST_EQUALTEST_HPP_
#define ALMOST_EQUALTEST_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class almost_equalTest : public ::testing::Test
{
    protected:
        almost_equalTest();
        virtual ~almost_equalTest();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;
        double very_slightly_less_than(const double x) const;
        double very_slightly_greater_than(const double x) const;
        double slightly_less_than(double x) const;
        double slightly_greater_than(double x) const;

};

#endif  /* ALMOST_EQUALTEST_HPP_ */
