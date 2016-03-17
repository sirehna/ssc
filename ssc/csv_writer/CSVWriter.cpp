#include "CSVWriter.hpp"
#include "ConvertNumericToString.hpp"

#include <iostream>

CSVWriter::CSVWriter() : data(std::vector<Column>()),
                         nb_of_rows(0),
                         nb_of_columns(0)
{
}

void CSVWriter::append(const std::string& column_title, const std::vector<double>& column_values)
{
    const std::vector<double> resized_values            = resize_if_needed(column_values);
    const Column column                                 = std::make_pair(column_title, resized_values);
    data.push_back(column);
    nb_of_columns++;
}

std::vector<double> CSVWriter::resize_if_needed(const std::vector<double>& column_values)
{
    std::vector<double> resized_column_values = column_values;
    const size_t nb_of_values_in_column       = column_values.size();
    if (nb_of_values_in_column < nb_of_rows) resized_column_values.resize(nb_of_rows,0);
    if (nb_of_values_in_column > nb_of_rows)
    {
        nb_of_rows = nb_of_values_in_column;
        append_zeros_to_all_columns_except_last(nb_of_values_in_column);
    }
    return resized_column_values;
}

void CSVWriter::append_zeros_to_all_columns_except_last(const size_t& new_size)
{
    for (size_t i = 0 ; i < nb_of_columns ; ++i)
    {
        data.at(i).second.resize(new_size, 0);
    }
    nb_of_rows = new_size;
}

std::string CSVWriter::generate() const
{
    const std::string title_line = make_title_line();
    const std::string data_rows  = make_data_rows();
    const std::string output     = title_line + data_rows;
    return output;
}

std::string CSVWriter::make_title_line() const
{
    std::string all_titles_except_last = add_all_titles_except_last();
    std::string last_title = data.back().first;
    std::string title = all_titles_except_last + last_title;
    title = normalize(title) + "\n";
    return title;
}

std::string CSVWriter::normalize(std::string title) const
{
    size_t position = title.find("\n");
    while (position < title.size())
    {
        title = replace_antislash(title, position);
        position = title.find("\n", position+2);
    }
    return title;
}

std::string CSVWriter::replace_antislash(std::string title, const size_t& position) const
{
    std::string slash = "\\";

    title.insert(position, slash.c_str(), 1);
    return title;
}

std::string CSVWriter::add_all_titles_except_last() const
{
    std::string title;
    for (size_t i = 0 ; i < nb_of_columns-1 ; ++i)
    {
        std::string current_title = data.at(i).first;
        title.append(current_title + ",");
    }
    return title;
}

std::string CSVWriter::make_data_rows() const
{
    std::string data_rows;
    for (size_t i = 0 ; i < nb_of_rows ; ++i)
    {
        std::string last_value = convert_to_string<double>(data.back().second.at(i));
        data_rows.append(get_all_values_in_row_except_last(i) + last_value + "\n");
    }
    return data_rows;
}

std::string CSVWriter::get_all_values_in_row_except_last(const size_t& row_idx) const
{
    std::string truncated_row;
    for (size_t j = 0 ; j < nb_of_columns-1 ; ++j)
    {
        std::string value = convert_to_string<double>(data.at(j).second.at(row_idx));
        truncated_row.append(value + ",");
    }
    return truncated_row;
}
