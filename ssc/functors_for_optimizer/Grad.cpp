/*
 * Grad.cpp
 *
 * \date 20 f�vr. 2013, 15:20:24
 *  \author cec
 */

#include "ssc/functors_for_optimizer/Grad.hpp"

Grad::Grad() : index(std::vector<size_t>()), values(std::vector<std::function<double()> >())
{

}

