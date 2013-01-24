/*
 * extra_test_assertions.hpp
 *
 * \date 8 oct. 2012, 08:27:53
 *  \author cec
 */

#ifndef EXTRA_TEST_ASSERTIONS_HPP_
#define EXTRA_TEST_ASSERTIONS_HPP_

#define ASSERT_SMALL_RELATIVE_ERROR(expected, actual, tol) ASSERT_NEAR(expected, actual, fabs(expected)*tol > tol ? fabs(expected)*tol:tol)
#define EXPECT_SMALL_RELATIVE_ERROR(expected, actual, tol) EXPECT_NEAR(expected, actual, fabs(expected)*tol > tol ? fabs(expected)*tol:tol)

#endif /* EXTRA_TEST_ASSERTIONS_HPP_ */
