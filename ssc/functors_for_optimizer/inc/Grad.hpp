/*
 * Grad.hpp
 *
 * \date 20 févr. 2013, 15:20:24
 *  \author cec
 */

#ifndef GRAD_HPP_
#define GRAD_HPP_

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/GradTest.cpp GradTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/GradTest.cpp GradTest expected output
 */

#include <vector>
#include <tr1/memory>
#include <functional>
class Node;
typedef std::tr1::shared_ptr<Node> NodePtr;

class Grad
{
    public:
        Grad();
        std::vector<size_t> index;
        std::vector<std::function<double()> > values;
};

#endif /* GRAD_HPP_ */
