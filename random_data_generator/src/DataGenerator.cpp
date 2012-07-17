#include "DataGenerator.hpp"
#include "sir_rand.h"
#include <iostream>


//#define MAX_RAND_INT RAND_MAX
#define MAX_RAND_INT 2147483647

#define MIN(a,b) (a<b) ? a : b;
#define MAX(a,b) (a>b) ? a : b;

DataGenerator::DataGenerator(const size_t& seed) : negated(false)
{
    srand(seed);
}

DataGenerator& DataGenerator::no()
{
    negated = true;
    return *this;
}

double DataGenerator::random_double() const
{
    return random_double(-1e6,1e6);
}

double DataGenerator::random_double_greater_than(const double& x0) const
{
    const double max_bound = (x0 < 1e6-5 ? 1e6 : 2*x0);
    return random_double(x0,max_bound);
    
}

int DataGenerator::random_int() const
{
    return random_int(-1e6,1e6);
}

size_t DataGenerator::random_size_t() const
{
    return random_size_t(0,1e4);
}

size_t DataGenerator::random_size_t_greater_than(const size_t& i0) const
{
    const size_t max_bound = (i0 < 1e4-5 ? 1e4 : 2*i0);
    return random_size_t(i0,max_bound);
}

float DataGenerator::random_float() const
{
    return random_float(-1e6,1e6);
}

long DataGenerator::random_long() const
{
    return random_long(-1e3,1e3);
}

short DataGenerator::random_short() const
{
    return random_short(-1e2,1e2);
}



double DataGenerator::random_double(const double& a, const double& b) const
{
    return (b-a)*get_random_number()/MAX_RAND_INT + a;
}

int DataGenerator::random_int(const int& a, const int& b) const
{
    return int(floor(double(b-a)*double(get_random_number())/MAX_RAND_INT + 0.5)) + a;
}

size_t DataGenerator::random_size_t(const size_t& a, const size_t& b) const
{
    return size_t(floor(double(b-a)*double(get_random_number())/MAX_RAND_INT + 0.5)) + a;
}

float DataGenerator::random_float(const float& a, const float& b) const
{
    return (b-a)*float(get_random_number())/float(MAX_RAND_INT) + a;
}

long DataGenerator::random_long(const long& a, const long& b) const
{
    return long(floor(double(b-a)*double(get_random_number())/MAX_RAND_INT + 0.5)) + a;
}

short DataGenerator::random_short(const short& a, const short& b) const
{
    return short(floor(double(b-a)*double(get_random_number())/MAX_RAND_INT + 0.5)) + a;
}

bool DataGenerator::random_bool() const
{
    return (get_random_number()%2) == 0;
}

char DataGenerator::random_char() const
{
    const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    const size_t random_index = get_random_number() % (sizeof(alphanum)/sizeof(char) - 1);
    return alphanum[random_index];
}

const std::string DataGenerator::random_string(const size_t& string_length) const
{
    std::string ret;
    ret.reserve(string_length);
    for (size_t i = 0 ; i < string_length ; ++i)
    {
        ret += random_char();
    }
    return ret;
}

const std::string DataGenerator::random_string(const size_t& min_string_length, const size_t& max_string_length) const
{
    const size_t string_length = random_size_t(min_string_length, max_string_length);
    return random_string(string_length);
}


const std::string DataGenerator::random_string() const
{
    return random_string(GET_A_MIN_STRING_LENGTH, GET_A_MAX_STRING_LENGTH);
}

const std::vector<bool>        DataGenerator::vector_of_random_booleans(const size_t& n) const
{
    std::vector<bool> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_bool());
    }
    return ret;
}

const std::vector<int>         DataGenerator::vector_of_random_integers(const size_t& n, const int& a, const int& b) const
{
    std::vector<int> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_int(a, b));
    }
    return ret;
}

const std::vector<size_t>      DataGenerator::vector_of_random_size_ts(const size_t& n, const size_t& a, const size_t& b) const
{
    std::vector<size_t> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_size_t(a, b));
    }
    return ret;
}

const std::vector<short>       DataGenerator::vector_of_random_shorts(const size_t& n, const short& a, const short& b) const
{
    std::vector<short> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_short(a,b));
    }
    return ret;
}

const std::vector<long>        DataGenerator::vector_of_random_longs(const size_t& n, const long& a, const long& b) const
{
    std::vector<long> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_long(a, b));
    }
    return ret;
}

const std::vector<float>       DataGenerator::vector_of_random_floats(const size_t& n, const float& a, const float& b) const
{
    std::vector<float> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_float(a, b));
    }
    return ret;
}

const std::vector<double>      DataGenerator::vector_of_random_doubles(const size_t& n, const double& a, const double& b) const
{
    std::vector<double> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_double(a,b));
    }
    return ret;
}

const std::vector<double>      DataGenerator::vector_of_random_doubles(const size_t& n) const
{
    const double min_bound = random_double();
    return vector_of_random_doubles(n, min_bound, random_double_greater_than(min_bound));
}

const std::vector<char>        DataGenerator::vector_of_random_chars(const size_t& n) const
{
    std::vector<char> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_char());
    }
    return ret;
}

const std::vector<std::string> DataGenerator::vector_of_random_strings(const size_t& n) const
{
    std::vector<std::string> ret;
    ret.reserve(n);
    for (size_t i = 0 ; i < n ; ++i)
    {
        ret.push_back(random_string());
    }
    return ret;
}

int DataGenerator::get_random_number() const
{
	return static_cast<int>(sir_rand_u01()*MAX_RAND_INT);
    //return rand();
}


const std::pair<int,int> DataGenerator::random_pair_of_int() const
{
    return std::pair<int,int>(random_int(),random_int());
}

template <> double TypedScalarDataGenerator<double>::get() const
{
    if ((forbidden_min==min_bound) && (forbidden_max==max_bound)) return 0;
    const double a = random_double(min_bound, max_bound);
    const bool outside_forbidden_zone = not((a>=forbidden_min)&&(a<=forbidden_max));
    if (outside_forbidden_zone) return a;
    else                        return get();
}

template <> size_t TypedScalarDataGenerator<size_t>::get() const
{
    if ((forbidden_min==min_bound) && (forbidden_max==max_bound)) return 0;
    const size_t a = random_size_t(min_bound, max_bound);
    const bool outside_forbidden_zone = not((a>=forbidden_min)&&(a<=forbidden_max));
    if (outside_forbidden_zone) return a;
    else                        return get();
}

template <> bool TypedScalarDataGenerator<bool>::get() const
{
    return random_bool();
}

template <> std::string TypedScalarDataGenerator<std::string>::get() const
{
    return random_string();
}


template <> std::vector<double> TypedVectorDataGenerator<double>::get() const
{
    return vector_of_random_doubles(size, min_bound, max_bound);
}

template <> std::vector<size_t> TypedVectorDataGenerator<size_t>::get() const
{
    return vector_of_random_size_ts(size, min_bound, max_bound);
}

template<> double get_min_bound<double>()
{
    return -1e10;
}

template<> double get_max_bound<double>()
{
    return 1e10;
}

template<> size_t get_min_bound<size_t>()
{
    return 0;
}

template<> size_t get_max_bound<size_t>()
{
    return 1e7;
}
