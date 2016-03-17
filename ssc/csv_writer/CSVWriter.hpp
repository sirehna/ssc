#ifndef __CSVWRITER__
#define __CSVWRITER__

#include <map>
#include <string>
#include <vector>

namespace ssc
{
    namespace csv_writer
    {
        class CSVWriter
        {
            typedef std::pair<std::string, std::vector<double> > Column;
            public:
                CSVWriter();
                void append(const std::string& column_title, const std::vector<double>& column_values);
                std::string generate() const;

            private:
                std::vector<Column>  data;
                size_t               nb_of_rows;
                size_t               nb_of_columns;

                std::vector<double> resize_if_needed(const std::vector<double>& column_values);
                void append_zeros_to_all_columns_except_last(const size_t& new_size);
                std::string make_title_line() const;
                std::string normalize(std::string title) const;
                std::string replace_antislash(std::string title, const size_t& position) const;
                std::string add_all_titles_except_last() const;
                std::string make_data_rows() const;
                std::string get_all_values_in_row_except_last(const size_t& row_idx) const;
        };
    }
}

#endif
