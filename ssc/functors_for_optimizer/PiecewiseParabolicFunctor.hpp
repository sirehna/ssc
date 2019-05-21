/*
 * PiecewiseParabolicFunctor.hpp
 *
 * \date 19 févr. 2013, 14:44:08
 * \author cec
 */

#ifndef PIECEWISEPARABOLICFUNCTOR_HPP_
#define PIECEWISEPARABOLICFUNCTOR_HPP_

#include "ssc/functors_for_optimizer/Unary.hpp"
#include "ssc/interpolation/ParabolicInterpolation.hpp"

namespace ssc
{
    namespace functors_for_optimizer
    {
        class State;

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
                PiecewiseParabolicFunctor(const StatePtr& state, const double& xmin, const double& xmax, const std::vector<ssc::interpolation::ParabolicCoefficients>& coeffs);
                NodePtr diff(const StatePtr& state) const;
                void accept(NodeVisitor& v) const;
                NodePtr clone() const;
                bool is_null() const;
                using Unary::equals_derived;
                bool equals_derived(const PiecewiseParabolicFunctor& rhs) const;
                std::string get_type() const;
                std::string get_operator_name() const;
                void update_lambda();
            private:
                PiecewiseParabolicFunctor();
                TR1(shared_ptr)<ssc::interpolation::ParabolicInterpolation> f;
                double xmin_;
                double xmax_;
                std::vector<double> dy;
                TR1(shared_ptr)<State> state;
        };
    }
}

#endif /* PIECEWISEPARABOLICFUNCTOR_HPP_ */
