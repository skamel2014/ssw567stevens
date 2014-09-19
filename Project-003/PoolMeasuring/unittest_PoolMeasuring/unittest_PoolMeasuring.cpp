#include "gtest/gtest.h"
#include "PoolHeader.h"

TEST(testWorking, simpleTest)
{
	int i;
	i = 4;
	EXPECT_EQ(4, i);
}

// Check if THIS is a POSITIVE INTEGER
TEST(testPosInteger, posIntegerTest)
{
	EXPECT_EQ(true, isPositiveInteger("270"));
	EXPECT_EQ(true, isPositiveInteger("92024303292"));
	EXPECT_EQ(false, isPositiveInteger("-15"));
	EXPECT_EQ(false, isPositiveInteger("Salad"));
	EXPECT_EQ(false, isPositiveInteger(""));
}

// Check: Is THIS is greater than THAT?
TEST(testGreater, greaterThanTest)
{
	EXPECT_EQ(true, isGreaterThan("200", "6"));
	EXPECT_EQ(true, isGreaterThan("200", ""));
	EXPECT_EQ(false, isGreaterThan("2", "50"));
	EXPECT_EQ(false, isGreaterThan("", "50"));
	EXPECT_EQ(false, isGreaterThan("", ""));
}

// Check: Is THIS is less than THAT?
TEST(testLess, lessThanTest)
{
	EXPECT_EQ(true, isLessThan("5", "20"));
	EXPECT_EQ(true, isLessThan("5", ""));
	EXPECT_EQ(false, isLessThan("15", "3"));
	EXPECT_EQ(false, isLessThan("", "38"));
	EXPECT_EQ(false, isLessThan("", ""));
}