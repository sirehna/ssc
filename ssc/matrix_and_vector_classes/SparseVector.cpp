#include "ssc/matrix_and_vector_classes/SparseVector.hpp"
#include "ssc/macros/test_macros.hpp"
#include <functional>

using namespace ssc::matrix_and_vector_classes;

SparseVector::SparseVector() :
        nb_of_elements(0),
        values(NULL),
        indexes(NULL),
        current_element(0),
        index_of_last_element(0),
        is_empty(true)
{
}

SparseVector::SparseVector(const SparseVector& A, const SparseVector& B) :
        nb_of_elements(count_nb_of_elements_in_sum(A, B)),
        values(new double[nb_of_elements]),
        indexes(new size_t[nb_of_elements]),
        current_element(0),
        index_of_last_element(0),
        is_empty(true)
{
    add(A, B, *this);
}

SparseVector::~SparseVector()
{
    deallocate_memory();
}

SparseVector::SparseVector(const size_t& nb_of_elements_) :
        nb_of_elements(nb_of_elements_),
        values(new double[nb_of_elements]),
        indexes(new size_t[nb_of_elements]),
        current_element(0),
        index_of_last_element(0),
        is_empty(true)
{
}

SparseVector::SparseVector(const SparseVector& rhs) :
       nb_of_elements(rhs.nb_of_elements),
       values(new double[nb_of_elements]),
       indexes(new size_t[nb_of_elements]),
       current_element(rhs.current_element),
       index_of_last_element(rhs.index_of_last_element),
       is_empty(rhs.is_empty)
{
    initialize_this_with(rhs);
}

void SparseVector::deallocate_memory()
{
    if (values) delete[] values;
    values = NULL;
    if (indexes) delete[] indexes;
    indexes = NULL;
}

SparseVector& SparseVector::operator=(const SparseVector& rhs)
{
    deallocate_memory();
    nb_of_elements = rhs.nb_of_elements;
    values = new double[nb_of_elements];
    indexes = new size_t[nb_of_elements];
    current_element = rhs.current_element;
    index_of_last_element = rhs.index_of_last_element;
    is_empty = rhs.is_empty;
    initialize_this_with(rhs);
    return *this;
}

void SparseVector::initialize_this_with(const SparseVector& rhs)
{
    for (size_t i  = 0 ; i < nb_of_elements ; ++i)
    {
        values[i]         = rhs.values[i];
        indexes[i]        = rhs.indexes[i];
    }
}

void SparseVector::add_element_in_order(const size_t& i, const double& val)
{
    if (current_element>=nb_of_elements)
    {
        THROW(__PRETTY_FUNCTION__, SparseVectorException,
              "Can't set a new element in the vector because the maximum number of elements was reached. Declare a bigger vector.");
    }
    if (not(position_in_vector_is_correct(i)))
    {
        THROW(__PRETTY_FUNCTION__, SparseVectorException,
              "Elements must be added by strictly increasing indexes.");
    }
    values[current_element] = val;
    indexes[current_element] = i;
    index_of_last_element = i;
    current_element++;
    is_empty = false;
}

bool SparseVector::position_in_vector_is_correct(const size_t& i) const
{
    return is_empty || (i > index_of_last_element);
}

double SparseVector::get(const size_t& i) const
{
    bool element_was_found = false;
    bool all_elements_were_scanned = (nb_of_elements==0);
    size_t k = 0;
    while (not(element_was_found || all_elements_were_scanned))
    {
        element_was_found = (indexes[k] == i);
        all_elements_were_scanned = (++k == nb_of_elements);
    }
    if (not(element_was_found))
    {
        THROW(__PRETTY_FUNCTION__, SparseVectorException, "element not found.");
    }
    return values[k-1];
}

size_t * SparseVector::get_indexes() const
{
    return indexes;
}

double * SparseVector::get_values() const
{
    return values;
}

const SparseVector SparseVector::operator*(const double& a) const
{
    SparseVector ret(nb_of_elements);
    for (size_t k = 0 ; k < nb_of_elements ; ++k)
    {
        ret.values[k] = a*values[k];
        ret.indexes[k] = indexes[k];
    }
    ret.current_element       = current_element;
    ret.is_empty              = is_empty;
    ret.index_of_last_element = index_of_last_element;
    return ret;
}

const SparseVector ssc::matrix_and_vector_classes::operator*(const double& a, const SparseVector& M)
{
    return (M*a);
}

void SparseVector::multiply_in_place_by(const double& a)
{
    for (size_t k = 0 ; k < nb_of_elements ; ++k)
    {
        values[k] *= a;
    }
}

SparseVector SparseVector::append(const SparseVector& rhs) const
{
    const size_t nc = this->nb_of_elements + rhs.nb_of_elements;
    SparseVector C(nc);
    size_t k = 0;
    for (size_t i = 0; i < this->nb_of_elements; ++i) {
        C.indexes[k] = indexes[i];
        C.values[k] = values[i];
        k++;
    }
    for (size_t i = 0; i < rhs.nb_of_elements; ++i) {
        C.indexes[k] = rhs.indexes[i];
        C.values[k] = values[i];
        k++;
    }
    if (k>0)
    {
        C.is_empty = false;
        C.index_of_last_element    = C.indexes[k-1];
        C.current_element          = k-1;
    }
    return C;
}

SparseVector SparseVector::operator+(const SparseVector& rhs) const
{
    const size_t nc = count_nb_of_elements_in_sum(*this, rhs);
    SparseVector C(nc);
    add(*this, rhs, C);
    return C;
}

size_t SparseVector::count_nb_of_elements_in_sum(const SparseVector& A, const SparseVector& B) const
{
    size_t ka = 0;
    size_t kb = 0;
    size_t nc = 0;
    for(;(ka<A.nb_of_elements)&&(kb<B.nb_of_elements);)
    {
        if (A.indexes[ka] < B.indexes[kb])
        {
            ++ka;
        }
        else if (A.indexes[ka] == B.indexes[kb])
        {
            ++ka;
            ++kb;
        }
        else
        {
            ++kb;
        }
        ++nc;
    }
    nc += (A.nb_of_elements-ka) + (B.nb_of_elements-kb);
    return nc;
}

void SparseVector::add(const SparseVector& A, const SparseVector& B, SparseVector& C) const
{
    size_t ka = 0;
    size_t kb = 0;
    size_t kc = 0;
    for(;(ka<A.nb_of_elements)&&(kb<B.nb_of_elements);)
    {
        if (A.indexes[ka] < B.indexes[kb])
        {
            C.indexes[kc]    = A.indexes[ka];
            C.values[kc]     = A.values[ka];
            ++ka;
        }
        else if (A.indexes[ka] == B.indexes[kb])
        {
            C.indexes[kc]    = A.indexes[ka];
            C.values[kc]     = A.values[ka] + B.values[kb];
            ++ka;
            ++kb;
        }
        else
        {
            C.indexes[kc]    = B.indexes[kb];
            C.values[kc]     = B.values[kb];
            ++kb;
        }
        ++kc;
    }
    fetch_extra_elements_if_vectors_have_different_nb_of_elements(ka, A, kc, C);
    fetch_extra_elements_if_vectors_have_different_nb_of_elements(kb, B, kc, C);
    if (kc>0)
    {
        C.is_empty = false;
        C.index_of_last_element    = C.indexes[kc-1];
        C.current_element          = kc-1;
    }
}

void SparseVector::fetch_extra_elements_if_vectors_have_different_nb_of_elements(size_t& k, const SparseVector& M, size_t& kc, SparseVector& C) const
{
    for (;k<M.nb_of_elements;++k,++kc)
    {
        C.indexes[kc]    = M.indexes[k];
        C.values[kc]     = M.values[k];
    }
}

size_t SparseVector::size() const
{
    return nb_of_elements;
}

bool SparseVector::empty() const
{
    return nb_of_elements==0;
}

SparseVector ssc::matrix_and_vector_classes::sum(const SparseVector& accumulator, const std::vector<SparseVector>& v)
{
    if (v.empty())           return accumulator;
    if (accumulator.empty()) return sum(v.at(0), std::vector<SparseVector>(v.begin()+1, v.end()));
                             return SparseVector(accumulator, sum(v.at(0), std::vector<SparseVector>(v.begin()+1, v.end())));
}

SparseVector ssc::matrix_and_vector_classes::sum(const std::vector<SparseVector>& v)
{
    if (v.empty())   return SparseVector();
    if (v.size()==1) return v.at(0);
                     return sum(v.at(0), std::vector<SparseVector>(v.begin()+1, v.end()));
}

void SparseVector::divide_in_place(const double& lambda)
{
    for (size_t k = 0 ; k < nb_of_elements ; ++k)
    {
        values[k] /= lambda;
    }
}

SparseVector SparseVector::operator/(const double& lambda) const
{
    SparseVector ret(*this);
    ret.divide_in_place(lambda);
    return ret;
}

SparseVector SparseVector::operator-(const SparseVector& rhs) const
{
    SparseVector ret(rhs);
    ret.multiply_in_place_by(-1);
    return SparseVector(*this, ret);
}

bool SparseVector::operator==(const SparseVector& rhs) const
{
    if (is_empty != rhs.is_empty)                           return false;
    if (index_of_last_element != rhs.index_of_last_element) return false;
    if (nb_of_elements != rhs.nb_of_elements)               return false;
    for (size_t i = 0 ; i < nb_of_elements ; ++i)
    {
        if (indexes[i] != rhs.indexes[i])                   return false;
        if (values[i] != rhs.values[i])                     return false;
    }
                                                            return true;
}

bool SparseVector::operator!=(const SparseVector& rhs) const
{
    return not(operator==(rhs));
}

SparseVector& SparseVector::operator+=(const SparseVector& rhs)
{
    const SparseVector S = *this + rhs;
    *this = S;
    return *this;
}

::std::ostream& ssc::matrix_and_vector_classes::operator<<(::std::ostream& os, const SparseVector& bar)
{
    size_t k = 0;
    os.width(2);
    os.precision(0);
    os.setf(os.fixed);
    os << "( 1 x " << bar.nb_of_elements <<  " ), empty: " << bar.is_empty << std::endl;
    os << "[ ";
    os.width(11);
    os.precision(4);
    os.setf(os.scientific);
    os.setf(os.right);
    for (size_t i = 0 ; i < bar.nb_of_elements ; ++i)
    {
        if (bar.indexes[k] == i)
        {
            os << bar.values[k];
            k++;
        }
        else
        {
            os << double(0);
        }
        os << " ";
    }
    os << "]" << std::endl;
    return os;
}


void SparseVector::copy_indexes_to(const size_t& n, size_t * const array) const
{
    if (!array)
    {
        THROW(__PRETTY_FUNCTION__,SparseVectorException,"Received a null pointer");
    }
    if (n != nb_of_elements)
    {
        THROW(__PRETTY_FUNCTION__,SparseVectorException,"n does not match the number of elements");
    }
    for (size_t i = 0 ; i < n ; ++i) array[i] = indexes[i];
}

void SparseVector::copy_values_to(const size_t& n, double * const array) const
{
    if (!array)
    {
        THROW(__PRETTY_FUNCTION__,SparseVectorException,"Received a null pointer");
    }
    if (n != nb_of_elements)
    {
        THROW(__PRETTY_FUNCTION__,SparseVectorException,"n does not match the number of elements");
    }
    for (size_t i = 0 ; i < n ; ++i) array[i] = values[i];
}

