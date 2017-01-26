/*
 * LPSolverTests.hpp
 *
 * \date 20 nov. 2013, 14:01:54
 *  \author cec
 */

#ifndef LPSOLVERTESTS_HPP_
#define LPSOLVERTESTS_HPP_

#include "gtest/gtest.h"
#include "DataGenerator.hpp"

class LPSolverTests : public ::testing::Test
{
    protected:
        LPSolverTests();
        virtual ~LPSolverTests();
        virtual void SetUp();
        virtual void TearDown();
        DataGenerator a;

};

#endif  /* LPSOLVERTESTS_HPP_ */
