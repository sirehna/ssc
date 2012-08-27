/*
 * TextFileReader.hpp
 *
 * \date 21 mars 2012, 15:13:03
 *  \author cec
 */

#include "Exception.hpp"
#include <string>
#include <vector>

class TextFileReaderException: public Exception
{
	public:
		TextFileReaderException(const char* s) :
				Exception(s)
		{
		}
};


#ifndef TEXTFILEREADER_HPP_
#define TEXTFILEREADER_HPP_

/** \author cec
 *  \brief This class was created to separate file reading from YAML parsing.
 *  \details It has the following responsibilities:
 *  - Attempt to read all the supplied text files & report any errors
 *  - Can return the contents read as a string
 *  \section ex1 Example
 *  \snippet yaml_parser/unit_tests/src/TextFileReaderTest.cpp TextFileReaderTest example
 *  \section ex2 Expected output
 *  \snippet yaml_parser/unit_tests/src/TextFileReaderTest.cpp TextFileReaderTest expected output
 */

class TextFileReader
{
	public:
		TextFileReader(const std::vector<std::string>& filenames_);
		std::string get_contents() const;
	private:
		TextFileReader();
		std::vector<std::string> filenames;
		std::string contents;
};

#endif /* TEXTFILEREADER_HPP_ */
