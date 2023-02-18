//
// Created by user-leshiy on 13.02.23.
//
#include <gtest/gtest.h>

TEST(SampleTestCase, STC_1to1)
{
	EXPECT_EQ(1, 1);
	ASSERT_EQ(2, 2);
}

TEST(SampleTestCase, STC_Basic)
{
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}

TEST(SampleTestCase, STC_1to2)
{
	EXPECT_EQ(1, 2);
}