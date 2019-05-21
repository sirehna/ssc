/*
 * YamlParser.cpp
 *
 * \date 27 août 2012, 13:04:19
 * \author cec
 */

#include "ssc/yaml_parser/YamlParser.hpp"
#include "yaml.h"
#include <sstream>

using namespace ssc::yaml_parser;

YamlParser::YamlParser(const std::string& contents_to_parse) : contents(contents_to_parse)
{

}

YAML::Node& YamlParser::convert_stream_to_yaml_node(const std::string& input_data, YAML::Node& node) const
{
    std::stringstream stream(input_data);
    YAML::Parser parser(stream);
    parser.GetNextDocument(node);
    return node;
}
