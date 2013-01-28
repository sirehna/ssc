#ifndef __NODEHPP__
#define __NODEHPP__

#include <functional>
#include <vector>
#include <cstddef>


class ValType
{
    public:
        ValType();
        ValType(const std::function<double ()>& f);
        ValType(const double& l, const std::function<double ()>& f);
        double operator()() const;
        ValType operator*(const double& l) const;
        friend ValType operator*(const double& l, const ValType& v);
    private:
        double lambda;
        std::function<double ()> _f;
};

ValType operator*(const double& l, const ValType& v);

struct Grad
{
    Grad() : idx(std::vector<size_t>()), values(std::vector<ValType>()) {}
    std::vector<size_t> idx;
    std::vector<ValType> values;
};

struct Hes
{
    Hes() : row_idx(std::vector<size_t>()), col_idx(std::vector<size_t>()), values(std::vector<ValType>()) {}
    std::vector<size_t> row_idx;
    std::vector<size_t> col_idx;
    std::vector<ValType> values;
};

class NodeAbstractVisitor;

class Node
{
    public:
        Node() : lambda(1) {}
        virtual ~Node() {}
        virtual ValType val() const = 0;
        virtual Grad grad() const = 0;
        virtual Hes hes() const = 0;
        virtual void accept(NodeAbstractVisitor& v) const = 0;
        virtual Node* clone() const = 0;

    protected:
        double lambda;
};

#endif

