/*
 * Multiply.hpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#ifndef MULTIPLY_HPP_
#define MULTIPLY_HPP_
#include "Binary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest expected output
 */

class Multiply : public Binary
{
    public:
        Multiply(const NodePtr& n1, const NodePtr& n2);
        NodePtr diff(const StatePtr& state) const;
        std::string get_operator_name() const;

};

typedef std::tr1::shared_ptr<Multiply> Mult;

#endif /* MULTIPLY_HPP_ */
