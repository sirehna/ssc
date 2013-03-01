/*
 * IpoptParameters.hpp
 *
 * \date 26 févr. 2013, 10:31:33
 *  \author cec
 */

#ifndef IPOPTPARAMETERS_HPP_
#define IPOPTPARAMETERS_HPP_

/** \author cec
 *  \brief This class was created to
 *  \details It has the following responsibilities:
 *  - Resp. 1 ...
 *  \section ex1 Example
 *  \snippet MODULE_NAME/unit_tests/src/IpoptParametersTest.cpp IpoptParametersTest example
 *  \section ex2 Expected output
 *  \snippet MODULE_NAME/unit_tests/src/IpoptParametersTest.cpp IpoptParametersTest expected output
 */

#include "Exception.hpp"

class PositiveDoubleException : public Exception
{
    public:
        PositiveDoubleException(const char* s) :
                Exception(s)
        {
        }
};


class PositiveDouble
{
    public:
        PositiveDouble(const double& val);
        operator double() const;
        double operator+(const double& rhs) const;
        PositiveDouble operator+(const PositiveDouble& rhs) const;
        double operator-(const double& rhs) const;
        double operator-(const PositiveDouble& rhs) const;
        PositiveDouble operator*(const PositiveDouble& rhs) const;
        double operator*(const double& rhs) const;
        PositiveDouble operator/(const PositiveDouble& rhs) const;
        PositiveDouble& operator+=(const PositiveDouble& rhs) const;
        double operator/(const double& rhs) const;
        PositiveDouble& operator=(const PositiveDouble& rhs);
        bool operator==(const double& rhs) const;
        bool operator==(const PositiveDouble& rhs) const;

    private:
        double value;

};

double operator+(const double& lhs, const PositiveDouble& rhs);
double operator-(const double& lhs, const PositiveDouble& rhs);
double operator*(const double& lhs, const PositiveDouble& rhs);
double operator/(const double& lhs, const PositiveDouble& rhs);

class IpoptParameters
{
    public:
        IpoptParameters();
        PositiveDouble tolerance;
        PositiveDouble bound_relaxation_factor;
        std::string mu_strategy;
        size_t print_level;
        size_t maximum_number_of_iterations;
        bool trace_function_calls;
};

#endif /* IPOPTPARAMETERS_HPP_ */
