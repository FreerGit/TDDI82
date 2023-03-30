
#include "List.h"

#include "catch.hpp"

using namespace std;
#include <iostream>

TEST_CASE( "Create list" )
{
    cout << "hej" << endl;
    List lst{1,4,2,6,8,9};
    cout << "hej" << endl;

    CHECK(lst.at(0) == 1);
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

