/*
 * Multiply.hpp
 *
 * \date 23 janv. 2013, 08:29:31
 *  \author cec
 */

#ifndef MULTIPLY_HPP_
#define MULTIPLY_HPP_
#include "Node.hpp"
#include <tr1/memory>

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/MultiplyTest.cpp MultiplyTest expected output
 */

class Multiply : public Node
{
    public:
        Multiply(const Node& n1_, const Node& n2_);
        ValType val() const;
        Grad grad() const;
        Hes hes() const;
        void accept(NodeAbstractVisitor& v) const;
        std::vector<std::tr1::shared_ptr<Node> > get_children() const;
        Node* clone() const;

    private:
        Multiply();
        Grad calculate_df(const Node& n1, const Node& n2) const;
        void fetch_extra_elements_if_vectors_have_different_nb_of_elements(size_t& k, const Node& A, const Node& B, size_t& kc, Grad& C) const;

        std::vector<std::tr1::shared_ptr<Node> > children;
        std::vector<ValType> v;
        std::vector<Grad> dv;
        std::vector<Hes> d2v;


        ValType f;
        Grad df;
        Hes d2f;
};

#endif /* MULTIPLY_HPP_ */
