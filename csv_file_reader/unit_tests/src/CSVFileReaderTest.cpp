/*
 * ValidateAgainstCSVTest.cpp
 *
 * \date 8 avr. 2012, 14:10:34
 *  \author cec
 */

#include "CSVFileReaderTest.hpp"
#include "CSVFileReader.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>

ValidateAgainstCSVTest::ValidateAgainstCSVTest() : a(DataGenerator(9487))
{
}

ValidateAgainstCSVTest::~ValidateAgainstCSVTest()
{
}

void ValidateAgainstCSVTest::SetUp()
{
}

void ValidateAgainstCSVTest::TearDown()
{
}

TEST_F(ValidateAgainstCSVTest, example)
{
//! [ValidateAgainstCSVTest example]
	char filename [L_tmpnam];
	tmpnam (filename);
	std::ofstream file (filename);
	const std::string contents = "A,B,C\n1,2,3\n4,5,6\n7,8,9";
	file << contents;
	file.close();
	const size_t invalid_nb_of_columns = a.random<size_t>().but_not(3);
	ASSERT_THROW(CSVFileReader(filename, invalid_nb_of_columns),CSVFileReaderException);
	CSVFileReader validator(filename, 3);
	remove (filename);
//! [ValidateAgainstCSVTest example]
//! [ValidateAgainstCSVTest expected output]
	std::vector<double> current_line;
	ASSERT_TRUE(validator.has_more_data());
	current_line = validator.get_line();
	ASSERT_EQ(3,current_line.size());
	ASSERT_EQ(1, current_line.at(0));
	ASSERT_EQ(2, current_line.at(1));
	ASSERT_EQ(3, current_line.at(2));
	ASSERT_TRUE(validator.has_more_data());
	current_line = validator.get_line();
	ASSERT_EQ(3,current_line.size());
	ASSERT_EQ(4, current_line.at(0));
	ASSERT_EQ(5, current_line.at(1));
	ASSERT_EQ(6, current_line.at(2));
	ASSERT_TRUE(validator.has_more_data());
	current_line = validator.get_line();
	ASSERT_EQ(3,current_line.size());
	ASSERT_EQ(7, current_line.at(0));
	ASSERT_EQ(8, current_line.at(1));
	ASSERT_EQ(9, current_line.at(2));
	ASSERT_FALSE(validator.has_more_data());
	ASSERT_THROW(validator.get_line(),CSVFileReaderException);
//! [ValidateAgainstCSVTest expected output]
}



