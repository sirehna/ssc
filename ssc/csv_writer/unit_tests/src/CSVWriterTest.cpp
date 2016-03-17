#include "CSVWriterTest.hpp"
#include "ssc/macros/test_macros.hpp"


void CSVWriterTest::SetUp()
{
    title_column1 = "First column";
    title_column2 = "Title of third column is empty";
    title_column3 = "";
    title_shorter_column = "shorter column";
    title_longer_column = "longer column \n has a newline character";

    const double c1[] = {1.2,2.3,3.4,4.5,5.6,6.7};
    const double c2[] = {4,5,6,3.15454212,654875421.321354,5648745.321321};
    const double c3[] = {7,6,5,4,3,2};
    const double sc[] = {3.5,3.2};
    const double lc[] = {1,2,3,4,5,6,7,8,9};

    column1        = std::vector<double>(c1, c1+sizeof(c1)/sizeof(double));
    column2        = std::vector<double>(c2, c2+sizeof(c2)/sizeof(double));
    column3        = std::vector<double>(c3, c3+sizeof(c3)/sizeof(double));
    shorter_column = std::vector<double>(sc, sc+sizeof(sc)/sizeof(double));
    longer_column  = std::vector<double>(lc, lc+sizeof(lc)/sizeof(double));
}

void CSVWriterTest::TearDown()
{
}

TEST_F(CSVWriterTest, DISABLED_append_vectors_of_same_size)
{
    csv.append(title_column1, column1);
    std::string expected_output_linux = "First column\n1.2000000000000000e+00\n2.2999999999999998e+00\n3.3999999999999999e+00\n4.5000000000000000e+00\n5.5999999999999996e+00\n6.7000000000000000e+00\n";
	std::string expected_output_windows = "First column\n1.2000000000000000e+000\n2.2999999999999998e+000\n3.3999999999999999e+000\n4.5000000000000000e+000\n5.5999999999999996e+000\n6.7000000000000002e+000\n";
	std::string actual_output = csv.generate();
	bool output_corresponds_to_linux = (actual_output == expected_output_linux);
	bool output_corresponds_to_windows = (actual_output == expected_output_windows);
	EXPECT_TRUE(output_corresponds_to_linux || output_corresponds_to_windows);

    csv.append(title_column2, column2);
	actual_output = csv.generate();
    expected_output_linux = "First column,Title of third column is empty\n1.2000000000000000e+00,4.0000000000000000e+00\n2.3000000000000000e+00,5.0000000000000000e+00\n3.4000000000000000e+00,6.0000000000000000e+00\n4.5000000000000000e+00,3.15454e+00\n5.6000000000000000e+00,6.54875e+08\n6.7000000000000000e+00,5.64875e+06\n";
	expected_output_windows = "First column,Title of third column is empty\n1.2000000000000000e+000,4.0000000000000000e+000\n2.3000000000000000e+000,5.0000000000000000e+000\n3.4000000000000000e+000,6.0000000000000000e+000\n4.5000000000000000e+000,3.15454e+000\n5.6000000000000000e+000,6.54875e+008\n6.7000000000000000e+000,5.64875e+006\n";
	output_corresponds_to_linux = (actual_output == expected_output_linux);
	output_corresponds_to_windows = (actual_output == expected_output_windows);
	EXPECT_TRUE(output_corresponds_to_linux || output_corresponds_to_windows);
}

TEST_F(CSVWriterTest, DISABLED_append_vectors_of_different_sizes)
{
	
    csv.append(title_column3, column3);
    csv.append(title_shorter_column, shorter_column);
    csv.append(title_longer_column, longer_column);
    std::string expected_output_linux = ",shorter column,longer column \\\n has a newline character\n7.0000000000000000e+00,3.5000000000000000e+00,1.0000000000000000e+00\n6.0000000000000000e+00,3.2000000000000000e+00,2.0000000000000000e+00\n5.0000000000000000e+00,0.0000000000000000e+00,3.0000000000000000e+00\n4.0000000000000000e+00,0.0000000000000000e+00,4.0000000000000000e+00\n3.0000000000000000e+00,0.0000000000000000e+00,5.0000000000000000e+00\n2.0000000000000000e+00,0.0000000000000000e+00,6.0000000000000000e+00\n0.0000000000000000e+00,0.0000000000000000e+00,7.0000000000000000e+00\n0.0000000000000000e+00,0.0000000000000000e+00,8.0000000000000000e+00\n0.0000000000000000e+00,0.0000000000000000e+00,9.0000000000000000e+00\n";
	std::string expected_output_windows = ",shorter column,longer column \\\n has a newline character\n7.0000000000000000e+000,3.5000000000000000e+000,1.0000000000000000e+000\n6.0000000000000000e+000,3.2000000000000000e+000,2.0000000000000000e+000\n5.0000000000000000e+000,0.0000000000000000e+000,3.0000000000000000e+000\n4.0000000000000000e+000,0.0000000000000000e+000,4.0000000000000000e+000\n3.0000000000000000e+000,0.0000000000000000e+000,5.0000000000000000e+000\n2.0000000000000000e+000,0.0000000000000000e+000,6.0000000000000000e+000\n0.0000000000000000e+000,0.0000000000000000e+000,7.0000000000000000e+000\n0.0000000000000000e+000,0.0000000000000000e+000,8.0000000000000000e+000\n0.0000000000000000e+000,0.0000000000000000e+000,9.0000000000000000e+000\n";
	std::string actual_output = csv.generate();
	bool output_corresponds_to_linux = (actual_output == expected_output_linux);
	bool output_corresponds_to_windows = (actual_output == expected_output_windows);
	EXPECT_TRUE(output_corresponds_to_linux || output_corresponds_to_windows);
}

