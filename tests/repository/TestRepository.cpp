//
// Created by Thorsten Claus on 18.04.23.
//

#include "Repository.h"
#include <String.h>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <iostream>
#include <fstream>

using Catch::Matchers::Equals;

TEST_CASE("Test read config file contents") {

    const char *path = "config";

    std::ofstream outFile("config");
    outFile << "{symbol: 'APPL'}" << std::endl;
    outFile.close();

    BString *fileContent = new BString("");
    Repository repository;
    repository.ReadFile(*path, *fileContent);

    REQUIRE_THAT(std::string(fileContent->String()), Equals("{symbol: 'APPL'}"));
}

TEST_CASE("Test write config file contents") {
    FAIL("TBD");

    // Have some content
    // write with test function
    // read with C++ stream
    // compare.

}
