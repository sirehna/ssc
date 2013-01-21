#ifndef __THRUSTERHPP__
#define __THRUSTERHPP__

#include <vector>
#include <tr1/memory>
#include <string>
#include "Node.hpp"

struct MinMax
{
    MinMax() : min(0), max(0) {}  
    MinMax(const double& min_, const double& max_) : min(min_),max(max_){}
    double min;
    double max;
};

struct ThrusterConfig
{
    ThrusterConfig();
    MinMax command_range_in_model;
    MinMax usable_command_range;
    MinMax angle_range_in_model;
    MinMax usable_angle_range;
    double Fmax;
    double Pmax;
    std::vector<double> normalized_thrust_for_each_command;
    std::vector<double> normalized_Fx_eff_for_each_angle;
    std::vector<double> normalized_Fy_eff_for_each_angle;
    std::vector<double> normalized_power_for_each_command;
};

class State;
typedef std::tr1::shared_ptr<State> StatePtr;
typedef std::vector<StatePtr> StateList;

class LinearInterpolator;
class StateGenerator;
class Thruster
{
    public:
       Thruster(const std::string& thruster_name,
                StateGenerator& make_a,
                const ThrusterConfig& conf);
       void update();
       ValType get_Fx() const;
       ValType get_Fy() const;
       std::vector<ValType> get_grad_Fx() const;
       std::vector<ValType> get_grad_Fy() const;
       std::vector<ValType> get_hes_Fx() const;
       std::vector<ValType> get_hes_Fy() const;
       StateList get_states() const;

    private:
        std::string name;
        StatePtr command;
        StatePtr angle;
        StateList states;
        std::tr1::shared_ptr<LinearInterpolator> Fx_eff;
        std::tr1::shared_ptr<LinearInterpolator> Fy_eff;
        std::tr1::shared_ptr<LinearInterpolator> P;
        std::tr1::shared_ptr<LinearInterpolator> thrust;
};

#endif
