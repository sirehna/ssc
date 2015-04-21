/*
 * Nullary.hpp
 *
 * \date 29 janv. 2013, 09:38:54
 *  \author cec
 */

#ifndef NULLARY_HPP_
#define NULLARY_HPP_

#include "ssc/functors_for_optimizer/Node.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/NullaryTest.cpp NullaryTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/NullaryTest.cpp NullaryTest expected output
 */

class Nullary : public Node
{

    public:
        Nullary();
        Nullary(const double& val);
        void set_value(const std::function<double()>& val);
        ~Nullary() {}
};

#endif /* NULLARY_HPP_ */
