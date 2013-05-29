/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Spherical Geometry functions
*/

#pragma once

#include "Vector3D.h"
#include "LatitudeLongitude.hpp"
#include "GreatCircle.h"

namespace Geometry {

	const double ArcRadTolerance=1.57e-10; /* roughly equivalent to 1mm precision on Earth */
	
	Vector3D LLToCartesian(const LatitudeLongitude& point);
	
	LatitudeLongitude cartesianToLL(const Vector3D& v);
	
	Vector3D localTangentVector(const LatitudeLongitude& point,const Angle& bearing);
	
	Vector3D localNorthVector(const LatitudeLongitude& point);
	
	Vector3D localEastVector(const LatitudeLongitude& point);
	
	Angle greatCircleArcDistance(const LatitudeLongitude& pointA,const LatitudeLongitude& pointB);
	
	Angle angle(const LatitudeLongitude& pointA,const LatitudeLongitude& pointB,const LatitudeLongitude& pointC);
	
	GreatCircle bisector(const LatitudeLongitude& pointA,const LatitudeLongitude& pointB,const LatitudeLongitude& pointC);

}
