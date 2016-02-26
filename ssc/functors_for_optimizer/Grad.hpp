/*
 * Grad.hpp
 *
 * \date 20 f�vr. 2013, 15:20:24
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
#include "ssc/macros/tr1_macros.hpp"
#include TR1INC(memory)
#include <functional>

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Node;
        typedef TR1(shared_ptr)<Node> NodePtr;

        template <typename T> class Grad
        {
            public:
                Grad() : index(), values() {}
                std::vector<size_t> index;
                std::vector<T> values;
        };
    }
}

#endif /* GRAD_HPP_ */
