/*
 * Hes.cpp
 *
 * \date 20 févr. 2013, 15:23:43
 *  \author cec
 */

#include "Hes.hpp"

Hes::Hes() : row_index(std::vector<size_t>()),
             col_index(std::vector<size_t>()),
             values(std::vector<std::function<double()> >())
{

}

