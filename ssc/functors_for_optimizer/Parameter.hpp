/*
 * Parameter.hpp
 *
 * \date 29 janv. 2013, 09:41:01
 * \author cec
 */

#ifndef PARAMETER_HPP_
#define PARAMETER_HPP_

#include "ssc/functors_for_optimizer/Nullary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/ConstantTest.cpp ConstantTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/ConstantTest.cpp ConstantTest expected output
 */
namespace ssc
{
    namespace functors_for_optimizer
    {
        class Parameter : public Nullary
        {
            public:
                Parameter(const double val);
                Parameter(const double val, const size_t index);
                Parameter(const Parameter& rhs);
                Parameter();
                ~Parameter();
                size_t get_index() const;
                Parameter& operator=(const Parameter& rhs);
                Parameter& operator=(const double rhs);
                bool operator<(const Parameter& rhs) const;
                NodePtr diff(const StatePtr& state) const;
                bool operator==(const Parameter& rhs) const;
                bool operator!=(const Parameter& rhs) const;
                void accept(NodeVisitor& v) const;
                NodePtr clone() const;
                bool is_null() const;
                bool equals(const Node& rhs) const;
                using Node::equals_derived;
                virtual bool equals_derived(const Parameter& rhs) const;
                std::string get_type() const;
                void update_lambda();

            protected:
                TR1(shared_ptr)<double> ptr;
                //friend double& operator*(const Parameter& s);
                int nb_of_copies;

            private:
                size_t index;

        };

        typedef TR1(shared_ptr)<Parameter> ParameterPtr;
    }
}
#endif /* PARAMETER_HPP_ */
