//
// Created by alex on 30.07.2019.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <alx/MaybeError.h>

alx::MaybeError<bool> always_error() { return true; }
alx::MaybeError<bool> never_error() { return {}; }

TEST_CASE("MaybeError", "[alx]")
{
    REQUIRE(always_error().errorSet());
    REQUIRE(!never_error().errorSet());
}
