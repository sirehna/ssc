#ifndef __NODEHPP__
#define __NODEHPP__

#include <functional>
#include <vector>
#include <cstddef>

typedef std::function<double ()> ValType;

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

class Node
{
    public:
        virtual ~Node() {}
        virtual ValType val() const = 0;
        virtual Grad grad() const = 0;
        virtual Hes hes() const = 0;
};


#endif

