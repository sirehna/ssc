#ifndef STATES_HPP
#define STATES_HPP

#include <stdlib.h> // For size_t
#include <string>
#include "Parameter.hpp"

class State : public Parameter
{
    public:
      State(const std::string& name_, const size_t& index_);

      std::string get_name() const;
      size_t get_index() const;
      Grad grad() const;
      Hes hes() const;

      bool operator<(const State& rhs) const;
    private:
        State(); // Private & without implementation to disable the use of the default constructor
        std::string name;
        size_t index;

};

::std::ostream& operator<<(::std::ostream& os, const State& bar);

#endif
