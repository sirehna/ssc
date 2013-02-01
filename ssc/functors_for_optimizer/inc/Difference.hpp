/*
 * Difference.hpp
 *
 * \date 1 févr. 2013, 09:22:47
 *  \author cec
 */

#ifndef DIFFERENCE_HPP_
#define DIFFERENCE_HPP_

#include "Sum.hpp"
/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/DifferenceTest.cpp DifferenceTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/DifferenceTest.cpp DifferenceTest expected output
 */

class Difference : public Sum
{
    public:
        Difference(const NodePtr& n1, const NodePtr& n2);
        std::string get_operator_name() const;
};

typedef std::tr1::shared_ptr<Difference> DiffPtr;

#endif /* DIFFERENCE_HPP_ */
