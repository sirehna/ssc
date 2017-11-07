/*
 * TwoDimensionalInterpolationVariableStepTest.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: cady
 */

#include "ssc/interpolation/TwoDimensionalInterpolationVariableStep.hpp"
#include "TwoDimensionalInterpolationVariableStepTest.hpp"

TwoDimensionalInterpolationVariableStepTest::TwoDimensionalInterpolationVariableStepTest() : a(ssc::random_data_generator::DataGenerator(5456466))
{
}

TwoDimensionalInterpolationVariableStepTest::~TwoDimensionalInterpolationVariableStepTest()
{
}

void TwoDimensionalInterpolationVariableStepTest::SetUp()
{
}

void TwoDimensionalInterpolationVariableStepTest::TearDown()
{
}

TEST_F(TwoDimensionalInterpolationVariableStepTest, example)
{
//! [TwoDimensionalSplinesTest example]
    std::vector<std::vector<double> > M;
    std::vector<double> v;
    v.push_back(883);v.push_back(969);v.push_back(1059);v.push_back(1153);v.push_back(1251);v.push_back(1353);v.push_back(1459);v.push_back(1569);v.push_back(1683);v.push_back(1801);M.push_back(v);v.clear();
    v.push_back(886);v.push_back(972);v.push_back(1062);v.push_back(1156);v.push_back(1254);v.push_back(1356);v.push_back(1462);v.push_back(1572);v.push_back(1686);v.push_back(1804);M.push_back(v);v.clear();
    v.push_back(891);v.push_back(977);v.push_back(1067);v.push_back(1161);v.push_back(1259);v.push_back(1361);v.push_back(1467);v.push_back(1577);v.push_back(1691);v.push_back(1809);M.push_back(v);v.clear();
    v.push_back(898);v.push_back(984);v.push_back(1074);v.push_back(1168);v.push_back(1266);v.push_back(1368);v.push_back(1474);v.push_back(1584);v.push_back(1698);v.push_back(1816);M.push_back(v);v.clear();
    v.push_back(907);v.push_back(993);v.push_back(1083);v.push_back(1177);v.push_back(1275);v.push_back(1377);v.push_back(1483);v.push_back(1593);v.push_back(1707);v.push_back(1825);M.push_back(v);v.clear();
    v.push_back(918);v.push_back(1004);v.push_back(1094);v.push_back(1188);v.push_back(1286);v.push_back(1388);v.push_back(1494);v.push_back(1604);v.push_back(1718);v.push_back(1836);M.push_back(v);v.clear();
    v.push_back(931);v.push_back(1017);v.push_back(1107);v.push_back(1201);v.push_back(1299);v.push_back(1401);v.push_back(1507);v.push_back(1617);v.push_back(1731);v.push_back(1849);M.push_back(v);v.clear();
    v.push_back(946);v.push_back(1032);v.push_back(1122);v.push_back(1216);v.push_back(1314);v.push_back(1416);v.push_back(1522);v.push_back(1632);v.push_back(1746);v.push_back(1864);M.push_back(v);v.clear();
    v.push_back(963);v.push_back(1049);v.push_back(1139);v.push_back(1233);v.push_back(1331);v.push_back(1433);v.push_back(1539);v.push_back(1649);v.push_back(1763);v.push_back(1881);M.push_back(v);v.clear();
    v.push_back(982);v.push_back(1068);v.push_back(1158);v.push_back(1252);v.push_back(1350);v.push_back(1452);v.push_back(1558);v.push_back(1668);v.push_back(1782);v.push_back(1900);M.push_back(v);v.clear();
    std::vector<double> x, y;
    for (size_t i = 0 ; i < 10 ; ++i)
    {
        x.push_back(1.+(double)i);
        y.push_back(21.+(double)i);
    }
    ssc::interpolation::TwoDimensionalInterpolationVariableStep spline(x,y,M);
    ASSERT_DOUBLE_EQ(883, spline.f(1.,21.));
    ASSERT_DOUBLE_EQ(886, spline.f(2.,21.));
    ASSERT_DOUBLE_EQ(891, spline.f(3.,21.));

    ASSERT_DOUBLE_EQ(982, spline.f(10,21));
    ASSERT_DOUBLE_EQ(1900, spline.f(10,30));
    ASSERT_DOUBLE_EQ(1801, spline.f(1,30));
    ASSERT_DOUBLE_EQ((1275+1377+1286+1388)/4., spline.f(5.5,25.5));
}
