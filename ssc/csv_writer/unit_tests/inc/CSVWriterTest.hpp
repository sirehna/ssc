#ifndef __SIR_CSVWRITERTEST__
#define __SIR_CSVWRITERTEST__

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ssc/csv_writer/CSVWriter.hpp"

class CSVWriterTest : public ::testing::Test
{
    protected:
        CSVWriterTest() : csv(CSVWriter()),
                          title_column1(std::string()),
                          title_column2(std::string()),
                          title_column3(std::string()),
                          title_shorter_column(std::string()),
                          title_longer_column(std::string()),
                          column1(std::vector<double>()),
                          column2(std::vector<double>()),
                          column3(std::vector<double>()),
                          shorter_column(std::vector<double>()),
                          longer_column(std::vector<double>())
        {}
        virtual void SetUp();
        virtual void TearDown();

        CSVWriter csv;
        std::string title_column1;
        std::string title_column2;
        std::string title_column3;
        std::string title_shorter_column;
        std::string title_longer_column;

        std::vector<double> column1;
        std::vector<double> column2;
        std::vector<double> column3;
        std::vector<double> shorter_column;
        std::vector<double> longer_column;

};

#endif
