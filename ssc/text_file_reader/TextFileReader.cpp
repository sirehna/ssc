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
    if (not(current_input_file.is_open()))
    {
        THROW(__PRETTY_FUNCTION__, TextFileReaderException, "Unable to open file '" << filename << "' for reading: maybe the file does not exist or you do not have read permission");
    }

    std::ifstream t(filename.c_str());
    
    current_input_file.seekg(0, std::ios::end);
    const size_t nb_of_characters = (size_t)current_input_file.tellg();
    if (nb_of_characters == 0)
    {
        std::cerr << "Warning: file '" << filename << "' is empty.";
        return;
    }
    contents.reserve(contents.size() + nb_of_characters);
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
