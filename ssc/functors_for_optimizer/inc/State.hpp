#ifndef STATES_HPP
#define STATES_HPP

#include <stdlib.h> // For size_t
#include <string>
#include "Parameter.hpp"



class State : public Parameter
{
    public:
      State(const std::string& name_, const size_t& index_);
      NodePtr diff(const StatePtr& state) const;
      std::string get_name() const;
      size_t get_index() const;
      bool operator<(const State& rhs) const;
      ~State();
      void accept(NodeVisitor& v) const;
      NodePtr clone() const;
      bool is_null() const;
      bool equals(const Node& rhs) const;
      using Parameter::equals_derived;
      bool equals_derived(const State& rhs) const;
      std::string get_type() const;
      NodePtr simplify() const;


    private:
        State(); // Private & without implementation to disable the use of the default constructor
        std::string name;
        size_t index;
};

typedef std::tr1::shared_ptr<State> StatePtr;

#endif
