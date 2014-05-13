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

double meridian_distance(const double f,  //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                         const double a,  //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                         const double phi //!< Latitude of the point (in radians)
                         )
{
    const double e2 = f*(2-f);
    const double e4  = e2*e2;
    const double e6  = e4*e2;
    const double e8  = e4*e4;
    const double e10 = e6*e4;

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
    const double A0  = 0.1e1 + (-0.1e1 / 0.4e1 + (-0.3e1 / 0.64e2 + (-0.5e1 / 0.256e3 + (-0.175e3 / 0.16384e5 + (-0.441e3 / 0.65536e5 - 0.43659e5 / 0.65536e5 * e2) * e2) * e2) * e2) * e2) * e2;
    const double A2  = (-0.3e1 / 0.8e1 + (-0.3e1 / 0.32e2 + (-0.45e2 / 0.1024e4 + (-0.105e3 / 0.4096e4 + (-0.2205e4 / 0.131072e6 - 0.6237e4 / 0.524288e6 * e2) * e2) * e2) * e2) * e2) * e2;
    const double A4  = (0.15e2 / 0.256e3 + (0.45e2 / 0.1024e4 + (0.525e3 / 0.16384e5 + (0.1575e4 / 0.65536e5 + 0.155925e6 / 0.8388608e7 * e2) * e2) * e2) * e2) * e4;
    const double A6  = (-0.35e2 / 0.3072e4 + (-0.175e3 / 0.12288e5 + (-0.3675e4 / 0.262144e6 - 0.13475e5 / 0.1048576e7 * e2) * e2) * e2) * e6;
    const double A8  = (0.315e3 / 0.131072e6 + (0.2205e4 / 0.524288e6 + 0.43659e5 / 0.8388608e7 * e2) * e2) * e8;
    const double A10 = (-0.693e3 / 0.1310720e7 - 0.6237e4 / 0.5242880e7 * e2) * e10;
    const double A12 = 0.1001e4 / 0.8388608e7 * e10*e2;

    return a*(A0*phi + A2*sin(2*phi) + A4*sin(4*phi) + A6*sin(6*phi) + A8*sin(8*phi) + A10*sin(10*phi) + A12*sin(12*phi));
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
