/*
 * test_systems.hpp
 *
 * \date 21 mars 2014
 *      Author: cec
 */

#ifndef TEST_SYSTEMS_HPP_
#define TEST_SYSTEMS_HPP_

typedef std::vector<double> StateType;

struct SimpleODE
{
    SimpleODE(const StateType& x0) : state(x0)
    {
    }

    void operator()(const StateType &x, StateType &dxdt, double )
    {
        state = x;
        dxdt[0] = 2;//*t;//2*x[0];
    }

    StateType state;
};

struct QuadraticODE
{
    QuadraticODE(const StateType& x0) : state(x0)
    {
    }

    void operator()(const StateType &x, StateType &dxdt, double t)
    {
        state = x;
        dxdt[0] = 2*t;
    }

    StateType state;
};



#endif /* TEST_SYSTEMS_HPP_ */
