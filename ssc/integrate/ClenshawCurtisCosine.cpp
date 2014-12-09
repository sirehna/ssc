/*
 * ClenshawCurtisCosine.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: cady
 */

#include <ssc/integrate/ClenshawCurtisCosine.hpp>

ssc::integrate::ClenshawCurtisCosine::ClenshawCurtisCosine(const double tau) : ClenshawCurtis(tau)
{
}

ssc::integrate::ClenshawCurtisCosine::ClenshawCurtisCosine(const Function& f, const double tau) : ClenshawCurtis(f,tau)
{
}

int ssc::integrate::ClenshawCurtisCosine::get_internal_type_number() const
{
    return 1;
}

