/*
 * generic_pimpl_implementation.hpp
 *
 * \date 8 oct. 2013, 09:04:58
 *  \author cec
 */

#ifndef GENERIC_PIMPL_IMPLEMENTATION_HPP_
#define GENERIC_PIMPL_IMPLEMENTATION_HPP_

<<<<<<< HEAD
#include <utility>

template<typename T>
Pimpl<T>::Pimpl() : m{ new T{} } { }

template<typename T>
template<typename ...Args>
Pimpl<T>::Pimpl( Args&& ...args )
    : m{ new T{ std::forward<Args>(args)... } } { }

template<typename T>
Pimpl<T>::~Pimpl() { }

template<typename T>
T* Pimpl<T>::operator->() { return m.get(); }

template<typename T>
T& Pimpl<T>::operator*() { return *m.get(); }
=======
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
>>>>>>> Added Herb Sutter's generic pimpl

#endif /* GENERIC_PIMPL_IMPLEMENTATION_HPP_ */
