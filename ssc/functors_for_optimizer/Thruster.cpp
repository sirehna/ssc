#include "Thruster.hpp"
#include "StateGenerator.hpp"
#include "State.hpp"
#include "LinearInterpolator.hpp"
#include <cmath>

#define PI 4.*atan(1.)


ThrusterConfig::ThrusterConfig() :
command_range_in_model(MinMax()),
usable_command_range(MinMax()),
angle_range_in_model(MinMax()),
usable_angle_range(MinMax()),
Fmax(double()),
Pmax(double()),
normalized_thrust_for_each_command(std::vector<double>()),
normalized_Fx_eff_for_each_angle(std::vector<double>()),
normalized_Fy_eff_for_each_angle(std::vector<double>()),
normalized_power_for_each_command(std::vector<double>())
{
}


Thruster::Thruster(const std::string& thruster_name, StateGenerator& make, const ThrusterConfig& conf) :
name(thruster_name),
command(make.state(name + " rpm")),
angle(make.state(name + "theta")),
states(StateList()),
Fx_eff(new LinearInterpolator(conf.angle_range_in_model.min, conf.angle_range_in_model.max,conf.normalized_Fx_eff_for_each_angle)),
Fy_eff(new LinearInterpolator(conf.angle_range_in_model.min,conf.angle_range_in_model.max,conf.normalized_Fy_eff_for_each_angle)),
P(new LinearInterpolator(conf.command_range_in_model.min, conf.command_range_in_model.max,conf.normalized_power_for_each_command)),
thrust(new LinearInterpolator(conf.command_range_in_model.min,conf.command_range_in_model.max,conf.normalized_thrust_for_each_command))
{
    states.push_back(command);
    states.push_back(angle);
}

StateList Thruster::get_states() const
{
    return states;
}

ValType Thruster::get_Fx() const
{
    auto ret = [&]() -> double {return (**command)*cos(**angle);};
    return ret;
}

std::vector<ValType> Thruster::get_grad_Fx() const
{
    std::vector<ValType> ret;
    auto dFx_dcommand = [&]() -> double {return cos(**angle);};
    auto dFx_dangle   = [&]() -> double {return -(**command)*sin(**angle);};
    ret.push_back(dFx_dcommand);
    ret.push_back(dFx_dangle);
    return ret;
}

