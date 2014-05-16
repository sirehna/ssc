/*
 * loxodrome_on_ellipsoid.hpp
 *
 *  Created on: May 12, 2014
 *      Author: cady
 */

#ifndef LOXODROME_ON_ELLIPSOID_HPP_
#define LOXODROME_ON_ELLIPSOID_HPP_

/**  \author cec
  *  \date May 13, 2014, 9:23:50 AM
  *  \brief Computes the azimuth of a loxodrome between two points P1 & P2
  *         on an ellipsoid.
  *  \returns Azimuth of the loxodrome (in radians).
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest azimuth_of_loxodrome_example
  */
double azimuth_of_loxodrome(const double e,      //!< Excentricity of the ellipsoid (in meters)
                            const double lat_P1, //!< Latitude of P1 (in radians)
                            const double lon_P1, //!< Longitude of P1 (in radians)
                            const double lat_P2, //!< Latitude of P2 (in radians)
                            const double lon_P2  //!< Longitude of P2 (in radians)
                       );

/**  \author cec
  *  \date May 13, 2014, 9:13:15 AM
  *  \brief Computes the isometric latitude on an ellipsoid of excentricity e.
  *  \details Equal increments of the isometric latitude give rise to equal
  *           distance displacements along the meridians on an ellipsoid.
  *  \returns Isometric latitude (in radians)
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest isometric_latitude_example
  */
double isometric_latitude(const double e,  //!< Excentricity of the ellipsoid (in meters)
                          const double phi //!< Latitude of the point under consideration (in radians)
                         );

/**  \author cec
  *  \date May 13, 2014, 8:55:58 AM
  *  \brief Computes the meridian distance to a point on an ellipsoid.
  *  \details Length of the arc of the meridian on an ellipsoid to a point in
  *           latitude phi.
  *           See 'The Loxodrome On An Ellipsoid', R. E. Deakin for details.
  *  \returns Meridian distance.
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest meridian_distance_example
  */
double meridian_distance(const double f,    //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                         const double a,    //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                         const double phi   //!< Latitude of the point (in radians)
                         );

/**  \author cec
  *  \date May 12, 2014, 5:20:00 PM
  *  \brief Solves the inverse loxodrome problem.
  *  \details Computes the arc length s12 along the loxodrome curve between P1
  *           and P2 and the azimuth az12 of that loxodrome (on the WGS84).
  *           No separate function to calculate only the arc length is provided
  *           because the loxodrome azimuth is needed to calculate the arc length.
    *         See 'The Loxodrome On An Ellipsoid', R. E. Deakin for details.
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest inverse_example
  */
void loxodrome_inverse(const double f,      //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                       const double a,      //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                       const double lat_P1, //!< Latitude of P1 (in radians)
                       const double lon_P1, //!< Longitude of P1 (in radians)
                       const double lat_P2, //!< Latitude of P2 (in radians)
                       const double lon_P2, //!< Longitude of P2 (in radians)
                       double& s12,         //!< Calculated arc length between P1 and P2 (in metres)
                       double& az12         //!< Calculated loxodrome azimuth (in radians)
                       );

/**  \author cec
  *  \date May 12, 2014, 5:20:00 PM
  *  \brief Solves the inverse loxodrome problem on the WGS84.
  *  \details Computes the arc length s12 along the loxodrome curve between P1
  *           and P2 and the azimuth az12 of that loxodrome (on the WGS84).
    *         See 'The Loxodrome On An Ellipsoid', R. E. Deakin for details.
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest inverse_example
  */
void loxodrome_inverse(const double lat_P1, //!< Latitude of P1 (in radians)
                       const double lon_P1, //!< Longitude of P1 (in radians)
                       const double lat_P2, //!< Latitude of P2 (in radians)
                       const double lon_P2, //!< Longitude of P2 (in radians)
                       double& s12,         //!< Calculated arc length between P1 and P2 (in metres)
                       double& az12         //!< Calculated loxodrome azimuth (in radians)
                       );

/**  \author cec
  *  \date May 13, 2014, 10:54:09 AM
  *  \brief Computes coordinates of a point at a given distance of another.
  *  \details Given latitude and longitude of a point P1, the azimuth az12 of a
  *           loxodrome P1P2 and an arc length s12 along that loxodrome curve,
  *           computes the latitude and longitude of P2 at distance s12 of P1
  *           along the loxodrome.
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest loxodrome_direct_example
  */
void loxodrome_direct(const double f,      //!< Flattening of the ellipsoid (298.257223563 for the WGS84 ellipsoid)
                      const double a,      //!< Length of the ellipsoid's semi-major axis (in metres) (6378137 m for the WGS84 ellipsoid)
                      const double lat_P1, //!< Latitude of P1 (in radians)
                      const double lon_P1, //!< Longitude of P1 (in radians)
                      double& lat_P2,      //!< Calculated latitude of P2 (in radians)
                      double& lon_P2,      //!< Calculated longitude of P2 (in radians)
                      const double s12,    //!< Arc length between P1 and P2 (in metres)
                      const double az12    //!< Loxodrome azimuth (in radians)
        );

/**  \author cec
  *  \date May 13, 2014, 10:54:09 AM
  *  \brief Solves the direct loxodrome problem on the WGS84.
  *  \details Given latitude and longitude of a point P1, the azimuth az12 of a
  *           loxodrome P1P2 and an arc length s12 along that loxodrome curve,
  *           computes the latitude and longitude of P2 at distance s12 of P1
  *           along the loxodrome.
  *  \snippet geometry/unit_tests/src/loxodrome_on_ellipsoidTest.cpp loxodrome_on_ellipsoidTest loxodrome_direct_example
  */
void loxodrome_direct(const double lat_P1, //!< Latitude of P1 (in radians)
                      const double lon_P1, //!< Longitude of P1 (in radians)
                      double& lat_P2,      //!< Calculated latitude of P2 (in radians)
                      double& lon_P2,      //!< Calculated longitude of P2 (in radians)
                      const double s12,    //!< Arc length between P1 and P2 (in metres)
                      const double az12    //!< Loxodrome azimuth (in radians)
        );
#endif /* LOXODROME_ON_ELLIPSOID_HPP_ */
