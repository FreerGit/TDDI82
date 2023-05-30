#include <iostream>
#include <vector>
using namespace std;

template <typename Container>
typename Container::value_type sum(Container const & c)
{
    typename Container::value_type sum {};
    for ( auto && val: c )
        sum = sum + val;
    return sum;
}
TEST_CASE("double") {
    vector<double> v {1.2,3,4.4};
    REQUIRE(Approx(sum(v)) == 8.6);
}
TEST_CASE("int") {
    vector<int> v {1,2,3,2,4,5,7};
    REQUIRE(sum(v) == 24);
}