/*
 * parse_unit_value.cpp
 *
 *  Created on: Apr 28, 2014
 *      Author: cady
 */

#include "ssc/decode_unit/DecodeUnit.h"
#include "parse_unit_value.hpp"


void ssc::yaml_parser::parse_uv(const YAML::Node& node, std::vector<double>& d)
{
    std::string unit = "";
    node["unit"] >> unit;
    const double factor = ssc::decode_unit::decodeUnit(unit);
    node["values"] >> d;
    for (std::vector<double>::iterator it = d.begin() ; it != d.end() ; ++it)
    {
        *it *= factor;
    }
}

void ssc::yaml_parser::parse_uv(const YAML::Node& node, double& d)
{
    UV uv;
    node >> uv;
    d = decode(uv);
}

void ssc::yaml_parser::operator >> (const YAML::Node& node, UV& g)
{
    node["unit"] >> g.unit;
    node["value"] >> g.value;
}

double ssc::yaml_parser::decode(const UV& uv)
{
    return uv.value * ssc::decode_unit::decodeUnit(uv.unit);
}
