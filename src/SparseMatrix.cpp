#include "SparseMatrix.hpp"
#include "test_macros.hpp"
#include <assert.h>
#include <math.h>
#include <list>

SparseMatrix::SparseMatrix() :
        nb_of_elements(0),
        values(NULL),
        row_indexes(NULL),
        column_indexes(NULL),
        current_element(0),
        row_index_of_last_element(0),
        column_index_of_last_element(0),
        is_empty(true)
{
}

SparseMatrix::SparseMatrix(const SparseMatrix& A, const SparseMatrix& B) :
        nb_of_elements(count_nb_of_elements_in_sum(A, B)),
        values(new double[nb_of_elements]),
        row_indexes(new size_t[nb_of_elements]),
        column_indexes(new size_t[nb_of_elements]),
        current_element(0),
        row_index_of_last_element(0),
        column_index_of_last_element(0),
        is_empty(true)
{
    add(A, B, *this);
}

SparseMatrix::~SparseMatrix()
{
    deallocate_memory();
}

bool SparseMatrix::empty() const
{
    return is_empty;
}

SparseMatrix::SparseMatrix(const size_t& nb_of_elements_) :
        nb_of_elements(nb_of_elements_),
        values(new double[nb_of_elements]),
        row_indexes(new size_t[nb_of_elements]),
        column_indexes(new size_t[nb_of_elements]),
        current_element(0),
        row_index_of_last_element(0),
        column_index_of_last_element(0),
        is_empty(true)
{
    for(size_t i = 0 ; i < nb_of_elements ; ++i)
    {
        values[i] = 0;
        row_indexes[i] = 0;
        column_indexes[i] = 0;
    }
}

SparseMatrix::SparseMatrix(const SparseMatrix& rhs) :
       nb_of_elements(rhs.nb_of_elements),
       values(new double[nb_of_elements]),
       row_indexes(new size_t[nb_of_elements]),
       column_indexes(new size_t[nb_of_elements]),
       current_element(rhs.current_element),
       row_index_of_last_element(rhs.row_index_of_last_element),
       column_index_of_last_element(rhs.column_index_of_last_element),
       is_empty(rhs.is_empty)
{
    initialize_this_with(rhs);
}

void SparseMatrix::deallocate_memory()
{
    if (values) delete[] values;
    values = NULL;
    if (row_indexes) delete[] row_indexes;
    row_indexes = NULL;
    if (column_indexes) delete[] column_indexes;
    column_indexes = NULL;
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& rhs)
{
    deallocate_memory();
    nb_of_elements = rhs.nb_of_elements;
    values = new double[nb_of_elements];
    row_indexes = new size_t[nb_of_elements];
    column_indexes = new size_t[nb_of_elements];
    current_element = rhs.current_element;
    row_index_of_last_element = rhs.row_index_of_last_element;
    column_index_of_last_element = rhs.column_index_of_last_element;
    is_empty = rhs.is_empty;
    initialize_this_with(rhs);
    return *this;
}

void SparseMatrix::initialize_this_with(const SparseMatrix& rhs)
{
    for (size_t i  = 0 ; i < nb_of_elements ; ++i)
    {
        values[i]         = rhs.values[i];
        row_indexes[i]    = rhs.row_indexes[i];
        column_indexes[i] = rhs.column_indexes[i];
    }
}

void SparseMatrix::add_element_in_row_order(const size_t& i, const size_t& j, const double& val)
{
    if (current_element>=nb_of_elements)
    {
        THROW("SparseMatrix::add_element_in_row_order",SparseMatrixException,
              "Can't set a new element in the matrix because the maximum number of elements was reached. Declare a bigger matrix.");
    }
    if (not(position_in_matrix_is_correct(i,j)))
    {
        THROW("SparseMatrix::add_element_in_row_order",SparseMatrixException,
              "Elements must be added in a strictly increasing order (row-wise).");
    }

	values[current_element] = val;
	row_indexes[current_element] = i;
	column_indexes[current_element] = j;
	row_index_of_last_element = i;
	column_index_of_last_element = j;
	current_element++;
	is_empty = false;

}


bool SparseMatrix::position_in_matrix_is_correct(const size_t& i, const size_t& j) const
{
    return is_empty || (i > row_index_of_last_element) || ((i == row_index_of_last_element) && (j > column_index_of_last_element));
}

double SparseMatrix::get(const size_t& i, const size_t& j) const
{
    bool element_was_found = false;
    bool all_elements_were_scanned = (nb_of_elements==0);
    size_t k = 0;
    while (not(element_was_found || all_elements_were_scanned))
    {
        element_was_found = (row_indexes[k] == i) && (column_indexes[k] == j);
        all_elements_were_scanned = (++k == nb_of_elements);
    }
    if (not(element_was_found))
    {
        return 0;
    }
    return values[k-1];
}

size_t SparseMatrix::size() const
{
    return nb_of_elements;
}

size_t * SparseMatrix::get_columns() const
{
    return column_indexes;
}

size_t * SparseMatrix::get_rows() const
{
    return row_indexes;
}

double * SparseMatrix::get_values() const
{
    return values;
}

const SparseMatrix SparseMatrix::operator*(const double& a) const
{
    SparseMatrix ret(nb_of_elements);
    for (size_t k = 0 ; k < nb_of_elements ; ++k)
    {
        ret.values[k] = a*values[k];
        ret.row_indexes[k] = row_indexes[k];
        ret.column_indexes[k] = column_indexes[k];
    }
    ret.current_element = current_element;
    ret.row_index_of_last_element = row_index_of_last_element;
    ret.column_index_of_last_element = column_index_of_last_element;
    ret.is_empty = is_empty;
    return ret;
}

const SparseMatrix operator*(const double& a, const SparseMatrix& M)
{
    return (M*a);
}

void SparseMatrix::multiply_in_place_by(const double& a)
{
    for (size_t k = 0 ; k < nb_of_elements ; ++k)
    {
        values[k] *= a;
    }
}

SparseMatrix SparseMatrix::append(const SparseMatrix& rhs) const
{
	const size_t nc = this->nb_of_elements + rhs.nb_of_elements;
	SparseMatrix C(nc);
	size_t k = 0;
	for (size_t i = 0; i < this->nb_of_elements; ++i)
	{
		C.row_indexes[k] = row_indexes[i];
		C.column_indexes[k] = column_indexes[i];
		C.values[k] = values[i];
		k++;
	}
	for (size_t i = 0; i < rhs.nb_of_elements; ++i)
	{
		C.row_indexes[k] = rhs.row_indexes[i];
		C.column_indexes[k] = column_indexes[i];
		C.values[k] = values[i];
		k++;
	}
	if (k>0)
	{
		C.is_empty = false;
		C.row_index_of_last_element    = C.row_indexes[k-1];
		C.column_index_of_last_element = C.column_indexes[k-1];
		C.current_element              = k;
	}
	return C;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& rhs) const
{
	if (this->is_empty) return rhs;
	if (rhs.is_empty) return *this;
	const bool all_elements_of_rhs_are_after_this =
			which_element_comes_first(row_index_of_last_element, column_index_of_last_element, row_indexes[0], column_indexes[0])==ELEMENT_IN_A_COMES_FIRST;
	if (all_elements_of_rhs_are_after_this)
	{
		return append(rhs);
	}
    const size_t nc = count_nb_of_elements_in_sum(*this, rhs);
    SparseMatrix C(nc);
    add(*this, rhs, C);
    return C;
}

size_t SparseMatrix::count_nb_of_elements_in_sum(const SparseMatrix& A, const SparseMatrix& B) const
{
    size_t ka = 0;
    size_t kb = 0;
    size_t nc = 0;
    for(;(ka<A.nb_of_elements)&&(kb<B.nb_of_elements);)
    {
        const WhichElementComesFirst element_coming_first = which_element_comes_first(A.row_indexes[ka], A.column_indexes[ka], B.row_indexes[kb], B.column_indexes[kb]);
        switch (element_coming_first)
        {
            case ELEMENT_IN_A_COMES_FIRST:
                ++ka;
                break;
            case ELEMENT_IN_B_COMES_FIRST:
                ++kb;
                break;
            case ELEMENTS_ARE_IN_THE_SAME_POSITION:
                ++ka;
                ++kb;
                break;
        }
        ++nc;
    }
    nc += (A.nb_of_elements-ka) + (B.nb_of_elements-kb);
    return nc;
}

WhichElementComesFirst SparseMatrix::which_element_comes_first(const size_t la, const size_t ca, const size_t lb, const size_t cb) const
{
    const size_t element_in_A_comes_first          = ((la<lb) || ((la==lb) && (ca<cb)));
    const size_t elements_are_in_the_same_position = (la==lb) && (ca==cb);

    if (element_in_A_comes_first)          return ELEMENT_IN_A_COMES_FIRST;
    if (elements_are_in_the_same_position) return ELEMENTS_ARE_IN_THE_SAME_POSITION;
                                           return ELEMENT_IN_B_COMES_FIRST;

}

void SparseMatrix::add(const SparseMatrix& A, const SparseMatrix& B, SparseMatrix& C) const
{
    size_t ka = 0;
    size_t kb = 0;
    size_t kc = 0;
    for(;(ka<A.nb_of_elements)&&(kb<B.nb_of_elements);)
    {
        const WhichElementComesFirst element_coming_first = which_element_comes_first(A.row_indexes[ka], A.column_indexes[ka], B.row_indexes[kb], B.column_indexes[kb]);
        switch (element_coming_first)
        {
            case ELEMENT_IN_A_COMES_FIRST:
                C.row_indexes[kc]    = A.row_indexes[ka];
                C.column_indexes[kc] = A.column_indexes[ka];
                C.values[kc]         = A.values[ka];
                ++ka;
                break;
            case ELEMENT_IN_B_COMES_FIRST:
                C.row_indexes[kc]    = B.row_indexes[kb];
                C.column_indexes[kc] = B.column_indexes[kb];
                C.values[kc]         = B.values[kb];
                ++kb;
                break;
            case ELEMENTS_ARE_IN_THE_SAME_POSITION:
                C.row_indexes[kc]    = A.row_indexes[ka];
                C.column_indexes[kc] = A.column_indexes[ka];
                C.values[kc]         = A.values[ka] + B.values[kb];
                ++ka;
                ++kb;
                break;
        }
        ++kc;
    }
    fetch_extra_elements_if_matrices_have_different_nb_of_elements(ka, A, kc, C);
    fetch_extra_elements_if_matrices_have_different_nb_of_elements(kb, B, kc, C);
    C.is_empty = (kc==0);
    if (not(C.is_empty))
    {
        C.row_index_of_last_element    = C.row_indexes[kc-1];
        C.column_index_of_last_element = C.column_indexes[kc-1];
    }
    C.current_element              = kc;
}

SparseMatrix& SparseMatrix::operator+=(const SparseMatrix& rhs)
{
    return (*this = *this + rhs);
}

void SparseMatrix::fetch_extra_elements_if_matrices_have_different_nb_of_elements(size_t& k, const SparseMatrix& M, size_t& kc, SparseMatrix& C) const
{
    for (;k<M.nb_of_elements;++k,++kc)
    {
        C.row_indexes[kc]    = M.row_indexes[k];
        C.column_indexes[kc] = M.column_indexes[k];
        C.values[kc]         = M.values[k];
    }
}

const SparseMatrix eye(const size_t& n)
{
    SparseMatrix ret(n);
    for (size_t k = 0 ; k < n ; ++k)
    {
        ret.row_indexes[k] = k;
        ret.column_indexes[k] = k;
        ret.values[k] = 1;
    }
    ret.current_element = n-1;
    ret.is_empty = false;
    return ret;
}

const SparseMatrix sum(const std::vector<SparseMatrix>& v)
{
    if (v.empty())   return SparseMatrix();
    if (v.size()==1) return v.at(0);
                     return sum(v.at(0), std::vector<SparseMatrix>(v.begin()+1, v.end()));
}

const SparseMatrix sum(const SparseMatrix& accumulator, const std::vector<SparseMatrix>& v)
{
    if (v.empty())           return accumulator;
    if (accumulator.empty()) return sum(v.at(0), std::vector<SparseMatrix>(v.begin()+1, v.end()));
                             return SparseMatrix(accumulator, sum(v.at(0), std::vector<SparseMatrix>(v.begin()+1, v.end())));
}

void SparseMatrix::divide_in_place(const double& lambda)
{
    for (size_t k = 0 ; k < nb_of_elements; ++k)
    {
        values[k] /= lambda;
    }
}

const SparseMatrix SparseMatrix::operator/(const double& lambda) const
{
    SparseMatrix ret(*this);
    ret.divide_in_place(lambda);
    return ret;
}

const SparseMatrix SparseMatrix::operator-(const SparseMatrix& rhs) const
{
    SparseMatrix ret(rhs);
    ret.multiply_in_place_by(-1);
    return SparseMatrix(*this, ret);
}

bool SparseMatrix::operator==(const SparseMatrix& rhs) const
{
    const size_t n = rhs.size();
    if (size() != n)                                                      return false;
    if (is_empty != rhs.is_empty)                                         return false;
    if (row_index_of_last_element != rhs.row_index_of_last_element)       return false;
    if (column_index_of_last_element != rhs.column_index_of_last_element) return false;
    for (size_t i = 0 ; i < n ; ++i)
    {
        if (row_indexes[i] != rhs.row_indexes[i])                         return false;
        if (column_indexes[i] != rhs.column_indexes[i])                   return false;
        if (values[i] != rhs.values[i])                                   return false;
    }
                                                                          return true;
}

bool SparseMatrix::operator!=(const SparseMatrix& rhs) const
{
    return not(*this == rhs);
}

::std::ostream& operator<<(::std::ostream& os, const SparseMatrix& bar)
{
    size_t nb_of_rows = 0;
    for (size_t i = 0 ; i < bar.nb_of_elements ; ++i)
    {
        if (bar.row_indexes[i] > nb_of_rows)
        {
            nb_of_rows = bar.row_indexes[i];
        }
    }
    ++nb_of_rows; // indexes start at 0...

    size_t nb_of_columns = 0;
    for (size_t i = 0 ; i < bar.nb_of_elements ; ++i)
    {
        if (bar.column_indexes[i] > nb_of_columns)
        {
            nb_of_columns = bar.column_indexes[i];
        }
    }
    ++nb_of_columns; // indexes start at 0...
    size_t k = 0;
    os.width(2);
    os.precision(0);
    os.setf(os.fixed);
    os << std::endl;
    if (bar.is_empty)
    {
        os << "empty matrix (can hold " << bar.nb_of_elements << " values)" << std::endl;
    }
    else
    {
        os << "(" << nb_of_rows << "x" << nb_of_columns << "):" << std::endl;
        for (size_t i = 0 ; i < nb_of_rows ; ++i)
        {
            os << "| ";
            for (size_t j = 0 ; j < nb_of_columns ; ++j)
            {
                if ((k < bar.nb_of_elements) && (bar.row_indexes[k] == i) && (bar.column_indexes[k] == j))
                {
                    os.width(11);
                    os.precision(4);
                    os.setf(os.scientific);
                    os.setf(os.right);
                    os << bar.values[k];

                    k++;
                }
                else
                {
                    os.width(11);
                    os.precision(4);
                    os.setf(os.scientific);
                    os.setf(os.right);
                    os << 0;
                }
                os << " ";
            }
            os << "|" << std::endl;
        }
    }
    return os;
}


void SparseMatrix::copy_row_indexes_to(const size_t& n, size_t * const array) const
{
    if (!array)
    {
        THROW("SparseMatrix::copy_row_indexes_to",SparseMatrixException,"Received a null pointer");
    }
    if (n != nb_of_elements)
    {
        THROW("SparseMatrix::copy_row_indexes_to",SparseMatrixException,"n does not match the number of elements");
    }
    for (size_t i = 0 ; i < n ; ++i) array[i] = row_indexes[i];
}

void SparseMatrix::copy_column_indexes_to(const size_t& n, size_t * const array) const
{
    if (!array)
    {
        THROW("SparseMatrix::copy_column_indexes_to",SparseMatrixException,"Received a null pointer");
    }
    if (n != nb_of_elements)
    {
        THROW("SparseMatrix::copy_column_indexes_to",SparseMatrixException,"n does not match the number of elements");
    }
    for (size_t i = 0 ; i < n ; ++i) array[i] = column_indexes[i];
}

void SparseMatrix::copy_values_to(const size_t& n, double * const array) const
{
    if (!array)
    {
        THROW("SparseMatrix::copy_column_indexes_to",SparseMatrixException,"Received a null pointer");
    }
    if (n != nb_of_elements)
    {
        THROW("SparseMatrix::copy_column_indexes_to",SparseMatrixException,"n does not match the number of elements");
    }
    for (size_t i = 0 ; i < n ; ++i) array[i] = values[i];
}

const SparseMatrix abs(SparseMatrix M)
{
    for (size_t i = 0 ; i < M.nb_of_elements ; ++i) M.values[i] = fabs(M.values[i]);
    return M;
}

double SparseMatrix::max() const
{
    double ret = 0;
    for (size_t i = 0 ; i < nb_of_elements ; ++i) ret = values[i]>ret ? values[i]:ret;
    return ret;
}

bool SparseMatrixElementComparator:: operator()(const SparseMatrixElement& lhs, const SparseMatrixElement& rhs) const
{
    if (lhs.row >  rhs.row) return false;
    if (lhs.row == rhs.row) return (lhs.col < rhs.col);
    else                    return true;
}

SparseMatrixElement::SparseMatrixElement(const size_t& row_, const size_t& col_, const double& val_) : row(row_),
                                                                                                       col(col_),
                                                                                                       val(val_)
{
}

SparseMatrix::SparseMatrix(const size_t& n, size_t const * const r, size_t const * const c, double const * const v) : nb_of_elements(n),
    values(NULL),
    row_indexes(NULL),
    column_indexes(0),
    current_element(0),
    row_index_of_last_element(0),
    column_index_of_last_element(0),
    is_empty(n==0)
{
    std::list<SparseMatrixElement> L;
    for (size_t i = 0 ; i < n ; ++i) L.push_back(SparseMatrixElement(r[i], c[i], v[i]));
    L.sort(SparseMatrixElementComparator());
    std::list<SparseMatrixElement>::const_iterator it = L.begin();
    size_t i = 0;
    values         = new double[n];
    row_indexes    = new size_t[n];
    column_indexes = new size_t[n];
    for (; it != L.end() ; ++it)
    {
        row_indexes[i]    = it->row;
        column_indexes[i] = it->col;
        values[i++]       = it->val;
    }
    current_element = n-1;
    row_index_of_last_element = row_indexes[n-1];
    column_index_of_last_element = column_indexes[n-1];
}

