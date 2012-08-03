#include "DataGenerator.hpp"
#include "sir_rand.h"
#include <iostream>


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

int DataGenerator::random_int() const
{
    return random_int(-1e6,1e6);
}

size_t DataGenerator::random_size_t() const
{
    return random_size_t(0,1e4);
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

int DataGenerator::get_random_number() const
{
	return static_cast<int>(sir_rand_u01()*MAX_RAND_INT);
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
