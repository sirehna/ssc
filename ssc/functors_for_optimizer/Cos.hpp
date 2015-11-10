/*
 * Cos.hpp
 *
 * \date 1 f�vr. 2013, 14:40:27
 *  \author cec
 */

#ifndef COS_HPP_
#define COS_HPP_

#include "ssc/functors_for_optimizer/Unary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/CosTest.cpp CosTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/CosTest.cpp CosTest expected output
 */

namespace ssc
{
    namespace functors_for_optimizer
    {
        class Cos : public Unary
        {
            public:
                Cos(const NodePtr& n_);
                std::string get_operator_name() const;
                NodePtr diff(const StatePtr& state) const;
                NodePtr clone() const;
                bool is_null() const;
                std::string get_type() const;
                void update_lambda();
        };

        typedef TR1(shared_ptr)<Cos> CosPtr;
    }
}

#endif /* COS_HPP_ */
