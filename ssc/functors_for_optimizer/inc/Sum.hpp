/*
 * Sum.hpp
 *
 * \date 31 janv. 2013, 16:05:52
 *  \author cec
 */

#ifndef SUM_HPP_
#define SUM_HPP_

#include "Binary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/SumTest.cpp SumTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/SumTest.cpp SumTest expected output
 */

class Sum : public Binary
{
    public:
        Sum(const NodePtr& n1, const NodePtr& n2);
        NodePtr diff(const StatePtr& state) const;
        std::string get_operator_name() const;
};

typedef std::tr1::shared_ptr<Sum> SumPtr;

#endif /* SUM_HPP_ */
