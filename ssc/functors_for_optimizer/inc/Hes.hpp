/*
 * Hes.hpp
 *
 * \date 20 févr. 2013, 15:23:43
 *  \author cec
 */

#ifndef HES_HPP_
#define HES_HPP_

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/HesTest.cpp HesTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/HesTest.cpp HesTest expected output
 */
#include <vector>
#include <tr1/memory>
#include <functional>
class Node;
typedef std::tr1::shared_ptr<Node> NodePtr;


class Hes
{
    public:
        Hes();
        std::vector<size_t> row_index;
        std::vector<size_t> col_index;
        std::vector<std::function<double()> > values;
};

#endif /* HES_HPP_ */
