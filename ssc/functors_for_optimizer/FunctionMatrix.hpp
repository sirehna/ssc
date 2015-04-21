/*
 * Hes.hpp
 *
 * \date 20 f�vr. 2013, 15:23:43
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
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <functional>


namespace ssc
{
    namespace functors_for_optimizer
    {
        class Node;
        typedef TR1(shared_ptr)<Node> NodePtr;


        class FunctionMatrix
        {
            public:
                FunctionMatrix();
                std::vector<size_t> row_index;
                std::vector<size_t> col_index;
                std::vector<std::function<double()> > values;
        };
    }
}

#endif /* HES_HPP_ */
