/*
 * Hes.cpp
 *
 * \date 20 f�vr. 2013, 15:23:43
 *  \author cec
 */

#include "ssc/functors_for_optimizer/FunctionMatrix.hpp"

using namespace ssc::functors_for_optimizer;

FunctionMatrix::FunctionMatrix() : row_index(std::vector<size_t>()),
             col_index(std::vector<size_t>()),
             values(std::vector<std::function<double()> >())
{

}

