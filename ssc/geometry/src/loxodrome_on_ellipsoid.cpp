/*
 * loxodrome_on_ellipsoid.cpp
 *
 *  Created on: May 12, 2014
 *      Author: cady
 */

#include "loxodrome_on_ellipsoid.hpp"
#include <cmath>

#define QUARTER_PI atan(1.)
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

double meridian_distance(const double f,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
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
    az12 = azimuth_of_loxodrome(sqrt(f*(2.-f)), lat_P1, lon_P1, lat_P2, lon_P2);
    const double m1 = meridian_distance(f, a, lat_P1);
    const double m2 = meridian_distance(f, a, lat_P2);
    s12 = (m2-m1)/cos(az12);
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

double next_newton_raphson_value(const double m, const double a, const double A[13], const double previous_phi);
double next_newton_raphson_value(const double m, const double a, const double A[13], const double previous_phi)
{
    return previous_phi - (series_expansion(a, A, previous_phi) - m)/derivative_series_expansion(a, A, previous_phi);
}

double newton_raphson(const double m, const double a, const double A[13], const double initial_phi, const double eps, const int maxiter);
double newton_raphson(const double m, const double a, const double A[13], const double initial_phi, const double eps, const int maxiter)
{
    double phi = initial_phi;
    double next_phi = initial_phi;
    for (int i = 0 ; i < maxiter ; ++i)
    {
        next_phi = next_newton_raphson_value(m, a, A, phi);
        if (fabs(phi-next_phi)<eps) return next_phi;
        phi = next_phi;
    }
    return next_phi;
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
    const double f = 1./f_inv;
    const double m1 = meridian_distance(f, a, lat_P1);
    const double m2 = s12*cos(az12) + m1;
    double e[11];
    double A[13];
    powers_of_e(f, e);
    taylor_series_coefficients(e,A);
    const double eps = 1E-12;
    const int max_nb_of_newton_raphson_iterations = 5;
    lat_P2 = newton_raphson(m2, a, A, lat_P1, eps, max_nb_of_newton_raphson_iterations);
    const double e1 = sqrt(e[2]);
    const double q1 = isometric_latitude(e1, lat_P1);
    const double q2 = isometric_latitude(e1, lat_P2);
    lon_P2 = lon_P1 + (q2-q1) * tan(az12);
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
