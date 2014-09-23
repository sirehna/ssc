/*
 * TextFileReader.cpp
 *
 * \date 21 mars 2012, 15:13:03
 *  \author cec
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "text_file_reader/TextFileReader.hpp"
#include "exception_handling/Exception.hpp"

using namespace ssc::text_file_reader;

class TextFileReaderException: public Exception
{
    public:
        TextFileReaderException(const char* s) :
                Exception(s)
        {
        }
};

TextFileReader::TextFileReader(const std::vector<std::string>& filenames_) : filenames(filenames_),
contents("")
{
	std::vector<std::string>::const_iterator that_filename = filenames.begin();
	std::stringstream ss;
	for (;that_filename!=filenames.end();++that_filename)
	{
		std::ifstream current_input_file(that_filename->c_str(),std::ifstream::in);
		if (current_input_file.fail())
		{
			std::string error = std::string("Unable to open input file '") + *that_filename + std::string("'");
			THROW("TextFileReader::TextFileReader::TextFileReader(const std::vector<std::string>&)", TextFileReaderException, "Unable to open input file");
		}
		std::string current_line;
		while (!current_input_file.eof())
		{
			getline(current_input_file,current_line);
			ss << current_line;
			if (!current_input_file.eof()) ss << std::endl;
		}
		current_input_file.close();
	}
	contents = ss.str();
}

std::string TextFileReader::get_contents() const
{
	return contents;
}
