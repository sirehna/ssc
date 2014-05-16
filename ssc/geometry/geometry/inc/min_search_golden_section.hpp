/*
 * min_search_golden_section.hpp
 *
 *  Created on: May 16, 2014
 *      Author: cady
 */

#ifndef MIN_SEARCH_GOLDEN_SECTION_HPP_
#define MIN_SEARCH_GOLDEN_SECTION_HPP_

#include <float.h>                          // required for DBL_EPSILON
#include <math.h>                           // required for fabs(), sqrt()

#define SQRT5 2.23606797749978969640

static int Stopping_Rule(double x0, double x1, double tolerance)
{
    double xm = 0.5 * fabs( x1 + x0 );
    if ( xm <= 1.0 ) return ( fabs( x1 - x0 ) < tolerance ) ? 1 : 0;
    return ( fabs( x1 - x0 ) < tolerance * xm ) ? 1 : 0;
}

template <typename F> double min_search_golden_section(const F& f, double a, double b, const double tolerance)
{
    static const double lambda = 0.5 * (SQRT5 - 1.0);
    static const double mu = 0.5 * (3.0 - SQRT5);         // = 1 - lambda
    double x1;
    double x2;
    double fx1;
    double fx2;


    // Find first two internal points and evaluate
    // the function at the two internal points.

    x1 = b - lambda * (b - a);
    x2 = a + lambda * (b - a);
    fx1 = f(x1);
    fx2 = f(x2);

    // Verify that the tolerance is an acceptable number

    //if (tolerance <= 0.0) tolerance = sqrt(DBL_EPSILON) * (b - a);

    // Loop by exluding segments from current endpoints a, b
    // to current internal points x1, x2 and then calculating
    // a new internal point until the length of the interval
    // is less than or equal to the tolerance.

    while ( ! Stopping_Rule(a, b, tolerance) )
    {
        if (fx1 > fx2)
        {
            a = x1;
            if ( Stopping_Rule(a, b, tolerance) ) break;
            x1 = x2;
            fx1 = fx2;
            x2 = b - mu * (b - a);
            fx2 = f(x2);
        }
        else
        {
            b = x2;
            if ( Stopping_Rule(a, b, tolerance) ) break;
            x2 = x1;
            fx2 = fx1;
            x1 = a + mu * (b - a);
            fx1 = f(x1);
        }
    }
    return (a+b)/2.;
}

#endif /* MIN_SEARCH_GOLDEN_SECTION_HPP_ */
