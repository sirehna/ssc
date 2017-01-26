#ifndef __SPARSEMATRIX__
#define __SPARSEMATRIX__

#ifdef WIN32
#include <ciso646>
#endif

#include <vector>
#include "ssc/exception_handling/Exception.hpp"

namespace ssc
{
    namespace matrix_and_vector_classes
    {
        class SparseMatrixException : public ssc::exception_handling::Exception
        {
            public:
                SparseMatrixException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line) {}
        };


        typedef enum WhichElementComesFirst {ELEMENT_IN_A_COMES_FIRST,
                                             ELEMENT_IN_B_COMES_FIRST,
                                             ELEMENTS_ARE_IN_THE_SAME_POSITION} WhichElementComesFirst;

        struct SparseMatrixElement
        {
            SparseMatrixElement(const size_t& row_, const size_t& col_, const double& val_);
            size_t row;
            size_t col;
            double val;
        };

        struct SparseMatrixElementComparator
        {
            bool operator()(const SparseMatrixElement& lhs, const SparseMatrixElement& rhs) const;
        };

        class SparseMatrix
        {
            public:
                SparseMatrix();
                SparseMatrix(const SparseMatrix& A, const SparseMatrix& B);
                SparseMatrix(const size_t& nb_of_elements_);
                SparseMatrix(const SparseMatrix& rhs);
                SparseMatrix(const size_t& n, size_t const * const r, size_t const * const c, double const * const v);
                SparseMatrix& operator=(const SparseMatrix& rhs);
                SparseMatrix& operator+=(const SparseMatrix& rhs);
                ~SparseMatrix();
                bool empty() const;
                void add_element_in_row_order(const size_t& i, const size_t& j, const double& val);
                double get(const size_t& i, const size_t& j) const;
                size_t size() const;
                size_t * get_columns() const;
                size_t * get_rows() const;
                double * get_values() const;
                const SparseMatrix operator*(const double& a) const;
                void multiply_in_place_by(const double& a);
                SparseMatrix operator+(const SparseMatrix& rhs) const;
                friend const SparseMatrix eye(const size_t& n);
                void divide_in_place(const double& lambda);
                const SparseMatrix operator/(const double& lambda) const;
                const SparseMatrix operator-(const SparseMatrix& rhs) const;
                bool operator==(const SparseMatrix& rhs) const;
                bool operator!=(const SparseMatrix& rhs) const;
                void copy_row_indexes_to(const size_t& n, size_t * const array) const;
                void copy_column_indexes_to(const size_t& n, size_t * const array) const;
                void copy_values_to(const size_t& n, double * const array) const;
                double max() const;

            private:
                void deallocate_memory();
                void initialize_this_with(const SparseMatrix& rhs);
                bool position_in_matrix_is_correct(const size_t& i, const size_t& j) const;
                SparseMatrix append(const SparseMatrix& rhs) const;

                size_t nb_of_elements;
                double *values;
                size_t *row_indexes;
                size_t *column_indexes;
                size_t current_element;
                size_t row_index_of_last_element;
                size_t column_index_of_last_element;
                bool is_empty;

                void add(const SparseMatrix& A, const SparseMatrix& B, SparseMatrix& C) const;
                size_t count_nb_of_elements_in_sum(const SparseMatrix& A, const SparseMatrix& B) const;
                WhichElementComesFirst which_element_comes_first(const size_t la, const size_t ca, const size_t lb, const size_t cb) const;
                void fetch_extra_elements_if_matrices_have_different_nb_of_elements(size_t& k, const SparseMatrix& M, size_t& kc, SparseMatrix& C) const;

            friend ::std::ostream& operator<<(::std::ostream& os, const SparseMatrix& bar);
            friend const SparseMatrix abs(SparseMatrix M);
        };
        ::std::ostream& operator<<(::std::ostream& os, const SparseMatrix& bar);
        const SparseMatrix operator*(const double& a, const SparseMatrix& M);

        const SparseMatrix eye(const size_t& n);

        const SparseMatrix sum(const std::vector<SparseMatrix>& v);
        const SparseMatrix sum(const SparseMatrix& accumulator, const std::vector<SparseMatrix>& v);

        const SparseMatrix abs(SparseMatrix M);
    }
}
#endif
