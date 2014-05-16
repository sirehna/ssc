/*
 * loxodrome_on_ellipsoid.cpp
 *
 *  Created on: May 12, 2014
 *      Author: cady
 */

#include <cmath>
#include <boost/math/tools/roots.hpp>
#include <boost/math/special_functions/ellint_3.hpp>

#include "loxodrome_on_ellipsoid.hpp"

#define QUARTER_PI atan(1.)
#define HALF_PI (2.*atan(1.))
#define PI (4.*QUARTER_PI)

double azimuth_of_loxodrome(const double e,      //!< Excentricity of the ellipsoid (in meters)
                            const double lat_P1, //!< Latitude of P1 (in radians)
                            const double lon_P1, //!< Longitude of P1 (in radians)
                            const double lat_P2, //!< Latitude of P2 (in radians)
                            const double lon_P2  //!< Longitude of P2 (in radians)
                       )
{
    const double q1 = isometric_latitude(e, lat_P1);
    const double q2 = isometric_latitude(e, lat_P2);
    return atan2(lon_P2-lon_P1, q2-q1);
}

double isometric_latitude(const double e,  //!< Excentricity of the ellipsoid (in meters)
                          const double phi //!< Latitude of the point under consideration (in radians)
                         )
{
    return log(tan(QUARTER_PI + phi/2.)*pow((1-e*sin(phi))/(1+e*sin(phi)),e/2.));
}

double isometric_latitude(const double phi //!< Latitude of the point under consideration (in radians)
                         )
{
    return isometric_latitude(0.0818191908426214943348024517538,phi);
}

double meridian_distance(const double f,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                         const double a,  //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                         const double phi //!< Latitude of the point (in radians)
                         )
{
    const double e2 = f*(2-f);
    const double e = sqrt(e2);
    return a*(1-e2)*boost::math::ellint_3(e,e2,phi);
}

void loxodrome_inverse(const double f_inv,  //!< Inverse flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                       const double a,      //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                       const double lat_P1, //!< Latitude of P1 (in radians)
                       const double lon_P1, //!< Longitude of P1 (in radians)
                       const double lat_P2, //!< Latitude of P2 (in radians)
                       const double lon_P2, //!< Longitude of P2 (in radians)
                       double& s12,         //!< Calculated arc length between P1 and P2 (in metres)
                       double& az12         //!< Calculated loxodrome azimuth (in radians)
            )
{
    const double f = 1./f_inv;
    const double e = sqrt(f*(2.-f));
    az12 = azimuth_of_loxodrome(e, lat_P1, lon_P1, lat_P2, lon_P2);
    // If the points are at the same latitude, the loxodrome never crosses the equator
    // hence the meridian distance is 0 & so is cos(az12): therefore we must use
    // another formula.
    if (fabs(lat_P2-lat_P1)<1E-10)
    {
        const double sin_phi0 = sin(lat_P1);
        const double nu = a/(1-e*e*sin_phi0*sin_phi0);
        s12 = nu*fabs((lon_P2-lon_P1)*cos(lat_P1));
        return;
    }

    const double m1 = meridian_distance(f, a, lat_P1);
    const double m2 = meridian_distance(f, a, lat_P2);
    s12 = fabs((m2-m1)/cos(az12));
}


void loxodrome_inverse(const double lat_P1, //!< Latitude of P1 (in radians)
                       const double lon_P1, //!< Longitude of P1 (in radians)
                       const double lat_P2, //!< Latitude of P2 (in radians)
                       const double lon_P2, //!< Longitude of P2 (in radians)
                       double& s12,         //!< Calculated arc length between P1 and P2 (in metres)
                       double& az12         //!< Calculated loxodrome azimuth (in radians)
            )
{
    loxodrome_inverse(298.257223563, 6378137, lat_P1, lon_P1, lat_P2, lon_P2, s12, az12);
}

struct latitude_functor
{
   latitude_functor(const double& m_, const double& e_, const double& a_) : m(m_), e(e_), e2(e*e), a(a_) {}

   std::tuple<double, double, double> operator()(const double phi) // Whatever you do, don't #include <tr1/tuple> as it won't compile...
   {

      double val = a*(1-e2)*boost::math::ellint_3(e,e2,phi) - m;
      double der = a*(1-e*e)/pow(1-e*e*sin(phi)*sin(phi),1.5);

      const double t1 = e * e;
      const double t4 = sin(phi);
      const double t5 = t4 * t4;
      const double t7 = 1 - t1 * t5;
      const double t8 = t7 * t7;
      const double second_der = 3 * a * (1 - t1) / sqrt(t7) / t8 * t1 * t4 * cos(phi);
      return std::make_tuple(val, der, second_der);
   }

   private:
       double m;
       double e;
       double e2;
       double a;
};

double halley(const double m, const double a, const double e, const double initial_phi, const int digits);
double halley(const double m, const double a, const double e, const double initial_phi, const int digits)
{
   double min = -PI/2;
   double max = -min;
   double guess = initial_phi;
   return boost::math::tools::halley_iterate(latitude_functor(m,e,a), guess, min, max, digits);
}

struct cbrt_functor
{
    cbrt_functor(const double e_, const double target) : q0(target), e(e_) {}

    std::tuple<double, double, double> operator()(double const& phi)
    {
            double t10;
          double t11;
          double t12;
          double t13;
          double t15;
          double t17;
          double t18;
          double t2;
          double t20;
          double t21;
          double t23;
          double t24;
          double t25;
          double t27;
          double t3;
          double t31;
          double t33;
          double t36;
          double t38;
          double t39;
          double t4;
          double t43;
          double t45;
          double t46;
          double t48;
          double t49;
          double t5;
          double t52;
          double t55;
          double t57;
          double t59;
          double t6;
          double t63;
          double t64;
          double t66;
          double t7;
          double t71;
          double t72;
          double t75;
          double t79;
          double t8;
          double t90;
          double t100;
          double t114;
          double t126;
          double t130;
          double t151;
          double t152;
          double t155;
          t2 = tan(0.31e2 / 0.64e2 * 0.3141592654e1);
          t3 = 0.15e2 / 0.32e2 * 0.3141592654e1;
          t4 = sin(t3);
          t5 = e * t4;
          t6 = -0.1e1 + t5;
          t7 = 0.1e1 + t5;
          t8 = 0.1e1 / t7;
          t10 = sqrt(-t6 * t8);
          t11 = pow(t10, e);
          t12 = t2 * t11;
          t13 = e * e;
          t15 = cos(t3);
          t17 = 0.1e1 / t6;
          t18 = t15 * t8 * t17;
          t20 = t2 * t2;
          t21 = 0.1e1 + t20;
          t23 = t21 * t11 / 0.2e1;
          t24 = t12 * t13 * t18 + t23;
          t25 = 0.1e1 / t2;
          t27 = 0.1e1 / t11;
          t31 = t4 * t4;
          t33 = t15 * t15;
          t36 = t4 + e * t31 + 0.2e1 * e * t33;
          t38 = t7 * t7;
          t39 = 0.1e1 / t38;
          t43 = t13 * e;
          t45 = t6 * t6;
          t46 = 0.1e1 / t45;
          t48 = e / 0.2e1;
          t49 = t48 - 0.1e1;
          t52 = -t13 * t36 * t39 * t17 / 0.2e1 + t43 * t33 * t39 * t46 * t49;
          t55 = t2 * t21 * t11;
          t57 = t23 * t13 * t18 + t12 * t52 + t55 / 0.4e1;
          t59 = t57 * t25 * t27;
          t63 = t13 * t31;
          t64 = t20 * t13;
          t66 = 0.2e1 * t2 * t13 * t15 - 0.1e1 + t63 - t20 + t64 * t31;
          t71 = t17 / t20 * t27;
          t72 = t66 * t24 * t8 * t71;
          t75 = phi - t3;
          t79 = t13 * t15;
          t90 = 0.1e1 / t38 / t7;
          t100 = t13 * t13;
          t114 = t20 * t20;
          t126 = t20 * t100;
          t130 = t31 * t31;
          t151 = (t23 * t52 + t55 * t79 * t8 * t17 / 0.4e1 + t12 * (t79 * (-0.1e1 + 0.4e1 * t5 + 0.5e1 * t63 + 0.6e1 * t13 * t33) * t90 * t17 / 0.6e1 - t43 * t15 * t90 * t46 * t49 * t36 + 0.2e1 / 0.3e1 * t100 * t33 * t15 * t90 / t45 / t6 * t49 * (t48 - 0.2e1)) + (t20 / 0.6e1 + t114 / 0.8e1 + 0.1e1 / 0.24e2) * t11) * t25 * t27 - t66 * t57 * t8 * t71 / 0.6e1 - (-0.1e1 + 0.2e1 * t63 + t114 - 0.8e1 * t126 * t33 * t4 - t100 * t130 + 0.4e1 * t64 * t4 - 0.4e1 * t126 * t31 * t4 - 0.2e1 * t114 * t13 * t31 + t114 * t100 * t130) * t24 * t39 * t46 / t20 / t2 * t27 / 0.12e2;
          t152 = t75 * t75;
          t155 = t24 * t25 * t27 + 0.2e1 * (t59 - t72 / 0.4e1) * t75 + 0.3e1 * t151 * t152;
          const double val = t155;
          const double der = t155;
          const double dder = 0.2e1 * t59 - t72 / 0.2e1 + 0.6e1 * t151 * t75;


        return std::make_tuple(val,der,dder);
    }

    private:
        double q0;
        double e;
};

double cbrt(const double e, const double q);
double cbrt(const double e, const double q)
{
   double max = HALF_PI;
   double min = -max;
   double guess = q/(1-e*e);
   int digits = std::numeric_limits<double>::digits;
   return boost::math::tools::halley_iterate(cbrt_functor(e,q), guess, min, max, digits);
}

struct isometric_latitude_functor
{
   isometric_latitude_functor(const double& e_, const double& q0) : e(e_), q(q0) {}

   std::tuple<double, double> operator()(const double phi) // Whatever you do, don't #include <tr1/tuple> as it won't compile...
   {
      const double val = isometric_latitude(e,phi) - q;
      const double der = ((0.500000000000000000000000000000e0 + 0.500000000000000000000000000000e0 * pow(tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi), 0.2e1)) * pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e) + 0.500000000000000000000000000000e0 * tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi) * pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e) * e * (-e * cos(phi) / (0.1e1 + e * sin(phi)) - (0.1e1 - e * sin(phi)) * pow(0.1e1 + e * sin(phi), -0.2e1) * e * cos(phi)) / (0.1e1 - e * sin(phi)) * (0.1e1 + e * sin(phi))) / tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi) / pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e);
      return std::make_tuple(val, der);
   }

   private:
       double e;
       double q;
};

double convert_isometric_latitude_to_latitude(const double e,  //!< Excentricity of the ellipsoid (in metres)
                                              const double q   //!< Isometric latitude to convert (in radians)
                                              )
{
    double min = -PI/2;
    double max = -min;
    double guess = fabs(q)<2 ? q : cbrt(e,fabs(q));
    if (q<0) guess = - fabs(guess);
    const int digits = 12;
    return boost::math::tools::newton_raphson_iterate(isometric_latitude_functor(e,q), guess, min, max, digits);
}

double convert_isometric_latitude_to_latitude(const double q   //!< Isometric latitude to convert (in radians)
                                              )
{
    return convert_isometric_latitude_to_latitude(0.0818191908426214943348024517538,q);
}

double wrap_minus_minus_alpha_and_alpha(double angle, const double alpha);
double wrap_minus_minus_alpha_and_alpha(double angle, const double alpha)
{
    double two_alpha = 2.0 * alpha;
    angle = angle - two_alpha * floor( angle / two_alpha );
    if (angle>alpha) angle = angle - two_alpha;
    return angle;
}

void loxodrome_direct(const double f_inv,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                      const double a,      //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                      const double lat_P1, //!< Latitude of P1 (in radians)
                      const double lon_P1, //!< Longitude of P1 (in radians)
                      double& lat_P2,      //!< Calculated latitude of P2 (in radians)
                      double& lon_P2,      //!< Calculated longitude of P2 (in radians)
                      const double s12,    //!< Arc length between P1 and P2 (in metres)
                      const double az12    //!< Loxodrome azimuth (in radians)
        )
{
    // If the points are at the same latitude, the loxodrome never crosses the equator
    // hence the meridian distance is 0 & so is cos(az12): therefore we must use
    // another formula.
    const double f = 1./f_inv;
    if ((fabs(az12-PI/2)<1E-10) or (fabs(az12+PI/2)<1E-10) or (fabs(az12-1.5*PI)<1E-10) or (fabs(az12+1.5*PI)<1E-10))
    {
        const double e = sqrt(f*(2.-f));
        const double sin_phi0 = sin(lat_P1);
        const double nu = a/(1-e*e*sin_phi0*sin_phi0);
        double sign = 1;
        if ((fabs(az12+PI/2)<1E-10) or (fabs(az12+1.5*PI)<1E-10)) sign = -1;
        lat_P2 = lat_P1;
        lon_P2 = lon_P1 + sign*s12/nu*fabs(cos(lat_P1));
        lon_P2 = wrap_minus_minus_alpha_and_alpha(lon_P2,PI);
        return;
    }
    const double m1 = meridian_distance(f, a, lat_P1);
    const double m2 = s12*cos(az12) + m1;
    const double e = sqrt(f*(2.-f));
    lat_P2 = halley(m2, a, e, lat_P1, std::numeric_limits<double>::digits / 2);
    lat_P2 = wrap_minus_minus_alpha_and_alpha(lat_P2,PI/2);
    const double q1 = isometric_latitude(e, lat_P1);
    const double q2 = isometric_latitude(e, lat_P2);
    lon_P2 = lon_P1 + (q2-q1) * tan(az12);
    lon_P2 = wrap_minus_minus_alpha_and_alpha(lon_P2,PI);
}

void loxodrome_direct(const double lat_P1, //!< Latitude of P1 (in radians)
                      const double lon_P1, //!< Longitude of P1 (in radians)
                      double& lat_P2,      //!< Calculated latitude of P2 (in radians)
                      double& lon_P2,      //!< Calculated longitude of P2 (in radians)
                      const double s12,    //!< Arc length between P1 and P2 (in metres)
                      const double az12    //!< Loxodrome azimuth (in radians)
        )
{
    loxodrome_direct(298.257223563, 6378137, lat_P1, lon_P1, lat_P2, lon_P2, s12, az12);
}

