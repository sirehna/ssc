/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Spherical Geometry functions
*/

#include "ssc/geometry/Geometry.h"
#include <cmath>

using namespace Geometry;
using namespace ssc::geometry;

Vector3D Geometry::LLToCartesian(const LatitudeLongitude& point) {
    return Vector3D(
        cos(point.lat)*cos(point.lon),
        cos(point.lat)*sin(point.lon),
        sin(point.lat));
}

LatitudeLongitude Geometry::cartesianToLL(const Vector3D& v) {
    return LatitudeLongitude(
        angle_atan2(v.z(),std::hypot(v.x(),v.y())).valueInDegrees() ,
        angle_atan2(v.y(),v.x()).valueInDegrees() );
}

Vector3D Geometry::localTangentVector(const LatitudeLongitude& point, const Angle& bearing) {
    return bearing.cos()*localNorthVector(point)+bearing.sin()*localEastVector(point);
}

Vector3D Geometry::localNorthVector(const LatitudeLongitude& point) {
    return Vector3D(
        -sin(point.lat)*cos(point.lon),
        -sin(point.lat)*sin(point.lon),
        cos(point.lat));
}

Vector3D Geometry::localEastVector(const LatitudeLongitude& point) {
    return Vector3D(
        -sin(point.lon),
        cos(point.lon),
        0.0);
}

Angle Geometry::greatCircleArcDistance(const LatitudeLongitude& pointA, const LatitudeLongitude& pointB) {
    return angle_acos(dotProduct( LLToCartesian(pointA) , LLToCartesian(pointB) ));
}

Angle Geometry::angle(const LatitudeLongitude& pointA, const LatitudeLongitude& pointB, const LatitudeLongitude& pointC) {
    GreatCircle gcBA=GreatCircle(pointB,pointA);
    GreatCircle gcBC=GreatCircle(pointB,pointC);
    Vector3D tgBA=gcBA.tangentAtArcDistance( Angle(Radians(0.0)) );
    Vector3D tgBC=gcBC.tangentAtArcDistance( Angle(Radians(0.0)) );
    return angle_acos( dotProduct( tgBA , tgBC ) );
}

GreatCircle Geometry::bisector(const LatitudeLongitude& pointA, const LatitudeLongitude& pointB, const LatitudeLongitude& pointC) {
    GreatCircle gcBA=GreatCircle(pointB,pointA);
    GreatCircle gcBC=GreatCircle(pointB,pointC);
    Angle bearingBA=gcBA.bearingAtArcDistance( Angle(Radians(0.0)) );
    Angle bearingBC=gcBC.bearingAtArcDistance( Angle(Radians(0.0)) );
    Angle bearing=0.5*(bearingBA+bearingBC);
    return GreatCircle(pointB,bearing);
}
