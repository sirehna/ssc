
#ifndef GETA
#define GETA

#define GET_A_MIN_STRING_LENGTH 3
#define GET_A_MAX_STRING_LENGTH 17

#include <math.h> // For floor
#include <stdlib.h> // For size_t
#include <string>
#include <vector>
#include <set>

#include "test_macros.hpp"

template <class C> class TypedScalarDataGenerator;
template <class C> class TypedVectorDataGenerator;
template <class C> class TypedSetDataGenerator;

class DataGenerator
{
    public:
        template <class T> TypedScalarDataGenerator<T> random() const
        {
            return TypedScalarDataGenerator<T>(*this);
        }
        template <class T> TypedVectorDataGenerator<T> random_vector_of() const
        {
            return TypedVectorDataGenerator<T>(*this);
        }
        template <class T> TypedSetDataGenerator<T> random_set_of() const
        {
            return TypedSetDataGenerator<T>(*this);
        }

        DataGenerator(const size_t& seed);
        virtual ~DataGenerator(){}
        bool random_bool() const;
        int    random_int() const;
        size_t random_size_t() const;
        size_t random_size_t_greater_than(const size_t& i0) const;
        float  random_float() const;
        long   random_long() const;
        short  random_short() const;
        double random_double() const;
        double random_double_greater_than(const double& x0) const;

        int    random_int(const int& a, const int& b) const;
        size_t random_size_t(const size_t& a, const size_t& b) const;
        float  random_float(const float& a, const float& b) const;
        long   random_long(const long& a, const long& b) const;
        short  random_short(const short& a, const short& b) const;
        double random_double(const double& a, const double& b) const;
        char   random_char() const;
        const std::string random_string(const size_t& string_length) const;
        const std::string random_string(const size_t& min_string_length, const size_t& max_string_length) const;
        const std::string random_string() const;

        const std::vector<bool>        vector_of_random_booleans(const size_t& n) const;
        const std::vector<int>         vector_of_random_integers(const size_t& n, const int& a, const int& b) const;
        const std::vector<size_t>      vector_of_random_size_ts(const size_t& n, const size_t& a, const size_t& b) const;
        const std::vector<short>       vector_of_random_shorts(const size_t& n, const short& a, const short& b) const;
        const std::vector<long>        vector_of_random_longs(const size_t& n, const long& a, const long& b) const;
        const std::vector<float>       vector_of_random_floats(const size_t& n, const float& a, const float& b) const;
        const std::vector<double>      vector_of_random_doubles(const size_t& n, const double& a, const double& b) const;
        const std::vector<double>      vector_of_random_doubles(const size_t& n) const;
        const std::vector<char>        vector_of_random_chars(const size_t& n) const;
        const std::vector<std::string> vector_of_random_strings(const size_t& n) const;

        const std::pair<int,int> random_pair_of_int() const;

        virtual DataGenerator& no();

    protected:
        bool negated;
    private:
        DataGenerator();
        int get_random_number() const;
};

template <class T> T get_min_bound() {return T();}
template <class T> T get_max_bound() {return T();}
template<> double get_min_bound<double>();
template<> double get_max_bound<double>();
template<> size_t get_min_bound<size_t>();
template<> size_t get_max_bound<size_t>();


template <class T> class TypedScalarDataGenerator : public DataGenerator
{
    public:
        TypedScalarDataGenerator(const DataGenerator& rhs) : DataGenerator(rhs),
                                                             min_bound(get_min_bound<T>()),
                                                             max_bound(get_max_bound<T>()),
                                                             forbidden_min(get_max_bound<T>()),
                                                             forbidden_max(get_min_bound<T>())
        {}

        T operator()()
        {
            T tmp = get();
            min_bound = get_min_bound<T>();
            max_bound = get_max_bound<T>();
            negated = false;
            return tmp;
        }

        TypedScalarDataGenerator& greater_than(const T& t)
        {
            if (negated)
            {
                max_bound = t;
            }
            else
            {
                min_bound = t;
            }
            return *this;
        }

        TypedScalarDataGenerator& between(const T& m, const T& M)
        {
            if (not(negated))
            {
                min_bound = m;
                max_bound = M;
            }
            else
            {
                forbidden_min = m;
                forbidden_max = M;
            }
            return *this;
        }

        TypedScalarDataGenerator<T>& no()
        {
            negated = true;
            return *this;
        }

        TypedScalarDataGenerator<T>& but_not()
        {
            return no();
        }

        TypedScalarDataGenerator<T>& but()
        {
            negated = false;
            return *this;
        }

        TypedScalarDataGenerator<T>& outside(const T& t1, const T& t2)
        {
            return (but_not().between(t1, t2)).but();
        }

        TypedScalarDataGenerator<T>& but_not(const T& t)
        {
            return outside(t, t).but();
        }



    private:
        T get() const;
        T min_bound;
        T max_bound;
        T forbidden_min;
        T forbidden_max;
};



template <class T> class TypedVectorDataGenerator : public DataGenerator
{
    public:
        TypedVectorDataGenerator(const DataGenerator& rhs) : DataGenerator(rhs),
                                                             size(0),
                                                             min_bound(get_min_bound<T>()),
                                                             max_bound(get_max_bound<T>())
        {}

        TypedVectorDataGenerator& of_size(const size_t& n)
        {
            size = n;
            return *this;
        }

        std::vector<T> operator()()
        {
            std::vector<T> tmp = get();
            negated = false;
            min_bound = get_min_bound<T>();
            max_bound = get_max_bound<T>();
            return tmp;
        }

        TypedVectorDataGenerator& greater_than(const T& t)
        {
            if (negated)
            {
                max_bound = t;
            }
            else
            {
                min_bound = t;
            }
            return *this;
        }

        TypedVectorDataGenerator<T>& no()
        {
            negated = true;
            return *this;
        }

    private:
        std::vector<T> get() const;
        size_t size;
        T min_bound;
        T max_bound;
};

template <class T> class TypedSetDataGenerator : public DataGenerator
{
    public:
        TypedSetDataGenerator(const DataGenerator& rhs) : DataGenerator(rhs),
                                                          size(0),
                                                          min_bound(get_min_bound<T>()),
                                                          max_bound(get_max_bound<T>())
        {}

        TypedSetDataGenerator& of_size(const size_t& n)
        {
            size = n;
            return *this;
        }

        std::set<T> operator()()
        {
            std::set<T> tmp = get();
            negated = false;
            min_bound = get_min_bound<T>();
            max_bound = get_max_bound<T>();
            return tmp;
        }

        TypedSetDataGenerator& greater_than(const T& t)
        {
            if (negated)
            {
                max_bound = t;
            }
            else
            {
                min_bound = t;
            }
            return *this;
        }

        TypedSetDataGenerator<T>& no()
        {
            negated = true;
            return *this;
        }

    private:
        std::set<T> get() const;
        size_t size;
        T min_bound;
        T max_bound;
};



#endif
