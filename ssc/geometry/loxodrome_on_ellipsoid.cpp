/*
 * loxodrome_on_ellipsoid.cpp
 *
 * \date May 12, 2014
 * \author cec
 */

#include "ssc/geometry/loxodrome_on_ellipsoid.hpp"
#include <boost/math/tools/roots.hpp>
#include <cmath>

using namespace ssc::geometry;

#define QUARTER_PI atan(1.)
#define HALF_PI (2.*atan(1.))
#define PI (4.*QUARTER_PI)

#define BISECTION double mid = 0;\
				  for (size_t i = 0 ; i < 30 ; ++i)\
				  {\
					   mid = (min+max)/2;\
					   double ymin = std::get<0>(L(min));\
					   double ymid = std::get<0>(L(mid));\
					   if (ymin*ymid > 0)\
					   {\
						   min = mid;\
					   }\
					   else\
					   {\
						   max = mid;\
					   }\
				  }\
				  return mid;

double ssc::geometry::azimuth_of_loxodrome(const double e,      //!< Excentricity of the ellipsoid (in meters)
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

double ssc::geometry::isometric_latitude(const double e,  //!< Excentricity of the ellipsoid (in meters)
                          const double phi //!< Latitude of the point under consideration (in radians)
                         )
{
    return log(tan(QUARTER_PI + phi/2.)*pow((1-e*sin(phi))/(1+e*sin(phi)),e/2.));
}

double ssc::geometry::isometric_latitude(const double phi //!< Latitude of the point under consideration (in radians)
                         )
{
    return isometric_latitude(0.0818191908426214943348024517538,phi);
}

void powers_of_e(const double f, double e[10]);
void powers_of_e(const double f, double e[10])
{
    e[2]  = f*(2-f);
    e[4]  = e[2]*e[2];
    e[6]  = e[4]*e[2];
    e[8]  = e[4]*e[4];
    e[10] = e[6]*e[4];
}

void taylor_series_coefficients(const double e[11],
                                double coeffs[13]);
void taylor_series_coefficients(const double e[11],
                                double coeffs[13])
{
    // Generated with MAPLE using the following code:
        /*
        sinlist := n -> [phi,seq(sin(2*k*phi),k=1..n)];
        f:=N->(x->eval(convert(taylor((1-e^2*t^2)^(-3/2),t=0,N),polynom),t=x));
        F:=N->collect(combine(expand((1-e^2)*integrate(f(N)(sin(t)),t=0..phi))),sinlist(N));
        get_coeff:=(N,idx)->convert(taylor(sort(map(x->coeff(F(N+2),x),sinlist(N+2)[2..])[idx],e,ascending),e=0,N+1),polynom);
        get_const_coeff:=N->sort(eval(F(N),phi=Pi)/Pi,e,ascending);

        CodeGeneration:-C(codegen:-horner(get_const_coeff(12),e), resultname=A0);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,1),e), resultname=A2);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,2),e), resultname=A4);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,3),e), resultname=A6);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,4),e), resultname=A8);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,5),e), resultname=A10);
        CodeGeneration:-C(codegen:-horner(get_coeff(12,6),e), resultname=A12);
        */

    coeffs[0]  = 0.1e1 + (-0.1e1 / 0.4e1 + (-0.3e1 / 0.64e2 + (-0.5e1 / 0.256e3 + (-0.175e3 / 0.16384e5 + (-0.441e3 / 0.65536e5 - 0.43659e5 / 0.65536e5 * e[2]) * e[2]) * e[2]) * e[2]) * e[2]) * e[2];
    coeffs[2]  = (-0.3e1 / 0.8e1 + (-0.3e1 / 0.32e2 + (-0.45e2 / 0.1024e4 + (-0.105e3 / 0.4096e4 + (-0.2205e4 / 0.131072e6 - 0.6237e4 / 0.524288e6 * e[2]) * e[2]) * e[2]) * e[2]) * e[2]) * e[2];
    coeffs[4]  = (0.15e2 / 0.256e3 + (0.45e2 / 0.1024e4 + (0.525e3 / 0.16384e5 + (0.1575e4 / 0.65536e5 + 0.155925e6 / 0.8388608e7 * e[2]) * e[2]) * e[2]) * e[2]) * e[4];
    coeffs[6]  = (-0.35e2 / 0.3072e4 + (-0.175e3 / 0.12288e5 + (-0.3675e4 / 0.262144e6 - 0.13475e5 / 0.1048576e7 * e[2]) * e[2]) * e[2]) * e[6];
    coeffs[8]  = (0.315e3 / 0.131072e6 + (0.2205e4 / 0.524288e6 + 0.43659e5 / 0.8388608e7 * e[2]) * e[2]) * e[8];
    coeffs[10] = (-0.693e3 / 0.1310720e7 - 0.6237e4 / 0.5242880e7 * e[2]) * e[10];
    coeffs[12] = 0.1001e4 / 0.8388608e7 * e[10]*e[2];
}

double series_expansion(const double a, const double A[13], const double phi);
double series_expansion(const double a, const double A[13], const double phi)
{
    return a*(A[0]*phi + A[2]*sin(2*phi) + A[4]*sin(4*phi) + A[6]*sin(6*phi) + A[8]*sin(8*phi) + A[10]*sin(10*phi) + A[12]*sin(12*phi));
}

double derivative_series_expansion(const double a, const double A[13], const double phi);
double derivative_series_expansion(const double a, const double A[13], const double phi)
{
    return a*(A[0] + 2*A[2]*cos(2*phi) + 4*A[4]*cos(4*phi) + 6*A[6]*cos(6*phi) + 8*A[8]*cos(8*phi) + 10*A[10]*cos(10*phi) + 12*A[12]*cos(12*phi));
}

double second_derivative_series_expansion(const double a, const double A[13], const double phi);
double second_derivative_series_expansion(const double a, const double A[13], const double phi)
{
    return -a*(4*A[2]*sin(2*phi) + 16*A[4]*sin(4*phi) + 36*A[6]*sin(6*phi) + 64*A[8]*sin(8*phi) + 100*A[10]*sin(10*phi) + 144*A[12]*sin(12*phi));
}

double ssc::geometry::meridian_distance(const double f,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                         const double a,  //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                         const double phi //!< Latitude of the point (in radians)
                         )
{
    double e[11];
    double A[13];
    powers_of_e(f, e);
    taylor_series_coefficients(e,A);
    return series_expansion(a, A, phi);
}

void ssc::geometry::loxodrome_inverse(const double f_inv,  //!< Inverse flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
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


void ssc::geometry::loxodrome_inverse(const double lat_P1, //!< Latitude of P1 (in radians)
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
   latitude_functor(const double& m_, const double& a_, const double*&  A_) : m(m_), a(a_), A(A_) {}
   latitude_functor(const latitude_functor& rhs) : m(rhs.m), a(rhs.a), A(rhs.A) {}
   latitude_functor& operator=(const latitude_functor& rhs)
   {
       if (this != &rhs)
       {
           m = rhs.m;
           a = rhs.a;
       }
       return *this;
   }
   ~latitude_functor(){}

   std::tuple<double, double, double> operator()(const double phi) // Whatever you do, don't #include <tr1/tuple> as it won't compile...
   {
      double val = series_expansion(a, A, phi) - m;
      double der = derivative_series_expansion(a, A, phi);
      double second_der = second_derivative_series_expansion(a, A, phi);
      return std::make_tuple(val, der, second_der);
   }

   private:
       double m;
       double a;
       const double* A;
};

double halley(const double m, const double a, const double A[13], const double initial_phi, const int digits);
double halley(const double m, const double a, const double A[13], const double initial_phi, const int digits)
{
   double min = -PI/2;
   double max = -min;

#if defined(__clang__)
   (void) initial_phi;
   (void) digits;
   latitude_functor L(m,a,A);
   BISECTION;
#else
   double guess = initial_phi;
   return boost::math::tools::halley_iterate(latitude_functor(m,a,A), guess, min, max, digits);
#endif
}

struct cbrt_functor
{
    cbrt_functor(const double e_, const double ) : e(e_) {}

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
        double e;
};

double cbrt(const double e, const double q);
double cbrt(const double e, const double q)
{
   double max = HALF_PI;
   double min = -max;
#if defined(__clang__)
   cbrt_functor L(e,q);
   BISECTION;
#else
   double guess = q/(1-e*e);
   int digits = std::numeric_limits<double>::digits;
   return boost::math::tools::halley_iterate(cbrt_functor(e,q), guess, min, max, digits);
#endif
}

struct isometric_latitude_functor
{
   isometric_latitude_functor(const double& e_, const double& q0) : e(e_), q(q0) {}

   std::tuple<double, double> operator()(const double phi) // Whatever you do, don't #include <tr1/tuple> as it won't compile...
   {
      const double val = isometric_latitude(e,phi) - q;
      const double der = ((0.500000000000000000000000000000e0 + 0.500000000000000000000000000000e0 * pow(tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi), 0.2e1)) * pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e) + 0.500000000000000000000000000000e0 * tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi) * pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e) * e * (-e * cos(phi) / (0.1e1 + e * sin(phi)) - (0.1e1 - e * sin(phi)) * pow(0.1e1 + e * sin(phi), -0.2e1) * e * cos(phi)) / (0.1e1 - e * sin(phi)) * (0.1e1 + e * sin(phi))) / tan(QUARTER_PI + 0.500000000000000000000000000000e0 * phi) / pow((0.1e1 - e * sin(phi)) / (0.1e1 + e * sin(phi)), 0.500000000000000000000000000000e0 * e);

      /*const double x_ = 1. - e * sin(phi);
      const double x = 1. + e * sin(phi);
      const double t = tan(QUARTER_PI + 0.5 * phi);
      const double p = pow(x_/x, 0.5 * e);
      const double x2 = x*x;
      const double t2 = t*t;
      const double der = ((0.5 + 0.5 * t2) * p + 0.5 * t * p * e * (-e * cos(phi) / x - x_/x2 * e * cos(phi)) / x_ * x) / t / p;*/
      return std::make_tuple(val, der);
   }

   private:
       double e;
       double q;
};

double ssc::geometry::convert_isometric_latitude_to_latitude(const double e,  //!< Excentricity of the ellipsoid (in metres)
                                              const double q   //!< Isometric latitude to convert (in radians)
                                              )
{
    double min = -PI/2;
    double max = -min;
#if defined(__clang__)
    isometric_latitude_functor L(e,q);
    BISECTION;
#else
    double guess = fabs(q)<2 ? q : cbrt(e,fabs(q));
    if (q<0) guess = - fabs(guess);
    const int digits = 12;
    return boost::math::tools::newton_raphson_iterate(isometric_latitude_functor(e,q), guess, min, max, digits);
#endif
}

double ssc::geometry::convert_isometric_latitude_to_latitude(const double q   //!< Isometric latitude to convert (in radians)
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

void ssc::geometry::loxodrome_direct(const double f_inv,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
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
    double e[11];
    double A[13];
    powers_of_e(f, e);
    taylor_series_coefficients(e,A);
    lat_P2 = halley(m2, a, A, lat_P1, std::numeric_limits<double>::digits / 2);
    lat_P2 = wrap_minus_minus_alpha_and_alpha(lat_P2,PI/2);
    const double e1 = sqrt(e[2]);
    const double q1 = isometric_latitude(e1, lat_P1);
    const double q2 = isometric_latitude(e1, lat_P2);
    lon_P2 = lon_P1 + (q2-q1) * tan(az12);
    lon_P2 = wrap_minus_minus_alpha_and_alpha(lon_P2,PI);
}

void ssc::geometry::loxodrome_direct(const double lat_P1, //!< Latitude of P1 (in radians)
                      const double lon_P1, //!< Longitude of P1 (in radians)
                      double& lat_P2,      //!< Calculated latitude of P2 (in radians)
                      double& lon_P2,      //!< Calculated longitude of P2 (in radians)
                      const double s12,    //!< Arc length between P1 and P2 (in metres)
                      const double az12    //!< Loxodrome azimuth (in radians)
        )
{
    loxodrome_direct(298.257223563, 6378137, lat_P1, lon_P1, lat_P2, lon_P2, s12, az12);
}

