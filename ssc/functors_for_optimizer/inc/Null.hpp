/*
 * Null.hpp
 *
 * \date 29 janv. 2013, 09:40:10
 *  \author cec
 */

#ifndef NULL_HPP_
#define NULL_HPP_

#include "Nullary.hpp"

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/NullTest.cpp NullTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/NullTest.cpp NullTest expected output
 */

class Null : public Nullary
{
    public:
        Null();
        NodePtr diff(const StatePtr& state) const;
        void accept(NodeVisitor& v) const;
        NodePtr clone() const;
        bool is_null() const;
};

typedef std::tr1::shared_ptr<Null> NullPtr;

#endif /* NULL_HPP_ */
