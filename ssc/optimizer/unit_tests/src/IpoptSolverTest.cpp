/*
 * IpoptSolverTest.cpp
 *
 * \date 22 févr. 2013, 15:28:17
 *  \author cec
 */

#include "IpoptSolverTest.hpp"
#include "IpoptSolver.hpp"
#include "OptimizationProblem.hpp"
#include "OptimizationResult.hpp"

#include "extra_test_assertions.hpp"

IpoptSolverTest::IpoptSolverTest() : a(DataGenerator(56)),
                                     generate(StateGenerator()),
                                     x1(generate.state("x1")),
                                     x2(generate.state("x2")),
                                     x3(generate.state("x3")),
                                     x4(generate.state("x4"))
{
}

IpoptSolverTest::~IpoptSolverTest()
{
}

void IpoptSolverTest::SetUp()
{
}

void IpoptSolverTest::TearDown()
{
}

TEST_F(IpoptSolverTest, example)
{
//! [IpoptSolverTest example]
    OptimizationProblem hs71;
    hs71.minimize(x1*x4*(x1+x2+x3)+x3)
        .subject_to(25,x1*x2*x3*x4)
        .subject_to(40,pow(x1,2)+pow(x2,2)+pow(x3,2)+pow(x4,2),40)
        .bound_state(1,x1,5)
        .bound_state(1,x2,5)
        .bound_state(1,x3,5)
        .bound_state(1,x4,5);
    IpoptSolver optimize(hs71);
    const std::vector<double> x0({1,5,5,1});
    COUT("");
    const auto result = optimize.solve(x0);
    COUT("");
//! [IpoptSolverTest example]
//! [IpoptSolverTest expected output]
    const double eps = 1e-6;
    COUT("");
    ASSERT_EQ(4, result.state_values.size());
    ASSERT_DOUBLE_EQ(1,result.state_values.at(0));
    ASSERT_SMALL_RELATIVE_ERROR(4.74299963,result.state_values.at(1),eps);
    ASSERT_SMALL_RELATIVE_ERROR(3.82114998,result.state_values.at(2),eps);
    ASSERT_SMALL_RELATIVE_ERROR(1.37940829,result.state_values.at(3),eps);
    COUT("");
//! [IpoptSolverTest expected output]
}
/*
TEST_F(IpoptSolverTest, test_01)
{
    OptimizationProblem pb;
    Parameter c0(2);
    pb.minimize(pow(x1*x1-c0.clone(),2));
    IpoptSolver optimize(pb);
    const std::vector<double> x0({0});
    const double eps = 1e-6;
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        *c0 = a.random<double>().between(0,100);
        const auto result = optimize.solve(x0);
        ASSERT_SMALL_RELATIVE_ERROR(sqrt(*c0),result.state_values.at(0),eps);
    }
}
*/
