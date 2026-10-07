#include "gtest_lite.h"

#include "errors.h"
#include "parsing_utils.h"

TEST(IsWhitespace, SpaceTabAndCarriageReturn) {
  EXPECT_TRUE(IsWhitespace(' '));
  EXPECT_TRUE(IsWhitespace('\t'));
  EXPECT_TRUE(IsWhitespace('\r'));
}

TEST(IsWhitespace, LettersDigitsAndNewlineAreNotWhitespace) {
  EXPECT_FALSE(IsWhitespace('a'));
  EXPECT_FALSE(IsWhitespace('0'));
  EXPECT_FALSE(IsWhitespace('\n'));
}

TEST(Split, EmptyTextGivesOneEmptyPart) {
  std::vector<std::string> parts = Split("", '.');
  ASSERT_EQ(parts.size(), 1u);
  EXPECT_EQ(parts[0], "");
}

TEST(Split, TextWithoutDelimiterIsOnePart) {
  std::vector<std::string> parts = Split("2024", '.');
  ASSERT_EQ(parts.size(), 1u);
  EXPECT_EQ(parts[0], "2024");
}

TEST(Split, ThreeParts) {
  std::vector<std::string> parts = Split("2024.3.11", '.');
  ASSERT_EQ(parts.size(), 3u);
  EXPECT_EQ(parts[0], "2024");
  EXPECT_EQ(parts[1], "3");
  EXPECT_EQ(parts[2], "11");
}

TEST(Split, EmptyPartsAreKept) {
  std::vector<std::string> parts = Split("1..2", '.');
  ASSERT_EQ(parts.size(), 3u);
  EXPECT_EQ(parts[1], "");
}

TEST(Split, DelimiterAtBothEnds) {
  std::vector<std::string> parts = Split(":5:", ':');
  ASSERT_EQ(parts.size(), 3u);
  EXPECT_EQ(parts[0], "");
  EXPECT_EQ(parts[1], "5");
  EXPECT_EQ(parts[2], "");
}

TEST(Trim, RemovesSpacesOnBothSides) { EXPECT_EQ(Trim("  abc \t\r"), "abc"); }

TEST(Trim, KeepsInnerSpaces) { EXPECT_EQ(Trim(" a  b "), "a  b"); }

TEST(Trim, EmptyAndBlankTextGiveEmptyString) {
  EXPECT_EQ(Trim(""), "");
  EXPECT_EQ(Trim(" \t\r "), "");
}

TEST(Trim, TextWithoutSpacesIsUnchanged) { EXPECT_EQ(Trim("abc"), "abc"); }

TEST(ParseDigits, ReadsNumbers) {
  EXPECT_EQ(ParseDigits("0", 2, "x"), 0);
  EXPECT_EQ(ParseDigits("07", 2, "x"), 7);
  EXPECT_EQ(ParseDigits("2024", 4, "x"), 2024);
}

TEST(ParseDigits, EmptyTextIsSyntaxError) {
  EXPECT_THROW(ParseDigits("", 2, "x"), SyntaxError);
}

TEST(ParseDigits, TooManyDigitsIsSyntaxError) {
  EXPECT_THROW(ParseDigits("123", 2, "x"), SyntaxError);
}

TEST(ParseDigits, LetterIsSyntaxError) {
  EXPECT_THROW(ParseDigits("1a", 2, "x"), SyntaxError);
}

TEST(ParseDigits, SignIsSyntaxError) {
  EXPECT_THROW(ParseDigits("-1", 2, "x"), SyntaxError);
  EXPECT_THROW(ParseDigits("+1", 2, "x"), SyntaxError);
}

TEST(ParseDigits, SpaceInsideIsSyntaxError) {
  EXPECT_THROW(ParseDigits("1 2", 3, "x"), SyntaxError);
}

TEST(ParseDigits, MessageNamesTheField) {
  try {
    ParseDigits("zz", 2, "Месяц");
    EXPECT_TRUE(false);
  } catch (const SyntaxError& error) {
    EXPECT_TRUE(std::string(error.what()).find("Месяц") != std::string::npos);
  }
}

TEST(CheckRange, AcceptsBounds) {
  EXPECT_NO_THROW(CheckRange(1, 1, 12, "x"));
  EXPECT_NO_THROW(CheckRange(12, 1, 12, "x"));
  EXPECT_NO_THROW(CheckRange(5, 1, 12, "x"));
}

TEST(CheckRange, RejectsBelowAndAbove) {
  EXPECT_THROW(CheckRange(0, 1, 12, "x"), RangeError);
  EXPECT_THROW(CheckRange(13, 1, 12, "x"), RangeError);
}

TEST(CheckRange, MessageContainsRangeAndValue) {
  try {
    CheckRange(13, 1, 12, "Месяц");
    EXPECT_TRUE(false);
  } catch (const RangeError& error) {
    std::string message = error.what();
    EXPECT_TRUE(message.find("Месяц") != std::string::npos);
    EXPECT_TRUE(message.find("1..12") != std::string::npos);
    EXPECT_TRUE(message.find("13") != std::string::npos);
  }
}

TEST(Errors, HierarchyAllowsCatchingByBaseClass) {
  EXPECT_THROW(throw SyntaxError("x"), LessonError);
  EXPECT_THROW(throw RangeError("x"), LessonError);
  EXPECT_THROW(throw RangeError("x"), std::runtime_error);
}

TEST(StripUtf8Bom, RemovesLeadingBom) {
  std::string text = "\xEF\xBB\xBF" "abc";
  StripUtf8Bom(&text);
  EXPECT_EQ(text, std::string("abc"));
}

TEST(StripUtf8Bom, LeavesTextWithoutBomUnchanged) {
  std::string text = "abc";
  StripUtf8Bom(&text);
  EXPECT_EQ(text, std::string("abc"));
}

TEST(StripUtf8Bom, RemovesOnlyOneBomAndOnlyAtStart) {
  std::string text = "a\xEF\xBB\xBF";
  StripUtf8Bom(&text);
  EXPECT_EQ(text, std::string("a\xEF\xBB\xBF"));
}

TEST(StripUtf8Bom, HandlesShortStrings) {
  std::string empty;
  std::string partial = "\xEF\xBB";
  StripUtf8Bom(&empty);
  StripUtf8Bom(&partial);
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(partial, std::string("\xEF\xBB"));
}

TEST(ZeroPad, PadsShortNumbersWithZeros) {
  EXPECT_EQ(ZeroPad(7, 2), std::string("07"));
  EXPECT_EQ(ZeroPad(0, 2), std::string("00"));
  EXPECT_EQ(ZeroPad(45, 4), std::string("0045"));
}

TEST(ZeroPad, DoesNotTruncateLongNumbers) {
  EXPECT_EQ(ZeroPad(12345, 4), std::string("12345"));
  EXPECT_EQ(ZeroPad(10, 2), std::string("10"));
}
