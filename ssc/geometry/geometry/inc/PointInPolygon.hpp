/*
 * PointInECAZone.hpp
 *
 * \date 21 mars 2013, 18:00:41
 *  \author cec
 */

#ifndef POINTINECAZONE_HPP_
#define POINTINECAZONE_HPP_

#include <vector>
#include <tr1/memory>
#include "LongitudeLatitude.hpp"

#include "Exception.hpp"

class PointInPolygonException : public Exception
{
    public:
        PointInPolygonException(const char* s) :
                Exception(s)
        {
        }
};


/** \author cec
 *  \brief This class was created to test whether a point is in a polygon.
 *  \details This is a base class: specific coordinate systems (Cartesian, spherical, geographical)
 *  are defined in derived classes. It is a simple wrapper around boost.geometry.
 *  \section ex1 Example
 *  See derived classes.
 */
class PointInPolygon
{
    public:
        bool is_in_polygon(const LongitudeLatitude& point) const;
        virtual ~PointInPolygon();

    private:
        PointInPolygon();

    protected:
        PointInPolygon(const std::vector<LongitudeLatitude>& polygon);
        class PointInPolygonPimpl;
        std::tr1::shared_ptr<PointInPolygonPimpl> pimpl;
};

#endif /* POINTINECAZONE_HPP_ */
