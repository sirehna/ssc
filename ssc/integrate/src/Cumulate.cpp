/*
 * Cumulate.cpp
 *
 * \date 8 oct. 2013, 08:22:31
 *  \author cec
 */

//#include <vector>
#include <list>

#include "Cumulate.hpp"
#include "CumulateException.hpp"
#include "generic_pimpl_implementation.hpp"
#include "test_macros.hpp"

class Cumulate::Impl
{
    public:
        Impl() : x_y_pairs(std::list<std::pair<double,double> >())
        {

        }

        void add(const double x, const double y)
        {
            /*
            const std::vector<double> x_old = xs;
            const std::vector<double> y_old = ys;
            const std::vector<double> integrals_old = integrals;
            const size_t n = xs.size();
            xs.clear();
            ys.clear();
            integrals.clear();
            for (size_t i = 0 ; i < n-1 ; ++i)
            {
                if (x < x_old.at(i))
                {
                    xs.push_back(x_old.at(i));
                    ys.push_back(y_old.at(i));
                    integrals.push_back(integrals_old.at(i));
                }
                if ((x_old.at(i) <= x) && (x < x_old.at(i+1)))
                {
                    xs.push_back(x);
                    ys.push_back(y);
                    integrals.push_back(integrals.back() + partial_integral(get_interval_index(x_old.at(i)), x));
                    integrals.push_back(integrals.back() + partial_integral(get_interval_index(x_old.at(i)), x));
                }
                if (x_old.at(i+1) <= x)
                {

                }
            }*/
            x_y_pairs.push_back(std::make_pair(x,y));
            x_y_pairs.sort();
        }

        double integrate(const double a, const double b) const
        {
            if (x_y_pairs.size()<2)
            {
                THROW(__PRETTY_FUNCTION__, CumulateException, "Not enough points: use Cumulate::add");
            }
            double ret = 0;
            for (auto it1 = x_y_pairs.begin() ; it1 != x_y_pairs.end() ; ++it1)
            {
                auto it2 = it1;
                if (++it2 != x_y_pairs.end())
                {
                    double x1 = it1->first;
                    double x2 = it2->first;
                    double y1 = it1->second;
                    double y2 = it2->second;
                    if ((it1->first < a) && (it2->first >= a))
                    {
                        y1 = (y2-y1)/(x2-x1)*(a-x1)+y1;
                        x1 = a;
                    }
                    if ((it1->first < b)&&(it2->first >= b))
                    {
                        y2 = (y2-y1)/(x2-x1)*(b-x2)+y2;
                        x2 = b;
                    }
                    if ((it1->first<b) && (it2->first>=a))
                    {
                        ret += (x2-x1)*(y1+y2)/2;
                    }
                }
            }
            /*
            const size_t idx1 = get_interval_index(a);
            const double I1 = integrals.at(idx1);
            const double Ia = partial_integral(idx1, a);

            const size_t idx2 = get_interval_index(b);
            const double I2 = integrals.at(idx2);
            const double Ib = partial_integral(idx2, a);

            return I2-I1+Ib-Ia;*/
            return ret;
        }

    private:
        /*
        double ordinate(const size_t idx, const double x0) const
        {
            const double x1 = xs.at(idx);
            const double x2 = xs.at(idx+1);
            const double y1 = ys.at(idx);
            const double y2 = ys.at(idx+1);
            return (y2-y1)/(x2-x1)*(x0-x1)+y1;
        }

        double partial_integral(const size_t idx, const double x2) const
        {
            const double x1 = xs.at(idx);
            const double y1 = ys.at(idx);
            const double y2 = ordinate(idx, x2);
            return (x2-x1)*(y1+y2)/2;
        }

        size_t get_interval_index(const double x0, size_t& idx_min=0, size_t& idx_max=xs.size()-1) const
        {
            if (xs.empty()) return 0;
            if (xs.size()==1) return 0;
            if ((idx_max-idx_min) <= 2) return std::min((idx_min+idx_max)/2, xs.size()-2);
            const double xmin = xs.at(idx_min);
            if (x0 <= xmin)
            {
                if (idx_min == 0) return 0;
                return get_interval_index(x0, idx_min/2, idx_min);
            }
            const double xmax = xs.at(idx_max);
            if (x0 >= xmax)
            {
                if (idx_max == (xs.size()-1)) return xs.size()-1;
                return get_interval_index(x0, idx_max, std::min(xs.size()-1,2*idx_max));
            }
            const size_t idx_mid = (idx_min+idx_max)/2;
            const double xmid = xs.at(idx_mid);
            if (x0<=xmid) return get_interval_index(x0, idx_min, idx_mid);
            return get_interval_index(x0, idx_mid, idx_max);
        }
        std::vector<double> xs;
        std::vector<double> ys;
        std::vector<double> integrals;*/
        std::list<std::pair<double,double> > x_y_pairs;

};


Cumulate::Cumulate() : pimpl{Impl{}}
{

}

Cumulate::~Cumulate()
{

}

void Cumulate::add(const double x, const double y)
{
    pimpl->add(x,y);
}

double Cumulate::integrate(const double a, const double b)
{
    return pimpl->integrate(a,b);
}
