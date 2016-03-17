#include "ConvertNumericToStringTest.hpp"
#include "ssc/macros/test_macros.hpp"

void ConvertNumericToStringTest::SetUp()
{
}

void ConvertNumericToStringTest::TearDown()
{
}

size_t ConvertNumericToStringTest::nb_of_zeros_in_exponents_on_current_platform() const
{
    std::ostringstream strs;
    strs << std::setprecision(1);
    strs.setf(std::ios::scientific,std::ios::floatfield);
    strs << double(0);
    const std::string str = strs.str();
    if (str == "0.0e+0")    return 1;
    if (str == "0.0e+00")   return 2;
    if (str == "0.0e+000")  return 3;
    if (str == "0.0e+0000") return 4;
    return 0;
}

TEST_F(ConvertNumericToStringTest, should_be_able_to_convert_to_string_from_bool)
{
    EXPECT_EQ("false",convert_to_string<bool>(false));
    EXPECT_EQ("true",convert_to_string<bool>(true));
}

TEST_F(ConvertNumericToStringTest, should_be_able_to_convert_to_string_from_int)
{
    EXPECT_EQ("123456",convert_to_string<size_t>(123456));
    EXPECT_EQ("-987654321",convert_to_string<int>(-987654321));
}

TEST_F(ConvertNumericToStringTest, number_of_zeros_in_exponent_should_be_either_two_or_three)
{
    const size_t nb_of_zeros = nb_of_zeros_in_exponents_on_current_platform();
    const bool could_detect_nb_of_zeros = ((nb_of_zeros==2) or (nb_of_zeros==3)) ? true : false;
    ASSERT_TRUE(could_detect_nb_of_zeros);
}

TEST_F(ConvertNumericToStringTest, should_be_able_to_convert_to_string_from_double)
{
    const std::string actual = convert_to_string<double>(98765431.123456789);
    if (nb_of_zeros_in_exponents_on_current_platform()==2)
        ASSERT_EQ("9.8765431123456791e+07", actual);
    else
        ASSERT_EQ("9.8765431123456791e+007", actual);
}

