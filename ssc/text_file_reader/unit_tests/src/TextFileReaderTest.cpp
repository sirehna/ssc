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

void create_file(const std::string& filename, const std::string& contents);
void create_file(const std::string& filename, const std::string& contents)
{
	remove_file_if_it_exists(filename);
    std::ofstream file(filename);
    file << contents;
    file.close();
}


TEST_F(TextFileReaderTest, example)
{
//! [TextFileReaderTest example]
    const std::string filename1 = "data_for_TextFileReaderTest_1";
    const std::string contents_file1 = a.random<std::string>();
    create_file(filename1, contents_file1);
    const std::string filename2 = "data_for_TextFileReaderTest_2";
    const std::string contents_file2 = a.random<std::string>();
    create_file(filename2, contents_file2);
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
    const std::string contents_file = a.random<std::string>()()
                                             + std::string("\n")
                                     + a.random<std::string>()()
                                     + std::string("\n")
                                     + a.random<std::string>()();
    create_file(filename, contents_file);
    TextFileReader reader(std::vector<std::string>(1, filename));
    remove_file_if_it_exists(filename);
    ASSERT_EQ(contents_file, reader.get_contents());
}

