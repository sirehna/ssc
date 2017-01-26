/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Vector3D cartesian coordinates
*/


#include "ssc/geometry/Vector3D.h"
#include <cmath>

using namespace Geometry;

Vector3D::Vector3D( double x,double y, double z) :  m_x(x), m_y(y), m_z(z)
{

}

double Vector3D::x() const
{
    return m_x;
}

double Vector3D::y() const
{
    return m_y;
}

double Vector3D::z() const
{
    return m_z;
}

Vector3D Vector3D::operator-() {
    return Vector3D( -m_x , -m_y , -m_z );
}

Vector3D&  Vector3D::operator+=(const Vector3D& right) {
    m_x += right.x();
    m_y += right.y();
    m_z += right.z();
    return *this;
}

Vector3D&  Vector3D::operator-=(const Vector3D& right) {
    m_x -= right.x();
    m_y -= right.y();
    m_z -= right.z();
    return *this;
}

Vector3D&  Vector3D::operator*=(double scal) {
    m_x *= scal;
    m_y *= scal;
    m_z *= scal;
    return *this;
}

Vector3D&  Vector3D::operator/=(double scal) {
    m_x /= scal;
    m_y /= scal;
    m_z /= scal;
    return *this;
}

void Vector3D::normalize() {
    *this /= norm();
}

double Vector3D::norm() const
{
    return std::sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}

//
// binary operations
//

Vector3D Geometry::operator+(Vector3D u,Vector3D v) {
    return Vector3D(
        u.x()+v.x(),
        u.y()+v.y(),
        u.z()+v.z());
}

Vector3D Geometry::operator-(Vector3D u,Vector3D v) {
    return Vector3D(
        u.x()-v.x(),
        u.y()-v.y(),
        u.z()-v.z());
}

Vector3D Geometry::operator*(double a,Vector3D u) {
    return Vector3D(
        a*u.x(),
        a*u.y(),
        a*u.z());
}

Vector3D Geometry::operator*(Vector3D u,double a) {
    return Vector3D(
        u.x()*a,
        u.y()*a,
        u.z()*a);
}

double Geometry::dotProduct(Vector3D u,Vector3D v) {
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}

Vector3D Geometry::crossProduct(Vector3D u,Vector3D v) {
    return Vector3D(
        u.y()*v.z() - u.z()*v.y(),
        u.z()*v.x() - u.x()*v.z(),
        u.x()*v.y() - u.y()*v.x());
}
