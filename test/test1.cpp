#include <catch.hpp>
#include "backends/cpp/vector.hpp"
#include "backends/cpp/algorithm.hpp"
#include "backends/cpp/reduction.hpp"

TEST_CASE( "algorithm", "[algorithm]" )
{
    auto myVec = backends::vector<int>(1);
    myVec.front() = 13;
    backends::fill(myVec, 12);
    REQUIRE( myVec.front() == 12 );
}

TEST_CASE( "reduction", "[reduction]" )
{
	auto myVec = backends::vector<float>{1, 2, 3, 4};
	float sum  = backends::sum(myVec);
	float mean = backends::mean(myVec);
    REQUIRE( sum  == 10 );
    REQUIRE( mean == Approx(2.5f).epsilon(0.01));
}