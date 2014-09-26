/*
 * Angle.cpp
 *
 * \date 14 mars 2013, 10:49:16
 *  \author cec
 */

#include "Angle.hpp"
#include <cmath>

using namespace ssc::geometry;

#define PI (4.*atan(1.))

Angle::Angle() : usi_value(0)
{

}

Angle Angle::degree(const double& value_in_degrees)
{
    return Angle(value_in_degrees*PI/180.);
}

Angle Angle::radian(const double& value_in_radians)
{
    return Angle(value_in_radians);
}

Angle Angle::degree_minute_second(const int& value_in_degrees, const int& value_in_angle_minutes, const int& value_in_angle_seconds)
{
    return degree(double(value_in_degrees)+double(value_in_angle_minutes)/60+double(value_in_angle_seconds)/360);
}

double Angle::get_degree() const
{
    return get_usi()*180./PI;
}

double Angle::get_usi() const
{
    return get_radian();
}

double Angle::get_radian() const
{
    return usi_value;
}

Angle Angle::operator*(const double& factor) const
{
    return Angle(usi_value*factor);
}

Angle Angle::operator/(const double& factor) const
{
    return Angle(usi_value/factor);
}

Angle Angle::operator+(const Angle& angle) const
{
    return Angle(usi_value+angle.usi_value);
}

Angle Angle::operator-(const Angle& angle) const
{
    return Angle(usi_value-angle.usi_value);
}

bool Angle::operator==(const Angle& rhs) const
{
    return usi_value==rhs.usi_value;
}

bool Angle::operator!=(const Angle& rhs) const
{
    return not(*this==rhs);
}

double ssc::geometry::cos(const ssc::geometry::Angle& angle)
{
    return ::cos(angle.get_radian());
}

double ssc::geometry::sin(const Angle& angle)
{
    return ::sin(angle.get_radian());
}

double ssc::geometry::tan(const Angle& angle)
{
    return ::tan(angle.get_radian());
}

Angle ssc::geometry::operator*(const double& factor, const Angle& angle)
{
    return angle*factor;
}

Angle ssc::geometry::operator-(const Angle& angle)
{
    return Angle::radian(-angle.get_radian());
}
