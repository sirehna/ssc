/*
 * IndexFinder.cpp
 *
 * \date 10 sept. 2013, 10:03:21
 *  \author cec
 */

#include "IndexFinder.hpp"
#include "test_macros.hpp"
#include <sstream>
#include <cassert>

IndexFinder::IndexFinder(const std::vector<double>& x) : n(x.size()), x_(x), xmin(0), xmax(0), idx_low(0)
{
    if (not(x.empty()))
    {
        xmin = x.front();
        xmax = x.back();
    }
    for (int i = 1 ; i < n ; ++i)
    {
        if (x[i]<=x[i-1])
        {
            std::stringstream ss;
            ss << "x should be in strictly increasing order: x[" << i-1 << "] = " << x.at(i-1)
               << ", but x" << "[" << i << "] = " << x.at(i);
            THROW(__PRETTY_FUNCTION__, IndexFinderException, ss.str());
        }
    }
}

size_t IndexFinder::compute(const double x0)
{
    //COUT(x0);
    if ((x0 < xmin) || (x0 > xmax))
    {
        std::stringstream ss;
        ss << "Received x0 = " << x0 << ", but x0 should be within [" << xmin << "," << xmax << "]";
        THROW(__PRETTY_FUNCTION__, IndexFinderException, ss.str());
    }
    //COUT("");
    int ilo = idx_low;
    int ihi = ilo + 1;
    if (ihi >= n-1)
    {
        if (x0 >= xmax)  return greater_than_max(ilo);
        if (n <= 1)      return lower_than_min(ilo);
        ilo = n - 2;
        ihi = n - 1;
    }
    //COUT("");
    if (x0 >= x_[ihi])   return increase_ihi_to_capture_x(ilo, ihi, x0);
    //COUT("");
    if (x0 >= x_[ilo])   return between_min_and_max(ilo);
    //COUT("");
                         return decrease_ilo_to_capture_x(ilo, ihi, x0);
                         //COUT("");
}

void IndexFinder::adjust_left(int& left) const
{
    while (true)
    {
        if (left == 0) break;
        left = left - 1;
        if (x_[left] < xmax) break;
    }
}

size_t IndexFinder::greater_than_max(const int ilo)
{
      idx_low = ilo;
      return n-1;
}

size_t IndexFinder::lower_than_min(const int ilo)
{
      idx_low = ilo;
      return 0;
}

size_t IndexFinder::between_min_and_max(const int ilo)
{
      idx_low = ilo;
      return ilo;
}

size_t IndexFinder::bisection (const int ilo, const int ihi, const double x)
{
    //COUT(ilo);
    //COUT(ihi);
    /*if ((ilo < 0) || (ihi < 0))
    {
        std::cout.precision(20);
        for (auto it = x_.begin() ; it != x_.end() ; ++it)
        {
            std::cout << *it << std::endl;
        }
        //COUT(x_.size());
    }*/

    assert(ilo>=0);
    assert(ihi>=0);
    const int middle = (ilo + ihi)/2;
    //COUT(middle);
    if (middle == ilo)   return between_min_and_max(ilo);
    //COUT("");
    if (x < x_[middle])  return bisection(ilo, middle, x);
    //COUT("");
                         return bisection(middle, ihi, x);
}

size_t IndexFinder::increase_ihi_to_capture_x(int& ilo, int& ihi, const double x)
{
    int istep = 1;
    while(true)
    {
        ilo = ihi;
        ihi = ilo + istep;
        if (ihi >= n-1)              break;
        if (x < x_[ihi])             return bisection(ilo, ihi, x);
        istep = istep*2;
    }
    if (x >= xmax)
    {
        int left = greater_than_max(ilo);
        adjust_left(left);
        return left;
    }
    ihi = n-1;
    ilo = std::max(0,std::min(ilo, n-1));
    return bisection(ilo, ihi, x);
}

size_t IndexFinder::decrease_ilo_to_capture_x(int& ilo, int& ihi, const double x)
{
    int istep = 1;
    while (ilo > 0)
    {
        //COUT(ilo);
        ihi = ilo;
        ilo = std::max(0,ihi - istep);
        //COUT(ilo);
        //COUT(ihi);
        if (x >= x_[ilo])           return bisection(ilo, ihi, x);
        istep = istep*2;
        //COUT(ilo);
        //COUT(ihi);
    }
    //COUT("");
    ilo = 0;
    if (x < xmin)                 return lower_than_min(ilo);
    //COUT(ilo);
    //COUT(ihi);
    return bisection(ilo, ihi, x);
}
