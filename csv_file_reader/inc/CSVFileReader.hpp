#ifndef	VALIDATE_AGAINST_CSV_FILE 
#define VALIDATE_AGAINST_CSV_FILE
#include "Exception.hpp"
#include "extra_test_assertions.hpp"



#include <vector>
#include <string>


#include "Exception.hpp"

class CSVFileReaderException: public Exception {
public:
	CSVFileReaderException(const char* s) :
			Exception(s) {
	}
};


class CSVFileReader
{
	public:
		CSVFileReader(const char* filename, const size_t& expected_nb_of_columns, const char& separator=',');
		bool has_more_data() const;
		std::vector<double> get_line();

	private:
		CSVFileReader();
		std::vector<std::string> titles;
		std::vector<std::vector<double> > values;
		const std::vector<std::string> convert_line_to_vector_of_strings(const std::string& line, const char& separator) const;
		const std::vector<double> convert_line_to_vector_of_doubles(const std::string& line, const char& separator) const;
		void extract_column_titles(std::ifstream& file, const size_t& expected_nb_of_columns, const char& separator);
		void extract_values(std::ifstream& file, const char& separator);
		std::vector<std::vector<double> >::const_iterator that_line;
};

#endif

