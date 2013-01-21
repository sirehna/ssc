#ifndef __LINEARINTERPOLATORHPP__
#define __LINEARINTERPOLATORHPP__

#include <vector>
#include <cstddef>

class LinearInterpolator
{
    public:
        LinearInterpolator(const double& xmin_, const double& xmax_, const std::vector<double>& y_);

        void set_x(const double& x0);
        double f() const;
        double df() const;
        inline double d2f() const {return 0;}
    private:
        LinearInterpolator();
        size_t idx;
        const double xmin;
        const double xmax;
        const std::vector<double> y;
        const size_t n;
        const double delta_x;
        double x;
};


#endif
