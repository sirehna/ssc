/*
 * generic_pimpl_implementation.hpp
 *
 * \date 8 oct. 2013, 09:04:58
 *  \author cec
 */

#ifndef GENERIC_PIMPL_IMPLEMENTATION_HPP_
#define GENERIC_PIMPL_IMPLEMENTATION_HPP_

#include <memory>

template<typename T>
class pimpl {
private:
    std::unique_ptr<T> m;
public:
    pimpl();
    template<typename ...Args> pimpl( Args&& ... );
    ~pimpl();
    T* operator->();
    T& operator*();
};

#endif /* GENERIC_PIMPL_IMPLEMENTATION_HPP_ */
