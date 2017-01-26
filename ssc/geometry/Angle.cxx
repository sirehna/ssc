/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Angle classes with various units
*/

#include "Angle.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace Geometry;

//
// Angle generic functions
//
Angle::Angle() :m_value(new Radians(0.0)) {

}

Angle::Angle(const AngleValue &av) : m_value(0) {
    switch(av.type()) {
    case e_Radians:
        m_value = new Radians( * reinterpret_cast<const Radians *>(&av) );
        break;
    case e_Degrees:
        m_value = new Degrees( * reinterpret_cast<const Degrees *>(&av) );
        break;
    case e_DM:
        m_value = new DM( * reinterpret_cast<const DM *>(&av) );
        break;
    case e_DMS:
        m_value = new DMS( * reinterpret_cast<const DMS *>(&av) );
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
}
Angle::Angle(const Angle &a) : m_value(NULL){
    switch(a.m_value->type()) {
    case e_Radians:
        m_value = new Radians( *reinterpret_cast<Radians *>(a.m_value) );
        break;
    case e_Degrees:
        m_value = new Degrees( *reinterpret_cast<Degrees *>(a.m_value) );
        break;
    case e_DM:
        m_value = new DM( *reinterpret_cast<DM *>(a.m_value) );
        break;
    case e_DMS:
        m_value = new DMS( *reinterpret_cast<DMS *>(a.m_value) );
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
}
Angle::~Angle() {
    delete m_value;
}
Angle & Angle::operator=(const Angle &a) {
    switch(a.m_value->type()) {
    case e_Radians:
        delete m_value;
        m_value = new Radians( *reinterpret_cast<Radians *>(a.m_value) );
        break;
    case e_Degrees:
        delete m_value;
        m_value = new Degrees( *reinterpret_cast<Degrees *>(a.m_value) );
        break;
    case e_DM:
        delete m_value;
        m_value = new DM( *reinterpret_cast<DM *>(a.m_value) );
        break;
    case e_DMS:
        delete m_value;
        m_value = new DMS( *reinterpret_cast<DMS *>(a.m_value) );
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
    return *this;
}

Angle & Angle::operator+=(const Angle &a) {
    switch(m_value->type()) {
    case e_Radians:
        *reinterpret_cast<Radians *>(m_value) += Radians(a.valueInRadians());
        break;
    case e_Degrees:
        *reinterpret_cast<Degrees *>(m_value) += Degrees(a.valueInDegrees());
        break;
    case e_DM:
    {
        int d;double m;
        a.valueInDegreeArcminute(d,m);
        *reinterpret_cast<DM *>(m_value) += DM(d,m);
    }
        break;
    case e_DMS:
    {
        int d,m;double s;
        a.valueInDegreeArcminuteArcsecond(d,m,s);
        *reinterpret_cast<DMS *>(m_value) += DMS(d,m,s);
    }
        break;
    default:
        perror("unknown angle type\n");
        abort();
        break;
    }
    return *this;
}
Angle & Angle::operator-=(const Angle &a) {
    int d1,d2,m2;
    double m1,s2;
    switch(m_value->type()) {
    case e_Radians:
        *reinterpret_cast<Radians *>(m_value) -= Radians(a.valueInRadians());
        break;
    case e_Degrees:
        *reinterpret_cast<Degrees *>(m_value) -= Degrees(a.valueInDegrees());
        break;
    case e_DM:
        a.valueInDegreeArcminute(d1,m1);
        *reinterpret_cast<DM *>(m_value) -= DM(d1,m1);
        break;
    case e_DMS:
        a.valueInDegreeArcminuteArcsecond(d2,m2,s2);
        *reinterpret_cast<DMS *>(m_value) -= DMS(d2,m2,s2);
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
    return *this;
}
Angle & Angle::operator*=(double d) {
    switch(m_value->type()) {
    case e_Radians:
        *reinterpret_cast<Radians *>(m_value) *=  d;
        break;
    case e_Degrees:
        *reinterpret_cast<Degrees *>(m_value) *= d;
        break;
    case e_DM:
        *reinterpret_cast<DM *>(m_value) *= d;
        break;
    case e_DMS:
        *reinterpret_cast<DMS *>(m_value) *= d;
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
    return *this;
}
Angle & Angle::operator/=(double d) {
    switch(m_value->type()) {
    case e_Radians:
        *reinterpret_cast<Radians *>(m_value) /=  d;
        break;
    case e_Degrees:
        *reinterpret_cast<Degrees *>(m_value) /= d;
        break;
    case e_DM:
        *reinterpret_cast<DM *>(m_value) /= d;
        break;
    case e_DMS:
        *reinterpret_cast<DMS *>(m_value) /= d;
        break;
    default:
        perror("unknown angle type\n");
        abort();
    }
    return *this;
}
double Angle::cos() const {
    return std::cos(valueInRadians());
}
double Angle::sin() const {
    return std::sin(valueInRadians());
}
double Angle::tan() const {
    return std::tan(valueInRadians());
}
Radians Angle::abs() const {
    return Radians(std::fabs(valueInRadians()));
}
int Angle::sign() const {
    double rd=valueInRadians();
    return (rd<0) ? -1 : ((rd>0) ? +1 : 0);
}
void Angle::valueInDegreeArcminute(int &deg,double &arcmin) const {
    m_value->valueInDegreeArcminute(deg,arcmin);
}
void Angle::valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &arcsec) const {
    m_value->valueInDegreeArcminuteArcsecond(deg,arcmin,arcsec);
}
double Angle::valueInDegrees() const {
    return m_value->valueInDegrees();
}
double Angle::valueInRadians() const {
    return m_value->valueInRadians();
}
Angle Angle::operator-() {
    switch(m_value->type()) {
    case e_Radians: {
        return Angle(Radians( -valueInRadians() ));
    } case e_Degrees: {
        return Angle(Degrees( -valueInDegrees() ));
    } case e_DM: {
        int d;
        double m;
        valueInDegreeArcminute(d,m);
        return Angle(DM( -d,-m ));
    } case e_DMS: {
        int d,m;
        double s;
        valueInDegreeArcminuteArcsecond(d,m,s);
        return Angle(DMS( -d,-m,-s ));
    } default:
        perror("unknown angle type\n");
        abort();
    }
}

AngleValue::~AngleValue()
{

}


//
// AngleValue generic functions
//

void AngleValue::valueInDegreeArcminute(int &deg,double &arcmin) const
{
    double d=valueInDegrees();
    deg=static_cast<int>(d);
    arcmin=(d-deg)*60.0;
}
void AngleValue::valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &arcsec) const
{
    double d=valueInDegrees();
    deg=static_cast<int>(d);
    double m=(d-deg)*60.0;
    arcmin=static_cast<int>(m);
    arcsec=(m-arcmin)*60.0;
}

//
// Angle in Degree Arc-minute Arc-second.fraction second
//

DMS::DMS( int d,int m,double s) : m_deg(d), m_arcmin(m), m_arcsec(s)
{
    normalize();}

void DMS::normalize() {
    bool loop;
    {
        loop=false;
        int x = (static_cast<int>(m_arcsec)) / 60;
        m_arcsec -= 60*x;
        m_arcmin += x;
        x = ((int) m_arcmin) / 60;
        m_arcmin -= 60*x;
        m_deg += x;

        if(m_deg > 0 && m_arcmin < 0) {
            m_deg -= 1;
            m_arcmin += 60;
        }
        if(m_deg < 0 && m_arcmin > 0) {
            m_deg += 1;
            m_arcmin -= 60;
        }
        if((m_deg > 0 || m_arcmin > 0) && m_arcsec < 0) {
            m_arcmin -= 1;
            m_arcsec += 60;
            loop=true;
        }
        if((m_deg < 0 || m_arcmin < 0) && m_arcsec > 0) {
            m_arcmin += 1;
            m_arcsec -= 60;
            loop=true;
        }
    } while(loop);
}
double DMS::valueInDegrees() const {
    return m_deg+m_arcmin/60.0+m_arcsec/3600.0;
}
double DMS::valueInRadians() const {
    return valueInDegrees()*M_PI/180.0;
}
void DMS::valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &arcsec) const
{
    deg=m_deg;
    arcmin=m_arcmin;
    arcsec=m_arcsec;
}
void DMS::valueInDegreeArcminute(int &deg,double &arcmin) const
{
    deg=m_deg;
    arcmin=m_arcmin+m_arcsec/60.0;
}
DMS&  DMS::operator += (const DMS&  operand) {
    int d,m;
    double s;
    operand.valueInDegreeArcminuteArcsecond(d,m,s);
    m_arcsec+=s;
    m_arcmin+=m;
    m_deg+=d;
    normalize();
    return *this;
}
DMS&  DMS::operator -= (const DMS&  operand) {
    int d,m;
    double s;
    operand.valueInDegreeArcminuteArcsecond(d,m,s);
    m_arcsec-=s;
    m_arcmin-=m;
    m_deg-=d;
    normalize();
    return *this;
}
DMS&  DMS::operator *= (double d) {
    Degrees tmp( valueInDegrees()*d);
    tmp.valueInDegreeArcminuteArcsecond(m_deg,m_arcmin,m_arcsec);
    normalize();
    return *this;
}
DMS&  DMS::operator /= (double d) {
    Degrees tmp( valueInDegrees()/d);
    tmp.valueInDegreeArcminuteArcsecond(m_deg,m_arcmin,m_arcsec);
    normalize();
    return *this;
}
AngleType DMS::type() const {
    return e_DMS;
}
//
// Angle in Degree Arc-minute.fraction minute
//

DM::DM( int d,double m) : m_deg(d), m_arcmin(m)
{
    normalize();}

void DM::normalize() {
    int x = (static_cast<int>(m_arcmin)) / 60;
    m_arcmin -= 60*x;
    m_deg += x;
    if(m_deg > 0 && m_arcmin < 0) {
        m_deg -= 1;
        m_arcmin += 60;
    }
    if(m_deg < 0 && m_arcmin > 0) {
        m_deg += 1;
        m_arcmin -= 60;
    }
}
double DM::valueInDegrees() const {
    return m_deg+m_arcmin/60.0;
}
double DM::valueInRadians() const {
    return valueInDegrees()*M_PI/180.0;
}
void DM::valueInDegreeArcminute(int &deg,double &arcmin) const
{
    deg=m_deg;
    arcmin=m_arcmin;
}
void DM::valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &arcsec) const
{
    deg=m_deg;
    arcmin=static_cast<int>(m_arcmin);
    arcsec=(m_arcmin-arcmin)*60.0;
}
DM&  DM::operator += (const DM&  operand) {
    int d;
    double m;
    operand.valueInDegreeArcminute(d,m);
    m_arcmin+=m;
    m_deg+=d;
    normalize();
    return *this;
}
DM&  DM::operator -= (const DM&  operand) {
    int d;
    double m;
    operand.valueInDegreeArcminute(d,m);
    m_arcmin-=m;
    m_deg-=d;
    normalize();
    return *this;
}
DM&  DM::operator *= (double d) {
    Degrees tmp( valueInDegrees()*d);
    tmp.valueInDegreeArcminute(m_deg,m_arcmin);
    normalize();
    return *this;
}
DM&  DM::operator /= (double d) {
    Degrees tmp( valueInDegrees()/d);
    tmp.valueInDegreeArcminute(m_deg,m_arcmin);
    normalize();
    return *this;
}
AngleType DM::type() const {
    return e_DM;
}

//
// Angle in Degree.fraction degree
//

Degrees::Degrees(double deg) : m_value(deg)
        {
}
double Degrees::valueInDegrees() const {
    return m_value;
}
double Degrees::valueInRadians() const {
    return valueInDegrees()*M_PI/180;
}
Degrees&  Degrees::operator += (const Degrees&  operand) {
    m_value += operand.valueInDegrees();
    return *this;
}
Degrees&  Degrees::operator -= (const Degrees&  operand) {
    m_value -= operand.valueInDegrees();
    return *this;
}
Degrees&  Degrees::operator *= (double d) {
    m_value *= d;
    return *this;
}
Degrees&  Degrees::operator /= (double d) {
    m_value /= d;
    return *this;
}
AngleType Degrees::type() const {
    return e_Degrees;
}
//
// Angle in Radians
//

Radians::Radians(double rad) : m_value(rad){
}
double Radians::valueInDegrees() const {
    return m_value*180/M_PI;
}
double Radians::valueInRadians() const {
    return m_value;
}
Radians&  Radians::operator += (const Radians&  operand) {
    m_value += operand.valueInRadians();
    return *this;
}
Radians&  Radians::operator -= (const Radians&  operand) {
    m_value -= operand.valueInRadians();
    return *this;
}
Radians&  Radians::operator *= (double d) {
    m_value *= d;
    return *this;
}
Radians&  Radians::operator /= (double d) {
    m_value /= d;
    return *this;
}
AngleType Radians::type() const {
    return e_Radians;
}

//
// binary operations on angles
//

Angle Geometry::operator+(const Angle& a,const Angle& b) {
    Angle result(a);
    result += b;
    return result;
}
Angle Geometry::operator-(const Angle& a,const Angle& b) {
    Angle result(a);
    result -= b;
    return result;
}
Angle Geometry::operator*(double d,const Angle& a) {
    Angle result(a);
    result *= d;
    return result;
}
Angle Geometry::operator*(const Angle& a,double d){
    Angle result(a);
    result *= d;
    return result;
}
Angle Geometry::operator/(const Angle& a,double d) {
    Angle result(a);
    result /= d;
    return result;
}
bool Geometry::operator<(const Angle& a,const Angle& b) {
    return a.valueInRadians() < b.valueInRadians();
}
bool Geometry::operator<=(const Angle& a,const Angle& b) {
    return a.valueInRadians() <= b.valueInRadians();
}
bool Geometry::operator>(const Angle& a,const Angle& b) {
    return a.valueInRadians() > b.valueInRadians();
}
bool Geometry::operator>=(const Angle& a,const Angle& b) {
    return a.valueInRadians() >= b.valueInRadians();
}
bool Geometry::operator==(const Angle& a,const Angle& b) {
    return a.valueInRadians() == b.valueInRadians();
}
bool Geometry::operator!=(const Angle& a,const Angle& b) {
    return a.valueInRadians() != b.valueInRadians();
}
Angle Geometry::min(const Angle& a,const Angle& b) {
    return (a<b)?a:b;
}
Angle Geometry::max(const Angle& a,const Angle& b) {
    return (a<b)?b:a;
}
//
// inverse trigonometry
//

Angle Geometry::angle_acos(double rad) {
    if(rad>1.0) rad=1.0;
    else if(rad<-1.0) rad=-1.0;
    return Angle(Radians(std::acos(rad)));
}

Angle Geometry::angle_asin(double rad) {
    if(rad>1.0) rad=1.0;
    else if(rad<-1.0) rad=-1.0;
    return Angle(Radians(std::asin(rad)));
}

Angle Geometry::angle_atan2(double y,double x) {
    return Angle(Radians(std::atan2(y,x)));
}
