/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* GreatCircle class
*/

#pragma once

#include "LatitudeLongitude.hpp"
#include "Vector3D.h"
#include "Angle.h"

namespace Geometry {
	
	enum  GCIntersection { NoIntersection=0 , PointIntersection , LineIntersection };

	class GreatCircle {
	protected:
		LatitudeLongitude m_A;
		LatitudeLongitude m_B;
	public:
		GreatCircle(const LatitudeLongitude& pole );
		GreatCircle(const LatitudeLongitude& pointA , const LatitudeLongitude& pointB );
		GreatCircle(const LatitudeLongitude& pointA , const Angle& bearing );
		Vector3D          poleVector() const;
		LatitudeLongitude pole() const;
		LatitudeLongitude pointAtArcDistance(const  Angle& arcDistance ) const;
		Vector3D          tangentAtArcDistance(const  Angle& arcDistance ) const;
		Angle             bearingAtArcDistance(const  Angle& arcDistance ) const;
		LatitudeLongitude nearestPointTo(const LatitudeLongitude& pointC) const;
		GreatCircle       perpendicular(const LatitudeLongitude& pointC ) const;
		Angle             distanceToPoint(const LatitudeLongitude& pointC ) const;
		int               hemisphereSign(const LatitudeLongitude& pointC ) const;
		Angle             angleWith(const  GreatCircle& gc ) const;
		LatitudeLongitude intersectionWith(const  GreatCircle& gc ) const;
	};
	
	class GreatCircleArc {
	protected:
		LatitudeLongitude m_A;
		LatitudeLongitude m_B;
	public:
		GreatCircleArc(const LatitudeLongitude& pointA ,const LatitudeLongitude& pointB );
		GreatCircleArc(const LatitudeLongitude& pointA ,const Angle& bearing, const Angle& arcDistance );
		GreatCircle       asGreatCircle() const;
		Angle             arcLength() const;
		LatitudeLongitude middle() const;
		Angle             distanceToPoint(const LatitudeLongitude& pointC ) const;
		Angle             angleWith(const GreatCircle& gc ) const;
		Angle             angleWith(const GreatCircleArc& gca ) const;
		enum GCIntersection intersectionWith(const GreatCircleArc& gca , LatitudeLongitude &pointI , LatitudeLongitude &pointJ) const;
	};
	
}
