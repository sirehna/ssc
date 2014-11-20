/*
 * TextFileReaderTest.cpp
 *
 * \date 21 mars 2012, 15:18:47
 *  \author cec
 */

#include <iostream>
#include <fstream>

#include "TextFileReaderTest.hpp"
#include "ssc/text_file_reader/TextFileReader.hpp"
#include "ssc/macros/test_macros.hpp"

using namespace ssc::text_file_reader;

TextFileReaderTest::TextFileReaderTest() : a(ssc::random_data_generator::DataGenerator(718293))
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

inline void remove_file_if_it_exists (const std::string& name)
{
  struct stat buffer;
  if (stat (name.c_str(), &buffer) == 0) remove (name.c_str());
}

TEST_F(TextFileReaderTest, example)
{
//! [TextFileReaderTest example]
	const std::string filename1 = "data_for_TextFileReaderTest_1";
	const std::string filename2 = "data_for_TextFileReaderTest_2";
	remove_file_if_it_exists(filename1);
	remove_file_if_it_exists(filename2);
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
    remove_file_if_it_exists(filename1);
	remove_file_if_it_exists(filename2);
//! [TextFileReaderTest example]
//! [TextFileReaderTest expected output]
    ASSERT_EQ(contents_file1+contents_file2, reader.get_contents());
//! [TextFileReaderTest expected output]
}

TEST_F(TextFileReaderTest, should_represent_newlines_correctly)
{
    const std::string filename = "data_for_TextFileReaderTest";
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
    remove (filename.c_str());
    ASSERT_EQ(contents_file, reader.get_contents());
}

