/*
 * LinearInterpolationVariableStepTest.cpp
 *
 * \date 10 avr. 2013, 12:52:58
 *  \author cec
 */

#include "LinearInterpolationVariableStepTest.hpp"
#include "LinearInterpolationVariableStep.hpp"
#include "PiecewiseConstantVariableStep.hpp"
#include "InterpolatorException.hpp"
#include "random_increasing_vector.hpp"
#include "extra_test_assertions.hpp"
#include "IndexFinder.hpp"

#define EPS 3e-3


LinearInterpolationVariableStepTest::LinearInterpolationVariableStepTest() : a(DataGenerator(12))
{
}

LinearInterpolationVariableStepTest::~LinearInterpolationVariableStepTest()
{
}

void LinearInterpolationVariableStepTest::SetUp()
{
}

void LinearInterpolationVariableStepTest::TearDown()
{
}

TEST_F(LinearInterpolationVariableStepTest, example)
{
//! [LinearInterpolationVariableStepTest example]
    const std::vector<double> x = {2,5,7,7.5,11,13};
    const std::vector<double> y = {2,2,5,4  ,8 ,7};
    LinearInterpolationVariableStep interpolate(x,y);
//! [LinearInterpolationVariableStepTest example]
//! [LinearInterpolationVariableStepTest expected output]
    ASSERT_DOUBLE_EQ(2, interpolate.f(2));
    ASSERT_DOUBLE_EQ(2, interpolate.f(5));
    ASSERT_DOUBLE_EQ(5, interpolate.f(7));
    ASSERT_DOUBLE_EQ(4, interpolate.f(7.5));
    ASSERT_DOUBLE_EQ(8, interpolate.f(11));
    ASSERT_DOUBLE_EQ(7, interpolate.f(13));

//! [LinearInterpolationVariableStepTest expected output]
}

TEST_F(LinearInterpolationVariableStepTest, should_be_able_to_retrieve_initial_values_bug)
{
    const std::vector<double> x = {2590646681.5750818253,2590646739.3061804771,2590647507.8936319351,2590647639.8501925468,2590648039.1781187057,2590648876.3285222054,2590649850.0800924301,2590650127.3491587639,2590650308.4413080215,2590650835.7462720871,2590650922.1302652359,2590650922.2486286163,2590651716.4692950249,2590651905.6780767441,2590652367.8981146812,2590653250.6430096626,2590654171.5978746414,2590654969.2793812752,2590655437.9171380997,2590656360.0427446365,2590656921.6756033897,2590657096.6664185524,2590657338.9127655029,2590658186.8733530045,2590658207.9641985893,2590658952.6549134254,2590659477.8687958717,2590660432.0627980232,2590661049.5781435966,2590661854.3548269272,2590662167.7148189545,2590662700.007256031,2590663001.6911635399,2590663306.1720843315,2590664207.3722276688,2590665130.893928051,2590665440.390941143,2590665668.4642882347,2590666399.5222496986,2590666445.2499046326,2590667296.6532697678,2590667686.1247301102,2590668241.7560658455,2590668618.4195127487,2590668810.9722127914,2590669027.9408707619,2590669088.8791556358,2590669960.0336780548,2590670674.4166917801,2590670950.8542561531,2590671542.6758332253,2590671548.1177973747,2590672522.5214562416,2590673254.8159770966,2590674019.2934451103,2590674958.245262146,2590675107.7772078514,2590675749.8390874863,2590675766.2688474655,2590676475.784485817,2590677125.3182058334,2590677164.2784142494,2590678004.6099395752,2590678608.7609825134,2590678842.0532021523,2590679125.2787747383};
    const std::vector<double> y = {453055631.82882922888,7129451673.3185071945,9899357229.2317523956,7524872323.2361154556,-1199043797.8549640179,7084989605.1586713791,2139262845.04291749,3806649838.5569233894,6725904183.9345722198,-4802166701.2297706604,-68396398.890604451299,-8740238562.439540863,7684265881.592004776,-9899055320.1098175049,3770207723.4115829468,-652782436.8921431303,1243996606.4935603142,-5206398931.9083871841,278476400.83092707396,9444700051.1350326538,-2974125331.0381264687,7279528123.8527145386,-6809542397.0589256287,-8662297835.637462616,564125742.55927824974,5470461943.9987096786,-288299150.51595377922,-3938184532.1575694084,-4898107308.0279188156,3796460304.3715696335,576984658.78514242172,-6931352401.3903226852,-5967686025.5585803986,-5633060624.1420097351,-6347974578.5911560059,-3926398249.8693671227,-2419775516.4376187325,8100592963.6690130234,5884040499.7473468781,-1515710866.7370898724,-7345912318.1739349365,2231300019.3637180328,1604609392.143907547,-4672007045.1194925308,-4834298321.0160150528,-8539735584.9053726196,-3771200522.5407185555,6572502302.8035840988,1000539049.8069410324,9177106338.1967182159,7234513248.8180265427,9753608462.6822109222,-1137690006.9685080051,-3602452172.5402469635,2003441126.2172114849,2576545908.2747812271,-4340657957.168636322,-5903005107.4701032639,1599156089.2359912395,452433027.24466085434,-8165699730.7001485825,5764022419.2155065536,5035498807.3847551346,-3263318648.998152256,6431239942.168598175,4953811133.682053566};
    LinearInterpolationVariableStep interpolate(x,y);
    for (size_t k = 0 ; k < 66 ; ++k)
    {
        ASSERT_SMALL_RELATIVE_ERROR(y.at(k), interpolate.f(x.at(k)),EPS);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_be_able_to_retrieve_initial_values)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t k = 0 ; k < n ; ++k)
        {
            ASSERT_SMALL_RELATIVE_ERROR(y.at(k), interpolate.f(x.at(k  )),EPS);
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_zero_if_y_is_constant)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y(n, a.random<double>());
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            //COUT("");
            ASSERT_DOUBLE_EQ(0, interpolate.df(a.random<double>().between(x.front(),x.back())));
//            COUT("");
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_constant_if_points_are_on_straight_line)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const double slope = a.random<double>();
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        std::vector<double> y;
        const double x0 = x.front();
        for (auto it = x.begin() ; it != x.end() ; ++it)
        {
            y.push_back(slope*(*it-x0));
        }
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n ; ++i)
        {
            ASSERT_SMALL_RELATIVE_ERROR(slope, interpolate.df(a.random<double>().between(x.front(),x.back())),EPS);
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, first_derivative_should_be_correctly_computed_for_example_case)
{
    const std::vector<double> x = {2,5,7,7.5,11,13};
    const std::vector<double> y = {2,2,5,4  ,8 ,7};
    LinearInterpolationVariableStep interpolate(x,y);
    for (size_t i = 0 ; i < 1000 ; ++i)
    {
        ASSERT_DOUBLE_EQ(0,interpolate.df(a.random<double>().between(2,5)));
        ASSERT_DOUBLE_EQ(1.5,interpolate.df(a.random<double>().between(5,7)));
        ASSERT_DOUBLE_EQ(-2,interpolate.df(a.random<double>().between(7,7.5)));
        ASSERT_DOUBLE_EQ(4./3.5,interpolate.df(a.random<double>().between(7.5,11)));
        ASSERT_DOUBLE_EQ(-0.5,interpolate.df(a.random<double>().between(11,13)));
    }
}

TEST_F(LinearInterpolationVariableStepTest, second_derivative_should_always_be_zero)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < 20 ; ++i)
        {
            ASSERT_DOUBLE_EQ(0, interpolate.df(a.random<double>().between(x.front(),x.back()),2));
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, interpolated_values_should_be_between_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        for (size_t i = 0 ; i < n-1 ; ++i)
        {
            const double y0 = y.at(i)>y.at(i+1) ? y.at(i+1) : y.at(i);
            const double y1 = y.at(i)>y.at(i+1) ? y.at(i) : y.at(i+1);
            ASSERT_LE(y0, interpolate.f(a.random<double>().between(x.at(i),x.at(i+1))));
            ASSERT_GE(y1, interpolate.f(a.random<double>().between(x.at(i),x.at(i+1))));
        }
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_and_y_have_different_sizes)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const size_t different_n = a.random<size_t>().between(2,100).but_not(n);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(different_n);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), PiecewiseConstantVariableStepException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_x_is_not_in_strictly_increasing_order)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        ASSERT_NO_THROW(LinearInterpolationVariableStep(x,y));
        const size_t idx = a.random<size_t>().between(1,n-1);
        x.at(idx) = x.at(idx-1);
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), IndexFinderException);
        x.at(idx) = x.at(idx-1)-1;
        ASSERT_THROW(LinearInterpolationVariableStep(x,y), IndexFinderException);
    }
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_there_are_not_at_least_two_points)
{
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(),std::vector<double>()), InterpolatorException);
    ASSERT_THROW(LinearInterpolationVariableStep(std::vector<double>(1,a.random<double>()),std::vector<double>(1,a.random<double>())), PiecewiseConstantVariableStepException);
}

TEST_F(LinearInterpolationVariableStepTest, should_throw_if_retrieving_an_x_outside_bounds)
{
    for (size_t i = 0 ; i < 100 ; ++i)
    {
        const size_t n = a.random<size_t>().between(2,100);
        const std::vector<double> x = a_random_vector_of_doubles_in_increasing_order_of_size(a, n);
        const std::vector<double> y = a.random_vector_of<double>().of_size(n);
        LinearInterpolationVariableStep interpolate(x,y);
        ASSERT_THROW(interpolate.f(a.random<double>().outside(x.front(),x.back())), IndexFinderException);
        ASSERT_THROW(interpolate.df(a.random<double>().outside(x.front(),x.back())), IndexFinderException);
        ASSERT_THROW(interpolate.df(a.random<double>().outside(x.front(),x.back()),2), IndexFinderException);
    }
}
