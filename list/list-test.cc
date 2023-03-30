
#include "List.h"

#include "catch.hpp"

TEST_CASE( "Create list" )
{
    {
    List lst{1,4,2,6,8,9};

    CHECK(lst.at(0) == 1);
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
    }
    {
        List lst{-1,-5,10,5,5,5,5};
        CHECK(lst.at(0) == -1);
        CHECK(lst.at(1) == -5);
        CHECK(lst.size() == 7);
        lst.push_front(100);
        lst.push_back(-100);
        CHECK(lst.at(0) == 100);
        CHECK(lst.at(8) == -100);
    }
    {
        List lst{1,2,3};
        List lst2;
        lst2 = std::move(lst);

        CHECK(lst.size() == 0);
        CHECK(lst2.at(0) == 1);
        CHECK(lst.empty());
    }
    {
        List lst{1,2,3};
        
        CHECK(lst.front() == 1);
        CHECK(lst.back() == 3);
    }
    {
        const List lst{1,2,3};
        CHECK(lst.at(0) == 1);
    }
    
}

