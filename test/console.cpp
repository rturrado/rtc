#include "rtc/console.h"

#include <fmt/core.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace rtc::console;


TEST(read_char, empty_options) {
    std::istringstream iss{};
    std::ostringstream oss{};
    auto ret{ read_char(iss, oss, "Do you want to proceed? [y/n] ", std::vector<char>{}) };
    EXPECT_EQ(ret, '\0');
}

TEST(read_char, invalid_input) {
    std::istringstream iss{ "Y\ny\n" };
    std::ostringstream oss{};
    auto ret{ read_char(iss, oss, "Do you want to proceed? [y/n] ", std::vector<char>{ 'y', 'n' })};
    EXPECT_EQ(ret, 'y');
}

TEST(read_char, valid_input_followed_by_invalid_input) {
    std::istringstream iss{ "yabc\ny\n" };
    std::ostringstream oss{};
    auto ret{ read_char(iss, oss, "Do you want to proceed? [y/n] ", std::vector<char>{ 'y', 'n' }) };
    EXPECT_EQ(ret, 'y');
}

TEST(read_char, valid_input) {
    std::istringstream iss{ "y\n" };
    std::ostringstream oss{};
    auto ret{ read_char(iss, oss, "Do you want to proceed? [y/n] ", std::vector<char>{ 'y', 'n' }) };
    EXPECT_EQ(ret, 'y');
}


class read_positive_number_test : public ::testing::Test {
protected:
    static auto RunWith(
        std::istringstream& iss,
        std::ostringstream& oss,
        int lower_limit,
        int upper_limit = std::numeric_limits<int>::max())
    {
        auto message{ upper_limit == std::numeric_limits<int>::max()
            ? fmt::format("Please enter a number (>= {}): ", lower_limit)
            : fmt::format("Please enter a number (between {} and {}): ", lower_limit, upper_limit - 1) };
        return read_positive_number(iss, oss, message, lower_limit, upper_limit);
    }
};

TEST_F(read_positive_number_test, lower_limit) {
    std::istringstream iss{ "0\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 0);
}

TEST_F(read_positive_number_test, number_within_the_limits) {
    std::istringstream iss{ "1\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 1);
}

TEST_F(read_positive_number_test, upper_limit) {
    std::istringstream iss{ "10\n0\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 0);
}

TEST_F(read_positive_number_test, invalid_input) {
    std::istringstream iss{ "abc\n1\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 1);
}

TEST_F(read_positive_number_test, number_with_the_limits_followed_by_invalid_input) {
    std::istringstream iss{ "1 abc\n2\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 2);
}

TEST_F(read_positive_number_test, number_not_within_the_limits) {
    std::istringstream iss{ "123\n4\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 4);
}

TEST_F(read_positive_number_test, negative_number) {
    std::istringstream iss{ "-1\n2\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: number not within the limits"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 2);
}

TEST_F(read_positive_number_test, floating_number) {
    std::istringstream iss{ "1.2\n3\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    EXPECT_EQ(ret, 3);
}


class read_list_of_positive_numbers_test : public ::testing::Test {
protected:
    static auto RunWith(
        std::istringstream& iss,
        std::ostringstream& oss,
        size_t minimum_list_size,
        int lower_limit,
        int upper_limit = std::numeric_limits<int>::max())
    {
        auto message{ upper_limit == std::numeric_limits<int>::max()
            ? fmt::format("Please enter {} or more numbers (>= {}) ('quit' to finish): ",
                minimum_list_size, lower_limit)
            : fmt::format("Please enter {} or more numbers (between {} and {}) ('quit' to finish): ",
                minimum_list_size, lower_limit, upper_limit - 1) };
        return read_list_of_positive_numbers(iss, oss, message, minimum_list_size, lower_limit, upper_limit);
    }
};

TEST_F(read_list_of_positive_numbers_test, lower_limit) {
    std::istringstream iss{ "0 0 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(0, 0));
}

TEST_F(read_list_of_positive_numbers_test, number_within_the_limits) {
    std::istringstream iss{ "1 2 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(1, 2));
}

TEST_F(read_list_of_positive_numbers_test, upper_limit) {
    std::istringstream iss{ "2 10\n9 8 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Error: number {} not within the limits", 10)));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(9, 8));
}

TEST_F(read_list_of_positive_numbers_test, minimum_list_size_equals_zero) {
    std::istringstream iss{};
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 0, 0) };
    EXPECT_EQ(ret.size(), 0);
}

TEST_F(read_list_of_positive_numbers_test, minimum_list_size_equals_one) {
    std::istringstream iss{ "1 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 1, 0) };
    ASSERT_THAT(ret, ::testing::ElementsAre(1));
}

TEST_F(read_list_of_positive_numbers_test, invalid_input) {
    std::istringstream iss{ "abc\n1 2 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(1, 2));
}

TEST_F(read_list_of_positive_numbers_test, number_with_the_limits_followed_by_invalid_input) {
    std::istringstream iss{ "1 2 abc\n3 4 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(3, 4));
}

TEST_F(read_list_of_positive_numbers_test, number_not_within_the_limits) {
    std::istringstream iss{ "1 23\n4 5 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Error: number {} not within the limits", 23)));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(4, 5));
}

TEST_F(read_list_of_positive_numbers_test, negative_number) {
    std::istringstream iss{ "-1 2\n3 4 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Error: number {} not within the limits", -1)));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(3, 4));
}

TEST_F(read_list_of_positive_numbers_test, floating_number) {
    std::istringstream iss{ "1.2 3\n4 5 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("Error: invalid input"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(4, 5));
}

TEST_F(read_list_of_positive_numbers_test, all_tokens_in_one_line) {
    std::istringstream iss{ "1 2 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(1, 2));
}

TEST_F(read_list_of_positive_numbers_test, some_tokens_in_different_lines) {
    std::istringstream iss{ "1\n2 quit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(1, 2));
}

TEST_F(read_list_of_positive_numbers_test, all_tokens_in_different_lines) {
    std::istringstream iss{ "1\n2\nquit\n" };
    std::ostringstream oss{};
    auto ret{ RunWith(iss, oss, 2, 0, 10) };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("OK"));
    ASSERT_THAT(ret, ::testing::ElementsAre(1, 2));
}
