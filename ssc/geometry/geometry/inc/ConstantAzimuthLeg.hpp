/*
 * ConstantAzimuthLeg.hpp
 *
 *  Created on: May 14, 2014
 *      Author: cady
 */

#ifndef CONSTANTAZIMUTHLEG_HPP_
#define CONSTANTAZIMUTHLEG_HPP_

#include "Leg.hpp"

/** \author cec
 *  \date May 14, 2014, 11:04:10 AM
 *  \brief Loxodrome curve between two points on the WGS84 ellipsoid.
 *  \ingroup geometry
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/ConstantAzimuthLegTest.cpp ConstantAzimuthLegTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/ConstantAzimuthLegTest.cpp ConstantAzimuthLegTest expected output
 */
class ConstantAzimuthLeg : public Leg
{
    public:
        ConstantAzimuthLeg();

    private:
};

#endif /* CONSTANTAZIMUTHLEG_HPP_ */
