/*
 * PiecewiseLinearFunctor.hpp
 *
 * \date 19 f�vr. 2013, 08:35:13
 *  \author cec
 */

#ifndef PIECEWISELINEARFUNCTOR_HPP_
#define PIECEWISELINEARFUNCTOR_HPP_

#include "ssc/interpolation/LinearInterpolation.hpp"

#include "Unary.hpp"

class State;

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseLinearFunctorTest.cpp PiecewiseLinearFunctorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseLinearFunctorTest.cpp PiecewiseLinearFunctorTest expected output
 */

class PiecewiseLinearFunctor : public Unary
{
    public:
        PiecewiseLinearFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values);
        NodePtr diff(const StatePtr& state) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
        using Unary::equals_derived;
        bool equals_derived(const PiecewiseLinearFunctor& rhs) const;
        std::string get_type() const;
        std::string get_operator_name() const;
        void update_lambda();
    private:
        PiecewiseLinearFunctor();
        TR1(shared_ptr)<ssc::interpolation::LinearInterpolation> f;
        double xmin_;
        double xmax_;
        std::vector<double> dy;
        StatePtr state;

};

#endif /* PIECEWISELINEARFUNCTOR_HPP_ */
