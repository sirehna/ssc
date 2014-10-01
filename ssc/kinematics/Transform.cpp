#include "ssc/kinematics/Transform.hpp"
#include "ssc/kinematics/KinematicsException.hpp"

using namespace ssc::kinematics;

Transform::Transform() : t(Point()), r(RotationMatrix(Eigen::MatrixXd::Identity(3,3))), to_frame("")
{
}

Transform::Transform(const Point& translation, const std::string& to_frame_) : t(translation), r(RotationMatrix(Eigen::MatrixXd::Identity(3,3))), to_frame(to_frame_)
{
}

Transform::Transform(const RotationMatrix& rotation, const std::string& from_frame, const std::string& to_frame_) : t(Point(from_frame)), r(rotation), to_frame(to_frame_)
{
}

Transform::Transform(const Point& translation, const RotationMatrix& rotation, const std::string& to_frame_) : t(translation), r(rotation), to_frame(to_frame_)
{
}

Eigen::Vector3d Transform::operator*(const Eigen::Vector3d& v) const
{
    return r*v+t.v;
}

Point Transform::operator*(const Point& P) const
{
    if (P.get_frame() != get_from_frame())
    {
        THROW(__PRETTY_FUNCTION__, KinematicsException, std::string("Frames don't match: transform goes from ") + get_from_frame() + " to " + to_frame + ", but point lies in " + P.get_frame());
    }
    return Point(to_frame, operator*(P.v));
}

PointMatrix Transform::operator*(const PointMatrix& P) const
{
    if (P.get_frame() != get_from_frame())
    {
        THROW(__PRETTY_FUNCTION__, KinematicsException, std::string("Frames don't match: transform goes from ") + get_from_frame() + " to " + to_frame + ", but point lies in " + P.get_frame());
    }
    Matrix3Xd m(r*P.m);
    m.colwise() += t.v;
    return PointMatrix(m,to_frame);
}

PointMatrix Transform::operator*(const PointMatrixPtr& P) const
{
    if (P->get_frame() != get_from_frame())
    {
        THROW(__PRETTY_FUNCTION__, KinematicsException, std::string("Frames don't match: transform goes from ") + get_from_frame() + " to " + to_frame + ", but point lies in " + P->get_frame());
    }
    Matrix3Xd m(r*P->m);
    m.colwise() += t.v;
    return PointMatrix(m,to_frame);
}

Velocity Transform::operator*(const Velocity& V) const
{
    if (V.get_frame() != get_from_frame())
    {
        THROW(__PRETTY_FUNCTION__, KinematicsException, std::string("Frames don't match: transform goes from ") + get_from_frame() + " to " + to_frame + ", but velocity is expressed in frame " + V.get_frame());
    }
    const Point P = V.get_point();
    const TranslationVelocityVector t = V.get_translation_velocity();
    const AngularVelocityVector omega = V.get_angular_velocity();
    return Velocity(V.get_point(), (*this)*t, (*this)*omega);
}

Transform Transform::operator*(const Transform& T) const
{
    if (get_from_frame() != T.get_to_frame())
    {
        THROW(__PRETTY_FUNCTION__, KinematicsException, std::string("Frames don't match in cTb*bTa: transform cTb goes from ") + get_from_frame() + " to " + to_frame + ", but transform bTa goes from " + T.get_from_frame() + " to " + T.get_to_frame());
    }
    return Transform(Point(T.get_from_frame(), r*T.t.v + t.v), r*T.r, to_frame);
}

std::string Transform::get_from_frame() const
{
    return t.get_frame();
}

std::string Transform::get_to_frame() const
{
    return to_frame;
}

Transform Transform::inverse() const
{
    return Transform(Point(to_frame, -r.lu().solve(t.v)), r.inverse(), get_from_frame());
}

Point Transform::get_point() const
{
    return t;
}

RotationMatrix Transform::get_rot() const
{
    return r;
}

std::ostream& ssc::kinematics::operator<<(std::ostream& os, const Transform& T)
{
    os << "(" << T.get_from_frame() << " -> " << T.get_to_frame() << "):" << std::endl
       << "R = " << std::endl << T.r << std::endl
       << "t = " << T.t.v.transpose() << std::endl;
    return os;
}

Transform ssc::kinematics::identity(const std::string& frame)
{
    return kinematics::Transform(Point(frame,0,0,0), frame);
}

void Transform::swap()
{
    const auto from_frame = t.get_frame();
    t = Point(to_frame, t.x(), t.y(), t.z());
    to_frame = from_frame;
}
