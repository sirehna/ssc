/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Vector3D cartesian coordinates
*/

#ifndef VECTOR3DHPP
#define VECTOR3DHPP

namespace Geometry {

    class Vector3D {
    protected:
        double m_x,m_y,m_z;
    public:
        Vector3D( double x,double y, double z);
        double x() const;// { return m_x; };
        double y() const;// { return m_y; };
        double z() const;// { return m_z; };
        double norm() const;// { return std::sqrt(m_x*m_x+m_y*m_y+m_z*m_z); };
        Vector3D operator-();
        Vector3D&  operator+=(const Vector3D& right);
        Vector3D& operator-=(const Vector3D& right);
        Vector3D& operator*=(double scal);
        Vector3D& operator/=(double scal);
        void normalize();
    };

    Vector3D operator+(Vector3D u,Vector3D v);
    Vector3D operator-(Vector3D u,Vector3D v);
    Vector3D operator*(double a,const Vector3D u);
    Vector3D operator*(Vector3D u,double a);
    double dotProduct(Vector3D u,Vector3D v);
    Vector3D crossProduct(Vector3D u,Vector3D v);

}

#endif
