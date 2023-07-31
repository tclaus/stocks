//
// Created by Thorsten Claus on 11.05.23.
//

#ifndef STOCKS_TESTQUOTEFORMATTER_CPP
#define STOCKS_TESTQUOTEFORMATTER_CPP

#include "QuoteFormatter.h"

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

using Catch::Matchers::Equals;


TEST_CASE("Test formatting lower float numbers to human readable format.") {
    // A number below what is 'large' should not be formatted

    float notALargeNumber = 42;

    char *charWithLargeNumber = QuoteFormatter::HumanReadableLargeNumber(notALargeNumber);
    REQUIRE_THAT(std::string(charWithLargeNumber), Equals("42"));
}

TEST_CASE("Test formatting large float numbers to human readable format") {
    // should become "1 Million"
    float largeNumber = 1'000'000;

    char *charWithLargeNumber = QuoteFormatter::HumanReadableLargeNumber(largeNumber);
    REQUIRE_THAT(std::string(charWithLargeNumber), Equals("1 Million"));
}


#endif //STOCKS_TESTQUOTEFORMATTER_CPP
