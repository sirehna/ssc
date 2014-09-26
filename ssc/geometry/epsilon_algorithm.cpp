/*
 * epsilon_algorithm.c
 *
 *  Created on: May 15, 2014
 *      Author: cady
 */

#include <cmath>
#include "ssc/geometry/epsilon_algorithm.hpp"

double ssc::geometry::epsilon_algorithm(std::vector<double> S)
{
    if (S.empty()) return 0;
    if (S.size() == 1) return S.front();
    const int N = (int)S.size()-1;
    int i, k = 1;
    double rLimes = S[N], A_max = 0.0;
    std::vector<double> A(N+1,0);
    while(N - 2*k + 1 >= 0)
    {
        for(i=0; i<=N - 2*k + 1; i++)
        {
            A[i] = (S[i+1] != S[i]) ? A[i+1] + 1.0 / (S[i+1] - S[i]) : A[i+1];
        }
        if(N - 2*k < 0) return rLimes;
        for(i=0; i<=N - 2*k; i++)
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
