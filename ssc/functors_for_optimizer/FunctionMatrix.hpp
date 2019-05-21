/*
 * FunctionMatrix.hpp
 *
 * \date 20 févr. 2013, 15:23:43
 * \author cec
 */

#ifndef FUNCTIONMATRIX_HPP_
#define FUNCTIONMATRIX_HPP_

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
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <functional>


namespace ssc
{
    namespace functors_for_optimizer
    {
        class Node;
        typedef TR1(shared_ptr)<Node> NodePtr;


        template <typename T> class FunctionMatrix
        {
            public:
                FunctionMatrix() : row_index(), col_index(), values() {}
                std::vector<size_t> row_index;
                std::vector<size_t> col_index;
                std::vector<T> values;
        };
    }
}

#endif /* FUNCTIONMATRIX_HPP_ */
