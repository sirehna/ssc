/*
 * parse_unit_value.hpp
 *
 *  Created on: Apr 28, 2014
 *      Author: cady
 */

#ifndef PARSE_UNIT_VALUE_HPP_
#define PARSE_UNIT_VALUE_HPP_

#include "yaml.h"

namespace ssc
{
    namespace yaml_parser
    {
        struct UV
        {
            UV() : value(0), unit("") {}
            UV(const double v, const std::string& u) : value(v), unit(u) {}
            double value;
            std::string unit;
        };

        void operator >> (const YAML::Node& node, UV& g);
        void parse_uv(const YAML::Node& node, double& d);
        void parse_uv(const YAML::Node& node, std::vector<double>& d);
        double decode(const UV& uv);
    }
}
#endif /* PARSE_UNIT_VALUE_HPP_ */
