//
// Created by Thorsten Claus on 16.04.23.
//

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "../../source/repository/RepositoryConfig.h"

using Catch::Matchers::Equals;

TEST_CASE("Repository Config has configured settings path") {
    REQUIRE_THAT(RepositoryConfig::GetConfigFilePath(), Equals("/home/config/settings/Stocks/quotes"));
}