/*
 * PiecewiseParabolicFunctor.hpp
 *
 * \date 19 févr. 2013, 14:44:08
 *  \author cec
 */

#ifndef PIECEWISEPARABOLICFUNCTOR_HPP_
#define PIECEWISEPARABOLICFUNCTOR_HPP_

#include "Unary.hpp"
#include "ParabolicCoefficients.hpp"
class ParabolicInterpolation;

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseParabolicFunctorTest.cpp PiecewiseParabolicFunctorTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/PiecewiseParabolicFunctorTest.cpp PiecewiseParabolicFunctorTest expected output
 */

class PiecewiseParabolicFunctor : public Unary
{
    public:
        PiecewiseParabolicFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<ParabolicCoefficients>& coeffs);
        NodePtr diff(const StatePtr& state) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
        using Unary::equals_derived;
        bool equals_derived(const PiecewiseParabolicFunctor& rhs) const;
        std::string get_type() const;
        std::string get_operator_name() const;
    private:
        PiecewiseParabolicFunctor();
        std::tr1::shared_ptr<ParabolicInterpolation> f;
        double xmin_;
        double xmax_;
        std::vector<double> dy;
};

#endif /* PIECEWISEPARABOLICFUNCTOR_HPP_ */
