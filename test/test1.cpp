#include <catch.hpp>
#include "backends/cpp/vector.hpp"
#include "backends/cpp/algorithm.hpp"

TEST_CASE( "initial test", "[something]" )
{
    auto myVec = backends::vector<int>(1);
    myVec.front() = 13;
    backends::fill(myVec, 12);
    REQUIRE( myVec.front() == 12 );
}