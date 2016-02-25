/*
 * FunctorAlgebra.hpp
 *
 * \date 1 f�vr. 2013, 15:29:46
 *  \author cec
 */

#ifndef FUNCTORALGEBRA_HPP_
#define FUNCTORALGEBRA_HPP_

#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)

#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace functors_for_optimizer
    {
        class FunctorAlgebraException : public ssc::exception_handling::Exception
        {
            public:
                FunctorAlgebraException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line)
                {
                }
        };

        class Node;
        class Parameter;
        class Difference;
        class Sum;
        class Divide;
        class Multiply;
        class State;
        class Pow;
        class Null;
        class Constant;
        class Sin;
        class Cos;
        typedef TR1(shared_ptr)<Node> NodePtr;
        typedef TR1(shared_ptr)<Parameter> ParameterPtr;
        typedef TR1(shared_ptr)<Difference> DifferencePtr;
        typedef TR1(shared_ptr)<Sum> SumPtr;
        typedef TR1(shared_ptr)<Divide> DividePtr;
        typedef TR1(shared_ptr)<Multiply> Mult;
        typedef TR1(shared_ptr)<State> StatePtr;
        typedef TR1(shared_ptr)<Pow> PowPtr;
        typedef TR1(shared_ptr)<Null> NullPtr;
        typedef TR1(shared_ptr)<Constant> ConstantPtr;
        typedef TR1(shared_ptr)<Cos> CosPtr;
        typedef TR1(shared_ptr)<Sin> SinPtr;

        Mult operator*(const Node& n1, const Node& n2);
        Mult operator*(const Node& n1, const NodePtr& n2);
        Mult operator*(const NodePtr& n1, const NodePtr& n2);
        Mult operator*(const NodePtr& n1, const Node& n2);
        NodePtr operator*(const NodePtr& n, const double d);
        NodePtr operator*(const double d, const NodePtr& n);
        NodePtr operator*(const NodePtr& n1, const Null& n2);
        NodePtr operator*(const Null& n1, const NodePtr& n2);
        NodePtr operator*(const Node& n1, const Null& n2);
        NodePtr operator*(const Null& n1, const Node& n2);

        NodePtr operator*(const Node& n1, const Constant& n2);
        NodePtr operator*(const Constant& n1, const Node& n2);
        NodePtr operator*(const NodePtr& n1, const Constant& n2);

        NodePtr operator+(const Node& n1, const Node& n2);
        NodePtr operator+(const Node& n1, const NodePtr& n2);
        NodePtr operator+(const NodePtr& n1, const NodePtr& n2);
        NodePtr operator+(const NodePtr& n1, const Node& n2);
        NodePtr operator+(const NodePtr& n, const double d);
        NodePtr operator+(const double d, const NodePtr& n);

        NodePtr operator-(const double d, const NodePtr& n);
        NodePtr operator-(const NodePtr& n, const double d);
        NodePtr operator-(const NodePtr& n1, const NodePtr&n2);
        NodePtr operator-(const NodePtr& n, const Parameter&p);

        NodePtr operator/(const Node& n1, const Node& n2);
        NodePtr operator/(const Node& n1, const NodePtr& n2);
        NodePtr operator/(const NodePtr& n1, const NodePtr& n2);
        NodePtr operator/(const NodePtr& n1, const Node& n2);
        NodePtr operator/(const NodePtr& n, const double d);
        NodePtr operator/(const double d, const NodePtr& n);

        NodePtr pow(const Node& n1, const double d);
        NodePtr pow(const NodePtr& n1, const double d);
        NodePtr pow(const Node& n1, const Node& n2);
        NodePtr pow(const NodePtr& n1, const Node& n2);
        NodePtr pow(const Node& n1, const NodePtr& n2);
        NodePtr pow(const NodePtr& n1, const NodePtr& n2);

        //NullPtr sin(const NullPtr& n);
        NodePtr sin(const NodePtr& n);
        //NodePtr sin(const Node& n);

        NodePtr cos(const NodePtr& n);
        NodePtr cos(const Node& n);

        NodePtr sign(const NodePtr& n);

        NodePtr abs(const NodePtr& n);

        NodePtr sqrt(const NodePtr& n);
        NodePtr if_positive(const NodePtr& test, const NodePtr& positive, const NodePtr& negative);

        bool operator==(const NodePtr& n, const double v);
        bool operator==(const double v, const NodePtr& n);
        bool operator!=(const NodePtr& n, const double v);
        bool operator!=(const double v, const NodePtr& n);


        bool operator==(const NodePtr& n1, const NodePtr& n2);
        bool operator!=(const NodePtr& n1, const NodePtr& n2);
        bool operator==(const Node& n1, const Node& n2);
        bool operator!=(const Node& n1, const Node& n2);
        bool operator==(const NodePtr& n1, const double n2);
        bool operator!=(const Node& n1, const double n2);
    }
}

#endif /* FUNCTORALGEBRA_HPP_ */
