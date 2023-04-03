
#include "List.h"

#include "catch.hpp"
#include <sstream>
#include <iterator>

TEST_CASE( "Create list" )
{
    {
    List<int> lst{1,4,2,6,8,9};

    CHECK(lst.at(0) == 1);
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);
    List<int> l2;
    l2 = lst;
    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
    }
    {
        List<int> lst{-1,-5,10,5,5,5,5};
        CHECK(lst.at(0) == -1);
        CHECK(lst.at(1) == -5);
        CHECK(lst.size() == 7);
        lst.push_front(100);
        lst.push_back(-100);
        CHECK(lst.at(0) == 100);
        CHECK(lst.at(8) == -100);
    }
    {
        List<int> lst{1,2,3};
        List<int> lst2;
        lst2 = std::move(lst);

        CHECK(lst.size() == 0);
        CHECK(lst2.at(0) == 1);
        CHECK(lst.empty());
    }
    {
        List<int> lst{1,2,3};
        
        CHECK(lst.front() == 1);
        CHECK(lst.back() == 3);
    }
    {
        const List<int> lst{1,2,3};
        CHECK(lst.at(0) == 1);
    }
    
}


TEST_CASE( "Iterator" ) {
    SECTION(" increment ") {
        List<int> lst{2,3,1,5};
        std::stringstream ss;
        for ( auto it = lst.begin(); it != lst.end(); ++it )
        {
          ss << *it << ' ';
        }

        CHECK(ss.str() == "2 3 1 5 ");
    }
    SECTION(" decrement ") {
        List<int> lst{2,3,1,5};
        std::stringstream ss;
        auto rb { std::make_reverse_iterator(lst.end()) };
        auto re { std::make_reverse_iterator(lst.begin()) };
        for ( auto it = rb; it != re; ++it )
        {
          ss << (*it) << ' ';
        }

        CHECK(ss.str() == "5 1 3 2 ");
    }
    SECTION(" complex datatype ") {
        List<std::string> lst{"hej","svej","dej"};
        std::stringstream ss;
        for ( auto it = lst.begin(); it != lst.end(); ++it )
        {
          ss << *it << ' ';
        }

        CHECK(ss.str() == "hej svej dej ");
    }
}
