#ifndef __STATE_GENERATOR_HPP__
#define __STATE_GENERATOR_HPP__

#include "ssc/functors_for_optimizer/State.hpp"
#include "ssc/exception_handling/Exception.hpp"
#include <set>

class StateGeneratorException : public ssc::exception_handling::Exception
{
    public:
        StateGeneratorException(const char* s) : Exception(s) {}
};



class StateGenerator
{
    public:
        StateGenerator();
        StatePtr state(const std::string& name);
        void reset();

    private:
        size_t current_index;
        std::set<std::string> names;
};

#endif
