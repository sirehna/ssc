/*
 * generic_pimpl.hpp
 *
 * \date 8 oct. 2013, 09:02:01
 *  \author cec
 */

#ifndef GENERIC_PIMPL_HPP_
#define GENERIC_PIMPL_HPP_

// From http://herbsutter.com/gotw/_101/

<<<<<<< HEAD
#include <memory>

template<typename T> class Pimpl
{
    private:
        std::unique_ptr<T> m;
    public:
        Pimpl();
        template<typename ...Args> Pimpl( Args&& ... );
        ~Pimpl();
        T* operator->();
        T& operator*();
};
=======
#include <utility>

template<typename T>
pimpl<T>::pimpl() : m{ new T{} } { }

template<typename T>
template<typename ...Args>
pimpl<T>::pimpl( Args&& ...args )
    : m{ new T{ std::forward<Args>(args)... } } { }

template<typename T>
pimpl<T>::~pimpl() { }

template<typename T>
T* pimpl<T>::operator->() { return m.get(); }

template<typename T>
T& pimpl<T>::operator*() { return *m.get(); }

>>>>>>> Added Herb Sutter's generic pimpl

#endif /* GENERIC_PIMPL_HPP_ */
