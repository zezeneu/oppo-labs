#include "gtest_lite.h"

#include "errors.h"
#include "time_of_day.h"

TEST(TimeOfDay, ConstructorStoresFields) {
  TimeOfDay time(14, 30);
  EXPECT_EQ(time.hours(), 14);
  EXPECT_EQ(time.minutes(), 30);
}

TEST(TimeOfDay, ConstructorAcceptsBounds) {
  EXPECT_NO_THROW(TimeOfDay(0, 0));
  EXPECT_NO_THROW(TimeOfDay(23, 59));
}

TEST(TimeOfDay, ConstructorRejectsBadHours) {
  EXPECT_THROW(TimeOfDay(24, 0), RangeError);
  EXPECT_THROW(TimeOfDay(-1, 0), RangeError);
}

TEST(TimeOfDay, ConstructorRejectsBadMinutes) {
  EXPECT_THROW(TimeOfDay(10, 60), RangeError);
  EXPECT_THROW(TimeOfDay(10, -1), RangeError);
}

TEST(TimeOfDay, ParseFullForm) {
  EXPECT_EQ(TimeOfDay::Parse("14:30"), TimeOfDay(14, 30));
}

TEST(TimeOfDay, ParseWithoutLeadingZeros) {
  EXPECT_EQ(TimeOfDay::Parse("7:5"), TimeOfDay(7, 5));
}

TEST(TimeOfDay, ParseMidnightAndLastMinute) {
  EXPECT_EQ(TimeOfDay::Parse("00:00"), TimeOfDay(0, 0));
  EXPECT_EQ(TimeOfDay::Parse("23:59"), TimeOfDay(23, 59));
}

TEST(TimeOfDay, ParseWrongNumberOfPartsIsSyntaxError) {
  EXPECT_THROW(TimeOfDay::Parse(""), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("1430"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("14:30:15"), SyntaxError);
}

TEST(TimeOfDay, ParseWrongSeparatorIsSyntaxError) {
  EXPECT_THROW(TimeOfDay::Parse("14.30"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("14-30"), SyntaxError);
}

TEST(TimeOfDay, ParseEmptyPartIsSyntaxError) {
  EXPECT_THROW(TimeOfDay::Parse(":30"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("14:"), SyntaxError);
}

TEST(TimeOfDay, ParseNonDigitsIsSyntaxError) {
  EXPECT_THROW(TimeOfDay::Parse("ab:30"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("14:3x"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("-1:30"), SyntaxError);
}

TEST(TimeOfDay, ParseTooLongPartsIsSyntaxError) {
  EXPECT_THROW(TimeOfDay::Parse("014:30"), SyntaxError);
  EXPECT_THROW(TimeOfDay::Parse("14:300"), SyntaxError);
}

TEST(TimeOfDay, ParseWrongValuesAreRangeError) {
  EXPECT_THROW(TimeOfDay::Parse("24:00"), RangeError);
  EXPECT_THROW(TimeOfDay::Parse("12:60"), RangeError);
  EXPECT_THROW(TimeOfDay::Parse("99:99"), RangeError);
}

TEST(TimeOfDay, ToStringPadsWithZeros) {
  EXPECT_EQ(TimeOfDay(9, 5).ToString(), "09:05");
  EXPECT_EQ(TimeOfDay(0, 0).ToString(), "00:00");
  EXPECT_EQ(TimeOfDay(23, 59).ToString(), "23:59");
}

TEST(TimeOfDay, EqualityAndInequality) {
  EXPECT_TRUE(TimeOfDay(9, 5) == TimeOfDay(9, 5));
  EXPECT_FALSE(TimeOfDay(9, 5) == TimeOfDay(9, 6));
  EXPECT_TRUE(TimeOfDay(9, 5) != TimeOfDay(10, 5));
  EXPECT_FALSE(TimeOfDay(9, 5) != TimeOfDay(9, 5));
}

TEST(TimeOfDay, OrderingComparesHoursThenMinutes) {
  EXPECT_TRUE(TimeOfDay(9, 59) < TimeOfDay(10, 0));
  EXPECT_TRUE(TimeOfDay(10, 0) < TimeOfDay(10, 1));
  EXPECT_FALSE(TimeOfDay(10, 1) < TimeOfDay(10, 1));
  EXPECT_FALSE(TimeOfDay(11, 0) < TimeOfDay(10, 59));
}
