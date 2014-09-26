/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* GreatCircle class
*/

#include "GreatCircle.h"
#include "Geometry.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define PI 4.*atan(1.)

using namespace Geometry;

using namespace ssc::geometry;

GreatCircle::GreatCircle(const LatitudeLongitude& pole ) : m_A(pole), m_B(pole){
	double latDeg=pole.lat*180./PI;
	m_A = LatitudeLongitude(
		(latDeg>=0.0)
		? latDeg - 90.0
		: latDeg + 90.0,
		pole.lon);
	Vector3D vectorB = crossProduct( LLToCartesian(pole) , LLToCartesian(m_A) );
	m_B=cartesianToLL( vectorB );
}

GreatCircle::GreatCircle(const LatitudeLongitude& pointA , const LatitudeLongitude& pointB )  : m_A(pointA), m_B(pointB){
	Vector3D vectorA = LLToCartesian(pointA);
	Vector3D vectorB = LLToCartesian(pointB);
	Vector3D vectorP = crossProduct( vectorA , vectorB );
	double sinDist = std::sqrt( dotProduct(vectorP,vectorP) );
	if( std::fabs(sinDist) < ArcRadTolerance ) {
		//fprintf(stderr,"ERROR in GreatCircle constructor: pointB too close to pointA (or antipode) \n");
	}
	vectorP /= sinDist;
	vectorB = crossProduct(vectorP,vectorA);
	m_B=cartesianToLL( vectorB );
}


GreatCircle::GreatCircle(const LatitudeLongitude& pointA , const Angle& bearing ) : m_A(pointA), m_B(pointA)
        {
	Vector3D tgA = localTangentVector(pointA,bearing);
	m_A = pointA;
	m_B=cartesianToLL( tgA );
}

LatitudeLongitude GreatCircle::pointAtArcDistance(const Angle& arcDistance ) const {
	return cartesianToLL(
		LLToCartesian(m_A)*arcDistance.cos()+LLToCartesian(m_B)*arcDistance.sin());
}

Vector3D GreatCircle::tangentAtArcDistance(const Angle& arcDistance ) const {
	Vector3D vectorA = LLToCartesian(m_A);
	Vector3D vectorB = LLToCartesian(m_B);
	Vector3D vectorP = crossProduct( vectorA , vectorB );
	Vector3D vectorC = vectorA*arcDistance.cos()+vectorB*arcDistance.sin();
	return crossProduct( vectorP,vectorC );
}

Angle GreatCircle::bearingAtArcDistance(const Angle& arcDistance ) const {
	Vector3D vectorA = LLToCartesian(m_A);
	Vector3D vectorB = LLToCartesian(m_B);
	Vector3D vectorP = crossProduct( vectorA , vectorB );
	Vector3D vectorC = vectorA*arcDistance.cos()+vectorB*arcDistance.sin();
	Vector3D tgC = crossProduct( vectorP,vectorC );
	Vector3D northC = localNorthVector( cartesianToLL(vectorC) );
	return angle_acos(dotProduct(tgC,northC));
}

Vector3D GreatCircle::poleVector() const {
	return crossProduct( LLToCartesian(m_A),LLToCartesian(m_B) );
}

LatitudeLongitude GreatCircle::pole() const {
	return cartesianToLL(poleVector());
}

LatitudeLongitude GreatCircle::nearestPointTo(const LatitudeLongitude& pointC) const {
	return perpendicular(pointC).pointAtArcDistance( Angle(Degrees(90.0)) );
}

GreatCircle GreatCircle::perpendicular(const LatitudeLongitude& pointC) const {
	return GreatCircle(pole(),pointC);
}

Angle GreatCircle::distanceToPoint(const LatitudeLongitude& pointC ) const {
	LatitudeLongitude p=pole();
	Angle dist=greatCircleArcDistance( p , pointC );
	return Angle(Degrees(90.0)) - dist;
}

int GreatCircle::hemisphereSign(const LatitudeLongitude& pointC ) const {
	Vector3D leftPoleVector=poleVector();
	double cos=dotProduct( leftPoleVector , LLToCartesian(pointC) );
	return (cos>ArcRadTolerance) ? -1 : ((cos < -ArcRadTolerance) ?+1 : 0);
}

Angle GreatCircle::angleWith(const GreatCircle& gc ) const {
	Vector3D poleA=poleVector();
	Vector3D poleB=gc.poleVector();
	Vector3D inter=crossProduct( poleA,poleB );
	if( inter.norm() < ArcRadTolerance) {
		// same circle...
		return Angle(Radians( 0.0 ));
	}
	inter.normalize();
	Vector3D pA=crossProduct( poleA,inter );
	Vector3D pB=crossProduct( inter,poleB );
	return angle( cartesianToLL(pA) , cartesianToLL(inter) , cartesianToLL(pB) );
}

LatitudeLongitude GreatCircle::intersectionWith(const GreatCircle& gc ) const {
	Vector3D poleA=poleVector();
	Vector3D poleB=gc.poleVector();
	Vector3D inter=crossProduct( poleA,poleB );
	if( inter.norm() < ArcRadTolerance) {
		// same circle...
		return m_A;
	}
	inter.normalize();
	return cartesianToLL(inter);
}

//
// class GreatCircleArc
//

GreatCircleArc::GreatCircleArc(const LatitudeLongitude& pointA, const LatitudeLongitude& pointB )
: m_A(pointA),
  m_B(pointB)
{}


GreatCircleArc::GreatCircleArc(const LatitudeLongitude& pointA, const Angle& bearing, const Angle& arcDistance) :
    m_A(pointA),
    m_B(pointA)
        {
	GreatCircle gc=GreatCircle(pointA,bearing);
	m_B=gc.pointAtArcDistance( arcDistance );
}

GreatCircle GreatCircleArc::asGreatCircle() const {
	return GreatCircle( m_A , m_B );
}

Angle GreatCircleArc::arcLength() const {
	return greatCircleArcDistance( m_A , m_B );
}

LatitudeLongitude GreatCircleArc::middle() const {
	GreatCircle gc=this->asGreatCircle();
	return gc.pointAtArcDistance( arcLength()/2.0 );
}

// distance of a point C to a segment (arc)
// if orthogonal projection J of point C on greatCircle(A,B) lie between A and B,
// then answer the distance to the great circle
// else answer the minimum distance (A,C) or (B,C)
//
// in order to check if projection J is inside the segment (A,B),
// we compare distance toward the middle I:
// dist(I,J) <= dist(A,B) / 2
//
Angle GreatCircleArc::distanceToPoint(const LatitudeLongitude& pointC ) const {
	GreatCircle gc=this->asGreatCircle();
	LatitudeLongitude pointI=middle();
	LatitudeLongitude pointJ=gc.nearestPointTo(pointC);
	Angle dIJ = greatCircleArcDistance( pointI,pointJ );
	Angle l2 = arcLength() / 2;
	return ( dIJ <= l2 )
		? gc.distanceToPoint( pointC )
		: min(
				greatCircleArcDistance(m_A,pointC),
				greatCircleArcDistance(m_B,pointC));
}


Angle GreatCircleArc::angleWith(const GreatCircle& gc) const {
	return (this->asGreatCircle()).angleWith(gc);
}

Angle GreatCircleArc::angleWith(const GreatCircleArc& gca) const {
	return (this->asGreatCircle()).angleWith(gca.asGreatCircle());
}

enum GCIntersection GreatCircleArc::intersectionWith(const  GreatCircleArc& gca , LatitudeLongitude &pointI , LatitudeLongitude &pointJ) const {
	Vector3D vA = LLToCartesian( m_A );
	Vector3D vB = LLToCartesian( m_B );
	Vector3D vP = crossProduct( vA , vB );
	vP.normalize();
	Vector3D vC = LLToCartesian( gca.m_A );
	Vector3D vD = LLToCartesian( gca.m_B );
	double pc=dotProduct( vP , vC );
	double pd=dotProduct( vP , vD );
	if (
		( pc > +ArcRadTolerance && pd > +ArcRadTolerance ) ||
		( pc < -ArcRadTolerance && pd < -ArcRadTolerance )) {
		// both points C and D lie in same hemisphere of GreatCircle(A,B)
		return NoIntersection;
	} else {
		Vector3D vM=LLToCartesian(middle());
		double limit=dotProduct(vA,vM);
		if ( std::fabs(pc) < ArcRadTolerance ) {
			if( std::fabs(pd) < ArcRadTolerance ) {
				// both point C and D are on GreatCircle(A,B)
				bool CinAB = dotProduct(vM,vC) >= limit;
				bool DinAB = dotProduct(vM,vD) >= limit;
				if( CinAB && DinAB ) {
					pointI=gca.m_A;
					pointJ=gca.m_B;
					return LineIntersection;
				} else {
					Vector3D vN=LLToCartesian(gca.middle());
					double limit2=dotProduct(vC,vN);
					bool AinCD = dotProduct(vN,vA) >= limit2;
					bool BinCD = dotProduct(vN,vB) >= limit2;
					if( AinCD & BinCD ) {
						pointI=m_A;
						pointJ=m_B;
						return LineIntersection;
					} else if( AinCD ) {
						pointI=m_A;
						pointJ=(CinAB) ? gca.m_A : gca.m_B;
						return LineIntersection;
					} else if( BinCD ) {
						pointI=m_B;
						pointJ=(CinAB) ? gca.m_A : gca.m_B;
						return LineIntersection;
					} else {
						return NoIntersection;
					}
				}
			} else {
				// only point C is on GreatCircle(A,B)
				if( dotProduct(vM,vC) >= limit) {
					pointI=gca.m_A;
					return PointIntersection;
				} else {
					return NoIntersection;
				}
			}
		} else if ( std::fabs(pd) < ArcRadTolerance ) {
			// only point D is on GreatCircle(A,B)
			if( dotProduct(vM,vD) >= limit ) {
				pointI=gca.m_B;
				return PointIntersection;
			} else {
				return NoIntersection;
			}
		} else {
			// point C and D lie each side of GreatCircle(A,B)
			LatitudeLongitude inter=this->asGreatCircle().intersectionWith(gca.asGreatCircle());
			Vector3D vI=LLToCartesian(inter);
			if( dotProduct(vM,vI) >= limit ) {
				pointI=inter;
				return PointIntersection;
			} else {
				inter=inter.antipode();
				if( dotProduct(vM,vI) >= limit ) {
					pointI=inter;
					return PointIntersection;
				} else {
					return NoIntersection;
				}
			}
		}
	}
}
