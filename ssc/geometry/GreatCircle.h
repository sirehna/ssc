/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* GreatCircle class
*/

#pragma once

#include "ssc/geometry/LatitudeLongitude.hpp"
#include "ssc/geometry/Vector3D.h"
#include "ssc/geometry/Angle.h"

namespace Geometry {
	
	enum  GCIntersection { NoIntersection=0 , PointIntersection , LineIntersection };

	class GreatCircle {
	protected:
		ssc::geometry::LatitudeLongitude m_A;
		ssc::geometry::LatitudeLongitude m_B;
	public:
		GreatCircle(const ssc::geometry::LatitudeLongitude& pole );
		GreatCircle(const ssc::geometry::LatitudeLongitude& pointA , const ssc::geometry::LatitudeLongitude& pointB );
		GreatCircle(const ssc::geometry::LatitudeLongitude& pointA , const Angle& bearing );
		Vector3D          poleVector() const;
		ssc::geometry::LatitudeLongitude pole() const;
		ssc::geometry::LatitudeLongitude pointAtArcDistance(const  Angle& arcDistance ) const;
		Vector3D          tangentAtArcDistance(const  Angle& arcDistance ) const;
		Angle             bearingAtArcDistance(const  Angle& arcDistance ) const;
		ssc::geometry::LatitudeLongitude nearestPointTo(const ssc::geometry::LatitudeLongitude& pointC) const;
		GreatCircle       perpendicular(const ssc::geometry::LatitudeLongitude& pointC ) const;
		Angle             distanceToPoint(const ssc::geometry::LatitudeLongitude& pointC ) const;
		int               hemisphereSign(const ssc::geometry::LatitudeLongitude& pointC ) const;
		Angle             angleWith(const  GreatCircle& gc ) const;
		ssc::geometry::LatitudeLongitude intersectionWith(const  GreatCircle& gc ) const;
	};
	
	class GreatCircleArc {
	protected:
        ssc::geometry::LatitudeLongitude m_A;
        ssc::geometry::LatitudeLongitude m_B;
	public:
		GreatCircleArc(const ssc::geometry::LatitudeLongitude& pointA ,const ssc::geometry::LatitudeLongitude& pointB );
		GreatCircleArc(const ssc::geometry::LatitudeLongitude& pointA ,const Angle& bearing, const Angle& arcDistance );
		GreatCircle       asGreatCircle() const;
		Angle             arcLength() const;
		ssc::geometry::LatitudeLongitude middle() const;
		Angle             distanceToPoint(const ssc::geometry::LatitudeLongitude& pointC ) const;
		Angle             angleWith(const GreatCircle& gc ) const;
		Angle             angleWith(const GreatCircleArc& gca ) const;
		enum GCIntersection intersectionWith(const GreatCircleArc& gca , ssc::geometry::LatitudeLongitude &pointI , ssc::geometry::LatitudeLongitude &pointJ) const;
	};
	
}
