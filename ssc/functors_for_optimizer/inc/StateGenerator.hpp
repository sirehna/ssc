#ifndef __STATE_GENERATOR_HPP__
#define __STATE_GENERATOR_HPP__

#include "State.hpp"
#include "Exception.hpp"
#include <set>

class StateGeneratorException : public Exception
{
    public:
        StateGeneratorException(const char* s) : Exception(s) {}
};



class StateGenerator
{
    public:
        StateGenerator();
        State state(const std::string& name);
        void reset();

    private:
        size_t current_index;
        std::set<std::string> names;
};

#endif
