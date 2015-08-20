/*
 * TextFileReader.cpp
 *
 * \date 21 mars 2012, 15:13:03
 *  \author cec
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "ssc/text_file_reader/TextFileReader.hpp"
#include "ssc/text_file_reader/TextFileReaderException.hpp"

using namespace ssc::text_file_reader;

void TextFileReader::fill(const std::string& filename)
{
    std::ifstream current_input_file(filename.c_str(),std::ifstream::in);

    std::ifstream t(filename.c_str());

    current_input_file.seekg(0, std::ios::end);
    contents.reserve(contents.size() + current_input_file.tellg());
    current_input_file.seekg(0, std::ios::beg);

    contents.append(std::istreambuf_iterator<char>(current_input_file),
                    std::istreambuf_iterator<char>());
}

TextFileReader::TextFileReader(const std::vector<std::string>& filenames) :
contents()
{
    std::vector<std::string>::const_iterator that_filename = filenames.begin();
    for (;that_filename!=filenames.end();++that_filename)
    {
        fill(*that_filename);
    }
}

TextFileReader::TextFileReader(const std::string& filename) :
contents()
{
    fill(filename);
}

std::string TextFileReader::get_contents() const
{
    return contents;
}
