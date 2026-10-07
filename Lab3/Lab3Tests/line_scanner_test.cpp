#include "gtest_lite.h"

#include "errors.h"
#include "line_scanner.h"

TEST(LineScanner, ReadsTokensSeparatedBySingleSpaces) {
  LineScanner scanner("abc def");
  EXPECT_EQ(scanner.ReadToken("a"), "abc");
  EXPECT_EQ(scanner.ReadToken("b"), "def");
}

TEST(LineScanner, SkipsLeadingAndRepeatedSpaces) {
  LineScanner scanner("   abc     def  ");
  EXPECT_EQ(scanner.ReadToken("a"), "abc");
  EXPECT_EQ(scanner.ReadToken("b"), "def");
}

TEST(LineScanner, TabsAndCarriageReturnSeparateTokens) {
  LineScanner scanner("a\tb\r");
  EXPECT_EQ(scanner.ReadToken("a"), "a");
  EXPECT_EQ(scanner.ReadToken("b"), "b");
}

TEST(LineScanner, ReadTokenOnEmptyLineIsSyntaxError) {
  LineScanner scanner("");
  EXPECT_THROW(scanner.ReadToken("дата"), SyntaxError);
}

TEST(LineScanner, ReadTokenOnlySpacesIsSyntaxError) {
  LineScanner scanner("    ");
  EXPECT_THROW(scanner.ReadToken("дата"), SyntaxError);
}

TEST(LineScanner, ReadTokenErrorNamesTheField) {
  LineScanner scanner("");
  try {
    scanner.ReadToken("время");
    EXPECT_TRUE(false);
  } catch (const SyntaxError& error) {
    EXPECT_TRUE(std::string(error.what()).find("время") != std::string::npos);
  }
}

TEST(LineScanner, ReadsQuotedText) {
  LineScanner scanner("\"Иванов Иван\"");
  EXPECT_EQ(scanner.ReadQuoted(), "Иванов Иван");
}

TEST(LineScanner, ReadsEmptyQuotedText) {
  LineScanner scanner("\"\"");
  EXPECT_EQ(scanner.ReadQuoted(), "");
}

TEST(LineScanner, ReadQuotedSkipsSpacesBeforeQuote) {
  LineScanner scanner("   \"abc\"");
  EXPECT_EQ(scanner.ReadQuoted(), "abc");
}

TEST(LineScanner, QuotedTextKeepsInnerSpaces) {
  LineScanner scanner("\"  a  b  \"");
  EXPECT_EQ(scanner.ReadQuoted(), "  a  b  ");
}

TEST(LineScanner, ReadQuotedWithoutOpeningQuoteIsSyntaxError) {
  LineScanner scanner("Иванов");
  EXPECT_THROW(scanner.ReadQuoted(), SyntaxError);
}

TEST(LineScanner, ReadQuotedAtEndOfLineIsSyntaxError) {
  LineScanner scanner("   ");
  EXPECT_THROW(scanner.ReadQuoted(), SyntaxError);
}

TEST(LineScanner, ReadQuotedWithoutClosingQuoteIsSyntaxError) {
  LineScanner scanner("\"Иванов");
  EXPECT_THROW(scanner.ReadQuoted(), SyntaxError);
}

TEST(LineScanner, ExpectEndAcceptsEndOfLine) {
  LineScanner scanner("");
  EXPECT_NO_THROW(scanner.ExpectEnd());
}

TEST(LineScanner, ExpectEndAcceptsTrailingSpaces) {
  LineScanner scanner("\"a\"   \t ");
  scanner.ReadQuoted();
  EXPECT_NO_THROW(scanner.ExpectEnd());
}

TEST(LineScanner, ExpectEndRejectsTrailingText) {
  LineScanner scanner("\"a\" extra");
  scanner.ReadQuoted();
  EXPECT_THROW(scanner.ExpectEnd(), SyntaxError);
}

TEST(LineScanner, ReadsDateTimeAndNameInSequence) {
  LineScanner scanner("2024.03.11 09:00 \"Иванов\"");
  EXPECT_EQ(scanner.ReadToken("d"), "2024.03.11");
  EXPECT_EQ(scanner.ReadToken("t"), "09:00");
  EXPECT_EQ(scanner.ReadQuoted(), "Иванов");
  EXPECT_NO_THROW(scanner.ExpectEnd());
}
