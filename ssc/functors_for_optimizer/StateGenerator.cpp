#include "ssc/functors_for_optimizer/StateGenerator.hpp"

#if defined(_MSC_VER)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#define not !
#endif

using namespace ssc::functors_for_optimizer;

StateGenerator::StateGenerator() : current_state_index(0), state_names(), current_parameter_index(0)
{
}

StatePtr StateGenerator::state(const std::string& name)
{
    bool name_already_given = not(state_names.insert(name).second);
    if (name_already_given)
    {
        THROW(__PRETTY_FUNCTION__, StateGeneratorException, "a state with that name was already generated");
    }
    return StatePtr(new State(name, current_state_index++));
}

ParameterPtr StateGenerator::parameter(const double val)
{
    return ParameterPtr(new Parameter(val, current_parameter_index++));
}

void StateGenerator::reset()
{
    current_state_index = 0;
    state_names.clear();
    current_parameter_index = 0;
}

size_t StateGenerator::total_number_of_states() const
{
    return state_names.size();
}

size_t StateGenerator::total_number_of_parameters() const
{
    return current_parameter_index;
}
