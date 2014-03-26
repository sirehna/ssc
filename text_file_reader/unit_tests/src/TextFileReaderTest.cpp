/*
 * TextFileReaderTest.cpp
 *
 * \date 21 mars 2012, 15:18:47
 *  \author cec
 */

#include "TextFileReaderTest.hpp"
#include "TextFileReader.hpp"

#include "test_macros.hpp"
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <fstream>

TextFileReaderTest::TextFileReaderTest() : a(DataGenerator(718293))
{
}

TextFileReaderTest::~TextFileReaderTest()
{

}

void TextFileReaderTest::SetUp()
{

}

void TextFileReaderTest::TearDown()
{
}

TEST_F(TextFileReaderTest, example)
{
//! [TextFileReaderTest example]
	char filename1 [L_tmpnam];
	char filename2 [L_tmpnam];
	std::ofstream file1 (filename1);
	const std::string contents_file1 = a.random<std::string>();
	const std::string contents_file2 = a.random<std::string>();
	file1 << contents_file1;
	file1.close();
	std::ofstream file2 (filename2);
	file2 << contents_file2;
	file2.close();
	std::vector<std::string> filenames;
	filenames.push_back(filename1);
	filenames.push_back(filename2);
	TextFileReader reader(filenames);
	remove (filename1);
	remove (filename2);
//! [TextFileReaderTest example]
//! [TextFileReaderTest expected output]
	ASSERT_EQ(contents_file1+contents_file2, reader.get_contents());
//! [TextFileReaderTest expected output]
}

TEST_F(TextFileReaderTest, should_represent_newlines_correctly)
{
	char filename [L_tmpnam];
	std::ofstream file (filename);
	const std::string contents_file = a.random<std::string>()()
			                         + std::string("\n")
	                                 + a.random<std::string>()()
	                                 + std::string("\n")
	                                 + a.random<std::string>()();
	file << contents_file;
	file.close();
	std::vector<std::string> filenames;
	filenames.push_back(filename);
	TextFileReader reader(filenames);
	remove (filename);
	ASSERT_EQ(contents_file, reader.get_contents());
}

