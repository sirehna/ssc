/*
 * Angle.hpp
 *
 * \date 14 mars 2013, 10:49:16
 *  \author cec
 */

#ifndef ANGLE_HPP_
#define ANGLE_HPP_

/** \author cec
 *  \brief Represents angles with various units
 *  \details It has the following responsibilities:
 *  - Store the value of the angle
 *  - Convert values to any angle unit
 *  \section ex1 Example
 *  \snippet geometry/unit_tests/src/AngleTest.cpp AngleTest example
 *  \section ex2 Expected output
 *  \snippet geometry/unit_tests/src/AngleTest.cpp AngleTest expected output
 */

class Angle
{
    public:
        static Angle degree(const double& value_in_degrees);
        static Angle radian(const double& value_in_radians);
        static Angle degree_minute_second(const int& value_in_degrees, const int& value_in_angle_minutes, const int& value_in_angle_seconds);

        double get_degree() const;
        double get_radian() const;
        double get_usi() const;

        Angle operator*(const double& factor) const;
        Angle operator/(const double& factor) const;
        Angle operator+(const Angle& angle) const;
        Angle operator-(const Angle& angle) const;
        bool operator==(const Angle& angle) const;
        bool operator!=(const Angle& angle) const;

    private:
        Angle();
        Angle(const double& value_in_radians);
        double usi_value;
};

double cos(const Angle& angle);
double sin(const Angle& angle);
double tan(const Angle& angle);

Angle operator*(const double& factor, const Angle& angle);
Angle operator-(const Angle& angle);

#endif /* ANGLE_HPP_ */
