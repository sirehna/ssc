#include "StateGenerator.hpp"


StateGenerator::StateGenerator() : current_index(0), names(std::set<std::string>())
{
}

StatePtr StateGenerator::state(const std::string& name)
{
    bool name_already_given = not(names.insert(name).second);
    if (name_already_given)
    {
        THROW("State StateGenerator::state(const std::string& name)", StateGeneratorException, "a state with that name was already generated");
    }
    return StatePtr(new State(name, current_index++));
}

void StateGenerator::reset()
{
    current_index = 0;
    names.clear();
}

