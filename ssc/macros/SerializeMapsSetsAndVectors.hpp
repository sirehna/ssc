/*Le présent logiciel est une connaissance propre de SIREHNA, au sens de l'article 2 de
l'Accord-Cadre de Propriété Intellectuelle (Annexe à la convention pluriannuelle avec l'IRT).

On en rappelle ici les paragraphes 5.2.4 et 5.2.5 :
"(...) l'utilisation de la décompilation, du reverse engineering ou de toute autre méthode permettant
de retrouver les codes sources à partir des exécutables est strictement prohibée sauf à obtenir
l'autorisation écrite préalable du Membre ou de l'IRT titulaire de ladite Connaissance Propre."

"En dehors des cas précités un Membre ou l'IRT peut opposer à un autre Membre ou à l'IRT ses
Connaissances Propres conformément à la loi, rien dans ce qui précède ne pouvant être interprété
comme une limitation des droits d'un Membre ou de l'IRT d'obtenir réparation du préjudice causé par
l'utilisation non consentie d'une de ses Connaissances Propres par un Membre, par l'IRT dans tous
les cas qui ne sont pas explicitement prévus dans l'ACPI, cette réparation pouvant être obtenue par
toutes les voies de droit appropriées."

(c) SIREHNA 2014.
*//*
 * SerializeMapsSetsAndVectors.hpp
 *
 *  Created on: Mar 4, 2015
 *      Author: cady
 */



#ifdef _GLIBCXX_VECTOR
#ifndef SERIALIZEVECTORS_HPP_
#define SERIALIZEVECTORS_HPP_
#include <ostream>
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& m)
{
    os << "[";
    if (not(m.empty())) os << m.front();
    for (size_t i = 1 ; i < m.size() ; ++i)
    {
        os << ", " << m.at(i);
    }
    os << "]";
    return os;
}
#endif
#endif

#ifdef _GLIBCXX_MAP
#ifndef SERIALIZEMAPS_HPP_
#define SERIALIZEMAPS_HPP_
#include <ostream>
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::map<T,U>& m)
{
    os << "{";
    if (not(m.empty())) os << m.begin()->first << ": " << m.begin()->second;
    for (auto it = m.begin() ; it != m.end() ; ++it)
    {
        if (it!=m.begin()) os << ", " << it->first << ": " << it->second;
    }
    os << "}";
    return os;
}
#endif
#endif

#ifdef _STL_PAIR_H
#ifndef SERIALIZEPAIRS_HPP_
#define SERIALIZEPAIRS_HPP_
#include <ostream>
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& m)
{
    os << "(" << m.first << "," << m.second << ")";
    return os;
}
#endif
#endif

#ifdef _GLIBCXX_SET
#ifndef SERIALIZESET_HPP_
#define SERIALIZESET_HPP_
#include <ostream>
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& m)
{
    os << "{";
    if (not(m.empty())) os << *m.begin();
    for (auto it = m.begin() ; it != m.end() ; ++it)
    {
        if (it!=m.begin()) os << ", " << *it;
    }
    os << "}";
    return os;
}
#endif
#endif

