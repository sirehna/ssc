/*
 * PiecewiseConstantFunctor.hpp
 *
 * \date 18 févr. 2013, 17:29:41
 *  \author cec
 */

#ifndef PIECEWISECONSTANTFUNCTOR_HPP_
#define PIECEWISECONSTANTFUNCTOR_HPP_

#include "Unary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseConstantFunctorTest.cpp PiecewiseConstantFunctorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseConstantFunctorTest.cpp PiecewiseConstantFunctorTest expected output
 */

class PiecewiseConstant;
class State;

class PiecewiseConstantFunctor : public Unary
{
    public:
        PiecewiseConstantFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values);
        NodePtr diff(const StatePtr& state) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
        using Unary::equals_derived;
        bool equals_derived(const PiecewiseConstantFunctor& rhs) const;
        std::string get_type() const;
        std::string get_operator_name() const;
        void update_lambda();
    private:
        PiecewiseConstantFunctor();
        std::tr1::shared_ptr<PiecewiseConstant> f;
        std::tr1::shared_ptr<State> state;

};

#endif /* PIECEWISECONSTANTFUNCTOR_HPP_ */
