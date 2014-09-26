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
	
	Vector3D LLToCartesian(const ssc::geometry::LatitudeLongitude& point);
	
	ssc::geometry::LatitudeLongitude cartesianToLL(const Vector3D& v);
	
	Vector3D localTangentVector(const ssc::geometry::LatitudeLongitude& point,const Angle& bearing);
	
	Vector3D localNorthVector(const ssc::geometry::LatitudeLongitude& point);
	
	Vector3D localEastVector(const ssc::geometry::LatitudeLongitude& point);
	
	Angle greatCircleArcDistance(const ssc::geometry::LatitudeLongitude& pointA,const ssc::geometry::LatitudeLongitude& pointB);
	
	Angle angle(const ssc::geometry::LatitudeLongitude& pointA,const ssc::geometry::LatitudeLongitude& pointB,const ssc::geometry::LatitudeLongitude& pointC);
	
	GreatCircle bisector(const ssc::geometry::LatitudeLongitude& pointA,const ssc::geometry::LatitudeLongitude& pointB,const ssc::geometry::LatitudeLongitude& pointC);

}
