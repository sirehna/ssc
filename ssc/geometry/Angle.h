/*
* SIREHNA UTILITY
* @NC
* 2006/10/30
* Angle classes with various units
*/

#pragma once

namespace Geometry {

	enum AngleType { e_Radians, e_Degrees, e_DM, e_DMS };

	class AngleValue {
	public:
		virtual double valueInRadians() const = 0; // pure virtual
		virtual double valueInDegrees() const = 0; // pure virtual
		virtual ~AngleValue();

		// decompose the angle into degree, arc minute and arc seconds components
		// note: if angle is negative, all components will be negative (or null)
		virtual void valueInDegreeArcminute(int &deg,double &arcmin) const;
		virtual void valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &sec) const;
		virtual AngleType type() const = 0;
	};

	
	class DMS : public AngleValue {
	protected:
		int m_deg;
		int m_arcmin;
		double m_arcsec;
	public:
		DMS( int d,int m,double s);
		virtual AngleType type() const;
		void normalize();
		virtual double valueInRadians() const;
		virtual double valueInDegrees() const;
		virtual void valueInDegreeArcminute(int &deg,double &arcmin) const;
		virtual void valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &sec) const;
		DMS& operator += (const DMS& operand);
		DMS& operator -= (const DMS& operand);
		DMS& operator *= (double operand);
		DMS& operator /= (double operand);
	};
	
	class DM : public AngleValue {
	protected:
		int m_deg;
		double m_arcmin;
	public:
		DM( int d, double m);
		virtual AngleType type() const;
		void normalize();
		virtual double valueInRadians() const;
		virtual double valueInDegrees() const;
		virtual void valueInDegreeArcminute(int &deg,double &arcmin) const;
		virtual void valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &sec) const;
		DM& operator += (const DM& operand);
		DM& operator -= (const DM& operand);
		DM& operator *= (double operand);
		DM& operator /= (double operand);
	};
	
	class Degrees : public AngleValue {
	protected:
		double m_value;
	public:
		Degrees( double deg);
		virtual AngleType type() const;
		virtual double valueInRadians() const;
		virtual double valueInDegrees() const;
		Degrees& operator += (const Degrees& operand);
		Degrees& operator -= (const Degrees& operand);
		Degrees& operator *= (double operand);
		Degrees& operator /= (double operand);
	};
	
	class Radians : public AngleValue {
	protected:
		double m_value;
	public:
		Radians( double rad);
		virtual AngleType type() const;
		virtual double valueInRadians() const;
		virtual double valueInDegrees() const;
		Radians& operator += (const Radians& operand);
		Radians& operator -= (const Radians& operand);
		Radians& operator *= (double operand);
		Radians& operator /= (double operand);
	};
	
	class Angle {
	protected:
		AngleValue *m_value;
	public:
		Angle();
		Angle(const AngleValue &a);
		Angle(const Angle &a);
		virtual ~Angle();
		double cos() const;
		double sin() const;
		double tan() const;
		int    sign() const; // return -1,0,or +1
		Radians  abs() const;
		virtual double valueInRadians() const;
		virtual double valueInDegrees() const;

		// decompose the angle into degree, arc minute and arc seconds components
		// note: if angle is negative, all components will be negative (or null)
		virtual void valueInDegreeArcminute(int &deg,double &arcmin) const;
		virtual void valueInDegreeArcminuteArcsecond(int &deg,int &arcmin,double &sec) const;

		Angle & operator=( const Angle &operand);
		Angle operator-();
		Angle &  operator += (const Angle  &operand);
		Angle &  operator -= (const Angle  &operand);
		Angle &  operator *= (double d);
		Angle &  operator /= (double d);
	};

	Angle operator+(const Angle& a,const Angle& b);
	Angle operator-(const Angle& a,const Angle& b);
	Angle operator*(double d, const Angle& a);
	Angle operator*(const Angle& a,double d);
	Angle operator/(const Angle& a,double d);
	bool operator<(const Angle& a,const Angle& b);
	bool operator<=(const Angle& a,const Angle& b);
	bool operator>(const Angle& a,const Angle& b);
	bool operator>=(const Angle& a,const Angle& b);
	bool operator==(const Angle& a,const Angle& b);
	bool operator!=(const Angle& a,const Angle& b);
	Angle min(const Angle& a,const Angle& b);
	Angle max(const Angle& a,const Angle& b);
	
	Angle angle_acos(double rad);
	Angle angle_asin(double rad);
	Angle angle_atan2(double y,double x);
	
}
