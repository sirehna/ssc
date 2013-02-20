/*
 * CubicSplineFunctor.hpp
 *
 * \date 19 févr. 2013, 09:39:25
 *  \author cec
 */

#ifndef SPLINEFUNCTOR_HPP_
#define SPLINEFUNCTOR_HPP_

#include "Unary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/CubicSplineFunctorTest.cpp CubicSplineFunctorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/CubicSplineFunctorTest.cpp CubicSplineFunctorTest expected output
 */
class NaturalSplines;

class SplineFunctor : public Unary
{
    public:
        SplineFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<double>& y_values);
        NodePtr diff(const StatePtr& state) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
        using Unary::equals_derived;
        bool equals_derived(const SplineFunctor& rhs) const;
        std::string get_type() const;
        std::string get_operator_name() const;
    private:
        SplineFunctor();
        std::tr1::shared_ptr<NaturalSplines> f;
        double xmin_;
        double xmax_;
        std::vector<double> dy;

};


#endif /* SPLINEFUNCTOR_HPP_ */
