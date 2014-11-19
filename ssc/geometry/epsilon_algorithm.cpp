/*
 * epsilon_algorithm.c
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#include <cmath>
#include <cstdlib> //size_t
#include "ssc/geometry/epsilon_algorithm.hpp"

double ssc::geometry::epsilon_algorithm(std::vector<double> S)
{
    if (S.empty()) return 0;
    if (S.size() == 1) return S.front();
    const int N = (int)S.size()-1;
    size_t i, k = 1;
    double rLimes = S[(size_t)N], A_max = 0.0;
    std::vector<double> A((size_t)N+1,0);
    while((int)((size_t)N - 2*k + 1) >= 0)
    {
        for(i=0; i<=(size_t)((size_t)N - 2*k + 1); i++)
        {
            A[i] = (S[i+1] != S[i]) ? A[i+1] + 1.0 / (S[i+1] - S[i]) : A[i+1];
        }
        if(N - 2*(int)k < 0) return rLimes;
        for(i=0; i<=(size_t)(N - (int)(2*k)); i++)
        {
            S[i] = (A[i+1] != A[i]) ?
            S[i+1] + 1.0 / (A[i+1] - A[i]) : S[i+1];
            if(fabs(A[i]) > A_max)
            {
                A_max = fabs(A[i]);
                rLimes = S[i];
                if(S[i+1] == S[i]) return rLimes;
            }
        }
        k++;
    }
    return rLimes;
}
