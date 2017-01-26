#ifndef __SPARSEVECTOR__
#define __SPARSEVECTOR__

#include <vector>
#include "ssc/exception_handling/Exception.hpp"
#ifdef WIN32
#include <ciso646>
#endif


namespace ssc
{
    namespace matrix_and_vector_classes
    {
        class SparseVectorException : public ssc::exception_handling::Exception
        {
            public:
                SparseVectorException(const std::string& message, const std::string& file, const std::string& function, const unsigned int line) :
                    Exception(message, file, function, line) {}
        };

        class SparseVector
        {
            public:
                SparseVector();
                SparseVector(const SparseVector& A, const SparseVector& B);
                SparseVector(const size_t& nb_of_elements_);
                SparseVector(const SparseVector& rhs);
                SparseVector& operator=(const SparseVector& rhs);
                SparseVector& operator+=(const SparseVector& rhs);
                ~SparseVector();
                void add_element_in_order(const size_t& i, const double& val);
                size_t size() const;
                bool empty() const;
                double get(const size_t& i) const;
                size_t * get_indexes() const;
                double * get_values() const;
                const SparseVector operator*(const double& a) const;
                void multiply_in_place_by(const double& a);
                SparseVector operator+(const SparseVector& rhs) const;
                void divide_in_place(const double& lambda);
                SparseVector operator/(const double& lambda) const;
                SparseVector operator-(const SparseVector& rhs) const;
                bool operator==(const SparseVector& rhs) const;
                bool operator!=(const SparseVector& rhs) const;
                void copy_indexes_to(const size_t& n, size_t * const array) const;
                void copy_values_to(const size_t& n, double * const array) const;

            private:
                void deallocate_memory();
                void initialize_this_with(const SparseVector& rhs);
                bool position_in_vector_is_correct(const size_t& i) const;

                size_t nb_of_elements;
                double *values;
                size_t *indexes;
                size_t current_element;
                size_t index_of_last_element;
                bool is_empty;
            SparseVector append(const SparseVector& rhs) const;
            void add(const SparseVector& A, const SparseVector& B,
                    SparseVector& C) const;
            size_t count_nb_of_elements_in_sum(const SparseVector& A,
                    const SparseVector& B) const;
            void fetch_extra_elements_if_vectors_have_different_nb_of_elements(
                    size_t& k, const SparseVector& M, size_t& kc,
                    SparseVector& C) const;
            SparseVector sum(const std::vector<SparseVector>& v);
            friend std::ostream& operator <<(std::ostream& os, const SparseVector& bar);
        };

        const SparseVector operator*(const double& a, const SparseVector& M);

        SparseVector sum(const SparseVector& accumulator, const std::vector<SparseVector>& v);
        SparseVector sum(const std::vector<SparseVector>& v);
        ::std::ostream& operator<<(::std::ostream& os, const SparseVector& bar);
    }
}

#endif
